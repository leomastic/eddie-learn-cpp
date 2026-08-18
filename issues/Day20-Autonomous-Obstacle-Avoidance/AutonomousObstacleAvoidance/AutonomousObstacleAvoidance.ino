#include <Servo.h>

// --- Pin Mapping ---
const int leftDirectionPin = 4;
const int leftSpeedPin = 6;

const int rightDirectionPin = 2;
const int rightSpeedPin = 5;

const int trigPin = 8;
const int echoPin = 7;
const int servoPin = 9;

// --- Speed Calibration ---
const int forwardLeftPwm = 120;
const int forwardRightPwm = 160;

const int turnFromStopLeftPwm = 90;
const int turnFromStopRightPwm = 170;

const int turnWhileMovingLeftPwm = 120;
const int turnWhileMovingRightPwm = 150;

const int reverseLeftPwm = 120;
const int reverseRightPwm = 160;

// --- Servo Calibration & Limits ---
const int servoRightAngle = 33;
const int servoCenterAngle = 93;
const int servoLeftAngle = 153;

// --- Timing & Safety Parameters ---
const float obstacleDistanceCm = 35.0; 
const int servoSettleTimeMs = 500;
const int turnDurationMs = 550;        
const int reverseDurationMs = 800;     

// --- Stuck Detection Tracking State ---
float lastDistance = -1.0;
int cornerStuckCount = 0;
const int maxCornerStuckCount = 5;     // 5 consecutive trapped turns

// Time-based tracking for >35cm low-obstacle stuck state
float motionStuckStartDistance = -1.0;
unsigned long motionStuckStartTime = 0;
bool isMotionTimerActive = false;

const unsigned long motionStuckTimeoutMs = 10000; // 10 seconds safeguard
const float minimumProgressCm = 5.0;              // Robot must cover at least 5cm to prove motion
const float distanceTolerance = 2.0;              // Margin of error in cm for corner checks

Servo scanServo;
bool isPaused = false;
String serialCommandBuffer;

// --- Enums ---
enum class ScanDirection { Right, Center, Left, Unknown };
enum class RobotAction { Stop, Forward, TurnRight, TurnLeft, ReverseAndRecover };
enum class TurnMode { FromStop, WhileMoving };

// --- Layer 1: Perception Layer ---

bool isValidDistance(float distance) {
    return distance >= 0.0;
}

void handleSerialCommand(const String& command) {
    if (command == "PAUSE") {
        isPaused = true;
        stopMotors();
        Serial.println("REMOTE COMMAND: PAUSE");
    } else if (command == "RESUME") {
        isPaused = false;
        resetStuckTrackers();
        Serial.println("REMOTE COMMAND: RESUME");
    }
}

void pollSerialCommands() {
    while (Serial.available() > 0) {
        char c = (char)Serial.read();

        if (c == '\r' || c == '\n') {
            continue;
        }

        if (c == '#') {
            if (serialCommandBuffer.length() > 0) {
                handleSerialCommand(serialCommandBuffer);
                serialCommandBuffer = "";
            }
            continue;
        }

        serialCommandBuffer += c;
        if (serialCommandBuffer.length() > 32) {
            serialCommandBuffer = "";
        }
    }
}

void cooperativeDelay(unsigned long durationMs) {
    unsigned long startMs = millis();
    while (millis() - startMs < durationMs) {
        pollSerialCommands();
        if (isPaused) {
            stopMotors();
            return;
        }
        delay(5);
    }
}

float measureDistanceCm() {
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);

    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);

    digitalWrite(trigPin, LOW);

    long duration = pulseIn(echoPin, HIGH, 30000);

    // Timeout (duration == 0) means open space (> 400cm max sensor range)
    if (duration == 0) {
        return -1.0;
    }

    return duration * 0.0343 / 2.0;
}

float measureDirection(ScanDirection direction) {
    int angle = (direction == ScanDirection::Right) ? servoRightAngle :
                (direction == ScanDirection::Left)  ? servoLeftAngle : servoCenterAngle;

    scanServo.write(angle);
    cooperativeDelay(servoSettleTimeMs);

    if (isPaused) {
        return -1.0;
    }

    return measureDistanceCm();
}

// --- Layer 2: Specialized Stuck Decision Functions ---

/**
 * Checks if an obstacle is closer than the threshold.
 * Note: -1.0 means open space (no echo), so it is NOT an obstacle!
 */
bool isObstacleAhead(float distance) {
    if (!isValidDistance(distance)) {
        return false; // -1.0 means infinite clear space!
    }
    return distance < obstacleDistanceCm;
}

/**
 * Checks if the robot is stuck facing an obstacle (< 35cm) despite turning.
 */
bool isStuckUnder35cm(float currentDistance) {
    // Reset open-space timer since we are now in close obstacle range
    motionStuckStartTime = 0;
    motionStuckStartDistance = -1.0;
    isMotionTimerActive = false;

    if (isValidDistance(currentDistance) && isValidDistance(lastDistance)) {
        if (abs(currentDistance - lastDistance) <= distanceTolerance) {
            cornerStuckCount++;
        } else {
            cornerStuckCount = 1;
        }
    } else {
        cornerStuckCount++;
    }

    lastDistance = currentDistance;

    Serial.print(" [CORNER STUCK: ");
    Serial.print(cornerStuckCount);
    Serial.print("/");
    Serial.print(maxCornerStuckCount);
    Serial.println("]");

    return cornerStuckCount >= maxCornerStuckCount;
}

/**
 * Checks if the robot is stuck on a low barrier (> 35cm) continuously for 10 seconds.
 */
bool isStuckOver35cm(float currentDistance) {
    // Reset corner count since path is open
    cornerStuckCount = 0;

    // 1. Start timer if not active
    if (!isMotionTimerActive) {
        motionStuckStartTime = millis();
        motionStuckStartDistance = currentDistance;
        isMotionTimerActive = true;
    } 
    // 2. Evaluate movement against anchor reading
    else {
        // If distance goes from valid to -1.0 (or vice versa), the robot made progress into open space!
        bool progressMade = false;

        if (isValidDistance(currentDistance) != isValidDistance(motionStuckStartDistance)) {
            progressMade = true;
        } else if (isValidDistance(currentDistance)) {
            float displacement = abs(currentDistance - motionStuckStartDistance);
            if (displacement >= minimumProgressCm) {
                progressMade = true;
            }
        }

        if (progressMade) {
            // Robot moved significantly — re-anchor baseline and reset timer
            motionStuckStartTime = millis();
            motionStuckStartDistance = currentDistance;
        }
    }

    // 3. Evaluate timer
    if (isMotionTimerActive) {
        unsigned long elapsed = millis() - motionStuckStartTime;

        Serial.print(" [MOTION STUCK TIMER: ");
        Serial.print(elapsed / 1000);
        Serial.print("s/10s]");

        if (elapsed >= motionStuckTimeoutMs) {
            return true;
        }
    }

    Serial.println();
    return false;
}

/**
 * Chooses turn direction. Converts -1.0 (out of range) to 999.0cm so 
 * open paths are always preferred over obstacle paths.
 */
RobotAction chooseAvoidanceAction(float rightDistance, float leftDistance) {
    float effectiveRight = isValidDistance(rightDistance) ? rightDistance : 999.0;
    float effectiveLeft  = isValidDistance(leftDistance)  ? leftDistance  : 999.0;

    // Default to turning right if both directions are equally clear
    return (effectiveRight >= effectiveLeft) ? RobotAction::TurnRight : RobotAction::TurnLeft;
}

// --- Layer 3: Action Layer ---

int validSpeed(int speed) {
    return constrain(speed, 0, 255);
}

void stopMotors() {
    analogWrite(leftSpeedPin, 0);
    analogWrite(rightSpeedPin, 0);
    digitalWrite(leftDirectionPin, LOW);
    digitalWrite(rightDirectionPin, LOW);
}

void moveForward() {
    digitalWrite(leftDirectionPin, LOW);
    digitalWrite(rightDirectionPin, LOW);
    analogWrite(leftSpeedPin, validSpeed(forwardLeftPwm));
    analogWrite(rightSpeedPin, validSpeed(forwardRightPwm));
}

void moveBackward() {
    digitalWrite(leftDirectionPin, HIGH);
    digitalWrite(rightDirectionPin, HIGH);
    analogWrite(leftSpeedPin, validSpeed(reverseLeftPwm));
    analogWrite(rightSpeedPin, validSpeed(reverseRightPwm));
}

void turnLeft(TurnMode mode) {
    int effectiveLeft = (mode == TurnMode::FromStop) ? turnFromStopLeftPwm : turnWhileMovingLeftPwm;
    int effectiveRight = (mode == TurnMode::FromStop) ? turnFromStopRightPwm : turnWhileMovingRightPwm;

    digitalWrite(leftDirectionPin, LOW);
    digitalWrite(rightDirectionPin, LOW);
    analogWrite(leftSpeedPin, validSpeed(effectiveLeft));
    analogWrite(rightSpeedPin, validSpeed(effectiveRight));
}

void turnRight(TurnMode mode) {
    int effectiveLeft = (mode == TurnMode::FromStop) ? turnFromStopRightPwm : turnWhileMovingRightPwm;
    int effectiveRight = (mode == TurnMode::FromStop) ? turnFromStopLeftPwm : turnWhileMovingLeftPwm;

    digitalWrite(leftDirectionPin, LOW);
    digitalWrite(rightDirectionPin, LOW);
    analogWrite(leftSpeedPin, validSpeed(effectiveLeft));
    analogWrite(rightSpeedPin, validSpeed(effectiveRight));
}

void resetStuckTrackers() {
    cornerStuckCount = 0;
    motionStuckStartTime = 0;
    motionStuckStartDistance = -1.0;
    isMotionTimerActive = false;
    lastDistance = -1.0;
}

void executeRecoverySequence() {
    Serial.println("\n*** EXECUTING BACKWARD RECOVERY ***");
    
    stopMotors();
    cooperativeDelay(200);
    if (isPaused) return;

    moveBackward();
    cooperativeDelay(reverseDurationMs);
    if (isPaused) return;
    stopMotors();
    cooperativeDelay(200);
    if (isPaused) return;

    float rightDist = measureDirection(ScanDirection::Right);
    float leftDist  = measureDirection(ScanDirection::Left);
    if (isPaused) return;

    scanServo.write(servoCenterAngle);
    cooperativeDelay(servoSettleTimeMs);
    if (isPaused) return;

    RobotAction action = chooseAvoidanceAction(rightDist, leftDist);

    if (action == RobotAction::TurnRight) {
        turnRight(TurnMode::FromStop);
        cooperativeDelay(turnDurationMs * 1.5);
    } else if (action == RobotAction::TurnLeft) {
        turnLeft(TurnMode::FromStop);
        cooperativeDelay(turnDurationMs * 1.5);
    }
    
    stopMotors();
    resetStuckTrackers();
    cooperativeDelay(200);
}

// --- Setup ---

void setup() {
    Serial.begin(9600);

    pinMode(leftDirectionPin, OUTPUT);
    pinMode(leftSpeedPin, OUTPUT);
    pinMode(rightDirectionPin, OUTPUT);
    pinMode(rightSpeedPin, OUTPUT);

    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);

    scanServo.attach(servoPin);
    scanServo.write(servoCenterAngle);
    cooperativeDelay(servoSettleTimeMs);

    stopMotors();
}

// --- Main Control Loop ---

void loop() {
    pollSerialCommands();

    if (isPaused) {
        stopMotors();
        delay(20);
        return;
    }

    float currentDistance = measureDistanceCm();

    Serial.print("FRONT: ");
    if (!isValidDistance(currentDistance)) {
        Serial.print("CLEAR (>400cm / NO ECHO)");
    } else {
        Serial.print(currentDistance);
        Serial.print(" cm");
    }

    if (isObstacleAhead(currentDistance)) {
        
        // 1. Check stuck state for < 35cm
        if (isStuckUnder35cm(currentDistance)) {
            executeRecoverySequence();
        } else {
            // Standard scan & turn sequence
            stopMotors();
            cooperativeDelay(200);
            if (isPaused) return;

            float rightDist = measureDirection(ScanDirection::Right);
            float leftDist  = measureDirection(ScanDirection::Left);
            if (isPaused) return;

            scanServo.write(servoCenterAngle);
            cooperativeDelay(servoSettleTimeMs);
            if (isPaused) return;

            RobotAction action = chooseAvoidanceAction(rightDist, leftDist);

            if (action == RobotAction::TurnRight) {
                turnRight(TurnMode::FromStop);
                cooperativeDelay(turnDurationMs);
            } else if (action == RobotAction::TurnLeft) {
                turnLeft(TurnMode::FromStop);
                cooperativeDelay(turnDurationMs);
            }
            stopMotors();
            cooperativeDelay(200);
        }

    } else {

        // 2. Check stuck state for > 35cm (Triggers ONLY if stuck continuously for 10 seconds)
        if (isStuckOver35cm(currentDistance)) {
            executeRecoverySequence();
        } else {
            moveForward();
        }

    }

    cooperativeDelay(50);
}

const int leftDirectionPin = 4;
const int leftSpeedPin = 6;

const int rightDirectionPin = 2;
const int rightSpeedPin = 5;

enum class Movement {
    Stop,
    Forward,
    Backward,
    Left,
    Right
};

enum class TurnMode {
    FromStop,
    WhileMoving
};

const int forwardLeftPwm = 120;
const int forwardRightPwm = 165;

const int backwardLeftPwm = 120;
const int backwardRightPwm = 110;

const int turnFromStopLeftPwm = 90;
const int turnFromStopRightPwm = 170;

const int turnWhileMovingLeftPwm = 120;
const int turnWhileMovingRightPwm = 150;

void setup() {
    Serial.begin(9600);

    pinMode(leftDirectionPin, OUTPUT);
    pinMode(leftSpeedPin, OUTPUT);

    pinMode(rightDirectionPin, OUTPUT);
    pinMode(rightSpeedPin, OUTPUT);

    stopCar();
}

int validSpeed(int speed) {
    if (speed < 0) return 0;
    if (speed > 255) return 255;
    return speed;
}

void stopCar() {
    Serial.println("Stop Car.");

    analogWrite(leftSpeedPin, 0);
    analogWrite(rightSpeedPin, 0);

    digitalWrite(leftDirectionPin, LOW);
    digitalWrite(rightDirectionPin, LOW);
}

void moveForward(int leftSpeed, int rightSpeed) {
    leftSpeed = validSpeed(leftSpeed);
    rightSpeed = validSpeed(rightSpeed);

    Serial.print("Forward - Left PWM: ");
    Serial.print(leftSpeed);
    Serial.print(", Right PWM: ");
    Serial.println(rightSpeed);

    digitalWrite(leftDirectionPin, LOW);
    digitalWrite(rightDirectionPin, LOW);

    analogWrite(leftSpeedPin, leftSpeed);
    analogWrite(rightSpeedPin, rightSpeed);
}

void moveBackward(int leftSpeed, int rightSpeed) {
    leftSpeed = validSpeed(leftSpeed);
    rightSpeed = validSpeed(rightSpeed);

    Serial.print("Backward - Left PWM: ");
    Serial.print(leftSpeed);
    Serial.print(", Right PWM: ");
    Serial.println(rightSpeed);

    digitalWrite(leftDirectionPin, HIGH);
    digitalWrite(rightDirectionPin, HIGH);

    analogWrite(leftSpeedPin, leftSpeed);
    analogWrite(rightSpeedPin, rightSpeed);
}

void turnLeft(int leftSpeed, int rightSpeed, TurnMode mode) {
    leftSpeed = validSpeed(leftSpeed);
    rightSpeed = validSpeed(rightSpeed);

    int effectiveLeft = leftSpeed;
    int effectiveRight = rightSpeed;

    if (mode == TurnMode::FromStop) {
        effectiveLeft = turnFromStopLeftPwm;
        effectiveRight = turnFromStopRightPwm;
        Serial.print("Turn left from stop - Left PWM: ");
        Serial.print(effectiveLeft);
        Serial.print(", Right PWM: ");
        Serial.println(effectiveRight);
    } else {
        effectiveLeft = turnWhileMovingLeftPwm;
        effectiveRight = turnWhileMovingRightPwm;
        Serial.print("Turn left while moving - Left PWM: ");
        Serial.print(effectiveLeft);
        Serial.print(", Right PWM: ");
        Serial.println(effectiveRight);
    }

    digitalWrite(leftDirectionPin, LOW);
    digitalWrite(rightDirectionPin, LOW);

    analogWrite(leftSpeedPin, effectiveLeft);
    analogWrite(rightSpeedPin, effectiveRight);
}

void turnRight(int leftSpeed, int rightSpeed, TurnMode mode) {
    leftSpeed = validSpeed(leftSpeed);
    rightSpeed = validSpeed(rightSpeed);

    int effectiveLeft = leftSpeed;
    int effectiveRight = rightSpeed;

    if (mode == TurnMode::FromStop) {
        effectiveLeft = turnFromStopRightPwm;
        effectiveRight = turnFromStopLeftPwm;
        Serial.print("Turn right from stop - Left PWM: ");
        Serial.print(effectiveLeft);
        Serial.print(", Right PWM: ");
        Serial.println(effectiveRight);
    } else {
        effectiveLeft = turnWhileMovingRightPwm;
        effectiveRight = turnWhileMovingLeftPwm;
        Serial.print("Turn right while moving - Left PWM: ");
        Serial.print(effectiveLeft);
        Serial.print(", Right PWM: ");
        Serial.println(effectiveRight);
    }

    digitalWrite(leftDirectionPin, LOW);
    digitalWrite(rightDirectionPin, LOW);

    analogWrite(leftSpeedPin, effectiveLeft);
    analogWrite(rightSpeedPin, effectiveRight);
}

String movementToString(Movement movement) {
    switch (movement) {
        case Movement::Stop:     return "Stop";
        case Movement::Forward:  return "Forward";
        case Movement::Backward: return "Backward";
        case Movement::Left:     return "Left";
        case Movement::Right:    return "Right";
        default:                 return "Unknown";
    }
}

void executeMovement(Movement movement, int leftSpeed, int rightSpeed, TurnMode mode) {
    Serial.print("Movement: ");
    Serial.println(movementToString(movement));

    switch (movement) {
        case Movement::Stop:
            stopCar();
            break;
        case Movement::Forward:
            moveForward(leftSpeed, rightSpeed);
            break;
        case Movement::Backward:
            moveBackward(leftSpeed, rightSpeed);
            break;
        case Movement::Left:
            turnLeft(leftSpeed, rightSpeed, mode);
            break;
        case Movement::Right:
            turnRight(leftSpeed, rightSpeed, mode);
            break;
    }
}

void loop() {
    executeMovement(Movement::Stop, 0, 0, TurnMode::FromStop);
    delay(1000);

    executeMovement(Movement::Forward, forwardLeftPwm, forwardRightPwm, TurnMode::FromStop);
    delay(3000);

    executeMovement(Movement::Stop, 0, 0, TurnMode::FromStop);
    delay(1000);

    executeMovement(Movement::Backward, backwardLeftPwm, backwardRightPwm, TurnMode::FromStop);
    delay(3000);

    executeMovement(Movement::Stop, 0, 0, TurnMode::FromStop);
    delay(1000);

    executeMovement(Movement::Left, turnFromStopLeftPwm, turnFromStopRightPwm, TurnMode::FromStop);
    delay(1000);

    executeMovement(Movement::Stop, 0, 0, TurnMode::FromStop);
    delay(1000);

    executeMovement(Movement::Right, turnFromStopRightPwm, turnFromStopLeftPwm, TurnMode::FromStop);
    delay(1000);

    executeMovement(Movement::Stop, 0, 0, TurnMode::FromStop);
    delay(1000);

    executeMovement(Movement::Forward, forwardLeftPwm, forwardRightPwm, TurnMode::FromStop);
    delay(2000);

    executeMovement(Movement::Left, turnWhileMovingLeftPwm, turnWhileMovingRightPwm, TurnMode::WhileMoving);
    delay(1000);

    executeMovement(Movement::Forward, forwardLeftPwm, forwardRightPwm, TurnMode::FromStop);
    delay(2000);

    executeMovement(Movement::Right, turnWhileMovingRightPwm, turnWhileMovingLeftPwm, TurnMode::WhileMoving);
    delay(1000);

    executeMovement(Movement::Stop, 0, 0, TurnMode::FromStop);
    delay(3000);
}

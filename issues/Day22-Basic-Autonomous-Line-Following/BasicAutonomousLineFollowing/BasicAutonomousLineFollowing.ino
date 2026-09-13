const int trackingLeftPin = 11;
const int trackingRightPin = 10;

const int leftDirectionPin = 4;
const int leftSpeedPin = 6;

const int rightDirectionPin = 2;
const int rightSpeedPin = 5;

// Normal forward calibration.
const int forwardLeftPwm = 80;
const int forwardRightPwm = 90;

// Startup test: both motors receive the same PWM briefly.
const int startupEqualPwm = 80;
const unsigned long startupEqualDurationMs = 150;

const int turnFromStopLeftPwm = 120;
const int turnFromStopRightPwm = 160;

const int turnWhileMovingLeftPwm = 120;
const int turnWhileMovingRightPwm = 160;

const int lineDetectedValue = HIGH;

// Keep true while measuring centered-only movement.
// Change to false when starting real line following.
const bool centeredOnlyStopTest = true;

enum class LineSensorState {
    BothBackground,
    LeftOnLine,
    RightOnLine,
    BothOnLine
};

enum class LineAction {
    Forward,
    CorrectLeft,
    CorrectRight,
    Stop
};

enum class TurnMode {
    FromStop,
    WhileMoving
};

bool stoppedAfterSeeingLine = false;

bool forwardStartupPending = true;
unsigned long forwardStartupStartTime = 0;

bool detectsLine(int pin) {
    return digitalRead(pin) == lineDetectedValue;
}

LineSensorState readLineSensorState() {
    bool leftOnLine = detectsLine(trackingLeftPin);
    bool rightOnLine = detectsLine(trackingRightPin);

    if (leftOnLine && rightOnLine) {
        return LineSensorState::BothOnLine;
    }

    if (leftOnLine) {
        return LineSensorState::LeftOnLine;
    }

    if (rightOnLine) {
        return LineSensorState::RightOnLine;
    }

    return LineSensorState::BothBackground;
}

const char* lineStateToString(LineSensorState state) {
    switch (state) {
        case LineSensorState::BothBackground:
            return "BOTH BACKGROUND";

        case LineSensorState::LeftOnLine:
            return "LEFT ON LINE";

        case LineSensorState::RightOnLine:
            return "RIGHT ON LINE";

        case LineSensorState::BothOnLine:
            return "BOTH ON LINE";
    }

    return "UNKNOWN";
}

LineAction chooseLineAction(LineSensorState state) {
    switch (state) {
        case LineSensorState::BothBackground:
            return LineAction::Forward;

        case LineSensorState::LeftOnLine:
            return LineAction::CorrectLeft;

        case LineSensorState::RightOnLine:
            return LineAction::CorrectRight;

        case LineSensorState::BothOnLine:
            return LineAction::Forward;
    }

    return LineAction::Stop;
}

int validSpeed(int speed) {
    return constrain(speed, 0, 255);
}

void stopMotors() {
    analogWrite(leftSpeedPin, 0);
    analogWrite(rightSpeedPin, 0);

    digitalWrite(leftDirectionPin, LOW);
    digitalWrite(rightDirectionPin, LOW);

    // The next forward command will use the startup phase again.
    forwardStartupPending = true;
}

void moveForward() {
    if (forwardStartupPending) {
        forwardStartupStartTime = millis();
        forwardStartupPending = false;
    }

    int leftPwm = forwardLeftPwm;
    int rightPwm = forwardRightPwm;

    bool inStartupPhase =
        millis() - forwardStartupStartTime <
        startupEqualDurationMs;

    if (inStartupPhase) {
        leftPwm = startupEqualPwm;
        rightPwm = startupEqualPwm;
    }

    digitalWrite(leftDirectionPin, LOW);
    digitalWrite(rightDirectionPin, LOW);

    analogWrite(leftSpeedPin, validSpeed(leftPwm));
    analogWrite(rightSpeedPin, validSpeed(rightPwm));
}

void turnLeft(TurnMode mode) {
    int effectiveLeft =
        (mode == TurnMode::FromStop)
            ? turnFromStopLeftPwm
            : turnWhileMovingLeftPwm;

    int effectiveRight =
        (mode == TurnMode::FromStop)
            ? turnFromStopRightPwm
            : turnWhileMovingRightPwm;

    digitalWrite(leftDirectionPin, LOW);
    digitalWrite(rightDirectionPin, LOW);

    analogWrite(leftSpeedPin, validSpeed(effectiveLeft));
    analogWrite(rightSpeedPin, validSpeed(effectiveRight));
}

void turnRight(TurnMode mode) {
    int effectiveLeft =
        (mode == TurnMode::FromStop)
            ? turnFromStopRightPwm
            : turnWhileMovingRightPwm;

    int effectiveRight =
        (mode == TurnMode::FromStop)
            ? turnFromStopLeftPwm
            : turnWhileMovingLeftPwm;

    digitalWrite(leftDirectionPin, LOW);
    digitalWrite(rightDirectionPin, LOW);

    analogWrite(leftSpeedPin, validSpeed(effectiveLeft));
    analogWrite(rightSpeedPin, validSpeed(effectiveRight));
}

void executeLineAction(LineAction action) {
    switch (action) {
        case LineAction::Forward:
            moveForward();
            break;

        case LineAction::CorrectLeft:
            turnLeft(TurnMode::WhileMoving);
            break;

        case LineAction::CorrectRight:
            turnRight(TurnMode::WhileMoving);
            break;

        case LineAction::Stop:
            stopMotors();
            break;
    }
}

void setup() {
    pinMode(trackingLeftPin, INPUT);
    pinMode(trackingRightPin, INPUT);

    pinMode(leftDirectionPin, OUTPUT);
    pinMode(leftSpeedPin, OUTPUT);

    pinMode(rightDirectionPin, OUTPUT);
    pinMode(rightSpeedPin, OUTPUT);

    Serial.begin(9600);

    stopMotors();
}

void loop() {
    LineSensorState state = readLineSensorState();

    if (centeredOnlyStopTest) {
        bool eitherSensorSeesLine =
            state == LineSensorState::LeftOnLine ||
            state == LineSensorState::RightOnLine ||
            state == LineSensorState::BothOnLine;

        if (stoppedAfterSeeingLine) {
            stopMotors();
            return;
        }

        if (eitherSensorSeesLine) {
            stopMotors();

            Serial.print("Stopped: ");
            Serial.println(lineStateToString(state));

            stoppedAfterSeeingLine = true;
            return;
        }

        moveForward();
        return;
    }

    LineAction action = chooseLineAction(state);
    executeLineAction(action);
}
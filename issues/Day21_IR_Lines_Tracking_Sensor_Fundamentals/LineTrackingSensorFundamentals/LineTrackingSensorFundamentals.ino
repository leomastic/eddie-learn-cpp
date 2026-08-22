const int trackingLeftPin = 11;
const int trackingRightPin = 10;
const int lineDetectedValue = HIGH;
const int backgroundValue = LOW;

enum class LineSensorState {
    BothBackground,
    LeftOnLine,
    RightOnLine,
    BothOnLine
};

LineSensorState readLineSensorState() {
    bool leftOnLine =
        detectsLine(trackingLeftPin);

    bool rightOnLine =
        detectsLine(trackingRightPin);

    if(leftOnLine && rightOnLine) {
        return LineSensorState::BothOnLine;
    }

    if(!leftOnLine && rightOnLine) {
        return LineSensorState::RightOnLine;
    }

    if(leftOnLine && !rightOnLine) {
        return LineSensorState::LeftOnLine;
    }

    if(!leftOnLine && !rightOnLine) {
        return LineSensorState::BothBackground;
    }
}

bool detectsLine(int pin) {
    return digitalRead(pin) ==
           lineDetectedValue;
}

const char* lineStateToString(
    LineSensorState state
) {
    if(state == LineSensorState::BothBackground) {
        return "BOTH BACKGROUND";
    }

    if(state == LineSensorState::BothOnLine) {
        return "BOTH ON LINE";
    }

    if(state == LineSensorState::LeftOnLine) {
        return "LEFT ON LINE";
    }

    if(state == LineSensorState::RightOnLine) {
        return "RIGHT ON LINE";
    }
}

void setup() {
    Serial.begin(9600);

    pinMode(trackingLeftPin, INPUT);
    pinMode(trackingRightPin, INPUT);
}

void loop() {
    Serial.println("-----------------");

    LineSensorState state =
        readLineSensorState();

    Serial.print("LEFT raw: ");
    Serial.println(detectsLine(trackingLeftPin));

    Serial.print("RIGHT raw: ");
    Serial.println(detectsLine(trackingRightPin));

    Serial.print("STATE: ");
    Serial.println(
        lineStateToString(state)
    );

    delay(200);
}
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

bool detectsLine(int pin) {
    return digitalRead(pin) ==
           lineDetectedValue;
}

const char* lineStateToString(
    LineSensorState state
) {
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

void setup() {
    Serial.begin(9600);

    pinMode(trackingLeftPin, INPUT);
    pinMode(trackingRightPin, INPUT);
}

void loop() {
    Serial.println("-----------------");

    int leftRaw =
    digitalRead(trackingLeftPin);

    int rightRaw =
        digitalRead(trackingRightPin);

    Serial.print("LEFT raw: ");
    Serial.println(leftRaw);

    Serial.print("RIGHT raw: ");
    Serial.println(rightRaw);

    Serial.print("LEFT meaning: ");
    Serial.println(
        detectsLine(trackingLeftPin)
            ? "LINE"
            : "BACKGROUND"
    );

    Serial.print("RIGHT meaning: ");
    Serial.println(
        detectsLine(trackingRightPin)
            ? "LINE"
            : "BACKGROUND"
    );

    LineSensorState state =
        readLineSensorState();

    Serial.print("STATE: ");
    Serial.println(
        lineStateToString(state)
    );

    delay(200);
}
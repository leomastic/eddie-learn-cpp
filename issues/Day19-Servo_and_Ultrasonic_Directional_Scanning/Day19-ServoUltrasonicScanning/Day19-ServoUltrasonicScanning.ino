#include <Servo.h>

const int trigPin = 8;
const int echoPin = 7;
const int servoPin = 9;

const int servoRightAngle = 33;
const int servoCenterAngle = 93;
const int servoLeftAngle = 153;

const int servoSettleTimeMs = 750;

Servo scanServo;

enum class ScanDirection {
    Right,
    Center,
    Left,
    Unknown
};

int angleForDirection(ScanDirection direction) {
    switch (direction) {
        case ScanDirection::Right:
            return servoRightAngle;

        case ScanDirection::Center:
            return servoCenterAngle;

        case ScanDirection::Left:
            return servoLeftAngle;
    }

    return servoCenterAngle;
}

const char* directionToString(ScanDirection direction) {
    switch (direction) {
        case ScanDirection::Right:
            return "RIGHT";

        case ScanDirection::Center:
            return "CENTER";

        case ScanDirection::Left:
            return "LEFT";

        case ScanDirection::Unknown:
            return "UNKNOWN";
    }
    return "UNKNOWN";
}

bool isValidDistance(float distance) {
    return distance >= 0;
}

float measureDistanceCm() {
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);

    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);

    digitalWrite(trigPin, LOW);

    long duration = pulseIn(echoPin, HIGH, 30000);

    if (duration == 0) {
        return -1;
    }

    return duration * 0.0343 / 2.0;
}

float measureDirection(ScanDirection direction) {
    int angle = angleForDirection(direction);

    scanServo.write(angle);
    delay(servoSettleTimeMs);

    float distance = measureDistanceCm();

    Serial.print(directionToString(direction));
    Serial.print(": ");

    if (!isValidDistance(distance)) {
        Serial.println("NO ECHO");
    } else {
        Serial.print(distance);
        Serial.println(" cm");
    }

    return distance;
}

// Fixed logic: Filters out invalid (-1) measurements & handles ties safely
ScanDirection findMostOpenDirection(
    float rightDistance,
    float centerDistance,
    float leftDistance
) {
    float maxDist = -1.0f;
    ScanDirection bestDir = ScanDirection::Unknown;

    if (isValidDistance(rightDistance) && rightDistance > maxDist) {
        maxDist = rightDistance;
        bestDir = ScanDirection::Right;
    }

    if (isValidDistance(centerDistance) && centerDistance > maxDist) {
        maxDist = centerDistance;
        bestDir = ScanDirection::Center;
    }

    if (isValidDistance(leftDistance) && leftDistance > maxDist) {
        maxDist = leftDistance;
        bestDir = ScanDirection::Left;
    }

    return bestDir;
}

void setup() {
    Serial.begin(9600);

    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);

    scanServo.attach(servoPin);

    scanServo.write(servoCenterAngle);
    delay(servoSettleTimeMs);
}

void loop() {
    Serial.println("--- SCAN ---");

    // Correct physical sequence: RIGHT -> CENTER -> LEFT
    float rightDistance = measureDirection(ScanDirection::Right);
    float centerDistance = measureDirection(ScanDirection::Center);
    float leftDistance = measureDirection(ScanDirection::Left);

    // Always return servo to center after scan completes
    scanServo.write(servoCenterAngle);
    delay(servoSettleTimeMs);

    ScanDirection mostOpen = findMostOpenDirection(rightDistance, centerDistance, leftDistance);
    
    Serial.println("--------------------");
    Serial.print("MOST OPEN: ");
    Serial.println(directionToString(mostOpen));
    Serial.println("------------\n");

    delay(2000); // Pause before next scan loop
}
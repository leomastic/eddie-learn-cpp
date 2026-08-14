#include <Servo.h>

const int servoPin = 9;

const int servoRightAngle = 33;
const int servoCenterAngle = 93;
const int servoLeftAngle = 153;

const int servoLeftestLimitCommandedAngle = 160;
const int servoRightestLimitCommandedAngle = 21;

Servo scanServo;

//void loop() {
//    scanServo.write(30); // Physical direction: 27°
//    delay(1500);

//    scanServo.write(90); // Physical direction: 87°
//    delay(1500);

//    scanServo.write(150); // Physical direction: 147°
//    delay(1500);
//}

int validServoAngle(int angle) {
    if (angle > servoLeftestLimitCommandedAngle) {
        return servoLeftestLimitCommandedAngle;
    }

    if (angle < servoRightestLimitCommandedAngle) {
        return servoRightestLimitCommandedAngle;
    }

    return angle;
}

void moveServoTo(int angle) {
    angle = validServoAngle(angle);

    scanServo.write(angle);

    Serial.print("Servo target: ");
    Serial.print(angle);
    Serial.println(" degrees");
}

void setup() {
    Serial.begin(9600);

    scanServo.attach(servoPin);

    moveServoTo(servoCenterAngle);
    delay(1000);
}

void loop() {
    moveServoTo(servoRightAngle);
    delay(1500);

    //moveServoTo(73);
    //delay(3000);

    //moveServoTo(83);
    //delay(3000);

    moveServoTo(servoCenterAngle);
    delay(3000);

    //moveServoTo(103);
    //delay(3000);

    //moveServoTo(113);
    //delay(3000);

    moveServoTo(servoLeftAngle);
    delay(1500);

    for (int angle = servoRightAngle; // turn servo to the left
     angle <= servoLeftAngle;
     angle += 5) {

        moveServoTo(angle);
        delay(100);
    }

    for (int angle = servoLeftAngle; // turn servo to the right
     angle >= servoRightAngle;
     angle -= 5) {

        moveServoTo(angle);
        delay(100);
    }
}

// Safe limit: Physically: 22° right; 160° left.
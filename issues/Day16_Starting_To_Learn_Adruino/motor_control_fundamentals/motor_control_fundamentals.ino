const int leftDirectionPin = 4;
const int leftSpeedPin = 6;

const int rightDirectionPin = 2;
const int rightSpeedPin = 5;

const int batteryPin = A0;          // Connected to the center of the divider
const float voltageMultiplier = 2.0; // Restores the halved voltage back to true value

enum class Movement {
    Stop,
    Forward,
    Backward,
    Left,
    Right
};

void setup() {
    Serial.begin(9600); // Open the Arduino IDE Serial Monitor at 9600 baud

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

    Serial.print("Forward, average speed = ");
    Serial.println((leftSpeed + rightSpeed) / 2);

    digitalWrite(leftDirectionPin, LOW);
    digitalWrite(rightDirectionPin, LOW);

    analogWrite(leftSpeedPin, leftSpeed);
    analogWrite(rightSpeedPin, rightSpeed);
}

void moveBackward(int leftSpeed, int rightSpeed) {
    leftSpeed = validSpeed(leftSpeed);
    rightSpeed = validSpeed(rightSpeed);

    Serial.print("Backward, average speed = ");
    Serial.println((leftSpeed + rightSpeed) / 2);

    digitalWrite(leftDirectionPin, HIGH);
    digitalWrite(rightDirectionPin, HIGH);

    analogWrite(leftSpeedPin, leftSpeed);
    analogWrite(rightSpeedPin, rightSpeed);
}

void turnLeft(int leftSpeed, int rightSpeed, bool isStopped) {
    leftSpeed = validSpeed(leftSpeed);
    rightSpeed = validSpeed(rightSpeed);

    Serial.println("Turn left...");

    digitalWrite(leftDirectionPin, LOW);
    digitalWrite(rightDirectionPin, LOW);

    analogWrite(leftSpeedPin, validSpeed(leftSpeed / (isStopped? 1.5 : 2)));
    analogWrite(rightSpeedPin, rightSpeed);
}

void turnRight(int leftSpeed, int rightSpeed, bool isStopped) {
    leftSpeed = validSpeed(leftSpeed);
    rightSpeed = validSpeed(rightSpeed);

    Serial.println("Turn right...");

    digitalWrite(leftDirectionPin, LOW);
    digitalWrite(rightDirectionPin, LOW);

    analogWrite(leftSpeedPin, leftSpeed);
    analogWrite(rightSpeedPin, validSpeed(rightSpeed / (isStopped? 1.5 : 2)));
}

String movementToString(Movement movement) {
    switch(movement) {
        case Movement::Stop:     return "Stop";
        case Movement::Forward:  return "Forward";
        case Movement::Backward: return "Backward";
        case Movement::Left:     return "Left";
        case Movement::Right:    return "Right";
        default:                 return "Unknown";
    }
}

void executeMovement(Movement movement, int leftSpeed, int rightSpeed, bool isStopped) {
    switch (movement) {
        case Movement::Forward:  moveForward(leftSpeed, rightSpeed); break;
        case Movement::Backward: moveBackward(leftSpeed, rightSpeed); break;
        case Movement::Left:     turnLeft(leftSpeed, rightSpeed, isStopped); break;
        case Movement::Right:    turnRight(leftSpeed, rightSpeed, isStopped); break;
        default:                 stopCar(); break;
    }
}

void loop() {
    // Read the raw ADC value (0 to 1023)
    int rawADC = analogRead(batteryPin);
  
    // Convert the raw number back into a real voltage based on the 5V Keyes Nano rail
    float pinVoltage = rawADC * (5.0 / 1023.0);
    float actualBatteryVoltage = pinVoltage * voltageMultiplier;

    // Print the true real-time charging voltage
    Serial.print("Battery Voltage: ");
    Serial.print(actualBatteryVoltage);
    Serial.println(" V");

    // Determine the charging phase
    if (actualBatteryVoltage >= 4.15) {
        Serial.println("Status: Final Saturation Phase (Almost Full)");
    } else if (actualBatteryVoltage > 3.0) {
        Serial.println("Status: Bulk Charging Phase");
    } else {
        Serial.println("Status: Deeply Discharged / Check Connections");
    }

    delay(2000); // Check every 2 seconds

    stopCar();
    delay(2000);

    moveForward(120, 165);
    delay(5000);

    stopCar();
    delay(5000);

    moveForward(200, 350);
    delay(5000);

    stopCar();
    delay(5000);

    turnLeft(120, 165, true);
    delay(1000);

    stopCar();
    delay(2000);

    moveBackward(120, 110);
    delay(5000);

    stopCar();
    delay(5000);

    turnLeft(120, 165, true);
    delay(1000);

    moveForward(50, 70);
    delay(5000);

    turnRight(120, 165, false);
    delay(1000);

    moveForward(120, 120);
    delay(2000);

    stopCar();
    delay(3000);
}
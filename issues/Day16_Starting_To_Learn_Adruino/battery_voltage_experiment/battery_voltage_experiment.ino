const int batteryPin = A0;
const float voltageMultiplier = 2.0;

void setup() {
    Serial.begin(9600);
}

void loop() {
    int rawADC = analogRead(batteryPin);
    float pinVoltage = rawADC * (5.0 / 1023.0);
    float actualBatteryVoltage = pinVoltage * voltageMultiplier;

    Serial.print("Battery Voltage: ");
    Serial.print(actualBatteryVoltage);
    Serial.println(" V");

    delay(2000);
}

const int trigPin = 8;
const int echoPin = 7;

void setup() {
    Serial.begin(9600);

    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);
}

float measureDistanceCm() {
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);

    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);

    digitalWrite(trigPin, LOW);

    long duration =                 
        pulseIn(echoPin, HIGH, 30000);  // "30000 is mean do not run forever, run for only 30000 microseconds = 30 miliseconds"

    if (duration == 0) {
        return -1;
    }

    return duration * 0.0343 / 2.0;
}

void loop() {
    float distance =
        measureDistanceCm();

    if (distance < 0) {
        Serial.println(
            "No valid echo"
        );
    } else {
        Serial.print("Distance: ");
        Serial.print(distance);
        Serial.println(" cm");
    }

    delay(100);
}
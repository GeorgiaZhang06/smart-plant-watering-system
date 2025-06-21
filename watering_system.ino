const int moisturePin = A0;   // Soil moisture sensor on A0
const int motorPin = 8;       // Transistor control pin used for motor switch

const int moistureThreshold = 600;  //Soil moisture threshold

unsigned long lastCheckTime = 0;
const unsigned long interval = 3600000;

void setup() {
  Serial.begin(9600);
  pinMode(motorPin, OUTPUT);
  digitalWrite(motorPin, LOW);  // Motor off to start
}

void waterPlant() {
  unsigned long currentTime = millis();

  digitalWrite(motorPin, HIGH); // Turn motor ON
  Serial.println("Soil is dry. Watering for 3 seconds.");
  delay(3000); // Run motor for 3 seconds
  digitalWrite(motorPin, LOW); // Turn motor back off
}

void loop() {
  unsigned long currentTime = millis();
  int moistureValue = analogRead(moisturePin);

  Serial.print("Soil Moisture: ");
  Serial.println(moistureValue);

  //Keep Arduino running in between soil moisture check times
  if (currentTime - lastCheckTime >= interval) {
  lastCheckTime = currentTime;

    if (moistureValue > moistureThreshold) {
      // Soil is dry
      waterPlant();
    } else {
      // Soil is moist
      digitalWrite(motorPin, LOW);    // Turn motor off
      Serial.println("Soil is moist. No watering needed.");
    }
  }
}

#include <Servo.h>
#include <SoftwareSerial.h>
#include <LiquidCrystal_I2C.h>
#define waterSensorPin A0
#define soilMoisturePin A1
#define waterSensorPower 7
LiquidCrystal_I2C lcd(0x27, 16, 2);

SoftwareSerial sim(10, 11);

String number = "+639686257330";
Servo myServoA;
Servo myServoB;

const int waterPumpPin = 12;//water pump
const int buttonPinA = 2;   // for servo A (drain)
const int buttonPinB = 3;  // for servo B (ricefield)
const int buttonPinC = 4;   // led button
const int buttonPinD = 8;   // water pump button
const int servoPinA = 9;    // drain
const int servoPinB = 6;    // ricefield
// const int ledPinA = 3;      // bridge lights
const int ledPinB = 5;      // house lights

int servoAAngle = 0; // drain
int servoBAngle = 0; // ricefield

int ledState = 0;

int buttonAState = LOW;
int buttonBState = LOW;
int buttonCState = LOW;
int buttonDState = LOW;

int waterPumpState = LOW;
int aWaterPumpState = LOW;

int waterLevelValue = 0;
int soilMoistureValue = 0;

unsigned long countdownSMS = 3000;
unsigned long countdownSoilMoisture = 3000;

void wait(int value) {
  delay(value);
  if (countdownSMS > 0) {
    countdownSMS -= value;
  }
  if (countdownSoilMoisture > 0) {
    countdownSoilMoisture -= value;
  }
}

void lcdWrite(String message1, String message2 = "") {
  lcd.clear();
  lcd.setCursor(1, 0);
  lcd.print(message1);
  lcd.setCursor(1, 1);
  lcd.print(message2);
}

void setup() {
  pinMode(waterSensorPower, OUTPUT);
  // pinMode(ledPinA, OUTPUT);
  pinMode(ledPinB, OUTPUT);
  digitalWrite(waterSensorPower, LOW);
  Serial.begin(9600);

  lcd.init();
  lcd.backlight();
  lcd.setCursor(1,0);
  lcd.print("RoboChill");
  lcd.setCursor(1,1);
  lcd.print("LET'S GO!!!");

  myServoA.attach(servoPinA);
  myServoB.attach(servoPinB);

  pinMode(buttonPinA, INPUT_PULLUP);
  pinMode(buttonPinB, INPUT_PULLUP);
  pinMode(buttonPinC, INPUT_PULLUP);
  pinMode(buttonPinD, INPUT_PULLUP);

  pinMode(waterPumpPin, OUTPUT);

  Serial.begin(9600);
}

void loop() {
  buttonAState = digitalRead(buttonPinA);
  buttonBState = digitalRead(buttonPinB);
  buttonCState = digitalRead(buttonPinC);
  buttonDState = digitalRead(buttonPinD);

  waterLevelValue = readWaterSensor();
  soilMoistureValue = readSoilMoistureSensor();

  // display current water level
  lcdWrite("Water Level", waterLevelValue + "");

  if (waterPumpState == HIGH) {
    if (aWaterPumpState == LOW) {
      aWaterPumpState = HIGH;
    } else {
      aWaterPumpState = LOW;
    }
    digitalWrite(waterPumpPin, aWaterPumpState);
    wait(500);
  }

  if (servoAAngle == 0) {
    myServoA.write(45);
    wait(300);
    myServoA.write(0);
  }

  if (waterLevelValue > 500 and countdownSMS <= 0) {
    // water level is high
    // send message
    lcdWrite("Sending SMS...");
    String message = "Warning!\n\nThe water level is rising!\nCurrent Water Level: ";
    message += waterLevelValue;
    // sendAlertSMS(message, number);
    Serial.println(message);

    countdownSMS = 90000;
  }

  if (soilMoistureValue > 600 and countdownSoilMoisture <= 0) {
    // soil is dry
    // need watering
    if (servoBAngle == 0) {
      servoBAngle = 90;
    }
    myServoB.write(servoBAngle);
    wait(150);
    servoBAngle = 0;
    myServoB.write(servoBAngle);
  }

  if (buttonAState == LOW) {
    // servo 1 for drain
    if (servoAAngle == 0) {
      servoAAngle = 90;
    } else {
      servoAAngle = 0;
    }
    myServoA.write(servoAAngle);
  }

  if (buttonBState == LOW) {
    // servo 2 ricefield
    if (servoBAngle == 0) {
      servoBAngle = 90;
    } else {
      servoBAngle = 0;
    }
    myServoB.write(servoBAngle);
  }

  if (buttonCState == LOW) {
    if (ledState == 1) {
      ledState = 0;
    } else {
      ledState = 1;
    }
    // digitalWrite(ledPinA, ledState);
    digitalWrite(ledPinB, ledState);
  }

  if (buttonDState == LOW) {
    // water pump
    if (waterPumpState == HIGH) {
      waterPumpState = LOW;
    } else {
      waterPumpState = HIGH;
    }
    digitalWrite(waterPumpPin, waterPumpState);
  }

  wait(150);
}

int readWaterSensor() {
  digitalWrite(waterSensorPower, HIGH);
  delay(10);
  waterLevelValue = analogRead(waterSensorPin);
  digitalWrite(waterSensorPower, LOW);
  return waterLevelValue;
}

int readSoilMoistureSensor() {
  soilMoistureValue = analogRead(soilMoisturePin);
  return soilMoistureValue;
}

void sendAlertSMS(String message, String phoneNumber) {

    sim.println("AT");  // Check if SIM800L is responding
    delay(100);
    if (sim.find("OK")) {
        Serial.println("SIM800L Ready");
    } else {
        Serial.println("SIM800L Not Responding");
        return;
    }
    sim.println("AT+CMGF=1");  // Set SMS to text mode
    delay(100);
    sim.print("AT+CMGS=\"");    // Start sending SMS
    sim.print(phoneNumber);     // Recipient phone number
    sim.println("\"");
    delay(100);
    sim.print(message);         // Message content
    sim.write(26);              // End SMS with Ctrl+Z (ASCII 26)
    delay(1000);
    Serial.println("SMS Sent Successfully!");
}

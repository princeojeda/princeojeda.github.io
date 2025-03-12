#include <Servo.h>
#include <SoftwareSerial.h>
#include <LiquidCrystal_I2C.h>
#define sensorPin A0
#define sensorPower 7

LiquidCrystal_I2C lcd(0x27, 16, 2);

SoftwareSerial sim(10, 11);

Servo myServo;

const int buttonPin = 2;
String number = "+639686257330";
int servoAngle = 0;

bool ledON = false;

int buttonState = LOW;
int val = 0;
int level = 0;

int waterPumpPin = 13;
int btnToWaterPumpPin = 8;
bool waterPumpState = false;
unsigned long countdown = 0;

int ledBridgePinA = 3;
int ledBridgePinB = 6;
int ledHousePin = 5;

int btnLedPin = 4;

void setup() {
  pinMode(sensorPower, OUTPUT);
  pinMode(waterPumpPin, OUTPUT);
  pinMode(ledBridgePinA, OUTPUT);
  pinMode(ledBridgePinB, OUTPUT);
  pinMode(ledHousePin, OUTPUT);
  digitalWrite(sensorPower, LOW);
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  lcd.setCursor(1,0);
  lcd.print("RoboChill");
  lcd.setCursor(1,1);
  lcd.print("LET'S GO!!!");
  myServo.attach(9);
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(btnToWaterPumpPin, INPUT_PULLUP);
  pinMode(btnLedPin, INPUT_PULLUP);
  Serial.begin(9600);
  sim.begin(9600);
}

void loop() {
  int level = readSensor();
  Serial.println(level);
  if (level > 500) {
    if (countdown <= 0) {
      countdown = 60000;
      String message = "Water level is now at " + String(level);
      // sendAlertSMS(message, number);
      Serial.println(message);
      Serial.println(number);
      Serial.println("Sending SMS!");
      Serial.println(countdown);
    }
  }
  if (btnToWaterPumpPin == LOW) {
    lcd.clear();
    lcd.setCursor(1, 0);
    if (waterPumpState == false) {
      digitalWrite(waterPumpPin, HIGH);
      waterPumpState = true;
    } else {
      String lcdMessage = "Draining the river";
      lcd.print(lcdMessage);
      digitalWrite(waterPumpPin, LOW);
      waterPumpState = false;

    }
  }
  if (btnLedPin == LOW) {

    if (ledON) {
      ledON = false;
      digitalWrite(ledBridgePinA, LOW);
      digitalWrite(ledBridgePinB, LOW);
      digitalWrite(ledHousePin, LOW);
    } else {
      ledON = true;
      digitalWrite(ledBridgePinA, HIGH);
      digitalWrite(ledBridgePinB, HIGH);
      digitalWrite(ledHousePin, HIGH);
    }

    delay(100);
    countdown -= 100;

  }
  if (buttonState == LOW) { // Button pressed
    if (servoAngle == 90) {
      servoAngle = 0;
    } else {
      servoAngle = 90;
    }
    myServo.write(servoAngle);  // Move to 90°
    delay(500);
    countdown -= 500;
  }
  delay(200);
  countdown -= 200;
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

int readSensor() {
  digitalWrite(sensorPower, HIGH);
  delay(10);
  val = analogRead(sensorPin);
  digitalWrite(sensorPower, LOW);
  return val;
}

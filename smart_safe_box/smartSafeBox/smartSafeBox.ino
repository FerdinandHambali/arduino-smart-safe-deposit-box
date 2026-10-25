#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Keypad.h>
#include <Servo.h>

#define LED_RED_PIN 11
#define LED_GREEN_PIN 12
#define BUZZER_PIN 13

#define TRIGGER_PIN A1
#define ECHO_PIN A2
const float THRESHOLD_CM = 40.0;

unsigned long lastPingMs = 0;
const unsigned long PING_INTERVAL_MS = 200;
bool activeMode = false;

//lcd
LiquidCrystal_I2C lcd(0x27, 16, 2);

//keypad
const byte ROWS = 4;
const byte COLS = 4;

//servo
Servo doorServo;
#define servoPin 10
int pos = 0;

char keys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

byte rowPins[ROWS] = {2, 3, 4, 5};
byte colPins[COLS] = {6, 7, 8, 9};

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

//lcd starting
String input = "";
bool unlocked = false;

float readDistanceCM() {
  digitalWrite(TRIGGER_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIGGER_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGGER_PIN, LOW);

  long duration = pulseIn(ECHO_PIN, HIGH, 30000);
  if (duration == 0) return 9999;
  return (duration * 0.0343) / 2.0;
}

void sleepMode() {
  digitalWrite(LED_RED_PIN, LOW);
  digitalWrite(LED_GREEN_PIN, LOW);
  digitalWrite(BUZZER_PIN, LOW);

  unlocked = false;
  input = "";
  pos = 90;                 // swapped (was 0)
  doorServo.write(pos);

  lcd.clear();
  lcd.noBacklight();
}

void wakeMode() {
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Welcome");
  delay(800);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Enter:");

  digitalWrite(LED_RED_PIN, HIGH);
  digitalWrite(LED_GREEN_PIN, LOW);
  digitalWrite(BUZZER_PIN, LOW);

  unlocked = false;
  input = "";
  pos = 90;                 // swapped (was 0)
  doorServo.write(pos);
}

void setup() {
  //lcd set up
  lcd.init();
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Enter:");

  pinMode(LED_RED_PIN, OUTPUT);
  pinMode(LED_GREEN_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  digitalWrite(BUZZER_PIN, LOW);

  digitalWrite(LED_RED_PIN, HIGH);
  digitalWrite(LED_GREEN_PIN, LOW);

  //servo set up
  doorServo.attach(servoPin);
  doorServo.write(90);      // swapped (was 0)

  pinMode(TRIGGER_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  activeMode = false;
  sleepMode();
}

void loop() {
  if (millis() - lastPingMs >= PING_INTERVAL_MS) {
    lastPingMs = millis(); //return miliseconds since arduino is activated, jadi kalau pake delay, the whole system bakal off selama delay itu, soalnya harus control servo, and read keypad + lcd + us sensor at the same time
    float distance = readDistanceCM();

    bool shouldBeActive = (distance <= THRESHOLD_CM);

    if (!activeMode && shouldBeActive) {
      activeMode = true;
      wakeMode();
    } else if (activeMode && !shouldBeActive) {
      activeMode = false;
      sleepMode();
    }
  }

  if (!activeMode) return;

  char key = keypad.getKey();
  if (!key) return;

  if (unlocked) {
    if (key == 'D') {
      pos = 90;             // swapped (was 0)
      doorServo.write(pos);

      digitalWrite(LED_GREEN_PIN, LOW);
      digitalWrite(LED_RED_PIN, HIGH);

      unlocked = false;

      input = "";
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Enter:");
    }
    return;
  }

  //clear
  if (key == '#') {
    input = "";
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Enter:");
    return;
  }

  //submit
  if (key == '*') {
    lcd.clear();
    lcd.setCursor(0, 0);

    if (input == "123ABC") {
      lcd.print("Unlocked");
      lcd.setCursor(0, 1);
      lcd.print("D to close");
      pos = 0;              // swapped (was 90)
      doorServo.write(pos);

      digitalWrite(LED_RED_PIN, LOW);
      digitalWrite(LED_GREEN_PIN, HIGH);
      digitalWrite(BUZZER_PIN, LOW);

      unlocked = true;
    } else {
      lcd.print("Wrong Passcode");
      pos = 90;             // swapped (was 0)
      doorServo.write(pos);

      digitalWrite(LED_GREEN_PIN, LOW);
      digitalWrite(LED_RED_PIN, HIGH);

      digitalWrite(BUZZER_PIN, HIGH);
      delay(250);
      digitalWrite(BUZZER_PIN, LOW);
      delay(150);
      digitalWrite(BUZZER_PIN, HIGH);
      delay(250);
      digitalWrite(BUZZER_PIN, LOW);
    }

    delay(1500);
    input = "";
    if (!unlocked) {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Enter:");
    }
    return;
  }

  // ---------- NORMAL KEY ----------
  if (input.length() < 16) {
    input += key;
    lcd.setCursor(0, 1);
    lcd.print(input);
  }
}

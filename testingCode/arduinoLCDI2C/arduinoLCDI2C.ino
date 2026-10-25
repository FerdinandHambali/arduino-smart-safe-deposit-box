#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Keypad.h>
#include <Servo.h>

//lcd
LiquidCrystal_I2C lcd(0x27, 16, 2);

//keypad
const byte ROWS = 4;
const byte COLS = 4;

//servo
Servo doorServo;
#define servoPin 12
int pos = 0;

char keys[ROWS][COLS] = {
  {'D','C','B','A'},
  {'#','9','6','3'},
  {'0','8','5','2'},
  {'*','7','4','1'}
};

byte rowPins[ROWS] = {2, 3, 4, 5};
byte colPins[COLS] = {6, 7, 8, 9};

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

//lcd starting
String input = "";
bool unlocked = false;

void setup() {
  //lcd set up
  lcd.init();
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Enter:");

  //servo set up
  doorServo.attach(servoPin);
  doorServo.write(0);
}

void loop() {
  char key = keypad.getKey();
  if (!key) return;

  if (unlocked) {
    if (key == 'D') {
      pos = 0;
      doorServo.write(pos);
      unlocked = false;

      input = "";
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Enter:");
    }
    return;
  }

  //clear
  if (key == '#') {
    input = "";
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Enter:");
    return;
  }

  //submit
  if (key == '*') {
    lcd.clear();
    lcd.setCursor(0,0);

    if (input == "988613") {
      lcd.print("Unlocked");
      lcd.setCursor(0,1);
      lcd.print("D to close");
      pos = 90;
      doorServo.write(pos);
      unlocked = true;
    } else {
      lcd.print("Wrong Passcode");
      pos = 0;
      doorServo.write(pos);
    }

    delay(1500);
    input = "";
    if (!unlocked) {
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Enter:");
    }
    return;
  }

  // ---------- NORMAL KEY ----------
  if (input.length() < 16) {
    input += key;
    lcd.setCursor(0,1);
    lcd.print(input);
  }
}

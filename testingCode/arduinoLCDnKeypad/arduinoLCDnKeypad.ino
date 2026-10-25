#include <LiquidCrystal.h>
#include <Keypad.h>

// LCD: RS, E, D4, D5, D6, D7
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

// 4x4 keypad layout (most common)
const byte ROWS = 4;
const byte COLS = 4;

char keys[ROWS][COLS] = {
  {'D','C','B','A'},
  {'#','9','6','3'},
  {'0','8','5','2'},
  {'*','7','4','1'}
};

// Arduino pins connected to keypad (R1..R4, C1..C4)
byte rowPins[ROWS] = {6, 7, 8, 9};
byte colPins[COLS] = {10, 13, A0, A1};

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

int cursorPos = 0;

void setup() {
  lcd.begin(16, 2);
  lcd.clear();
  lcd.print("Enter:");
  lcd.setCursor(0, 1);
}

void loop() {
  char key = keypad.getKey();

  if (key) {
    // Special keys
    if (key == '*') {            // Clear
      lcd.setCursor(0, 1);
      lcd.print("                "); // 16 spaces
      lcd.setCursor(0, 1);
      cursorPos = 0;
    }
    else if (key == '#') {       // "Enter"
      lcd.setCursor(0, 0);
      lcd.print("Submitted      ");
      delay(800);
      lcd.setCursor(0, 0);
      lcd.print("Enter:         ");
      lcd.setCursor(cursorPos, 1);
    }
    else {
      // Print key on line 2
      if (cursorPos < 16) {
        lcd.setCursor(cursorPos, 1);
        lcd.print(key);
        cursorPos++;
      }
    }
  }
}

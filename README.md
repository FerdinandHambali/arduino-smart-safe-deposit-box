# Arduino Smart Safe Deposit Box

**Embedded Systems | Arduino | SolidWorks | 3D Design**

## Project Overview

This project involves the design and development of an Arduino-based electronic safe deposit box integrating embedded programming, electronic components, and mechanical design.

The system uses keypad-based passcode authentication to control a servo-operated locking mechanism. An ultrasonic sensor detects user proximity and activates the system, while an LCD, LEDs, and buzzer provide visual and audible feedback.

The enclosure was designed using SolidWorks, with CAD models and 3D-printing files developed for the mechanical components.

## Technologies Used

- **Microcontroller:** Arduino
- **Programming Language:** C/C++ (Arduino)
- **Development Software:** Arduino IDE
- **Mechanical Design:** SolidWorks
- **Manufacturing Design:** 3D printing
- **Actuation:** Servo motor
- **Sensors:** Ultrasonic distance sensor
- **User Interface:** 4×4 membrane keypad, 16×2 I2C LCD
- **Indicators:** Red and green LEDs, buzzer

## System Features

### 1. Keypad Authentication

- Accepts passcode input through a 4×4 keypad.
- Validates the entered passcode against a predefined value.
- Allows users to clear or submit their input.
- Provides success or failure messages on the LCD.

### 2. Servo-Based Locking Mechanism

- Uses a servo motor to control the locking mechanism.
- Unlocks the safe when the correct passcode is entered.
- Allows the user to relock the safe using the keypad.
- Returns the mechanism to its locked position when the system becomes inactive.

### 3. Ultrasonic Proximity Detection

- Uses an ultrasonic sensor to measure the distance between the user and the safe.
- Activates the user interface when an object is detected within 40 cm.
- Deactivates the interface when the user moves outside the detection range.
- Turns off the LCD backlight and indicators in inactive mode.

### 4. LCD and LED Feedback

The system provides feedback using a 16×2 LCD and two LEDs.

- **Red LED:** Locked state
- **Green LED:** Unlocked state
- **LCD:** Passcode prompts, authentication results, and system messages

### 5. Buzzer Feedback

The buzzer produces an audible notification when an incorrect passcode is submitted.

### 6. Mechanical Design

The safe enclosure was designed in SolidWorks.

Design components include:

- Main enclosure and walls
- Door and locking mechanism
- Servo mounting components
- Arduino and electronics mounting structures
- Keypad and LCD openings
- Ultrasonic sensor and LED mounting positions

SolidWorks assembly and part files are provided alongside STL and 3MF files for selected 3D-printing components.

## System Operation

1. **Inactive Mode:** The safe remains locked with its LCD backlight and indicators disabled.
2. **User Detection:** The ultrasonic sensor detects an approaching user within the configured distance.
3. **System Activation:** The LCD turns on and requests a passcode.
4. **Passcode Entry:** The user enters the passcode through the keypad.
5. **Authentication:** The system compares the entered passcode with the predefined value.
6. **Unlocking:** A correct passcode activates the servo and changes the status LED to green.
7. **Incorrect Entry:** An incorrect passcode keeps the safe locked and activates the buzzer.
8. **Relocking:** The user can press `D` to relock the safe. The system also returns to its locked state when proximity activation ends.

### Keypad Controls

| Key | Function |
|---|---|
| `#` | Clear entered passcode |
| `*` | Submit passcode |
| `D` | Relock after unlocking |

## Repository Structure

- `smartSafeBox/smartSafeBox/smartSafeBox.ino` – Integrated Arduino control program
- `smartSafeBox/Assembly_Fixed.SLDASM` – Revised SolidWorks assembly
- `smartSafeBox/Assembly.SLDASM` – Earlier assembly
- `smartSafeBox/Part/` – Mechanical enclosure components
- `smartSafeBox/Holes/` – Component mounting and cutout models
- `smartSafeBox/print/` – 3D-printing files
- `Servo/` – Additional CAD component
- `Screenshots/` – Project photographs and demonstrations, when added

## How to Run

1. Install Arduino IDE.
2. Install the required `Keypad` and `LiquidCrystal_I2C` libraries. The sketch also uses `Wire` and `Servo`.
3. Open `smartSafeBox/smartSafeBox/smartSafeBox.ino`.
4. Connect the keypad, LCD, servo, LEDs, buzzer, and ultrasonic sensor according to the pin definitions in the source code.
5. Select the appropriate Arduino board and port.
6. Upload the program.
7. Test the proximity activation, keypad authentication, servo locking, and feedback indicators.

**Note:** The source contains a hardcoded demonstration passcode. This is an academic electronics prototype, not a production-grade security system. The passcode and authentication design should be improved before any real security use.

## Skills Demonstrated

- Arduino embedded programming
- Electronic circuit integration
- Sensor and actuator control
- Keypad input processing
- LCD interface programming
- Servo motor control
- Sequential control logic
- SolidWorks CAD modelling
- Mechanical enclosure design
- Integration of hardware and software

## Project Status

Prototype source code and CAD design files are included for documentation and further development.

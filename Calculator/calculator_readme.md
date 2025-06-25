# Thash Calculator - Arduino Scientific Calculator

A full-featured calculator using Arduino, 4x4 keypad, LCD display, and buzzer. Supports basic arithmetic, binary/hex conversion, sleep mode, and advanced key combinations with audio feedback.

## Features

- 🧮 **Full Calculator Functions** - Addition, subtraction, multiplication, division
- 🔢 **Number Base Conversion** - Decimal to Binary/Hex display (1-256)
- 💤 **Sleep Mode** - Power saving with double-click activation
- 🎵 **Audio Feedback** - Buzzer sounds for keypress confirmation and alerts
- ⌨️ **Advanced Key Controls** - Single-click, double-click, and long-press functions
- 🚨 **Error Handling** - Division by zero and overflow protection
- 📺 **16x2 LCD Display** - Clear number display with operation indicators
- 🧹 **Smart Backspace** - Single character deletion and smart clearing

## Hardware Requirements

### Components
- Arduino Uno (or compatible)
- 4x4 Matrix Keypad
- 16x2 I2C LCD Display (0x27 address)
- Piezo Buzzer
- Jumper wires
- Breadboard (optional)

### Wiring Diagram

```
Arduino Pin → Component
─────────────────────────
D10         → Buzzer (+)
GND         → Buzzer (-)

D6          → Keypad Row 1
D7          → Keypad Row 2
D8          → Keypad Row 3
D9          → Keypad Row 4
A0          → Keypad Col 1
A1          → Keypad Col 2
A2          → Keypad Col 3
A3          → Keypad Col 4

SDA (A4)    → LCD SDA
SCL (A5)    → LCD SCL
5V          → LCD VCC
GND         → LCD GND
```

## Required Libraries

Install these libraries through Arduino IDE Library Manager:

```cpp
#include <Wire.h>             // Built-in Arduino library
#include <LiquidCrystal_I2C.h> // LiquidCrystal I2C by Frank de Brabander
#include <Keypad.h>           // Keypad library by Mark Stanley
```

## Keypad Layout & Functions

### Basic Layout
```
┌───┬───┬───┬───┐
│ 1 │ 2 │ 3 │ + │  ← Numbers & Addition
├───┼───┼───┼───┤
│ 4 │ 5 │ 6 │ - │  ← Numbers & Subtraction
├───┼───┼───┼───┤
│ 7 │ 8 │ 9 │ × │  ← Numbers & Multiplication
├───┼───┼───┼───┤
│ * │ 0 │ # │ ÷ │  ← Special & Division
└───┴───┴───┴───┘
```

### Key Functions

**Number Keys (0-9):**
- Enter digits for calculations
- Maximum 10 digits per number

**Operation Keys:**
- **A** = Addition (+)
- **B** = Subtraction (-)
- **C** = Multiplication (×)
- **D** = Division (÷)

**Special Keys:**

**`*` (Star Key) - Multiple Functions:**
- **Single Click** = Backspace (delete last character)
- **Double Click** = Clear All (reset calculator)
- **Long Press (1s)** = Show Welcome Screen

**`#` (Hash Key) - Multiple Functions:**
- **Single Click** = Equals (calculate result)
- **Single Click on Number (1-256)** = Binary/Hex Conversion
- **Double Click** = Enter Sleep Mode

## Advanced Features

### Binary/Hex Conversion Mode
When you have a number from 1-256 displayed and press `#`:

**Display Format:**
```
Bin: 01000001    ← 8-bit binary
Dec: 65  Hex: 41h ← Decimal and hexadecimal
```

**Usage:**
1. Enter a number (1-256)
2. Press `#` for conversion
3. Press `#` again to return to calculator

### Sleep Mode
**Activation:** Double-click `#` key
- LCD backlight turns off
- Calculator enters low-power state
- Press any key to wake up
- Returns to welcome screen on wake

### Error Handling
The calculator handles various error conditions:

**Division by Zero:**
```
ERROR:
Division by 0
```

**Number Overflow:**
```
ERROR:
Overflow
```

**Recovery:** Press `*` (any click type) to clear errors

## Audio Feedback System

### Sound Types

**Key Press Confirmation:**
- 500Hz tone for 100ms
- Plays on every valid key press

**Welcome Screen Melody:**
- Musical sequence: C4 → D#4 → F4 → G4
- Plays on startup and welcome screen

**Error Alert:**
- Three 300Hz beeps
- Indicates calculation errors

**Binary/Hex Mode:**
- Ascending tones (800Hz → 1000Hz)
- Confirms conversion display

**Double-Click Confirmation:**
- Two 800Hz beeps
- Confirms special double-click actions

## Calculator Operations

### Basic Arithmetic

**Addition Example:**
```
Input: 25 + 17 =
Display: 42
```

**Chain Operations:**
```
Input: 10 + 5 - 3 =
Display: 12
```

**Decimal Results:**
```
Input: 22 ÷ 7 =
Display: 3.142857
```

### Operation Display
During operation entry, the bottom line shows:
```
Top:    [Current Result]
Bottom: [25 +]  ← Shows number and operation
```

## Usage Instructions

### Basic Calculator Use
1. Power on Arduino - Welcome screen appears
2. Enter first number using digit keys
3. Press operation key (A, B, C, or D)
4. Enter second number
5. Press `#` for result

### Number Base Conversion
1. Enter a number between 1-256
2. Press `#` (equals key)
3. View binary, decimal, and hex values
4. Press `#` again to return to calculator

### Backspace Operations
- **Single `*` click** = Delete last digit
- **Double `*` click** = Clear everything
- **Long `*` press** = Show welcome screen

### Sleep Mode
- **Double `#` click** = Enter sleep mode
- **Any key** = Wake up from sleep

## Troubleshooting

### Common Issues

**LCD shows garbage or nothing:**
- Check I2C connections (SDA/SCL to A4/A5)
- Verify LCD address (0x27 or try 0x3F)
- Check power connections (5V/GND)

**No buzzer sound:**
- Verify buzzer polarity (+ to D10, - to GND)
- Check if buzzer is working (swap with known good one)
- Ensure pin 10 connection is secure

**Keypad not responding:**
- Verify all row/column pin connections
- Check for loose wires on breadboard
- Test individual keys using serial monitor

**Calculator giving wrong results:**
- Check for number overflow (>16 digits)
- Verify operation sequence
- Clear calculator with double-click `*`

**Sleep mode not working:**
- Ensure double-click timing is correct (<500ms between clicks)
- Check if hash key is properly connected
- Try single hash press first to test key

### Debug Mode

Add this to setup() for serial debugging:
```cpp
Serial.begin(9600);
```

Add this to processKey() to monitor key presses:
```cpp
Serial.print("Key pressed: ");
Serial.println(key);
```

## Performance Specifications

- **Maximum Number Length:** 10 digits
- **Maximum Display Length:** 16 characters
- **Decimal Precision:** 6 decimal places
- **Binary Conversion Range:** 1-256 (8-bit)
- **Double-Click Timing:** 500ms window
- **Long Press Timing:** 1000ms hold
- **Key Response Time:** ~100ms with audio feedback

## Customization Options

### Modify Welcome Message
```cpp
void showWelcomeScreen() {
  lcd.clear();
  lcd.print("   Your Name");      // Line 1 (centered)
  lcd.setCursor(0, 1);
  lcd.print("Your Calculator");   // Line 2
  // ... rest of function
}
```

### Change Audio Frequencies
```cpp
// Key press sound
tone(buzzerPin, 600, 100);  // Change 600 to desired frequency

// Error sound  
tone(buzzerPin, 200, 300);  // Lower frequency for errors
```

### Adjust Timing Values
```cpp
const unsigned long longPressTime = 1500;    // Longer press required
const unsigned long doubleClickTime = 300;   // Faster double-click needed
```

## Technical Notes

### Memory Usage
- Program uses approximately 60% of Arduino Uno flash memory
- RAM usage is optimized for string operations
- No EEPROM storage used (settings reset on power cycle)

### Floating Point Precision
- Uses Arduino's double precision (actually float on Uno)
- Results may have minor rounding errors for complex decimals
- Integer results display without decimal points

## License

Open source - modify and share freely!

## Version History

- **v1.0** - Basic calculator functions
- **v1.1** - Added binary/hex conversion
- **v1.2** - Sleep mode and advanced key controls
- **v1.3** - Enhanced audio feedback system

---

**Project:** Thash Calculator  
**Version:** 1.3  
**Last Updated:** June 2025  
**Compatible:** Arduino Uno, Nano, Pro Mini
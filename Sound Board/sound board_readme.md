# SoundFX Pad - Arduino Sound Effects Controller

A customizable sound effects pad using Arduino, 4x4 keypad, LCD display, and buzzer. Play up to 9 different sound effects with full playback control including pause/resume functionality.

## Features

- 🎵 **9 Sound Effect Slots** - Assign custom sound effects to keys 1-9
- ⏯️ **Play/Pause Control** - Pause and resume playback anytime
- 🛑 **Stop Function** - Immediately stop any playing sound
- 📺 **LCD Display** - Real-time status and control instructions
- 🎛️ **Easy Customization** - Simple array-based sound definition
- 🚫 **Instant Cancel** - Stop playback immediately from any state

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
#include <Keypad.h>           // Keypad library by Mark Stanley
#include <Wire.h>             // Built-in Arduino library
#include <LiquidCrystal_I2C.h> // LiquidCrystal I2C by Frank de Brabander
```

## Control Layout

### Keypad Functions
```
┌───┬───┬───┬───┐
│ 1 │ 2 │ 3 │ A │  ← 1-3: Sound FX slots
├───┼───┼───┼───┤
│ 4 │ 5 │ 6 │ B │  ← 4-6: Sound FX slots  
├───┼───┼───┼───┤
│ 7 │ 8 │ 9 │ C │  ← 7-9: Sound FX slots
├───┼───┼───┼───┤
│ * │ 0 │ # │ D │  ← *=STOP, #=PAUSE/RESUME
└───┴───┴───┴───┘
```

### Control Keys
- **`*`** (Asterisk) = **STOP** - Immediately stops playback
- **`#`** (Hash) = **PAUSE/RESUME** - Toggles pause during playback
- **`1-9`** = **PLAY** - Starts the assigned sound effect

## How to Add Custom Sound Effects

### Step 1: Define Your Sound Effect

Find the sound effect section in the code:

```cpp
// ==============================================
// SOUND EFFECT X - [YOUR SOUND NAME HERE]
// ==============================================
int soundFXX[] = {
  // Add your frequencies here (Hz values)
  440, 523, 659, 784, 0, 659, 523, 440
};
int soundFXX_durations[] = {
  // Add corresponding note durations 
  4, 4, 4, 4, 8, 4, 4, 2
};
```

### Step 2: Add Frequencies and Durations

**Frequencies (Hz):**
- Use musical note frequencies (440 = A4, 523 = C5, etc.)
- Use 0 for silence/rest
- Common frequencies: 262(C4), 294(D4), 330(E4), 349(F4), 392(G4), 440(A4), 494(B4), 523(C5)

**Note Durations:**
- `1` = Whole note (longest)
- `2` = Half note
- `4` = Quarter note (standard)
- `8` = Eighth note
- `16` = Sixteenth note (shortest)

### Step 3: Update Display Name

In the switch statement, update the LCD display text:

```cpp
case '1':
  lcd.print("Playing: Laser");  // Your custom name here
  playSoundEffect(soundFX1, soundFX1_durations, sizeof(soundFX1)/sizeof(int));
  break;
```

## Example Sound Effects

### Simple Beep
```cpp
int beepFX[] = {1000, 0, 1000, 0, 1000};
int beepFX_durations[] = {8, 8, 8, 8, 8};
```

### Laser Sound
```cpp
int laserFX[] = {2000, 1800, 1600, 1400, 1200, 1000, 800};
int laserFX_durations[] = {16, 16, 16, 16, 16, 16, 8};
```

### Explosion
```cpp
int explosionFX[] = {100, 150, 200, 180, 160, 140, 120, 100, 80};
int explosionFX_durations[] = {16, 16, 16, 8, 8, 8, 4, 4, 2};
```

### Siren
```cpp
int sirenFX[] = {800, 1200, 800, 1200, 800, 1200, 800, 1200};
int sirenFX_durations[] = {4, 4, 4, 4, 4, 4, 4, 4};
```

## Usage Instructions

### Basic Operation
1. Power on the Arduino
2. LCD displays "SoundFX Pad Ready" and "*=Stop #=Pause"
3. Press any number key (1-9) to play the assigned sound effect
4. Use `*` to stop or `#` to pause/resume during playback

### During Playback
- **To Pause:** Press `#` key - LCD shows "PAUSED" and "# to resume"
- **To Resume:** Press `#` again - LCD shows "RESUMING..." then continues
- **To Stop:** Press `*` key - Immediately stops and returns to ready state

### Pause State Options
When paused, you can:
- Press `#` to resume from where you left off
- Press `*` to stop completely and return to main menu

## Troubleshooting

### Common Issues

**No sound from buzzer:**
- Check buzzer polarity (+ to pin 10, - to GND)
- Verify buzzer is working (try simple tone test)
- Check pin 10 connection

**LCD not displaying:**
- Verify I2C address (default 0x27, may be 0x3F)
- Check SDA/SCL connections (A4/A5 on Uno)
- Test I2C scanner to find address

**Keypad not responding:**
- Check all row/column connections
- Verify pin assignments match code
- Test individual keys with serial monitor

**Sound effects not playing:**
- Ensure arrays have matching lengths
- Check for empty arrays (add sample frequencies)
- Verify switch case matches your key

### Serial Monitor Debug
Enable Serial Monitor (9600 baud) to see key presses:
```
Key Pressed: 1
Key Pressed: *
Key Pressed: #
```

## Customization Tips

### Creating Realistic Sound Effects
- **Robot Voice:** Use square wave patterns with abrupt frequency changes
- **Sci-Fi Effects:** Combine high frequencies with rapid transitions
- **Alarms:** Use alternating frequencies with consistent timing
- **Musical Notes:** Use proper musical intervals and scales

### Performance Notes
- Keep sound effect arrays reasonable in size (< 100 notes)
- Use shorter durations for rapid-fire effects
- Test each sound effect individually before adding to final code
- Consider speaker/buzzer limitations for very high/low frequencies

## License

Open source - feel free to modify and share!

## Contributing

Found a bug or want to add features? Submit issues or pull requests on GitHub.

---

**Version:** 1.0  
**Last Updated:** June 2025  
**Compatible:** Arduino Uno, Nano, Pro Mini

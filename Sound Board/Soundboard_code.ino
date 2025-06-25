#include <Keypad.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

const int buzzerPin = 10;

// Keypad configuration
const byte ROWS = 4;
const byte COLS = 4;
char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte rowPins[ROWS] = {6, 7, 8, 9};
byte colPins[COLS] = {A0, A1, A2, A3};
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

// LCD configuration
LiquidCrystal_I2C lcd(0x27, 16, 2);

// ==============================================
// SOUND EFFECT 1 - RICKROLL (Never Gonna Give You Up)
// ==============================================
int soundFX1[] = {
  // Never Gonna Give You Up - Rick Astley
  330, 330, 370, 330, 440, 415, 0,
  330, 330, 370, 330, 494, 440, 0,
  330, 330, 660, 554, 440, 415, 370, 0,
  587, 587, 554, 440, 494, 440, 0,
  
  // "Never gonna give you up"
  440, 494, 523, 494, 466, 440, 415, 440,
  415, 370, 330, 370, 415, 440,
  
  // "Never gonna let you down"  
  440, 494, 523, 494, 466, 440, 415, 440,
  415, 370, 330, 370, 415, 330,
  
  // "Never gonna run around"
  330, 370, 415, 370, 349, 330, 311, 330,
  311, 277, 247, 277, 311, 330
};
int soundFX1_durations[] = {
  4, 4, 4, 4, 4, 2, 4,
  4, 4, 4, 4, 4, 2, 4,
  4, 4, 4, 4, 4, 4, 2, 4,
  4, 4, 4, 4, 4, 2, 4,
  
  4, 4, 4, 4, 4, 4, 4, 4,
  4, 4, 4, 4, 4, 2,
  
  4, 4, 4, 4, 4, 4, 4, 4,
  4, 4, 4, 4, 4, 2,
  
  4, 4, 4, 4, 4, 4, 4, 4,
  4, 4, 4, 4, 4, 2
};

// ==============================================
// SOUND EFFECT 2 - [ADD YOUR SOUND NAME HERE]
// ==============================================
int soundFX2[] = {
  // Add your frequencies here
};
int soundFX2_durations[] = {
  // Add corresponding durations here
};

// ==============================================
// SOUND EFFECT 3 - [ADD YOUR SOUND NAME HERE]
// ==============================================
int soundFX3[] = {
  // Add your frequencies here
};
int soundFX3_durations[] = {
  // Add corresponding durations here
};

// ==============================================
// SOUND EFFECT 4 - [ADD YOUR SOUND NAME HERE]
// ==============================================
int soundFX4[] = {
  // Add your frequencies here
};
int soundFX4_durations[] = {
  // Add corresponding durations here
};

// ==============================================
// SOUND EFFECT 5 - [ADD YOUR SOUND NAME HERE]
// ==============================================
int soundFX5[] = {
  // Add your frequencies here
};
int soundFX5_durations[] = {
  // Add corresponding durations here
};

// ==============================================
// SOUND EFFECT 6 - [ADD YOUR SOUND NAME HERE]
// ==============================================
int soundFX6[] = {
  // Add your frequencies here
};
int soundFX6_durations[] = {
  // Add corresponding durations here
};

// ==============================================
// SOUND EFFECT 7 - [ADD YOUR SOUND NAME HERE]
// ==============================================
int soundFX7[] = {
  // Add your frequencies here
};
int soundFX7_durations[] = {
  // Add corresponding durations here
};

// ==============================================
// SOUND EFFECT 8 - [ADD YOUR SOUND NAME HERE]
// ==============================================
int soundFX8[] = {
  // Add your frequencies here
};
int soundFX8_durations[] = {
  // Add corresponding durations here
};

// ==============================================
// SOUND EFFECT 9 - [ADD YOUR SOUND NAME HERE]
// ==============================================
int soundFX9[] = {
  // Add your frequencies here
};
int soundFX9_durations[] = {
  // Add corresponding durations here
};

// Global control variables
volatile bool cancelPlayback = false;
volatile bool pausePlayback = false;
volatile bool isPlaying = false;


// ==============================================
// SOUND PLAYBACK FUNCTION
// ==============================================
void playSoundEffect(int* melody, int* durations, int length) {
  cancelPlayback = false; // Reset cancel flag at start
  pausePlayback = false;  // Reset pause flag
  isPlaying = true;       // Set playing flag

  for (int i = 0; i < length; i++) {
    // Check for control keys
    char controlKey = keypad.getKey();
    if (controlKey == '*') {
      cancelPlayback = true;
      break;
    }
    if (controlKey == '#') {
      pausePlayback = !pausePlayback; // Toggle pause
      if (pausePlayback) {
        noTone(buzzerPin);
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("PAUSED");
        lcd.setCursor(0, 1);
        lcd.print("# to resume");
      }
    }

    // Handle pause state
    while (pausePlayback && !cancelPlayback) {
      char resumeKey = keypad.getKey();
      if (resumeKey == '#') {
        pausePlayback = false;
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("RESUMING...");
        delay(500);
        break;
      }
      if (resumeKey == '*') {
        cancelPlayback = true;
        break;
      }
      delay(50);
    }

    if (cancelPlayback) break;

    // Play the note
    int duration = 1000 / durations[i];
    if (melody[i] == 0) {
      noTone(buzzerPin);
    } else {
      tone(buzzerPin, melody[i], duration);
    }

    // Delay in smaller chunks so we can poll keypad for controls
    unsigned long start = millis();
    while (millis() - start < duration * 1.3) {
      char k = keypad.getKey();
      if (k == '*') {
        cancelPlayback = true;
        break;
      }
      if (k == '#') {
        pausePlayback = !pausePlayback;
        if (pausePlayback) {
          noTone(buzzerPin);
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("PAUSED");
          lcd.setCursor(0, 1);
          lcd.print("# to resume");
          break;
        }
      }
      delay(10);
    }

    noTone(buzzerPin);

    if (cancelPlayback) break;
  }
  
  isPlaying = false; // Clear playing flag when done
}


// ==============================================
// ARDUINO SETUP
// ==============================================
void setup() {
  pinMode(buzzerPin, OUTPUT);
  Serial.begin(9600);

  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("SoundFX Pad Ready");
  lcd.setCursor(0, 1);
  lcd.print("*=Stop #=Pause");
}


// ==============================================
// MAIN LOOP
// ==============================================
void loop() {
  char key = keypad.getKey();
  
  if (key) {
    Serial.print("Key Pressed: ");
    Serial.println(key);

    // Cancel playback with asterisk key
    if (key == '*') {
      cancelPlayback = true;
      pausePlayback = false;
      noTone(buzzerPin);
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Playback stopped");
      delay(1000);
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("SoundFX Pad Ready");
      lcd.setCursor(0, 1);
      lcd.print("*=Stop #=Pause");
      return;
    }

    // Handle pause/resume with hash key (only if something is playing)
    if (key == '#' && isPlaying) {
      // Pause functionality is handled within playSoundEffect function
      return;
    }

    // Display key pressed
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Key: ");
    lcd.print(key);
    lcd.setCursor(0, 1);

    // Sound effect mappings
    switch(key) {
      case '1':
        lcd.print("Playing: Rickroll");  // Never Gonna Give You Up
        playSoundEffect(soundFX1, soundFX1_durations, sizeof(soundFX1)/sizeof(int));
        break;
        
      case '2':
        lcd.print("Playing: FX2");  // Replace "FX2" with your sound name
        playSoundEffect(soundFX2, soundFX2_durations, sizeof(soundFX2)/sizeof(int));
        break;
        
      case '3':
        lcd.print("Playing: FX3");  // Replace "FX3" with your sound name
        playSoundEffect(soundFX3, soundFX3_durations, sizeof(soundFX3)/sizeof(int));
        break;
        
      case '4':
        lcd.print("Playing: FX4");  // Replace "FX4" with your sound name
        playSoundEffect(soundFX4, soundFX4_durations, sizeof(soundFX4)/sizeof(int));
        break;
        
      case '5':
        lcd.print("Playing: FX5");  // Replace "FX5" with your sound name
        playSoundEffect(soundFX5, soundFX5_durations, sizeof(soundFX5)/sizeof(int));
        break;
        
      case '6':
        lcd.print("Playing: FX6");  // Replace "FX6" with your sound name
        playSoundEffect(soundFX6, soundFX6_durations, sizeof(soundFX6)/sizeof(int));
        break;
        
      case '7':
        lcd.print("Playing: FX7");  // Replace "FX7" with your sound name
        playSoundEffect(soundFX7, soundFX7_durations, sizeof(soundFX7)/sizeof(int));
        break;
        
      case '8':
        lcd.print("Playing: FX8");  // Replace "FX8" with your sound name
        playSoundEffect(soundFX8, soundFX8_durations, sizeof(soundFX8)/sizeof(int));
        break;
        
      case '9':
        lcd.print("Playing: FX9");  // Replace "FX9" with your sound name
        playSoundEffect(soundFX9, soundFX9_durations, sizeof(soundFX9)/sizeof(int));
        break;
        
      default:
        lcd.print("No FX mapped");
        delay(1000);
        break;
    }

    // Return to ready state after playback (if not cancelled)
    if (!cancelPlayback && !pausePlayback) {
      delay(500);
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("SoundFX Pad Ready");
      lcd.setCursor(0, 1);
      lcd.print("*=Stop #=Pause");
    }
  }
}

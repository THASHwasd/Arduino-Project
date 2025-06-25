#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Keypad.h>

// Initialize the I2C LCD with the address 0x27 (common for 16x2 LCDs)
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Keypad setup
const byte ROWS = 4;
const byte COLS = 4;
char keys[ROWS][COLS] = {
  {'1','2','3','A'},  // A = +
  {'4','5','6','B'},  // B = -
  {'7','8','9','C'},  // C = *
  {'*','0','#','D'}   // D = /, * = backspace/clear, # = equals
};
byte rowPins[ROWS] = {6, 7, 8, 9};
byte colPins[COLS] = {A0, A1, A2, A3};
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

const int buzzerPin = 10;

// Calculator variables
String display = "0";
String currentNumber = "";
String operation = "";
double firstNumber = 0;
double secondNumber = 0;
bool operationPressed = false;
bool equalsPressed = false;
bool errorState = false;

// Variables for star key press detection
unsigned long starPressTime = 0;
bool starPressed = false;
const unsigned long longPressTime = 1000;
unsigned long lastStarPress = 0;
const unsigned long doubleClickTime = 500;

// Variables for hash key double-click detection
unsigned long lastHashPress = 0;

// Sleep mode
bool sleepMode = false;

void setup() {
  lcd.init();
  lcd.backlight();
  pinMode(buzzerPin, OUTPUT);
  showWelcomeScreen();
}

void loop() {
  if (sleepMode) {
    char key = keypad.getKey();
    if (key) wakeUp();
    return;
  }

  char key = keypad.getKey();

  if (key) {
    tone(buzzerPin, 500, 100);
    delay(100);
    noTone(buzzerPin);
    processKey(key);
  }

  if (key == '*') {
    if (!starPressed) {
      starPressed = true;
      starPressTime = millis();
    }
  } else if (starPressed) {
    unsigned long pressDuration = millis() - starPressTime;
    unsigned long currentTime = millis();

    if (pressDuration >= longPressTime) {
      showWelcomeScreen();
    } else {
      if (currentTime - lastStarPress <= doubleClickTime) {
        tone(buzzerPin, 800, 200);
        delay(250);
        tone(buzzerPin, 800, 200);
        delay(200);
        noTone(buzzerPin);
        clearAll();
        lastStarPress = 0;
      } else {
        backspace();
        lastStarPress = currentTime;
      }
    }
    starPressed = false;
  }
}

void processKey(char key) {
  if (errorState && key != '*') return;
  if (key == '*') return;

  if (key >= '0' && key <= '9') handleNumber(key);
  else if (key == 'A' || key == 'B' || key == 'C' || key == 'D') {
    char op;
    if (key == 'A') op = '+';
    else if (key == 'B') op = '-';
    else if (key == 'C') op = '*';
    else op = '/';
    handleOperation(op);
  } else if (key == '#') {
    unsigned long currentTime = millis();
    if (currentTime - lastHashPress <= doubleClickTime) {
      enterSleepMode();
      return;
    } else {
      handleEquals();
      lastHashPress = currentTime;
    }
  }
}

void handleNumber(char key) {
  if (equalsPressed) clearAll();
  if (operationPressed) {
    currentNumber = "";
    operationPressed = false;
  }
  if (currentNumber.length() < 10) {
    if (currentNumber == "0") currentNumber = key;
    else currentNumber += key;
    display = currentNumber;
    updateDisplay();
  }
}

void handleOperation(char op) {
  if (currentNumber == "" && display == "0") return;
  if (operation != "" && !operationPressed && currentNumber != "") {
    calculateResult();
    if (errorState) return;
  }
  firstNumber = display.toDouble();
  operation = op;
  operationPressed = true;
  equalsPressed = false;
  lcd.setCursor(0, 1);
  lcd.print("                ");
  lcd.setCursor(0, 1);
  lcd.print(display + " " + operation);
}

void handleEquals() {
  if (operation == "" || operationPressed) {
    if (currentNumber != "" || display != "0") {
      int num = display.toInt();
      if (num >= 1 && num <= 256) {
        displayBinaryHex(num);
        return;
      }
    }
    return;
  }
  calculateResult();
  equalsPressed = true;
}

void calculateResult() {
  secondNumber = currentNumber != "" ? currentNumber.toDouble() : display.toDouble();
  double result = 0;
  if (operation == "+") result = firstNumber + secondNumber;
  else if (operation == "-") result = firstNumber - secondNumber;
  else if (operation == "*") result = firstNumber * secondNumber;
  else if (operation == "/") {
    if (secondNumber == 0) {
      showError("Division by 0");
      return;
    }
    result = firstNumber / secondNumber;
  }
  if (result == (long)result) display = String((long)result);
  else {
    display = String(result, 6);
    while (display.endsWith("0") && display.indexOf('.') != -1)
      display.remove(display.length() - 1);
    if (display.endsWith(".")) display.remove(display.length() - 1);
  }
  if (display.length() > 16) {
    showError("Overflow");
    return;
  }
  currentNumber = display;
  operation = "";
  operationPressed = false;
  updateDisplay();
  lcd.setCursor(0, 1);
  lcd.print("                ");
}

void backspace() {
  if (errorState || equalsPressed) {
    clearAll();
    return;
  }
  if (operationPressed) {
    operation = "";
    operationPressed = false;
    display = String(firstNumber);
    currentNumber = display;
    lcd.setCursor(0, 1);
    lcd.print("                ");
  } else if (currentNumber.length() > 1) {
    currentNumber.remove(currentNumber.length() - 1);
    display = currentNumber;
  } else {
    currentNumber = "0";
    display = "0";
  }
  updateDisplay();
}

void clearAll() {
  display = "0";
  currentNumber = "";
  operation = "";
  firstNumber = 0;
  secondNumber = 0;
  operationPressed = false;
  equalsPressed = false;
  errorState = false;
  updateDisplay();
  lcd.setCursor(0, 1);
  lcd.print("                ");
}

void showError(String errorMsg) {
  errorState = true;
  lcd.clear();
  lcd.print("ERROR:");
  lcd.setCursor(0, 1);
  lcd.print(errorMsg);
  for (int i = 0; i < 3; i++) {
    tone(buzzerPin, 300, 200);
    delay(300);
    noTone(buzzerPin);
  }
}

void updateDisplay() {
  lcd.setCursor(0, 0);
  lcd.print("                ");
  lcd.setCursor(0, 0);
  int spaces = 16 - display.length();
  for (int i = 0; i < spaces; i++) lcd.print(" ");
  lcd.print(display);
}

void displayBinaryHex(int num) {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Bin: ");
  String binary = "";
  for (int i = 7; i >= 0; i--) binary += ((num >> i) & 1) ? "1" : "0";
  lcd.print(binary);
  lcd.setCursor(0, 1);
  lcd.print("Dec: ");
  lcd.print(num);
  lcd.setCursor(8, 1);
  lcd.print("Hex: ");
  if (num < 16) lcd.print("0");
  lcd.print(num, HEX);
  lcd.print("h");

  char key;
  do {
    key = keypad.getKey();
    if (key && key != '#') {
      tone(buzzerPin, 500, 100);
      delay(100);
      noTone(buzzerPin);
    }
  } while (key != '#');

  tone(buzzerPin, 800, 150);
  delay(200);
  tone(buzzerPin, 1000, 150);
  delay(200);
  noTone(buzzerPin);

  clearAll();
}

void showWelcomeScreen() {
  lcd.clear();
  lcd.print("   Welcome to");
  lcd.setCursor(0, 1);
  lcd.print("Thash Calculator");
  tone(buzzerPin, 262, 300);
  delay(350);
  tone(buzzerPin, 311, 300);
  delay(250);
  tone(buzzerPin, 349, 300);
  delay(250);
  tone(buzzerPin, 392, 600);
  
  delay(650);  
  noTone(buzzerPin);
  delay(2000);
  clearAll();
}

void enterSleepMode() {
  lcd.clear();
  lcd.noBacklight();
  sleepMode = true;
}

void wakeUp() {
  sleepMode = false;
  lcd.backlight();
  showWelcomeScreen();
}

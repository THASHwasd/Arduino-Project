#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Keypad.h>

// Initialise the I2C LCD with the address 0x27 - refer to your LCD address if this doesn't work
LiquidCrystal_I2C lcd(0x27, 16, 2); 

// Keypad setup
const byte ROWS = 4;
const byte COLS = 4;
char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte rowPins[ROWS] = {6, 7, 8, 9};         // pin connections
byte colPins[COLS] = {A0, A1, A2, A3};    // pin connections
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

// Car park data
String carparks[] = {"enfield", "walthamstow", "greenpark", "romford", "tooting",                // theese 5 (rate @ 1)
                     "wimbledon", "westminster", "chingford", "bradford", "hornchurch"};        // theese 5 (rate @ 2.5)
float carpark_rates[] = {1.0, 1.0, 1.0, 1.0, 1.0, 2.5, 2.5, 2.5, 2.5, 2.5}; // Rates for each car park
float vehicle_multiplier = 1.0;
int hours = 0;
float carpark_rate = 0.0;

// Variables for admin access
const String adminCode = "CAB86331"; // Edit "CAB86331" to change password
String enteredCode = "";
int loopCount = 0; // To count the number of loops
float totalRevenue = 0.0; // To track revenue across all loops
const int buzzerPin = 10; // Pin for the buzzer

// Function to calculate cost
float calculateCost(int hours, float vehicleMultiplier, float carparkRate) {
  return round((hours * vehicleMultiplier + carparkRate) * 100.0) / 100.0;
}

void setup() {
  lcd.init();           // Initialise the LCD
  lcd.backlight();      // Turn on the backlight
  pinMode(buzzerPin, OUTPUT); // Set buzzer pin as output
  showWelcomeMessage(); // Show welcome message on startup
}

void loop() {
  // Show the welcome message at the start of each loop
  showWelcomeMessage();
  
  // Step 1: Ask for hours
  lcd.clear();
  lcd.print("Enter hours: ");
  lcd.setCursor(3, 1);
  hours = getNumber(); 
  if (hours < 0) { // If hours are invalid
    lcd.print("Invalid hours");
    delay(2000); // Give the user time to see the message
    return; // Exit the loop and start again
  }
  delay(500); // Delay after valid input

  // Step 2: Ask for vehicle type
  lcd.clear();
  lcd.print("Electric vehicle? ");
  lcd.setCursor(0, 1);
  lcd.print("* = Yes  # = No");
  char vehicleType = getCharacter(); // Get vehicle type input

  // Set the vehicle multiplier based on input
  vehicle_multiplier = (vehicleType == '*') ? 0.8 : 1.2;     // EV cars cheaper rate

  delay(500); // Delay to allow user to see the choice

  // Step 3: Select carpark
  lcd.clear();
  lcd.print("Enter carpark #: ");
  lcd.setCursor(3, 1);
  int carparkIndex = getCarparkNumber(); // Get the selected carpark number

  if (carparkIndex >= 0 && carparkIndex < 10) {
    carpark_rate = carpark_rates[carparkIndex];  
    lcd.clear();
    lcd.print("Selected Carpark:");
    lcd.setCursor(0, 1);
    lcd.print(carparks[carparkIndex]);
    delay(2000); // Delay to show the selected car park
  } else {
    lcd.clear();
    lcd.print("Invalid selection");
    delay(2000); // Show error for invalid selection
    return; // Exit to start again
  }

  // Step 4: Calculate and display cost
  float totalCost = calculateCost(hours, vehicle_multiplier, carpark_rate);
  lcd.clear();
  lcd.print("Pay: £");
  lcd.print(totalCost, 2); // Display total cost
  lcd.setCursor(0, 1);
  lcd.print(" ");      // optional add of second line of text e.g ("to admin")
  totalRevenue += totalCost; // Accumulate revenue for admin display
  delay(5000); // Give user time to see the cost

  //  Sound a buzzer to indicate completion of each loop
  tone(buzzerPin, 1000, 200); // Short beep
  delay(200); // Brief pause
  noTone(buzzerPin); // Stop tone

  // Increment loop count for admin access
  loopCount++;

  // Step 5: Request Admin code - Only show every 3 loops
  if (loopCount % 3 == 0) {  // Check if loopCount is a multiple of 3 - using the mod function
    lcd.clear();
    lcd.print("Enter Admin Code:");
    lcd.setCursor(0,1);
    lcd.print("Press * to Bypass");  // to continue the code as normal without accessing admin page
    enteredCode = getAdminCode(); // Get admin code from keypad

    if (enteredCode == adminCode) {
      lcd.clear();
      lcd.print("Clients: ");
      lcd.print(loopCount); // Display the total loops (clients)
      lcd.setCursor(0,1);
      lcd.print("Rev: £");
      lcd.print(totalRevenue, 2); // Display total accumulated revenue
      tone(buzzerPin, 1000, 500); // Sound the buzzer for 0.5s (500ms) upon successful entry
      delay(500); // Pause for buzzer sound
      noTone(buzzerPin); // Stop tone
      delay(7000); // Delay 7s (7000ms) to show loop count (clients) and revenue
    }
  }
}

// Function to show the welcome message
void showWelcomeMessage() {
  lcd.clear();
  lcd.print("   Welcome to   ");   // spaces to center on the 16x2 lcd
  lcd.setCursor(0, 1);
  lcd.print(" Smart Car Park ");  // spaces to center on the 16x2 lcd
  waitForKeyPress(); // Wait for user to press a key to continue
}

// Function to wait for a key press
void waitForKeyPress() {
  while (!keypad.getKey()) {
    // Do nothing, just wait for a key press
  }
  tone(buzzerPin, 500, 100); // Short beep for key press confirmation
  delay(100); // Pause before continuing
}

// Function to get a multi-digit number for hours
int getNumber() {
  int num = 0;
  char key;
  while (true) {
    key = keypad.getKey();
    if (key) {
      tone(buzzerPin, 500, 100); // Short beep for key press
      if (key == '#') break;  // Allow the user to finish input by pressing #
      if (key >= '0' && key <= '9') {
        num = num * 10 + (key - '0'); 
        lcd.print(key); 
      }
    }
  }
  return num;
}

// Function to get a single character for electric vehicle question
char getCharacter() {
  char key;
  while (true) {
    key = keypad.getKey();
    if (key) {
      tone(buzzerPin, 500, 100); // Short beep for key press
      lcd.print(key);
      delay(1000);
      return key;
    }
  }
}

// Function to get a single digit car park number - prevent errors
int getCarparkNumber() {
  char key;
  while (true) {
    key = keypad.getKey();
    if (key && key >= '0' && key <= '9') {
      tone(buzzerPin, 500, 100); // Short beep for key press
      lcd.print(key); 
      delay(1000);
      return key - '0';  // casting char to int (e.g., '1' to 1)
    }
  }
}

// Function to get admin code
String getAdminCode() {
  String code = "";
  char key;
  while (true) {
    key = keypad.getKey();
    if (key) {
      tone(buzzerPin, 500, 100); // Short beep for key press
      if (key == '*') break; // End input on '*'
      code += key; // Append key to code
      lcd.print(key); // !! Will not be able be seen on 16x2 lcd screen !!
    }
  }
  return code; // Return the entered admin code
}

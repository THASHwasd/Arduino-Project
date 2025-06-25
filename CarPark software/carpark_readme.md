# Car Park Terminal

An Arduino-based automated car park payment terminal with LCD display, keypad input, and admin functionality.

## Features

- **Multi-location Support**: 10 different car park locations with varying rates
- **Vehicle Type Pricing**: Discounted rates for electric vehicles (20% discount) vs regular vehicles (20% surcharge)
- **Interactive LCD Interface**: 16x2 I2C LCD display for user interaction
- **Admin Dashboard**: Revenue tracking and client statistics
- **Audio Feedback**: Buzzer confirmation for all user inputs
- **Robust Input Validation**: Prevents invalid entries and system errors

## Hardware Requirements

### Components
- Arduino Uno (or compatible)
- 16x2 I2C LCD Display
- 4x4 Matrix Keypad
- Buzzer
- Jumper wires and breadboard

### Pin Connections

| Component | Arduino Pin |
|-----------|-------------|
| LCD SDA   | A4 (I2C)    |
| LCD SCL   | A5 (I2C)    |
| Keypad Rows | 6, 7, 8, 9 |
| Keypad Cols | A0, A1, A2, A3 |
| Buzzer    | 10          |

## Software Dependencies

Install these libraries through the Arduino IDE Library Manager:

```
Wire.h (built-in)
LiquidCrystal_I2C
Keypad
```

## Configuration

### Car Park Locations & Rates

The system includes 10 pre-configured locations:

**Tier 1 (£1.00 base rate):**
- Enfield
- Walthamstow  
- Green Park
- Romford
- Tooting

**Tier 2 (£2.50 base rate):**
- Wimbledon
- Westminster
- Chingford
- Bradford
- Hornchurch

### Pricing Structure

**Base Cost Calculation:**
```
Total Cost = (Hours × Vehicle Multiplier) + Car Park Rate
```

**Vehicle Multipliers:**
- Electric Vehicle: 0.8 (20% discount)
- Regular Vehicle: 1.2 (20% surcharge)

### Admin Configuration

```cpp
const String adminCode = "CAB86331"; // Change this to set your admin password
```

**Admin Access:**
- Prompted every 3rd transaction
- Displays total clients served and revenue generated
- Bypass option available with '*' key

## Usage Instructions

### For Customers

1. **Start**: Press any key at the welcome screen
2. **Enter Hours**: Input parking duration, press '#' to confirm
3. **Vehicle Type**: 
   - Press '*' for Electric Vehicle
   - Press '#' for Regular Vehicle
4. **Select Location**: Enter car park number (0-9)
5. **Payment**: View calculated cost on screen

### For Administrators

1. **Access**: Admin prompt appears every 3rd transaction
2. **Login**: Enter admin code or press '*' to bypass
3. **Dashboard**: View client count and total revenue
4. **Exit**: System returns to normal operation after 7 seconds

## Key Functions

### Core Functions

- `calculateCost()`: Computes parking fees based on hours, vehicle type, and location
- `getNumber()`: Handles multi-digit hour input with '#' termination
- `getCharacter()`: Captures single character for vehicle type selection
- `getCarparkNumber()`: Validates and returns car park selection (0-9 only)
- `getAdminCode()`: Securely captures admin authentication

### User Interface

- `showWelcomeMessage()`: Displays startup screen
- `waitForKeyPress()`: Pauses system until user interaction
- Audio feedback on all key presses and transactions

## Customization

### Adding New Locations

1. **Update Arrays**: Add new locations to `carparks[]` and corresponding rates to `carpark_rates[]`
2. **Modify Validation**: Update `getCarparkNumber()` function range check
3. **Adjust Display**: Consider scrolling text for longer location names

### Changing Pricing

```cpp
// Modify vehicle multipliers
vehicle_multiplier = (vehicleType == '*') ? 0.8 : 1.2;

// Update car park rates
float carpark_rates[] = {1.0, 1.0, 1.0, 1.0, 1.0, 2.5, 2.5, 2.5, 2.5, 2.5};
```

### LCD Address Configuration

If your LCD doesn't respond, try these common I2C addresses:
```cpp
LiquidCrystal_I2C lcd(0x27, 16, 2); // Most common
LiquidCrystal_I2C lcd(0x3F, 16, 2); // Alternative address
```

Use an I2C scanner sketch to find your LCD's address if needed.

## Troubleshooting

### Common Issues

**LCD Not Displaying:**
- Check I2C connections (SDA/SCL)
- Verify LCD address (try 0x3F if 0x27 doesn't work)
- Ensure proper power supply to LCD

**Keypad Not Responding:**
- Verify all row/column pin connections
- Check for loose connections on breadboard
- Test individual keys systematically

**Buzzer Not Working:**
- Confirm buzzer polarity (+ to pin 10, - to GND)
- Check if buzzer is active or passive type
- Verify pin 10 connection

**Admin Code Issues:**
- Remember: code entry is case-sensitive
- Use '*' to bypass if needed
- Check `adminCode` variable for correct password

## System Limitations

- **Input Display**: Admin code entry not visible on 16x2 display
- **Storage**: Revenue data resets on system restart (no persistent storage)
- **Concurrent Users**: Single-user system design
- **Payment Integration**: Display-only system (no actual payment processing)

## Future Enhancements

- **Persistent Storage**: Add EEPROM or SD card for data retention
- **Network Connectivity**: WiFi/Ethernet for remote monitoring
- **Receipt Printing**: Thermal printer integration
- **Payment Processing**: Card reader or mobile payment support
- **Larger Display**: 20x4 LCD for better admin interface

## License

This project is open source. Feel free to modify and distribute according to your needs.


**Note**: This system is designed for educational and demonstration purposes.

## Author

**Made by Thash Kunarajah**

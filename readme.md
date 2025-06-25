# Arduino Multi-Purpose Hardware Platform

**Author:** Thash Kunarajah

A simple, **beginner-friendly Arduino project** that demonstrates versatile hardware usage with multiple interchangeable code examples. One hardware setup, multiple applications!

## 🎯 Project Overview

This project showcases how the same Arduino hardware setup can be programmed for different purposes by simply flashing different code. Perfect for beginners learning Arduino fundamentals and exploring various project possibilities.

## 📂 Code Organization

Each application has its own dedicated folder in this repository:

- **`/calculator/`** - Contains `calculator.ino` and related files for the calculator application
- **`/carpark software/`** - Contains `car-park-machine.ino` and related files for the parking machine
- **`/soundboard/`** - Will contain `soundboard.ino` when completed (coming soon)

Simply navigate to the desired folder and open the `.ino` file in Arduino IDE to flash that specific application to your hardware. All applications use the same wiring setup!

## 🛠️ Hardware Components

### Required Components
- **Arduino Microcontroller** (Uno/Nano/compatible)
- **16x2 LCD Display** (with I2C backpack recommended)
- **4x4 Matrix Keypad** 
- **Buzzer** (Active or Passive)
- **Breadboard** and **Jumper Wires**
- **Power Supply** (USB or external)

### Optional Components
- **Potentiometer** (for LCD contrast adjustment if not using I2C)
- **Resistors** (as needed for circuit protection)

## 📱 Available Applications

### 1. 🅿️ **Car Park Ticket Machine**
A realistic parking ticket dispenser simulation with:
- Welcome screen and time selection
- Ticket pricing calculation
- Payment processing simulation
- Ticket printing confirmation
- Sound effects for user feedback

### 2. 🧮 **Calculator**
A functional calculator featuring:
- Basic arithmetic operations (+, -, ×, ÷)
- Multi-digit number input
- Clear and result display
- Error handling for invalid operations
- Beep feedback for button presses

### 3. 🎵 **Custom Soundboard** *(requires mod)*
Interactive sound effects board with:
- Multiple sound effect slots
- Customizable button mappings
- Volume control options
- Sound sequence programming

## 🔌 Wiring Diagram

**Detailed wiring instructions available in:** `Arduino Car Park Hardware Setup.pdf`

**Visual reference photo available:** `Arduino Car Park Hardware Visual.png`

### Quick Reference:
```
Arduino Uno Connections:
├── 16x2 LCD Display
│   ├── VCC  → 5V
│   ├── GND  → GND
│   ├── SDA  → A4 (if using I2C)
│   └── SCL  → A5 (if using I2C)
├── 4x4 Keypad
│   ├── Row pins    → Digital pins 2, 3, 4, 5
│   └── Column pins → Digital pins 6, 7, 8, 9
└── Buzzer
    ├── Positive → Digital pin 10
    └── Negative → GND
```

*Note: Pin assignments may vary depending on your specific code implementation. Always refer to the setup PDF for exact wiring details.*

## 🚀 Getting Started

### Prerequisites
- **Arduino IDE** (latest version recommended)
- **Required Libraries:**
  - `LiquidCrystal` or `LiquidCrystal_I2C` (for LCD)
  - `Keypad` library (for 4x4 keypad)

### Installation & Setup

1. **Clone this repository:**
```bash
git clone https://github.com/yourusername/arduino-multi-purpose-platform.git
cd arduino-multi-purpose-platform
```

2. **Install required libraries:**
   - Open Arduino IDE
   - Go to **Sketch → Include Library → Manage Libraries**
   - Search and install: `Keypad`, `LiquidCrystal_I2C`

3. **Wire your components** according to the wiring diagram

4. **Choose and upload code:**
   - Open desired `.ino` file in Arduino IDE
   - Select your Arduino board and port
   - Click **Upload**

## 🎮 Usage Examples

### Car Park Machine
```
Welcome to SmartPark!
Press * to start
> Duration: 2 hours
> Cost: £4.00
> Insert coins: £4.00
> Printing ticket...
> Thank you!
```

### Calculator
```
Arduino Calculator
> 123 + 456 =
> Result: 579
> Press C to clear
```

## 🔧 Customization Options

### Easy Modifications:
- **Change pin assignments** in the code header
- **Modify LCD messages** for different languages
- **Adjust buzzer tones** and timing
- **Add new calculator functions**
- **Create custom parking rates**

### Advanced Modifications:
- **Add RTC module** for real-time clock functionality
- **Include SD card** for data logging
- **Add LED strips** for visual feedback
- **Implement wireless connectivity** (WiFi/Bluetooth)

## 🐛 Troubleshooting

### Common Issues:
- **LCD not displaying:** Check wiring and I2C address
- **Keypad not responding:** Verify pin connections
- **No sound from buzzer:** Check polarity and pin assignment
- **Compilation errors:** Ensure all required libraries are installed

### Tips:
- Use **Serial Monitor** for debugging (9600 baud rate)
- Double-check **wiring connections** before powering on
- Ensure **adequate power supply** for all components

## 🎯 Learning Objectives

This project helps you learn:
- **Basic Arduino programming** concepts
- **LCD display** control and formatting
- **Keypad input** handling and debouncing
- **Buzzer control** and sound generation
- **State machine** programming
- **User interface** design principles
- **Hardware-software** integration

## 🚀 Future Enhancements

### Planned Features:
- **Custom Soundboard** implementation - [X]RELEASED 25/06/25[X]
- **Menu system** for switching between applications (mock lower powered mimic of older phones)
- **EEPROM storage** for settings persistence
- **Real-time clock** integration (digital Clock)
- **Wireless connectivity** options e.g. to control smarthome appliances via home assistant

### Community Contributions Welcome:
- New application ideas
- Code optimizations
- Additional hardware integrations
- Documentation improvements

## 📚 Educational Value

Perfect for:
- **Arduino beginners** learning hardware interfacing
- **Students** studying embedded systems
- **Experimental Makers** exploring multi-purpose hardware designs
- **Hobbyists** building foundational projects

## 🤝 Contributing

Feel free to contribute by:
- Adding new applications
- Improving existing code
- Creating better documentation
- Sharing photos of your builds
- Reporting bugs or issues

## 📄 License

This project is open source and available under the MIT License. Feel free to use, modify, and distribute according to your needs.

## 🙏 Acknowledgments

- Arduino community for excellent documentation
- Library authors for making development easier
- Fellow makers for inspiration and feedback

## 📞 Support

If you encounter issues or have questions:
- Check the **troubleshooting section** above
- Review individual project README files
- Share your builds and modifications

---

**Remember:** This is designed as a learning platform - experiment, modify, and make it your own! 🚀

### 🏷️ Tags
`#Arduino` `#BeginnerFriendly` `#LCD` `#Keypad` `#Buzzer` `#MultiPurpose` `#Learning` `#Electronics` `#DIY` `#Embedded`

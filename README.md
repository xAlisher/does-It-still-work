# DoesItStillWork

**DoesItStillWork** is an Arduino-based project for monitoring the success rate of power cycles for devices with an LCD screen or power LED. It logs and displays the results, making it easier to evaluate the reliability of your power button 🤣

## Features
- Tracks total power cycles, successful attempts, and failures.
- Logs data to an SD card for later analysis.
- Displays real-time results on an I2C-connected LCD screen.
- Easy-to-build and customizable.

## Requirements

### **Hardware**
- Arduino MKR WiFi 1010 (or compatible board)
- Servo motor
- Phototransistor
- I2C LCD display
- MicroSD card module
- MicroSD card
- Resistors and jumper wires

### **Libraries**
Ensure these libraries are installed in your Arduino IDE:
1. [Servo](https://www.arduino.cc/reference/en/libraries/servo/)
2. [Wire](https://www.arduino.cc/reference/en/libraries/wire/)
3. [SPI](https://www.arduino.cc/reference/en/libraries/spi/)
4. [LiquidCrystal_I2C](https://github.com/johnrickman/LiquidCrystal_I2C)
5. [SD](https://www.arduino.cc/en/Reference/SD)

---

## Getting Started

### **Hardware Setup**
1. Connect the LCD display to the I2C pins on your Arduino.
   - `SDA` → `A4`
   - `SCL` → `A5`
2. Connect the phototransistor to the analog pin (`A1`) and ground.
3. Attach the servo motor to pin `9` and power it using `Vin`.
4. Connect the SD card module:
   - `MISO` → `Pin 12`
   - `MOSI` → `Pin 11`
   - `SCK` → `Pin 13`
   - `CS` → `Pin 10`
5. Insert the SD card and ensure it's formatted as FAT32.

### **Software Setup**
1. Clone the repository:
   ```bash
   git clone https://github.com/xAlisher/does-It-still-work.git
   ```
2. Open the `.ino` file in Arduino IDE.
3. Install the required libraries via Arduino's Library Manager.
4. Upload the code to your Arduino.

---

## How It Works

1. The servo motor toggles the power for the device being tested.
2. A phototransistor detects the power status via the device’s LCD backlight or LED.
3. The results are logged to the SD card in the format:
   ```
   Cycle: <Cycle Number>, Success: <Success Count>, Failure: <Failure Count>
   ```
4. The LCD display shows real-time updates.

---

## Future Plans
- Stream real-time data to a webpage using the Arduino's WiFi capabilities.
- Add timestamping for each log entry.
- Create an online dashboard for visualizing statistics.


## License
This project is licensed under the MIT License. See the `LICENSE` file for details.

---

## Contributing
Contributions are welcome! Please open an issue or a pull request for any improvements or features you'd like to add.

---

## Acknowledgments
Special thanks to the Arduino community for libraries and resources that made this project possible.
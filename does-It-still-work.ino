#include <Servo.h>                //Library for servo motor
#include <Wire.h>                 //Library for I2C hardware
#include <LiquidCrystal_I2C.h>    //Library for LCD
#include <SD.h>                   //Library for SD reader
#include <SPI.h>                  //LIbrary for Serial Peripheral Interface

// Initialize the LCD with I2C address 0x27
LiquidCrystal_I2C lcd(0x27, 16, 2);

Servo myServo;            
int cycleCount = 0;       // Total cycle count
int success = 0;          // Successful power ON
int failure = 0;          // Failure to power ON
const int photoPin = A1;  // Analog pin connected to the phototransistor
int lightValueOn = 0;     // Amount of light from LCD when ON
int lightValueOff = 0;    // Amount of light from LCD when OFF

const int chipSelect = 10; // SD card chip select pin
File logFile;              // File object for writing logs

void setup() {
  myServo.attach(9);
  Serial.begin(9600);

  // Initialize the I2C LCD
  lcd.init();
  lcd.backlight(); // Turn on the backlight
  lcd.print("Initializing...");
  delay(2000);
  lcd.clear();

  // Initialize the SD card
  lcd.print("Init SD...");
  if (!SD.begin(chipSelect)) {
    lcd.clear();
    lcd.print("SD Init Fail");
    Serial.println("SD card initialization failed!");
    while (true); // Halt execution if SD card fails
  }
  lcd.clear();
  lcd.print("SD Ready");
  Serial.println("SD card initialized.");
  delay(1000);
  lcd.clear();
}

void loop() {
  // Move servo to ON position and wait for stabilization
  myServo.write(50);
  delay(1000);
  lightValueOn = analogRead(photoPin);
  Serial.print("On: ");
  Serial.println(lightValueOn);

  // Move servo to OFF position and wait for stabilization
  myServo.write(120);
  delay(1000);
  lightValueOff = analogRead(photoPin);
  Serial.print("Off: ");
  Serial.println(lightValueOff);

  // Compare light values and determine success or failure
  Serial.print("Comparison: ");
  Serial.print(lightValueOn);
  Serial.print(" > ");
  Serial.print(lightValueOff);

  if (lightValueOn > lightValueOff) {
    success++;
    Serial.println(" -> Success");
  } else {
    failure++;
    Serial.println(" -> Failure");
  }

  // Increment total cycle count
  cycleCount++;

  // Update Serial Monitor
  Serial.print("T: ");
  Serial.print(cycleCount);
  Serial.print("  S: ");
  Serial.print(success);
  Serial.print("  F: ");
  Serial.println(failure);

  // Update LCD
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Total: ");
  lcd.print(cycleCount);
  lcd.setCursor(0, 1);
  lcd.print("S: ");
  lcd.print(success);
  lcd.print("F: ");
  lcd.print(failure);

  // Write log data to SD card
  logFile = SD.open("log.txt", FILE_WRITE);
  if (logFile) {
    logFile.print("Cycle: ");
    logFile.print(cycleCount);
    logFile.print(", Light ON: ");
    logFile.print(lightValueOn);
    logFile.print(", Light OFF: ");
    logFile.print(lightValueOff);
    logFile.print(", Success: ");
    logFile.print(success);
    logFile.print(", Failure: ");
    logFile.println(failure);
    logFile.close();
    Serial.println("Log written to SD card.");
  } else {
    Serial.println("Failed to open log file.");
  }

  delay(1000); // Wait before next cycle
}

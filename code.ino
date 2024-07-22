#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DHT.h>
#include <Adafruit_BMP280.h>
#include <SPI.h>
#include <SD.h>

// Initialize the LCD display with I2C address 0x27
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Define the DHT sensor pin and type
#define DHTPIN 2
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

// Define the BMP280 sensor
Adafruit_BMP280 bmp;

// Define the MQ-135 sensor pin
#define MQ135_PIN A0

// Define SD card module pin
#define CS_PIN 10

void setup() {
  // Initialize Serial Monitor
  Serial.begin(9600);

  // Initialize LCD
  lcd.begin();
  lcd.backlight();

  // Initialize DHT sensor
  dht.begin();

  // Initialize BMP280 sensor
  if (!bmp.begin()) {
    Serial.println("Could not find a valid BMP280 sensor, check wiring!");
    while (1);
  }

  // Initialize SD card
  if (!SD.begin(CS_PIN)) {
    Serial.println("Initialization of SD card failed!");
    return;
  }
  Serial.println("SD card initialized.");

  // Create a file to save data
  File dataFile = SD.open("datalog.txt", FILE_WRITE);
  if (dataFile) {
    dataFile.println("Temperature, Humidity, Pressure, Air Quality");
    dataFile.close();
  }
}

void loop() {
  // Read temperature and humidity from DHT22
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();

  // Read pressure from BMP280
  float pressure = bmp.readPressure() / 100.0F;

  // Read air quality from MQ-135
  int airQuality = analogRead(MQ135_PIN);

  // Display data on LCD
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("T:");
  lcd.print(temperature);
  lcd.print(" H:");
  lcd.print(humidity);

  lcd.setCursor(0, 1);
  lcd.print("P:");
  lcd.print(pressure);
  lcd.print(" AQ:");
  lcd.print(airQuality);

  // Print data to Serial Monitor
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.print(" C, Humidity: ");
  Serial.print(humidity);
  Serial.print(" %, Pressure: ");
  Serial.print(pressure);
  Serial.print(" hPa, Air Quality: ");
  Serial.println(airQuality);

  // Save data to SD card
  File dataFile = SD.open("datalog.txt", FILE_WRITE);
  if (dataFile) {
    dataFile.print(temperature);
    dataFile.print(", ");
    dataFile.print(humidity);
    dataFile.print(", ");
    dataFile.print(pressure);
    dataFile.print(", ");
    dataFile.println(airQuality);
    dataFile.close();
  }

  // Wait before repeating
  delay(2000);
}

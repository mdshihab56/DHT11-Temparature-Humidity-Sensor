#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DHT.h>

// Define DHT11 settings
#define DHTPIN 2 // DHT11 data pin connected to digital pin 2
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

// Define LCD settings
LiquidCrystal_I2C lcd(0x27, 16, 2); // Adjust the I2C address if needed

// Define Buzzer pin
#define BUZZER 8

// Variable to track the error state
bool sensorError = false;

void setup() {
  // Initialize LCD, DHT sensor, and buzzer
  pinMode(BUZZER, OUTPUT);
  lcd.init();
  lcd.backlight(); // Turn on the backlight
  dht.begin();

  // Buzzer: 2 short beeps on power-on
  shortBeep(2);

  // Display "Initializing..." with blinking dots
  for (int i = 0; i < 10; i++) { // Loop for ~2 seconds (adjust as needed)
    lcd.setCursor(0, 0);
    lcd.print("INITIALIZING");
    for (int j = 0; j <= i % 4; j++) {
      lcd.print(".");
    }
    lcd.setCursor(0, 1);
    lcd.print("ATMEGA328P-U MCU");
    delay(200); // Delay to simulate blinking effect
    lcd.clear();
  }

  // Buzzer: 3 short beeps after initialization
  shortBeep(3);

  lcd.clear();
}

void loop() {
  // Read temperature and humidity
  float tempC = dht.readTemperature();
  float tempF = dht.readTemperature(true);
  float humidity = dht.readHumidity();

  // Check if reading failed
  if (isnan(tempC) || isnan(tempF) || isnan(humidity)) {
    if (!sensorError) { // Display error message only once
      lcd.clear();
      lcd.print("DHT11 INFO ERROR!");
      lcd.setCursor(0, 1);
      lcd.print("INSPECT MOD/PINs");
      sensorError = true; // Set error flag
    }

    // Continuous beep in case of sensor error
    continuousBeep();
    return;
  }

  // If no error, stop the beep and update the LCD
  noTone(BUZZER);
  if (sensorError) { // Clear error flag and reset display
    sensorError = false;
    lcd.clear();
  }

  // Determine weather status
  String weatherStatus = getWeatherStatus(tempC, humidity);

  // Display Temperature and Humidity on LCD
  lcd.setCursor(0, 0);
  lcd.print("TEMP:");
  lcd.print(tempC, 1); // 1 decimal place for precision
  lcd.print("C|");
  lcd.print(tempF, 1);
  lcd.print("F");

  lcd.setCursor(0, 1);
  lcd.print("HUMI:");
  lcd.print(humidity, 1);
  lcd.print("%|");
  lcd.print(weatherStatus);

  delay(2000); // Update every 2 seconds
}

// Function to determine weather status
String getWeatherStatus(float tempC, float humidity) {
  if (tempC > 30 && humidity > 70) return "HOT";
  if (tempC > 20 && tempC <= 30 && humidity > 50) return "MILD";
  if (tempC <= 20 && humidity > 30) return "AMBT";
  if (tempC <= 10 || humidity < 30) return "COLD";
  return "NORM";
}

// Function to make short beeps
void shortBeep(int count) {
  for (int i = 0; i < count; i++) {
    tone(BUZZER, 2000); // Generate sound at 1kHz
    delay(50); // Beep duration
    noTone(BUZZER); // Stop sound
    delay(50); // Pause between beeps
  }
}

// Function for continuous beep
void continuousBeep() {
  static unsigned long lastBeepTime = 0;
  static bool buzzerState = false;

  if (millis() - lastBeepTime >= 500) { // Toggle beep every 500ms
    buzzerState = !buzzerState;
    if (buzzerState) {
      tone(BUZZER, 2000);
    } else {
      noTone(BUZZER);
    }
    lastBeepTime = millis();
  }
}

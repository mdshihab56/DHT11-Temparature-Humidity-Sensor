# DHT11-Temparature-Humidity-Sensor
This Arduino code reads temperature and humidity data from a DHT11 sensor and displays it on a 16x2 LCD screen using the LiquidCrystal_I2C library. 
Additionally, a buzzer module is used to provide audible feedback, particularly in cases where sensor readings fail.

The LCD screen turns on and displays an initializing message with blinking dots.
The buzzer beeps twice at startup.
The DHT11 sensor begins operation.

### Reading Sensor Data:
1. The program continuously reads temperature and humidity values.
2. If the sensor fails to provide valid readings, an error message appears on the LCD, and the buzzer starts beeping continuously.
3. If readings are valid, the buzzer stops, and the LCD updates with:
i. Temperature in Celsius and Fahrenheit
ii. Humidity percentage
iii. Weather status (HOT, MILD, AMBT, COLD, NORM)
iv. The display updates every 2 seconds.

### Weather Classification Logic:
Based on temperature and humidity levels, the system categorizes the environment into different weather statuses.
Buzzer Feedback Mechanism:
1. Short beeps during initialization.
2. Continuous beep if the DHT11 sensor fails.
3. Stop beep when valid data is retrieved.

### Pin Connections

Component	Arduino UNO Pin
DHT11 Sensor	Data pin → 2 | 
LCD Display	I2C communication → SDA (A4), SCL (A5) | 
Buzzer Module	Signal pin → 8

-----------------------------------------------------------------------------------------------------------------------------------
This project is great for real-time environmental monitoring, and with your expertise in IoT applications and environmental systems.

#include <Wire.h>                  // Include library for I2C communication
#include <LiquidCrystal_I2C.h>     // Include library for controlling I2C LCD displays
#include <DHT.h>                   // Include library for DHT temperature and humidity sensor

// Define pin assignments for components
#define TRIG_PIN 9                 // Pin for triggering the ultrasonic sensor
#define ECHO_PIN 10                // Pin for receiving the echo signal from the ultrasonic sensor
#define BUZZER_PIN 8               // Pin for controlling the buzzer
#define LED_PIN 5                  // Pin for controlling the LED
#define DHT_PIN 7                  // Pin connected to the DHT sensor

// Initialize the DHT sensor (DHT11 model)
DHT dht(DHT_PIN, DHT11);

// Initialize the LCD object with I2C address and display size
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Variables for ultrasonic sensor readings
long duration;                     // Variable to store the time it takes for the echo to return
int distance;                      // Variable to store the calculated distance in centimeters

void setup() {
  pinMode(TRIG_PIN, OUTPUT);       // Set the ultrasonic trigger pin as output
  pinMode(ECHO_PIN, INPUT);        // Set the ultrasonic echo pin as input
  pinMode(BUZZER_PIN, OUTPUT);     // Set the buzzer pin as output
  pinMode(LED_PIN, OUTPUT);        // Set the LED pin as output

  // Initialize the DHT sensor
  dht.begin();

  // Initialize the LCD display
  lcd.begin(16, 2);                // Specify the LCD dimensions (16 columns x 2 rows)
  lcd.backlight();                 // Turn on the LCD backlight for visibility
}

void loop() {
  // Configuration 1: Measure distance using the ultrasonic sensor
  digitalWrite(TRIG_PIN, LOW);     // Ensure the trigger pin starts LOW
  delayMicroseconds(2);            // Wait for 2 microseconds
  
  digitalWrite(TRIG_PIN, HIGH);    // Send a HIGH pulse to trigger the ultrasonic signal
  delayMicroseconds(10);           // Keep the trigger HIGH for 10 microseconds
  digitalWrite(TRIG_PIN, LOW);     // Set the trigger pin back to LOW

  // Measure the time of the echo signal
  duration = pulseIn(ECHO_PIN, HIGH); // Capture the duration of the HIGH echo pulse
  distance = duration * 0.034 / 2;    // Convert duration to distance in centimeters

  // Configuration 2: Read temperature and humidity from the DHT11 sensor
  float temp = dht.readTemperature(); // Get temperature in Celsius
  float humidity = dht.readHumidity(); // Get humidity as a percentage

  // Configuration 3: Display temperature and humidity on the LCD
  lcd.clear();                     // Clear the previous content on the LCD
  lcd.setCursor(0, 0);             // Move the cursor to the first row
  lcd.print("Temp: " + String(temp) + "C"); // Display the temperature
  lcd.setCursor(0, 1);             // Move the cursor to the second row
  lcd.print("Humidity: " + String(humidity) + "%"); // Display the humidity

  // Configuration 4: Check if an object is detected within range
  if (distance < 100) {            // If distance is less than 100 cm
    digitalWrite(LED_PIN, HIGH);   // Turn on the LED
    digitalWrite(BUZZER_PIN, HIGH); // Activate the buzzer

    // Display detection message on the LCD
    lcd.setCursor(0, 0);           // Move cursor to the first row
    lcd.print("Person Detected");  // Display detection message
    lcd.setCursor(0, 1);           // Move cursor to the second row
    lcd.print("Infront The Door"); // Display location message
    
    delay(2000);                   // Keep the buzzer and LED on for 2 seconds

    // Turn off the LED and buzzer after 2 seconds
    digitalWrite(LED_PIN, LOW);
    digitalWrite(BUZZER_PIN, LOW);
  }

  delay(500);                      // Short delay before the next reading
}
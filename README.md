# Smart Door Alarming System (Distance Presence)

An Arduino project that detects when someone is standing in front of a door
and alerts you with a buzzer, an LED, and a message on an LCD screen. When
nobody is nearby, the display shows the current temperature and humidity.

## Features
- Detects a person within 100 cm using an HC-SR04 ultrasonic sensor
- Visual alert (LED) and audible alert (buzzer) for 2 seconds
- "Person Detected / Infront The Door" message on a 16x2 I2C LCD
- Live temperature and humidity readings from a DHT11 sensor
- Handles sensor errors and out-of-range readings

## Hardware
- Arduino Uno (or compatible)
- HC-SR04 ultrasonic sensor
- DHT11 temperature and humidity sensor
- 16x2 LCD with I2C backpack (address 0x27)
- Buzzer and LED (with a resistor)

## Pin Connections
| Component   | Arduino Pin |
|-------------|-------------|
| HC-SR04 TRIG | 9 |
| HC-SR04 ECHO | 10 |
| Buzzer       | 8 |
| LED          | 5 |
| DHT11 data   | 7 |
| LCD SDA/SCL  | A4 / A5 |

## Libraries
- LiquidCrystal_I2C
- DHT sensor library (Adafruit)
- Wire (built in)

# Fall Detection System

A real-time fall detection system designed for the elderly using an MPU6050 sensor, NodeMCU (ESP32), and the Blynk platform. This project aims to enhance safety by detecting falls and sending real-time alerts.

## Features

- **Real-Time Fall Detection**: Detects falls using accelerometer and gyroscope data from the MPU6050 sensor.
- **Alerts and Notifications**: Sends notifications via the Blynk app when a fall is detected.
- **Wearable Integration**: Designed to be integrated into a wearable jacket for ease of use.
- **Adjustable Sensitivity**: Sensitivity can be adjusted based on the user’s needs.

## Why is it Different
- **Pre-Impact Detection**: The system detects falls before the person makes contact with the ground, enabling potential integration with airbag mechanisms to proactively prevent injuries.

## Hardware Components

- **NodeMCU (ESP32)**
- **MPU6050 Sensor**
- **LED Indicator**
- **Buzzer**
- **Buck Converter**
- **Wearable Jacket (for final integration)**

## Software Libraries Used

- **Arduino Wire Library**: For I2C communication with MPU6050.
- **WiFi Library for ESP32**: To connect NodeMCU to a WiFi network.
- **Blynk Library**: For real-time app notifications and remote control.

## Setup Instructions

1. **Clone the repository**:
   ```bash
   git clone https://github.com/sujalarora19/Fall_Detection.git
2. **Open the project in Arduino IDE**:
   - Install the necessary libraries: `Wire.h`, `WiFi.h`, `BlynkSimpleEsp32.h`.

3. **Update WiFi credentials in the code**:
   ```cpp
   char ssid[] = "Your_SSID";
   char pass[] = "Your_PASSWORD";
4. **Upload the code to your NodeMCU (ESP32).**:

## How It Works

- The **MPU6050 sensor** collects acceleration and gyroscope data.
- The **NodeMCU** processes the data to detect a fall based on defined thresholds.
- If a fall is detected, an alert is sent to the **Blynk app**, and an **LED** and **buzzer** are activated.

## Important Notes

- Ensure the **MPU6050 sensor** is calibrated before using it.
- The sensitivity of the fall detection can be adjusted by changing the threshold values in the code.

## Libraries and Dependencies

Ensure you have the following libraries installed in your Arduino IDE:

- **Wire.h** - For I2C communication.
- **WiFi.h** - To connect to WiFi.
- **BlynkSimpleEsp32.h** - For Blynk platform integration.

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## Acknowledgments

- Thanks to the developers of all open-source libraries and tools used in this project.
- Special thanks to the Blynk community for their support and guidance.


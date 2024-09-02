# Fall Detection System

A real-time fall detection system designed for the elderly using an MPU6050 sensor, NodeMCU (ESP32), and the Blynk platform. This project aims to enhance safety by detecting falls and sending real-time alerts.

## Features

- **Real-Time Fall Detection**: Detects falls using accelerometer and gyroscope data from the MPU6050 sensor.
- **Alerts and Notifications**: Sends notifications via the Blynk app when a fall is detected.
- **Wearable Integration**: Designed to be integrated into a wearable jacket for ease of use.
- **Adjustable Sensitivity**: Sensitivity can be adjusted based on the user’s needs.

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

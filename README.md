# Smoke Detector Project with Arduino MKR WiFi 1010, Blynk, and Firebase

This project utilizes an Arduino MKR WiFi 1010 equipped with an MQ2 smoke sensor to detect the presence of smoke. When smoke levels exceed a predetermined threshold, the system triggers an alarm and sends data to both Blynk and Firebase for real-time monitoring and logging.

## Prerequisites

- Arduino IDE installed on your computer.
- Accounts on Blynk and Firebase platforms.
- Arduino MKR WiFi 1010 board.

## Hardware Required

- Arduino MKR WiFi 1010
- MQ2 smoke sensor
- Buzzer
- Red and Green LEDs
- Jumper wires
- Breadboard

## Software and Libraries

Ensure the following libraries are installed in your Arduino IDE:
- `WiFiNINA` for WiFi support on MKR WiFi 1010.
- **[MQ2 by labay11](https://github.com/labay11/MQ-2-sensor-library)** for interfacing with the smoke sensor.
- `Firebase_Arduino_WiFiNINA` for Firebase integration.
- `BlynkSimpleWiFiNINA` for Blynk connectivity.

### Installation
Install libraries through the Arduino IDE Library Manager:
1. Open the Arduino IDE, navigate to **Sketch > Include Library > Manage Libraries…**
2. Search for `WiFiNINA`, `Firebase_Arduino_WiFiNINA`, and `BlynkSimpleWiFiNINA` by name and install.
3. For the MQ2 sensor library, download it directly from GitHub using this link:
   - [MQ-2 sensor library on GitHub](https://github.com/labay11/MQ-2-sensor-library)
   - Follow the repository instructions to install the library into your Arduino IDE.

## Circuit Connections

1. **MQ2 Sensor:**
   - Connect the A0 pin of the MQ2 sensor to the A5 pin on the Arduino.
2. **Buzzer:**
   - Connect one pin to digital pin 10 and the other to GND on the Arduino.
3. **LEDs:**
   - Red LED: Positive leg to pin 12, negative leg to GND.
   - Green LED: Positive leg to pin 11, negative leg to GND.

## Configuration

### Blynk App Setup
1. Create a new project in the Blynk app.
2. Note the Auth Token sent via email.
3. Add Value Display widgets and link them to V5, V6, and V7 for displaying sensor readings and thresholds.

### Firebase Setup
1. Create a new project in Firebase.
2. Initiate a Realtime Database.
3. Configure the database rules for public or authenticated access based on your preference.

## Upload and Run

1. Replace placeholders in the Arduino sketch with your actual WiFi credentials, Blynk Auth Token, and Firebase project details.
2. Upload the sketch to your Arduino MKR WiFi 1010.
3. Power the Arduino and verify that all connections are correct.
4. Open the Blynk app on your mobile device to view real-time data.

## Monitoring

The system should now be up and running. Monitor smoke levels through the Blynk app and check data logs in the Firebase console. Adjust sensitivity and thresholds in your sketch as necessary based on testing and environmental conditions.

## Troubleshooting

- **WiFi Connection Issues:** Double-check your SSID and password.
- **Blynk Not Updating:** Verify that you are using the correct Auth Token.
- **Firebase Errors:** Check your Firebase URL and authentication credentials.

#include <WiFiNINA.h>
#include <MQ2.h>
#include "Firebase_Arduino_WiFiNINA.h" 
#define BLYNK_TEMPLATE_ID "" 
#define BLYNK_TEMPLATE_NAME ""  
#include <BlynkSimpleWiFiNINA.h>

// Wi-Fi network credentials
const char* ssid = "";
const char* password = "";

// Blynk Auth Token
char auth[] = "";

// Firebase Connection
const char* FIREBASE_HOST = "";
const char* FIREBASE_AUTH = "";

FirebaseData firebaseData;
String path = "/sensor-reading";

int redLed = 12;
int greenLed = 11;
int buzzer = 10;
int smokeA0 = A5;
float sensorThres = 0.5;

  
MQ2 mq2(smokeA0);

BlynkTimer timer;

void setup() {
  Serial.begin(9600);
  pinMode(redLed, OUTPUT);
  pinMode(greenLed, OUTPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(smokeA0, INPUT);

  mq2.begin();
  
  connectToWiFi();
  connectToBlynk(); 
  connectToFirebase();

}

void loop() {
  Blynk.run(); // Initiates Blynk
  timer.run(); // Initiates BlynkTimer

  static bool initialReadingRecorded = false;
    
  // Read the smoke sensor value
  //int analogSensor = analogRead(smokeA0);
  float smokeInPPM = mq2.readSmoke();
  Serial.print("Pin A0: ");
  Serial.println(smokeInPPM);
  Serial.println(sensorThres);


  if(!initialReadingRecorded) {
    sendInitialData(smokeInPPM);
    initialReadingRecorded = true;
  }

  sendSensorData(smokeInPPM);
  
  if (smokeInPPM > sensorThres) {
    digitalWrite(redLed, HIGH);
    digitalWrite(greenLed, LOW);
    activateBuzzer(buzzer, 1000); // Activate the buzzer
    Blynk.logEvent("smoke_detected", "Smoke is detected in your area!");
  } else {
    digitalWrite(redLed, LOW);
    digitalWrite(greenLed, HIGH);
    digitalWrite(buzzer, LOW); // Deactivate the buzzer
  }
}

void sendInitialData(float smokeInPPM) {
    Firebase.setFloat(firebaseData, path + "/initialReading", smokeInPPM);
    Firebase.setFloat(firebaseData, path + "/threshold", sensorThres);
    Blynk.virtualWrite(V7, smokeInPPM); 
    Blynk.virtualWrite(V6, sensorThres);
}

void sendSensorData(float smokeInPPM) {
  Firebase.setFloat(firebaseData, path + "/currentReading", smokeInPPM);
  Blynk.virtualWrite(V5, smokeInPPM); 
}

void activateBuzzer(int pin, int duration) {
  tone(pin, 1000);
  delay(duration);
  noTone(pin);
}

void connectToWiFi() {
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi connected.");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}

void connectToBlynk() {
  Blynk.begin(auth, ssid, password); // Initialize Blynk
  Serial.println("Connected to Blynk");
}

void connectToFirebase() {
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH, ssid, password);
  Firebase.reconnectWiFi(true);
  Serial.println("Connected to Firebase");

}

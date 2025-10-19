#include <Arduino.h>
#include <WiFi.h>
#include <WiFiUdp.h>
#include <ESP32Servo.h>

// ---- AP Mode Credentials ----
const char* apSSID = "ESP32_Robot";
const char* apPassword = "12345678";

// ---- UDP Settings ----
WiFiUDP Udp;
const unsigned int localUdpPort = 4210;  // Port to listen on
char incomingPacket[255];  // Buffer for incoming data

// ---- Motor & Servo Pins ----
#define IN1_PIN 12
#define IN2_PIN 14
#define IN3_PIN 26
#define IN4_PIN 27
#define SERVO_PIN 32

Servo myServo;

void setup() {
  Serial.begin(115200);
  delay(1000);

  // ---- Start Access Point ----
  WiFi.softAP(apSSID, apPassword);
  Serial.println("Access Point started!");
  Serial.print("Connect to Wi-Fi: ");
  Serial.println(apSSID);
  Serial.print("ESP32 AP IP address: ");
  Serial.println(WiFi.softAPIP());  // usually 192.168.4.1

  // ---- Start UDP ----
  Udp.begin(localUdpPort);
  Serial.printf("Listening for UDP on port %d\n", localUdpPort);

  // ---- Motor setup ----
  pinMode(IN1_PIN, OUTPUT);
  pinMode(IN2_PIN, OUTPUT);
  pinMode(IN3_PIN, OUTPUT);
  pinMode(IN4_PIN, OUTPUT);
  stopMotors();

  // ---- Servo setup ----
  myServo.setPeriodHertz(50);
  myServo.attach(SERVO_PIN, 500, 2400);
  myServo.write(90); // Neutral position
}

void loop() {
  int packetSize = Udp.parsePacket();
  if (packetSize) {
    int len = Udp.read(incomingPacket, 255);
    if (len > 0) incomingPacket[len] = '\0';
    char cmd = incomingPacket[0];

    Serial.print("UDP Command: ");
    Serial.println(cmd);

    switch (cmd) {
      case 'w': moveForward(); break;
      case 's': moveBackward(); break;
      case 'a': turnLeft(); break;
      case 'd': turnRight(); break;
      case 'x': stopMotors(); break;
      case 'j': myServo.write(45); break;
      case 'l': myServo.write(135); break;
      case 'k': myServo.write(90); break;
    }
  }
}

// ---- Movement Functions ----
void moveForward() {
  digitalWrite(IN1_PIN, HIGH);
  digitalWrite(IN2_PIN, LOW);
  digitalWrite(IN3_PIN, HIGH);
  digitalWrite(IN4_PIN, LOW);
}

void moveBackward() {
  digitalWrite(IN1_PIN, LOW);
  digitalWrite(IN2_PIN, HIGH);
  digitalWrite(IN3_PIN, LOW);
  digitalWrite(IN4_PIN, HIGH);
}

void turnLeft() {
  digitalWrite(IN1_PIN, LOW);
  digitalWrite(IN2_PIN, HIGH);
  digitalWrite(IN3_PIN, HIGH);
  digitalWrite(IN4_PIN, LOW);
}

void turnRight() {
  digitalWrite(IN1_PIN, HIGH);
  digitalWrite(IN2_PIN, LOW);
  digitalWrite(IN3_PIN, LOW);
  digitalWrite(IN4_PIN, HIGH);
}

void stopMotors() {
  digitalWrite(IN1_PIN, LOW);
  digitalWrite(IN2_PIN, LOW);
  digitalWrite(IN3_PIN, LOW);
  digitalWrite(IN4_PIN, LOW);
}

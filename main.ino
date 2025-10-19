#include <Arduino.h>
#include <ESP32Servo.h>

// Motor control pins
#define IN1_PIN 12
#define IN2_PIN 14
#define IN3_PIN 26
#define IN4_PIN 27

// Servo control pin
#define SERVO_PIN 32

// Create a Servo object
Servo myServo;

void setup() {
  Serial.begin(9600);
  // Set motor pins as outputs
  pinMode(IN1_PIN, OUTPUT);
  pinMode(IN2_PIN, OUTPUT);
  pinMode(IN3_PIN, OUTPUT);
  pinMode(IN4_PIN, OUTPUT);
  digitalWrite(IN1_PIN, LOW);
  digitalWrite(IN2_PIN, LOW);
  digitalWrite(IN3_PIN, LOW);
  digitalWrite(IN4_PIN, LOW);
  // Attach the servo to the pin
  myServo.setPeriodHertz(50);          // Optional: set frequency to 50Hz (standard for servos)
  myServo.attach(SERVO_PIN, 500, 2400); // Attach with min/max pulse width in microseconds

  myServo.write(45); // Center the servo
  stopMotors();      // Stop motors initially
}

void loop() {
  if (Serial.available()) {
    char cmd = Serial.read();
    Serial.print("Command: ");
    Serial.println(cmd);

    switch (cmd) {
      case 'w': moveForward(); break;
      case 's': moveBackward(); break;
      case 'a': turnLeft(); break;
      case 'd': turnRight(); break;
      case 'x': stopMotors(); break;

      case 'j': myServo.write(45); break;    // Turn servo left
      case 'l': myServo.write(135); break;   // Turn servo right
      case 'k': myServo.write(90); break;    // Center the servo
    }
  }
}

// Motor control functions
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

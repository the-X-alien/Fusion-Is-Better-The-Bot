// Motor A (L298N) pins - use PWM-capable GPIO for ENA
#include <BleKeyboard.h>
BleKeyboard bleKeyboard("ESP32 Keyboard", "Espressif", 100); 


#define IN2_PIN    14   // PWM-capable GPIO for Enable A
#define IN1_PIN    12
#define IN3_PIN    26
#define IN4_PIN    27

void setup() {
  pinMode(IN3_PIN, OUTPUT);
  pinMode(IN4_PIN, OUTPUT);
  pinMode(IN1_PIN, OUTPUT);
  pinMode(IN2_PIN, OUTPUT);

}

void loop() {
  digitalWrite(IN3_PIN, HIGH);
  digitalWrite(IN4_PIN, LOW);
  digitalWrite(IN1_PIN, LOW);
  digitalWrite(IN2_PIN, HIGH);

}

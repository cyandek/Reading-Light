#include <Arduino.h>
#define FASTLED_INTERNAL
#include <FastLED.h>
#define NUM_LEDS 84
#define LED_PIN 2
#define C_SWITCH_PIN 4
#define A_SWITCH_PIN 12
int offinterval = 0; // 2500;
int C_val, A_val = 0;
static unsigned long lastoff = millis();

CRGB leds[NUM_LEDS] = {0}; // Frame buffer for FastLED

void setup() {
  Serial.begin(115200);
  pinMode(LED_BUILTIN,OUTPUT);
  pinMode(LED_PIN, OUTPUT);
  pinMode(C_SWITCH_PIN, INPUT_PULLDOWN);
  pinMode(A_SWITCH_PIN, INPUT_PULLDOWN);

  // Add FastLED
  FastLED.addLeds<WS2812B, LED_PIN, GRB>(leds, NUM_LEDS);
  FastLED.clear();
  FastLED.clearData();
  FastLED.setBrightness(100);
  delay(2000);
}

void loop() {
  // put your main code here, to run repeatedly:
  if ((millis() - lastoff) > offinterval) {
    lastoff = millis();

    if (digitalRead(C_SWITCH_PIN) == LOW) {
        Serial.printf("Caleb Button Off\n");
        for (int i = 0; i < 42; i++) {
          leds[i] = CRGB(0, 0, 0);
        }
    }

    if (digitalRead(A_SWITCH_PIN) == LOW) {
        Serial.printf("Ana Button Off\n");
        for (int i = 43; i < 84; i++) {
          leds[i] = CRGB(0, 0, 0);
        }
    }

    if (digitalRead(C_SWITCH_PIN) == HIGH && digitalRead(A_SWITCH_PIN) == LOW) {
      Serial.printf("Caleb Button On\n");
      for (int i = 0; i < 42; i++) {
        leds[i] = CRGB(85, 35, 5);
      }
    }

        C_val = digitalRead(C_SWITCH_PIN);      // read the input pin
        Serial.printf("C_SWITCH: %d\n", C_val); // debug value

        if (digitalRead(A_SWITCH_PIN) == HIGH &&
            digitalRead(C_SWITCH_PIN) == LOW) {
            Serial.printf("Ana Button On\n");
            for (int i = 43; i < 84; i++) {
              leds[i] = CRGB(85, 35, 5);
            }
          }

        A_val = digitalRead(A_SWITCH_PIN);      // read the input pin
        Serial.printf("A_SWITCH: %d\n", A_val); // debug value

        if (digitalRead(C_SWITCH_PIN) == HIGH && digitalRead(A_SWITCH_PIN) == HIGH) {
            Serial.printf("Both Button On\n");
            for (int i = 0; i < 84; i++) {
              leds[i] = CRGB(130, 65, 0);
            }
        }
      }
      FastLED.show();
      delay(250);
}

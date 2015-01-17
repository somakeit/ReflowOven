#include <SPI.h>
#include "Adafruit_MAX31855.h"

#define CS   4
Adafruit_MAX31855 thermocouple(CS);

#define  HEATER_PIN  3

//heater PWM definitions
void heater_pwm_machine();
int heater_pwm = 80; //0 to 100, only 100 AC 0-crossings in 1s

unsigned long last_report = 0;

void setup() {
  Serial.begin(9600);
  
  // wait for MAX chip to stabilize
  delay(500);
  
  pinMode(HEATER_PIN, OUTPUT);
  digitalWrite(HEATER_PIN, LOW);
}

void loop() {
  if (millis() > last_report + 1000) {
    last_report = millis();
    double c = thermocouple.readCelsius();
    if (isnan(c)) {
      Serial.print("Something wrong with thermocouple!");
    } else {
      Serial.print("Temp: "); 
      Serial.print(c);
    }
    Serial.print("    Internal: ");
    Serial.println(thermocouple.readInternal());
  }
  
  heater_pwm_machine();
}

void heater_pwm_machine() {
  /* Call this frequnetly.
   State machine to do 1Hz PWM of the heater. */
  if ((millis() % 1000) / 10 < heater_pwm) {
    digitalWrite(HEATER_PIN, HIGH);
  } else {
    digitalWrite(HEATER_PIN, LOW);
  }
}

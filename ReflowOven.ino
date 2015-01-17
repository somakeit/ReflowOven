#include <SPI.h>
#include "Adafruit_MAX31855.h"

#define CS   4
Adafruit_MAX31855 thermocouple(CS);

#define  HEATER_PIN  3
#define  TARGET  0.0

void setup() {
  Serial.begin(9600);
  
  // wait for MAX chip to stabilize
  delay(500);
  
  pinMode(HEATER_PIN, OUTPUT);
  digitalWrite(HEATER_PIN, LOW);
}

void loop() {
   Serial.print("Internal Temp = ");
   Serial.println(thermocouple.readInternal());

   double c = thermocouple.readCelsius();
   if (isnan(c)) {
     Serial.println("Something wrong with thermocouple!");
     digitalWrite(HEATER_PIN, LOW);
   } else {
     Serial.print("C = "); 
     Serial.println(c);
     if (c < TARGET) {
       digitalWrite(HEATER_PIN, HIGH);
     } else {
       digitalWrite(HEATER_PIN, LOW);
     }
   }

   delay(1000);
}

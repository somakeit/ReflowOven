#include <PID_v1.h>
#include <SPI.h>
#include "Adafruit_MAX31855.h"

#define CS   4
Adafruit_MAX31855 thermocouple(CS);

#define  HEATER_PIN  3

//heater PWM definitions
void heater_pwm_machine();
double heater_pwm = 0;

//heater PID definitions
double kp = 2;
double ki = 5;
double kd = 1;
double target_temp = 20;
double input_temp = 0;

PID heater_pid(&input_temp, &heater_pwm, &target_temp, kp, ki, kd, DIRECT);

unsigned long last_report = 0;
unsigned long last_poll = 0; //TODO think about 50 day wrap
#define  POLL_RATE  1000

void setup() {
  Serial.begin(9600);
  
  // wait for MAX chip to stabilize
  delay(500);
  
  pinMode(HEATER_PIN, OUTPUT);
  digitalWrite(HEATER_PIN, LOW);
  
  heater_pid.SetOutputLimits(0, 100);
  heater_pid.SetMode(AUTOMATIC);
}

void loop() {
  if (millis() > last_poll + POLL_RATE) {
    input_temp = thermocouple.readCelsius();
    if (isnan(input_temp)) {
      heater_pwm = 0;
      Serial.println("ERROR WITH THERMOCOUPLE");
    } else {
      heater_pid.Compute();
    }
  }
    
  
  if (millis() > last_report + 1000) {
    last_report = millis();
    Serial.print("Temp: ");
    Serial.print(input_temp);
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

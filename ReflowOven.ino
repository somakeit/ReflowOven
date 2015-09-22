#include <PID_v1.h>
#include <SPI.h>
#include "Adafruit_MAX31855.h"
#include <LiquidCrystal.h>

#define MAX31855_DO   5
#define MAX31855_CS   4
#define MAX31855_CLK  3
Adafruit_MAX31855 thermocouple(MAX31855_CLK, MAX31855_CS, MAX31855_DO);

#define  HEATER_PIN  6

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

//LiquidCrystal lcd(7, 8, 9, 10, 11, 12);
LiquidCrystal lcd(7, 8, A2, A3, A4, A5);

void setup() {
  Serial.begin(9600);
  
  lcd.begin(16, 2);
  lcd.print("Reflow Oven");
  
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
    
    char lcd_text[33];
    sprintf(lcd_text, "T%03d/%03dC P%03d%%", (int) input_temp, (int) target_temp, (int) heater_pwm);
    
    lcd.setCursor(0, 0);
    lcd.print(lcd_text);
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

#ifndef BATTERY_H
#define BATTERY_H

#include "Arduino.h"

#define CURRENT_SENSOR_PIN A0
#define BATTERY_VOLTAGE_PIN A1

#define ANALOG_RANGE 1023.0
#define ANALOG_VOLTAGE 5.0
#define CURRENT_SENSOR_SENSITIVITY 0.066

float readCurrent(uint8_t pin);

#endif
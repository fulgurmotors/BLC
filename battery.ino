#include "battery.h"

//Valeur a calibrer
float currentSensorOffset = 2.5;

//Mersure un courant en ampere
float readCurrent(uint8_t pin){
    int measure = analogRead(pin);
    float voltage = measure * (ANALOG_VOLTAGE / ANALOG_RANGE);
    float current = (voltage - currentSensorOffset) / CURRENT_SENSOR_SENSITIVITY;
}
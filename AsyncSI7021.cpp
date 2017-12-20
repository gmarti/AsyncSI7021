#if ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include <Wire.h>
#include <AsyncSI7021.h>



AsyncSI7021::AsyncSI7021() {}

bool AsyncSI7021::begin() {
  Wire.begin();
  Wire.beginTransmission(SI7021_I2C_ADDRESS);

  return Wire.endTransmission() == 0;
}

float AsyncSI7021::syncHumidityMeasurement() {
  _write(SI7021_CMD_RH_HOLDMM, false);
  return getHumditityMeasurement();
}

float AsyncSI7021::syncTemperatureMeasurement() {
  _write(SI7021_CMD_TEMP_HOLDMM, false);
  return getTemperatureMeasurement();
}

bool AsyncSI7021::startHumidityMeasurement() {
  _write(SI7021_CMD_RH_NOHOLDMM);
}
bool AsyncSI7021::startTemperatureMeasurement() {
  _write(SI7021_CMD_TEMP_NOHOLDMM);
}

float AsyncSI7021::getHumditityMeasurement() {
  return _humidityConversion(_read16());
}
float AsyncSI7021::getTemperatureMeasurement() {
  return _temperatureConversion(_read16());
}

bool AsyncSI7021::isMeasurementReady() {
  Wire.beginTransmission(SI7021_I2C_ADDRESS);
  return Wire.endTransmission() != 2;
}

float AsyncSI7021::readTemperatureFromHumidityMeasurement() {
  _write(SI7021_CMD_TEMP_LASTRH, false);
  return _temperatureConversion(_read16());
}


float  AsyncSI7021::_humidityConversion(uint16_t rawHumidity) {
  float humidity = rawHumidity;
  return ((125 * humidity) / 65536) - 6;
}

float AsyncSI7021::_temperatureConversion(uint16_t rawTemperature) {
  float temperature = rawTemperature;
  return ((175.72 * temperature) / 65536) - 46.85;
}

uint8_t AsyncSI7021::_read() {
  Wire.requestFrom(SI7021_I2C_ADDRESS, 1);
  return Wire.read();
}

uint16_t AsyncSI7021::_read16() {
  Wire.requestFrom(SI7021_I2C_ADDRESS, 2);
  uint16_t result;
  result = Wire.read();
  result <<= 8;
  result |= Wire.read();
  return result;
}
void AsyncSI7021::_write(uint8_t reg, bool i2cStopMessage  = true) {
  Wire.beginTransmission(SI7021_I2C_ADDRESS);
  Wire.write(reg);
  Wire.endTransmission(i2cStopMessage);
}
void AsyncSI7021::_writeValue(uint8_t reg, uint8_t value, bool i2cStopMessage  = true) {
  Wire.beginTransmission(SI7021_I2C_ADDRESS);
  Wire.write(reg);
  Wire.write(value);
  Wire.endTransmission(i2cStopMessage);
}
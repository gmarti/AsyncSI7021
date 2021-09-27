/*
    AsyncSI7021.cpp
 
    Created by Grégory Marti <greg.marti@gmail.com>
    Copyright 2017 Grégory Marti
 
    This file is part of the AsyncSI7021 library.
 
    AsyncSI7021 library is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#if ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include <Wire.h>
#include "AsyncSI7021.h"

AsyncSI7021::AsyncSI7021() {}

bool AsyncSI7021::begin() {
  Wire.begin();
  Wire.beginTransmission(SI7021_I2C_ADDRESS);

  return Wire.endTransmission() == 0;
}

float AsyncSI7021::syncHumidityMeasurement() {
  _write(SI7021_CMD_RH_HOLDMM, false);
  return getHumidityMeasurement();
}

float AsyncSI7021::syncTemperatureMeasurement() {
  _write(SI7021_CMD_TEMP_HOLDMM, false);
  return getTemperatureMeasurement();
}

int AsyncSI7021::startHumidityMeasurement() {
  return _write(SI7021_CMD_RH_NOHOLDMM);
}

int AsyncSI7021::startTemperatureMeasurement() {
  return _write(SI7021_CMD_TEMP_NOHOLDMM);
}

float AsyncSI7021::getHumidityMeasurement() {
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

int AsyncSI7021::_write(uint8_t reg, bool i2cStopMessage  = true) {
  Wire.beginTransmission(SI7021_I2C_ADDRESS);
  Wire.write(reg);
  return Wire.endTransmission(i2cStopMessage);
}

int AsyncSI7021::_writeValue(uint8_t reg, uint8_t value, bool i2cStopMessage  = true) {
  Wire.beginTransmission(SI7021_I2C_ADDRESS);
  Wire.write(reg);
  Wire.write(value);
  return Wire.endTransmission(i2cStopMessage);
}

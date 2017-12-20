/*
    AsyncRead.ino
 
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

#include <AsyncSI7021.h>

AsyncSI7021 sensor;

void setup() {
  Serial.begin(9600);
  if (sensor.begin()) {
    Serial.print("Sensor found !");
  } else {
    Serial.print("Sensor not found !");
  }
}


void loop() {

  unsigned long startTime;
  unsigned long duration;

  Serial.println("Starting humidity measurement");
  startTime = millis();

  sensor.startHumidityMeasurement();

  while (!sensor.isMeasurementReady()) {
  }

  duration = millis() - startTime;
  Serial.print(duration);
  Serial.println("ms (following datasheet, should be between (10+7) and (12+10.8)ms)");

  float humidity = sensor.getHumditityMeasurement();

  Serial.print("Humidity : ");
  Serial.print(humidity, 2);
  Serial.println("%");


  Serial.print("Read temperature of humidity measurement : ");
  startTime = millis();

  float temperature = sensor.readTemperatureFromHumidityMeasurement();

  duration = millis() - startTime;
  Serial.print(duration);
  Serial.println("ms");
  Serial.print("Temperature : ");
  Serial.print(temperature, 2);
  Serial.println("C°");

  Serial.println("Starting temperature measurement");
  startTime = millis();

  sensor.startTemperatureMeasurement();

  while (!sensor.isMeasurementReady()) {
  }

  duration = millis() - startTime;
  Serial.print(duration);
  Serial.println("ms (following datasheet, should be between 7 and 10.8ms)");

  temperature = sensor.getTemperatureMeasurement();

  Serial.print("Temperature : ");
  Serial.print(temperature, 2);
  Serial.println("C°");

  delay(5000);
}
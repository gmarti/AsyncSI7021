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

  Serial.println("Humidity measurement");
  startTime = millis();

  float humidity = sensor.syncHumidityMeasurement();


  duration = millis() - startTime;
  Serial.print(duration);
  Serial.println("ms (following datasheet, should be between (10+7) and (12+10.8)ms)");

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

  Serial.println("Temperature measurement");
  startTime = millis();

  temperature = sensor.syncTemperatureMeasurement();

  duration = millis() - startTime;
  Serial.print(duration);
  Serial.println("ms (following datasheet, should be between 7 and 10.8ms)");

  Serial.print("Temperature : ");
  Serial.print(temperature, 2);
  Serial.println("C°");

  delay(5000);
}
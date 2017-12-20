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

  float temperature = sensor.readTemperatureAfterHumidity();

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
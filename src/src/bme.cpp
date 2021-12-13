#include <bme.h>

Adafruit_BME280 bme;

float getTemperature()
{
  return bme.readTemperature();
}

float getPressure()
{
  return bme.readPressure() / 100;
}

float getHumidity()
{
  return bme.readHumidity();
}

float getAltitude()
{
  return bme.readAltitude(1013);
}

float getFeelsLike()
{
  return -8.78469475556 + 1.61139411 * bme.readTemperature() + 2.33854883889 *  (bme.readHumidity() / 100)  + -0.14611605 * bme.readTemperature() * (bme.readHumidity() / 100) + -0.012308094 * bme.readTemperature() * bme.readTemperature() + -0.0164248277778 * (bme.readHumidity() / 100) * (bme.readHumidity() / 100) + 0.002211732 * bme.readTemperature() * bme.readTemperature() * (bme.readHumidity() / 100) + 0.00072546 * bme.readTemperature() * (bme.readHumidity() / 100) * (bme.readHumidity() / 100) + -0.000003582 * bme.readTemperature() * bme.readTemperature() * (bme.readHumidity() / 100) * (bme.readHumidity() / 100);
}

bool initBME()
{
  return bme.begin(0x76, &Wire);
}







































































/*Adafruit_Sensor *bme_temp = bme.getTemperatureSensor();
Adafruit_Sensor *bme_pressure = bme.getPressureSensor();
Adafruit_Sensor *bme_humidity = bme.getHumiditySensor();

void setup()
{
  delay(2000);
  Serial.begin(115200);
  Serial.println(F("BME280 Sensor event test"));
  if (!bme.begin(0x76, &Wire))
  {
    Serial.println(F("Could not find a valid BME280 sensor, check wiring!"));
    while (1)
      delay(10);
  }

  Serial.print(getTemperature());

  bme_temp->printSensorDetails();
  bme_pressure->printSensorDetails();
  bme_humidity->printSensorDetails();

}

void loop()
{
  sensors_event_t temp_event, pressure_event, humidity_event;
  bme_temp->getEvent(&temp_event);
  bme_pressure->getEvent(&pressure_event);
  bme_humidity->getEvent(&humidity_event);

  Serial.print(F("Temperature = "));
  Serial.print(getTemperature());
  Serial.println(" *C");

  Serial.print(F("Humidity = "));
  Serial.print(getHumidity());
  Serial.println(" %");

  Serial.print(F("Pressure = "));
  Serial.print(getAltitude());
  Serial.println(" hPa");

  Serial.println();
  delay(2000);
}*/
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_BME280.h>

/*Gets the temperature which the BME measures*/
float getTemperature();

/*Gets the presssure which the BME measures*/
float getPressure();

/*Gets the humidity which the BME measures*/
float getHumidity();

/*Gets the altitude which the BME measures*/
float getAltitude();

/*Gets the feels like temperature which the BME measures*/
float getFeelsLike();

/*Initializes the BME*/
bool initBME();
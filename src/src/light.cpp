#include "light.h"

BH1750 lightMeter;

bool initBH()
{
  lightMeter.begin(BH1750::CONTINUOUS_HIGH_RES_MODE, 0x5C, &Wire);
  return lightMeter.measurementReady();
}

float getLightLevel()
{
  return lightMeter.readLightLevel();
}

bool readyMeasurementReady()
{
    return lightMeter.measurementReady();
}

#include <Wire.h>
#include <BH1750.h>


/*Initializes the BH Sensor, which measures the Light Level*/
bool initBH(); 

float getLightLevel();

bool readyMeasurementReady();

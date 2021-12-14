#include <Arduino.h>
#include <WiFi.h>
#include <stdlib.h>
#include <string.h>
#include <ESPAsyncWebServer.h>
#include <AsyncTCP.h>
#include <WebSockets.h>
#include <SPIFFS.h>
#include "esp_wpa2.h"
#include <ArduinoJson.h>
/// include sensors
#include "bme.h"
#include "light.h"

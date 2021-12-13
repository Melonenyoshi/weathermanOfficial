#include <main.h>

const char *ssid = "your networks name goes here";
const char *password = "your password goes here";
const int delayAmount = 500;

String firstVal;
String lastVal;
String temperature = "";
String humidity = "";
String pressure = "";
String altitude = "";
String lightlevel = "";
const uint JsonArrayLength = 10;
int currentIndexJsonArray = 0;
DynamicJsonDocument doc((1024 * JsonArrayLength));
String output;

AsyncWebServer server(80);
AsyncWebSocket ws("/ws");


// This section is for further internet settings 
IPAddress staticIP(192, 168, 1, 137);
IPAddress gateway(192, 168, 1, 1);
IPAddress subnet(255, 255, 255, 0);
#define EAP_ID ""
#define EAP_USERNAME ""
#define EAP_PASSWORD ""



void setup()
{
    Serial.begin(115200);
    SPIFFS.begin(true);
    initBME();
    initBH();
    initWiFi();
    initServer();
    initWebSocket();
    initJson();
}

void loop()
{
    changeAndSendJson();
    sendData();
    delay(delayAmount);

}

void initWiFi()
{
    WiFi.mode(WIFI_STA);
    WiFi.config(staticIP, gateway, subnet);
    WiFi.disconnect(true);
    // this is if you use a wpa2 Enterprise
    /*
    esp_wifi_sta_wpa2_ent_set_identity((uint8_t *)EAP_ID, strlen(EAP_ID));
    esp_wifi_sta_wpa2_ent_set_username((uint8_t *)EAP_USERNAME, strlen(EAP_USERNAME));
    esp_wifi_sta_wpa2_ent_set_password((uint8_t *)EAP_PASSWORD, strlen(EAP_PASSWORD));
    esp_wpa2_config_t config = WPA2_CONFIG_INIT_DEFAULT();
    esp_wifi_sta_wpa2_ent_enable(&config);
    */
    WiFi.begin(ssid);
    Serial.printf("Trying to connect [%s] ", WiFi.macAddress().c_str());
    while (WiFi.status() != WL_CONNECTED)
    {
        Serial.print(".");
        delay(500);
    }
    Serial.printf(" %s\n", WiFi.localIP().toString().c_str());
}

void initServer()
{
    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request)
              { request->send(SPIFFS, "/index.html", "text/html"); });
    server.on("/charts.html", HTTP_GET, [](AsyncWebServerRequest *request)
              { request->send(SPIFFS, "/charts.html", "text/html"); });
    server.on("/stylesheet.css", HTTP_GET, [](AsyncWebServerRequest *request)
              { request->send(SPIFFS, "/stylesheet.css", "text/css"); });
    server.on("/charts.js", HTTP_GET, [](AsyncWebServerRequest *request)
              { request->send(SPIFFS, "/charts.js", "text/javascript"); });
    server.on("/charts.js.map", HTTP_GET, [](AsyncWebServerRequest *request)
              { request->send(SPIFFS, "/charts.js.map", "text/javascriptmap"); });
    server.on("/v1", HTTP_GET, [](AsyncWebServerRequest *request)
              { request->send(SPIFFS, "/v1index.html", "text/html"); });
    server.on("/weather.js", HTTP_GET, [](AsyncWebServerRequest *request)
              { request->send(SPIFFS, "/weather.js", "text/javascript"); });
    server.on("/weather.js.map", HTTP_GET, [](AsyncWebServerRequest *request)
              { request->send(SPIFFS, "/weather.js.map", "text/javascriptmap"); });
    server.on("/v1weather.js", HTTP_GET, [](AsyncWebServerRequest *request)
              { request->send(SPIFFS, "/v1weather.js", "text/javascript"); });
    server.on("/v1weather.js.map", HTTP_GET, [](AsyncWebServerRequest *request)
              { request->send(SPIFFS, "/v1weather.js.map", "text/javascriptmap"); });
    server.on("/dataset.json", HTTP_GET, [](AsyncWebServerRequest *request)
              { request->send(SPIFFS, "/dataset.json", "text/json"); });
    server.begin();
}

void initWebSocket()
{
    ws.onEvent(onEvent);
    server.addHandler(&ws);
}

void onEvent(AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type, void *arg, uint8_t *data, size_t len)
{
    switch (type)
    {
    case WS_EVT_CONNECT:
        Serial.printf("WebSocket client #%u connected from %s\n", client->id(), client->remoteIP().toString().c_str());
        break;
    case WS_EVT_DISCONNECT:
        Serial.printf("WebSocket client #%u disconnected\n", client->id());
        break;
    default:
        break;
    }
}

void sendData()
{
    ws.textAll('t'+ temperature);
    delay(delayAmount);
    ws.textAll('p'+ pressure);
    delay(delayAmount);
    ws.textAll('h'+ humidity);
    delay(delayAmount);
    ws.textAll('a'+ altitude);
    delay(delayAmount);
    ws.textAll('f'+ (String)getFeelsLike());
    delay(delayAmount);
    ws.textAll('l'+ lightlevel);
    delay(delayAmount);

}

void initJson()
{
    for (int i = 0; i < JsonArrayLength; i++)
    {
        doc[i]["Temperature"] = ((String)0);
        doc[i]["Humidity"] = ((String)0);
        doc[i]["Pressure"] = ((String)0);
        doc[i]["Altitude"] = ((String)0);
        doc[i]["LightLevel"] = ((String)0);
    }
}

void writeJSON()
{
    if (currentIndexJsonArray < JsonArrayLength)
    {
        doc[currentIndexJsonArray]["Temperature"] = temperature;
        doc[currentIndexJsonArray]["Humidity"] = humidity;
        doc[currentIndexJsonArray]["Pressure"] = pressure;
        doc[currentIndexJsonArray]["Altitude"] = altitude;
        doc[currentIndexJsonArray]["LightLevel"] = lightlevel;
        currentIndexJsonArray++;
    }
    else
    {
        currentIndexJsonArray = 0;
        writeJSON();
    }
}

void changeAndSendJson()
{
    temperature = (String)getTemperature();
    humidity = (String)getHumidity();
    pressure = (String)getPressure();
    altitude = (String)getAltitude();
    lightlevel = (String)getLightLevel();
    writeJSON();
    serializeJsonPretty(doc, output);
    ws.textAll(output);
    output = "";
}
#include "includes.h"
/// Prototypes
void initWiFi();
void initServer();
void initWebSocket();
void webSocketEvent(uint8_t num, WStype_t type, uint8_t *payload, size_t length);
void onEvent(AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type, void *arg, uint8_t *data, size_t len);
void sendData();
void initJson();
void changeAndSendJson();
void writeJSON();
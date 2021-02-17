#pragma once
#include <Arduino.h>
 

#define lampWebServer LampWebServer::instance()

class AsyncWebSocket;
class AsyncWebSocketClient;
class LampWebServer
{
public:
    static LampWebServer *instance();
    static void Initialize(uint16_t webPort = 80);
    void enterSetupMode();

    bool isConnected();
    void autoConnect();
    void loop();
    void sendConfig(uint32_t source);
    bool isUpdating();
    void onConnected(void (*func)(bool));
    void update();
    void update(uint32_t source);
    String createConfigJson();

protected:
    LampWebServer(uint16_t webPort);

};


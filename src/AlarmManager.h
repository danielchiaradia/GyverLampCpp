#pragma once
#include <Arduino.h>
#define ARDUINOJSON_ENABLE_PROGMEM 1
#include <ArduinoJson.h>

#include <map>
    

#define alarmManager AlarmManager::instance()

class AlarmManager
{
public:
    static AlarmManager *instance();
    static void Initialize();

    void loop();

    void processAlarmSettings(const JsonArray &root);
    void buildAlarmJson(JsonArray &alarms);
    // void processAllEffects();

    // void changeEffectByName(const String &name);
    // void changeEffectById(const String &id);
    // void activateEffect(uint8_t index);

    // void updateCurrentSettings(const JsonObject &json);
    // void updateSettingsById(const String &id, const JsonObject &json);

protected:
    AlarmManager();



};


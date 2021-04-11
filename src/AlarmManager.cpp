#include "AlarmManager.h"
#include <list>

namespace
{
    AlarmManager *object = nullptr;

    struct Alarm {
        public:
            String day;
            int hour = 12;
            int minute = 0;
            bool enabled = false;
    };

    std::list<Alarm> alarms;

} // namespace

AlarmManager *AlarmManager::instance()
{
    return object;
}

void AlarmManager::Initialize()
{
    if (object)
    {
        return;
    }

    Serial.println(F("Initializing AlarmManager"));
    object = new AlarmManager();
}

void AlarmManager::loop() 
{

}

void AlarmManager::processAlarmSettings(const JsonArray &root)
{
    alarms.clear();

    for (JsonObject json : root) {
        Alarm alarm;
        String day = json[F("day")];
        alarm.day = day;
        alarm.enabled = json[F("enabled")];

        String time = json[F("time")];
        if (time.length() > 2) {
            alarm.hour = time.substring(0, 2).toInt();
        }

        if (time.length() > 4) {
            alarm.minute = time.substring(3, 5).toInt();
        }
        alarms.push_back(alarm);
    }
}

void AlarmManager::buildAlarmJson(JsonArray &alarmsJson)
{
    for (Alarm alarm : alarms) {
        JsonObject alarmObject = alarmsJson.createNestedObject();
        alarmObject[F("day")] = alarm.day;

        char time[5];
        sprintf(time, "%02d:%02d", alarm.hour, alarm.minute);

        alarmObject[F("time")] = time;
        alarmObject[F("enabled")] = alarm.enabled;
    }
}
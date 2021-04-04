#include "ColorEffect.h"
#include <Spectrometer.h>

namespace  {

bool useSpectrometer = false;
uint32_t myColor = 0;
bool breath = false;
uint32_t frequency = 50;
uint32_t minBrightness = 120;
uint32_t maxBrightness = 255;

} // namespace

ColorEffect::ColorEffect(const String &id)
    : Effect(id)
{
}

void ColorEffect::tick()
{
    CRGB color = myColor;

    if (!color) {
        uint8_t hue = (mySettings->generalSettings.soundControl && useSpectrometer)
                ? mySpectrometer->asHue()
                : settings.scale * 2.55;
        color = CHSV(hue, 255, 255);
    }

    if (breath) {
        float dV = ((exp(sin(frequency / 100.0 * millis()/2000.0*PI)) -0.36787944) * ((maxBrightness - minBrightness) / 2.35040238));
        // uint8_t fade = map((uint8_t) dV, 0, 134, minBrightness, maxBrightness);
        color.fadeToBlackBy(dV);
    }

    myMatrix->fill(color);
}

void ColorEffect::initialize(const JsonObject &json)
{
    Effect::initialize(json);
//    if (json.containsKey(F("useSpectrometer"))) {
//        useSpectrometer = json[F("useSpectrometer")];
//    }
    if (json.containsKey(F("color"))) {
        const JsonVariant color = json[F("color")];
        if (color.is<uint32_t>()) {
            myColor = json[F("color")];
        } else if (color.is<JsonObject>()) {
            myColor = json[F("color")]["r"].as<uint8_t>() << 16 |
                      json[F("color")]["g"].as<uint8_t>() << 8 |
                      json[F("color")]["b"].as<uint8_t>();
        }
    }
    if (json.containsKey(F("breath"))) {
        breath = json[F("breath")];
    }

    if (json.containsKey(F("min"))) {
        minBrightness = json[F("min")];
    }

    if (json.containsKey(F("max"))) {
        maxBrightness = json[F("max")];
    }

    if (json.containsKey(F("frequency"))) {
        frequency = json[F("frequency")];
    }
}

void ColorEffect::writeSettings(JsonObject &json)
{
//    json[F("useSpectrometer")] = useSpectrometer;
    json[F("color")] = myColor;
    json[F("breath")] = breath;
    json[F("min")] = minBrightness;
    json[F("max")] = maxBrightness;
    json[F("frequency")] = frequency;
}

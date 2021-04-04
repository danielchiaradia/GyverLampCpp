![Github Actions CI Status](https://github.com/CODeRUS/GyverLampCpp/workflows/PlatformIO%20build/badge.svg)

<br />
You can download latest build with artifacts from GitHub [Releases](https://github.com/CODeRUS/GyverLampCpp/releases) page
<br />
# GyverLampCpp

Rewrite of https://github.com/AlexGyver/GyverLamp in C++ and classes for PlatformIO: https://platformio.org/platformio-ide

Discuss building, modifications, deployment, etc. in telegram group: [@GyverLampCpp](https://t.me/GyverLampCpp)

Contains effects ported from:
- https://community.alexgyver.ru/threads/wifi-lampa-budilnik-obsuzhdenie-proshivki-ot-gunner47.2418/page-72#post-33652
- https://github.com/pixelmatix/aurora
- https://github.com/marcmerlin/FastLED_NeoMatrix_SmartMatrix_LEDMatrix_GFX_Demos

Contains DMX core ported from:
- https://github.com/Aircoookie/WLED

All original code is owned by it's authors

Supported boards:
- esp8266 with 4MB flash. Environment name - `nodemcu`
- esp-01s board woth 1MB flash. Environment name - `esp01s`
- Sonoff (Basic) board with 1MB flash. Environment name - `sonoff-r1`
- Sonoff (Basic) board with 4MB flash. Environment name - `sonoff-r1-4m`
- Any ESP32 board. Environment name - `esp32dev`

Note: 1MB boards are not capable of OTA firmware updates

# Construction
This is how I built it:
1. Get the following materials:
   - ESP32
   - Lampshade/Socket (for example this one: https://de.aliexpress.com/item/4000386426747.html)
   - 1xARCELI 5PCS 2.5-5.5V TTP223
   - 1xFemale DC Connector 2.1*5.5mm (no housing - you might have to remove it)
   - 16x16 LED Matrix (can be bought together with the lampshade)
   - 5V 15Watt power supply
   - 3D Printed Socket and Top parts (top cap height needs to be adjusted according to your pipe length)
   ![Materials](https://github.com/danielchiaradia/GyverLampCpp/raw/master/assets/01-materials.jpg)
2. Drill a hole in the socket and guide a cable through it.
   ![Materials](https://github.com/danielchiaradia/GyverLampCpp/raw/master/assets/02-socket.jpg)
3. Solder the power jack to the cable and plug it into the socket. Some material of the socket must be removed to have a leveled bottom surface.
   ![Materials](https://github.com/danielchiaradia/GyverLampCpp/raw/master/assets/03-socket.jpg)
4. Use some wax or hotglue to secure the jack into the socket. You can use some sandpaper to create a leveled surface.
   ![Materials](https://github.com/danielchiaradia/GyverLampCpp/raw/master/assets/04-socket.jpg)
5. Print the socket.blend file and attach it to the socket with some hotglue:
   ![Materials](https://github.com/danielchiaradia/GyverLampCpp/raw/master/assets/05-socket.jpg)
6. Get a plastic pipe with a 50cm outer diameter and 46cm inner diameter (height must be measured together with the top cap). It is not required for the cap to touch the lampshade. The touch sensor works also with some space. Create some holes for the matrix connectors and secure the matrix with some zip ties.
   ![Materials](https://github.com/danielchiaradia/GyverLampCpp/raw/master/assets/06-pipe.jpg)
7. Print the top.blend file (rearrange the thickness of the cap according to your pipe height), guide the cables of the touch sensors through the hole and solder them to the touch sensor.
  ![Materials](https://github.com/danielchiaradia/GyverLampCpp/raw/master/assets/07-top.jpg)
9. Wire the ESP with the ingoing connector of the matrix (red=5V, white=GND, green=21) and the touch sensor (27 from the touch I/O)
  ![Materials](https://github.com/danielchiaradia/GyverLampCpp/raw/master/assets/08-esp.jpg)
10. Solder a small perfboard with two cable connectors (one side for your power supply, the other side to the matrix power input) and solder the touch sensors PWR/GND accordingly (or use a jumper connector if you have one :)).
  ![Materials](https://github.com/danielchiaradia/GyverLampCpp/raw/master/assets/09-power.jpg)
11. Put everything into the pipe (secured with hotglue), drill a small hole into the pipe/socket and secure the pipe on the socket with a coarse thread screw.
  ![Materials](https://github.com/danielchiaradia/GyverLampCpp/raw/master/assets/10-result.jpg)

Thats it. The lampshade is loose on the socket but you should not shake the lamp anyways.

# How to build

1. build firmware: `pio run -e esp32dev`
2. build filesystem: `pio run --target buildfs -e esp32dev`

# Filesystem build

Manual steps:

- build https://github.com/danielchiaradia/led-lamp-webui
- copy gzipped artifacts to data folder and remove any precached files.
- build filesystem in Platform IO


**PLEASE!** Do not forget to build or to download and extract data artifacts from releases page! It is not present in git repository!

Then just upload built fs to module using `pio run --target uploadfs -e esp32dev`

## Configuration

src/EffectsManager.cpp - comment out unused effects here. Comment out incudes at top and RegisterEffect from bottom of file.

data/effects.json - default options for effects

    i - id of effect, should match one in src/EffectsManager.cpp
    n - name of efect visible in ui and Home Assistant
    e - effect enabled (will be ignored when pressing the button)
    s - effect speed
    l - effect scale
    b - effect brightness

data/settings.json - main settings of firmware
matrix - settings of matrix

    pin - GPIO number of pin used to communicate with matrix leds
    type - match with Framebuffer GFX: https://github.com/marcmerlin/Framebuffer_GFX/blob/master/Framebuffer_GFX.h#L43
    values should be combined. Example: NEO_MATRIX_ZIGZAG + NEO_MATRIX_BOTTOM + NEO_MATRIX_RIGHT + NEO_MATRIX_ROWS (or NEO_MATRIX_COLUMNS) = 11 (or 15). Matrix test effect at boot: Pixels started from left bottom. Red is horizontal from left to right, Green is vertical from bottom to top.
    rotation - value from 0 to 3, each value by +90 degree.
    dither - enable or disable dithering: https://github.com/FastLED/FastLED/wiki/FastLED-Temporal-Dithering

connection - connection settings

    mdns - domain name in .local
    apName - access point name for initial configuration
    apPassword - access point password
    ntpServer - time server name
    ntpOffset - time offset in seconds
    hostname - hostname for local network
    ssid - name of wifi network to connect
    bssid - mac of wifi network, use for connection to certain access point
    password - password of wifi network to connect
    login - login for connection to wifi network (WPA-E)

mqtt - mqtt settings

    host - server address
    port - server port
    username - username
    password - password
    uniqueId - unique identifier for entity light in Home Assistant
    name - device name in Home Assistant
    model - model name in Home Assistant

button - button settings

    pin - GPIO pin number, set to 255 if you have no button connected
    type - 0 if pin button is connected to 3v3, 0 if button connected to GND
    state - set to 1 to invert button state, 0 for normal operation

Please refer to https://github.com/esp8266/Arduino/blob/master/variants/nodemcu/pins_arduino.h#L40 for pin numbers if using nodemcu-like ESP8266 boards! This configuration uses numeric gpio pins, not the ones marked as D0-D10 on the board!

## Safe mode

If lamp is turned on while button is pressed, it will boot into safe mode. Lamp will try to connect to last known network, otherwise it will create access point. You can connect to lamp with your mobile device using wifi and upload correct json settings or firmware files.

Please do not use GPIO0, GPIO2, GPIO15 (D3, D4 and D8 on nodemcu boards) for button connection, your board may fail to boot at all if button will be pressed during startup: https://www.forward.com.au/pfod/ESP8266/GPIOpins/index.html

## OTA - Over The Air updates

You can upload firmware.bin, fs.bin, settings.json, effects.json with OTA using web interface. Boards with 1MB flash memory don't have enough space for firmware/fs updates, but capable of json configuration updates. The lamp also allows direct OTA updated via port 8266.

## Changes with original GyverLampCpp 
- Generally optimized for ESP32 with the drawback that it might now work on chips with less than 4 MB Flash.
- Removed the static hosted pages and host everything on the ESP.
- Fixed some bugs in the WebUI (effects were not always loaded)
- WiFi reconnect was buggy on ESP32 and has been replaced with WiFiManager
- ArduinoOTA support (partitions have been resized)


## Changes with original GyverLamp projects

- Rewritten in C++ and classes for easier maintenance
- ESP32 support
- Sonoff Basic support
- Asynchronous WiFi Manager
- FastLED_NeoMatrix library instead of Gyver handmade one (sorry)
- Settings moved to SPIFFS json file

## New features:

- Clock effects
- Spectrometer effect (requires microphone module or aux, should be uncommented in EffectsManager.cpp and added to effects.json)
- React web with controls self-coded component. No need to install client applications
- Firmware update page, allowing to upload firmware bin, filesystem bin or settings json
- MQTT for Home Assistant integration
- Sonoff Basic relay and led are bound to led state
- DMX input via e131 and Art-Net protocols

## Missing features from original project

- Not compatible with any client application. You can connect to lamp directly using any web browser. Or use MQTT/HomeAssistant to control it
- Alarms not implemented

## TODO

- Alarms support

## Audio input wirings for Spectrometer effects

Please check by link: https://gist.github.com/CODeRUS/f025fa5c12d6eaad6878576e8255913a

# ESP-SMART-Thermostat
ESP32 smart thermostat with remote sensor and watchdog

An ESP implementation of a smart thermostat or simple ON/OFF timer

Access via logical name e.g. http://thermostat.local/

For ESP8266 it requires ESPAsyncTCP to use this library you will need version 2.5.1 of ESP8266 Arduino Core until the issues are fixed with the latest.

For ESP32 it requires AsyncTCP to use this library you may need to have the latest git versions of ESP32 Arduino Core

Comprehensive features:
1. 7-Day timer and 4 target temperature periods per-day, all adjustable

2. Graphical view of temperature / humidity history 

3. Frost protection, Over-heat protection

4. Hysteresis to prevent cycling and save energy

5. Early start mode, to achieve room temperature before the Schedule begins

6. Saves all settings in flash memory

7. Simulation mode for testing without a sensor or relay (just ESP required)

8. Use as a simple ON/OFF timer

9. All HTML is fully validated by W3C

Example webpages:

![alt_text, width="200"](/Slide1.JPG)

ESP32 Wiring:

![alt_text, width="200"](/Slide6.JPG)

ESP8266 Wiring:

![alt_text, width="200"](/Slide7.JPG)





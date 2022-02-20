# ESP-SMART-Thermostat
ESP32 smart thermostat with remote sensor and watchdog

An ESP implementation of a smart thermostat or simple ON/OFF timer

Access via logical name e.g. http://thermostat.local/


For ESP32 it requires AsyncTCP to use this library you may need to have the latest git versions of ESP32 Arduino Core

Comprehensive features:
1. 7-Day timer and 6 target temperature periods per-day, all adjustable

2. Graphical view of temperature / humidity history 

3. Hysteresis to prevent cycling

4. Saves all settings in flash memory

5. Simulation mode for testing without a sensor or relay (just ESP required)

6. Use as a simple ON/OFF timer with temperature signal filtering

9. All HTML is fully validated by W3C

Example webpages:

![alt_text, width="200"](/RemoteSensor.png)

ESP32 Wiring:
https://github.com/rcdesigns/ESP-SMART-Thermostat-With-Remote-Sensor_And_Watchdog/blob/main/ESP%20Receiver%20with%20Watchdog.png







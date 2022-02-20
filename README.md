# ESP-SMART-Thermostat
ESP32 smart thermostat with remote sensor and watchdog

An ESP implementation of a smart thermostat with simple ON/OFF timer

Access via logical name e.g. http://thermostat.local/


For ESP32 it requires AsyncTCP to use this library you may need to have the latest git versions of ESP32 Arduino Core

Comprehensive features:
1. 7-Day timer and 6 target temperature periods per-day, all adjustable
2. Graphical view of temperature history 
3. Hysteresis to prevent cycling
4. Saves all settings in flash memory
5. Simulation mode for testing without a sensor or relay (just ESP required)
6. Use as a simple ON/OFF timer with temperature signal filtering
7. All HTML is fully validated by W3C
8. Watchdog using Arduino or similar to shut off an additional relay should the main ESP32 hang
9. Remote Sensor with OLED display and boost button, using local Access Point (not reliant on a router)
10. Local temperature sensor on the Receiver as a fallback incase the remote sensor fails

Remote Sensor:

![alt_text, width="200"](/RemoteSensor.png)

ESP32 Receiver Wiring:
![alt_text, width="200"](/ESPReceiverWithWatchdog.png)

Web pages:
![alt_text, width="200"](/StatusScreen.png)

![alt_text, width="200"](/ScheduleScreen.png)

![alt_text, width="200"](/StatusScreen.png)







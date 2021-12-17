# The HomeKit-enabled Christmas Tree!

..aka **SantaKit**. This is firmware for an ESP8266 with an IR led connected
(directly!) to one of the GPIO pins.

Edit the platformio.ini file to match your config, build with PlatformIO:

`WIFI_SSID='"[SID name]"' WIFI_PASS='"[WiFi password]"'  pio run --target=upload``

...and add to your HomeKit installation. The default password is set to 
666-66-666 and I'm pretty sure it won't work for more than one tree at a time.



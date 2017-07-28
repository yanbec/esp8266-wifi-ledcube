# esp8266-wifi-ledcube
### About
These days every device needs to have WiFi. So do LED-cubes like the DIY-kits (featuring the STC12C5A60S2) sold on eBay.
It's a first try to make the cube controllable by a responsive web interface.

### Features
* Responsive Web-Interface made with bootstrap
* Built-in simple animations in the arduino-project
* Turn cube full on, off, pause and resume animations
* Capability to load animations made with [DotMatrixJava](https://github.com/tomazas/DotMatrixJava) from SPIFFS
* SPIFF-data includes all examples from DotMatrixJava
* You get a wifi-enabled LED-cube

### Not-So-Features
* Work of about a day and a night, may contain horrible design choices and serious bugs
* Not really cleaned the code until now

### ToDo
* Code cleaning
* More animations
* Possibility to let the cube cycle animations "on it's own"
* Configure WiFi credentials via web interface (and store them on the SPIFFS)
* Maybe make it somehow possible to create animations via the web interface
* More animations
* Upload animations made with DotMatrixJava via web interface and list them
* More animations
* Get rid of unneccessary bootstrap features (loading times of the interface)

### How to Use

Check these projects:
* [ledcube8x8x8](https://github.com/tomazas/ledcube8x8x8)
* [DotMatrixJava](https://github.com/tomazas/DotMatrixJava)
* [arduino-esp8266fs-plugin](https://github.com/esp8266/arduino-esp8266fs-plugin)

To get your WifiCube up and running, the firmware v2 out of the first project needs to be flashed to the STC microcontroller.
When that's done, the cube is controllable via UART with the ESP8266(and with your PC and the second project mentioned above). In order to do this, get the Arduino sketch out of this project on your ESP, flash the data-folder to the SPIFF, connect TX, RX, & GND from the ESP and enjoy. If the WiFi of the ESP can't connect with the configured credentials (ESPCube.ino) in about 10 seconds, it will raise a Soft-AP named "ESPCube" for you to use. The standard IP should be 192.168.4.1.

On startup, the whole cube will blink with a delay of 100 ms, trying to connect to the configured WiFi. On success, the animation will change to to one fourth of the cube circling counter-clockwise. If the connection can't be established, it will set up a SoftAP and you'll see 1x8 LEDs circling around clockwise.

Let me know if you are in trouble, but also if you have fun :)

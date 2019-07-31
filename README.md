# LoRa_P2P
Testing by transmission data of Temp and Humi via LoRa between Sender and Receiver.
I used Heltec WIFI_ESP_32
![My image](https://raw.github.com/atthana/LoRa_P2P/master/14627-1.jpg)

In the Sender I'm now using BAND = 921E6 (921 MHz) and pin 2 to connect to DHT11.
## Library:
~~~
#include<ArduinoJson.h>   // For arrange data to be JSON format and serialize to broadcast. 
#include <U8x8lib.h>      // For display OLED on module Heltec_ESP_32
#include <LoRa.h>         // For using LoRa function.
#include <SimpleDHT.h>    // For using DHT
~~~
![My image](https://raw.github.com/atthana/LoRa_P2P/master/14628-1.jpg)
![My image](https://raw.github.com/atthana/LoRa_P2P/master/1563873050666.jpg)
![My image](https://raw.github.com/atthana/LoRa_P2P/master/1563873129204.jpg)

## RSSI = Received signal strength indication.

![My_image](https://www.researchgate.net/profile/Venet_Osmani/publication/220535505/figure/tbl1/AS:649635978817582@1531896695609/FM-RSSI-level-conversion.png)

### More specifications about LoRa:
LoRaWan Network 101 OverView Lora alliance go to https://lora-alliance.org/

![My image](https://raw.github.com/atthana/LoRa_P2P/master/1564116318365.jpg)
![My image](https://raw.github.com/atthana/LoRa_P2P/master/1564134711764.jpg)

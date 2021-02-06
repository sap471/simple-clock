# Simple Clock

**TODO**

- Add Temperature Sensor (ds18b20 / dht11 / dht22)
- Maybe Alarm ?

Using :

- NodeMCU Lolin v3 ESP8266
- MAX7219 Led Matrix
- DS3231

Libraries :

- RTCLib
- MD_Parola
- MD_MAX72xx

Diagram :

| NodeMCU | Max7219 | DS3231 |
| ------- | ------- | ------ |
| D1      |         | SCL    |
| D2      |         | SDA    |
| D5      | CLK     |        |
| D7      | DOUT    |        |
| D8      | CS      |        |

IDE :

- Visual Studio Code

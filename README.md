# Tiny_LightWand
![alt tag](https://github.com/brinnLabs/Tiny_Light_Wand/blob/master/IMG_9149.JPG)

A simple cheap light wand for time lapse photography

This is for controlling a strip of 50 neopixels or ws2812s with several preprogrammed animations. 
Using about 5$ in parts for the board and 20$ or so for the remaining materials.

![alt tag](https://github.com/brinnLabs/Tiny_Light_Wand/blob/master/IMG_9121.JPG)

### Board Parts:
 * ATTiny85 ~$1
 * L7805 5V voltage regulator ~$.50
 * 9V Battery depends on the brand
 * 9V Battery connector ~$.50
 * momentary/toggle switch x2 ~$1

### Wand Parts:
 * 20mm x 20mm 80/20 aluminum x profile extrusion ~$10 size will depend on led spacing etc...
 * neopixel/ws2812 strip ~$15
 
![alt tag](https://github.com/brinnLabs/Tiny_Light_Wand/blob/master/IMG_9147.JPG)

To program the ATTinys follow the tutroial written by the High-Low Tech guys over at MIT:
http://highlowtech.org/?p=1695

This program uses the bounce 2 libary found here:
https://github.com/thomasfredericks/Bounce2

I also slightly changed the adafruit neopixel library to give it an easy color structure to work with but 
the normal library will work as long as you change all the uses of the color structure

https://github.com/adafruit/Adafruit_NeoPixel

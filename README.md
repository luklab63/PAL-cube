# PAL V2 

## electronics 

* ESP32 C6 devmodule
* 2x SG90 servo moteurs 
* SH1106 0.94" OLED screen 
* power switch 
* small battery bank 
* used usb cable 
* PCB 

## The PCB 

it is a simple PCB that holds the ESP32 the battery connector and the screen and servo connectors. it is 70 x 60 mm 

![pcb](/PAL%20V2/PCB%203D.png) ![PCB](/PAL%20V2/PCB%20layers.png)

## firmware

### APK

the apk was designed in MIT app inventor using the BLE library and by revers engineering the BLE-controller project on github.

the app is used to control the servo motors and the face that is shown
### The code 

the code is also based on the BLE-controller project however i have modified a lot to add the U2G8 library to control the screen

the faces are stored in the bitmap.h file. to get the bitmaps for each face you need to convert your image to XBM and than open it with a text editor 

![XBM](/PAL%20V2/Pasted%20image.png) 

## final product 

the final product i intend to make is a shoulder mounted PAL that is battery powered. 

all i need to do now is create a box for the controller and battery, create the shoulder mount and a way to add the controller housing to said shoulder mount.

## funding required

i am pretty autonomous for electronics and coding however funding is needed for 3D printing filament and to print out the PCB.

# **AtTiny412 TrafficLight**

### **So, what is this ?**

Recently I bought a bunch of the new AtTiny412 series microcontroller, these controller have 8 pins, where 5 pins are useable by the user. They are programmed with the UPDI programming interface, occupying only one pin.

For a getting-to-know I quickly created this little project. It is a double trafficlight intended for a plain crossing.

The circuit is as simple as can be, 6 leds, 3 resistors, 1 capacitor, 1 attiny.

Techniques:

- Led multiplexing
- AtTiny412

Programmer:

I use a USB-C CH340 board, it is fitted with a 1k resistor seated between Rx and Tx, Rx is UPDI interface. IMPORANT: To get the thing going, I had to remove the leds fom the board. On hindsight, the Rx led would probably be sufficient but I removed all three of them (or there resistors)

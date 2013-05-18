/*
Bluetooth Mouse Wheel - Example

This example illustrated the use of the Bluetooth Mouse Wheel (Scrolling).

*/

#include <BPLib.h>

BPLib BPMod;
void setup(){
BPMod.begin(BP_MODE_HID,BP_HID_MOUSE);
}

void loop(){
  delay(5000);
  for(signed int i=-5;i<5;i++){
    BPMod.mouseWheel(i);
    delay(100);
  }
}

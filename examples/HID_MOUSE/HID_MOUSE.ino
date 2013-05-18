/*
Bluetooth HID Mouse - Example

This example illustrated how the library can be used to make mouse movements and clicks.

*/

#include <BPLib.h>

BPLib BPMod;
void setup(){
BPMod.begin(BP_MODE_HID,BP_HID_MOUSE);
  
}

void loop(){
  delay(1000);
  for(signed int i=-127;i<127;i++){
    BPMod.mouseMove(i,i);
    delay(100);
  }
  BPMod.mouseClick(BP_MOUSE_BTN_LEFT);
}

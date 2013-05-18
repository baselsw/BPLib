/*
Bluetooth HID Keyboard - example
This example illustrates the different ways you can send keys/keystrokes with the HID keyboard protocol.
This sketch will print the following on the recieving device: lesab (mirrored basel).
*/


#include <BPLib.h>

BPLib BPMod;
void setup(){
BPMod.begin(BP_MODE_HID,BP_HID_KEYBOARD);   //Begin HID Mode with HID KEYBOARD AS TYPE
  
}

void loop(){
  delay(5000);    //Delay 5 seconds between each loop (Not nec.)
  BPMod.sendString("b");  //Send a string (will be recieved as keystroke)
  BPMod.keyboardPress(BP_KEY_LEFT_ARROW,BP_MOD_NOMOD); //Send Scan code (KEY, MODEFIER key)
  BPMod.keyboardReleaseAll(); //Release all keys
  BPMod.sendString("a");
  BPMod.keyboardPress(BP_KEY_LEFT_ARROW,BP_MOD_NOMOD);
  BPMod.keyboardReleaseAll();
  BPMod.sendString("s");
  BPMod.keyboardPress(BP_KEY_LEFT_ARROW,BP_MOD_NOMOD);
  BPMod.keyboardReleaseAll();
  BPMod.sendString("e");
  BPMod.keyboardPress(BP_KEY_LEFT_ARROW,BP_MOD_NOMOD);
  BPMod.keyboardReleaseAll();
  BPMod.sendString("l");
  BPMod.keyboardPress(BP_KEY_LEFT_ARROW,BP_MOD_NOMOD);
  BPMod.keyboardReleaseAll();
}

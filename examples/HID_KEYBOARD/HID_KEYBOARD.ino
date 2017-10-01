/*
Bluetooth HID Keyboard - example
This example illustrates the different ways you can send keys/keystrokes with the HID keyboard protocol.
This sketch will print the following on the recieving device: lesab (mirrored basel).

This example is using the ESP8266 software serial
*/


#include <BPLib.h>
#include <SoftwareSerial.h>

#define RX_PIN D2 // connect to TXD of module
#define TX_PIN D1 // connect to RXD of module (logic level 3.3v!)

SoftwareSerial swSer(RX_PIN, TX_PIN, false, 128);

BPLib *BPMod;
void setup(){
  Serial.begin(115200);
  swSer.begin(115200);

  BPMod = new BPLib(swSer);

  BPMod->begin(BP_MODE_HID,BP_HID_KEYBOARD);   //Begin HID Mode with HID KEYBOARD AS TYPE

}

void loop(){
  Serial.println("loop");
  delay(5000);    //Delay 5 seconds between each loop (Not nec.)
  BPMod->sendString("b");  //Send a string (will be recieved as keystroke)
  BPMod->keyboardPress(BP_KEY_LEFT_ARROW,BP_MOD_NOMOD); //Send Scan code (KEY, MODEFIER key)
  BPMod->keyboardReleaseAll(); //Release all keys
  BPMod->sendString("a");
  BPMod->keyboardPress(BP_KEY_LEFT_ARROW,BP_MOD_NOMOD);
  BPMod->keyboardReleaseAll();
  BPMod->sendString("s");
  BPMod->keyboardPress(BP_KEY_LEFT_ARROW,BP_MOD_NOMOD);
  BPMod->keyboardReleaseAll();
  BPMod->sendString("e");
  BPMod->keyboardPress(BP_KEY_LEFT_ARROW,BP_MOD_NOMOD);
  BPMod->keyboardReleaseAll();
  BPMod->sendString("l");
  BPMod->keyboardPress(BP_KEY_LEFT_ARROW,BP_MOD_NOMOD);
  BPMod->keyboardReleaseAll();
}

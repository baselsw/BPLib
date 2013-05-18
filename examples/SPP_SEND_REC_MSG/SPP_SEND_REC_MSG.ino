/*

Bluetooth SPP - example
This example illustrates the use of the bluetooth serial protocol.

*/


#include <BPLib.h>

BPLib BPMod;
int count = 0;
void setup(){
  BPMod.begin(BP_MODE_SPP,BP_SPP_SPP); //Bluetooth Serial Mode
  BPMod.changeName("BlueNar_One");    //Change bluetooth name (appears on devices searching for BT)
  while(!BPMod.connected()){}; //BlueNar One only! Check if a connection is made
}

void loop(){
  if(BPMod.connected()){    //BlueNar One only! if connected then proceed
 if(BPMod.available()>0){   //Check if data is available
  BPMod.readRaw();    //Read the data (just to empty the buffer)
  count++;
  BPMod.sendString("Count: ");  //Send a string
  BPMod.sendInt(count);         //Send a integer
  BPMod.sendChar('\n');         //Send character
 }
  }
  else{
    while(!BPMod.connected()){};  //BlueNar One only! - If disconnected wait for a new connection
  }
}

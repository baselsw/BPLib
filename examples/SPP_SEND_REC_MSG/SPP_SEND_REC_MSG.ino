/*

Bluetooth SPP - example
This example illustrates the use of the bluetooth serial protocol.

*/


#include <BPLib.h>

BPLib *BPMod;
int count = 0;
void setup(){
  Serial.begin(115200);

  // The 7 pin was something that was previously hard coded into the library, its state gets read by the connected method
  // I'm not really sure what it does :)
  // I guess it has something to do with "BlueNar One only" comments
  pinMode(7, INPUT);
  BPMod = new BPLib(swSer, 7);
  BPMod->begin(BP_MODE_SPP,BP_SPP_SPP); //Bluetooth Serial Mode
  BPMod->changeName("BlueNar_One");    //Change bluetooth name (appears on devices searching for BT)
  while(!BPMod->connected()){}; //BlueNar One only! Check if a connection is made
}

void loop(){
  if(BPMod->connected()){    //BlueNar One only! if connected then proceed
 if(BPMod->available()>0){   //Check if data is available
  BPMod->readRaw();    //Read the data (just to empty the buffer)
  count++;
  BPMod->sendString("Count: ");  //Send a string
  BPMod->sendInt(count);         //Send a integer
  BPMod->sendChar('\n');         //Send character
 }
  }
  else{
    while(!BPMod->connected()){};  //BlueNar One only! - If disconnected wait for a new connection
  }
}

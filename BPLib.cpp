/*
  BPLib.cpp - Library for communication with RN-42 HID Bluetooth module
  Created by Basel Al-Rudainy, 6 april 2013.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.
*/
#include "Arduino.h"
#include "BPLib.h"

BPLib::BPLib(Stream &port, int pin) {
  this->serialInterface = &port;
  if (pin > -1) {
    statusPin = pin;
  }
}

byte BPLib::begin(char BP_Mode[], char BP_Type[])
{
  serialInterface->print(BP_MODE_COMMAND);
  if (get(BP_STAT_CMD, (byte)5) != 1) {
    return (byte)0;
  }//if

  serialInterface->print(BP_Mode);
  if (get(BP_STAT_ACK, (byte)5) != 1) {
    return (byte)0;
  }//if
  if (strcmp(BP_Type, BP_SPP_SPP) > 0) {
    serialInterface->print(BP_Type);
    if (get(BP_STAT_ACK, (byte)5) != 1) {
      return (byte)0;
    }//if
  }
  serialInterface->print(BP_REBOOT);
  if (get(BP_STAT_REBOOT, (byte)9) != 1) {
    return (byte)0;
  }//if
  delay(1000); //Delay (Bluetooth boot-up)

  return (byte)1;
}

byte BPLib::sendCmd(char BP_CMD[])
{
  serialInterface->print(BP_MODE_COMMAND);
  if (get(BP_STAT_CMD, (byte)5) != 1) {
    return (byte)0;
  }//if
  serialInterface->print(BP_CMD);
  if (get(BP_STAT_ACK, (byte)5) != 1) {
    return (byte)0;
  }//if
  serialInterface->print(BP_MODE_EXITCOMMAND);
  if (get(BP_STAT_END, (byte)5) != 1) {
    return (byte)0;
  }//if
  return (byte)1;
}

byte BPLib::readRaw() {
  return serialInterface->read();
}
int BPLib::available() {
  return serialInterface->available();
}

byte BPLib::get(char BP_STAT[], byte strlen)
{
  char buffer[strlen + 1];
  while (serialInterface->available() <= (strlen - 1)) {};
  int count = 0;
  while (serialInterface->available() > 0) {
    buffer[count] = (char)serialInterface->read();
    count++;
  }//while
  buffer[strlen] = 0;
  //serialInterface->print(buffer);//DEBUG
  if (strcmp(buffer, BP_STAT) == 0) {
    return (byte)1;
  }//if
  else {
    return (byte)0;
  }//else
}//get


void BPLib::keyboardPress(byte BP_KEY, byte BP_MOD) {
  serialInterface->write((byte)0xFD); //Start HID Report
  serialInterface->write((byte)0x9); //Length byte
  serialInterface->write((byte)0x1); //Descriptor byte
  serialInterface->write(BP_MOD); //Modifier byte
  serialInterface->write((byte)0x00); //-
  serialInterface->write(BP_KEY); //Send KEY
  for (byte i = 0; i < 5; i++) { //Send five zero bytes
    serialInterface->write((byte)0x00);
  }

}

void BPLib::keyboardReleaseAll() {
  keyboardPress((byte)0x00, BP_MOD_NOMOD);
}

void BPLib::mouseClick(byte BP_BUTTON) {
  mousePress(BP_BUTTON);
  mouseReleaseAll();
}
void BPLib::mouseMove(signed int BP_X, signed int BP_Y) {
  serialInterface->write((byte)0xFD); //Start HID Report
  serialInterface->write((byte)0x5); //Length byte
  serialInterface->write((byte)0x2); //Descriptor byte
  serialInterface->write((byte)0x00); //Button byte
  serialInterface->write(BP_X);  //(-127 to 127)
  serialInterface->write(BP_Y); //(-127 to 127)
  serialInterface->write((byte)0x00);

}
void BPLib::mousePress(byte BP_BUTTON) {
  serialInterface->write((byte)0xFD); //Start HID Report
  serialInterface->write((byte)0x5); //Length byte
  serialInterface->write((byte)0x2); //Descriptor byte
  serialInterface->write(BP_BUTTON); //Button byte
  for (byte i = 0; i < 3; i++) { //Send three zero bytes
    serialInterface->write((byte)0x00);
  }
}

void BPLib::mouseReleaseAll() {
  serialInterface->write((byte)0xFD); //Start HID Report
  serialInterface->write((byte)0x5); //Length byte
  serialInterface->write((byte)0x2); //Descriptor byte
  for (byte i = 0; i < 4; i++) { //Send four zero bytes
    serialInterface->write((byte)0x00);
  }
}

void BPLib::mouseWheel(signed int BP_WHEEL) {
  serialInterface->write((byte)0xFD); //Start HID Report
  serialInterface->write((byte)0x5); //Length byte
  serialInterface->write((byte)0x2); //Descriptor byte
  for (byte i = 0; i < 3; i++) { //Send three zero bytes
    serialInterface->write((byte)0x00);
  }
  serialInterface->write(BP_WHEEL); //Wheel byte (-127 to 127)
}

void BPLib::volumeUp() {
  sendConsumerCommand((byte)0x10, (byte)0x00);
}

void BPLib::volumeDown() {
  sendConsumerCommand((byte)0x20, (byte)0x00);
}

void BPLib::muteAudio() {
  sendConsumerCommand((byte)0x40, (byte)0x00);
}

void BPLib::playPause() {
  sendConsumerCommand((byte)0x80, (byte)0x00);
}

void BPLib::nextTrack() {
  sendConsumerCommand((byte)0x00, (byte)0x01);
}

void BPLib::prevTrack() {
  sendConsumerCommand((byte)0x00, (byte)0x02);
}

void BPLib::stopAudio() {
  sendConsumerCommand((byte)0x00, (byte)0x04);
}

void BPLib::fastForwardAudio() {
  sendConsumerCommand((byte)0x00, (byte)0x10);
}

void BPLib::rewindAudio() {
  sendConsumerCommand((byte)0x00, (byte)0x20);
}

void BPLib::keyRelease() {
  sendConsumerCommand((byte)0x00, (byte)0x00);
}

void BPLib::sendConsumerCommand(byte lowByte, byte highByte) {
  serialInterface->write((byte)0xFD); //Start HID Report
  serialInterface->write((byte)0x3); //Length byte
  serialInterface->write((byte)0x3); //Descriptor byte
  serialInterface->write(lowByte); //Key Release LowByte
  serialInterface->write(highByte); //Key Release HighByte
}

byte BPLib::changeName(char BP_NAME[]) {
  serialInterface->print(BP_MODE_COMMAND);
  if (get(BP_STAT_CMD, (byte)5) != 1) {
    return (byte)0;
  }//if
  serialInterface->print(BP_CHANGE_NAME);
  serialInterface->print(BP_NAME);
  serialInterface->print(F("\r\n"));
  if (get(BP_STAT_ACK, (byte)5) != 1) {
    return (byte)0;
  }//if
  serialInterface->print(BP_MODE_EXITCOMMAND);
  if (get(BP_STAT_END, (byte)5) != 1) {
    return (byte)0;
  }//if
  return (byte)1;

}


void BPLib::sendByte(byte rawData) {
  serialInterface->print(rawData);
}
void BPLib::sendChar(char rawData) {
  serialInterface->print(rawData);
}
void BPLib::sendInt(int rawData) {
  serialInterface->print(rawData);
}
void BPLib::sendFloat(float rawData) {
  serialInterface->print(rawData);
}
void BPLib::sendLong(long rawData) {
  serialInterface->print(rawData);
}
void BPLib::sendString(char rawData[]) {
  serialInterface->print(rawData);
}

void BPLib::gameJoyPress(byte BP_ST_BTN, byte BP_ND_BTN) {
  serialInterface->write((byte)0xFD); //Start HID Report
  serialInterface->write((byte)0x6); //Length byte
  serialInterface->write((byte)BP_ST_BTN); //First Button byte
  serialInterface->write((byte)BP_ND_BTN); //Second Button byte
  for (byte i = 0; i < 4; i++) { //Send four zero bytes
    serialInterface->write((byte)0x00);
  }
}
void BPLib::gameJoyMove(signed int BP_X1, signed int BP_Y1, signed int BP_X2, signed int BP_Y2) {
  serialInterface->write((byte)0xFD); //Start HID Report
  serialInterface->write((byte)0x6); //Length byte
  serialInterface->write((byte)BP_GAMEJOY_ST_NOBTN); //First Button byte
  serialInterface->write((byte)BP_GAMEJOY_ND_NOBTN); //Second Button byte
  serialInterface->write(BP_X1 & 0xFF); //First X coordinate
  serialInterface->write(BP_Y1 & 0xFF); //First Y coordinate
  serialInterface->write(BP_X2 & 0xFF); //Second X coordinate
  serialInterface->write(BP_Y2 & 0xFF); //Second Y coordinate
}
void BPLib::gameJoyReleaseAll() {
  gameJoyPress(BP_GAMEJOY_ST_NOBTN, BP_GAMEJOY_ND_NOBTN);
}

int BPLib::connected() {
  if (statusPin > -1) {
    return digitalRead(statusPin);
  } else {
    return -1;
  }
}

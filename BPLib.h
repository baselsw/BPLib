/*
  BPLib.h - Library for communication with RN-42 HID Bluetooth module
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
#ifndef BPLib_h
#define BPLib_h

#include "Arduino.h"

//Bluetooth Modes
#define BP_MODE_COMMAND    	"$$$"
#define BP_MODE_EXITCOMMAND  	"---\r\n"
#define BP_MODE_SPP  			"S~,0\r\n"
#define BP_MODE_HID  			"S~,6\r\n"
#define BP_MODE_AUTOCONNECT  	"SM,6\r\n"
#define BP_MODE_MANUCONNECT  	"SM,4\r\n"
#define BP_MODE_STATUS			"SO,/#\r\n"

//Bluetooth status messages
#define BP_STAT_CMD  			"CMD\r\n"
#define BP_STAT_END  			"END\r\n"
#define BP_STAT_ACK  			"AOK\r\n"
#define BP_STAT_REBOOT  		"Reboot!\r\n"
//Bluetooth GET commands
#define BP_GET_HID  			"GH\n"

//Bluetooth system commands
#define BP_REBOOT  				"R,1\r\n"
#define BP_RECONNECT  			"C\r\n"
#define BP_CHANGE_NAME			"SN,"
//Bluetooth protocol types
#define BP_SPP_SPP				"AW\r\n"
#define BP_HID_KEYBOARD  		"SH,0200\r\n"
#define BP_HID_MOUSE  			"SH,0220\r\n"
#define BP_HID_GAMEPAD  		"SH,0210\r\n"
#define BP_HID_JOYSTICK  		"SH,0240\r\n"
#define BP_HID_COMBO  			"SH,0230\r\n"

// KEYBOARD Scan Codes
#define	BP_KEY_ENTER		0x28	//Enter
#define	BP_KEY_LEFT_ARROW	0x50	//Left arrow
#define	BP_KEY_DOWN_ARROW	0x51	//Down arrow
#define	BP_KEY_ENTER		0x28	//Enter
#define	BP_KEY_UP_ARROW		0x52	//Up arrow
#define	BP_KEY_ESCAPE		0x29	//Escape
#define	BP_KEY_CAPSLOCK		0x39	//CapsLock
#define	BP_KEY_SCROLLLOCK	0x47	//ScrollLock
#define	BP_KEY_BREAK_PAUSE	0x48	//Break-pause
#define	BP_KEY_NUMLOCK		0x53	//NumLock
#define	BP_KEY_TOGGLE_IPHONE_VIRTUAL_KEYBOARD	0x65	//Toggle iPhone Virtual Keyboard
#define	BP_KEY_LEFT_CONTROL	0xE0	//Left Control
#define	BP_KEY_LEFT_SHIFT	0xE1	//Left Shift
#define	BP_KEY_LEFT_ALT		0xE2	//Left Alt
#define	BP_KEY_LEFT_GUI		0xE3	//Left GUI
#define	BP_KEY_RIGHT_CONTROL	0xE4	//Right Control
#define	BP_KEY_RIGHT_SHIFT	0xE5	//Right Shift
#define	BP_KEY_RIGHT_ALT	0xE6	//Right Alt
#define	BP_KEY_RIGHT_GUI	0xE7	//Right GUI
#define	BP_KEY_F1	0x3A	//F1
#define	BP_KEY_F2	0x3B	//F2
#define	BP_KEY_F3	0x3C	//F3
#define	BP_KEY_F4	0x3D	//F4
#define	BP_KEY_F5	0x3E	//F5
#define	BP_KEY_F6	0x3F	//F6
#define	BP_KEY_F7	0x40	//F7
#define	BP_KEY_F8	0x41	//F8
#define	BP_KEY_F9	0x42	//F9
#define	BP_KEY_F10	0x43	//F10
#define	BP_KEY_F11	0x44	//F11
#define	BP_KEY_F12	0x45	//F12


//KEYBOARD MODEFIER CODES
#define BP_MOD_RIGHT_GUI	(1<<7)
#define BP_MOD_RIGHT_ALT	(1<<6)
#define BP_MOD_RIGHT_SHIFT	(1<<5)
#define BP_MOD_RIGHT_CTRL	(1<<4)
#define BP_MOD_LEFT_GUI		(1<<3)
#define BP_MOD_LEFT_ALT		(1<<2)
#define BP_MOD_LEFT_SHIFT	(1<<1)
#define BP_MOD_LEFT_CTRL	(1<<0)
#define BP_MOD_NOMOD		0x00

//Mouse Codes
#define BP_MOUSE_BTN_LEFT	(1<<0)
#define BP_MOUSE_BTN_RIGHT	(1<<1)
#define BP_MOUSE_BTN_MIDDLE	(1<<2)

//GAMEPAD/JOYSTICK BUTTON CODES
//ST == First button combination (BTN0 to BTN7)
#define BP_GAMEJOY_ST_BTN0	(1<<0)
#define BP_GAMEJOY_ST_BTN1	(1<<1)
#define BP_GAMEJOY_ST_BTN2	(1<<2)
#define BP_GAMEJOY_ST_BTN3	(1<<3)
#define BP_GAMEJOY_ST_BTN4	(1<<4)
#define BP_GAMEJOY_ST_BTN5	(1<<5)
#define BP_GAMEJOY_ST_BTN6	(1<<6)
#define BP_GAMEJOY_ST_BTN7	(1<<7)
#define BP_GAMEJOY_ST_NOBTN	0x00

//ND = Second button combination (BTN0 to BTN7)
#define BP_GAMEJOY_ND_BTN0	(1<<0)
#define BP_GAMEJOY_ND_BTN1	(1<<1)
#define BP_GAMEJOY_ND_BTN2	(1<<2)
#define BP_GAMEJOY_ND_BTN3	(1<<3)
#define BP_GAMEJOY_ND_BTN4	(1<<4)
#define BP_GAMEJOY_ND_BTN5	(1<<5)
#define BP_GAMEJOY_ND_BTN6	(1<<6)
#define BP_GAMEJOY_ND_BTN7	(1<<7)
#define BP_GAMEJOY_ND_NOBTN	0x00


class BPLib
{
public:
  BPLib(Stream &port, int pin = -1);
  byte begin(char BP_Mode[], char BP_Type[]);
  byte sendCmd(char BP_CMD[]);
  void sendByte(byte rawData);
  void sendChar(char rawData);
  void sendInt(int rawData);
  void sendFloat(float rawData);
  void sendLong(long rawData);
  void sendString(char rawData[]);
  byte readRaw();
  int available();
  //Keyboard
  void keyboardPrint(char BP_MSG[]);
  void keyboardPress(byte BP_KEY,byte BP_MOD);
  void keyboardReleaseAll();
  // Mouse
  void mouseClick(byte BP_BUTTON);
  void mouseMove(signed int BP_X,signed int BP_Y);
  void mouseWheel(signed int BP_WHEEL);
  void mousePress(byte BP_BUTTON);
  void mouseReleaseAll();
  // Consumer
  void volumeUp();
  void volumeDown();
  void muteAudio();
  void playPause();
  void nextTrack();
  void prevTrack();
  void stopAudio();
  void fastForwardAudio();
  void rewindAudio();
  void keyRelease();
  void sendConsumerCommand(byte lowByte, byte highByte);
  // GamePad
  void gameJoyPress(byte BP_ST_BTN, byte BP_ND_BTN);
  void gameJoyMove(signed int BP_X1,signed int BP_Y1,signed int BP_X2,signed int BP_Y2);
  void gameJoyReleaseAll();
  int connected();
  byte changeName(char BP_NAME[]);
private:
  Stream *serialInterface;
  int statusPin;
  byte get(char BP_STAT[], byte strlen);
};
#endif

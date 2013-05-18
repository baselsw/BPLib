BPLib - Bluetooth SPP/HID Library
=====

This library simplifies the communication protocol between the RN-42 (HID enabled) device and the atmega32u4.
Some functions won't work on for example (Arduino(R) Leonardo) because there is some hardware mods between the module
and the atmega32u4. One of these functions/statements is the "connected()" statement in the library.

The library is written with arduino statements (like Serial.begin(), etc) inorder to make the code very
simple/understandable/editable to a Arduino IDE newcomer.

The library isn't complete, todo list:

- Add, authorization mode: Toggle between an Open/Pin Locked connection.
- Add, more keyboard scan codes
- Add, software connection check (to support Arduino Uno/Leonardo/Mega)

Working with following boards:
- BlueNar One
- Arduino(R) Leonardo (One function doesn't work, everything else AOK)

The library will work with the following BT protocols:
- SPP (Bluetooth Serial)
- HID (Bluetooth Human Interface Device)
  - Keyboard
  - Mouse
  - Combo (Keyboard + Mouse)
  - Joystick
  - Gamepad

For example code, see the examples directory

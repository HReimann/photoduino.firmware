           _                          _       _             
          | |           _            | |     (_)            
     ____ | |__   ___ _| |_  ___   __| |_   _ _ ____   ___  
    |  _ \|  _ \ / _ (_   _)/ _ \ / _  | | | | |  _ \ / _ \ 
    | |_| | | | | |_| || |_| |_| ( (_| | |_| | | | | | |_| |
    |  __/|_| |_|\___/  \__)\___/ \____|____/|_|_| |_|\___/ 
    |_|  THE OPENSOURCE CAMERA CONTROLLER BASED ON ARDUINO                                                         



#Photoduino firmware

This code is the firmware for Photoduino Shields (1.0, 2.0 and 3.0 hardware versions) as Arduino Sketch.

Visit the project site: <http://www.photoduino.com>

* * *

## How to upload firmware to the board

### DOWNLOADS

  1. Download the zip with the Arduino sketch of latest Photoduino firmware: http://www.photoduino.com/downloads
  2. Download the latest version of the Arduino development environment: http://arduino.cc/en/Main/

### PREPARE

  1. **Unzip the downloaded Arduino environment.**
     You will find two things. The installer of the environment and the drivers for the FTDI chip that 
     carries Arduino to connect to USB. You should install both.

  2. **Unzip the downloaded firmware.**
     Is very important that all files are together in a folder called "Photoduino", if not, rename it.

  3. You must **connect the Arduino board** to your computer via USB.

  4. **Open the Arduino environment** you have installed.

  5. In the Arduino environment, **go to menu "Tools->Board" and select your arduino model**.

  6. In the Arduino environment, **go to menu "Tools->Serial Port" and select the port of arduino**.


### COMPILING AND UPLOADING THE FIRMWARE

  1. In the Arduino environment **go to menu "File-> Open ..." and select the file "Photoduino.pde"** in 
     the unzipped firmware folder. This will open as tabs each of the firmware files in the folder.

  2. Click the "Verify" or **go to the "Sketches"> Verify / Compile ... "**

  3. In the black area at the bottom **should not appear any error**. Only white text. 
     **If the text is red are errors** and you should check the name of the folder as explained above.

  4. If all goes fine, you can **press the button "Upload" or go to the menu "File-> Upload to IO board"** and wait to finish. 

  5. The environment **will tell you about everything on the console** (bottom box with black background)

### FINISHED

  * If all goes well, you have the firmware loaded on your plate and you should hear one beep.
  * If not text appears on the LCD screen, adjust the contrast potentiometer.

* * *

##Firmware changelog:
 
##release 0.10 (current development)

 - All files use ".ino" file extension for the 1.0 Arduino environment
 - Fix compile errors on Arduino 1.0 environment
 - No use progmem for allocate strings in program memory and reduce compiled code size
 - New progress bar interface element
 - Added confirmation message when you reset config in any execution mode to avoid accidental losses
 - Fixed some messages spelling errors
 - Now the shutterlag is a system parameter because it depends of the camera model and is the same in all the run modes. 
 - Now Useflash1 and Useflash2 are system parameters. If p.e. UseFlash2 is "NO", then in the config menus of all run modes you will don't see the "flash2 pretime".
 - Now, the language messages are in separated files for each language to improve future translations.
 - Mirror lockup timeout is now configurable throught the system menu.
 - New system parameter "DEVICE PORT TYPE" determines the use of the Device port like laser, electrovalve, ...
 - A big new functionality of control electrovalve. Docs soon.
 - New key input holding A+B buttons to use it in numeric sensor tunning to match sensor and limit values to equal.
  
 
##release 0.9 

 - Added new "Mirror lockup" functionality in all sensor modes
 - Added new "Numeric mode" for tuning sensor limit with more precision. 
 - Added compatibility with ArduinoMega by "#define BOARD_ARDUINO_MEGA".
 - Default interval time is now 1 second instead 1000 miliseconds because 
   is more common used.
 - Added a compile value to define the pulse width for shooting the flash.
 - Some other minor fixes and code reviews.  
 
##release 0.8

 - Bug fixed on some cameras like canon 50d with prebulb yes. 
 
##release 0.7 

 - Bug fixed on shutterEnd with prebulb yes. 
  
##release 0.6 

 - New mode "Flash slave" uses the LDR sensor to shoot the flashes like a 
   slave flash.
 - Now all text messages are defines to make posible the i18n. 
   Current available languages are spanish and english
 - Fixed a bug with cycles on intervalmode
 
##release 0.5 

 - Now each sensor have a run mode and custom config
 - New parameter "cycles" also on sensor trigger modes
 - New parameter "intercicle time" added on sensor trigger modes for wait
   between cycles to let the camera time to process the photo or avoid shoots
   by noise on sensors.
 - Removed all "exit" options from menus to reduce code size and simplify. 
   Use hold-A-button to exit.
 - Added power on/off control of a laser connected to the RESERVED port. 
   Laser is set power-off before open the camera shutter.
 - Re-organization of .pde files
 - Many code improvements to reduce code size and enhace the organization
 
##release 0.4

 - Keyboard reading is completly re-writed code to enhance control and use 
   debounce and hold time
 - Revision of code comments
 - added reference of default shutterlag times for canon DSLR cameras
 - (function setSensorLimit) now uses two buttons for up and down the value
  
##release 0.3

 - (function setIntValue) Bug fixed when sets numeric values higher than 59999 
 - (function setIntValue) Numeric values now uses two buttons for up and down 
 - (function setIntValue) Now shows the measure units
 - (PINS_BTN_A and PINS_BTN_B) Interchanged to be the same reference in silkscreen
 - (function keyScan) Bug fixed
 
##release 0.2

 - New file organization
 - Various improvements
 - Configuration backup on eeprom
 

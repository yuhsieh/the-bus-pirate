v0f
I. Upgrade only
II. New installs
III. History

I. Upgrade only
If your Bus Pirate already has a bootloader programmed, follow these steps to load the new firmware.
1. Place a jumper between the PGC and PGD pins of the programming header. This will trigger the bootloader mode.
2. Connect the Bus Pirate to a USB port (or, if applicable, power and serial cable).
3. Start the MS Windows P24QP.exe programmer utility included in this archive. You may need to modify the COM port (portindex=) in P24qp.ini to match your system.
4. Click the connect to device icon. The program should detect and connect to the PIC.
5. Click the folder icon and open the firmware update file (vxx-Firmware for BL.hex).
6. Click the erase device icon to erase the chip. DO NOT SKIP THIS STEP.
7. Click the write device icon to program the new firmware. 
8. Ignore any verify errors between 0x400 and 0xBFF, this is where the bootloader lives.
9. Click the green arrow icon (normal execution mode) to exit the bootloader and start the program.
10. Remove the jumper from the PGC and PGD pins, or move it over one position to connect the inner PGx pin to GND.
11. ***IMPORTANT*** Now restart the Bus Pirate by disconnecting and reconnecting the USB cable (or power cable). Some features won't work until after a complete hardware reset.

II. New installs
If you're starting with a blank chip, follow these steps to load the firmware. 
1. Connect the Bus Pirate to a USB port (or, if applicable, power and serial cable).
2. Program the PIC with the bootloader HEX file through the 5pin ICSP header (vxx-PIC Bootloader.hex).
3. Disconnect the programing cable. DO NOT SKIP THIS STEP.
4. Start the MS Windows P24QP.exe programmer utility included in this archive. You may need to modify the COM port (portindex=) in P24qp.ini to match your system.
5. Click the connect to device icon. The program should detect and connect to the PIC.
6. Click the folder icon and open the firmware update file (vxx-Firmware for BL.hex).
7. Click the erase device icon to erase the chip. DO NOT SKIP THIS STEP.
8. Click the write device icon to program the new firmware. 
9. Ignore any verify errors between 0x400 and 0xBFF, this is where the bootloader lives.
10. Click the green arrow icon (normal execution mode) to exit the bootloader and start the program.
11. ***IMPORTANT*** Now restart the Bus Pirate by disconnecting and reconnecting the USB cable (or power cable). Some features won't work until after a complete hardware reset.

***You DO NOT need to use a jumper between PGC and PGD on a new install, a fresh bootloader on a blank chip waits forever to connect to the programmer utility. 

III. History
v0f is the first version that uses the PIC24 bootloader. 
Use/upgrade to v0g bootloader if possible.
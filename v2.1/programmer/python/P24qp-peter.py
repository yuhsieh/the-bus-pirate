"""
A python based programmer for the AN1157 serial bootloader from Microchip [1].
This file acts either as a standalone application or it can be used as a
library for developing your own applications.

The library depends on and makes use of the pyserial library[2]  licensed
under the terms of the Python license.
The author hereby thanks the pyserial project for this great piece of software.

If you have any questions/suggestions concerning the code, don't hesitate
to contact me.
Moreover I would be glad if I receive some feedback about your experiences with
the tool and some details of the products you have used the programmer.

WARNING:
Use this software at your own risk!
   -> I managed to (temporarily) brick one of my PICs!
You have been warned.


All trademarks are the property of their respective owners.

References:
[1] http://www.microchip.com/stellent/idcplg?IdcService=SS_GET_PAGE&nodeId=1824
&appnote=en533906
[2] http://pyserial.sourceforge.net/

Copyright (C) 2009  Peter Huewe <peterhuewe #at# gmx #dot# de>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
"""



import serial
import sys
class PIC24FFirmwareFlasher:
    """ Class for accessing the features of Microchips serial bootloader based
    on Aplication Note AN1157 for PIC24 based devices

    If the STX,ETX,DLE values are set correctly this class should also work
    with PIC8 and PIC16 based devices (untested)

    Fully supported:
    * Read Bootloader Version

    Partially supported:
    * generic read/writes with automatic checksum calculation

    For bugs see bugs() below.
    """

    def __init__(self, port="/dev/ttyUSB0", baudrate=9600, timeout=3,
            STX="\x55", ETX="\x04", DLE="\x05"):
        """ Constructor for the class:
            baudrate can be set up to 115200, however 9600 is the safest value
            timeout should  NOT be set to 0
            STX, ETX, DLE can be set to the values according to the application
            note of the bootloader you use
            * AN1157 - PIC24 based devices -> STX="\x55", ETX="\x04", DLE="\x05"
            * AN851 - PIC 8/16 based devices -> STX="\x0f", ETX="\0x04", DLE="\x05"
        """
        self.STX = STX
        self.ETX = ETX
        self.DLE = DLE
        if timeout == 0:
            print "WARNING: timeout=0 is not supported by bootloader!"

        try:
            self.ser = serial.Serial(port, baudrate, timeout=timeout)
        except serial.serialutil.SerialException:
            print "The serial port %s does not exist or an error occured while\
                    connecting to it" % port
            print "the original error message was "
            raise

    def calculateChecksum(self, data):
        """ Calculates the checksum for the data only (stx / etx excluded)
        returns the checksum as an integer - insert using %x
        """
        chksum = 0
        for i in map(ord, data):
            if i == 0x05:# skip only first!
                continue
            chksum += i

        #chksum=reduce (lambda x,y: x+y, map(ord,data)) # calculate sum
        chksum = ((~(chksum)+1)&0xFF)#create 2's complement of lower byte
        print hex(chksum)
        return chksum

    def writeCommand(self, data):
        """ Write a command to the device  - the data has to be hexvalues
        encoded as a string by using \\xVV
        STX and ETX are added
        """
        command = self.STX
        command += self.STX
        command += "".join(data)#meeep! FIXME -- add 0x05 for each special command
        tmp = self.calculateChecksum(data)
        if(tmp == self.STX or tmp == self.ETX or tmp == self.DLE):
            #escape special chars -'byte stuffing'
            command += self.DLE
        command += chr(tmp)
        command += self.ETX
        self.ser.write(command)



    def readData(self):
        """ Read data from the device  - some parsing of the output is done,
        and the checksum is checked.
        only the raw values (without the echo and etx/checksum) is returned"""
        data = ""
        tmp = self.ser.read(1) # stx
        if tmp != self.STX:
            print "Error receiving first STX start command"
            return
        tmp = self.ser.read(1) # stx
        if tmp != self.STX:
            print "Error receiving second STX start command"
            return
        data += self.ser.read(2) # command +  LEN or CHECKSUM
        if(data[0] == self.ETX):
            return self.ETX # device resetted? - guess this is dead code (tm)

        if data[0] == "\x00" and data[1] == "\x02":
            data += self.ser.read(2) # VERL VERH
            print "bootloader"


        if data[0] == "\x02" or data[0] == "\x03" or data[0] =="\x05" or data[0] =="\x07" or data[0] =="\x08" :
            data += self.ser.read(1) # checksum already read -> ETX
        else:
            data += self.ser.read(2) # checksum +  ETX
        if ord(data[-2]) != self.calculateChecksum(data[:-2]):
            print "received wrong checksum"
            print "checksum was %x and should be %x" % (ord(data[-2]), self.calculateChecksum(data[:-2]))
        if data[-1] != self.ETX:
            print "Error receiving ETX end command"
        return data[2:-2]



    def printBootloaderVersion(self):
        """Prints the bootloader version to the screen """
        self.writeCommand("\x00\x02")
        version = self.readData()
        print "Bootloader Version: %x.%x " % (ord(version[0]), ord(version[1]))



def showusage():
    """ usage information """
    print "python an1157.py"
    print "\t --usage show this information"
    print "\t --help show this information"
    print "\t --version show version information"
    print "\t --bugs show known bugs"
    print "Without any option the the bootloader version will be displayed"

def showbugs():
    """ show currently known bugs """
    print "* Data with special values like STX ETX and DLE has to be escaped"
    print "* Bug in checksum calculation when value is DLE 0x05"
    print "* read command not fully implemented"




def showhelp():
    """ usage information """
    showusage()

def showversion():
    """ version information """
    print "Version v.0.1-20090731"
    print "Copyright (C) 2009  Peter Huewe <peterhuewe #at# gmx #dot# de>"
    print """
   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.
   """
    print "USE AT YOUR OWN RISK - you have been warned"



if __name__ == '__main__':
    if len(sys.argv) > 1:
        if sys.argv[1] == "--usage":
            showusage()
        elif sys.argv[1] == "--help":
            showhelp()
        elif sys.argv[1] == "--bugs":
            showbugs()
        elif sys.argv[1] == "--version":
            showversion()
        else:
            myFF = PIC24FFirmwareFlasher()
            myFF.printBootloaderVersion()
    else:
        myFF = PIC24FFirmwareFlasher()
        myFF.printBootloaderVersion()

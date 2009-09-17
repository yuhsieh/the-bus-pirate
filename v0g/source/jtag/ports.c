/*******************************************************/
/* file: ports.c                                       */
/* abstract:  This file contains the routines to       */
/*            output values on the JTAG ports, to read */
/*            the TDO bit, and to read a byte of data  */
/*            from the prom                            */
/*                                                     */
/*******************************************************/
#include "ports.h"
#include "../base.h"
#include "../jtag.h"

static unsigned char buf[100]; //buffer to hold incoming bytes
static unsigned int cnt=0, bufCnt=0, bufMax=0;

unsigned char bm(void){return bufMax;}

void ereset(void){
	cnt=0;bufCnt=0;bufMax=0;
	JTAGTDI_TRIS=0;
	JTAGTCK_TRIS=0;
	JTAGTD0_TRIS=1;
	JTAGTMS_TRIS=0;
}

/* if in debugging mode, then just set the variables */
//need to bring into compliance with hiz structure
void setPort(short p,short val){
    if (p==TMS) {JTAGTMS = (unsigned char) val;}//  bpDelayUS(10);}
    if (p==TDI) {JTAGTDI = (unsigned char) val;}//  bpDelayUS(10);}
    if (p==TCK) {JTAGTCK = (unsigned char) val;}//  bpDelayUS(50);}
}



void uartXon(void){UART1TX(0x11);}

/* read in a byte of data*/
/**********************
*
*
*	The code was intened to read from a static source, but 
*	we use the serial port. 
*	The JTAG routines have significant delays, and we'll get garbage
*	data from the serial port without flow control.
*	Even with software flow control, it takes a dozen or more bytes
*  before the data stops coming
*	This routine grabs a group of bytes with one XON/XOFF command. then 
*	returns them until the buffer is empty.
*
**************************/
void readByte(unsigned char *data){
	unsigned char i;

	//if the buffer read pointer and the buffer byte counter are equal, we need to grab more bytes
	if(bufCnt==cnt){
		bufCnt=0;
		cnt=0;	
		bufMax=0;
		//check overrun
		if(U1STAbits.OERR==1){
			bpWstring("BUFFEROVERRUN ERROR, DATA TOO FAST!!!\x0D\x0A");
			U1STAbits.OERR=0;
		}

		//software flow control
		UART1TX(0x11);	//send XON 0x11
	
		while(U1STAbits.URXDA == 0); //wait for byte

		//now get bytes as long as the host cares to spit them out
		//windows seems to send about 15 more bytes, depending
		//We do this a total of 3 times to make absolutly certain that we have all the bytes
		//without this 3x loop we got tons of errors above 57600bps, 
		//with this we can go to 115200 with no signal switching delays in setPort (above)
		for(i=0;i<3;i++){	
			UART1TX(0x13);//send xoff. This delays one byte time....
		
			while(U1STAbits.URXDA == 1){
				UART1TX(0x13); 	//send XOFF 0x13 (delay 1 byte time...)
				buf[cnt]=U1RXREG;
				cnt++;	
				if(cnt==sizeof(buf)){
					//bigger than buffer, XON/XOFF not configured?
					bpWstring("BUFFER ERROR, IS XON/XOFF FLOW CONTROL ENABLED?\x0D\x0A");
					break;
				}							
			}
		}
		if(cnt>bufMax){bufMax=cnt;}
	}

	(*data)=buf[bufCnt];
	bufCnt++;		
}

/* read the TDO bit from port */
unsigned char readTDOBit(){return JTAGTDO;}


/* Wait at least the specified number of microsec.                           */
/* Use a timer if possible; otherwise estimate the number of instructions    */
/* necessary to be run based on the microcontroller speed.  For this example */
/* we pulse the TCK port a number of times based on the processor speed.     */
void waitTime(long microsec){
    long i;

    /* For systems with TCK rates >= 1 MHz;  This implementation is fine. */
    for ( i = 0; i < microsec; ++i ){
        bpDelayUS(1);
    }
}

//this DOES NOT work with the PIC 24Fj64GA002
//there is an error in revision 3 silicon
//with the I2C1 module
//no work around
// we'll use a dspic in a future revision, but stuck to the software routine for now.
//http://forum.microchip.com/tm.aspx?m=271183&mpage=1
#include "I2Cb.h"
#include "base.h"

extern struct _set settings;

void hwi2cSetup(void);
void hwi2cstart(void);
void hwi2cstop(void);
unsigned char hwi2cgetack(void);
void hwi2cwrite(unsigned char c);
unsigned char hwi2cread(void);

static unsigned char I2Cspeed[]={157,37,13};//100,400,1000khz; datasheet pg 145

void hwi2cProcess(unsigned char cmd, unsigned char val){
	static unsigned char c;
	static unsigned int i;

	switch(cmd){
		case CMD_PRESETUP:
			//set the options avaiable here....
			settings.allowHiZ=0;
			settings.allowlsb=0;
#ifdef BUSPIRATEV0A
			settings.allowpullup=1; 
#endif
			bpWstring("Set speed:\x0D\x0A 1. 100KHz\x0D\x0A 2. 400KHz\x0D\x0A 3. 1MHz\x0D\x0A SPEED>");
			settings.speed=(bpGetMenuReply(3)-1);
			break;
		case CMD_SETUP:
			hwi2cSetup();
			bpWline("x02 HWI2C READY");
			break;
		case CMD_CLEANUP:
			//disable I2C module
			I2C1CONbits.I2CEN = 0;
			break;
		case CMD_STARTR:
		case CMD_START:
			// Enable a start condition
			hwi2cstart();
			bpWline("x10 HWI2C START");
			break;
		case CMD_STOP:
			hwi2cstop();
			bpWline("x40 HWI2C STOP");
			break;
		case CMD_READ:
			bpWstring("x30 HWI2C READ: ");
			c=hwi2cread();
			bpWbyte(c);
			bpWstring("\x0D\x0A");
			break;
		case CMD_READBULK:
			bpWstring("131 SPI BULK READ, ");	
			bpWbyte(val);
			bpWstring(" BYTES:\x0D\x0A");
			for(i=0;i<val;i++){	
				bpWbyte(hwi2cread());
				UART1TX(0x20);//space
			}
			bpWstring("\x0D\x0A");
			break;
		case CMD_WRITE:
			bpWstring("x20 HWI2C WRITE: ");
			bpWbyte(val);
			hwi2cwrite(val);
			if(hwi2cgetack()==0){
				bpWline(" GOT ACK: YES");
			}else{
				bpWline(" GOT ACK: NO");			
			}
			break;
		case CMD_MACRO:
			switch(val){
				case 0://menu
					bpWstring(" 0.Macro menu\x0D\x0A 1.7bit address search\x0D\x0A 2.10bit address search\x0D\x0A");
					break;
				case 1:
					bpWline("xxx Searching 7bit I2C addresss space. \x0D\x0A   Found devices at:");
					for(i=0;i<0x100;i++){
						hwi2cstart();
			 			hwi2cwrite(i);
						if(hwi2cgetack()==0){
							bpWbyte(i);
							bpWstring(" ");		
						}
						hwi2cstop();
					}
					bpWstring("\x0D\x0A");	
					break;
				case 2:
				default:
					bpWstring("xxx NO SUCH MACRO IN THIS MODE\x0D\x0A");
			}
			break;
		default:
			bpWstring("70 COMMAND NOT IMPLEMENTED IN THIS MODE\x0D\x0A");
	}

}
void hwi2cstart(void){
	// Enable a start condition
	I2C1CONbits.SEN = 1;
	while(I2C1CONbits.SEN==1);//wait
}

void hwi2cstop(void){
	I2C1CONbits.PEN = 1;
	while(I2C1CONbits.PEN==1);//wait
}

unsigned char hwi2cgetack(void){
	return I2C1STATbits.ACKSTAT;
}

void hwi2cwrite(unsigned char c){
	I2C1TRN=c;
	while(I2C1STATbits.TRSTAT==1);
}

unsigned char hwi2cread(void){
	unsigned char c;
	I2C1CONbits.RCEN=1;
	while(I2C1CONbits.RCEN==1);
	c=I2C1RCV;
	I2C1CONbits.ACKDT=0;//send ACK, not NACK?
	I2C1CONbits.ACKEN=1;
	while(I2C1CONbits.ACKEN==1);
	return c;
}

void hwi2cSetup(void){

	I2C1CONbits.A10M=0;
	I2C1CONbits.SCLREL=0;

	I2C1ADD=0;
	I2C1MSK=0;

	// Enable SMBus 
	I2C1CONbits.SMEN = 0; 

	// Baud rate setting
	I2C1BRG = I2Cspeed[settings.speed];
	
	// Enable I2C module
	I2C1CONbits.I2CEN = 1;
	
	//NICE TRY, BUT NO CIGAR
	//for revision 3, the SDA has to be hit once manually before
	//it will work, we use the connected pullup resistor to jump start
	//the broken hardware module.
	bpDelayUS(200);
	LATBbits.LATB11=0;//hold to ground
	TRISBbits.TRISB11=0;//SDA Pullup
	bpDelayUS(250);
	TRISBbits.TRISB11=1;//SDA Pullup
	LATBbits.LATB11=1;//release


}


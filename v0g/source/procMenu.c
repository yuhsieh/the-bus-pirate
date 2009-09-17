/*
 * This file is part of the Bus Pirate project (buspirate.com).
 *
 * Originally written by hackaday.com <legal@hackaday.com>
 *
 * To the extent possible under law, hackaday.com <legal@hackaday.com> has
 * waived all copyright and related or neighboring rights to Bus Pirate. This
 * work is published from United States.
 *
 * For details see: http://creativecommons.org/publicdomain/zero/1.0/.
 *
 *    This program is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 */
#include "base.h"
#include "AUXpin.h"
#include "busPirateCore.h"
#include "procMenu.h" //need our public versionInfo() function

extern struct _bpConfig bpConfig;
extern struct _modeConfig modeConfig;

void setMode(void); //change protocol/bus mode
void setDisplayMode(void); //user terminal number display mode dialog (eg HEX, DEC, BIN, RAW)
void setPullups(void); //pullup resistor dialog
void measureSupplyVoltages(void); //display supply voltage measurements for 3.3, 5, and vpullup
void setBitOrder(void); //LSB/MSB menu for modes that allow it
void setAltAuxPin(void); //configure AUX syntax to control AUX or CS pin
void setBaudRate(void); //configure user terminal side UART baud rate
void statusInfo(void); //display properties of the current bus mode (pullups, vreg, lsb, output type, etc)
void easterEgg(void);

//check byte c for valid menu commands, 0=no menu commands
unsigned char checkMenuCommand(unsigned char c){

	if((c>0x60) && (c<0x7b)){c-=0x20;}//change lowercase to uppercase
	switch(c){//check for command codes
		case MENU_BUSMODE://set protocol
			setMode();
			break;
		case MENU_DISPLAYMODE://set output format
			setDisplayMode();
			break;	
		case MENU_PULLUPS: //pullups
			#if defined( BUSPIRATEV0A) || defined( BUSPIRATEV2)
				//don't allow pullups on some modules. also: V0a limitation of 2 resistors
				if(modeConfig.allowpullup==0){bpWmessage(MSG_ERROR_MODE);break;}//is it allowed?
				setPullups();
			#elif defined(BUSPIRATEV1A)
				bpWline("SUPPLY CONFIG DEPRICATED, USE W/w TO TOGGLE BOTH");
			#endif
			break;
		#if defined( BUSPIRATEV1A) || defined (BUSPIRATEV2)
		case MENU_VMONITOR://take voltage reading
			measureSupplyVoltages();
			break;
		#endif
		case MENU_BITORDER://config sig bit first
			setBitOrder();
			break;
		case MENU_HELP: //show help
			printHelp(); //moved to baseUI.c for easy translation
			break;
		case MENU_FREQMEASURE://measure frequency on AUX pin
			bpFreq();
			break;
		case MENU_FREQGENERATE://generate frequency on AUX pin
			bpPWM();
			break;
		case MENU_VERSIONINFO://display version info
			versionInfo();//display hardware and firmware version string
			if(bpConfig.busMode==HIZ){			
				//enable timer 1 with interrupts, 
				//service with function in main.c.
				//IEC0bits.T1IE = 1;
				//IFS0bits.T1IF = 0;
				//PR1 = 0xFFFF;
				//T1CON = 0x8010;
			}else{
				statusInfo();
			}
			break;
		case MENU_AUXPIN://change aA@ to control AUX or CS/TMS
			//don't allow changes in HiZ mode
			if(bpConfig.busMode==HIZ){bpWmessage(MSG_ERROR_MODE);break;}//are we in a mode?
			setAltAuxPin();
			break;
		case MENU_BAUDRATE://configure the PC side speed
			setBaudRate();
			break;
		case '=':
			easterEgg();
			break;
		default:
			return 0;//no commands
	}
	return 1;
}

//
//
// 	HELPER FUNCTIONS FOR MENU OPTIONS
//
//

//print version info (used in menu and at startup in main.c)
void versionInfo(void){
	bpWline(BP_VERSION_STRING);
	bpWline("http://www.buspirate.com");
	bpWline(BP_FIRMWARE_STRING);
}

//display properties of the current bus mode (pullups, vreg, lsb, output type, etc)
void statusInfo(void){
	bpWline("*----------*");

	#if defined (BUSPIRATEV1A) || defined (BUSPIRATEV2)
	//vreg status 
	if(modeConfig.vregEN==1) bpWmessage(MSG_VREG_ON); else bpWmessage(MSG_VREG_OFF);
	//voltage report
	measureSupplyVoltages();
	#endif
	
	//AUX pin setting
	if(modeConfig.altAUX==1) bpWmessage(MSG_OPT_AUXPIN_CS); else bpWmessage(MSG_OPT_AUXPIN_AUX);

	//open collector outputs?
	if(modeConfig.HiZ==1) bpWmessage(MSG_STATUS_OUTPUT_HIZ); else bpWmessage(MSG_STATUS_OUTPUT_NORMAL);
	
	//pullups available, enabled?
	#if defined (BUSPIRATEV1A) || defined (BUSPIRATEV2)
	if(modeConfig.allowpullup==1){
		if(modeConfig.pullupEN==1) bpWmessage(MSG_OPT_PULLUP_ON); else bpWmessage(MSG_OPT_PULLUP_OFF);
	}else{
		bpWmessage(MSG_STATUS_PULLUP_NOTALLOWED);
	}
	#endif
	
	//bitorder toggle available, enabled
	if(modeConfig.allowlsb==1){
		if(modeConfig.lsbEN==1) bpWmessage(MSG_OPT_BITORDER_LSB); else bpWmessage(MSG_OPT_BITORDER_MSB);
	}else{
		bpWmessage(MSG_STATUS_BITORDER_NOTALLOWED);
	}

	bpWline("*----------*");

}

//change protocol/bus mode
//cleans from previous mode and initializes new mode
void setMode(void){
	unsigned char i,j;

	bpProcess(CMD_CLEANUP, 0,0);//deactivate anything from the last module			
	bpInit();//clean up
	j=bpNumBusModes();
	for(i=0; i<j; i++){	
		bpWdec(i+1);
		bpWstring(". ");
		bpEchoBusMode(i);//ends line
		bpWBR;
	}

	bpConfig.busMode=(bpUserNumberPrompt(2, j, 1)-1);

	bpWmessage(MSG_OPT_MODESET);

	bpProcess(CMD_PRESETUP, 0,0);

	BP_LEDMODE=1;//light MODE LED

	bpProcess(CMD_SETUP, 0,0); 	//use settings....
}

//user terminal number display mode dialog (eg HEX, DEC, BIN, RAW)
void setDisplayMode(void){
	bpWmessage(MSG_OPT_DISPLAYMODE); //show the display mode options message			
	bpConfig.displayMode=(bpUserNumberPrompt(1, 4, 1)-1); //get, store user reply
	bpWmessage(MSG_OPT_DISPLAYMODESET);//show display mode update text
}

//pullup resistor dialog
#ifndef BUSPIRATEV1A
void setPullups(void){

	//warn if using pullups with non-hiz pin settings
	if(modeConfig.HiZ==0){bpWmessage(MSG_ERROR_NOTHIZPIN);}

	bpWmessage(MSG_OPT_PULLUP);	//show pullup menu	
	modeConfig.pullupEN=(bpUserNumberPrompt(1, 2, 1)-1); //get user reply		
	if(modeConfig.pullupEN==0){ //pullup OFF
		BP_PULLUP_OFF(); //pseudofunction in hardwarevx.h
		bpWmessage(MSG_OPT_PULLUP_OFF);
	}else{//pullup ON
		BP_PULLUP_ON();
		bpWmessage(MSG_OPT_PULLUP_ON);
	}
}
#endif

//display supply voltage measurements for 3.3, 5, and vpullup
#ifndef BUSPIRATEV0A
void measureSupplyVoltages(void){
	unsigned int a;

	AD1CON1bits.ADON = 1; // turn ADC ON

	bpWmessage(MSG_OPT_VMONITOR);

	//set the pin to measure, 5 volts....
	a=bpADC(9);
	bpWstring("5V: ");
	bpWvolts(a);

	a=bpADC(10);
	bpWstring(" | 3.3V: ");
	bpWvolts(a);

	a=bpADC(11);
	bpWstring(" | VPULLUP: ");
	bpWvolts(a);

	bpWline(" |");
	AD1CON1bits.ADON = 0; // turn ADC OFF
}
#endif

//LSB/MSB menu for modes that allow it
void setBitOrder(void){
	
	//check if this is a valid option in the current mode
	if(modeConfig.allowlsb==0){bpWmessage(MSG_ERROR_MODE); return;}

	bpWmessage(MSG_OPT_BITORDER); //show stored dialog (see baseUI.c/h)				
	modeConfig.lsbEN=(bpUserNumberPrompt(1, 2, 1)-1); //get reply
	
	if(modeConfig.lsbEN==0){ //show stored message
		bpWmessage(MSG_OPT_BITORDER_MSB);	
	}else{
		bpWmessage(MSG_OPT_BITORDER_LSB);
	}
}

//configure AUX syntax to control AUX or CS pin
void setAltAuxPin(void){

	bpWmessage(MSG_OPT_AUXPIN);	//show stored dialog (see baseUI.c/h)			
	modeConfig.altAUX=(bpUserNumberPrompt(1, 2, 1)-1);
	
	if(modeConfig.altAUX==0){
		bpWmessage(MSG_OPT_AUXPIN_AUX);
	}else{
		bpWmessage(MSG_OPT_AUXPIN_CS);
	}
}

//configure user terminal side UART baud rate
void setBaudRate(void){
	unsigned char i;

	bpWmessage(MSG_OPT_TERMBAUD); //show stored dialog
	bpConfig.termSpeed=(bpUserNumberPrompt(1, 9, 9)-1);
	bpWmessage(MSG_OPT_TERMBAUD_ADJUST); //show 'adjust and press space dialog'
	while(U1STAbits.TRMT==0);//wait for TX to finish or reinit flushes part of prompt string from buffer
	InitializeUART1();
	while(1){ //wait for space to prove valid baud rate switch
    	while(U1STAbits.URXDA == 0); //new style with buffer
		i=U1RXREG; //return the byte
	    IFS0bits.U1RXIF = 0;
		if(i==0x20)break;
	}
}

char ee[]={
0x20, 0x20, 0x5F, 0x20, 0x20, 0x20, 0x5F, 0x20, 0x20, 0x20, 0x20, 0x20, 0x5F, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x5F, 0x5F, 0x5F, 0x5F, 0x20, 0x20, 0x20, 0x5F, 0x20, 0x20, 0x5F, 0x5F, 0x20, 0x20, 0x20, 0x20, 0x20, 0x5F, 0x5F, 0x20, 0x20, 0x5F, 0x5F, 0x20, 0x20, 0x55, 0x20, 0x5F, 0x5F, 0x5F, 0x5F, 0x5F, 0x20, 0x75, 0x20, 0x0D, 0x0A, 0x20, 0x7C, 0x27, 0x7C, 0x20, 0x7C, 0x27, 0x7C, 0x55, 0x20, 0x20, 0x2F, 0x22, 0x5C, 0x20, 0x20, 0x75, 0x55, 0x20, 0x2F, 0x22, 0x5F, 0x5F, 0x5F, 0x7C, 0x20, 0x7C, 0x22, 0x7C, 0x2F, 0x20, 0x2F, 0x20, 0x20, 0x20, 0x55, 0x7C, 0x27, 0x20, 0x5C, 0x2F, 0x20, 0x27, 0x7C, 0x75, 0x5C, 0x7C, 0x20, 0x5F, 0x5F, 0x5F, 0x22, 0x7C, 0x2F, 0x20, 0x0D, 0x0A, 0x2F, 0x7C, 0x20, 0x7C, 0x5F, 0x7C, 0x20, 0x7C, 0x5C, 0x5C, 0x2F, 0x20, 0x5F, 0x20, 0x5C, 0x2F, 0x20, 0x5C, 0x7C, 0x20, 0x7C, 0x20, 0x75, 0x20, 0x20, 0x20, 0x7C, 0x20, 0x27, 0x20, 0x2F, 0x20, 0x20, 0x20, 0x20, 0x5C, 0x7C, 0x20, 0x7C, 0x5C, 0x2F, 0x7C, 0x20, 0x7C, 0x2F, 0x20, 0x7C, 0x20, 0x20, 0x5F, 0x7C, 0x22, 0x20, 0x20, 0x20, 0x0D, 
0x0A, 0x55, 0x7C, 0x20, 0x20, 0x5F, 0x20, 0x20, 0x7C, 0x75, 0x2F, 0x20, 0x5F, 0x5F, 0x5F, 0x20, 0x5C, 0x20, 0x20, 0x7C, 0x20, 0x7C, 0x2F, 0x5F, 0x5F, 0x55, 0x2F, 0x7C, 0x20, 0x2E, 0x20, 0x5C, 0x5C, 0x75, 0x20, 0x20, 0x20, 0x7C, 0x20, 0x7C, 0x20, 0x20, 0x7C, 0x20, 0x7C, 0x20, 0x20, 0x7C, 0x20, 0x7C, 0x5F, 0x5F, 0x5F, 0x20, 0x20, 0x20, 0x0D, 0x0A, 0x20, 0x7C, 0x5F, 0x7C, 0x20, 0x7C, 0x5F, 0x7C, 0x2F, 0x5F, 0x2F, 0x20, 0x20, 0x20, 0x5C, 0x5F, 0x5C, 0x20, 0x20, 0x5C, 0x5F, 0x5F, 0x5F, 0x5F, 0x7C, 0x20, 0x7C, 0x5F, 0x7C, 0x5C, 0x5F, 0x5C, 0x20, 0x20, 0x20, 0x20, 0x7C, 0x5F, 0x7C, 0x20, 0x20, 0x7C, 0x5F, 0x7C, 0x20, 0x20, 0x7C, 0x5F, 0x5F, 0x5F, 0x5F, 0x5F, 0x7C, 0x20, 0x20, 0x0D, 0x0A, 0x20, 0x2F, 0x2F, 0x20, 0x20, 0x20, 0x5C, 0x5C, 0x20, 0x5C, 0x5C, 0x20, 0x20, 0x20, 0x20, 0x3E, 0x3E, 0x20, 0x5F, 0x2F, 0x2F, 0x20, 0x5C, 0x5C, 0x2C, 0x2D, 0x2C, 0x3E, 0x3E, 0x20, 0x5C, 0x5C, 0x2C, 0x2D, 0x2E, 0x3C, 0x3C, 0x2C, 0x2D, 0x2C, 0x2C, 0x2D, 0x2E, 0x20, 0x20, 0x20, 0x3C, 0x3C, 0x20, 0x20, 0x20, 0x3E, 0x3E, 0x20, 0x20, 
0x0D, 0x0A, 0x28, 0x5F, 0x22, 0x29, 0x20, 0x28, 0x22, 0x5F, 0x29, 0x5F, 0x5F, 0x29, 0x20, 0x20, 0x28, 0x5F, 0x5F, 0x29, 0x5F, 0x5F, 0x29, 0x28, 0x5F, 0x5F, 0x29, 0x5C, 0x2E, 0x29, 0x20, 0x20, 0x20, 0x28, 0x5F, 0x2F, 0x20, 0x20, 0x28, 0x2E, 0x2F, 0x20, 0x20, 0x5C, 0x2E, 0x29, 0x20, 0x28, 0x5F, 0x5F, 0x29, 0x20, 0x28, 0x5F, 0x5F, 0x29, 0x20, 
};
void easterEgg(void){bpWstring(ee);bpWBR;}

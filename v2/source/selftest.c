#include "base.h"
//#include "busPirateCore.h"

#ifdef BUSPIRATEV25
void bpTest(unsigned char p, unsigned char d);
void bpBusPinsTest(unsigned char d);
void bpADCPinTest(unsigned char a, unsigned int val);

void selfTest(void){
//instructions
//Connect PU, ADC to 5V
	bpWline("Disconnect any devices.");
	bpWline("Connect the Vpu pin to the +5V pin.");
	bpWline("Connect the ADC pin to the +3.3V pin.");
	bpWline("These results are experimental.");
	bpWline("Press any key to continue.");
	while(!UART1RXRdy());
	UART1RX();

	bpWline("Starting test.");

	bpWline("Control pin test...");
	BP_AUX=1;
	BP_AUX_DIR=0; 
	bpWstring("AUX PIN");
	bpTest(BP_AUX,1);
	BP_AUX=0;
	BP_AUX_DIR=1; 
				
	BP_LEDMODE=1;
	BP_LEDMODE_DIR=0;	
	bpWstring("MODE LED PIN");
	bpTest(BP_LEDMODE,1);
	BP_LEDMODE=0;
	BP_LEDMODE_DIR=1;
	
	BP_PULLUP_ON();
	bpWstring("PULLUP PIN H");
	bpTest(BP_PULLUP,1);
	BP_PULLUP_OFF();
	bpWstring("PULLUP PIN L");
	bpTest(BP_PULLUP,0);
	
	BP_VREG_ON();
	bpWstring("VREG PIN");
	bpTest(BP_VREGEN,1);

	//ADC check
	bpWline("Analog pin and power supply test...");
	AD1CON1bits.ADON = 1; // turn ADC ON

	//0x030F is 5volts
	bpWstring("5V");
	bpADCPinTest(9,0x250);

	//Vpullup is connected to 5volts
	bpWstring("VPULLUP");
	bpADCPinTest(11,0x250);

	//0x0208 is 3.3volts
	bpWstring("3.3V");
	bpADCPinTest(10,0x150);

	//ADC is connected to 3.3volts
	bpWstring("ADC");
	bpADCPinTest(12,0x150);

	AD1CON1bits.ADON = 0; // turn ADC OFF 

//*************
//
//  Test bus pins three ways, also tests on-board pullup resistors:
//	1. normal/high, 2. open collector ground, 3. open collector high.
//
//***************

//pullup off, pins=output & high, read input, high?
	bpWline("Bus pins, normal, high...");
	TRISB&= ~(0b1111000000);//output
	LATB|=0b1111000000; //high	
	bpDelayMS(100);
	bpBusPinsTest(1);

//pullup on, pins=output & low, read input, low?
	bpWline("Bus pins, open collector, low...");
	LATB&= ~(0b1111000000); //low
	BP_PULLUP_ON();
	bpDelayMS(100);
	bpBusPinsTest(0);

//pullup on, pins=input & low, read input, high?
	bpWline("Bus pins, open collector, high...");
	TRISB|= 0b1111000000;//output
	bpDelayMS(100);
	bpBusPinsTest(1);

	bpInit();//clean up

}

void bpADCPinTest(unsigned char a, unsigned int val){
	unsigned int b;
	bpWstring("(");
	b=bpADC(a);
	bpWvolts(b);
	bpWstring(")");
	bpTest(b>val,1);
}

//test that all bus pins are direction d
void bpBusPinsTest(unsigned char d){
	bpWstring("MOSI PIN");
	bpTest(BP_MOSI,d);
	bpWstring("CLK PIN");
	bpTest(BP_CLK,d);
	bpWstring("MISO PIN");
	bpTest(BP_MISO,d);
	bpWstring("CS PIN");
	bpTest(BP_CS,d);
}

//tests pin p for direction d
void bpTest(unsigned char p, unsigned char d){
	if(p==d) bpWline(" OK"); else bpWline(" FAIL");
}

#endif

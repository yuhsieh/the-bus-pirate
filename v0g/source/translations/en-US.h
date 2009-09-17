//note: not everything has been moved to the translation file...
/*struct _UImessages{
	enum {
		MSG2_READ="READ: ",
		MSG2_READBULK_T="BULK READ ",
	}char* message[];
}*/

#define MSG_READ_T 			"READ: "
#define MSG_READBULK_T		"BULK READ "
#define MSG_READBULK_BYTES_T " BYTES:\x0D\x0A"
#define MSG_WRITE_T 		"WRITE: "
#define MSG_WRITEBULK_T 	"BULK WRITE "

#define MSG_BIT_READ_T 		"READ BIT: "
#define MSG_BIT_PEEK_T 		"DATA INPUT, STATE: "
#define MSG_BIT_NOWINPUT_T	" *now input direction\x0D\x0A"
#define MSG_BIT_CLK_T  		" CLOCK TICKS\x0D\x0A"
#define MSG_BIT_CLKH_T 		"CLOCK, 1\x0D\x0A"
#define MSG_BIT_CLKL_T 		"CLOCK, 0\x0D\x0A"
#define MSG_BIT_DATH_T 		"DATA OUTPUT, 1\x0D\x0A"
#define MSG_BIT_DATL_T 		"DATA OUTPUT, 0\x0D\x0A"

#define MSG_VREG_ON_T		"POWER SUPPLIES ON\x0D\x0A"
#define MSG_VREG_OFF_T		"POWER SUPPLIES OFF\x0D\x0A"

#define MSG_ERROR_MACRO_T 	"NO SUCH MACRO IN THIS MODE, TRY ? OR (0) FOR HELP\x0D\x0A"
#define MSG_ERROR_MODE_T 	"COMMAND NOT IMPLEMENTED IN THIS MODE\x0D\x0A"
#define MSG_ERROR_SYNTAX_T 	"* SYNTAX ERROR, TYPE ? FOR HELP\x0D\x0A"
#define MSG_ERROR_BUFFER_T	"* TERMINAL BUFFER OVERFLOW, TRY SMALLER SEGMENTS\x0D\x0A"
#define MSG_ERROR_NOMODE_T	"NO MODE SET, M FOR MODE\x0D\x0A"
#define MSG_ERROR_NOTHIZPIN_T "WARNING, PINS NOT HIGH IMPEDANCE (HiZ)\x0D\x0A"

#define MSP_OPT_INVALID_T "INVALID, TRY AGAIN>"
#define MSG_OPT_OUTPUT_TYPE_T	"Output type:\x0D\x0A 1. High-Z outputs (H=input, L=GND)\x0D\x0A 2. Normal outputs (H=Vcc, L=GND)\x0D\x0A"
#define MSG_OPT_MODESET_T	"MODE SET\x0D\x0A"
#define MSG_OPT_DISPLAYMODE_T " 1. HEX\x0D\x0A 2. DEC\x0D\x0A 3. BIN\x0D\x0A 4. RAW\x0D\x0A"
#define MSG_OPT_DISPLAYMODESET_T "DISPLAY FORMAT SET\x0D\x0A"
#define MSG_OPT_PULLUP_T		" 1. Pullup off\x0D\x0A 2. Pullup on\x0D\x0A"
#define MSG_OPT_PULLUP_OFF_T "PULLUP RESISTORS OFF\x0D\x0A"
#define MSG_OPT_PULLUP_ON_T "PULLUP RESISTORS ON\x0D\x0A"
#define MSG_OPT_VMONITOR_T	"VOLTAGE MONITOR: "
#define MSG_OPT_BITORDER_T 	" 1. MSB first\x0D\x0A 2. LSB first\x0D\x0A"
#define MSG_OPT_BITORDER_MSB_T	"MSB SET: MOST SIG BIT FIRST\x0D\x0A"
#define MSG_OPT_BITORDER_LSB_T	"LSB SET: LEAST SIG BIT FIRST\x0D\x0A"
#define MSG_OPT_AUXPIN_T	"AUX PIN\x0D\x0A 1. AUX (DEFAULT)\x0D\x0A 2. CS/TMS\x0D\x0A"
#define MSG_OPT_AUXPIN_AUX_T "AUX: DEFAULT SETTING (AUX PIN)\x0D\x0A"
#define MSG_OPT_AUXPIN_CS_T "AUX: CONTROLS CS/TMS PIN\x0D\x0A"
#define MSG_OPT_TERMBAUD_T 	"Set serial port speed: (bps)\x0D\x0A 1. 300\x0D\x0A 2. 1200\x0D\x0A 3. 2400\x0D\x0A 4. 4800\x0D\x0A 5. 9600\x0D\x0A 6. 19200\x0D\x0A 7. 38400\x0D\x0A 8. 57600\x0D\x0A 9. 115200\x0D\x0A"
#define MSG_OPT_TERMBAUD_ADJUST_T	"Adjust your terminal and press space to continue\x0D\x0A"
#define MSG_OPT_UART_DBP_T "Data bits and parity:\x0D\x0A 1. 8, NONE *default \x0D\x0A 2. 8, EVEN \x0D\x0A 3. 8, ODD \x0D\x0A 4. 9, NONE \x0D\x0A"
#define MSG_OPT_UART_STOPBITS_T "Stop bits:\x0D\x0A 1. 1 *default\x0D\x0A 2. 2 \x0D\x0A"
#define MSG_OPT_UART_RXP_T "Receive polarity:\x0D\x0A 1. Idle 1 *default\x0D\x0A 2. Idle 0\x0D\x0A"
#define MSG_OPT_SPI_SPEED_T "Set speed:\x0D\x0A 1. 30KHz\x0D\x0A 2. 125KHz\x0D\x0A 3. 250KHz\x0D\x0A 4. 1MHz\x0D\x0A"
#define MSG_OPT_SPI_CKP_T "Clock polarity:\x0D\x0A 1. Idle low *default\x0D\x0A 2. Idle high\x0D\x0A"
#define MSG_OPT_SPI_CKE_T "Output clock edge:\x0D\x0A 1. Idle to active\x0D\x0A 2. Active to idle *default\x0D\x0A"
#define MSG_OPT_SPI_SMP_T "Input sample phase:\x0D\x0A 1. Middle *default\x0D\x0A 2. End\x0D\x0A"



#define MSG_STATUS_OUTPUT_HIZ_T 	"High-Z outputs (H=input, L=GND)\x0D\x0A"
#define MSG_STATUS_OUTPUT_NORMAL_T 	"Normal outputs (H=Vcc, L=GND)\x0D\x0A"
#define MSG_STATUS_PULLUP_NOTALLOWED_T 	"PULLUPS NOT ALLOWED IN THIS MODE\x0D\x0A"
#define MSG_STATUS_BITORDER_NOTALLOWED_T "BITORDER CONFIGURATION NOT ALLOWED IN THIS MODE\x0D\x0A"

/************************
*
*
*	HELP TEXT
*
*
*************************/
#define HELP_TITLE_MENUS_T			"MENUS"
#define HELP_MENUS_HELP_T 			"? Help"
#define HELP_MENUS_VERSION_T		"I Version & status info"
#define HELP_MENUS_BUSMODE_T		"M Bus mode"
#define HELP_MENUS_TERMBAUD_T		"B Terminal speed"
#define HELP_MENUS_DISPLAYMODE_T	"O Data display format"
#define HELP_MENUS_VMONITOR_T		"V Check supply volts"
#define HELP_MENUS_FREQCOUNT_T		"F Frequency count on AUX"
#define HELP_MENUS_FREQGEN_T		"G Frequency generator/PWM on AUX"
#define HELP_MENUS_AUXPIN_T			"C AUX pin assignment"
#define HELP_MENUS_BITORDER_T		"L Bit order"
#define HELP_MENUS_PULLUPV0A_T		"P SDA/SCL pullup resistors"
#define HELP_MENUS_PULLUPV2_T		"P Pullup resistors"
#define HELP_MENUS_VREG_T			"P Deprecated, use W/w"

#define HELP_TITLE_SYNTAX_T			"SYNTAX"
#define HELP_SYNTAX_AUXPIN_T		"A/a/@ Aux output toggle H/L/Hi-Z(read)"
#define HELP_SYNTAX_VREG_T			"W/w Power supply toggle on/off"
#define HELP_SYNTAX_VPROBE_T		"D Measure volts on probe"
#define HELP_SYNTAX_START_T			"[ ({) start write (with read)"
#define HELP_SYNTAX_STOP_T			"] or } stop write"
#define HELP_SYNTAX_READ_T			"R or r Read byte (r:1...255 for bulk reads)"
#define HELP_SYNTAX_WRITEBIN_T		"0b Write BIN byte"
#define HELP_SYNTAX_WRITEHEX_T		"0h or 0x Write HEX byte"
#define HELP_SYNTAX_WRTIEDEC_T		"0-255 Write DEC byte"
#define HELP_SYNTAX_DELIMIT_T		", Value delimiter (also space)"
#define HELP_SYNTAX_DELAY_T			"& 1uS delay (&:1...255 for multiple delays)"
#define HELP_SYNTAX_MACRO_T			"(#) Run macro, (0) for macro list"
#define HELP_SYNTAX_BITWISETITLE_T	"RAW BUS OPERATIONS"
#define HELP_SYNTAX_BITCLK_T		"^ Clock tick (^:1...255 for multiple ticks)"
#define HELP_SYNTAX_BITCLKHL_T		"/\\ Clock H/L"
#define HELP_SYNTAX_BITDATHL_T		"-/_ Data H/L"
#define HELP_SYNTAX_BITREAD_T		"! Read bit"
#define HELP_SYNTAX_BITPEEK_T		". Data pin state (no clock)"

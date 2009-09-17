//***************************************/
//
// Spanish translation by Pastus AKA Alessandro
// for contact of information about this translation pastus@gmail.com
//
//****************************************/
//these terms become part of the terminal text messaging system 
//one copy can be accessed from anywhere in the code, this saves a bunch of space

#define MSG_READY_T			"LISTO\x0D\x0A"

#define MSG_READ_T 		"LECTURA: "
#define MSG_READBULK_T		"LECTURA "
#define MSG_READBULK_BYTES_T 	" BYTES:\x0D\x0A"
#define MSG_WRITE_T 		"ESCRITURA: "
#define MSG_WRITEBULK_T 	" VEZ"
#define MSG_ACK_T		"ACK"
#define MSG_NACK_T		"NACK"
#define MSG_I2C_START_T		"BIT DE START I2C\x0D\x0A"
#define MSG_I2C_STOP_T		"BIT DE STOP I2C\x0D\x0A"
#define MSG_CS_ENABLED_T 	"CS HABILITADO\x0D\x0A"
#define MSG_CS_DISABLED_T	"CS INHABILITADO\x0D\x0A"
#define MSG_ADAPTER_T		"Esta modalidad necesida de un adaptador\x0D\x0A"

#define MSG_BIT_READ_T 		"BIT LEIDO: "
#define MSG_BIT_PEEK_T 		"DATO EN INGRESO, ESTADO: "
#define MSG_BIT_NOWINPUT_T	" *pin ahora es en Hi-Z\x0D\x0A"
#define MSG_BIT_CLK_T  		" CLOCK TICKS\x0D\x0A"
#define MSG_BIT_CLKH_T 		"CLOCK, 1\x0D\x0A"
#define MSG_BIT_CLKL_T 		"CLOCK, 0\x0D\x0A"
#define MSG_BIT_DATH_T 		"DATO EN SALIDA, 1\x0D\x0A"
#define MSG_BIT_DATL_T 		"DATO EN SALIDAA, 0\x0D\x0A"

#define MSG_VREG_ON_T		"ALIMENTACIO'N ENCENDIDA\x0D\x0A"
#define MSG_VREG_OFF_T		"ALIMENTACIO'N APAGADA\x0D\x0A"

#define MSG_ERROR_MACRO_T 	"Macro desconocida, intentar con ? o (0) para ayuda\x0D\x0A"
#define MSG_ERROR_MODE_T 	"Comando non usado por esa modalidad\x0D\x0A"
#define MSG_ERROR_SYNTAX_T 	"* Error de sintaxis,teclar ? para ayuda\x0D\x0A"
#define MSG_ERROR_BUFFER_T	"* SOBREFLUJO DE LA MEMORIA TAMPO'N DEL TERMINAL, INTENTAR CON SEGMENTO DATOS MAS CORTOS\x0D\x0A"
#define MSG_ERROR_NOMODE_T	"Ninguna modalidad definida, teclar M para la lista de modo\x0D\x0A"
#define MSG_ERROR_NOTHIZPIN_T 	"ATTENCIO'N, pins non en open drain (HiZ)\x0D\x0A"
#define MSP_OPT_INVALID_T 	"Error, ententa otra vez>"
#define MSG_OPT_OUTPUT_TYPE_T	"Elegir tipo de salida:\x0D\x0A 1. Open drain (H=Hi-z, L=tierra)\x0D\x0A 2. Salida normal (H=3.3V, L=tierra)\x0D\x0A"
#define MSG_OPT_MODESET_T	"Modalidad definida\x0D\x0A"
#define MSG_OPT_DISPLAYMODE_T 	" 1. HEX\x0D\x0A 2. DEC\x0D\x0A 3. BIN\x0D\x0A 4. CRUDO\x0D\x0A"
#define MSG_OPT_DISPLAYMODESET_T "Formato de visualicaciòn definido\x0D\x0A"
#define MSG_OPT_PULLUP_T	" 1. Pull-ups encendido\x0D\x0A 2. Pull-ups apagado\x0D\x0A"
#define MSG_OPT_PULLUP_OFF_T 	"Resistencias de pull-up APAGADE\x0D\x0A"
#define MSG_OPT_PULLUP_ON_T 	"Resistencias de pull-up ENCENDIDE\x0D\x0A"
#define MSG_OPT_VMONITOR_T	"CONTROL DE TENSIO'N: "
#define MSG_OPT_BITORDER_T	" 1. primero MSB \x0D\x0A 2. primero LSB \x0D\x0A"
#define MSG_OPT_BITORDER_MSB_T	"MSB definido: primero bit MAS SIGNIFICATIVO\x0D\x0A"
#define MSG_OPT_BITORDER_LSB_T	"LSB definido: primero bit MENOS SIGNIFICATIVO\x0D\x0A"
#define MSG_OPT_AUXPIN_T	"Elegir funciòn pin aux\x0D\x0A 1. AUX (por defecto)\x0D\x0A 2. CS/TMS\x0D\x0A"
#define MSG_OPT_AUXPIN_AUX_T 	"a/A/@ mandos pin AUX\x0D\x0A"
#define MSG_OPT_AUXPIN_CS_T 	"a/A/@ mandos pin CS/TMS\x0D\x0A"
#define MSG_OPT_TERMBAUD_ADJUST_T	"Arreglar el terminal y teclear espaciador para proseguir\x0D\x0A"
#define MSG_OPT_UART_BAUD_T 	"Elegir velocidad puerto serial(bps)\x0D\x0A 1. 300\x0D\x0A 2. 1200\x0D\x0A 3. 2400\x0D\x0A 4. 4800\x0D\x0A 5. 9600\x0D\x0A 6. 19200\x0D\x0A 7. 38400\x0D\x0A 8. 57600\x0D\x0A 9. 115200\x0D\x0A"
#define MSG_OPT_CKP_T 		"Polaridad de Clock:\x0D\x0A 1. Parado bajo *por defecto\x0D\x0A 2. Parado alto\x0D\x0A" //use these with BB library too
#define MSG_OPT_CKE_T 		"Frente de clock de salida:\x0D\x0A 1. Cambio Parado/Activo\x0D\x0A 2. Cambio Activo/Parado *por defecto\x0D\x0A"
#define MSG_OPT_SMP_T 		"Fase de muestro entrada:\x0D\x0A 1. Mitad *por defecto\x0D\x0A 2. Final\x0D\x0A"
#define MSG_OPT_BB_SPEED_T 	"Elegir velocidad:\x0D\x0A 1. Baja(~5KHz)\x0D\x0A 2. Alta(~50KHz)\x0D\x0A"
#define MSG_OPT_UART_DBP_T 	"Bit de datos y paridad:\x0D\x0A 1. 8, NINGUNA *por defecto \x0D\x0A 2. 8, PAR \x0D\x0A 3. 8, IMPAR \x0D\x0A 4. 9, NINGUNA \x0D\x0A"
#define MSG_OPT_UART_STOPBITS_T "Bits de stop:\x0D\x0A 1. 1 *por defecto\x0D\x0A 2. 2 \x0D\x0A"
#define MSG_OPT_UART_RXP_T 	"Polaridad de recepciòn:\x0D\x0A 1. Parado con 1 *por defecto\x0D\x0A 2. Parado con 0\x0D\x0A"
#define MSG_OPT_SPI_SPEED_T 	"Elegir velocidad:\x0D\x0A 1. 30KHz\x0D\x0A 2. 125KHz\x0D\x0A 3. 250KHz\x0D\x0A 4. 1MHz\x0D\x0A"

#define MSG_STATUS_OUTPUT_HIZ_T 	"Salidas open drain (H=entrada, L=tierra)\x0D\x0A"
#define MSG_STATUS_OUTPUT_NORMAL_T 	"Salidas normal (H=V+, L=tierra)\x0D\x0A"
#define MSG_STATUS_PULLUP_NOTALLOWED_T 	"Resistencias de pull-ups no permitida en esa modalidad\x0D\x0A"
#define MSG_STATUS_BITORDER_NOTALLOWED_T "Configuraciòn orden de bits no permitida en esa modalidad\x0D\x0A"

/************************
*
*
*	One use messages
*	These are only used once, usually through a bpWstring,
*   and not by registration in the terminal message system above
*
*
*************************/
// 1-Wire //
#define OUMSG_1W_BIT_BULKWRITE  " ESCRIBI BIT(S) ("
#define OUMSG_1W_BIT_WRITE	"ESCRIBI BIT: "
#define OUMSG_1W_BIT_WRITE_NOTE	" *en el siguiente clock (^) voy a tener esto valor"
#define OUMSG_1W_MACRO_MENU	" 0.Menù de las macro"
#define OUMSG_1W_MACRO_MENU_ROM	"1WIRE ROM MACROS MANDOS (RIFERENCIADO A PROTOCOL 1WIRE):\x0D\x0A 51.READ ROM (0x33) *per bus con singola rom\x0D\x0A 85.MATCH ROM (0x55) *seguito da indirizzo 64bit\x0D\x0A 204.SKIP ROM (0xCC) *seguito da comando\x0D\x0A 236.ALARM SEARCH (0xEC)\x0D\x0A 240.SEARCH ROM (0xF0)"
#define OUMSG_1W_MACRO_ADDRESS	"INDIRIZZO MACRO" //(#): 0 0 0 0 0 0 0 0
#define OUMSG_1W_MACRO_ADDRESS_NODEVICE "Ningun dispositivo encontrado, ententar antes con la macro (ALARM) SEARCH"
#define OUMSG_1W_MACRO_ALARMSEARCH_ROM 	"ALARM SEARCH (0xEC)"
#define OUMSG_1W_MACRO_SEARCH_ROM 	"SEARCH (0xF0)"
#define OUMSG_1W_MACRO_SEARCH_ROM_HEADER "Direcciòn macro     1WIRE"
#define OUMSG_1W_MACRO_SEARCH_ROM_NOTE	"ID dispositivo disponible con MACRO, intentar (0)."
#define OUMSG_1W_MACRO_READ_ROM 	"READ ROM (0x33): "
#define OUMSG_1W_MACRO_MATCH_ROM 	"MATCH ROM (0x55)"
#define OUMSG_1W_MACRO_SKIP_ROM 	"SKIP ROM (0xCC)"
#define OUMSG_1W_RESET			"BUS RESET "
#define OUMSG_1W_RESET_OK		"OK"
#define OUMSG_1W_RESET_ERROR		"ERROR: "
#define OUMSG_1W_RESET_SHORT		"*Cortocitcuito o pull-ups apagados "
#define OUMSG_1W_RESET_NODEV 		"*Ningun dispositivo encontrado "
//AUXpin//
#define OUMSG_AUX_PWM_OFF 		"PWM apagado"
#define OUMSG_AUX_PWM_NOTE 		"Generador de frecuencia/PWM 1KHz-4,000KHz (beta)"
#define OUMSG_AUX_PWM_FREQ 		"Frecuencia en KHz "
#define OUMSG_AUX_PWM_PRESCALE 		"Prescale:"
#define OUMSG_AUX_PWM_DUTY 		"Duty cycle en % "
#define OUMSG_AUX_PWM_ON 		"PWM encendido"
#define OUMSG_AUX_FREQ_PWM 		"PWM encendido: teclar G para apagar el PWM"
#define OUMSG_AUX_FREQCOUNT 		"Frecuecimetro Sobre pin AUX: "
#define OUMSG_AUX_HIZ			"AUX INPUT/HiZ, LECTURA"
#define OUMSG_AUX_HIGH			"AUX ALTO"
#define OUMSG_AUX_LOW			"AUX BAJO"
#define OUMSG_AUX_INPUT_READ		"AUX Hi-Z, LECTURA: "
//HD44780//
#define OUMSG_LCD_WRITE_COMMAND 	"CMD " //indicates writes to command register
#define OUMSG_LCD_WRITE_DATA 		"DAT " //indicates writes to data register
#define OUMSG_LCD_COMMAND_MODE 		"RS BAJO, MODALIDAD MANDOS"
#define OUMSG_LCD_DATA_MODE 		"RS ALTA, MODALIDAD DATOS"
#define OUMSG_LCD_SETUP_ADAPTER 	"Tipo de LCD:\x0D\x0A 1. HD44780 (usando PCF8574 IO expander)"
#define OUMSG_LCD_MACRO_MENU 		" 0.Menù de las Macro\x0D\x0A 1.LCD reinicio\x0D\x0A 2.Iinicializaciòn LCD\x0D\x0A 3.Limpia LCD\x0D\x0A 4.Position de cursor ex:(4:0)\x0D\x0A 5.(obsoleto)\x0D\x0A 6.Escribe :numero de numeros de test ex:(6:80)\x0D\x0A 7.Escribe :numero de caracter de test ex:(7:80)\x0D\x0A 8. Inserta texto en la posicion actual"
#define OUMSG_LCD_MACRO_INIT_DISPLAYLINES 	"Lineas de el display:\x0D\x0A 1. 1 \x0D\x0A 2. Mùltiplas"
#define OUMSG_LCD_MACRO_RESET 		"REINICIO"
#define OUMSG_LCD_MACRO_INIT 		"INICIALIZACIO'N"
#define OUMSG_LCD_MACRO_CLEAR 		"LIMPIADO"
#define OUMSG_LCD_MACRO_CURSOR		"CURSOR POSICIONADO"
#define OUMSG_LCD_MACRO_TEXT 		"Inserir texto"
#define OUMSG_LCD_ERROR_ADAPTER 	"No ACK, comprobar l'adaptador"
// I2C //
#define OUMSG_I2C_READ_PEND 	"*(N)ACK EN ESPERA"

#define OUMSG_I2C_CON 		"Modalidad I2C:\x0D\x0A 1. Software\x0D\x0A 2. Hardware"
#define OUMSG_I2C_REV3_WARN 	 "ATTENCIO'N: El periférico hardware I2C no es disponible en eso PIC! (REV A3)\x0D\x0A"
#define OUMSG_I2C_HWSPEED 	"Elegir velocidad:\x0D\x0A 1. 100KHz\x0D\x0A 2. 400KHz\x0D\x0A 3. 1MHz"
#define OUMSG_I2C_MACRO_MENU 	" 0.Menù del las macro\x0D\x0A 1.Direcciòn de bùsqueada a 7bit"
#define OUMSG_I2C_MACRO_SEARCH 	"Bùsqueada sobre I2C con direcciòn a 7bit. \x0D\x0A   Encontrado dispositivo al la direcciòn:"
#define OUMSG_I2C_MACRO_SNIFFER	"Sniffer sobre bus I2C, teclar qualqier buton para terminar"
//menu//
//jtag// // Yuck, I don't want to deal with this one...
//midi//
#define OUMSG_MIDI_READ_FAIL 		"FALLIDO, NINGUN DATO"
#define OUMSG_MIDI_LIVE_DISPLAY_ON 	"MONITOR UART EN TIEMPO REAL, } PER PARAR"
#define OUMSG_MIDI_LIVE_DISPLAY_OFF 	"MONITOR EN TIEMPO REAL PARADO"
//pckeyboard//
#define OUMSG_KB_TIMEOUT 		" BIT TIMEOUT"
#define OUMSG_KB_MACRO_MENU 		" 0. Menù de las macro\x0D\x0A 1. Monitor en tiempo real"
#define OUMSG_KB__MACRO_LIVE 		"Monitor de input, teclar qualquier buton para terminar"
#define OUMSG_KB_ERROR_STARTBIT 	" *error sobre bit de start"
#define OUMSG_KB_ERROR_PARITY 		" *error sobre bit de parità"
#define OUMSG_KB_ERROR_STOPBIT 		" *error sobre bit de stop"
#define OUMSG_KB_ERROR_TIMEOUT 		" BIT TIMEOUT"
#define OUMSG_KB_ERROR_NONE 		" NINGUN ERROR"
#define OUMSG_KB_ERROR_UNK 		" ERROR DESCONOCIDO"
//procMenu//
#define OUMSG_PM_1A_P_DEPRECATED 	"Configuraciòn de la tension de alimentacio obosleta, usar W/w para modificar"
#define OUMSG_PM_RESET 			"REINICIO"
#define OUMSG_PM_SELFTEST_HIZ		"Self-test en modalidad solo Hi-Z."
#define OUMSG_PM_CONVERT		"CONVERTI "
//procSyntax//
#define OUMSG_PS_DELAY			"RETRASO "
#define OUMSG_PS_DELAY_US		"uS"
#define OUMSG_PS_ADC_VOLT_PROBE		"TENSION EN LA SONDA: "
#define OUMSG_PS_ADC_VOLTS		"V"
//RAW2WIRE//
#define OUMSG_R2W_MACRO_MENU	" 0.Menù de las macro\x0D\x0A 1.ISO7813-3 ATR\x0D\x0A 2.ISO7813-3 solo parse\x0D\x0A"
//RAW3WIRE//
//selftest// //just leave in english for now...
//selftest//
// SPI //
#define OUMSG_SPI_SPEED 	"Elegir velocidad\x0D\x0A 1. 30KHz\x0D\x0A 2. 125KHz\x0D\x0A 3. 250KHz\x0D\x0A 4. 1MHz"
#define OUMSG_SPI_MACRO_MENU	" 0.Menù de las macro\x0D\x0A 1.Sniffer bus SPI"
#define OUMSG_SPI_SNIFF_MENU	"Sniffa cuando:\x0D\x0A 1. CS bajo\x0D\x0A 2. CS alto\x0D\x0A 3. Todos el trafico"
#define OUMSG_SPI_SNIFF_BEGIN	"Sniffer bus SPI, teclar qualqier buton para terminar"
#define OUMSG_SPI_SNIFF_BUFFER	"BUFFER OVERFLOW!\x0D\x0A Velocidad de bus demasiado alta, ententar con modalidad de visualizaciòn RAW"
//UART //
#define OUMSG_UART_READ_FAIL 		"FALLITO, NINGUN DATO"
#define OUMSG_UART_LIVE_DISPLAY_ON 	"MONITOR UART EN TIEMPO REAL, } PARA PARAR"
#define OUMSG_UART_LIVE_DISPLAY_OFF 	"MONITOR EN TIEMPO REALE PARADO"

#define OUMSG_UART_DATABITS_PARITY 	"Bit de datos y paridad:\x0D\x0A 1. 8, NINGUNA *por defecto \x0D\x0A 2. 8, PAR \x0D\x0A 3. 8, IMPAR \x0D\x0A 4. 9, NINGUNA"
#define OUMSG_UART_STOPBITS		"Bit de stop:\x0D\x0A 1. 1 *por defecto\x0D\x0A 2. 2"
#define OUMSG_UART_RXPOLARITY		"Polaridad de recibo:\x0D\x0A 1. Inactivo con 1 *por defecto\x0D\x0A 2. Inactivo con 0"
/************************
*
*
*	HELP TEXT
*
*
*************************/
#define HELP_TITLE_MENUS_T			"MENU'"
#define HELP_MENUS_HELP_T 			"? Ayuda"
#define HELP_MENUS_VERSION_T		"I Informacio'n de estado"
#define HELP_MENUS_BUSMODE_T		"M Modalidad del bus"
#define HELP_MENUS_TERMBAUD_T		"B Velocidad del terminal"
#define HELP_MENUS_DISPLAYMODE_T	"O Formato de visualizaciòn datos"
#define HELP_MENUS_VMONITOR_T		"V Control de tension de alimentaciòn"
#define HELP_MENUS_FREQCOUNT_T		"F Frecuencìmetro sobre AUX"
#define HELP_MENUS_FREQGEN_T		"G Generador de frecuencia/PWM sobre AUX"
#define HELP_MENUS_AUXPIN_T			"C Asignaciòn pin de AUX"
#define HELP_MENUS_BITORDER_T		"L Orden de los Bits"
#define HELP_MENUS_PULLUPV0A_T		"P Resistencias de pullup sobre SDA/SC"
#define HELP_MENUS_PULLUPV2_T		"P Resistencias de pullup"
#define HELP_MENUS_VREG_T			"P obsoleto, usar W/w"
#define HELP_MENUS_HDBCONVERT_T		"= Convertidor HEX/DEC/BIN"
#define HELP_MENUS_SELFTEST_T		"~ Auto test"
#define HELP_MENUS_RESET_T			"# Reinicio"

#define HELP_TITLE_SYNTAX_T			"SINTAXIS"
#define HELP_SYNTAX_AUXPIN_T		"A/a/@ Commutes salida AUX H/L/lectura"
#define HELP_SYNTAX_VREG_T			"W/w Commutes tensiòn de alimentaciòn encendida/apagada"
#define HELP_SYNTAX_VPROBE_T		"D Medida de tensiòn sobre las sondas ADC"
#define HELP_SYNTAX_START_T			"[ ({) inicio (con lectura)"
#define HELP_SYNTAX_STOP_T			"] o } acabar"
#define HELP_SYNTAX_READ_T			"R o r lectura byte"
#define HELP_SYNTAX_WRITEBIN_T		"0b Escribe byte BIN"
#define HELP_SYNTAX_WRITEHEX_T		"0h o 0x Escribe byte HEX"
#define HELP_SYNTAX_WRTIEDEC_T		"0-255 Escribe byte DEC"
#define HELP_SYNTAX_DELIMIT_T		", Delimitador (tambien espaciador)"
#define HELP_SYNTAX_DELAY_T			"& retraso de 1uS"
#define HELP_SYNTAX_REPEAT_T		": Repetir (r:2, 0x0a:4, &:20, ^:2, etc.)"
#define HELP_SYNTAX_MACRO_T			"(#) Ejecuta macro, (0) para ejecuciòn lista de macro"

#define HELP_SYNTAX_BITWISETITLE_T	"OPERACIO'N SOBRE BUS A BAJO NIVELL"
#define HELP_SYNTAX_BITCLKHL_T		"/\\ Clock H/L"
#define HELP_SYNTAX_BITDATHL_T		"-/_ Data H/L"
#define HELP_SYNTAX_BITPEEK_T		". Leer estado de pin de entrada"
#define HELP_SYNTAX_BITCLK_T		"^ Clock tick"
#define HELP_SYNTAX_BITREAD_T		"! Leer bit"

//Please leave one blank line after this comment. If you don't, the compiler gets mad.

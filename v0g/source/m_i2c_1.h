//******** REQUIRED DEFINES ***********
#define SCL 		BP_CLK
#define SCL_TRIS 	BP_CLK_DIR     //-- The SCL Direction Register Bit
#define SDA 		BP_MOSI        //-- The SDA output pin
#define SDA_TRIS 	BP_MOSI_DIR    //-- The SDA Direction Register Bit

#define I2CLOW  	0         //-- Puts pin into output/low mode
#define I2CHIGH 	1         //-- Puts pin into Input/high mode

char I2C_Send(char Address,char *Data,char Num);
char I2C_Read(char Address,char *Data,char Num);
char i2csendbyte(char byte);
char i2cgetbyte(void);
char i2cgetack(void);
void i2csendack(void);
void i2cdelay(char delay);
void i2cstart(void);
void i2cstop(void);
void i2cclock(void);
char i2creadbit(void);


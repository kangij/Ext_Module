#ifndef __ELMOS_E523_REGISTER_H_
#define __ELMOS_E523_REGISTER_H_
    
    /*********************************************************************************************************************/
/*										    ELMOS Register Map														 */
/*********************************************************************************************************************/
enum _ELMOS_REGISTER
{
	ELMOS523_CLKCTRL_REG01=0x01,
	ELMOS523_CHIPCTRL_REG02=0x02,
	ELMOS523_SLEEPCTRL_REG03=0x03,
	ELMOS523_SECURCTRL_REG04=0x04,
	ELMOS523_SAFECTRL_REG05=0x05,
	ELMOS523_IOCFG_REG06=0x06,
	ELMOS523_VREGCTRL_REG07=0x07,
	ELMOS523_PWM_LH_REG09=0x09,
	ELMOS523_PWM_HL_REG0A=0x0A,
	ELMOS523_SCPCTRL_REG0B=0x0B,
	ELMOS523_WDCTRL_REG10=0x10,
	ELMOS523_WDTRIG_REG11=0x11,
	ELMOS523_IRQMSK1_REG12=0x12,
	ELMOS523_IRQSTAT1_REG13=0x13,
	ELMOS523_IRQMSK2_REG14=0x14,
	ELMOS523_IRQSTAT2_REG15=0x15,
	ELMOS523_IOCOMPTHR_REG16=0x16,
	ELMOS523_AMUX_REG17=0x17,
	ELMOS523_CMUX_REG18=0x18,
	ELMOS523_DMUX_REG19=0x19,
	ELMOS523_DMON1_REG1A=0x1A,
	ELMOS523_DMON2_REG1B=0x1B,
	ELMOS523_BRIDGEMODE_REG20=0x20,
	ELMOS523_GATECFG1_REG21=0x21,
	ELMOS523_GATECFG2_REG22=0x22,
	ELMOS523_GATECFG3_REG23=0x23,
	ELMOS523_DEADTIME_LH_REG24=0x24,
	ELMOS523_DEADTIME_HL_REG25=0x25,
	ELMOS523_SCTH_REG26=0x26,
	ELMOS523_SCTH_HS_REG28=0x28,
	ELMOS523_SCTH_LS_REG29=0x29
};

/*********************************************************************************************************************/
/*										    ELMOS Register All Data Struct   										 */
/*********************************************************************************************************************/

typedef struct _ELMOS_523_Configuration_var_
{
	unsigned char CLKCTRL_REG01;
	unsigned char CHIPCTRL_REG02;
	unsigned char SLEEPCTRL_REG03;
	unsigned char SECURCTRL_REG04;
	unsigned char SAFECTRL_REG05;
	unsigned char IOCFG_REG06;
	unsigned char VREGCTRL_REG07;
	unsigned char PWM_LH_REG09;
	unsigned char PWM_HL_REG0A;
	unsigned char SCPCTRL_REG0B;
	unsigned char WDCTRL_REG10;
	unsigned char WDTRIG_REG11;
	unsigned char IRQMSK1_REG12;
	unsigned char IRQSTAT1_REG13;
	unsigned char IRQMSK2_REG14;
	unsigned char IRQSTAT2_REG15;
	unsigned char IOCOMPTHR_REG16;
	unsigned char AMUX_REG17;
	unsigned char CMUX_REG18;
	unsigned char DMUX_REG19;
	unsigned char DMON1_REG1A;
	unsigned char DMON2_REG1B;
	unsigned char BRIDGEMODE_REG20;
	unsigned char GATECFG1_REG21;
	unsigned char GATECFG2_REG22;
	unsigned char GATECFG3_REG23;
	unsigned char DEADTIME_LH_REG24;
	unsigned char DEADTIME_HL_REG25;
	unsigned char SCTH_REG26;
	unsigned char SCTH_HS_REG28;
	unsigned char SCTH_LS_REG29;
}ELMOS_523_Configuration_var;

/*********************************************************************************************************************/
/*									ELMOS User Configuration Option	enum									     */
/*********************************************************************************************************************/
enum
{
    ELMOS_INPUT_CLK_32M=0x00,
    ELMOS_INPUT_CLK_30M=0x02,
    ELMOS_INPUT_CLK_28M=0x01,
    ELMOS_INPUT_CLK_25M=0x03,
    ELMOS_INPUT_CLK_24M=0x02,
    ELMOS_INPUT_CLK_20M=0x03,
    ELMOS_INPUT_CLK_18M=0x05,
    ELMOS_INPUT_CLK_16M=0x04,
    ELMOS_INPUT_CLK_15M=0x05,
    ELMOS_INPUT_CLK_12M=0x05,
    ELMOS_INPUT_CLK_10M=0x06,
    ELMOS_INPUT_CLK_8M=0x06,
    ELMOS_INPUT_CLK_6M=0x07,
    ELMOS_INPUT_CLK_5M=0x07,
    ELMOS_INPUT_CLK_4M=0x07,
};

enum
{
    ELMOS_TDEAD_DIV8 = 0x00,
    ELMOS_TDEAD_DIV7 = 0x01,
    ELMOS_TDEAD_DIV6 = 0x02,
    ELMOS_TDEAD_DIV5 = 0x03,
    ELMOS_TDEAD_DIV4 = 0x04,
    ELMOS_TDEAD_DIV3 = 0x05,
    ELMOS_TDEAD_DIV2 = 0x06,
    ELMOS_TDEAD_DIV1 = 0x07
};

#define ELMOS_ENABLE        1
#define ELMOS_DISABLE       0

	
/*********************************************************************************************************************/	
/*	                                                                                                                 */
/*********************************************************************************************************************/	
		
/////////////////////// Reg01 CLKCTRL /////////////////////////////	
typedef struct 	
{	
    unsigned char addr;	
    union	
    {	
        struct	
        {	
            unsigned char CLKDIV :3;	
            unsigned char CLKTEST :1; // Read_Only_Reg	
            unsigned char TDEAD_DIV :3;	
            unsigned char F2X :1;     // Double Rate	
        };	
        unsigned char reg;	
    };  	
}ELMOS_CLKCTRL_Reg01;	
	
/////////////////////// Reg02 CHIPCTRL /////////////////////////////	
typedef struct 	
{	
    unsigned char addr;	
    union	
    {	
        struct	
        {	
            unsigned char BUSWA_EN :1;	
            unsigned char BUSWA_KEEDGE :1; // Read_Only_Reg	
            unsigned char SSENS :1;	
            unsigned char Nop :4;	
        };	
        unsigned char reg;	
    };  	
}ELMOS_CHIPCTRL_Reg02;	
	
/////////////////////// Reg03 SLEEPCTRL /////////////////////////////	
	
typedef struct 	
{	
    unsigned char addr;	
    union	
    {	
        struct	
        {	
            unsigned char SLEEP :1;	
            unsigned char DELAYSLEEP :1; // Read_Only_Reg	
            unsigned char Nop :6;	
        };	
        unsigned char reg;	
    };  	
}ELMOS_SLEEPCTRL_Reg03;	
	
	
/////////////////////// Reg04 SECURCTRL /////////////////////////////	
typedef struct 	
{	
    unsigned char addr;	
    union	
    {	
        struct	
        {	
            unsigned char ESECURE :1;	
            unsigned char EDEADNEG :1; // Read_Only_Reg	
            unsigned char EDEADMULT :1;	
            unsigned char EMERGENCY :1;	
            unsigned char EACMUX :1; // Read_Only_Reg	
            unsigned char EDMUX :1;	
            unsigned char Nop:2;	
        };	
        unsigned char reg;	
    };  	
}ELMOS_SECURCTRL_Reg04;	
	
/////////////////////// Reg05 SAFECTRL /////////////////////////////	
	
typedef struct 	
{	
    unsigned char addr;	
    union	
    {	
        struct	
        {	
            unsigned char OTSLEEP :1;	
            unsigned char OTVCCOFF :1; // Read_Only_Reg	
            unsigned char SVG :1;	
            unsigned char SVBATO :1;	
            unsigned char SOC :1; // Read_Only_Reg	
            unsigned char VGUV6V :1;	
            unsigned char VBATOV:2;	
        };	
        unsigned char reg;	
    };  	
}ELMOS_SAFECTRL_Reg05;	
	
/////////////////////// Reg06 IOCFG /////////////////////////////	
typedef struct 	
{	
    unsigned char addr;	
    union	
    {	
        struct	
        {	
            unsigned char EINT :1;	
            unsigned char VSELDIR :1; // Read_Only_Reg	
            unsigned char Nop :1;	
            unsigned char PWMIF :1;	
            unsigned char BUSIF :1;	
            unsigned char PWMFREQ :1; // Read_Only_Reg	
            unsigned char LIN_FLASH :1;	
            unsigned char TXDTO:1;	
        };	
        unsigned char reg;	
    };  	
}ELMOS_IOCFG_Reg06;	
	
/////////////////////// Reg07 VREGCTRL /////////////////////////////	
typedef struct 	
{	
    unsigned char addr;	
    union	
    {	
        struct	
        {	
            unsigned char VCCON :1;	
            unsigned char VGON :1; // Read_Only_Reg	
            unsigned char VSEL :1;	
            unsigned char VCC_SON :1;	
            unsigned char Nop :4;	
        };	
        unsigned char reg;	
    };  	
}ELMOS_VREGCTRL_Reg07;	
	
/////////////////////// Reg09 PWM_LH /////////////////////////////	
typedef struct 	
{	
    unsigned char addr;	
    union	
    {	
        struct	
        {	
            unsigned char D07 :8;	
        };	
        unsigned char reg;	
    };  	
}ELMOS_PWM_LH_Reg09;	
	
	
/////////////////////// Reg0A PWM_HL /////////////////////////////	
typedef struct 	
{	
    unsigned char addr;	
    union	
    {	
        struct	
        {	
            unsigned char D07 :8;	
        };	
        unsigned char reg;	
    };  	
}ELMOS_PWM_HL_Reg0A;	
	
	
/////////////////////// Reg0B SCPCTRL /////////////////////////////	
	
typedef struct 	
{	
    unsigned char addr;	
    union	
    {	
        struct	
        {	
            unsigned char SCFCT :2;	
            unsigned char Nop :2;	
            unsigned char SCALL :1;	
            unsigned char Nop2 :3;	
        };	
        unsigned char reg;	
    };  	
}ELMOS_SCPCTRL_Reg0B;	
	
/////////////////////// Reg10 WDCTRL /////////////////////////////	
	
typedef struct 	
{	
    unsigned char addr;	
    union	
    {	
        struct	
        {	
            unsigned char CLKWDEN :1;	
            unsigned char REGWDEN :1; 	
            unsigned char WDTEST :1;  // Read_Only_Reg	
            unsigned char WDFOW :1;	
            unsigned char WDTOW :2;	
            unsigned char PINTRIG :1;	
            unsigned char WDUSECW :1;	
        };	
        unsigned char reg;	
    };  	
}ELMOS_WDCTRL_Reg10;	
	
	
/////////////////////// Reg11 WDTRIG /////////////////////////////	
	
typedef struct 	
{	
    unsigned char addr;	
    union	
    {	
        struct	
        {	
            unsigned char TRIG :1;	
            unsigned char Nop :7; 	
        };	
        unsigned char reg;	
    };  	
}ELMOS_WDTRIG_Reg11;	
/////////////////////// Reg12 IRQMSK1 /////////////////////////////	
typedef struct 	
{	
    unsigned char addr;	
    union	
    {	
        struct	
        {	
            unsigned char EN_SC_LS1 :1;	
            unsigned char EN_SC_LS2 :1;	
            unsigned char EN_SC_LS3 :1;	
            unsigned char EN_SC_HS1 :1; 	
            unsigned char EN_SC_HS2 :1;	
            unsigned char EN_SC_HS3 :1; 	
            unsigned char EN_OC :1;	
            unsigned char EN_OT :1;             	
        };	
        unsigned char reg;	
    };  	
}ELMOS_IRQMSK1_Reg12;	
	
	
/////////////////////// Reg13 IRQSTAT1 ( Forced Interrupt or Read ) /////////////////////////////	
	
typedef struct 	
{	
    unsigned char addr;	
    union	
    {	
        struct	
        {	
            unsigned char SC_LS1 :1;	
            unsigned char SC_LS2 :1;	
            unsigned char SC_LS3 :1;	
            unsigned char SC_HS1 :1; 	
            unsigned char SC_HS2 :1;	
            unsigned char SC_HS3 :1; 	
            unsigned char OC :1;	
            unsigned char OT :1;             	
        };	
        unsigned char reg;	
    };  	
}ELMOS_IRQSTAT1_Reg13;	
	
	
/////////////////////// Reg14 IRQMSK2 /////////////////////////////	
typedef struct 	
{	
    unsigned char addr;	
    union	
    {	
        struct	
        {	
            unsigned char EN_VCC_UV :1;	
            unsigned char EN_VG_UV :1;	
            unsigned char EN_VG_OV :1;	
            unsigned char EN_VBATOV :1; 	
            unsigned char EN_PWM :1;	
            unsigned char EN_REG_WD :1; 	
            unsigned char EN_CLK_WD :1;	
            unsigned char Nop :1;             	
        };	
        unsigned char reg;	
    };  	
}ELMOS_IRQMSK2_Reg14;	
	
	
/////////////////////// Reg15 IRQSTAT2 ( Forced Interrupt or Read ) /////////////////////////////	
	
typedef struct 	
{	
    unsigned char addr;	
    union	
    {	
        struct	
        {	
            unsigned char VCC_UV :1;	
            unsigned char VG_UV :1;	
            unsigned char VG_OV :1;	
            unsigned char VBATOV :1; 	
            unsigned char PWM :1;	
            unsigned char REG_WD :1; 	
            unsigned char CLK_WD :1;	
            unsigned char Nop :1;             	
        };	
        unsigned char reg;	
    };  	
}ELMOS_IRQSTAT2_Reg15;	
	
	
/////////////////////// Reg16 IOCOMPTHR(IO Comparator Threshold)  /////////////////////////////	
typedef struct 	
{	
    unsigned char addr;	
    union	
    {	
        struct	
        {	
            unsigned char D05 :6;        	
            unsigned char Nop :2;	
        };	
        unsigned char reg;	
    };  	
}ELMOS_IOCOMPTHR_Reg16;	
	
	
/////////////////////// Reg17 AMUX(Analogue Signal Measurement) /////////////////////////////	
	
typedef struct 	
{	
    unsigned char addr;	
    union	
    {	
        struct	
        {	
            unsigned char S03 :4;	
            unsigned char S4  :1;	
            unsigned char Nop :3;            	
        };	
        unsigned char reg;	
    };  	
}ELMOS_AMUX_Reg17;	
	
	
/////////////////////// Reg18 CMUX(motor over current comparator input signal selection) /////////////////////////////	
typedef struct 	
{	
    unsigned char addr;	
    union	
    {	
        struct	
        {	
            unsigned char S03 :4;	
            unsigned char S4  :1;	
            unsigned char Nop :3;	
        };	
        unsigned char reg;	
    };  	
}ELMOS_CMUX_Reg18;	
	
/////////////////////// Reg19 DMUX(digital value output SO selection) /////////////////////////////	
	
typedef struct 	
{	
    unsigned char addr;	
    union	
    {	
        struct	
        {	
            unsigned char S03 :4;	
            unsigned char Nop :4;	
        };	
        unsigned char reg;	
    };  	
}ELMOS_DMUX_Reg19;	
	
/////////////////////// Reg1A DMON1(digital value monitoring) /////////////////////////////	
	
typedef struct 	
{	
    unsigned char addr;	
    union	
    {	
        struct	
        {	
            unsigned char SC_LS1 :1;	
            unsigned char SC_LS2 :1;	
            unsigned char SC_LS3 :1;	
            unsigned char SC_HS1 :1;	
            unsigned char SC_HS2 :1;	
            unsigned char SC_HS3 :1;	
            unsigned char OC :1;	
            unsigned char OT :1;	
        };	
        unsigned char reg;	
    };  	
}ELMOS_DMON1_Reg1A;	
	
/////////////////////// Reg1A/1B DMON1/2(digital value monitoring) /////////////////////////////	
	
typedef struct 	
{	
    unsigned char addr;	
    union	
    {	
        struct	
        {	
            unsigned char Nop :1;	
            unsigned char VG_UV :1;	
            unsigned char VG_OV :1;	
            unsigned char VBAT_OV :1;	
            unsigned char VTHONLS1 :1;	
            unsigned char VTHONLS2 :1;	
            unsigned char VTHONLS3 :1;	
            unsigned char S :1;	
        };	
        unsigned char reg;	
    };  	
}ELMOS_DMON2_Reg1B;	
	
	
/////////////////////// Reg20 BRIDGEMODE(bridge mode configuration) /////////////////////////////	
	
typedef struct 	
{	
    unsigned char addr;	
    union	
    {	
        struct	
        {	
            unsigned char DM1011 :2;	
            unsigned char DM2021 :2;	
            unsigned char DM3031 :2;	
            unsigned char ASYNC :1;	
            unsigned char Nop :1;	
        };	
        unsigned char reg;	
    };  	
}ELMOS_BRIDGEMODE_Reg20;	
	
	
/////////////////////// Reg21~3 GATECFG(motor phase gate driver control configuration) /////////////////////////////	
	
typedef struct 	
{	
    unsigned char addr;	
    union	
    {	
        struct	
        {	
            unsigned char GLLEVEL :1;	
            unsigned char GLPWM :1;	
            unsigned char GLHZ :1;	
            unsigned char GHLEVEL :1;	
            unsigned char GHPWM :1;	
            unsigned char GHHZ :1;	
            unsigned char GLINV :1;	
            unsigned char GLSYNC :1;	
        };	
        unsigned char reg;	
    };  	
}ELMOS_GATECFG03_Reg21_23;	
	
	
/////////////////////// Reg24/25 DEADTIME_LH/HL /////////////////////////////	
typedef struct 	
{	
    unsigned char addr;	
    union	
    {	
        struct	
        {	
            unsigned char D05 :6;	
            unsigned char PARITY :1;	
            unsigned char NEG :1;	
        };	
        unsigned char reg;	
    };  	
}ELMOS_DEADTIME_LHHL_Reg2425;	
	
/////////////////////// Reg26 SCTH(short circuit threshold selection (low resolution mode) and masking time) /////////////////////////////	
	
typedef struct 	
{	
    unsigned char addr;	
    union	
    {	
        struct	
        {	
            unsigned char TH02 :3;	
            unsigned char Nop :1;	
            unsigned char MT02 :3;	
            unsigned char Nop2 :1;	
        };	
        unsigned char reg;	
    };  	
}ELMOS_SCTH_Reg26;	
	
	
/////////////////////// Reg28 SCTH_HS(high side short circuit threshold selection (high resolution mode) /////////////////////////////	
typedef struct 	
{	
    unsigned char addr;	
    union	
    {	
        struct	
        {	
            unsigned char D06 :7;	
            unsigned char Nop :1;	
        };	
        unsigned char reg;	
    };  	
}ELMOS_SCTH_HS_Reg28;	
	
	
/////////////////////// Reg29 SCTH_LS(low side short circuit threshold selection (Low resolution mode) /////////////////////////////	
typedef struct 	
{	
    unsigned char addr;	
    union	
    {	
        struct	
        {	
            unsigned char D06 :7;	
            unsigned char Nop :1;	
        };	
        unsigned char reg;	
    };  	
}ELMOS_SCTH_LS_Reg29;	
///////////////////////////////////////////	
    	

    
#endif
    
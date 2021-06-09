
/*
 *   Dabo_Corp R&D Team
 *   Woker : Kang Injun
 * 	 Ver : v0.0.1
 */
/*********************************************************************************************************************/

/*********************************************************************************************************************/

/*********************************************************************************************************************/
/*										            Includes														 */
/*********************************************************************************************************************/
#include "ELMOS_E523.h"

/*********************************************************************************************************************/
/*											Function														         */
/*********************************************************************************************************************/

// Init
static void ELMOS_Dabo_Cfg(void);
//static void ELMOS_Reference_Cfg(void);
void ELMOS_Init_Cfg(void);

// ELMOS Cfg Read
void ELMOS_Read_ALL_Cfg(void);

// ELMOS Int Monitor
void ELMOS_DMON_Monitor(void);

// ELMOS Control Function
void ELMOS_SLEEP(unsigned char en, unsigned char sleep_dly);
void ELMOS_WATCHDOG_Enable(unsigned char en);
void ELMOS_WatchDog_Trg_Toggle(void);

/*********************************************************************************************************************/
/*									    ELMOS Register Configuration        										 */
/*********************************************************************************************************************/

/*********************************************************************************************************************/
ELMOS_CLKCTRL_Reg01 ELMOS_CLKCTRL_Reg01_cfg =
{
    .addr =0x01,
    .CLKDIV=ELMOS_INPUT_CLK_32M,
    .TDEAD_DIV=ELMOS_TDEAD_DIV8,
    .F2X=ELMOS_DISABLE
};
/*********************************************************************************************************************/
ELMOS_CHIPCTRL_Reg02 ELMOS_CHIPCTRL_Reg02_cfg =
{
    .addr =0x02,
    .BUSWA_EN=ELMOS_ENABLE,    // ENABLE : LEVEL TYPE / DISABLE : EDGE TYPE
    .BUSWA_KEEDGE=ELMOS_ENABLE,// ENABLE : RISING / DISABLE : FALLING
    .SSENS=ELMOS_DISABLE,       // ENABLE : BUS WAKE UP EN / DISABLE : DISABLE
};
/*********************************************************************************************************************/
ELMOS_SLEEPCTRL_Reg03 ELMOS_SLEEPCTRL_Reg03_cfg =
{
    .addr =0x03,
    .SLEEP=ELMOS_ENABLE,    // ENABLE : LEVEL TYPE / DISABLE : EDGE TYPE
    .DELAYSLEEP=ELMOS_ENABLE,// ENABLE : RISING / DISABLE : FALLING
};
/*********************************************************************************************************************/
ELMOS_SECURCTRL_Reg04 ELMOS_SECURCTRL_Reg04_cfg =
{
    .addr =0x04,
    .ESECURE=ELMOS_ENABLE,    //DMUX Access Enable
    .EDEADNEG=ELMOS_DISABLE,   //A/CMUX Access Enable
    .EDEADMULT=ELMOS_DISABLE,  //VIN Pin FET Gate Driver Emergency shut-down
    .EMERGENCY=ELMOS_DISABLE,  //DeadTime Var Write Access
    .EACMUX=ELMOS_DISABLE,     //DeadTime Negative Var allow
    .EDMUX=ELMOS_DISABLE,      //Disable All Register Block
};
/*********************************************************************************************************************/
ELMOS_SAFECTRL_Reg05 ELMOS_SAFECTRL_Reg05_cfg =
{
    .addr =0x05,
    .OTSLEEP=ELMOS_DISABLE,     // IC Shut down on over temerature
    .OTVCCOFF=ELMOS_ENABLE,    // Over Temperature function ( Enable : No Effect , Disable :  VCC Disable )
    .SVG=ELMOS_ENABLE,         // Safety Function on VG under voltage
    .SVBATO=ELMOS_ENABLE,      // Safety Function on Over VBAT
    .SOC=ELMOS_ENABLE,         // Safety Function on Over current
    .VGUV6V=ELMOS_DISABLE,      // VVG under Volatege Set ( Enable : VVBAT>6V , Disable : VVBAT>7V )
    .VBATOV=1,                  // VBAT over voltage failure reaction code table [FR1:FR0]
                                // 0 : ALL LS-FET ON, HS-FET Automatically OFF
                                // 1 : ALL FET OFF
                                // 2 : ALL HS-FET OFF, LS-FET Swtiching Allowed
};
/*********************************************************************************************************************/
ELMOS_IOCFG_Reg06 ELMOS_IOCFG_Reg06_cfg =
{
    .addr =0x06,
    .EINT=ELMOS_ENABLE,       // Interrupt Output Enable
    .VSELDIR=ELMOS_ENABLE,    // ENABLE: VSEL is interrupt output, DISABLE: SO is interrupt output
    .PWMIF=ELMOS_DISABLE,      // Enable : VSEL is Interrupt Ouput , Disable : SO is Interrupt Output
    .BUSIF=ELMOS_DISABLE,      // Enable : dedicated H/W Duty Cycle measurement S Pin
                               // Disalbe : Apply Dedicated H/W Duty Cycle measurement BUS Pin
    
    .PWMFREQ=ELMOS_DISABLE,    // Enable : 2kHz mode, Disalbe : 1kHz Mode
    .LIN_FLASH=ELMOS_DISABLE,  // Enable : LIN Flash Mode
    .TXDTO=ELMOS_ENABLE,      // Enable : TXD Clamping Time Out Enable
};
/*********************************************************************************************************************/
ELMOS_VREGCTRL_Reg07 ELMOS_VREGCTRL_Reg07_cfg =
{
    .addr =0x07,
    .VCCON=ELMOS_ENABLE,      //ENABLE: VCC Supply Powere
    .VGON=ELMOS_ENABLE,       //ENABLE: VG Supply Power
    .VSEL=ELMOS_DISABLE,       //ENABLE: Mcu Supply VCC 5V , Disalbe : 3.3V
    .VCC_SON=ELMOS_DISABLE,    //ENABLE: SleepMode -> VCC Connect VDD 
};
/*********************************************************************************************************************/
ELMOS_PWM_LH_Reg09 ELMOS_PWM_LH_Reg09_cfg =
{
    .addr =0x09,
    .D07=0,      // Read Only PWM LH ( Rising Edge Pos Val )
};
/*********************************************************************************************************************/
ELMOS_PWM_HL_Reg0A ELMOS_PWM_HL_Reg0A_cfg =
{
    .addr =0x0A,
    .D07=0,      // Read Only PWM HL ( Rising Edge Pos Val )
};
/*********************************************************************************************************************/
ELMOS_SCPCTRL_Reg0B ELMOS_SCPCTRL_Reg0B_cfg =
{
    .addr =0x0B,
    
    /*
    superior short circuit protection Type SCFCT[1:0]

    0 : e-try of power FET switching at every rising edge of the correspondent
        input control. Interrupt is thrown after first short circuit
        failure detection

    1 : Drivers remain off until interrupt is cleared by the microcontroller
   
    2 : One re-try of power FET switching allowed, after that all drivers
        remain off until interrupt is cleared by the microcontroller 
    */
    
    .SCFCT=0x01,      
    .SCALL=ELMOS_ENABLE//ENABLE: Switch off All Power FETs on short circuit
                       //Disable : correspondent FET
};
/*********************************************************************************************************************/
ELMOS_WDCTRL_Reg10 ELMOS_WDCTRL_Reg10_cfg =
{
    .addr =0x10,
    .CLKWDEN=ELMOS_DISABLE,  //Enable CLK watchdog
    .REGWDEN=ELMOS_ENABLE,  //Enable register watchdog 
    .WDFOW=ELMOS_DISABLE,    //Register watchdog is in first open window
    .WDTOW=3,               //[2bit]Register watchdog open window time (WDT,OW)
    .PINTRIG=ELMOS_DISABLE,  //ENABLE: Register watchdog is triggered on PWML3 rising edge, 
                            //DISABLE: Register watchdog is triggered via WDTRIG register (SPI access)
    .WDUSECW=ELMOS_ENABLE   //Use closed window for register watchdog (WDT,CW)
};
/*********************************************************************************************************************/
ELMOS_WDTRIG_Reg11 ELMOS_WDTRIG_Reg11_cfg =
{
    .addr =0x11,
    .TRIG=ELMOS_ENABLE // Value has to be toggled on each write access in order to trigger the watchdog
};
/*********************************************************************************************************************/
ELMOS_IRQMSK1_Reg12 ELMOS_IRQMSK1_Reg12_cfg =
{
    .addr =0x12,
    .EN_SC_LS1=ELMOS_ENABLE, // Enable LS 1 short circuit interrupt
    .EN_SC_LS2=ELMOS_ENABLE, // Enable LS 2 short circuit interrupt    
    .EN_SC_LS3=ELMOS_ENABLE, // Enable LS 3 short circuit interrupt
    .EN_SC_HS1=ELMOS_ENABLE, // Enable HS 1 short circuit interrupt
    .EN_SC_HS2=ELMOS_ENABLE, // Enable HS 2 short circuit interrupt
    .EN_SC_HS3=ELMOS_ENABLE, // Enable HS 3 short circuit interrupt  
    .EN_OC=ELMOS_ENABLE,     // Enable motor over current interrupt / CMUX multiplexer interrupt
    .EN_OT=ELMOS_ENABLE      // Enable over temperature interrupt
};
/*********************************************************************************************************************/
ELMOS_IRQSTAT1_Reg13 ELMOS_IRQSTAT1_Reg13_cfg =
{
    .addr =0x13,
    .SC_LS1=ELMOS_ENABLE, // LS 1 short circuit interrupt flag
    .SC_LS2=ELMOS_ENABLE, // LS 2 short circuit interrupt flag
    .SC_LS3=ELMOS_ENABLE, // LS 3 short circuit interrupt flag
    .SC_HS1=ELMOS_ENABLE, // HS 1 short circuit interrupt flag
    .SC_HS2=ELMOS_ENABLE, // HS 2 short circuit interrupt flag
    .SC_HS3=ELMOS_ENABLE, // HS 3 short circuit interrupt flag    
    .OC=ELMOS_ENABLE,     // Motor over current interrupt flag / CMUX multiplexer interrupt flag
    .OT=ELMOS_ENABLE      // Over temperature interrupt flag
};
/*********************************************************************************************************************/
ELMOS_IRQMSK2_Reg14 ELMOS_IRQMSK2_Reg14_cfg =
{
    .addr =0x14,
    .EN_VCC_UV=ELMOS_ENABLE,    // Enable VCC under voltage interrupt
    .EN_VG_UV=ELMOS_ENABLE,     // Enable VG under voltage interrupt   
    .EN_VG_OV=ELMOS_ENABLE,     // Enable VG over voltage interrupt
    .EN_VBATOV=ELMOS_ENABLE,    // Enable VBAT over voltage interrupt
    .EN_PWM=ELMOS_DISABLE,       // Enable dedicated hardware at BUS pin (PWM mode) interrupt
    .EN_REG_WD=ELMOS_ENABLE,    // Enable register watchdog interrupt    
    .EN_CLK_WD=ELMOS_DISABLE,    // Enable clock watchdog interrupt
};
/*********************************************************************************************************************/
ELMOS_IRQSTAT2_Reg15 ELMOS_IRQSTAT2_Reg15_cfg =
{
    .addr =0x15,
    .VCC_UV=ELMOS_ENABLE,    // Enable VCC under voltage interrupt
    .VG_UV=ELMOS_ENABLE,     // Enable VG under voltage interrupt   
    .VG_OV=ELMOS_ENABLE,     // Enable VG over voltage interrupt
    .VBATOV=ELMOS_ENABLE,    // Enable VBAT over voltage interrupt
    .PWM=ELMOS_ENABLE,       // Enable dedicated hardware at BUS pin (PWM mode) interrupt
    .REG_WD=ELMOS_ENABLE,    // Enable register watchdog interrupt    
    .CLK_WD=ELMOS_ENABLE,    // Enable clock watchdog interrupt
};
/*********************************************************************************************************************/
ELMOS_IOCOMPTHR_Reg16 ELMOS_IOCOMPTHR_Reg16_cfg =
{
    .addr =0x16,
    // Calc -> Vth ,OC= (IOCOMPTHR짹8/64) X VVDD
    .D05=0x3e    // Motor over current threshold value
    
};
/*********************************************************************************************************************/
ELMOS_AMUX_Reg17 ELMOS_AMUX_Reg17_cfg =
{
    .addr =0x17,

    /*
        #define ELMOS_AMUX_Current_amplifier_mode       0 // Standard
        #define ELMOS_AMUX_VVIN                         1
        #define ELMOS_AMUX_VIP                          2
        #define ELMOS_AMUX_VTEMP                        3
        #define ELMOS_AMUX_VVBAT_DIV12                  4
        #define ELMOS_AMUX_VVG_DIV5                     5
        #define ELMOS_AMUX_IOCOMPTHR                    6
        #define ELMOS_AMUX_SCTH_SCTH_LS                 7
        #define ELMOS_AMUX_VGL1                         8
        #define ELMOS_AMUX_VGL2                         9
        #define ELMOS_AMUX_VGL3                         10
    */
    
    .S03=0,    // Analogue signal selection. See below for coding
    .S4=0      // Reserved, bit must be 0
};
/*********************************************************************************************************************/
ELMOS_CMUX_Reg18 ELMOS_CMUX_Reg18_cfg =
{
    .addr =0x18,

    /*
        #define ELMOS_AMUX_Current_amplifier_mode       0 // Standard
        #define ELMOS_AMUX_VVIN                         1
        #define ELMOS_AMUX_VIP                          2
        #define ELMOS_AMUX_VTEMP                        3
        #define ELMOS_AMUX_VVBAT_DIV12                  4
        #define ELMOS_AMUX_VVG_DIV5                     5
        #define ELMOS_AMUX_IOCOMPTHR                    6
        #define ELMOS_AMUX_SCTH_SCTH_LS                 7
        #define ELMOS_AMUX_VGL1                         8
        #define ELMOS_AMUX_VGL2                         9
        #define ELMOS_AMUX_VGL3                         10
    */
    
    .S03=0,    // Motor over current comparator configuration. See below for coding.
    .S4=0       // Reserved, bit must be 0
};
/*********************************************************************************************************************/
ELMOS_DMUX_Reg19 ELMOS_DMUX_Reg19_cfg =
{
    .addr =0x19,

    /*
        #define ELMOS_DMUX_No_internal_digit_signal_out         0 // Standard
        #define ELMOS_DMUX_VSEL_pin_level                       1
        #define ELMOS_DMUX_S_pin_level                          2
        #define ELMOS_DMUX_T_pin_level                          3
        #define ELMOS_DMUX_Motorover_current_comp_level         4
        #define ELMOS_DMUX_Over_temper_comparator_level         5
        #define ELMOS_DMUX_lowside_gatedriver_output_GL1        6
        #define ELMOS_DMUX_lowside_gatedriver_output_GL2        7
        #define ELMOS_DMUX_lowside_gatedriver_output_GL3        8
        #define ELMOS_DMUX_VG_under_voltage_comparator_level    9
    */
    
    .S03=0,    // SO pin digital signal output selection. See below for coding.
};
/*********************************************************************************************************************/
ELMOS_DMON1_Reg1A ELMOS_DMON1_Reg1A_cfg =
{
    .addr =0x1a,
    // Read Only Reg
    .SC_LS1=ELMOS_DISABLE,    // Low side 1 short circuit comparator level
    .SC_LS2=ELMOS_DISABLE,    // Low side 2 short circuit comparator level
    .SC_LS3=ELMOS_DISABLE,    // Low side 3 short circuit comparator level
    .SC_HS1=ELMOS_DISABLE,    // High side 1 short circuit comparator level
    .SC_HS2=ELMOS_DISABLE,    // High side 2 short circuit comparator level
    .SC_HS3=ELMOS_DISABLE,    // High side 3 short circuit comparator level
    .OC=ELMOS_DISABLE,    // Motor over current comparator level
    .OT=ELMOS_DISABLE       // Over temperature comparator level
};
/*********************************************************************************************************************/
ELMOS_DMON2_Reg1B ELMOS_DMON2_Reg1B_cfg =
{
    .addr =0x1b,
    // Read Only Reg
    .VG_UV=ELMOS_DISABLE,    // VG under voltage comparator level
    .VG_OV=ELMOS_DISABLE,    // VG over voltage comparator level
    .VBAT_OV=ELMOS_DISABLE,    // VBAT over voltage comparator level
    .VTHONLS1=ELMOS_DISABLE,    // Low side 1 on threshold comparator level
    .VTHONLS2=ELMOS_DISABLE,    // Low side 2 on threshold comparator level
    .VTHONLS3=ELMOS_DISABLE,    // Low side 3 on threshold comparator level
    .S=ELMOS_DISABLE,    // Pin S input comparator level
};
/*********************************************************************************************************************/
ELMOS_BRIDGEMODE_Reg20 ELMOS_BRIDGEMODE_Reg20_cfg =
{
    .addr =0x20,
    .DM1011=0x03,    // Phase 3 driver mode
    .DM2021=0x03,    // Phase 2 driver mode
    .DM3031=0x03,    // Phase 1 driver mode
    .ASYNC=ELMOS_ENABLE,     // ELMOS_ENABLE  : PWMH / L 1~3 ASync Enable 
                              // ELMOS_DISABLE : PWMH / L 1~3 Sync Enable ( Internal Clock Use & Dead Time ) 
};
/*********************************************************************************************************************/
ELMOS_GATECFG03_Reg21_23 ELMOS_GATECFG0_Reg21_cfg =
{
    .addr =0x21,
    .GLLEVEL=ELMOS_DISABLE,    // Low side driver output level,
    .GLPWM=ELMOS_ENABLE,    // Use internal high side driver control to control low side driver
    .GLHZ=ELMOS_DISABLE,    // Switch GL to high impedance
    .GHLEVEL=ELMOS_DISABLE,   //  High side driver output level 
    .GHPWM=ELMOS_ENABLE,    // Use PWMH input pin to control high side driver
    .GHHZ=ELMOS_DISABLE,     // Switch GH to high impedance
    .GLINV=ELMOS_DISABLE,    // Low side driver is controlled inverted to HS driver
    .GLSYNC=ELMOS_DISABLE    //Low side driver is controlled synchronous
};
/*********************************************************************************************************************/
ELMOS_GATECFG03_Reg21_23 ELMOS_GATECFG1_Reg22_cfg =
{
    .addr =0x22,
    .GLLEVEL=ELMOS_DISABLE,    // Low side driver output level,
    .GLPWM=ELMOS_ENABLE,    // Use internal high side driver control to control low side driver
    .GLHZ=ELMOS_DISABLE,    // Switch GL to high impedance
    .GHLEVEL=ELMOS_DISABLE,   //  High side driver output level 
    .GHPWM=ELMOS_ENABLE,    // Use PWMH input pin to control high side driver
    .GHHZ=ELMOS_DISABLE,     // Switch GH to high impedance
    .GLINV=ELMOS_DISABLE,    // Low side driver is controlled inverted to HS driver
    .GLSYNC=ELMOS_DISABLE    //Low side driver is controlled synchronous
};
/*********************************************************************************************************************/
ELMOS_GATECFG03_Reg21_23 ELMOS_GATECFG2_Reg23_cfg =
{
    .addr =0x23,
    .GLLEVEL=ELMOS_DISABLE,    // Low side driver output level,
    .GLPWM=ELMOS_ENABLE,    // Use internal high side driver control to control low side driver
    .GLHZ=ELMOS_DISABLE,    // Switch GL to high impedance
    .GHLEVEL=ELMOS_DISABLE,   //  High side driver output level 
    .GHPWM=ELMOS_ENABLE,    // Use PWMH input pin to control high side driver
    .GHHZ=ELMOS_DISABLE,     // Switch GH to high impedance
    .GLINV=ELMOS_DISABLE,    // Low side driver is controlled inverted to HS driver
    .GLSYNC=ELMOS_DISABLE    //Low side driver is controlled synchronous
};
/*********************************************************************************************************************/
ELMOS_DEADTIME_LHHL_Reg2425 ELMOS_DEADTIME_LH_Reg24_cfg =
{
    .addr =0x24,
    .D05=0,                 // Dead time value. (Rising)
    .PARITY=ELMOS_DISABLE,  // Even register parity (write only, read as 0)
    .NEG=ELMOS_DISABLE,     // On-switching before off-switching of the correspondent power FET
};
/*********************************************************************************************************************/
ELMOS_DEADTIME_LHHL_Reg2425 ELMOS_DEADTIME_HL_Reg25_cfg =
{
    .addr =0x25,
    .D05=0,                 // Dead time value. (FALLING)
    .PARITY=ELMOS_DISABLE,  // Even register parity (write only, read as 0)
    .NEG=ELMOS_DISABLE,     // On-switching before off-switching of the correspondent power FET
};
/*********************************************************************************************************************/
ELMOS_SCTH_Reg26 ELMOS_SCTH_Reg26_cfg =
{
    .addr =0x26,
    .TH02=0x00,              // Short circuit threshold value (0 �� 4)
    .MT02=0x01,  // Short circuit initial masking time value
};
/*********************************************************************************************************************/
ELMOS_SCTH_HS_Reg28 ELMOS_SCTH_HS_Reg28_cfg =
{
    .addr =0x28,
    .D06=0x03,              // Short circuit threshold value (3~80)
};
/*********************************************************************************************************************/
ELMOS_SCTH_LS_Reg29 ELMOS_SCTH_LS_Reg29_cfg =
{
    .addr =0x29,
    .D06=0x03,              // Short circuit threshold value (3~80)
};
/*********************************************************************************************************************/
/*                                      Default Register Variable                                                    */
/*********************************************************************************************************************/
ELMOS_CLKCTRL_Reg01     ELMOS_CLKCTRL_Reg01_cfg;
ELMOS_CHIPCTRL_Reg02    ELMOS_CHIPCTRL_Reg02_cfg;
ELMOS_SLEEPCTRL_Reg03   ELMOS_SLEEPCTRL_Reg03_cfg;
ELMOS_SECURCTRL_Reg04   ELMOS_SECURCTRL_Reg04_cfg;
ELMOS_SAFECTRL_Reg05    ELMOS_SAFECTRL_Reg05_cfg;
ELMOS_IOCFG_Reg06       ELMOS_IOCFG_Reg06_cfg;
ELMOS_VREGCTRL_Reg07    ELMOS_VREGCTRL_Reg07_cfg;
ELMOS_PWM_LH_Reg09      ELMOS_PWM_LH_Reg09_cfg;
ELMOS_PWM_HL_Reg0A      ELMOS_PWM_HL_Reg0A_cfg;
ELMOS_SCPCTRL_Reg0B     ELMOS_SCPCTRL_Reg0B_cfg;
ELMOS_WDCTRL_Reg10      ELMOS_WDCTRL_Reg10_cfg;
ELMOS_WDTRIG_Reg11      ELMOS_WDTRIG_Reg11_cfg;
ELMOS_IRQMSK1_Reg12     ELMOS_IRQMSK1_Reg12_cfg;
ELMOS_IRQSTAT1_Reg13    ELMOS_IRQSTAT1_Reg13_cfg;
ELMOS_IRQMSK2_Reg14     ELMOS_IRQMSK2_Reg14_cfg;
ELMOS_IRQSTAT2_Reg15    ELMOS_IRQSTAT2_Reg15_cfg;
ELMOS_IOCOMPTHR_Reg16   ELMOS_IOCOMPTHR_Reg16_cfg;
ELMOS_AMUX_Reg17        ELMOS_AMUX_Reg17_cfg;
ELMOS_CMUX_Reg18        ELMOS_CMUX_Reg18_cfg;
ELMOS_DMUX_Reg19        ELMOS_DMUX_Reg19_cfg;
ELMOS_DMON1_Reg1A       ELMOS_DMON1_Reg1A_cfg;
ELMOS_DMON2_Reg1B       ELMOS_DMON2_Reg1B_cfg;
ELMOS_BRIDGEMODE_Reg20  ELMOS_BRIDGEMODE_Reg20_cfg;
ELMOS_GATECFG03_Reg21_23 ELMOS_GATECFG0_Reg21_cfg;
ELMOS_GATECFG03_Reg21_23 ELMOS_GATECFG1_Reg22_cfg;
ELMOS_GATECFG03_Reg21_23 ELMOS_GATECFG2_Reg23_cfg;
ELMOS_DEADTIME_LHHL_Reg2425 ELMOS_DEADTIME_LH_Reg24_cfg;
ELMOS_DEADTIME_LHHL_Reg2425 ELMOS_DEADTIME_HL_Reg25_cfg;
ELMOS_SCTH_Reg26            ELMOS_SCTH_Reg26_cfg;
ELMOS_SCTH_HS_Reg28         ELMOS_SCTH_HS_Reg28_cfg;
ELMOS_SCTH_LS_Reg29         ELMOS_SCTH_LS_Reg29_cfg;

/*********************************************************************************************************************/

static void ELMOS_Dabo_Cfg(void)
{   
	// ELMOS TEST Variable ( Recommand Sequence )
	ELMOS_E523_SPI_TX(ELMOS_CLKCTRL_Reg01_cfg.addr,ELMOS_CLKCTRL_Reg01_cfg.reg);   
	ELMOS_E523_SPI_TX(ELMOS_WDCTRL_Reg10_cfg.addr,ELMOS_WDCTRL_Reg10_cfg.reg);
	ELMOS_E523_SPI_TX(ELMOS_VREGCTRL_Reg07_cfg.addr,ELMOS_VREGCTRL_Reg07_cfg.reg);
	ELMOS_E523_SPI_TX(ELMOS_BRIDGEMODE_Reg20_cfg.addr,ELMOS_BRIDGEMODE_Reg20_cfg.reg);
	ELMOS_E523_SPI_TX(ELMOS_GATECFG0_Reg21_cfg.addr,ELMOS_GATECFG0_Reg21_cfg.reg);
	ELMOS_E523_SPI_TX(ELMOS_GATECFG1_Reg22_cfg.addr,ELMOS_GATECFG1_Reg22_cfg.reg);
	ELMOS_E523_SPI_TX(ELMOS_GATECFG2_Reg23_cfg.addr,ELMOS_GATECFG2_Reg23_cfg.reg);
	ELMOS_E523_SPI_TX(ELMOS_DEADTIME_LH_Reg24_cfg.addr,ELMOS_DEADTIME_LH_Reg24_cfg.reg);
	ELMOS_E523_SPI_TX(ELMOS_DEADTIME_HL_Reg25_cfg.addr,ELMOS_DEADTIME_HL_Reg25_cfg.reg);
	ELMOS_E523_SPI_TX(ELMOS_SCTH_HS_Reg28_cfg.addr,ELMOS_SCTH_HS_Reg28_cfg.reg);
	ELMOS_E523_SPI_TX(ELMOS_SCPCTRL_Reg0B_cfg.addr,ELMOS_SCPCTRL_Reg0B_cfg.reg);
	ELMOS_E523_SPI_TX(ELMOS_AMUX_Reg17_cfg.addr,ELMOS_AMUX_Reg17_cfg.reg);
	ELMOS_E523_SPI_TX(ELMOS_CMUX_Reg18_cfg.addr,ELMOS_CMUX_Reg18_cfg.reg);
	ELMOS_E523_SPI_TX(ELMOS_DMUX_Reg19_cfg.addr,ELMOS_DMUX_Reg19_cfg.reg);
	ELMOS_E523_SPI_TX(ELMOS_IOCOMPTHR_Reg16_cfg.addr,ELMOS_IOCOMPTHR_Reg16_cfg.reg);
	ELMOS_E523_SPI_TX(ELMOS_IOCFG_Reg06_cfg.addr,ELMOS_IOCFG_Reg06_cfg.reg);
	ELMOS_E523_SPI_TX(ELMOS_CHIPCTRL_Reg02_cfg.addr,ELMOS_CHIPCTRL_Reg02_cfg.reg);
	ELMOS_E523_SPI_TX(ELMOS_IRQMSK1_Reg12_cfg.addr,ELMOS_IRQMSK1_Reg12_cfg.reg);
	ELMOS_E523_SPI_TX(ELMOS_IRQMSK2_Reg14_cfg.addr,ELMOS_IRQMSK2_Reg14_cfg.reg);
	ELMOS_E523_SPI_TX(ELMOS_SAFECTRL_Reg05_cfg.addr,ELMOS_SAFECTRL_Reg05_cfg.reg);
	ELMOS_E523_SPI_TX(ELMOS_SECURCTRL_Reg04_cfg.addr,ELMOS_SECURCTRL_Reg04_cfg.reg); //Register Write Unlock
	ELMOS_E523_SPI_TX(ELMOS_SECURCTRL_Reg04_cfg.addr,ELMOS_SECURCTRL_Reg04_cfg.reg|0x01); //Register Write Lock
	ELMOS_E523_SPI_TX(ELMOS_IRQSTAT1_Reg13_cfg.addr,ELMOS_IRQSTAT1_Reg13_cfg.reg);
	ELMOS_E523_SPI_TX(ELMOS_IRQSTAT2_Reg15_cfg.addr,ELMOS_IRQSTAT2_Reg15_cfg.reg);

    // Add
    ELMOS_E523_SPI_TX(ELMOS_SLEEPCTRL_Reg03_cfg.addr,ELMOS_SLEEPCTRL_Reg03_cfg.reg);
    ELMOS_E523_SPI_TX(ELMOS_SECURCTRL_Reg04_cfg.addr,ELMOS_SECURCTRL_Reg04_cfg.reg);
    ELMOS_E523_SPI_TX(ELMOS_SAFECTRL_Reg05_cfg.addr,ELMOS_SAFECTRL_Reg05_cfg.reg);
    ELMOS_E523_SPI_TX(ELMOS_PWM_LH_Reg09_cfg.addr,ELMOS_PWM_LH_Reg09_cfg.reg);
	ELMOS_E523_SPI_TX(ELMOS_PWM_HL_Reg0A_cfg.addr,ELMOS_PWM_HL_Reg0A_cfg.reg);
    ELMOS_E523_SPI_TX(ELMOS_WDTRIG_Reg11_cfg.addr,ELMOS_WDTRIG_Reg11_cfg.reg);
	//ELMOS_E523_SPI_TX(ELMOS_DMON1_Reg1A_cfg.addr,ELMOS_DMON1_Reg1A_cfg.reg); // Read Only
	//ELMOS_E523_SPI_TX(ELMOS_DMON2_Reg1B_cfg.addr,ELMOS_DMON2_Reg1B_cfg.reg); // Read Only
    ELMOS_E523_SPI_TX(ELMOS_SCTH_Reg26_cfg.addr,ELMOS_SCTH_Reg26_cfg.reg);
    ELMOS_E523_SPI_TX(ELMOS_SCTH_LS_Reg29_cfg.addr,ELMOS_SCTH_LS_Reg29_cfg.reg);
}

#if 0
static void ELMOS_Reference_Cfg(void)
{   
	// ELMOS TEST Variable ( Recommand Sequence )
	ELMOS_E523_SPI_TX(ELMOS_CLKCTRL_Reg01_cfg.addr,0x77);   
	ELMOS_E523_SPI_TX(ELMOS_WDCTRL_Reg10_cfg.addr,0x00);
	ELMOS_E523_SPI_TX(ELMOS_VREGCTRL_Reg07_cfg.addr,0x03);
	ELMOS_E523_SPI_TX(ELMOS_BRIDGEMODE_Reg20_cfg.addr,0x3f);
	ELMOS_E523_SPI_TX(ELMOS_GATECFG0_Reg21_cfg.addr,0x12);
	ELMOS_E523_SPI_TX(ELMOS_GATECFG1_Reg22_cfg.addr,0x12);
	ELMOS_E523_SPI_TX(ELMOS_GATECFG2_Reg23_cfg.addr,0x12);
	ELMOS_E523_SPI_TX(ELMOS_DEADTIME_LH_Reg24_cfg.addr,0x00);
	ELMOS_E523_SPI_TX(ELMOS_DEADTIME_HL_Reg25_cfg.addr,0x00);
	ELMOS_E523_SPI_TX(ELMOS_SCTH_HS_Reg28_cfg.addr,0x32);
	ELMOS_E523_SPI_TX(ELMOS_SCPCTRL_Reg0B_cfg.addr,0x11);
	ELMOS_E523_SPI_TX(ELMOS_AMUX_Reg17_cfg.addr,0x00);
	ELMOS_E523_SPI_TX(ELMOS_CMUX_Reg18_cfg.addr,0x00);
	ELMOS_E523_SPI_TX(ELMOS_DMUX_Reg19_cfg.addr,0x00);
	ELMOS_E523_SPI_TX(ELMOS_IOCOMPTHR_Reg16_cfg.addr,0x3f);
	ELMOS_E523_SPI_TX(ELMOS_IOCFG_Reg06_cfg.addr,0x03);
	ELMOS_E523_SPI_TX(ELMOS_CHIPCTRL_Reg02_cfg.addr,0x07);
	ELMOS_E523_SPI_TX(ELMOS_IRQMSK1_Reg12_cfg.addr,0xff);
	ELMOS_E523_SPI_TX(ELMOS_IRQMSK2_Reg14_cfg.addr,0x0f);
	ELMOS_E523_SPI_TX(ELMOS_SAFECTRL_Reg05_cfg.addr,0x00);
	ELMOS_E523_SPI_TX(ELMOS_SECURCTRL_Reg04_cfg.addr,0x14); //Register Write Unlock
	ELMOS_E523_SPI_TX(ELMOS_SECURCTRL_Reg04_cfg.addr,0x15); //Register Write Lock
	ELMOS_E523_SPI_TX(ELMOS_IRQSTAT1_Reg13_cfg.addr,0xff);
	ELMOS_E523_SPI_TX(ELMOS_IRQSTAT2_Reg15_cfg.addr,0xff);      
}
#endif

void ELMOS_Init_Cfg(void)
{
	ELMOS_E523_SPI_Init();
	ELMOS_Dabo_Cfg();
}


/****************************************************************************************/
void ELMOS_Read_ALL_Cfg(void)
{
    ELMOS_523_Configuration_var ELMOS_523_Cfg_0;
    
    unsigned char Elmos_reg[]=
    {
        0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x09,0x0a,
        0x0b,0x10,0x11,0x12,0x13,0x14,0x15,0x16,0x17,
        0x18,0x19,0x1a,0x1b,0x20,0x21,0x22,0x23,0x24,
        0x25,0x26,0x28,0x29
    };
    unsigned char cnt;
    unsigned char *ptr=&ELMOS_523_Cfg_0.CLKCTRL_REG01;
    
    for(cnt=0;cnt<sizeof(Elmos_reg);cnt++)
    {
       ptr[cnt]=ELMOS_E523_SPI_RX(Elmos_reg[cnt]);
    }  
}
/*****************************************************************************/
void ELMOS_DMON_Monitor(void)
{
    unsigned char dmon1=0;
    unsigned char dmon2=0;
    unsigned char cnt=0;
    
    // ELMOS MONITOR_1 
    dmon1=ELMOS_E523_SPI_RX(ELMOS523_DMON1_REG1A);
  
    for(cnt=0;cnt<8;cnt++)
    {
       if( (dmon1&(0x01<<cnt)) != 0x00)
       {
            switch(cnt)
            {
                case 0:
                //printf("\r\n Low side 1 short circuit comparator level"); 
                break;
                
                case 1:
                //printf("\r\n Low side 2 short circuit comparator level"); 
                break;
                
                case 2:
                //printf("\r\n Low side 3 short circuit comparator level"); 
                break;
                
                case 3:
                //printf("\r\n High side 1 short circuit comparator level"); 
                break;
                
                case 4:
                //printf("\r\n High side 2 short circuit comparator level"); 
                break;
                
                case 5:
                //printf("\r\n High side 3 short circuit comparator level"); 
                break;
                
                case 6:
                //printf("\r\n Motor over current comparator level"); 
                break;
                
                case 7:
                //printf("\r\n Over temperature comparator level"); 
                break;
            }
       }
    }
    
    // ELMOS MONITOR_2 
    dmon2=ELMOS_E523_SPI_RX(ELMOS523_DMON2_REG1B);
    
    for(cnt=0;cnt<8;cnt++)
    {
       if( (dmon2&(0x01<<cnt)) != 0x00)
       {
            switch(cnt)
            {
                case 0:
                //printf("\r\n Nop"); 
                break;
                
                case 1:
                //printf("\r\n VG under voltage comparator level"); 
                break;
                
                case 2:
                //printf("\r\n VG over voltage comparator level"); 
                break;
                
                case 3:
                //printf("\r\n VBAT over voltage comparator level"); 
                break;
                
                case 4:
                //printf("\r\n Low side 1 on threshold comparator level"); 
                break;
                
                case 5:
                //printf("\r\n Low side 2 on threshold comparator level"); 
                break;
                
                case 6:
                //printf("\r\n Low side 3 on threshold comparator level"); 
                break;
                
                case 7:
                //printf("\r\n Pin S input comparator level"); 
                break;
            }
       }
    }
};
/*********************************************************************************************************************/

/*******************************************************************************
* Function Name: ELMOS_E523_SLEEP                                           */
/****************************************************************************/
/*
*
*  THIS Function is ELMOS_E523 SLEEP MODE Enable
*  Sleep Mode On is ELMOS All Register Clear 
*  Must Be Wakeup & Register ReInit
*
*  \param en: ELMOS_ENABLE or ELMOS_DISABLE
*  \param sleep_dly: Number of bytes to be read.
*
*******************************************************************************/
void ELMOS_SLEEP(unsigned char en, unsigned char sleep_dly)
{
  if(en==ELMOS_ENABLE)
  {
    if(sleep_dly==ELMOS_ENABLE)
    {
        ELMOS_E523_SPI_TX(ELMOS523_SLEEPCTRL_REG03,0x03);   
    }
    else
    {
        ELMOS_E523_SPI_TX(ELMOS523_SLEEPCTRL_REG03,0x01);      
    }
  }
  else
  {
    // ELMOS SLEEP is ALL Register Clear! DataSheet refer to P28
    // WAKEUP & Register ReInit
    ELMOS_E523_SPI_TX(ELMOS523_CHIPCTRL_REG02,0x05);
    ELMOS_Dabo_Cfg();
  }
}


/*******************************************************************************
* Function Name: ELMOS_E523_WINDOW_WATCHDOG
****************************************************************************/
/*
*
*  THIS Function is ELMOS_E523 WATCH DOG Enable (STANDARD Watchdog)
*  Use Case : 1. Standard WatchDog ( AnyTime WatchDog Register Clear ) / WDUSECW=0
*             2. Window WatchDog ( 1Cycle = open Window + close Window -> Only Close Window Time Register Clear
*                                   /WDUSECW=1
*  
*  \param en: ELMOS_ENABLE or ELMOS_DISABLE
*  NOTE : For Debugging purposes and software upload only, the watchdog can be stopped by setting "T Pin" to VCC Level
*  Show Table : Datasheet 4.17 Table
*******************************************************************************/

void ELMOS_WATCHDOG_Enable(unsigned char en)
{
  if(en==ELMOS_ENABLE)
  {
    ELMOS_E523_SPI_TX(ELMOS523_WDCTRL_REG10,0x03);
  }
  else
  {
    ELMOS_E523_SPI_TX(ELMOS523_WDCTRL_REG10,0x00);
  }
}


/*******************************************************************************
* Function Name: ELMOS_WatchDog_Trg_Toggle  
  Note : Window WatchDog
*/
/****************************************************************************/
void ELMOS_WatchDog_Trg_Toggle(void)
{
  unsigned char WDTRIG_Status=0;
  WDTRIG_Status=ELMOS_E523_SPI_RX(ELMOS_WDTRIG_Reg11_cfg.addr);
  ELMOS_E523_SPI_TX(ELMOS_WDTRIG_Reg11_cfg.addr,!WDTRIG_Status);
}



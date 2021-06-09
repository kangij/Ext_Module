
#ifndef __TLE_9201_DRIVER_H
#define __TLE_9201_DRIVER_H
    
//***********************************************************************************************************/			    
//                                      TLE9201_REGISTER					
//***********************************************************************************************************/			    
enum TLE9201_ENDISABLE
{
  TLE9201_DISABLE=0,
  TLE9201_ENABLE=1,
};
/**********************************************************************************************************/
enum TLE9201_CMD
{
    TLE9201_RD_DIA=0x00,            // Read Dianosis Register
    TLE9201_RES_DIA=0x80,           // Reset Diagnosis Register
    TLE9201_RD_REV=0x20,            // Read Device Revision Number
    TLE9201_RD_CTRL=0x60,           // Read Control Register
    TLE9201_WR_CTRL_RD_DIA=0xD0,    // Write Control and Read Diagnosis- sets Control Register values and
                                    // returns Diagnosis Register values
    TLE9201_WR_CTRL=0xE0,           // Write Control - sets and returns Control Register
};
/**********************************************************************************************************/				
enum TLE9201_DIAGONOSIS_STATUS 
{
    TLE9201_DIA_NO_FAULT=0xF,			
    TLE9201_DIA_SCG1=0xE,		
    TLE9201_DIA_SCVS1=0xD,		
    TLE9201_DIA_OL=0xC,		
    TLE9201_DIA_SCG2=0xB,		
    TLE9201_DIA_SCG1_SCG2=0xA,		
    TLE9201_DIA_SCVS1_SCG2=0x9,			
    TLE9201_DIA_SCVS2=0x7,	
    TLE9201_DIA_SCVS1_SCVS2=0x6,			
    TLE9201_DIA_UV=0x3,	
};
/**********************************************************************************************************/	
enum TLE9201_MOTOR_OUTPUT_STAGES
{
    TLE9201_FORWARD_CLOCKWISE=0x00,
    TLE9201_FREEWHEELING_IN_HS_FOWARD=0x01,
    TLE9201_REVERSE_COUNTER_CLOCKWISE=0x02,
    TLE9201_FREEWHEELING_IN_HS_REVERSE=0x03
};
//***********************************************************************************************************/			
//                                              DATA 					
//***********************************************************************************************************/	
typedef struct _TLE9201_DIAG_Stat_
{
    unsigned char EN_Stat;
    unsigned char OT_Stat;
    unsigned char TV_Stat;
    unsigned char CL_Stat;
    unsigned char DIA_Stat;
}TLE9201_DIAG_Stat;

typedef union _TLE9201_CTL_Var
{
    struct
    {
        unsigned char SPWM:1;
        unsigned char SDIR:1;
        unsigned char SEN :1;
        unsigned char SIN :1;
        unsigned char OLDIS :1;
        unsigned char CMD :3;
    };
    unsigned char var;
}TLE9201_CTL_Var;

TLE9201_DIAG_Stat TLE9201_DIAG_Status;
TLE9201_CTL_Var   TLE9201_CTL_Variable;    

//***********************************************************************************************************/			
//                                              FUNCTION 					
//***********************************************************************************************************/	
/*---------          TLE9201 MOTOR OUTPUT STAGES SET          -------------  */
extern void TLE9201_Motor_Output_Stages(unsigned char en, unsigned char mod);	

/*---------          TLE9201 CONTROL FUNCTION          -------------  */
extern void TLE9201_Control_Write(TLE9201_CTL_Var *ctr);
extern unsigned char TLE9201_Control_Stat(void);	

/*---------          TLE9201 DIAGONOSIS FUNCTION          -------------  */
extern void TLE9201_Diagnosis_Read(void);
extern void TLE9201_Diagnosis_Stat_Decode(TLE9201_DIAG_Stat *dia);
extern void TLE9201_Diagnosis_Reg_Reset(void);

/*---------          TLE9201 REVISION READ         -------------  */
extern unsigned char TLE9201_Revision_Read(void);

/*---------          TLE9201 INIT          -------------  */
extern void TLE9201_Init(void);
    
#endif

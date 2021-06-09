

//***********************************************************************************************************/			
//                                              INCLUDE					
//***********************************************************************************************************/
#include "TLE9201.h"
//***********************************************************************************************************/			
//                                          FUNCTION 					
//***********************************************************************************************************/		

void TLE9201_Motor_Output_Stages(unsigned char en, unsigned char mod);	

void TLE9201_Control_Write(TLE9201_CTL_Var *ctr);
unsigned char TLE9201_Control_Stat(void);	

void TLE9201_Diagnosis_Read(void);
void TLE9201_Diagnosis_Stat_Decode(TLE9201_DIAG_Stat *dia);
void TLE9201_Diagnosis_Reg_Reset(void);

unsigned char TLE9201_Revision_Read(void);

void TLE9201_Init(void);

/***********************************************************************************************************			
                                        TLE9201_INIT
***********************************************************************************************************/	
void TLE9201_Init(void)			
{			    
    unsigned char TEL9201_Rev=0;
    unsigned char TEL9201_CTRL_Reg_Stat=0;
    
    // HW Init
    TLE9201_HW_Init();
    
    // TLE9201 Control Register Setting
    TLE9201_CTL_Var test_cfg=
    {
        .SPWM  = TLE9201_DISABLE,
        .SDIR  = TLE9201_DISABLE,
        .SEN   = TLE9201_DISABLE,
        .SIN   = TLE9201_DISABLE,
        .OLDIS = TLE9201_DISABLE,
        .CMD   = TLE9201_DISABLE
    };
    TLE9201_Control_Write(&test_cfg);
    TEL9201_CTRL_Reg_Stat=TLE9201_Control_Stat();
    
    // TLE9201 Register Setting
    TLE9201_Motor_Output_Stages(TLE9201_ENABLE,TLE9201_FORWARD_CLOCKWISE);
    
    // TLE9201 Diagnosis Read ( Must Be Dispose of Diagnosis Error -> Dianosis Reg Reset )
    TLE9201_Diagnosis_Read(); // Diag Status Buffer Save
    TLE9201_Diagnosis_Stat_Decode(&TLE9201_DIAG_Status); // Diag Status Error Decode
    TLE9201_Diagnosis_Reg_Reset(); // Diag Status Reset
    
    // TLE9201 Reivision 
    TEL9201_Rev=TLE9201_Revision_Read();
}		

/***********************************************************************************************************			
  FUNCTION NAME :  TLE9201_Revision_Read
  Parameter
  INPUT : NONE
  OUTPUT : (unsigned char) TLE9201_Revision Number        
***********************************************************************************************************/		
unsigned char TLE9201_Revision_Read(void)			
{			    
    return TLE9201_SPI_Read(TLE9201_RD_REV);
}	

/***********************************************************************************************************			
  FUNCTION NAME :  TLE9201_Output_Stages
  Parameter
  INPUT : 
          unsigned char en
          0 : DISABLE
          1 : ENABLE

          unsigned char mod
          0 = TLE9201_FORWARD_CLOCKWISE
          1 = TLE9201_FREEWHEELING_IN_HS_FOWARD
          2 = TLE9201_REVERSE_COUNTER_CLOCKWISE
          3 = TLE9201_FREEWHEELING_IN_HS_REVERSE
  OUTPUT : NONE        
***********************************************************************************************************/
void TLE9201_Motor_Output_Stages(unsigned char en, unsigned char mod)			
{			
    if(en==TLE9201_ENABLE)
    {
        TLE9201_DIS_Write(0); // TODO TLE9201_DIS_PIN_LOW (0) 
        switch(mod)
        {   
         case TLE9201_FORWARD_CLOCKWISE:  // DIR (1)  / PWM (1) / OUT1 (H) / OUT2 (L)
            TLE9201_DIR_Write(1);
            TLE9201_PWM_Write(1);
            break;
            
         case TLE9201_FREEWHEELING_IN_HS_FOWARD: // DIR (1)  / PWM (0) / OUT1 (L) / OUT2 (H)
            TLE9201_DIR_Write(1);
            TLE9201_PWM_Write(0);            
            break;
            
         case TLE9201_REVERSE_COUNTER_CLOCKWISE: // DIR (0)  / PWM (1) / OUT1 (H) / OUT2 (Z)
            TLE9201_DIR_Write(0);
            TLE9201_PWM_Write(1); 
            break;
            
         case TLE9201_FREEWHEELING_IN_HS_REVERSE: // DIR (0)  / PWM (0) / OUT1 (Z) / OUT2 (H)
            TLE9201_DIR_Write(0);
            TLE9201_PWM_Write(0);             
            break;
        }
    }
    else if(en==TLE9201_DISABLE)
    {
        TLE9201_DIS_Write(1); // DIS (1) / DIR (X)  / PWM (X) / OUT1 (Z) / OUT2 (Z)
    }
}			
/***********************************************************************************************************			
  FUNCTION NAME :  TLE9201_Control_Write(TLE9201_CTL_Var *ctr)
  Parameter
  INPUT : TLE9201_CTL_Var
  OUTPUT : NONE        
***********************************************************************************************************/
void TLE9201_Control_Write(TLE9201_CTL_Var *ctr)			
{	
    ctr->CMD=(TLE9201_WR_CTRL>>5); // Always WR_CONTROL
    TLE9201_SPI_Write(ctr->var);
}

/***********************************************************************************************************			
  FUNCTION NAME :  (unsigned char) TLE9201_Control_Stat
  Parameter
  INPUT : NONE
  OUTPUT : (unsigned char) Control_Register       
***********************************************************************************************************/
unsigned char TLE9201_Control_Stat(void)			
{	
    return TLE9201_SPI_Read(TLE9201_RD_CTRL);
}	

/***********************************************************************************************************			
  FUNCTION NAME :  (void) TLE9201_Diagnosis_Read
  Parameter
  INPUT : NONE
  OUTPUT : NONE

  This Function Is DIAGONOSIS Register Data Save for "TLE9201_DIAG_Status"
  If TLE9201 Diagnosis Error Flag ON -> Process Error -> function "TLE9201_Diagnosis_Reg_Reset" Call
***********************************************************************************************************/
void TLE9201_Diagnosis_Read(void)			
{				
	unsigned char Diagnosis_Data;		
			
    Diagnosis_Data=TLE9201_SPI_Read(TLE9201_RD_DIA);
    
    //1 = outputs enabled by low signal on pin DIS
    //0 = outputs disabled by high signal on pin DIS
    TLE9201_DIAG_Status.EN_Stat=(Diagnosis_Data & 0x80)>>7; 
    
    //0 = overtemperature shutdown
    TLE9201_DIAG_Status.OT_Stat=(Diagnosis_Data & 0x40)>>6;
    
    //Always 0 - used for transmission validation
    TLE9201_DIAG_Status.TV_Stat=(Diagnosis_Data & 0x20)>>5;
    
    //0 = current limitation active
    TLE9201_DIAG_Status.CL_Stat=(Diagnosis_Data & 0x10)>>4;
    
    //DIAGONOSIS
    TLE9201_DIAG_Status.DIA_Stat=(Diagnosis_Data & 0x0f);
}
/***********************************************************************************************************			
  FUNCTION NAME :  void TLE9201_Diagnosis_Stat_Decode(TLE9201_DIAG_Stat *dia)
  Parameter
  INPUT : TLE9201_DIAG_Status
          
  OUTPUT : NONE

  TLE9201_DIAG_Status Data Decode
***********************************************************************************************************/	
void TLE9201_Diagnosis_Stat_Decode(TLE9201_DIAG_Stat *dia)
{

    TLE9201_DIAG_Stat check=*dia;
    
    // DIA_EN_STAT
    if(check.EN_Stat==TLE9201_ENABLE)
    {   /* 1= outputs enabled by low signal on pin DIS */ }
    else
    {   /* 0 = outputs disabled by high signal on pin DIS */ }
    
    // DIA_OT_STAT
    if(check.OT_Stat==TLE9201_ENABLE)
    {   /* 1 = NOT overtemperature shutdown */ }
    else
    {   /* 0 = overtemperature shutdown */ }
   
    // DIA_TV_STAT
    if(check.TV_Stat==TLE9201_ENABLE)
    {   /* NONE */ }
    else
    {   /* Always 0 - used for transmission validation */ }    
 
    // DIA_TV_STAT
    if(check.TV_Stat==TLE9201_ENABLE)
    {   /* 1 = Not current limitation active */ }
    else
    {   /* 0 = current limitation active */ }    
    
    // DIAGONOSIS_TRUTH_TABLE
    switch(dia->DIA_Stat)
    {
        case TLE9201_DIA_NO_FAULT:
        
        break;
        
        case TLE9201_DIA_SCG1:
        
        break;
        
        case TLE9201_DIA_SCVS1:
        
        break;
        
        case TLE9201_DIA_OL:
        
        break;
        
        case TLE9201_DIA_SCG2:
        
        break;
        
        case TLE9201_DIA_SCG1_SCG2:
        
        break;        
        
        case TLE9201_DIA_SCVS1_SCG2:
        
        break;
        
        case TLE9201_DIA_SCVS2:
        
        break;

        case TLE9201_DIA_SCVS1_SCVS2:
        
        break;
        
        case TLE9201_DIA_UV:
        
        break;
    }
}
/**********************************************************************************************************/	
void TLE9201_Diagnosis_Reg_Reset(void)
{
    TLE9201_SPI_Write(TLE9201_RES_DIA); // Clear DIAGONOSIS   
}			
/*****************************************   END   ****************************************************/

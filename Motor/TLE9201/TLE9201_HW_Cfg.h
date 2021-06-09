
#ifndef __TLE9201_HW_CFG_H_
#define __TLE9201_HW_CFG_H_
    
//***********************************************************************************************************/			    
//                      FUNCTIONS
//***********************************************************************************************************/	    
    
    // User MCU & Pin Setup 
    extern void TLE9201_DIR_PIN_CTL(unsigned char en);
    extern void TLE9201_DIS_PIN_CTL(unsigned char en);
    extern void TLE9201_PWM_PIN_CTL(unsigned char en);
    
    extern void TLE9201_HW_Init(void);
    extern void TLE9201_SPI_Write(unsigned char reg);
    extern unsigned char TLE9201_SPI_Read(unsigned char reg);
    
#endif
    
/*
 *   Dabo_Corp R&D Team
 *   Woker : Kang Injun
 * 	 Ver : v0.0.1
 */

#ifndef __ELMOS_E523_Control_H_
#define __ELMOS_E523_Control_H_


/******************************************************************************/
/*-----------------------------------Defined-----------------------------------*/
/******************************************************************************/



/******************************************************************************/
/*-----------------------------------Variable-----------------------------------*/
/******************************************************************************/

/******************************************************************************/
/*-----------------------------------Function-----------------------------------*/
/******************************************************************************/

// Init
extern void ELMOS_Init_Cfg(void);

// ELMOS Cfg Read
extern void ELMOS_Read_ALL_Cfg(void);

// ELMOS Int Monitor
extern void ELMOS_DMON_Monitor(void);

// ELMOS Control Function
extern void ELMOS_SLEEP(unsigned char en, unsigned char sleep_dly);
extern void ELMOS_WATCHDOG_Enable(unsigned char en);
extern void ELMOS_WatchDog_Trg_Toggle(void);
#endif


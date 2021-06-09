
//***********************************************************************************************************/			
//                                              INCLUDE					
//***********************************************************************************************************/
#include "TLE9201.h"

//***********************************************************************************************************/			
//                                              FUNCTION					
//***********************************************************************************************************/
static void TLE9201_GPIO_Init(void);
static void TLE9201_Spi_Init(void);

void TLE9201_HW_Init(void);

void TLE9201_DIS_PIN_CTL(unsigned char en);
void TLE9201_PWM_PIN_CTL(unsigned char en);
void TLE9201_DIR_PIN_CTL(unsigned char en);

void TLE9201_SPI_Write(unsigned char reg);
unsigned char TLE9201_SPI_Read(unsigned char reg);

/***********************************************************************************************************			
  FUNCTION NAME :  TLE9201_GPIO_Init
  TODO : TLE9201 CONTROL PIN ( DIS / PWM / DIR ) Setup      
***********************************************************************************************************/	
static void TLE9201_GPIO_Init(void)
{
    // Cypress PSOC Crator Auto Init
};

/***********************************************************************************************************			
  FUNCTION NAME :  TLE9201_Spi_Init
  TODO : TLE9201 SPI SetUp       
***********************************************************************************************************/		
static void TLE9201_Spi_Init(void)
{
    SPIM_Start();
};

/***********************************************************************************************************			
  FUNCTION NAME :  TLE9201_Spi_Write
  TODO : TLE9201 SPI Write Funtion       
***********************************************************************************************************/
void TLE9201_SPI_Write(unsigned char reg)			
{			
    /* Start transfer */
    SPIM_SpiUartPutArray(&reg, 1);
    while(0 != SPIM_SpiUartGetTxBufferSize());
    /* Clear dummy bytes from RX buffer */
    SPIM_SpiUartClearRxBuffer();
    SPIM_SpiUartClearTxBuffer();
}	
/***********************************************************************************************************			
  FUNCTION NAME :  TLE9201_Spi_Read
  TODO : TLE9201 SPI Read     
***********************************************************************************************************/	
unsigned char TLE9201_SPI_Read(unsigned char reg)			
{	    
    unsigned char rx_data=0;
    /* Start transfer */
    SPIM_SpiUartPutArray(&reg, 1);

    while (1 != SPIM_SpiUartGetRxBufferSize());

    /* Clear dummy bytes from TX buffer */
    SPIM_SpiUartClearTxBuffer();

    /* Read data from the RX buffer */
    while(0u != SPIM_SpiUartGetRxBufferSize())
    {
        rx_data = (uint8) SPIM_SpiUartReadRxData();
    }
    SPIM_SpiUartClearRxBuffer();
    
    
    return rx_data;
}	

/***********************************************************************************************************			
  FUNCTION NAME :  TLE9201_CONTROL_PIN
  TODO : TLE9201 DIS / PWM / DIR Control Pin  
***********************************************************************************************************/
void TLE9201_DIS_PIN_CTL(unsigned char en)
{
    TLE9201_DIS_Write(en);
}

void TLE9201_PWM_PIN_CTL(unsigned char en)
{
    TLE9201_PWM_Write(en);
}

void TLE9201_DIR_PIN_CTL(unsigned char en)
{
    TLE9201_DIR_Write(en);
}	

/***********************************************************************************************************			
  FUNCTION NAME :  TLE9201_HW_Init
  This Function Call is TLE9201_Init()  
***********************************************************************************************************/
void TLE9201_HW_Init(void)
{
    TLE9201_GPIO_Init();
	TLE9201_Spi_Init();
}
/*****************************************END**************************************************/	

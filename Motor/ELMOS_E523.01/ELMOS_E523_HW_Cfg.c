
/*
 *   Dabo_Corp R&D Team
 *   Woker : Kang Injun
 * 	 Ver : v0.0.1
     SPI Spec
     Speed : 1Mhz
     Mode : Motolola
     SCLK : CPHA =1 CPOL = 0
     Oversampling : 8
 */

/*********************************************************************************************************************/
/*										    Includes														         */
/*********************************************************************************************************************/
#include "ELMOS_E523.h"
/*********************************************************************************************************************/
/*										    MCU SPI Configuration											    	 
                                        NOTE : EACH MCU SPI Setting TODO
                                        // ELMOS Abstruct SPI Function
                                      void  ELMOS_Spi_Init() - SPI Configuration
                                      void  ELMOS_Spi_Transmit(unsigned char addr, unsigned char val) - Spi Transmit
                                      unsigned char ELMOS_Spi_Receive(unsigned char addr) - Spi Receiver
*/
/*********************************************************************************************************************/
#include "Ifx_Types.h"
#include "IfxCpu.h"
#include "IfxQspi_SpiMaster.h"
#include "IfxQspi_PinMap.h"
#include "IfxPort.h"

#define SPI_BUFFER_SIZE     5                       /* Buffers size                  */

typedef struct
{
    uint8 spiMasterTxBuffer[SPI_BUFFER_SIZE];       /* QSPI Master Transmit buffer   */
    uint8 spiMasterRxBuffer[SPI_BUFFER_SIZE];       /* QSPI Master Receive buffer    */
} qspiBuffers;

typedef struct
{
    qspiBuffers               spiBuffers;           /* Buffers instance              */
    IfxQspi_SpiMaster         spiMaster;            /* QSPI Master handle            */
    IfxQspi_SpiMaster_Channel spiMasterChannel;     /* QSPI Master Channel handle    */
} qspiComm;

qspiComm g_qspi;

#define ELMOS_SPI_Master &MODULE_QSPI2

#define ELMOS_SPI_BAUDRATE 1000000

static void ELMOS_Spi_Init(void)
{
    IfxQspi_SpiMaster_Config spiMasterConfig;                           /* Define a Master configuration            */

    {
    IfxQspi_SpiMaster_initModuleConfig(&spiMasterConfig, ELMOS_SPI_Master); /* Initialize it with default values        */

    spiMasterConfig.base.mode = SpiIf_Mode_master;                      /* Configure the mode                       */

    /* Select the port pins for communication */
    const IfxQspi_SpiMaster_Pins qspi2MasterPins = {
        &IfxQspi2_SCLK_P15_3_OUT, IfxPort_OutputMode_pushPull,          /* SCLK Pin                       (CLK)     */
        &IfxQspi2_MTSR_P15_5_OUT, IfxPort_OutputMode_pushPull,          /* MasterTransmitSlaveReceive pin (MOSI)    */
        &IfxQspi2_MRSTA_P15_4_IN, IfxPort_InputMode_pullDown,           /* MasterReceiveSlaveTransmit pin (MISO)    */
        IfxPort_PadDriver_cmosAutomotiveSpeed3                          /* Pad driver mode                          */
    };
    spiMasterConfig.pins = &qspi2MasterPins;                            /* Assign the Master's port pins            */

    /* Set the ISR priorities and the service provider */
    //spiMasterConfig.base.txPriority = ISR_PRIORITY_MASTER_TX;
    //spiMasterConfig.base.rxPriority = ISR_PRIORITY_MASTER_RX;
    //spiMasterConfig.base.erPriority = ISR_PRIORITY_MASTER_ER;
    //spiMasterConfig.base.isrProvider = IfxSrc_Tos_cpu0;

    /* Initialize the QSPI Master module */
    IfxQspi_SpiMaster_initModule(&g_qspi.spiMaster, &spiMasterConfig);
    }

    // MASTER Setting
    {
        IfxQspi_SpiMaster_ChannelConfig spiMasterChannelConfig;             /* Define a Master Channel configuration    */

           /* Initialize the configuration with default values */
           IfxQspi_SpiMaster_initChannelConfig(&spiMasterChannelConfig, &g_qspi.spiMaster);

           spiMasterChannelConfig.base.baudrate = ELMOS_SPI_BAUDRATE;     /* Set SCLK frequency to 1 MHz              */

           /* Select the port pin for the Chip Select signal */
           const IfxQspi_SpiMaster_Output qspi2SlaveSelect = {                 /* QSPI2 Master selects the QSPI3 Slave     */
               &IfxQspi2_SLSO0_P15_2_OUT, IfxPort_OutputMode_pushPull,         /* Slave Select port pin (CS)               */
               IfxPort_PadDriver_cmosAutomotiveSpeed1                          /* Pad driver mode                          */
           };
           spiMasterChannelConfig.sls.output = qspi2SlaveSelect;

           /* Initialize the QSPI Master channel */
           IfxQspi_SpiMaster_initChannel(&g_qspi.spiMasterChannel, &spiMasterChannelConfig);
    }

    // Buffer Setting
    {
        for (uint8 i = 0; i < SPI_BUFFER_SIZE; i++)
        {
            g_qspi.spiBuffers.spiMasterTxBuffer[i] = (uint8)(i + 1);        /* Fill TX Master Buffer with pattern       */
            g_qspi.spiBuffers.spiMasterRxBuffer[i] = 0;                     /* Clear RX Buffer                          */
        }
    }
};

static void ELMOS_Spi_Transmit(unsigned char addr, unsigned char val)
{
    unsigned char tx_buf[2];
    tx_buf[0]=val;
    tx_buf[1]=addr;
    while(IfxQspi_SpiMaster_getStatus(&g_qspi.spiMasterChannel) == SpiIf_Status_busy);
    
    IfxQspi_SpiMaster_exchange(&g_qspi.spiMasterChannel, &tx_buf[0], NULL_PTR, 2);
}

static unsigned char ELMOS_Spi_Receive(unsigned char addr)
{
    unsigned char tx_buf=addr;
    unsigned char rx_buf=0;

    while(IfxQspi_SpiMaster_getStatus(&g_qspi.spiMasterChannel) == SpiIf_Status_busy);

    IfxQspi_SpiMaster_exchange(&g_qspi.spiMasterChannel, &tx_buf, &rx_buf, 1);
    return rx_buf;
}

/*********************************************************************************************************************/
/*										    Mapping														             */
/*********************************************************************************************************************/
//#define ELMOS_CS_EN             SPI_SpiSetActiveSlaveSelect(SPI_SPI_SLAVE_SELECT0)     
//#define ELMOS_CS_DIS            SPI_SpiSetActiveSlaveSelect(SPI_SPI_SLAVE_SELECT1)   

#define ELMOS_SPI_Init			ELMOS_Spi_Init()
#define ELMOS_SPI_TX(addr,val)  ELMOS_Spi_Transmit(addr,val)
#define ELMOS_SPI_RX(addr)      ELMOS_Spi_Receive(addr)

/*********************************************************************************************************************/
/*											ELMOS Function														 */
/*********************************************************************************************************************/
void ELMOS_E523_SPI_Init(void)
{
	ELMOS_SPI_Init;
}

/*----------------------------------------------------------------------------------------------------------------*/
void ELMOS_E523_SPI_TX(unsigned char addr, unsigned char var)
{
    ELMOS_SPI_TX(addr<<1,var);   
}
/*----------------------------------------------------------------------------------------------------------------*/
unsigned char ELMOS_E523_SPI_RX(unsigned char addr)
{
	unsigned char rx_data;
    
    rx_data=ELMOS_SPI_RX((addr<<1)|0x01);
    
	return rx_data;
}
/*----------------------------------------------------------------------------------------------------------------*/

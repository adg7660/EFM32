/*************************************************************************!
*Copyright (c), 2008-2016, Qingdao Topscomm Communication Co .Ltd.
*File name: radio_hal.c
*Version: 0.1.0
*Date: 2016-08-26
*Author: WANGJIANHUI
*Description:
*************************************************************************/
#include "radio_hal.h"
#include "include.h"


/**********RADIO�����շ�����ṹ��**********/
RADIOPACKET RadioPkt;
uint8_t preamble[64];  //ǰ������ֽ�
uint8_t ctsWentHigh=0;
uint8_t Radio_Configuration_Data_Array[]=RADIO_CONFIGURATION_DATA_ARRAY;
tRadioConfiguration RadioConfiguration=RADIO_CONFIGURATION_DATA;
tRadioConfiguration *pRadioConfiguration=&RadioConfiguration;

/************************************************************!
*Function: Radio_PowerUp
*Description: RADIOӲ���ϵ縴λ
*Input: null
*Output: null
*Return: null
*************************************************************/
void Radio_PowerUp(void)
{
	si446x_reset();

	for(uint32_t i=0;i<0xFFFF;i++);
}
/************************************************************!
*Function: Radio_Init
*Description: RADIOӲ���ϵ縴λ������radio_config.h���ɵļĴ�����
*             ʼ�����鷢����RADIO������ʼ��ʧ�ܣ������ϵ縴λ��ʼ����
*Input: null
*Output: null
*Return: null
*************************************************************/
void Radio_Init(void)
{
	Spi_Init();  //SPI����

	Radio_PowerUp(); //�ϵ縴λ

	while(SI446X_SUCCESS!=si446x_configuration_init(pRadioConfiguration->Radio_ConfigurationArray))
	{
		for(uint32_t i=0;i<10000;i++);
		Radio_PowerUp();
	}

	si446x_get_int_status(0u,0u,0u);
}
/************************************************************!
*Function: Radio_StartRx
*Description: RADIO��ʼ�������ݺ���
*Input: 1.channel���������ݵ��ŵ�
*       2.lens�������յ����ݳ���
*Output: null
*Return: null
*************************************************************/
void Radio_StartRx(uint8_t channel,uint8_t lens)
{
	#ifdef RADIO_LDC_MODE
	//si446x_set_property(0x00,0x01,0x04,0x42); //����WUT_LDC
	#endif

	si446x_fifo_info(SI446X_CMD_FIFO_INFO_ARG_RX_BIT); //��λFIFO

	si446x_get_int_status(0u,0u,0u);

	#ifdef RADIO_LDC_MODE
	si446x_start_rx(channel,0u,lens,
			      SI446X_CMD_START_RX_ARG_RXTIMEOUT_STATE_ENUM_RX,
				  SI446X_CMD_START_RX_ARG_RXVALID_STATE_ENUM_SLEEP,
				  SI446X_CMD_START_RX_ARG_RXINVALID_STATE_ENUM_RX);
	#else
	si446x_start_rx(channel,0u,lens,
                  SI446X_CMD_START_RX_ARG_RXTIMEOUT_STATE_ENUM_NOCHANGE,
                  SI446X_CMD_START_RX_ARG_RXVALID_STATE_ENUM_RX,
                  SI446X_CMD_START_RX_ARG_RXINVALID_STATE_ENUM_RX);
	#endif
}
/************************************************************!
*Function: Radio_StartTx
*Description: RADIO���ݷ��ͺ���
*Input: 1.channel���������ݵ��ŵ�
*       2.data�� ���������ݵ��׵�ַ
*       3.lens�����������ݵĳ���
*Output: null
*Return: null
*************************************************************/
void Radio_StartTx(uint8_t channel,uint8_t *data,uint8_t lens)
{
	#ifdef RADIO_LDC_MODE
	si446x_set_property(0x00,0x01,0x04,0x02); //�ر�LDCʹ��,����Ҫ�ر�WUT
	#endif

	si446x_change_state(SI446X_CMD_CHANGE_STATE_ARG_NEW_STATE_ENUM_READY);
	si446x_fifo_info(SI446X_CMD_FIFO_INFO_ARG_TX_BIT); //��λFIFO
	si446x_get_int_status(0u,0u,0u);
	si446x_write_tx_fifo(lens,data);
	si446x_start_tx(channel,0x30,lens);
}
/************************************************************!
*Function: Radio_WakeUp_Tx
*Description: ����ǰ������֡���ͺ���
*Input: 1.channel: ͨ��
*       2. repeat: ����ʱ��Ϊrepeat*2MS
*       3.data:  �������ݵ��׵�ַ
*       4.lens: �������ݵĳ���
*Output: null
*Return: ��������״̬
*************************************************************/
void Radio_WakeUp_Tx(uint8_t channel,uint8_t repeat,uint8_t *data,uint8_t lens)
{
	RadioPkt.TXTHRESH=50; //TX_FIFO_ALMOST_EMPTY=50

	memset(preamble,0xAA,64); //���ǰ����

	RadioPkt.LENS=lens;
	RadioPkt.ENABLE=true;
	RadioPkt.REPEAT=repeat-1; //һ��Ҫ��1

	memcpy(RadioPkt.DATA,data,lens);

	#ifdef RADIO_LDC_MODE
	si446x_set_property(0x00,0x01,0x04,0x02); //�ر�LDCʹ��,����Ҫ�ر�WUT
	#endif

	Radio_Set_TXFIFOAE_Thresh(RadioPkt.TXTHRESH); //��������Ϊ50�ֽ�,200kbps��Ϊ2ms

	Radio_TFAERFAF_Enable(1,0); //��TX_FIFO_ALMOST_EMPTY�ж�

	Radio_Change_Syncword(0x5555); //��ͬ���ָ�Ϊ0xAA

	si446x_fifo_info(SI446X_CMD_FIFO_INFO_ARG_TX_BIT);

	si446x_get_int_status(0u,0u,0u);

	si446x_write_tx_fifo(RadioPkt.TXTHRESH,preamble);

	si446x_start_tx(channel,0x30,RadioPkt.TXTHRESH*repeat+lens); //�˴��ĳ���һ��Ҫ�뷢�͵ĳ���һ�£���
}
/************************************************************!
*Function: Enter_LDCRx_Mode
*Description: RADIO����LDC��������ģʽ,��������LDC���Ĵ���ֵ��
*Input: null
*Output: null
*Return: null
*************************************************************/
void Enter_LDCRx_Mode(void)
{
	si446x_set_property(0x00,0x01,0x04,0x42); //����WUT_LDC
}
/************************************************************!
*Function: Exit_LDCRx_Mode
*Description: �˳�LDC��������ģʽ��
*Input: null
*Output: null
*Return: null
*************************************************************/
void Exit_LDCRx_Mode(void)
{
	si446x_set_property(0x00,0x01,0x04,0x02); //�ر�LDCʹ��,����Ҫ�ر�WUT
}
/************************************************************!
*Function: Radio_Set_LDC_Time
*Description: RADIO����LDC��RX��SLEEP���ڡ�������������ο������ֲᡣ
*Input:
*Output: null
*Return: null
*************************************************************/
void Radio_Set_LDC_Time(uint8_t wut_m_15_8,uint8_t wut_m_7_0,
		                uint8_t wut_r,uint8_t wut_ldc)
{
	si446x_set_property(0x00,0x01,0x04,0x00);

	si446x_set_property(0x00,0x04,0x05,wut_m_15_8,wut_m_7_0,wut_r,wut_ldc);
}
/************************************************************!
*Function: Radio_Wait_Channel_Idle
*Description: RADIO�ȴ��ŵ��Ƿ���С�GPIO�ܽ�Ϊ�ߵ�ƽʱ�ж��ŵ���ռ
*             �ã�Ϊ�͵�ƽʱ����Ϊ�ŵ����У����Է������ݣ��˺�����Ҫ
*             ���Set_RSSI_Thresh����ʹ�ã���Ҫ������RSSI����ֵ��
*             �˺�����ȶ�RSSI��ֵ�ж��ŵ��Ƿ���С�
*Input: null
*Output: null
*Return: null
*************************************************************/
void Radio_Wait_Channel_Idle(void)
{
	while(radio_hal_Gpio1Level()==true);
}
/************************************************************!
*Function: Radio_Set_RSSI_Thresh
*Description: RADIO����RSSI��ֵ,�����ŵ�������ֵ�жϡ�
*Input: thresh��RSSI��ֵ
*Output: null
*Return: null
*************************************************************/
void Radio_Set_RSSI_Thresh(uint8_t thresh)
{
	si446x_set_property(0x20,0x01,0x4a,thresh);
}
/************************************************************!
*Function: Radio_Set_TXFIFOAE_Thresh
*Description: RADIO����TX_FIFO_ALMOST_EMPTY��ֵ��
*Input: thresh����ֵ
*Output: null
*Return: null
*************************************************************/
void Radio_Set_TXFIFOAE_Thresh(uint8_t thresh)
{
	si446x_set_property(0x12,0x01,0x0b,thresh);
}
/************************************************************!
*Function: Radio_Set_RXFIFOAF_Thresh
*Description: RADIO����RX_FIFO_ALMOST_FULL��ֵ��
*Input: thresh����ֵ
*Output: null
*Return: null
*************************************************************/
void Radio_Set_RXFIFOAF_Thresh(uint8_t thresh)
{
	si446x_set_property(0x12,0x01,0x0c,thresh);
}
/************************************************************!
*Function: Radio_Set_Preamble
*Description: RADIO����ǰ�����׼��ʽ�����ȡ�
*Input: 2.lens��ǰ���볤��,��λbyte
*Output: null
*Return: null
*************************************************************/
void Radio_Set_Preamble(uint8_t lens)
{
	si446x_set_property(0x10,0x01,0x00,lens);
}
/************************************************************!
*Function: Radio_TFAERFAF_Enable
*Description: RADIO���÷���FIFO���޿�ʹ�ܺͽ���FIFO������ʹ��
*Input: 1.tfae: ����FIFO����ʹ��
*       2.rfaf: ����FIFO����ʹ��
*Output: null
*Return: null
*************************************************************/
void Radio_TFAERFAF_Enable(uint8_t tfae,uint8_t rfaf)
{
	uint8_t data=0x38; //ʹ�ܷ����ж�,�����ж�,CRC�����ж�

	data=((tfae==1)?(data|0x02):(data&0xFD));

	data=((rfaf==1)?(data|0x01):(data&0xFE));

	si446x_set_property(0x01,0x01,0x01,data);
}
/************************************************************!
*Function: Radio_Field1_Length
*Description: RADIO����FIELD1�򳤶�
*Input: 1.lens: FIELD1�򳤶�
*Output: null
*Return: null
*************************************************************/
void Radio_Field1_Length(uint16_t lens)
{
	if(lens>=0x1FFF) //8191�ֽ�
		while(1);

	si446x_set_property(0x12,0x02,0x0d,(uint8_t)(lens>>8),(uint8_t)lens);
}
/************************************************************!
*Function: Radio_Change_Syncword
*Description: RADIO����ͬ���ָ�ʽ��
*Input: 1.sw: ͬ����
*Output: null
*Return: null
*************************************************************/
void Radio_Change_Syncword(uint16_t sw)
{
	si446x_set_property(0x11,0x04,0x01,(uint8_t)((sw>>8)&0xFF),(uint8_t)(sw&0xFF),0x00,0x00);
}
/************************************************************!
*Function: Radio_Cmd
*Description: RADIO��������
*Input: 1.data�������׵�ַ
*       2.lens�����ݳ���
*Output: null
*Return: ��������״̬
*************************************************************/
uint8_t Radio_Cmd(uint8_t *data,uint8_t lens)
{
	if (radio_comm_SendCmdGetResp(lens,data,0,0)!=0xFF)
		return false;

	return true;
}
/************************************************************!
*Function: Radio_StartSleep
*Description: RADIO˯��״̬����
*Input: null
*Output: null
*Return: null
*************************************************************/
void Radio_StartSleep(void)
{
	si446x_change_state(SI446X_CMD_CHANGE_STATE_ARG_NEW_STATE_ENUM_SLEEP);
}
/************************************************************!
*Function: Radio_ReadyTx
*Description: RADIO���ݷ���״̬����
*Input: null
*Output: null
*Return: null
*************************************************************/
void Radio_ReadyTx(void)
{
  si446x_change_state(SI446X_CMD_CHANGE_STATE_ARG_NEW_STATE_ENUM_READY);
}
/************************************************************!
*Function: radio_comm_GetResp
*Description: RADIO�õ�Ӧ�����ݺ���
*Input: null
*Output: null
*Return: null
*************************************************************/
uint8_t radio_comm_GetResp(uint8_t byteCount, uint8_t* pData)
{
	uint8_t ctsVal = 0;
	uint16_t errCnt = RADIO_CTS_TIMEOUT;

	while (errCnt != 0)      //wait until radio IC is ready with the data
	{
		radio_hal_ClearNsel();
		radio_hal_SpiWriteByte(0x44);    //read CMD buffer
		ctsVal = radio_hal_SpiReadByte();
		if (ctsVal == 0xFF)
		{
			if (byteCount)
			{
				radio_hal_SpiReadData(byteCount, pData);
			}
			radio_hal_SetNsel();
			break;
		}
		radio_hal_SetNsel();
		errCnt--;
	}
	if (errCnt == 0)
	{
		while(1);
	}
	if (ctsVal == 0xFF)
	{
		ctsWentHigh = 1;
	}
	return ctsVal;
}
/************************************************************!
*Function: radio_comm_SendCmd
*Description: RADIO�����������ݺ���
*Input: null
*Output: null
*Return: null
*************************************************************/
void radio_comm_SendCmd(uint8_t byteCount, uint8_t* pData)
{
	/* There was a bug in A1 hardware that will not handle 1 byte commands.
	It was supposedly fixed in B0 but the fix didn't make it at the last minute, so here we go again */
    if (byteCount == 1)
    	byteCount++;

	while (!ctsWentHigh)
    {
		radio_comm_PollCTS();
    }
    radio_hal_ClearNsel();
    radio_hal_SpiWriteData(byteCount, pData);
    radio_hal_SetNsel();
    ctsWentHigh = 0;
}
/************************************************************!
*Function: radio_comm_ReadData
*Description: RADIO ��ȡ�������ݺ���
*Input: null
*Output: null
*Return: null
*************************************************************/
void radio_comm_ReadData(uint8_t cmd, uint8_t pollCts, uint8_t byteCount, uint8_t* pData)
{
	if(pollCts)
	{
		while(!ctsWentHigh)
        {
			radio_comm_PollCTS();
        }
    }
    radio_hal_ClearNsel();
    radio_hal_SpiWriteByte(cmd);
    radio_hal_SpiReadData(byteCount, pData);
    radio_hal_SetNsel();
    ctsWentHigh = 0;
}
/************************************************************!
*Function: radio_comm_WriteData
*Description: RADIOд�������ݺ���
*Input: null
*Output: null
*Return: null
*************************************************************/
void radio_comm_WriteData(uint8_t cmd, uint8_t pollCts, uint8_t byteCount, uint8_t* pData)
{
	if(pollCts)
	{
		while(!ctsWentHigh)
        {
			radio_comm_PollCTS();
        }
    }
	radio_hal_ClearNsel();
    radio_hal_SpiWriteByte(cmd);
    radio_hal_SpiWriteData(byteCount, pData);
    radio_hal_SetNsel();
    ctsWentHigh = 0;
}
/************************************************************!
*Function: radio_comm_PollCTS
*Description:
*Input: null
*Output: null
*Return: null
*************************************************************/
uint8_t radio_comm_PollCTS(void)
{
	#ifdef RADIO_USER_CFG_USE_GPIO1_FOR_CTS
		while(!radio_hal_Gpio1Level())
		{
			/* Wait...*/
		}
		ctsWentHigh = 1;
		return 0xFF;
	#else
		return radio_comm_GetResp(0, 0);
	#endif
}
/************************************************************!
*Function: radio_comm_ClearCTS
*Description:
*Input: null
*Output: null
*Return: null
*************************************************************/
void radio_comm_ClearCTS()
{
	ctsWentHigh = 0;
}
/************************************************************!
*Function: radio_comm_SendCmdGetResp
*Description:
*Input: null
*Output: null
*Return: null
*************************************************************/
uint8_t radio_comm_SendCmdGetResp(uint8_t cmdByteCount, uint8_t* pCmdData, uint8_t respByteCount, uint8_t* pRespData)
{
	radio_comm_SendCmd(cmdByteCount, pCmdData);
	return radio_comm_GetResp(respByteCount, pRespData);
}
/************************************************************!
*Function: radio_hal_AssertShutdown
*Description:
*Input: null
*Output: null
*Return: null
*************************************************************/
void radio_hal_AssertShutdown(void)
{
	GPIO_PinOutSet(RF_SDN_PORT, RF_SDN_PIN);
}
/************************************************************!
*Function: radio_hal_DeassertShutdown
*Description:
*Input: null
*Output: null
*Return: null
*************************************************************/
void radio_hal_DeassertShutdown(void)
{
	GPIO_PinOutClear(RF_SDN_PORT, RF_SDN_PIN);
}
/************************************************************!
*Function: radio_hal_ClearNsel
*Description:
*Input: null
*Output: null
*Return: null
*************************************************************/
void radio_hal_ClearNsel(void)
{
    GPIO_PinOutClear(SPI_CS_PORT, SPI_CS_PIN);
}
/************************************************************!
*Function: radio_hal_SetNsel
*Description:
*Input: null
*Output: null
*Return: null
*************************************************************/
void radio_hal_SetNsel(void)
{
	GPIO_PinOutSet(SPI_CS_PORT, SPI_CS_PIN);
}
/************************************************************!
*Function: radio_hal_NirqLevel
*Description:
*Input: null
*Output: null
*Return: null
*************************************************************/
uint8_t radio_hal_NirqLevel(void)
{
	return GPIO_PinInGet(RF_NIRQ_PORT, RF_NIRQ_PIN);
}
/************************************************************!
*Function: radio_hal_SpiWriteByte
*Description:
*Input: null
*Output: null
*Return: null
*************************************************************/
void radio_hal_SpiWriteByte(uint8_t byteToWrite)
{
	Spi_ReadWrite(byteToWrite);
}
/************************************************************!
*Function: radio_hal_SpiReadByte
*Description:
*Input: null
*Output: null
*Return: null
*************************************************************/
uint8_t radio_hal_SpiReadByte(void)
{
	return Spi_ReadWrite(0x00);
}
/************************************************************!
*Function: radio_hal_SpiWriteData
*Description:
*Input: null
*Output: null
*Return: null
*************************************************************/
void radio_hal_SpiWriteData(uint8_t byteCount, uint8_t* pData)
{
	Spi_WriteDataBurst(byteCount, pData);
}
/************************************************************!
*Function: radio_hal_SpiReadData
*Description:
*Input: null
*Output: null
*Return: null
*************************************************************/
void radio_hal_SpiReadData(uint8_t byteCount, uint8_t* pData)
{
	Spi_ReadDataBurst(byteCount, pData);
}
/************************************************************!
*Function: radio_hal_Gpio0Level
*Description:
*Input: null
*Output: null
*Return: null
*************************************************************/
#ifdef RADIO_DRIVER_EXTENDED_SUPPORT
uint8_t radio_hal_Gpio0Level(void)
{
	return GPIO_PinInGet(RF_GPIO0_PORT, RF_GPIO0_PIN);
}
/************************************************************!
*Function: radio_hal_Gpio1Level
*Description:
*Input: null
*Output: null
*Return: null
*************************************************************/
uint8_t radio_hal_Gpio1Level(void)
{
    return GPIO_PinInGet(RF_GPIO1_PORT, RF_GPIO1_PIN);
}
/************************************************************!
*Function: radio_hal_Gpio2Level
*Description:
*Input: null
*Output: null
*Return: null
*************************************************************/
uint8_t radio_hal_Gpio2Level(void)
{
	return GPIO_PinInGet(RF_GPIO2_PORT, RF_GPIO2_PIN);
}
/************************************************************!
*Function: radio_hal_Gpio3Level
*Description:
*Input: null
*Output: null
*Return: null
*************************************************************/
uint8_t radio_hal_Gpio3Level(void)
{
	return GPIO_PinInGet(RF_GPIO3_PORT, RF_GPIO3_PIN);
}
#endif


/******************************************************************!
*Copyright (c), 2008-2017, Qingdao Topscomm Communication Co .Ltd.
*File name: init.c
*Version: 0.1.0
*Date: 2016-09-20
*Author: WANGJIANHUI
*Description:
*******************************************************************/
#include "include.h"

/************************************************************!
*Function:
*Description:
*Input: null
*Output: null
*Return: null
*************************************************************/
void BSP_Init(void)
{
	CHIP_Init();
	Cmu_Init();
	Emu_Init();
	Msc_Init();
	Rtc_Init();
	I2c_Init();
	Dma_Init();
	Gpio_Init();
	Wdog_Init();
	Adc0_Init();
	Radio_Init();
	Timer0_Init();
	Timer2_Init();
	Usart0_Init();
	Usart1_Init();
	Rx8025t_Init();
	Letimer0_Init();
	Mx25_Flash_Init();
	Uart0_Init(115200);
	Uart1_Init(115200);
	Leuart1_Init(9600);
	MX25_CHIP_ALL_ERASE();
	Radio_Set_Preamble(90);

	#ifdef PRINT_SYS_INIT_DEBUG
	DEBUG_PRINT("KKNSKK","<-------------------- �㼯��Ԫ  BSP ģ���ʼ�����! -------------------->");
	#endif
}
/************************************************************!
*Function:
*Description:
*Input: null
*Output: null
*Return: null
*************************************************************/
void APP_Init(void)
{
	SysPara_Init();        //ϵͳ��Ϣ��ʼ��
	EcpPara_Init();
	SysFlag_Init();
	DataFile_Init();       //�ļ�ͷ�ṹ���ʼ��
	DataCache_Init();      //���ζ��г�ʼ��
	FlashPara_Init();      //FLASH������ָ���ʼ��
	Print_Sys_Para();
	PointTable_Init();
	Mcu_Reset_Record();    //��¼MCU�����쳣״̬


	Rtc_Int_CallBack(Sys_Tick);
	Uart0_Rx_CallBack(Gprs_Queue_Rx);           //GPRS����ע�ắ��
	Uart1_Rx_CallBack(WeiHu_Queue_Rx);          //GPRS����ע�ắ��
	Leuart1_Rx_CallBack(Gps_Queue_Rx);          //GPS���ջ���ע��
	Uart0_Tx_CallBack(Gprs_ContinueTx);
	Uart1_Tx_CallBack(WeiHu_ContinueTx);
    Gpio_Int_CallBack(Radio_Int_Process);       //��Ƶ�ж�ע�ắ��
    Letimer0_Int_CallBack(Radio_Time_Slice);
    Radio_StartRx(gECPPARA.RADIO_CHANNEL,0x40);

    Wdog_Enable();

	#ifdef PRINT_SYS_INIT_DEBUG //��ʼ����Ϣ
    DEBUG_PRINT("KNSK","<-------------------- �㼯��Ԫ APP ģ���ʼ�����! -------------------->");
    DEBUG_PRINT("KNSKKK","<-------------------- �㼯��Ԫ *** ���� *** ��ʼ�����! -------------------->");
	#endif
}
/************************************************************!
*Function: DataFile_Init
*Description:
*Input: null
*Output: null
*Return: null
*************************************************************/
void DataFile_Init(void)
{
	YaoCeFile_Init(&gYCFILE);
}
/************************************************************!
*Function: Mcu_Reset_Record
*Description: MCU��λ�¼���¼
*Input: null
*Output: null
*Return: null
*************************************************************/
void Mcu_Reset_Record(void)
{
	RMU_RESETCAUSE RRC;

	RRC.DATA=RMU_ResetCauseGet(); //���ϵͳ�ĸ�λԴ
	RMU_ResetCauseClear();

	if(RRC.POR==0x01) //�ϵ縴λ
		Log_Data_Record(0x01,"S","�㼯��Ԫ�ϵ縴λ��");

	if(RRC.ETR==0x01) //�⹷��λ
		Log_Data_Record(0x05,"S","�㼯��Ԫ�ⲿ���Ź���λ��");

	if(RRC.SRR==0x01) //������¸�λ
		Log_Data_Record(0x0A,"S","�㼯��Ԫ����������ɣ�");

	if(RRC.WDR==0x01) //���Ź���λ
	{
		gSYSFLAG.CWS.SYS_STATUS=1;
		Log_Data_Record(0x05,"S","�㼯��Ԫ�ڲ����Ź���λ��");

		#ifdef PRINT_SYS_INIT_DEBUG
		for(uint32_t i=0;i<10;i++)
			DEBUG_PRINT("KKNSKK","<----- �㼯��Ԫ����λ,����������... ----->");
		Run_Led_Set();
		Status_Led1_Set();
		Status_Led2_Set();
		//while(1);
		#endif
	}
}
/************************************************************!
*Function:
*Description:
*Input: null
*Output: null
*Return: null
*************************************************************/
void Sys_Status_Report(void)
{
	if(gSYSFLAG.CWS.SYS_STATUS==1) //ϵͳװ���쳣
	{
		gSYSFLAG.CWS.SYS_STATUS=0;
		Soe_Data_Record(&gECPINFO.YX.STATUS,1,true,0);
	}
}
/************************************************************!
*Function:
*Description:
*Input: null
*Output: null
*Return: null
*************************************************************/
bool SysFlag_PrintOut(void)
{
	if(((gUNIXTIME.UNIX%5)!=0))
		return false;

	if(gUNIXTIME.UNIX==gSYSFLAG.STM.SYSFLAG_PRINT_TIME)
		return false;

	gSYSFLAG.STM.SYSFLAG_PRINT_TIME=gUNIXTIME.UNIX;

	vTaskSuspendAll();

	for(uint8_t line=0;line<LINEGROUP_MAXNUM;line++)
	{
		if(gSYSPARA.LINEGROUP.LINE[line].LINENO==0)
			continue;

		if(gSYSFLAG.AWS.ASF[line].WORKMODE==0)
			DEBUG_PRINT_NISR("KSDSK","<------------------- ",line," �߲ɼ���Ԫ��Ĺ���ģʽ: ȫ����ģʽ");

		if(gSYSFLAG.AWS.ASF[line].WORKMODE==1)
			DEBUG_PRINT_NISR("KSDSK","<------------------- ",line," �߲ɼ���Ԫ��Ĺ���ģʽ: �˻�ģʽ");
	}

	DEBUG_PRINT_NISR("KS","<------------------- ��ǰ��·����״̬: ");
	if(gECPFRAMELIST.LINKSTATE==0)
		DEBUG_PRINT_NISR("SK","��·δ����");
	if(gECPFRAMELIST.LINKSTATE!=0)
		DEBUG_PRINT_NISR("SK","��·������");

//	DEBUG_PRINT_NISR("KS","<------------------- ��ǰGPRS�˿�״̬: ");
//	if(gSYSFLAG.CIS.GPRS==TX)
//		DEBUG_PRINT_NISR("SK","���ڷ�������");
//	if(gSYSFLAG.CIS.GPRS==TXC)
//		DEBUG_PRINT_NISR("SK","�����ѷ������");
//
//	DEBUG_PRINT_NISR("KS","<------------------- ��ǰ��Ƶ�˿�״̬: ");
//	if(gSYSFLAG.CIS.RADIO==RX)
//		DEBUG_PRINT_NISR("SK","����״̬");
//	if(gSYSFLAG.CIS.RADIO==TX)
//		DEBUG_PRINT_NISR("SK","����״̬");

//	DEBUG_PRINT_NISR("KSDK","<------------------- ��ǰICP����״̬ : ",gSYSFLAG.CWS.ICPSTATUS);
//
//	DEBUG_PRINT_NISR("KSDK","<------------------- ��ǰECP����״̬ : ",gSYSFLAG.CWS.ECPSTATUS);
//
//	DEBUG_PRINT_NISR("KSDK","<------------------- ��ǰICP�߳�״̬ : ",gSYSFLAG.CWS.ICPRUNCOUNT);
//
	DEBUG_PRINT_NISR("SDK","<------------------- ��ǰECP�߳�״̬ : ",gSYSFLAG.CWS.ECPRUNCOUNT);
//
//	DEBUG_PRINT_NISR("KSDK","<------------------- ��ǰ��Ƶ�����ж�: ",gSYSFLAG.CWS.RADIORECEIVECNT);
//
//	DEBUG_PRINT_NISR("KSDK","<------------------- ��ǰ��Ƶ���泤��: ",DataCacheLength(&RADIO_RXDC));
//
	DEBUG_PRINT_NISR("SDK","<------------------- ��ǰ��Լ���泤��: ",DataCacheLength(&GPRS_RXDC));
//
//	DEBUG_PRINT_NISR("KSDK","<------------------- ��Ƶ����֡״̬  : ",RADIOFRAME.ISLOCK);
//
	DEBUG_PRINT_NISR("SDK","<------------------- ��Լ����֡״̬  : ",gECPFRAMELIST.REQ.ISLOCK);

	DEBUG_PRINT_NISR("KK");

	xTaskResumeAll();

	return true;
}
/************************************************************!
*Function: Gps_Timing_Process
*Description:
*Input: null
*Output: null
*Return: null
*************************************************************/
bool Gps_Timing_Process(void)
{
	if(gECPPARA.GPS_TIMING_MODE==0)
		return false;

	if(((gUNIXTIME.UNIX%gECPPARA.GPS_TIMING_CYCLE)!=0))
		return false;

	if(gUNIXTIME.UNIX==gSYSFLAG.STM.GPS_TIMING_TIME)
		return false;

	gSYSFLAG.STM.GPS_TIMING_TIME=gUNIXTIME.UNIX;

	Gps_Power_On();

	return true;
}
/************************************************************!
*Function:
*Description:
*Input: null
*Output: null
*Return: null
*************************************************************/
void Run_Led_Toggle(void)
{
	gSYSFLAG.CWS.RUN_LED_STATUS^=1;

	if(gSYSFLAG.CWS.RUN_LED_STATUS==0)
		Timer0_Stop();

	if(gSYSFLAG.CWS.RUN_LED_STATUS==1)
		Timer0_Start();
}
/************************************************************!
*Function:
*Description:
*Input: null
*Output: null
*Return: null
*************************************************************/
void Run_Led_Set(void)
{
	Timer0_Start();
}
/************************************************************!
*Function: MX25_CHIP_ALL_ERASE
*Description:
*Input: null
*Output: null
*Return: null
*************************************************************/
void MX25_CHIP_ALL_ERASE(void)
{
    #ifdef PRINT_MX25_ERASE_DEBUG
	if(Mx25_Gpio_Pin()==true)
	{
		DEBUG_PRINT_NISR("KKSKK","<----- ���ڲ���MX25�洢!��Լ��Ҫ38��,���Ժ�... ----->");
		Mx25_Erase_Chip();
		DEBUG_PRINT_NISR("KKSKK","<----- MX25�洢�������!���ڳ�ʼ��ϵͳ����,��Լ��Ҫ47��,���Ժ�... ----->");
	}
	#endif
}
/************************************************************!
*Function: Default_Handler
*Description:
*Input: null
*Output: null
*Return: null
*************************************************************/
void Default_Handler(void)
{
	//__asm volatile ("MRS %0, msp\n" : "=r" (ExceptionAddr) );
	//ExceptionAddr =  *((uint32_t*) ExceptionAddr+7);//��¼�쳣��ַ
}


/******************************************************************!
*Copyright (c), 2008-2017, Qingdao Topscomm Communication Co .Ltd.
*File name: mytask.c
*Version: 0.1.0
*Date: 2016-09-20
*Author: WANGJIANHUI
*Description:
*******************************************************************/
#include "include.h"
#include "mytask.h"
#include <stdlib.h>
#include <time.h>


/************************************************************!
*Function: Test_Task
*Description: ��������,������ʹ��
*Input: null
*Output: null
*Return: null
*************************************************************/
void Test_Task(void *pvParameters)
{
	#ifdef TASKSTACK_HIGHWATERMARK
	UBaseType_t uxHighWaterMark;
	uxHighWaterMark=uxTaskGetStackHighWaterMark(NULL);
	#endif

	while(1)
	{
		Wdog_Feed();

		//Gprs_StartTx();
		Gprs_Queue_Tx();
		WeiHu_StartTx();

		SysFlag_PrintOut();
		Au_Timing_Process();
		Gps_Timing_Process();
		Au_Offline_Process();
		//Au_WorkMode_Process();

		#ifdef TASKSTACK_HIGHWATERMARK
		uxHighWaterMark=uxTaskGetStackHighWaterMark(NULL);
		if(uxHighWaterMark<=100)
			DEBUG_PRINT_NISR("NSDS","��ǰ Test_Task ����ʣ���ջ�ռ�Ϊ: ",uxHighWaterMark*4," �ֽ�!\r\n");
		#endif
	}
}
/************************************************************!
*Function: Power_Monitor
*Description: ��Դ�������,�������Ҫ�����Ƕ�ʱ����������Դ�ĵ�ѹ,
*             �����ص�ѹС����ֵ,����PWM���,����رճ�硣
*Input: null
*Output: null
*Return: null
*************************************************************/
void Power_Monitor(void *pvParameters)
{
	uint8_t erratashift;
	uint32_t samples[3];

	#ifdef TASKSTACK_HIGHWATERMARK
	UBaseType_t uxHighWaterMark;
	uxHighWaterMark=uxTaskGetStackHighWaterMark(NULL);
	#endif

	erratashift=Adc0_Errata(); //��ȡADC��У������

	while (1)
	{
		Wdog_Feed();

		Timer2_Stop(); //������ѹǰ�ȹر�PWM����ֹ�����ĵ�ѹ���ݲ�׼ȷ

		vTaskDelay(pdMS_TO_TICKS(1000)); //�ر�PWM����ʱ100MS������ѹ�ȶ�

		DMA_ActivateBasic(0,true,false,samples,(void *)((uint32_t)&(ADC0->SCANDATA)),3-1);

		ADC_Start(ADC0,adcStartScan);

		while(ADC0->STATUS&ADC_STATUS_SCANACT); //�ȴ�SCAN���

		if(erratashift) //ADC����ֵ�Ƿ���ҪУ��
		{
			for(uint8_t i=0;i<3;i++)
				samples[i]<<=erratashift;
		}

		gSYSFLAG.CBV.SUN=samples[0]*((3.31/4096)*6*1000);
		gSYSFLAG.CBV.XDC=samples[1]*((3.31/4096)*6*1000);
		gSYSFLAG.CBV.CAP=samples[2]*((3.31/4096)*6*1000);

		Yc_Sudden_Report(&gECPINFO.YC.SUN_VOL,gSYSFLAG.CBV.SUN,gECPPARA.SUN_VOL_REPORT_THRESHOLD);
		Yc_Sudden_Report(&gECPINFO.YC.BAT_VOL,gSYSFLAG.CBV.XDC,gECPPARA.BATT_VOL_REPORT_THRESHOLD);

		if(gECPINFO.YC.BAT_VOL.MSG.U16<=gECPPARA.BATT_VOL_THRESHOLD) //���ص�ѹ������ֵ
		{
			if(gECPINFO.YX.LOW_POWER.MSG.U16==0) //֮ǰδ�����򱨾�
				Soe_Data_Record(&gECPINFO.YX.LOW_POWER,1,true,0);
		}

		if(gECPINFO.YC.BAT_VOL.MSG.U16>gECPPARA.BATT_VOL_THRESHOLD) //���ص�ѹ������ֵ
		{
			if(gECPINFO.YX.LOW_POWER.MSG.U16==1) //֮ǰ�ѱ����򸴹�
				Soe_Data_Record(&gECPINFO.YX.LOW_POWER,0,true,0);
		}

		if(gECPINFO.YC.BAT_VOL.MSG.U16>gECPINFO.YC.SUN_VOL.MSG.U16)
		{
			if(gECPINFO.YX.POWER_SWITCH.MSG.U16==0)
			{
				Soe_Data_Record(&gECPINFO.YX.POWER_SWITCH,1,true,0);
				Log_Data_Record(0x01,"S","�㼯��Ԫ��������̫���ܵ���л�Ϊ����!");
			}
		}

		if(gECPINFO.YC.BAT_VOL.MSG.U16<gECPINFO.YC.SUN_VOL.MSG.U16)
		{
			if(gECPINFO.YX.POWER_SWITCH.MSG.U16==1)
			{
				Soe_Data_Record(&gECPINFO.YX.POWER_SWITCH,0,true,0);
				Log_Data_Record(0x01,"S","�㼯��Ԫ�������������л�Ϊ̫���ܵ��!");
			}
		}

		if((gSYSFLAG.CBV.XDC<12)&&(gSYSFLAG.CBV.SUN>=17))
			Timer2_Start();
		else
			Timer2_Stop();

		#ifdef PRINT_SYS_VOL_DEBUG //ά���˿ڴ�ӡϵͳ��ѹ
		DEBUG_PRINT_NISR("KNSDSDSDKK","<----- �������ݵ�ѹ: ",(uint32_t)(gSYSFLAG.CBV.CAP)," ���ص�ѹ: ",(uint32_t)(gSYSFLAG.CBV.XDC)," ̫���ܵ�ѹ: ",(uint32_t)(gSYSFLAG.CBV.SUN));
		#endif

		vTaskDelay(pdMS_TO_TICKS(100000)); //5���Ӽ��һ�ε�ѹ

		#ifdef TASKSTACK_HIGHWATERMARK
		uxHighWaterMark=uxTaskGetStackHighWaterMark(NULL);
		if(uxHighWaterMark<=100)
			DEBUG_PRINT_NISR("NSDS","��ǰ Power_Monitor ����ʣ���ջ�ռ�Ϊ: ",uxHighWaterMark*4," �ֽ�!\r\n");
		#endif
	}
}
/************************************************************!
*Function: Ecp_Protocol_Comm
*Description:
*Input: null
*Output: null
*Return: null
*************************************************************/
void Icp_Protocol_Comm(void *pvParameters)
{
	#ifdef TASKSTACK_HIGHWATERMARK
	UBaseType_t uxHighWaterMark;
	uxHighWaterMark=uxTaskGetStackHighWaterMark(NULL);
	#endif

	while (1)
	{
		Wdog_Feed();

		gSYSFLAG.CWS.ICPSTATUS++;

		Icp_Process(&RADIOFRAME);
		Icp_Process(&WEIHUFRAME);

		Icp_Parse(&RADIO_RXDC,&RADIOFRAME);     //�ɼ���Ԫ��ά����Ƶͨ�Ŵ���
		Icp_Parse(&WEIHU_RXDC,&WEIHUFRAME);     //ά��232�˿�ͨ�Ŵ���

		#ifdef TASKSTACK_HIGHWATERMARK
		uxHighWaterMark=uxTaskGetStackHighWaterMark(NULL);
		if(uxHighWaterMark<=100)
			DEBUG_PRINT_NISR("NSDS","��ǰ Protocol_Comm ����ʣ���ջ�ռ�Ϊ: ",uxHighWaterMark*4," �ֽ�!\r\n");
		#endif
	}
}

/************************************************************!
*Function: Ecp_Protocol_Comm
*Description:
*Input: null
*Output: null
*Return: null
*************************************************************/
void Ecp_Protocol_Comm(void *pvParameters)
{
    #ifdef TASKSTACK_HIGHWATERMARK
    UBaseType_t uxHighWaterMark;
    uxHighWaterMark=uxTaskGetStackHighWaterMark(NULL);
	#endif

	while (1)
	{
		Wdog_Feed();

		//gSYSFLAG.CWS.ECPSTATUS++;

		Ecp_Process(&gECPFRAMELIST);

		Ecp_Parse(&GPRS_RXDC,&gECPFRAMELIST);   //GPRS�˿�101��Լ������

		#ifdef TASKSTACK_HIGHWATERMARK
		uxHighWaterMark=uxTaskGetStackHighWaterMark(NULL);
		if(uxHighWaterMark<=100)
			DEBUG_PRINT_NISR("NSDS","��ǰ Protocol_Comm ����ʣ���ջ�ռ�Ϊ: ",uxHighWaterMark*4," �ֽ�!\r\n");
		#endif
	}
}
/************************************************************!
*Function: Call_Wave
*Description: �ٻ����ϲ�������
*Input: null
*Output: null
*Return: null
*************************************************************/
void Call_Wave(void *pvParameters)
{
	#ifdef TASKSTACK_HIGHWATERMARK
	UBaseType_t uxHighWaterMark;
	uxHighWaterMark=uxTaskGetStackHighWaterMark(NULL);
	#endif

	while(1)
	{
		vTaskSuspend(NULL); //��������,�ȴ�����ң��֡��ұ�����

		vTaskDelay(pdMS_TO_TICKS(2000));

		Cu_Call_Wave(); //�ٻ�����

		#ifdef TASKSTACK_HIGHWATERMARK
		uxHighWaterMark=uxTaskGetStackHighWaterMark(NULL);
		if(uxHighWaterMark<=100)
			DEBUG_PRINT_NISR("NSDS","��ǰ Call_Wave ����ʣ���ջ�ռ�Ϊ: ",uxHighWaterMark*4," �ֽ�!\r\n");
		#endif
	}
}
/************************************************************!
*Function: Data_Report
*Description:
*Input: null
*Output: null
*Return: null
*************************************************************/
void Data_Report(void *pvParameters)
{
	#ifdef TASKSTACK_HIGHWATERMARK
	UBaseType_t uxHighWaterMark;
	uxHighWaterMark=uxTaskGetStackHighWaterMark(NULL);
	#endif

	while(1)
	{
		Wdog_Feed();

		Yc_Data_Record();

		Sys_Status_Report();

		ShortCircuit_Fault_Process();

		Ecp_Yc_Timing_Report(&gECPFRAMELIST);

		App_Send_P101SoeQueue(&gECPFRAMELIST,&gSOEQUEUE);     //SOE�����ϱ�
		//App_Send_P101FaultQueue(&gECPFRAMELIST,&gFAULTQUEUE); //���������ϱ�

		#ifdef TASKSTACK_HIGHWATERMARK
		uxHighWaterMark=uxTaskGetStackHighWaterMark(NULL);
		if(uxHighWaterMark<=100)
			DEBUG_PRINT_NISR("NSDS","��ǰ Data_Report ����ʣ���ջ�ռ�Ϊ: ",uxHighWaterMark*4," �ֽ�!\r\n");
		#endif
	}
}
/************************************************************!
*Function: Data_Send_Reply
*Description:
*Input: null
*Output: null
*Return: null
*************************************************************/
void Data_Send_Reply(void *pvParameters)
{
	#ifdef TASKSTACK_HIGHWATERMARK
	UBaseType_t uxHighWaterMark;
	uxHighWaterMark=uxTaskGetStackHighWaterMark(NULL);
	#endif

	while(1)
	{
		Wdog_Feed();

		App_Send_Reply(&gECPFRAMELIST);

		#ifdef TASKSTACK_HIGHWATERMARK
		uxHighWaterMark=uxTaskGetStackHighWaterMark(NULL);
		if(uxHighWaterMark<=100)
			DEBUG_PRINT_NISR("NSDS","��ǰ Data_Send_Reply ����ʣ���ջ�ռ�Ϊ: ",uxHighWaterMark*4," �ֽ�!\r\n");
		#endif
	}
}
/************************************************************!
*Function: Ecp_File_Report
*Description:
*Input: null
*Output: null
*Return: null
*************************************************************/
void Ecp_File_Report(void *pvParameters)
{
	#ifdef TASKSTACK_HIGHWATERMARK
	UBaseType_t uxHighWaterMark;
	uxHighWaterMark=uxTaskGetStackHighWaterMark(NULL);
	#endif

	while(1)
	{
		Wdog_Feed();

		Ecp_File_Send(&gECPFRAMELIST);

		#ifdef TASKSTACK_HIGHWATERMARK
		uxHighWaterMark=uxTaskGetStackHighWaterMark(NULL);
		if(uxHighWaterMark<=100)
			DEBUG_PRINT_NISR("NSDS","��ǰ Ecp_File_Report ����ʣ���ջ�ռ�Ϊ: ",uxHighWaterMark*4," �ֽ�!\r\n");
		#endif
	}
}
/************************************************************!
*Function: vApplicationIdleHook
*Description: �����Ӻ���
*Input: null
*Output: null
*Return: null
*************************************************************/
void vApplicationIdleHook(void *pvParameters)
{
	//EMU_EnterEM2(false);
}
/************************************************************!
*Function: Statistics_Au_Ticks
*Description:
*Input: null
*Output: null
*Return: null
*************************************************************/
void vApplicationStackOverflowHook(TaskHandle_t xTask,signed char *pcTaskName)
{
	DEBUG_PRINT_NISR("NSS","<------���� ",pcTaskName," ��ջ���!!!!------>\r\n");

	vTaskDelay(pdMS_TO_TICKS(500));
}
/************************************************************!
*Function: Statistics_Au_Ticks
*Description:
*Input: null
*Output: null
*Return: null
*************************************************************/
bool Power_Management(void)
{
//	if((gUNIXTIME.UNIX%600)!=0)
//		return false;
//
//
//	if(gSYSFLAG.CWS.CHARGE_STATUS==false)
//		Timer2_Stop(); //������ѹǰ�ȹر�PWM����ֹ�����ĵ�ѹ���ݲ�׼ȷ
//
//	vTaskDelay(pdMS_TO_TICKS(1000)); //�ر�PWM����ʱ100MS������ѹ�ȶ�
//
//	DMA_ActivateBasic(0,true,false,samples,(void *)((uint32_t)&(ADC0->SCANDATA)),3-1);
//
//	ADC_Start(ADC0,adcStartScan);
//
//	while(ADC0->STATUS&ADC_STATUS_SCANACT); //�ȴ�SCAN���
//
////		if(erratashift) //ADC����ֵ�Ƿ���ҪУ��
////		{
////			for(uint8_t i=0;i<3;i++)
////				samples[i]<<=erratashift;
////		}
//
//	gSYSFLAG.CBV.SUN=samples[0]*((3.31/4096)*6*1000);
//	gSYSFLAG.CBV.XDC=samples[1]*((3.31/4096)*6*1000);
//	gSYSFLAG.CBV.CAP=samples[2]*((3.31/4096)*6*1000);
//
//	Yc_Sudden_Deport(&gECPINFO.YC.SUN_VOL,gSYSFLAG.CBV.SUN,gECPPARA.SUN_VOL_REPORT_THRESHOLD);
//	Yc_Sudden_Deport(&gECPINFO.YC.BAT_VOL,gSYSFLAG.CBV.XDC,gECPPARA.BATT_VOL_REPORT_THRESHOLD);
//
//	if(gECPINFO.YC.BAT_VOL.MSG.U16<=gECPPARA.BATT_VOL_THRESHOLD) //���ص�ѹ������ֵ
//	{
//		if(gECPINFO.YX.LOW_POWER.MSG.U16==0) //֮ǰδ�����򱨾�
//			Soe_Data_Record(&gECPINFO.YX.LOW_POWER,1,true,0);
//	}
//
//	if(gECPINFO.YC.BAT_VOL.MSG.U16>gECPPARA.BATT_VOL_THRESHOLD) //���ص�ѹ������ֵ
//	{
//		if(gECPINFO.YX.LOW_POWER.MSG.U16==1) //֮ǰ�ѱ����򸴹�
//			Soe_Data_Record(&gECPINFO.YX.LOW_POWER,0,true,0);
//	}
//
//	if(gECPINFO.YC.BAT_VOL.MSG.U16>gECPINFO.YC.SUN_VOL.MSG.U16)
//	{
//		if(gECPINFO.YX.POWER_SWITCH.MSG.U16==0)
//			Soe_Data_Record(&gECPINFO.YX.POWER_SWITCH,1,true,0);
//
//		Log_Data_Record(0x01,"S","�㼯��Ԫ��������̫���ܵ���л�Ϊ����!");
//	}
//
//	if(gECPINFO.YC.BAT_VOL.MSG.U16<gECPINFO.YC.SUN_VOL.MSG.U16)
//	{
//		if(gECPINFO.YX.POWER_SWITCH.MSG.U16==1)
//			Soe_Data_Record(&gECPINFO.YX.POWER_SWITCH,0,true,0);
//
//		Log_Data_Record(0x01,"S","�㼯��Ԫ�������������л�Ϊ̫���ܵ��!");
//	}
//
//	if((gSYSFLAG.CBV.XDC<12)&&(gSYSFLAG.CBV.SUN>=17))
//		Timer2_Start();
//	else
//		Timer2_Stop();
//
//	#ifdef PRINT_SYS_VOL_DEBUG //ά���˿ڴ�ӡϵͳ��ѹ
//	DEBUG_PRINT_NISR("KNSDSDSDKK","<----- �������ݵ�ѹ: ",(uint32_t)(gSYSFLAG.CBV.CAP)," ���ص�ѹ: ",(uint32_t)(gSYSFLAG.CBV.XDC)," ̫���ܵ�ѹ: ",(uint32_t)(gSYSFLAG.CBV.SUN));
//	#endif
//
//	vTaskDelay(pdMS_TO_TICKS(10000)); //5���Ӽ��һ�ε�ѹ

	return true;
}
/************************************************************!
*Function: Statistics_Au_Ticks
*Description:
*Input: null
*Output: null
*Return: null
*************************************************************/
void Mx25_Erase_Test(uint32_t startaddr,uint32_t sectornum)
{
	uint8_t write[200],read[200];

	for(uint32_t i=0;i<200;i++)
		write[i]=i;

	Status_Led2_Clear();

	DEBUG_PRINT_NISR("KKNSDSDSDSKK","��ǰ���ڲ���FLASH,��ΧΪ�� ",startaddr/MX25_SECTOR_LEN," �ڵ��� ",(startaddr/MX25_SECTOR_LEN)+sectornum-1," ��,�� ",sectornum," ��FLASH...");

	for(uint32_t i=0;i<sectornum;i++)
	{
		Wdog_Feed();

		Mx25_Erase_Sector((startaddr/MX25_SECTOR_LEN)+i);
	}

	DEBUG_PRINT_NISR("KKNSKK","��ǰ����FLASH���!���ڶ�ȡ��FLASH������...");

	for(uint32_t i=0;i<((sectornum*MX25_SECTOR_LEN)/200);i++)
	{
		Wdog_Feed();

		Mx25_Read_U8_Array(startaddr+i*200,read,200,false);

		for(uint32_t j=0;j<200;j++)
		{
			if(read[j]!=0xFF)
			{
				DEBUG_PRINT_NISR("KKNSDSKK","��ǰ�� ",(startaddr+i*200)/MX25_SECTOR_LEN, " ��FLASH��Ϊ0xFF!");
				break;
			}
		}
	}

	DEBUG_PRINT_NISR("KKNSKK","��FLASH��ȡ�������,���ڽ���дFLASH����...");

	for(uint32_t i=0;i<((sectornum*MX25_SECTOR_LEN)/200);i++)
	{
		Wdog_Feed();

		Mx25_Write_U8_Array(startaddr+i*200,write,200,false);
	}

	DEBUG_PRINT_NISR("KKNSKK","дFLASH�������,���ڽ���FLASHд������֤...");

	for(uint32_t i=0;i<((sectornum*MX25_SECTOR_LEN)/200);i++)
	{
		Wdog_Feed();

		Mx25_Read_U8_Array(startaddr+i*200,read,200,false);

		if(memcmp(write,read,200)!=0)
			DEBUG_PRINT_NISR("KKNSDSKK","��ǰ �� ",(startaddr+i*200)/MX25_SECTOR_LEN, " ��FLASHд����ʧ��!");
	}

	DEBUG_PRINT_NISR("KKNSKK","FLASH�������!���ڲ���FLASH");

	for(uint32_t i=0;i<sectornum;i++)
	{
		Wdog_Feed();

		Mx25_Erase_Sector((startaddr/MX25_SECTOR_LEN)+i);
	}

	DEBUG_PRINT_NISR("KKNSKK","FLASH�������!!!!!");

	Status_Led2_Set();
}


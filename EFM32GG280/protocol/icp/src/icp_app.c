/******************************************************************!
*Copyright (c), 2008-2017, Qingdao Topscomm Communication Co .Ltd.
*File name: icp_app.c
*Version: 0.1.0
*Date: 2016-09-20
*Author: WANGJIANHUI
*Description:
*******************************************************************/
#include "include.h"


/************************************************************!
*Function: Icp_PduType_Process
*Description:
*Input:
*Output: null
*Return: null
*************************************************************/
void Icp_PduType_Process(ICPFRAME *IF)
{
	switch (IF->TYPE)
	{
		case TIMESTAMP:  //ʱ��
			App_Timestamp_Process(IF);
			break;

		case DBYC:       //ң��
			App_Yc_Process(IF);
			break;

		case DBSOE:      //SOE
			App_Soe_Yx_Process(IF);
			break;

		case DBWAVE:     //¼������
			App_Wave_Process(IF);
			break;

		case DBPARA:     //����
			App_Para_Process(IF);
			break;

		case DBPROG:     //����
			App_Program_Process(IF);
			break;

		case FAULTWRG:   //����¼��
			App_Faultwrg_Process(IF);
			break;

		case LED:        //��Ʋ���
			App_Led_Process(IF);
			break;

		case WAKEUP:     //ά����Ԫ����
			App_WakeUp_Process(IF);
			break;

		case DBYX:       //��ʱ��ң��
			App_Soe_Yx_Process(IF);
			break;

		case RSTPROCESS: //��λ����
			App_Reset_Process(IF);
			break;

		case WORKMODE:   //����ģʽ
			App_WorkMode_Process(IF);
			break;

		case ERASEFLASH: //����FLASH
			DEBUG_ERASE_MX25(IF);
			break;

		case READLOG:    //��ȡLOG
			DEBUG_READ_LOG();
			break;

		case ECPREADLOG: //ģ���ȡLOG
		    DEBUG_ECP_READ_LOG();
			break;

		case READSOE:    //��ȡSOE
			DEBUG_READ_SOE();
			break;

		case ECPREADSOE: //ģ���ȡSOE
			DEBUG_ECP_READ_SOE();
			break;

		case READYC:     //��ȡYC
			DEBUG_READ_YC();
			break;

		case ECPREADYC:  //ģ���ȡYC
			DEBUG_ECP_READ_YC(IF->IFD.DATA[0]);
			break;

		case READFAULT:  //��ȡFAULT
			DEBUG_READ_FAULT();
			break;

		case ECPREADFAULT://ģ���ȡFAULT
			DEBUG_ECP_READ_FAULT();
			break;

		case READYK:  //��ȡYK
			DEBUG_READ_YK();
			break;

		case ECPREADYK://ģ���ȡYK
			DEBUG_ECP_READ_YK();
			break;

		case READWAVE:  //��ȡWAVE
			DEBUG_READ_WAVE();
			break;

		case ECPREADWAVE://ģ���ȡWAVE
			DEBUG_ECP_READ_WAVE(IF->IFD.DATA[0]);
			break;

		case NOWTIME:     //��ȡTIME
			DEBUG_READ_NOWTIME();
			break;

		case ERASEPARA:     //��������������
			DEBUG_ERASE_PARABLOCK();
			break;

		case ECPSTARTWAVE:
			DEBUG_ECP_START_WAVE(IF);
			break;

		default:
			break;
	}

	Au_Online_Process(IF);  //�ɼ���Ԫ���ߴ���
}
/************************************************************!
*Function: App_Timestamp_Process
*Description:
*Input:
*Output: null
*Return: null
*************************************************************/
void App_Timestamp_Process(ICPFRAME *IF)
{
	if(IF->PHASE==0)
		gSYSFLAG.AWS.ASF[IF->LINE].AU_TIMING_ACK+=1;
	if(IF->PHASE==1)
		gSYSFLAG.AWS.ASF[IF->LINE].AU_TIMING_ACK+=2;
	if(IF->PHASE==2)
		gSYSFLAG.AWS.ASF[IF->LINE].AU_TIMING_ACK+=4;

	#ifdef PRINT_AU_TIMING_ASYNC_DEBUG
	DEBUG_PRINT_NISR("KNSDSDSK","<----- �յ� ",IF->LINE," �� ",IF->PHASE," �Ųɼ���Ԫ��УʱӦ��֡! ----->");
	if(gSYSFLAG.AWS.ASF[IF->LINE].AU_TIMING_ACK!=0&&gSYSFLAG.AWS.ASF[IF->LINE].AU_TIMING_ACK%7==0)
		DEBUG_PRINT_NISR("KNSDSKK","<----- ��ǰ ",IF->LINE," �ߵ�ʱ���Ѿ�ͬ��! ----->");
	#endif
}
/************************************************************!
*Function: App_Yc_Process
*Description:
*Input:
*Output: null
*Return: null
*************************************************************/
bool App_Yc_Process(ICPFRAME *IF)
{
	if((IF->LEN1-ICP_MINPDULEN)<9) //��Խ��,ң������һ��9���ֽ�
		return false;

	gSYSFLAG.STM.YC_RECEIVE=gUNIXTIME.UNIX; //����ң�����ݽ���ʱ��

	if(gYCFILE.TIME.YEAR==0) //�ж�ң�⻺��ʱ��Ϊ��
		NowTime2P101Time(gYCFILE.TIME.DATA,7); //������ǰʱ���

	Yc_Sudden_Report(&gECPINFO.YC.ECPYC[IF->LINE].CUR[IF->PHASE],IF->IFD.I,gECPPARA.I_REPORT_THRESHOLD);

	Yc_Sudden_Report(&gECPINFO.YC.ECPYC[IF->LINE].VOL[IF->PHASE],IF->IFD.U,gECPPARA.U_REPORT_THRESHOLD);

	Yc_Sudden_Report(&gECPINFO.YC.ECPYC[IF->LINE].TEM[IF->PHASE],IF->IFD.T,gECPPARA.T_REPORT_THRESHOLD);

	Yc_Sudden_Report(&gECPINFO.YC.ECPYC[IF->LINE].AU_BAT_VOL[IF->PHASE],IF->IFD.B,gECPPARA.B_REPORT_THRESHOLD);


	if(gSYSFLAG.AWS.ASF[IF->LINE].AU_WORKMODE[IF->PHASE]!=IF->IFD.WORKMODE)  //����ģʽ��һ��
	{
		Modify_Au_WorkMode(IF->LINE,IF->PHASE,IF->IFD.WORKMODE);
		//gSYSFLAG.AWS.ASF[IF->LINE].AU_WORKMODE[IF->PHASE]=IF->IFD.WORKMODE;  //���»㼯��Ԫ�еĹ���ģʽ

//		if(gSYSFLAG.AWS.ASF[IF->LINE].AU_WORKMODE[IF->PHASE]==0)
//			Log_Data_Record(0x0A,"DSDS",IF->LINE," �� ",IF->PHASE," �Ųɼ���Ԫ���л�Ϊȫ����ģʽ!");
//		if(gSYSFLAG.AWS.ASF[IF->LINE].AU_WORKMODE[IF->PHASE]==1)
//			Log_Data_Record(0x0A,"DSDS",IF->LINE," �� ",IF->PHASE," �Ųɼ���Ԫ���л�Ϊ�˻�ģʽ!");
	}

	#ifdef PRINT_AU_YC_DATA_DEBUG
	DEBUG_PRINT_YC_DATA(IF);
	#endif

	#ifdef AU_YC_LOST_STATS_DEBUG //ң�����ݵ���ͳ��,������ʹ��
	if(IF->PHASE==0)
		gSYSFLAG.AWS.ASF[IF->LINE].AU_YC_REPORT+=1;
	if(IF->PHASE==1)
		gSYSFLAG.AWS.ASF[IF->LINE].AU_YC_REPORT+=2;
	if(IF->PHASE==2)
		gSYSFLAG.AWS.ASF[IF->LINE].AU_YC_REPORT+=4;
	#endif

	return true;
}
/************************************************************!
*Function: App_Yx_Soe_Process
*Description:
*Input:
*Output: null
*Return: null
*************************************************************/
bool App_Soe_Yx_Process(ICPFRAME *IF)
{
	if((gUNIXTIME.UNIX-gSYSFLAG.STM.STC[IF->LINE].AU_SOE_TIME[IF->PHASE])<5) //����N���ڵ�SOE�ط�����
		return false;

	gSYSFLAG.STM.STC[IF->LINE].AU_SOE_TIME[IF->PHASE]=gUNIXTIME.UNIX;    //����SOE����ʱ��

	if(IF->TYPE==DBSOE) //��ʱ���ң��
	{
		if((IF->LEN1-ICP_MINPDULEN)<9) //��Խ��,��ʱ���ң������һ��9���ֽ�
			return false;

		UnixTime2P101Time(&IF->IFD.TIME,IF->IFD.DATA,7); //���ɼ���Ԫʱ��ת��Ϊ101ʱ��
	}

	if(IF->TYPE==DBYX) //����ʱ���ң��
	{
		if((IF->LEN1-ICP_MINPDULEN)<1) //��Խ��,����ʱ���ң������һ��1���ֽ�
			return false;

		IF->IFD.SOE.DATA=IF->IFD.YX.DATA;
		NowTime2P101Time(IF->IFD.DATA,7); //��¼��ǰʱ��
	}

	if(IF->IFD.SOE.SHUNSHI==0x01) //˲ʱ�Զ�·
		Soe_Data_Record(&gECPINFO.YX.ECPYX[IF->LINE].SHUNSHI_FAULT[IF->PHASE],IF->IFD.SOE.FUGUI,true,IF->IFD.DATA);

	if(IF->IFD.SOE.YONGJIU==0x01) //�����Զ�·
		Soe_Data_Record(&gECPINFO.YX.ECPYX[IF->LINE].YONGJIU_FAULT[IF->PHASE],IF->IFD.SOE.FUGUI,true,IF->IFD.DATA);

	if(IF->IFD.SOE.IOVERRUN==0x01) //��������
		Soe_Data_Record(&gECPINFO.YX.ECPYX[IF->LINE].CUR_OVER[IF->PHASE],IF->IFD.SOE.FUGUI,true,IF->IFD.DATA);

	if(IF->IFD.SOE.LOWPOWER==0x01) //���Ƿѹ
		Soe_Data_Record(&gECPINFO.YX.ECPYX[IF->LINE].AU_LOW_POWER[IF->PHASE],IF->IFD.SOE.FUGUI,true,IF->IFD.DATA);

	Fill_Icp_Frame(IF->CHANNEL,IF->SRCADDR,0x00,0x03,1,1,0,0);
	Fill_Icp_Frame(IF->CHANNEL,IF->SRCADDR,0x00,0x03,1,1,0,0);

	return true;
}
/************************************************************!
*Function: App_Wave_Process
*Description:
*Input:
*Output: null
*Return: null
*************************************************************/
bool App_Wave_Process(ICPFRAME *IF)
{
	WAVE_DAT_FORMAT WDF;

	if(((IF->LEN1-ICP_MINPDULEN)%4)!=0) //�˴����¼�����ݳ��ȱ���Ҫ��4�ı���,��ֹ��������Խ��,Ҫ��ɼ���Ԫ���ƴ˳���
		return false;

	if(IF->FRAMESEQ!=gFAULTINFO.FRAMESEQ) //������֡,��¼��־
		return false;

	if(IF->FRAMESEQ!=gFAULTINFO.FRAMENUM) //�����һ֡,���ݳ���ӦΪ WAVE_FRAME_LEN,����
	{
		if((IF->LEN1-ICP_MINPDULEN)!=WAVE_FRAME_LEN)
			return false;
	}

	for(uint8_t write=0;write<((IF->LEN1-ICP_MINPDULEN)/4);write++) //��������ݷֿ��洢,����������ǰ
	{
		memcpy(gFAULTINFO.WAVE[IF->PHASE].CUR+(IF->FRAMESEQ-1)*(WAVE_FRAME_LEN/4)+write,IF->IFD.DATA+(write*4+0),2*sizeof(uint8_t));
		memcpy(gFAULTINFO.WAVE[IF->PHASE].VOL+(IF->FRAMESEQ-1)*(WAVE_FRAME_LEN/4)+write,IF->IFD.DATA+(write*4+2),2*sizeof(uint8_t));
	}

	xTaskNotifyGive(xCall_Wave); //�ٻ���������֪ͨ

	#ifdef PRINT_AU_WAVE_DATA_DEBUG //��ӡ¼������֡
	DEBUG_PRINT_NISR("KNSDSDSDSDSDSK","<----- �յ����� ",IF->LINE," �� ",IF->PHASE," �Ųɼ���Ԫ�Ĳ�������,�� ",gFAULTINFO.FRAMENUM," ֡,�� ",gFAULTINFO.FRAMESEQ," ֡,�� ",IF->LEN1-ICP_MINPDULEN," �ֽ�����!");
	DEBUG_PRINT_U8CHAR_ARRAY_NISR(IF->DATA,IF->LEN1-ICP_MINPDULEN);
	DEBUG_PRINT_NISR("KK");
	#endif

	if((IF->FRAMESEQ==IF->FRAMENUM)&&(IF->PHASE==2)) //��ABC�����һ��CҲ¼�����ʱ
	{
		//Correct_The_Phase(); //ABC�������λ����

		for(uint32_t i=0;i<gFAULTINFO.WAVELEN;i++) //�����ѹ�������ݺϳ���������
		{
			gFAULTINFO.ZEROI[i]=gFAULTINFO.WAVE[0].CUR[i]+gFAULTINFO.WAVE[1].CUR[i]+gFAULTINFO.WAVE[2].CUR[i];
			gFAULTINFO.ZEROU[i]=gFAULTINFO.WAVE[0].VOL[i]+gFAULTINFO.WAVE[1].VOL[i]+gFAULTINFO.WAVE[2].VOL[i];
		}

		#ifdef PRINT_WAVE_DEBUG //��ӡ��ѹ��������
		vTaskSuspendAll();
		for(uint8_t i=0;i<3;i++)
		{
			DEBUG_PRINT_NISR("KKSDSDSKK","<----- ���ڴ�ӡ�� ",gFAULTINFO.LINE, " �� ",i," �Ųɼ���Ԫ�ĵ�������:");
			DEBUG_PRINT_S16_ARRAY_NISR(gFAULTINFO.WAVE[i].CUR,gFAULTINFO.WAVELEN);
			DEBUG_PRINT_NISR("KKSDSDSKK","<----- ���ڴ�ӡ�� ",gFAULTINFO.LINE, " �� ",i," �Ųɼ���Ԫ�ĵ�ѹ����:");
			DEBUG_PRINT_S16_ARRAY_NISR(gFAULTINFO.WAVE[i].VOL,gFAULTINFO.WAVELEN);
			DEBUG_PRINT_NISR("KK");
		}

		DEBUG_PRINT_NISR("KKSDSKK","<----- ���ڴ�ӡ�� ",gFAULTINFO.LINE, " �ߵ������������:");
		DEBUG_PRINT_S16_ARRAY_NISR(gFAULTINFO.ZEROI,gFAULTINFO.WAVELEN);
		DEBUG_PRINT_NISR("KKSDSKK","<----- ���ڴ�ӡ�� ",gFAULTINFO.LINE, " �ߵ������ѹ����:");
		DEBUG_PRINT_S16_ARRAY_NISR(gFAULTINFO.ZEROU,gFAULTINFO.WAVELEN);
		DEBUG_PRINT_NISR("KK");
		xTaskResumeAll();
		#endif

		if(gFAULTINFO.TYPE==1) //�ж��Ƿ�Ϊ�ӵع���
		{
			//if(�ӵع��ϲ����ж��㷨==false)
				//return false;

			Fill_Icp_Frame(RADIO_CHANNEL,gSYSPARA.BROADCAST,0x40,0x08,1,1,&gFAULTINFO.LINE,1); //���������ź�
		}

		Switch_NextWave_Position(); //�л����δ洢ָ������һ�ļ�

		Wave_Cfg_File_Init(); //�����ļ�ͷ��ʼ��

		memset(WDF.DATA,0,WAVE_INFO_LEN); //���

		vTaskSuspendAll();

		for(uint32_t i=0;i<gFAULTINFO.WAVELEN;i++) //�������ݼ��㼰�洢
		{
			Wdog_Feed(); //��ʱι��

			WDF.N=i+1;
			WDF.TIMESTAMP=0;
			WDF.AU=(uint16_t)gFAULTINFO.WAVE[0].VOL[i];
			WDF.BU=(uint16_t)gFAULTINFO.WAVE[1].VOL[i];
			WDF.CU=(uint16_t)gFAULTINFO.WAVE[2].VOL[i];
			WDF.AI=(uint16_t)gFAULTINFO.WAVE[0].CUR[i];
			WDF.BI=(uint16_t)gFAULTINFO.WAVE[1].CUR[i];
			WDF.CI=(uint16_t)gFAULTINFO.WAVE[2].CUR[i];
			WDF.ZU=(uint16_t)gFAULTINFO.ZEROU[i];
			WDF.ZI=(uint16_t)gFAULTINFO.ZEROI[i];
			WDF.YX=0x0000;     //SOE����δ����

			Wave_Data_Record(WDF.DATA,WAVE_INFO_LEN);	 //���δ洢
		}

		xTaskResumeAll();

		memset(gFAULTINFO.DATA,0,FAULT_DATA_LEN); //���gFAULTINFO

		Soe_Data_Record(&gECPINFO.YX.WAVEFILE,1,true,0);

		#ifdef PRINT_WAVE_FILE_DEBUG //��ӡ��ǰ�����ļ�
		DEBUG_PRINT_WAVE(WAVE_START_ADDR1+((gSYSFLAG.MFW.WAVE-WAVE_START_ADDR1)/WAVE_FILE_LEN)*WAVE_FILE_LEN);
		#endif
	}

	return true;
}
/************************************************************!
*Function: App_Para_Process
*Description:
*Input:
*Output: null
*Return: null
*************************************************************/
bool App_Para_Process(ICPFRAME *IF)
{
	SYSPARA SP;
	uint8_t priority,sn;

	if(IF->CTRL.PRM==1) //ά�������ȡ�㼯��Ԫ����
	{
		if(IF->CTRL.CC==FCSENDDATA) //�޸Ĳ���
		{
			if((IF->LEN1-ICP_MINPDULEN)!=SYSPARA_NUM)
				return false;

			Mx25_Erase_Sector(SYSPARA_ADDR/MX25_SECTOR_LEN);

			Mx25_Data_Storage(SYSPARA_ADDR,IF->IFD.DATA,SYSPARA_NUM);

			Fill_Icp_Frame(IF->CHANNEL,IF->SRCADDR,0x00,0x06,1,1,0,0);

			Log_Data_Record(0x0A,"S","ά��������޸Ļ㼯��Ԫ�Ĳ�����Ϣ!");

			vTaskDelay(pdMS_TO_TICKS(2000));

			SCB->AIRCR=0x05FA0004;  //M3�ں˸�λ����
		}

		if(IF->CTRL.CC==FCREQUESTD) //������
		{
			Mx25_Read_U8_Array(SYSPARA_ADDR,SP.DATA,SYSPARA_NUM,false);

			if(SP.LINEGROUP.LINE[0].LINENO!=0xFF)  //��MX25����
				memcpy(IF->IFD.DATA,SP.DATA,SYSPARA_NUM);

			if(SP.LINEGROUP.LINE[0].LINENO==0xFF)  //��MX25����,����Ĭ�ϲ���
				memcpy(IF->IFD.DATA,gSYSPARA.DATA,SYSPARA_NUM);

			Fill_Icp_Frame(IF->CHANNEL,IF->SRCADDR,0x00,0x06,1,1,IF->IFD.DATA,SYSPARA_NUM);

			Log_Data_Record(0x0A,"S","ά������Ѷ�ȡ�㼯��Ԫ�Ĳ�����Ϣ!");

			#ifdef PRINT_READ_SYSPARA_DEBUG
			#endif
		}
	}

	if(IF->CTRL.PRM==0) //��վ��ȡ�ɼ���Ԫ����
	{
		memcpy(gECPFRAMELIST.AP.DATA,IF->IFD.DATA,25);

		priority=8;
		sn=Req_Empty_ResFrame(&gECPFRAMELIST,priority); //������õ�Ӧ��֡

		gECPFRAMELIST.RES[priority].ETQ[sn].EF.VF.CTRL.DATA=0xD3;
		gECPFRAMELIST.RES[priority].ETQ[sn].EF.VF.ASDU.TI=102;
		gECPFRAMELIST.RES[priority].ETQ[sn].EF.VF.ASDU.VSQ=1;
		gECPFRAMELIST.RES[priority].ETQ[sn].EF.VF.ASDU.COT.U16=7;
		gECPFRAMELIST.RES[priority].ETQ[sn].EF.VF.ASDU.MSGADDR.U16=gECPFRAMELIST.AP.MSGADDR.U16;

		if(gECPFRAMELIST.AP.MSGADDR.U8[0]<=7) //ǰ7������Ϊ16λ,��ַ��01-14
		{
			memcpy(gECPFRAMELIST.RES[priority].ETQ[sn].EF.VF.ASDU.MSG,gECPFRAMELIST.AP.DATA+(gECPFRAMELIST.AP.MSGADDR.U8[0]-1)*2,2);
			Fill_Ecp_Frame(&gECPFRAMELIST,VAR_FRAME,priority,sn,2);
		}
		if(gECPFRAMELIST.AP.MSGADDR.U8[0]>7)//����Ĳ���Ϊ8λ,��15-
		{
			memcpy(gECPFRAMELIST.RES[priority].ETQ[sn].EF.VF.ASDU.MSG,gECPFRAMELIST.AP.DATA+6+gECPFRAMELIST.AP.MSGADDR.U8[0],1);
			Fill_Ecp_Frame(&gECPFRAMELIST,VAR_FRAME,priority,sn,1);
		}

		Log_Data_Record(0x0A,"S","��վ�Ѷ�ȡ�ɼ���Ԫ�Ĳ�����Ϣ!");
	}

	return true;
}
/************************************************************!
*Function: App_Prog_Process
*Description:
*Input:
*Output: null
*Return: null
*************************************************************/
bool App_Program_Process(ICPFRAME *IF)
{
	DOUBLEBYTE FRAMENUM,FRAMESEQ,TMP;
	static uint32_t framenum,datalens;

	memcpy(FRAMENUM.U8,IF->IFD.DATA+0,2*sizeof(uint8_t)); //����֡����
    memcpy(FRAMESEQ.U8,IF->IFD.DATA+2,2*sizeof(uint8_t)); //����֡���

	if(FRAMESEQ.U16==1) //���յ�������ݵĵ�һ֡
	{
		datalens=0;
		framenum=FRAMENUM.U16;
		gSYSFLAG.CWS.UPDATING=true;

		for(uint32_t i=0;i<BACKUP_PAGE_NUM;i++) //�������ݳ�����
			Msc_ErasePage(BACKUP_PRM_KEY+i*MSC_PAGE_LEN); //��ʱû�п��ǹ��ж�
	}

	if(gSYSFLAG.CWS.UPDATING==false) //����
		return false;

	if(framenum!=FRAMENUM.U16)
	{
		//Log_Data_Record(0x03,"SDSD","���³��������֡������!��ȷ֡��Ϊ: ",framenum," �����֡��Ϊ: ",FRAMENUM.U16);

		return false;
	}

	#ifdef PRINT_PROGRAM_DEBUG
	DEBUG_PRINT_NISR("KNSDSDSK","<----- �յ������������֡,�� ",FRAMENUM.U16," ֡,�� ",FRAMESEQ.U16," ֡:");
	DEBUG_PRINT_U8CHAR_ARRAY_NISR(IF->IFD.DATA,IF->LEN1-ICP_MINPDULEN-4);
	DEBUG_PRINT_NISR("KK");
	#endif

	if(FRAMESEQ.U16!=FRAMENUM.U16) //�����һ֡����
	{
		if(Msc_ReadWord(BACKUP_PROGRAM+(FRAMESEQ.U16-1)*BACKUP_PRM_BLOCK)==0xFFFFFFFF) //����д
		{
			datalens+=IF->LEN1-ICP_MINPDULEN-4;  //��������ļ�����

			Program_Storage(FRAMESEQ.U16,IF->IFD.DATA+4,IF->LEN1-ICP_MINPDULEN-4); //д���̳�������
		}
	}

	if(FRAMESEQ.U16==FRAMENUM.U16) //���յ�������ݵ����һ֡
	{
		for(uint32_t i=0;i<(FRAMENUM.U16-1);i++)
		{
			if(Msc_ReadWord(BACKUP_PROGRAM+i*BACKUP_PRM_BLOCK)==0xFFFFFFFF)
			{
				memcpy(TMP.U8,&i,2);

				Fill_Icp_Frame(RADIO_CHANNEL,IF->SRCADDR,0x00,0x06,1,1,TMP.U8,2); //��ʧ֡����

				#ifdef PRINT_PROGRAM_DEBUG
				DEBUG_PRINT_NISR("NSDS","<----- ���³����ļ�ȱ�ٵ� ",TMP.U16," ֡!");
				#endif

				return false;
			}
		}

		#ifdef PRINT_PROGRAM_DEBUG
		DEBUG_PRINT_NISR("KNSK","<----- ���³����޶�ʧ֡,������������!����У������ļ�......");
		#endif

		memcpy(TMP.U8,IF->IFD.DATA+4,2); //������λ����CS

		if(TMP.U16!=Get_Program_Cs(datalens))
		{
			#ifdef PRINT_PROGRAM_DEBUG
			DEBUG_PRINT_NISR("KSKK","<-----���³�����ļ�У�������!");
			#endif

			return false;
		}

		#ifdef PRINT_PROGRAM_DEBUG
		DEBUG_PRINT_NISR("KNSKK","<----- �����ļ�У�����ȷ,���������㼯��Ԫ,���Ժ�......");
		#endif

		gSYSFLAG.CWS.UPDATING=false;

		Msc_WriteWord(BACKUP_PRM_KEY,0x05FA05FB); //д������Կ

		Fill_Icp_Frame(RADIO_CHANNEL,IF->SRCADDR,0x00,0x06,1,1,IF->IFD.DATA,4);

		vTaskDelay(pdMS_TO_TICKS(2000));

		SCB->AIRCR=0x05FA0004;  //M3�ں˸�λ����
	}

	Fill_Icp_Frame(RADIO_CHANNEL,IF->SRCADDR,0x00,0x06,1,1,IF->IFD.DATA,4); //����ACK

	return true;
}
/************************************************************!
*Function: App_Faultwrg_Process
*Description:
*Input:
*Output: null
*Return: null
*************************************************************/
bool App_Faultwrg_Process(ICPFRAME *IF)
{
	if((IF->LEN1-ICP_MINPDULEN)<8) //��Խ��,����¼������һ��9���ֽ�
		return false;

	Trigger_Start_Call_Wave(IF->LINE,IF->IFD.DATA);

	return true;
}
/************************************************************!
*Function: App_Led_Process
*Description:
*Input:
*Output: null
*Return: null
*************************************************************/
void App_Led_Process(ICPFRAME *IF)
{
	Status_Led2_Toggle();
}
/************************************************************!
*Function: App_WakeUp_Process
*Description:
*Input:
*Output: null
*Return: null
*************************************************************/
void App_WakeUp_Process(ICPFRAME *IF)
{
	Fill_Icp_Frame(IF->CHANNEL,IF->SRCADDR,0x00,0x0A,1,1,0,0);

	//Log_Data_Record(0x01,"S","�㼯��Ԫ�յ�ά�������ID����֡!");
}
/************************************************************!
*Function: App_Rst_Process
*Description:
*Input:
*Output: null
*Return: null
*************************************************************/
void App_Reset_Process(ICPFRAME *IF)
{
	if(memcmp(gSYSPARA.WEIHU,IF->SRCADDR,6)==0) //�յ�ά������ĸ�λ����
	{
		Fill_Icp_Frame(IF->CHANNEL,IF->SRCADDR,0x00,0x0C,1,1,0,0);

		Log_Data_Record(0x01,"S","�㼯��Ԫ�յ�ά������ĳ���λ����!");

		vTaskDelay(pdMS_TO_TICKS(1000)); //��ʱ1S

		SCB->AIRCR=0x05FA0004;  //M3�ں˸�λ����
	}

	Log_Data_Record(0x05,"DSDS",IF->LINE," �� ",IF->PHASE," �Ųɼ���Ԫ����λ!");
}
/************************************************************!
*Function: App_WorkMode_Process
*Description:
*Input:
*Output: null
*Return: null
*************************************************************/
bool App_WorkMode_Process(ICPFRAME *IF)
{
	if((IF->LEN1-ICP_MINPDULEN)<1) //��Խ��,ģʽ�л�����һ��1���ֽ�
		return false;

	if(IF->IFD.DATA[0]==1)  //�˻�
	{
		gSYSFLAG.AWS.ASF[IF->LINE].WORKMODE=1;  //�˻�

		#ifdef PRINT_AU_WORKMODE_DEBUG
		DEBUG_PRINT_NISR("KKDSKK",IF->LINE," �ߵĲɼ���Ԫ���л�Ϊ�˻�ģʽ!");
		#endif

		return true;
	}

	if(IF->PHASE==0)
		gSYSFLAG.AWS.ASF[IF->LINE].AU_WORKMODE_ACK+=1;
	if(IF->PHASE==1)
		gSYSFLAG.AWS.ASF[IF->LINE].AU_WORKMODE_ACK+=2;
	if(IF->PHASE==2)
		gSYSFLAG.AWS.ASF[IF->LINE].AU_WORKMODE_ACK+=4;

	gSYSFLAG.STM.STC[IF->LINE].AU_WORKMODE_MARK[IF->LINE]=gUNIXTIME.UNIX;

	if(IF->IFD.DATA[0]==1)
		Log_Data_Record(0x0A,"DSDS",IF->LINE," �� ",IF->PHASE," �Ųɼ���Ԫ���л�Ϊ�˻�ģʽ!");
	if(IF->IFD.DATA[0]==0)
		Log_Data_Record(0x0A,"DSDS",IF->LINE," �� ",IF->PHASE," �Ųɼ���Ԫ���л�Ϊȫ����ģʽ!");

	return true;
}
/************************************************************!
*Function: Modify_Au_WorkMode
*Description:
*Input:
*Output: null
*Return: null
*************************************************************/
bool Modify_Au_WorkMode(uint8_t line,uint8_t phase,uint8_t workmode)
{
	if(workmode==0) //�л�Ϊȫ����ģʽ
	{
		//gSYSFLAG.AWS.ASF[line].WORKMODE_SWITCH=1;
		gSYSFLAG.AWS.ASF[line].AU_WORKMODE[phase]=0;                     //�˴�����ҪĿ�����޸ĸ��ߵĹ���״̬,ʹ��������Уʱ
		gSYSFLAG.AWS.ASF[line].AU_TIMING_ASYNC=AU_TIMING_ASYNC_BUFFER;   //�޸�Уʱ�첽ͳ��,�����Ը��߽��л���Уʱͬ��
	}

	if(workmode==1) //�л�Ϊ�˻�ģʽ
	{
		gSYSFLAG.AWS.ASF[line].AU_WORKMODE[phase]=1;
	}

	for(uint8_t line=0;line<LINEGROUP_MAXNUM;line++)
	{
		if(gSYSPARA.LINEGROUP.LINE[line].LINENO==0)
			continue;

		if(gSYSFLAG.AWS.ASF[line].WORKMODE==0) //ȫ����
		{
			for(uint8_t phase=0;phase<3;phase++)
			{
				if(gSYSFLAG.AWS.ASF[line].AU_WORKMODE[phase]==0)
					continue;

				gSYSFLAG.AWS.ASF[line].WORKMODE=1;

				Soe_Data_Record(&gECPINFO.YX.LINE_WORKMODE[line],1,true,0);

				Log_Data_Record(0x0A,"DS",line," �ߵĲɼ���Ԫ��ȫ���л�Ϊ�˻�ģʽ!");

				return true;
			}
		}

		if(gSYSFLAG.AWS.ASF[line].WORKMODE==1) //�˻�
		{
			for(uint8_t phase=0;phase<3;phase++)
			{
				if(gSYSFLAG.AWS.ASF[line].AU_WORKMODE[phase]==1)
					return true;
			}

			gSYSFLAG.AWS.ASF[line].WORKMODE=0;

			Soe_Data_Record(&gECPINFO.YX.LINE_WORKMODE[line],0,true,0);

			Log_Data_Record(0x0A,"DS",line," �ߵĲɼ���Ԫ��ȫ���л�Ϊȫ����ģʽ!");
		}
	}

	return true;
}
/************************************************************!
*Function: Au_Online_Process
*Description:
*Input:
*Output: null
*Return: null
*************************************************************/
bool Au_Online_Process(ICPFRAME *IF)
{
	if((IF->LINE==0xFF)||(IF->PHASE==0xFF)) //�ǲɼ���Ԫ��ĵ�ַ�ϱ�������
		return false;

	gSYSFLAG.STM.STC[IF->LINE].AU_OFFLINE_MARK[IF->PHASE]=gUNIXTIME.UNIX;

	if(gECPINFO.YX.ECPYX[IF->LINE].COMM_FAULT[IF->PHASE].MSG.U16==0) //֮ǰδ����ͨ�Ź���
		return false;

	Modify_Au_WorkMode(IF->LINE,IF->PHASE,0);

	Soe_Data_Record(&gECPINFO.YX.ECPYX[IF->LINE].COMM_FAULT[IF->PHASE],0,true,0);

	return true;
}
/************************************************************!
*Function: Au_Offline_Process
*Description:
*Input:
*Output: null
*Return: null
*************************************************************/
void Au_Offline_Process(void)
{
	for(uint8_t line=0;line<LINEGROUP_MAXNUM;line++)
	{
		if(gSYSPARA.LINEGROUP.LINE[line].LINENO==0) //��Ч�ɼ���Ԫ��
			continue;

		for(uint8_t phase=0;phase<3;phase++)
		{
			if((gUNIXTIME.UNIX-gSYSFLAG.STM.STC[line].AU_OFFLINE_MARK[phase]<gECPPARA.AU_OFFLINE_TIME)) //����N��ɼ���Ԫ��ͨ��,��Ϊͨ�Ź���
				continue;

			if(gECPINFO.YX.ECPYX[line].COMM_FAULT[phase].MSG.U16==1) //�Ѳ���ͨ�Ź���
				continue;

			Modify_Au_WorkMode(line,phase,1);

			Soe_Data_Record(&gECPINFO.YX.ECPYX[line].COMM_FAULT[phase],1,true,0);
		}
	}
}
/************************************************************!
*Function: App_WorkMode_Process
*Description:
*Input:
*Output: null
*Return: null
*************************************************************/
bool Au_WorkMode_Process(void)
{
//	for(uint8_t line=0;line<LINEGROUP_MAXNUM;line++)
//	{
//		if(gSYSPARA.LINEGROUP.LINE[line].LINENO==0)
//			continue;
//
//		if(gSYSFLAG.AWS.ASF[line].WORKMODE==0) //ȫ����
//		{
//			for(uint8_t phase=0;phase<3;phase++)
//			{
//				if(gSYSFLAG.AWS.ASF[line].AU_WORKMODE[phase]==1)
//				{
//					Modify_Au_WorkMode(line,1);
//
//					Log_Data_Record(0x0A,"DS",line," �ߵĲɼ���Ԫ��ȫ���л�Ϊ�˻�ģʽ!");
//
//					return true;
//				}
//			}
//		}
//
//		if(gSYSFLAG.AWS.ASF[line].WORKMODE==1) //�˻�
//		{
//			for(uint8_t phase=0;phase<3;phase++)
//			{
//				if(gSYSFLAG.AWS.ASF[line].AU_WORKMODE[phase]==1)
//					return true;
//			}
//
//			Modify_Au_WorkMode(line,0);
//
//			Log_Data_Record(0x0A,"DS",line," �ߵĲɼ���Ԫ��ȫ���л�Ϊȫ����ģʽ!");
//		}
//	}

	return true;
}
/************************************************************!
*Function:  Au_Timing_Process
*Description:
*Input: null
*Output: null
*Return: null
*************************************************************/
bool Au_Timing_Process(void)
{
	if((gUNIXTIME.UNIX-3)%5!=0)  //ÿ��5S����һ��
		return false;

	if(gUNIXTIME.UNIX==gSYSFLAG.STM.AU_TIMING_TIME)  //5S��ֻ����һ��Уʱ
		return false;

	gSYSFLAG.STM.AU_TIMING_TIME=gUNIXTIME.UNIX;  //��¼Уʱʱ��

	for(uint8_t line=0;line<LINEGROUP_MAXNUM;line++)
	{
		if(gSYSPARA.LINEGROUP.LINE[line].LINENO==0)
			continue;

		if(gSYSFLAG.AWS.ASF[line].AU_TIMING_ACK!=0&&gSYSFLAG.AWS.ASF[line].AU_TIMING_ACK%7==0) //�ɼ���Ԫ��УʱӦ���Ѿ�ͬ��
		{
			gSYSFLAG.AWS.ASF[line].AU_TIMING_ACK=0;
			gSYSFLAG.AWS.ASF[line].AU_TIMING_ASYNC=0;

			#ifdef STATUS_LED2_AU_TIMING_ASYNC
			Status_Led2_Clear();
			#endif

			continue;
		}

		#ifdef STATUS_LED2_AU_TIMING_ASYNC
		Status_Led2_Set();
		#endif

		#ifdef PRINT_AU_TIMING_ASYNC_DEBUG
		DEBUG_PRINT_NISR("KNSDSDKK","<----- ",line," �ߵ�ʱ��û��ͬ��,Уʱ֡������: ",gSYSFLAG.AWS.ASF[line].AU_TIMING_ACK);
		#endif

		gSYSFLAG.AWS.ASF[line].AU_TIMING_ACK=0;
		gSYSFLAG.AWS.ASF[line].AU_TIMING_ASYNC+=1; //Уʱ�첽

		if(gSYSFLAG.AWS.ASF[line].AU_TIMING_ASYNC<=AU_TIMING_ASYNC_BUFFER)   //Уʱ�첽����,������ʧ����УʱACK����Ҫ���Ѹòɼ���Ԫ��
			continue;

		if(gSYSFLAG.AWS.ASF[line].WORKMODE==1) //�˻�ģʽ
		{
			//if((gSYSFLAG.AWS.ASF[line].AU_TIMING_ASYNC%AU_ASYNC_ENTER_LPOWER_MODE)!=0) //�˻�ģʽ��,1����һ�λ���Уʱ
				continue;
		}

		Au_WakeUp_Frame(line);

		Log_Data_Record(0x03,"DS",line," �ߵ�ʱ��û��ͬ��,�ѷ��͸��ߵ�ͬ��֡!");
	}

	return true;
}
/************************************************************!
*Function: App_Call_Wave
*Description:
*Input:
*Output: null
*Return: null
*************************************************************/
bool Cu_Call_Wave(void)
{
	#ifdef PRINT_WAVE_DEBUG
	DEBUG_PRINT_NISR("KKNSDSKK","<----- �㼯��Ԫ�����ٻ� ",gFAULTINFO.LINE," �ߵĹ��ϲ���!");
	#endif

	uint32_t cnt=0;

	gSYSFLAG.CWS.ISCALLWAVE=true;

	DEBUG_PRINT_NISR("KNSKK","<----- �ѽ�����¼���γ���");

	for(uint8_t phase=0;phase<3;phase++) //��ʼ���ڷ������ϵ�һ���ٻ�����,�����ѯ
	{
		for(gFAULTINFO.FRAMESEQ=1;gFAULTINFO.FRAMESEQ<=gFAULTINFO.FRAMENUM;gFAULTINFO.FRAMESEQ++)//����֡֡����ѯ
		{
			for(uint8_t retrans=0;retrans<5;retrans++) //ÿһ֡������֡���ط�����
			{
				Fill_Icp_Frame(RADIO_CHANNEL,gSYSPARA.LINEGROUP.LINE[gFAULTINFO.LINE].AU[phase].ADDR,0x42,0x04,gFAULTINFO.FRAMENUM,gFAULTINFO.FRAMESEQ,0,0);

				cnt++;

				#ifdef PRINT_AU_WAVE_DATA_DEBUG
				if(retrans>=1)
					DEBUG_PRINT_NISR("KNSDSDSDSDSKK","<----- ���ڵ� ",retrans+1," �η��� ",gFAULTINFO.LINE," �� ",phase," �Ųɼ���Ԫ�ĵ� ",gFAULTINFO.FRAMESEQ," ֡�ٻ�����֡!");
				#endif

				if(ulTaskNotifyTake(pdTRUE,pdMS_TO_TICKS(2500))==pdTRUE) //�ȴ�2S��ʱ�ط�
					break;

				if(retrans!=4) //5�������ٻ�����ʱ����¼�ٻ�ʧ���¼�
					continue;

				gSYSFLAG.CWS.ISCALLWAVE=false;

				memset(gFAULTINFO.DATA,0,FAULT_DATA_LEN); //���gFAULTINFO

				Log_Data_Record(0x03,"DSDSDS",gFAULTINFO.LINE," �� ",phase," �Ųɼ���Ԫ�ٻ��� ",gFAULTINFO.FRAMESEQ," ֡����ʧ��!");

				return false;
			}
		}
	}

	gSYSFLAG.CWS.ISCALLWAVE=false;

	Log_Data_Record(12,"DS",gFAULTINFO.LINE," �ߵĹ��ϲ����ٻ��ɹ�!");

	DEBUG_PRINT_NISR("KNSDSKK","<----- �ٻ�����һ������ ",cnt, " ֡����֡");

	return true;
}
/************************************************************!
*Function: App_Call_Wave
*Description:
*Input:
*Output: null
*Return: null
*************************************************************/
bool ShortCircuit_Fault_Process(void)
{
	if(gECPINFO.YX.ALL_FAULT.MSG.U16==0)
	{
		for(uint8_t line=0;line<LINEGROUP_MAXNUM;line++)
		{
			if(gSYSPARA.LINEGROUP.LINE[line].LINENO==0)
				continue;

			for(uint8_t phase=0;phase<3;phase++)
			{
				if(gECPINFO.YX.ECPYX[line].SHUNSHI_FAULT[phase].MSG.U16==1||gECPINFO.YX.ECPYX[line].YONGJIU_FAULT[phase].MSG.U16==1) //�����µĶ�·����
				{
					Soe_Data_Record(&gECPINFO.YX.ALL_FAULT,1,true,0);

					return true;
				}
			}
		}
	}

	if(gECPINFO.YX.ALL_FAULT.MSG.U16==1)
	{
		for(uint8_t line=0;line<LINEGROUP_MAXNUM;line++)
		{
			if(gSYSPARA.LINEGROUP.LINE[line].LINENO==0)
				continue;

			for(uint8_t phase=0;phase<3;phase++)
			{
				if(gECPINFO.YX.ECPYX[line].SHUNSHI_FAULT[phase].MSG.U16==1||gECPINFO.YX.ECPYX[line].YONGJIU_FAULT[phase].MSG.U16==1) //�����µĶ�·����
					return false;
			}
		}

		Soe_Data_Record(&gECPINFO.YX.ALL_FAULT,0,true,0);

		return true;
	}

	return true;
}
/************************************************************!
*Function:
*Description:
*Input:
*Output: null
*Return: null
*************************************************************/
bool Trigger_Start_Call_Wave(uint8_t line,uint8_t *wavetime)
{
	uint8_t waveinfo[9];

	if(gSYSFLAG.AWS.ASF[line].WORKMODE==1)  //�˻�ģʽ
	{
		#ifdef PRINT_TRIGGER_CALL_WAVE_DEBUG
		DEBUG_PRINT_NISR("KKNSDSKK","<----- ",line,"���ѽ����˻�ģʽ,�޷���������¼���߳�!");
		#endif

		return false;
	}

	if(gSYSFLAG.CWS.ISCALLWAVE==true)
	{
		#ifdef PRINT_TRIGGER_CALL_WAVE_DEBUG
		DEBUG_PRINT_NISR("KKNSKK","<----- ����¼���߳�������,�޷��ٴν�������¼���߳�!");
		#endif

		return false;
	}

	gFAULTINFO.LINE=line;

	gSYSFLAG.CWS.ISCALLWAVE=true;   //�ٻ����α�־

	gFAULTINFO.WAVENUM.DATA=(((gECPPARA.FAULT_WAVE_NUM>>4)&0xF0)+gECPPARA.FAULT_WAVE_NUM)&0xFF;
	gFAULTINFO.WAVELEN=(AU_ADC_SAMPLE*(gFAULTINFO.WAVENUM.U03+gFAULTINFO.WAVENUM.U47));   //�õ�¼�����ݵ��ܲ���

	if(((gFAULTINFO.WAVELEN*4)%WAVE_FRAME_LEN)==0)
		gFAULTINFO.FRAMENUM=(gFAULTINFO.WAVELEN*4)/WAVE_FRAME_LEN;
	else
		gFAULTINFO.FRAMENUM=((gFAULTINFO.WAVELEN*4)/WAVE_FRAME_LEN)+1;

	memcpy(gFAULTINFO.DATA,wavetime,8); //����ʱ��

	memcpy(waveinfo,wavetime,8);

	waveinfo[8]=gFAULTINFO.WAVENUM.DATA;

	Fill_Icp_Frame(RADIO_CHANNEL,gSYSPARA.BROADCAST,0x40,0x07,1,1,waveinfo,9); //�㲥��������¼��֡,δ����δͬ�������

	Fault_Data_Record(1,wavetime,line);

	vTaskResume(xCall_Wave); //���ٻ���������֪ͨ

	#ifdef PRINT_TRIGGER_CALL_WAVE_DEBUG
	DEBUG_PRINT_NISR("KKNSDSKK","<----- �յ� ",line," �ߵ�����¼��֡,������������¼���߳�!");
	#endif

	return true;
}
/************************************************************!
*Function: Au_Timing_Frame
*Description:
*Input:
*Output: null
*Return: null
*************************************************************/
void Au_Timing_Frame(void)
{
	gICPFRAMELIST[0].FRAME[0]=ICP_STARTBYTE;
	gICPFRAMELIST[0].FRAME[1]=24;
	gICPFRAMELIST[0].FRAME[2]=24;
	gICPFRAMELIST[0].FRAME[3]=ICP_STARTBYTE;
	gICPFRAMELIST[0].FRAME[4]=0x41;

	memcpy(gICPFRAMELIST[0].FRAME+5,gSYSPARA.BENJI,6);
	memcpy(gICPFRAMELIST[0].FRAME+11,gSYSPARA.BROADCAST,6);

	gICPFRAMELIST[0].FRAME[17]=0x01;
	gICPFRAMELIST[0].FRAME[18]=1;
	gICPFRAMELIST[0].FRAME[19]=1;

	while(RTC->CNT>32760);
	gUNIXTIME.CNT=RTC->CNT+278;

	memcpy(gICPFRAMELIST[0].FRAME+20,gUNIXTIME.DATA,8);

	gICPFRAMELIST[0].FRAME[28]=Check_Icp_Cs(gICPFRAMELIST[0].FRAME+ICP_FRAMEHEAD,24);
	gICPFRAMELIST[0].FRAME[29]=ICP_ENDBYTE;

	Radio_ShortPkt_Tx(gICPFRAMELIST[0].FRAME,30);

	#ifdef PRINT_AUTIMING_TIMESTAMP_DEBUG //ά���˿ڴ�ӡ����ʱ��
	DEBUG_PRINT("KKNSDSDSDSKK","<------ ��Ƶ���ڵ� ",gSYSFLAG.CWS.RADIOTICKS," ʱ��Ƭ����JIAOSHIʱ֡,��ǰRTC����ֵ: ",RTC->CNT," ʱ��Ϊ: ",(gUNIXTIME.CNT-278)*1000/32768," MS ----->");
	#endif
}

/************************************************************!
*Function:  Au_WakeUp_Frame
*Description:
*Input: null
*Output: null
*Return: null
*************************************************************/
void Au_WakeUp_Frame(uint8_t line)
{
	memset(gICPFRAMELIST[1].FRAME,0x55,39);

	gICPFRAMELIST[1].FRAME[39]=0x2D;
	gICPFRAMELIST[1].FRAME[40]=0xD4;

	gICPFRAMELIST[1].FRAME[41]=ICP_STARTBYTE;
	gICPFRAMELIST[1].FRAME[42]=17;
	gICPFRAMELIST[1].FRAME[43]=17;
	gICPFRAMELIST[1].FRAME[44]=ICP_STARTBYTE;
	gICPFRAMELIST[1].FRAME[45]=0x40;

	memcpy(gICPFRAMELIST[1].FRAME+46,gSYSPARA.BENJI,6);
	memcpy(gICPFRAMELIST[1].FRAME+52,gSYSPARA.BROADCAST,6);

	gICPFRAMELIST[1].FRAME[58]=0x0A;
	gICPFRAMELIST[1].FRAME[59]=1;
	gICPFRAMELIST[1].FRAME[60]=1;
	gICPFRAMELIST[1].FRAME[61]=line;
	gICPFRAMELIST[1].FRAME[62]=Check_Icp_Cs(gICPFRAMELIST[1].FRAME+45,17);
	gICPFRAMELIST[1].FRAME[63]=ICP_ENDBYTE;

	vTaskSuspendAll();

	for(uint8_t i=0;i<25;i++)
		Radio_WakeUp_StartTx(gICPFRAMELIST[1].FRAME,64);

	xTaskResumeAll();
}
/************************************************************!
*Function:  Calc_NVA_F16_Value
*Description:
*Input: null
*Output: null
*Return: null
*************************************************************/
uint16_t Calc_NVA_F16_Value(uint16_t data,uint32_t max,uint16_t scale)
{
	NVA F16NVA;
	uint8_t SIGN;
	uint32_t U32;

	F16NVA.F16=data;

	SIGN=F16NVA.SIGN;

	U32=(uint16_t)((~(0x8000|F16NVA.DATA))+1);

	F16NVA.F16=(uint16_t)((max*scale*U32)/32768);

	F16NVA.SIGN=SIGN;

	return F16NVA.F16;
}
/************************************************************!
*Function:  Correct_The_Phase
*Description:
*Input: null
*Output: null
*Return: null
*************************************************************/
void Correc_The_Phase(void)
{
	uint8_t CORRECT_FLAG=0;
	int16_t MAX_A=0,MAX_B=0,MAX_C=0;
	uint32_t IDX_A,IDX_B,IDX_C,ABS_AB,ABS_AC;

	for(uint32_t i=0;i<82;i++)
	{
		if(gFAULTINFO.WAVE[0].CUR[i]>MAX_A)
		{
			IDX_A=i;
			MAX_A=gFAULTINFO.WAVE[0].CUR[i];
		}

		if(gFAULTINFO.WAVE[1].CUR[i]>MAX_B)
		{
			IDX_B=i;
			MAX_B=gFAULTINFO.WAVE[1].CUR[i];
		}

		if(gFAULTINFO.WAVE[2].CUR[i]>MAX_C)
		{
			IDX_C=i;
			MAX_C=gFAULTINFO.WAVE[2].CUR[i];
		}
	}

	ABS_AB=abs(IDX_A-IDX_B);
	ABS_AC=abs(IDX_A-IDX_C);

	if(ABS_AB<=21)
		CORRECT_FLAG+=1;
	else if(ABS_AB>=48&&ABS_AB<=60)
		CORRECT_FLAG+=1;
	else if(ABS_AB>60)
		CORRECT_FLAG+=1;

	if(ABS_AC<=21)
		CORRECT_FLAG+=2;
	else if(ABS_AC>=48&&ABS_AC<=60)
		CORRECT_FLAG+=2;
	else if(ABS_AC>60)
		CORRECT_FLAG+=2;

	if(CORRECT_FLAG==1) //B�෴
	{
		for(uint32_t i=0;i<MAX_WAVE_LEN;i++)
		{
			gFAULTINFO.WAVE[1].CUR[i]=-gFAULTINFO.WAVE[1].CUR[i];
			gFAULTINFO.WAVE[1].VOL[i]=-gFAULTINFO.WAVE[1].VOL[i];
		}
	}
	else if(CORRECT_FLAG==2) //C�෴
	{
		for(uint32_t i=0;i<MAX_WAVE_LEN;i++)
		{
			gFAULTINFO.WAVE[2].CUR[i]=-gFAULTINFO.WAVE[2].CUR[i];
			gFAULTINFO.WAVE[2].VOL[i]=-gFAULTINFO.WAVE[2].VOL[i];
		}
	}
	else if(CORRECT_FLAG==3) //A�෴
	{
		for(uint32_t i=0;i<MAX_WAVE_LEN;i++)
		{
			gFAULTINFO.WAVE[0].CUR[i]=-gFAULTINFO.WAVE[0].CUR[i];
			gFAULTINFO.WAVE[0].VOL[i]=-gFAULTINFO.WAVE[0].VOL[i];
		}
	}

	#ifdef PRINT_CORRECT_PHASE_DEBUG
	if(CORRECT_FLAG==1)
		DEBUG_PRINT_NISR("KS","<----- B��ĵ���������,�ѽ���B���������! ----->");
	if(CORRECT_FLAG==2)
		DEBUG_PRINT_NISR("KS","<----- C��ĵ���������,�ѽ���C���������! ----->");
	if(CORRECT_FLAG==3)
		DEBUG_PRINT_NISR("KS","<----- A��ĵ���������,�ѽ���A���������! ----->");
	#endif
}
/************************************************************!
*Function: Wave_Cfg_File_Init
*Description:
*Input:
*Output: null
*Return: null
*************************************************************/
void Wave_Cfg_File_Init(void)
{
	typedef union
	{
	    char     C8[150];
		uint8_t  U8[150];
	}UINT8_CHAR;

	UNIXTIME UT;
	DOUBLEBYTE DB;
	UINT8_CHAR UC;
	uint8_t u32lens;
	uint32_t read,lens;

	DB.U16=0;
	read=gSYSFLAG.MFW.WAVE;
	gSYSFLAG.MFW.WAVE+=2;

	memcpy(UT.DATA,gFAULTINFO.DATA,8);
	UnixTime2P101Time(&UT,UC.U8,7);
	Mx25_Data_Storage(gSYSFLAG.MFW.WAVE,UC.U8,7);
	gSYSFLAG.MFW.WAVE+=7;

	strcpy(UC.C8,
	"FAULT INDICATOR ");

	lens=strlen(UC.C8);
	Mx25_Data_Storage(gSYSFLAG.MFW.WAVE,UC.U8,lens);
	gSYSFLAG.MFW.WAVE+=lens;
	DB.U16+=lens;

	gFAULTINFO.LINE+=0x31;
	Mx25_Data_Storage(gSYSFLAG.MFW.WAVE,&gFAULTINFO.LINE,1);
	gSYSFLAG.MFW.WAVE+=1;
	DB.U16+=1;

	gFAULTINFO.LINE-=0x31;

strcpy(UC.C8,
" LINE,01,1999\r\n\
11,8A,3D\r\n\
1,UA,A,FI,V,1,0,0,-32767,32767\r\n\
2,UB,B,FI,V,1,0,0,-32767,32767\r\n");

	lens=strlen(UC.C8);
	Mx25_Data_Storage(gSYSFLAG.MFW.WAVE,UC.U8,lens);
	gSYSFLAG.MFW.WAVE+=lens;
	DB.U16+=lens;

strcpy(UC.C8,
"3,UC,C,FI,V,1,0,0,-32767,32767\r\n\
4,UZ,Z,FI,V,1,0,0,-32767,32767\r\n\
5,IA,A,FI,A,1,0,0,-32767,32767\r\n");

	lens=strlen(UC.C8);
	Mx25_Data_Storage(gSYSFLAG.MFW.WAVE,UC.U8,lens);
	gSYSFLAG.MFW.WAVE+=lens;
	DB.U16+=lens;

strcpy(UC.C8,
"6,IB,B,FI,A,1,0,0,-32767,32767\r\n\
7,IC,C,FI,A,1,0,0,-32767,32767\r\n\
8,IZ,Z,FI,A,1,0,0,-32767,32767\r\n");

	lens=strlen(UC.C8);
	Mx25_Data_Storage(gSYSFLAG.MFW.WAVE,UC.U8,lens);
	gSYSFLAG.MFW.WAVE+=lens;
	DB.U16+=lens;

strcpy(UC.C8,
"1,ASOE,0\r\n\
2,BSOE,0\r\n\
3,CSOE,0\r\n\
50\r\n\
1\r\n\
4096,");

	lens=strlen(UC.C8);
	Mx25_Data_Storage(gSYSFLAG.MFW.WAVE,UC.U8,lens);
	gSYSFLAG.MFW.WAVE+=lens;
	DB.U16+=lens;

	u32lens=Get_U32_Dec(gFAULTINFO.WAVELEN,UC.U8,10);

	Mx25_Data_Storage(gSYSFLAG.MFW.WAVE,UC.U8+u32lens,10-u32lens);
	gSYSFLAG.MFW.WAVE+=10-u32lens;
	DB.U16+=10-u32lens;

strcpy(UC.C8,"\r\n");

	lens=strlen(UC.C8);
	Mx25_Data_Storage(gSYSFLAG.MFW.WAVE,UC.U8,lens);
	gSYSFLAG.MFW.WAVE+=lens;
	DB.U16+=lens;

	memcpy(UT.DATA,gFAULTINFO.DATA,8);

	if(UT.CNT>=(20*gFAULTINFO.WAVENUM.U47*32768/1000))
		UT.CNT-=20*gFAULTINFO.WAVENUM.U47*32768/1000;
	else
	{
		UT.UNIX--;
		UT.CNT=32768-(20*gFAULTINFO.WAVENUM.U47*32768/1000)+UT.CNT;
	}

	lens=UnixTime2StringTime(UT.DATA,UC.U8);

	Mx25_Data_Storage(gSYSFLAG.MFW.WAVE,UC.U8,lens);
	gSYSFLAG.MFW.WAVE+=lens;
	DB.U16+=lens;

	strcpy(UC.C8,"\r\n");

	lens=strlen(UC.C8);
	Mx25_Data_Storage(gSYSFLAG.MFW.WAVE,UC.U8,lens);
	gSYSFLAG.MFW.WAVE+=lens;
	DB.U16+=lens;

	lens=UnixTime2StringTime(gFAULTINFO.DATA,UC.U8);

	Mx25_Data_Storage(gSYSFLAG.MFW.WAVE,UC.U8,lens);
	gSYSFLAG.MFW.WAVE+=lens;
	DB.U16+=lens;

strcpy(UC.C8,
"\r\nBINARY\r\n\
1\r\n");

	lens=strlen(UC.C8);
	Mx25_Data_Storage(gSYSFLAG.MFW.WAVE,UC.U8,lens);
	gSYSFLAG.MFW.WAVE+=lens;
	DB.U16+=lens;

	Mx25_Data_Storage(read,DB.U8,2);
}
/************************************************************!
*Function: Wave_Cfg_File_Init
*Description:
*Input:
*Output: null
*Return: null
*************************************************************/
uint8_t UnixTime2StringTime(uint8_t *datetime,uint8_t *data)
{
	UNIXTIME UT;
	P101TIME PT;
	DOUBLEBYTE DB;
	uint8_t localtime[8];

	memcpy(UT.DATA,datetime,8);
	UnixTime2P101Time(&UT,PT.DATA,7);

	memcpy(localtime+1,PT.DATA,7);

	memcpy(DB.U8,localtime+1,2*sizeof(uint8_t));

	localtime[5]&=0x1F;           //���ε�����
	localtime[2]=DB.U16/1000;    //��
	DB.U16%=1000;
	localtime[1]=DB.U16/100;     //�����λ
	localtime[0]=DB.U16%100;     //�����λ

	for(uint8_t i=0;i<8;i++)
		localtime[i]=Byte2Bcd(localtime[i]);

	DB.U4[0].DATA=localtime[5];   //��
	data[0]=DB.U4[0].U47+0x30;
	data[1]=DB.U4[0].U03+0x30;
	data[2]=0x2F;
	DB.U4[0].DATA=localtime[6];  //��
	data[3]=DB.U4[0].U47+0x30;
	data[4]=DB.U4[0].U03+0x30;
	data[5]=0x2F;
	DB.U4[0].DATA=localtime[7];  //��
	data[6]=0x32;
	data[7]=0x30;
	data[8]=DB.U4[0].U47+0x30;
	data[9]=DB.U4[0].U03+0x30;
	data[10]=0x2C;
	DB.U4[0].DATA=localtime[4];  //ʱ
	data[11]=DB.U4[0].U47+0x30;
	data[12]=DB.U4[0].U03+0x30;
	data[13]=0x3A;
	DB.U4[0].DATA=localtime[3];  //��
	data[14]=DB.U4[0].U47+0x30;
	data[15]=DB.U4[0].U03+0x30;
	data[16]=0x3A;
	DB.U4[0].DATA=localtime[2];  //��
	data[17]=DB.U4[0].U47+0x30;
	data[18]=DB.U4[0].U03+0x30;
	data[19]=0x2E;
	DB.U4[0].DATA=localtime[1];  //����
	data[20]=DB.U4[0].U03+0x30;
	DB.U4[0].DATA=localtime[0];  //����
	data[21]=DB.U4[0].U47+0x30;
	data[22]=DB.U4[0].U03+0x30;
	data[23]=0x30;
	data[24]=0x30;
	data[25]=0x30;

	return 26;
}
/************************************************************!
*Function: DEBUG_ERASE_MX25
*Description:
*Input:
*Output: null
*Return: null
*************************************************************/
void DEBUG_ERASE_MX25(ICPFRAME *IF)
{
	vTaskSuspendAll();
	Wdog_Disable();

	DEBUG_PRINT_NISR("KNSKK","<----- ��ʼ����MX25�洢... ----->");

	Mx25_Erase_Chip();
	FlashPara_Init();

	DEBUG_PRINT_NISR("KKNSKK","<----- MX25�洢�����ɹ�!���������㼯��Ԫ! ----->");

	for(uint32_t i=0;i<20000;i++);

	SCB->AIRCR=0x05FA0004;  //M3�ں˸�λ����

	Wdog_Enable();
	xTaskResumeAll();
}
/************************************************************!
*Function: DEBUG_READ_LOG
*Description:
*Input:
*Output: null
*Return: null
*************************************************************/
void DEBUG_READ_LOG(void)
{
	vTaskSuspendAll();

	DEBUG_PRINT_NISR("KKSKK","<--------------- ���ڶ�ȡ��ʷ LOG ���� --------------->");

	for(uint32_t i=0;i<(LOG_FLASH_LEN/LOG_INFO_LEN);i++)
	{
		if(DEBUG_PRINT_LOG(LOG_START_ADDR1+i*LOG_INFO_LEN)==false)
			break;
	}

	DEBUG_PRINT_NISR("KKSKK","<--------------- LOG ��1��ȡ��� --------------->");

	for(uint32_t i=0;i<(LOG_FLASH_LEN/LOG_INFO_LEN);i++)
	{
		if(DEBUG_PRINT_LOG(LOG_START_ADDR2+i*LOG_INFO_LEN)==false)
			break;
	}

	DEBUG_PRINT_NISR("KKSKK","<--------------- LOG ��2��ȡ��� --------------->");

	xTaskResumeAll();
}
/************************************************************!
*Function: DEBUG_ECP_READ_LOG
*Description:
*Input: null
*Output: null
*Return:
*************************************************************/
void DEBUG_ECP_READ_LOG(void)
{
	uint32_t sn;
	FILEINFO FI;

	vTaskSuspendAll();

	Locate_Log_FileInfo(&FI);

	if(((FI.READ-LOG_START_ADDR1)/LOG_FLASH_LEN)==0)  //��1
		sn=((FI.READ-LOG_START_ADDR1)/LOG_INFO_LEN)+1;
	if(((FI.READ-LOG_START_ADDR1)/LOG_FLASH_LEN)==1)  //��2
		sn=(LOG_FLASH_LEN/LOG_INFO_LEN)+((FI.READ-LOG_START_ADDR1)/LOG_INFO_LEN)+1;

	DEBUG_PRINT_NISR("KKNSKK","<--------------- ģ���ȡ��ʷ LOG �ļ����� --------------->");
	DEBUG_PRINT_NISR("KSDSDSESDSKK","<--------------- ��ǰ LOG����: ",FI.INFONUM," LOG�ļ�����: ",FI.LENS," LOGʱ��: ",FI.TIME," ��һ��LOGΪMX25�еĵ�: ",sn," ��LOG!");

	for(uint32_t i=0;i<FI.INFONUM;i++)
	{
		if(DEBUG_PRINT_LOG(FI.READ)==false)
		{
			if(((FI.READ-LOG_START_ADDR1)/LOG_FLASH_LEN)==0)  //��1
				sn=((FI.READ-LOG_START_ADDR1)/LOG_INFO_LEN)+1;
			if(((FI.READ-LOG_START_ADDR1)/LOG_FLASH_LEN)==1)  //��2
				sn=(LOG_FLASH_LEN/LOG_INFO_LEN)+((FI.READ-LOG_START_ADDR1)/LOG_INFO_LEN)+1;

			DEBUG_PRINT_NISR("KKSDSK","<--------------- ��ǰ��: ",sn," ��LOG����Ϊ��! --------------->");
		}

		FI.READ+=LOG_INFO_LEN;
	}

	DEBUG_PRINT_NISR("KKSKK","<--------------- ��ʷ LOG �ļ���ȡ��� --------------->");

	xTaskResumeAll();
}
/************************************************************!
*Function: DEBUG_PRINT_LOG
*Description:
*Input:
*Output: null
*Return: null
*************************************************************/
bool DEBUG_PRINT_LOG(uint32_t read)
{
	uint32_t sn;
	LOGRECORD LOG;

	if(((read-LOG_START_ADDR1)/LOG_FLASH_LEN)==0) //��1
	{
		if((LOG_START_ADDR1+LOG_FLASH_LEN-read)<LOG_INFO_LEN)
			read=LOG_START_ADDR2;
	}

	if(((read-LOG_START_ADDR1)/LOG_FLASH_LEN)==1) //��2
	{
		if((LOG_START_ADDR2+LOG_FLASH_LEN-read)<LOG_INFO_LEN)
			read=LOG_START_ADDR1;
	}

	Mx25_Read_U8_Array(read,LOG.DATA,LOG_INFO_LEN,false);

	if(LOG.LENS==0xFF) //����
		return false;

	if(((read-LOG_START_ADDR1)/LOG_FLASH_LEN)==0)
		sn=((read-LOG_START_ADDR1)/LOG_INFO_LEN)+1;
	if(((read-LOG_START_ADDR1)/LOG_FLASH_LEN)==1)
		sn=(LOG_FLASH_LEN/LOG_INFO_LEN)+((read-LOG_START_ADDR2)/LOG_INFO_LEN)+1;

	DEBUG_PRINT_NISR("KSDSDSESDS","��ǰΪ�� ",sn," ����־,����: ",LOG.TYPE," ʱ��: ",LOG.TIME.DATA," ����: ",LOG.LENS," ����: ");
	DEBUG_PRINT_U8_ARRAY_NISR((uint8_t *)LOG.ASCII,LOG.LENS-8); //8:һ�ֽ�����,�߸��ֽڵ�ʱ��
	DEBUG_PRINT_NISR("S","\r\n");

	return true;
}
/************************************************************!
*Function: DEBUG_READ_SOE
*Description:
*Input:
*Output: null
*Return: null
*************************************************************/
void DEBUG_READ_SOE(void)
{
	vTaskSuspendAll();

	DEBUG_PRINT_NISR("KKNSKK","<--------------- ���ڶ�ȡ��ʷ SOE ���� --------------->");

	for(uint32_t i=0;i<(SOE_FLASH_LEN/SOE_INFO_LEN);i++)
	{
		if(DEBUG_PRINT_SOE(SOE_START_ADDR1+i*SOE_INFO_LEN)==false)
			break;
	}

	DEBUG_PRINT_NISR("KKSKK","<--------------- SOE ��1��ȡ��� --------------->");

	for(uint32_t i=0;i<(SOE_FLASH_LEN/SOE_INFO_LEN);i++)
	{
		if(DEBUG_PRINT_SOE(SOE_START_ADDR2+i*SOE_INFO_LEN)==false)
			break;
	}

	DEBUG_PRINT_NISR("KKSKK","<--------------- SOE ��2��ȡ��� --------------->");

	xTaskResumeAll();
}
/************************************************************!
*Function: DEBUG_ECP_READ_SOE
*Description:
*Input:
*Output: null
*Return: null
*************************************************************/
void DEBUG_ECP_READ_SOE(void)
{
	uint32_t sn;
	FILEINFO FI;

	vTaskSuspendAll();

	Locate_Soe_FileInfo(&FI);

	if(((FI.READ-SOE_START_ADDR1)/SOE_FLASH_LEN)==0) //��1
		sn=((FI.READ-SOE_START_ADDR1)/SOE_INFO_LEN)+1;
	if(((FI.READ-SOE_START_ADDR1)/SOE_FLASH_LEN)==1) //��2
		sn=(SOE_FLASH_LEN/SOE_INFO_LEN)+((FI.READ-SOE_START_ADDR1)/SOE_INFO_LEN)+1;

	DEBUG_PRINT_NISR("KKNSKK","<--------------- ģ���ȡ��ʷ SOE �ļ����� --------------->");
	DEBUG_PRINT_NISR("SDSDSESDSKK","<--------------- ��ǰSOE����: ",FI.INFONUM," SOE�ļ�����: ",FI.LENS," SOEʱ��: ",FI.TIME," ��һ��SOEΪMX25�еĵ�: ",sn," ��SOE !");

	for(uint32_t i=0;i<FI.INFONUM;i++)
	{
		if(DEBUG_PRINT_SOE(FI.READ)==false)
		{
			if(((FI.READ-SOE_START_ADDR1)/SOE_FLASH_LEN)==0) //��1
				sn=((FI.READ-SOE_START_ADDR1)/SOE_INFO_LEN)+1;
			if(((FI.READ-SOE_START_ADDR1)/SOE_FLASH_LEN)==1) //��2
				sn=(SOE_FLASH_LEN/SOE_INFO_LEN)+((FI.READ-SOE_START_ADDR1)/SOE_INFO_LEN)+1;

			DEBUG_PRINT_NISR("KKSDSKK","<--------------- ��ǰ��: ",sn," ��SOE����Ϊ��! --------------->");
		}

		FI.READ+=SOE_INFO_LEN;
	}

	DEBUG_PRINT_NISR("KKSKK","<--------------- ��ʷSOE�ļ���ȡ��� --------------->");

	xTaskResumeAll();
}
/************************************************************!
*Function: DEBUG_PRINT_SOE
*Description:
*Input: null
*Output: null
*Return:
*************************************************************/
bool DEBUG_PRINT_SOE(uint32_t read)
{
	P101SOE PS;
	uint32_t sn;

	vTaskSuspendAll();

	if(((read-SOE_START_ADDR1)/SOE_FLASH_LEN)==0) //��1
	{
		if((SOE_START_ADDR1+SOE_FLASH_LEN-read)<SOE_INFO_LEN)
			read=SOE_START_ADDR2;
	}

	if(((read-SOE_START_ADDR1)/SOE_FLASH_LEN)==1) //��2
	{
		if((SOE_START_ADDR2+SOE_FLASH_LEN-read)<SOE_INFO_LEN)
			read=SOE_START_ADDR1;
	}

	if(((read-SOE_START_ADDR1)/SOE_FLASH_LEN)==0)
		sn=((read-SOE_START_ADDR1)/SOE_INFO_LEN)+1;
	if(((read-SOE_START_ADDR1)/SOE_FLASH_LEN)==1)
		sn=(SOE_FLASH_LEN/SOE_INFO_LEN)+((read-SOE_START_ADDR2)/SOE_INFO_LEN)+1;

	Mx25_Read_U8_Array(read,PS.DATA,SOE_INFO_LEN,false);

	if(PS.TYPE==0xFF) //����Ϊ��
		return false;

	if(PS.MSGADDR.U16==gECPINFO.YX.STATUS.ADDR.U16)
	{
		DEBUG_PRINT_NISR("KNSDSDSH","�� ",sn," ��SOE,MX25ָ��: ",read," ��Ϣ���ַ ",PS.MSGADDR.U16);
		DEBUG_PRINT_NISR("SESDS"," ʱ�� ",PS.TIME," ���� ",PS.TYPE," ����: װ���쳣: ");
	}

	if(PS.MSGADDR.U16==gECPINFO.YX.LOW_POWER.ADDR.U16)
	{
		DEBUG_PRINT_NISR("KNSDSDSH","�� ",sn," ��SOE,MX25ָ��: ",read," ��Ϣ���ַ ",PS.MSGADDR.U16);
		DEBUG_PRINT_NISR("SESDS"," ʱ�� ",PS.TIME," ���� ",PS.TYPE," ����: ��ص�ѹ��: ");
	}

	if(PS.MSGADDR.U16==gECPINFO.YX.POWER_SWITCH.ADDR.U16)
	{
		DEBUG_PRINT_NISR("KNSDSDSH","�� ",sn," ��SOE,MX25ָ��: ",read," ��Ϣ���ַ ",PS.MSGADDR.U16);
		DEBUG_PRINT_NISR("SESDS"," ʱ�� ",PS.TIME," ���� ",PS.TYPE," ����: �󱸵�ԴͶ��: ");
	}

	if(PS.MSGADDR.U16==gECPINFO.YX.RF_FAULT.ADDR.U16)
	{
		DEBUG_PRINT_NISR("KNSDSDSH","�� ",sn," ��SOE,MX25ָ��: ",read," ��Ϣ���ַ ",PS.MSGADDR.U16);
		DEBUG_PRINT_NISR("SESDS"," ʱ�� ",PS.TIME," ���� ",PS.TYPE," ����: С����ģ�����: ");
	}

	if(PS.MSGADDR.U16==gECPINFO.YX.GPS_LOCK.ADDR.U16)
	{
		DEBUG_PRINT_NISR("KNSDSDSH","�� ",sn," ��SOE,MX25ָ��: ",read," ��Ϣ���ַ ",PS.MSGADDR.U16);
		DEBUG_PRINT_NISR("SESDS"," ʱ�� ",PS.TIME," ���� ",PS.TYPE," ����: GPS����״̬: ");
	}

	if(PS.MSGADDR.U16==gECPINFO.YX.WAVEFILE.ADDR.U16)
	{
		DEBUG_PRINT_NISR("KNSDSDSH","�� ",sn," ��SOE,MX25ָ��: ",read," ��Ϣ���ַ ",PS.MSGADDR.U16);
		DEBUG_PRINT_NISR("SESDS"," ʱ�� ",PS.TIME," ���� ",PS.TYPE," ����: ��¼���ļ�����: ");
	}

	if(PS.MSGADDR.U16==gECPINFO.YX.ALL_FAULT.ADDR.U16)
	{
		DEBUG_PRINT_NISR("KNSDSDSH","�� ",sn," ��SOE,MX25ָ��: ",read," ��Ϣ���ַ ",PS.MSGADDR.U16);
		DEBUG_PRINT_NISR("SESDS"," ʱ�� ",PS.TIME," ���� ",PS.TYPE," ����: ���߹���: ");
	}

	for(uint8_t line=0;line<LINEGROUP_MAXNUM;line++)
	{
		if(gSYSPARA.LINEGROUP.LINE[line].LINENO==0) //��Ч�ɼ���Ԫ��
			continue;

		for(uint8_t phase=0;phase<3;phase++)
		{
			if(PS.MSGADDR.U16==gECPINFO.YX.ECPYX[line].CUR_OVER[phase].ADDR.U16)
			{
				DEBUG_PRINT_NISR("KNSDSDSDSDS","�� ",sn," ��SOE,MX25ָ��: ",read," ���� ",line," �� ",phase," �Ųɼ���Ԫ,��Ϣ���ַ ");
				DEBUG_PRINT_NISR("HSESDS",PS.MSGADDR.U16," ʱ�� ",PS.TIME," ����: ",PS.TYPE," ����: ��������: ");
			}

			if(PS.MSGADDR.U16==gECPINFO.YX.ECPYX[line].COMM_FAULT[phase].ADDR.U16)
			{
				DEBUG_PRINT_NISR("KNSDSDSDSDS","�� ",sn," ��SOE,MX25ָ��: ",read," ���� ",line," �� ",phase," �Ųɼ���Ԫ,��Ϣ���ַ ");
				DEBUG_PRINT_NISR("HSESDS",PS.MSGADDR.U16," ʱ�� ",PS.TIME," ����: ",PS.TYPE," ����: ͨ�Ź���: ");
			}

			if(PS.MSGADDR.U16==gECPINFO.YX.ECPYX[line].SHUNSHI_FAULT[phase].ADDR.U16)
			{
				DEBUG_PRINT_NISR("KNSDSDSDSDS","�� ",sn," ��SOE,MX25ָ��: ",read," ���� ",line," �� ",phase," �Ųɼ���Ԫ,��Ϣ���ַ ");
				DEBUG_PRINT_NISR("HSESDS",PS.MSGADDR.U16," ʱ�� ",PS.TIME," ����: ",PS.TYPE," ����: ˲ʱ�Զ�·: ");
			}

			if(PS.MSGADDR.U16==gECPINFO.YX.ECPYX[line].YONGJIU_FAULT[phase].ADDR.U16)
			{
				DEBUG_PRINT_NISR("KNSDSDSDSDS","�� ",sn," ��SOE,MX25ָ��: ",read," ���� ",line," �� ",phase," �Ųɼ���Ԫ,��Ϣ���ַ ");
				DEBUG_PRINT_NISR("HSESDS",PS.MSGADDR.U16," ʱ�� ",PS.TIME," ����: ",PS.TYPE," ����: �������Զ�·: ");
			}

			if(PS.MSGADDR.U16==gECPINFO.YX.ECPYX[line].AU_LOW_POWER[phase].ADDR.U16)
			{
				DEBUG_PRINT_NISR("KNSDSDSDSDS","�� ",sn," ��SOE,MX25ָ��: ",read," ���� ",line," �� ",phase," �Ųɼ���Ԫ,��Ϣ���ַ ");
				DEBUG_PRINT_NISR("HSESDS",PS.MSGADDR.U16," ʱ�� ",PS.TIME," ����: ",PS.TYPE," ����: ���Ƿѹ: ");
			}

			if(PS.MSGADDR.U16==gECPINFO.YX.ECPYX[line].AU_POWER_SWITCH[phase].ADDR.U16)
			{
				DEBUG_PRINT_NISR("KNSDSDSDSDS","�� ",sn," ��SOE,MX25ָ��: ",read," ���� ",line," �� ",phase," �Ųɼ���Ԫ,��Ϣ���ַ ");
				DEBUG_PRINT_NISR("HSESDS",PS.MSGADDR.U16," ʱ�� ",PS.TIME," ����: ",PS.TYPE," ����: ���õ���л�: ");
			}

			if(PS.MSGADDR.U16==gECPINFO.YX.ECPYX[line].FUHE_OVER[phase].ADDR.U16)
			{
				DEBUG_PRINT_NISR("KNSDSDSDSDS","�� ",sn," ��SOE,MX25ָ��: ",read," ���� ",line," �� ",phase," �Ųɼ���Ԫ,��Ϣ���ַ ");
				DEBUG_PRINT_NISR("HSESDS",PS.MSGADDR.U16," ʱ�� ",PS.TIME," ����: ",PS.TYPE," ����: ����Խ��: ");
			}

			if(PS.MSGADDR.U16==gECPINFO.YX.ECPYX[line].ZHONGZAI[phase].ADDR.U16)
			{
				DEBUG_PRINT_NISR("KNSDSDSDSDS","�� ",sn," ��SOE,MX25ָ��: ",read," ���� ",line," �� ",phase," �Ųɼ���Ԫ,��Ϣ���ַ ");
				DEBUG_PRINT_NISR("HSESDS",PS.MSGADDR.U16," ʱ�� ",PS.TIME," ����: ",PS.TYPE," ����: ����: ");
			}
		}
	}

	if(PS.SOE==0)
		DEBUG_PRINT_NISR("SKK","����");
	if(PS.SOE==1)
		DEBUG_PRINT_NISR("SKK","��ʼ");

	xTaskResumeAll();

	return true;
}
/************************************************************!
*Function: DEBUG_READ_YC
*Description:
*Input:
*Output: null
*Return: null
*************************************************************/
void DEBUG_READ_YC(void)
{
	vTaskSuspendAll();

	DEBUG_PRINT_NISR("KKNSKK","<--------------- ��ʼ����MX25�е���ʷң���ļ�  --------------->");

	for(uint8_t i=0;i<((2*YC_SECTOR_NUM)/YC_FILE_SECTOR_NUM);i++)
	{
		if(DEBUG_PRINT_YC_FILE(YC_START_ADDR1+i*YC_FILE_LEN)==false)
			DEBUG_PRINT_NISR("KKSDSKK","<--------------- ��ǰ��: ",i+1," ��ң���ļ�,�ļ�Ϊ��! --------------->");
	}

	DEBUG_PRINT_NISR("KKNSKK","<--------------- MX25�е���ʷң���ļ��������  --------------->");

	xTaskResumeAll();
}
/************************************************************!
*Function: DEBUG_ECP_READ_YC
*Description:
*Input:
*Output: null
*Return: null
*************************************************************/
void DEBUG_ECP_READ_YC(uint16_t fileid)
{
	uint8_t sn;
	FILEINFO FI;

	FI.ID=fileid;

	vTaskSuspendAll();

	Locate_Yc_FileInfo(&FI);

	sn=((FI.READ-YC_START_ADDR1)/YC_FILE_LEN)+1;

	if(DEBUG_PRINT_YC_FILE(FI.READ)==false)
	{
		DEBUG_PRINT_NISR("KNSDSK","<--------------- ��ǰ��: ",sn," ��ң���ļ�,�ļ�Ϊ��! --------------->");
		return;
	}

	DEBUG_PRINT_NISR("NSDSDSESDSDSDSKK","<----- ģ��ECP��ȡ��ң���ļ���Ϊ: ",FI.ID," ΪMX25�е�: ",sn," ��ң���ļ�,�ļ�ʱ��: ",FI.TIME," �ļ�����: ",FI.INFONUM," �ļ�����: ",FI.LENS," �ļ�ָ��: ",FI.READ," ----->");

	xTaskResumeAll();
}
/************************************************************!
*Function: DEBUG_PRINT_YC_DATA
*Description:
*Input:
*Output: null
*Return: null
*************************************************************/
void DEBUG_PRINT_YC_DATA(ICPFRAME *IF)
{
	vTaskSuspendAll();

	DEBUG_PRINT_NISR("KKNSDSDSK","<----- �յ� ",IF->LINE," �� ",IF->PHASE," �Ųɼ���Ԫ��ң������:");

	DEBUG_PRINT_NISR("S","<----- ����ģʽ: ");

	if(IF->IFD.WORKMODE==0)
		DEBUG_PRINT_NISR("SK","ȫ����ģʽ");
	if(IF->IFD.WORKMODE==1)
		DEBUG_PRINT_NISR("SK","�˻�ģʽ");

	DEBUG_PRINT_NISR("SFK","<----- ��������: ",IF->IFD.I);

	DEBUG_PRINT_NISR("SFK","<----- �糡����: ",IF->IFD.U);

	DEBUG_PRINT_NISR("SFK","<----- �¶�����: ",IF->IFD.T);

	DEBUG_PRINT_NISR("SFKK","<----- ��ص�ѹ: ",IF->IFD.B);



	xTaskResumeAll();
}
/************************************************************!
*Function: DEBUG_PRINT_YC_FILE_SECTION
*Description:
*Input: null
*Output: null
*Return:
*************************************************************/
bool DEBUG_PRINT_YC_FILE_SECTION(uint32_t read,uint32_t sn)
{
	FOURBYTE FB;
	YAOCEFILE YCF;

	vTaskSuspendAll();
	Wdog_Feed();

	for(uint8_t i=0;i<YC_INFO_NUM;i++) //�����Ч�Ķ��������ļ�ͷʱ��
	{
		Mx25_Read_U8_Array(read+i*YC_INFO_LEN+8,FB.U8,4,false); //+4:��ȡ�����ݵ������յ�ʱ��λ��

		if(FB.U32==0xFFFFFFFF||FB.U32!=0x00000000)
			break;
	}

	Mx25_Read_U8_Array(read+(sn-1)*YC_INFO_LEN,YCF.DATA,YC_INFO_LEN,false);

	YCF.OLDTIME=((FB.U32&0xFFFF1F00)>>8);
	DEBUG_PRINT_NISR("NSDSTSDSKK","<----- ��ǰд���� ",((read-YC_START_ADDR1)/YC_FILE_LEN)+1," ��ң���ļ�( ",YCF.OLDTIME," )�ĵ� ",YCF.SN," �Ŷ���!");

	if(YCF.N==0xFF)
	{
		DEBUG_PRINT_NISR("KSDSKK","<---------- ��ǰ����: ",YCF.SN," ������Ϊ��! ----------->");

		Wdog_Feed();
		xTaskResumeAll();

		return false;
	}

	DEBUG_PRINT_NISR("KSDSESDSDSK","<---------- ��ǰ����: ",YCF.SN," ����ʱ��: ",YCF.TIME.DATA," ��������: ",YCF.N," ���㳤�� ",YCF.LENS," ----------->");

	YCF.N=YCF.N>=27?27:YCF.N;

	for(uint32_t i=0;i<YCF.N;i+=9)
		for(uint32_t j=0;j<9;j++)
			DEBUG_PRINT_NISR("SHSHK","��Ϣ���ַ ",YCF.YC[i+j].ADDR.U16," ��Ϣ���� ",YCF.YC[i+j].DATA);

	DEBUG_PRINT_NISR("S","\r\n\r\n");

	Wdog_Feed();
	xTaskResumeAll();

	return true;
}
/************************************************************!
*Function: DEBUG_PRINT_YC_FILE
*Description:
*Input: null
*Output: null
*Return:
*************************************************************/
bool DEBUG_PRINT_YC_FILE(uint32_t read)
{
	FOURBYTE FB;
	uint32_t sn;
	YAOCEFILE YCF;

	vTaskSuspendAll();
	Wdog_Feed();

	for(uint32_t i=0;i<YC_INFO_NUM;i++)
	{
		Mx25_Read_U8_Array(read+i*YC_INFO_LEN,FB.U8,4,false);

		if(FB.U32!=0xFFFFFFFF)
			break;

		if(i==(YC_INFO_NUM-1))
			return false;
	}

	for(uint32_t i=0;i<YC_INFO_NUM;i++) //�����Ч�Ķ��������ļ�ͷʱ��
	{
		Mx25_Read_U8_Array(read+i*YC_INFO_LEN+8,FB.U8,4,false); //+4:��ȡ�����ݵ������յ�ʱ��λ��

		if(FB.U32==0xFFFFFFFF||FB.U32!=0x00000000)
			break;
	}

	YCF.OLDTIME=(FB.U32&0xFFFF1F00)>>8;

	sn=((read-YC_START_ADDR1)/YC_FILE_LEN)+1;

	DEBUG_PRINT_NISR("KKNSDSTSKK","<---------- ��ǰ�� ",sn," ��ң���ļ�( ",YCF.OLDTIME," )��������: ");

	for(uint32_t i=0;i<YC_INFO_NUM;i++)
	{
		Mx25_Read_U8_Array(read+i*YC_INFO_LEN,YCF.DATA,YC_INFO_LEN,false);

		if(YCF.N==0xFF)
		{
			DEBUG_PRINT_NISR("KSDSK","<---------- ��ǰ����: ",YCF.SN," ������Ϊ��! ----------->");
			continue;
		}

		DEBUG_PRINT_NISR("KSDSESDSDSK","<---------- ��ǰ����: ",YCF.SN," ����ʱ��: ",YCF.TIME.DATA," ��������: ",YCF.N," ���㳤�� ",YCF.LENS," ----------->");

		YCF.N=YCF.N>=27?27:YCF.N;

		for(uint32_t j=0;j<YCF.N;j+=9)
			for(uint32_t k=0;k<9;k++)
				DEBUG_PRINT_NISR("SHSHK","��Ϣ���ַ ",YCF.YC[j+k].ADDR.U16," ��Ϣ���� ",YCF.YC[j+k].DATA);

		DEBUG_PRINT_NISR("SK","\r\n");
	}

	Wdog_Feed();
	xTaskResumeAll();

	return true;
}
/************************************************************!
*Function: DEBUG_READ_FAULT
*Description:
*Input:
*Output: null
*Return: null
*************************************************************/
void DEBUG_READ_FAULT(void)
{
	vTaskSuspendAll();

	DEBUG_PRINT_NISR("KKNSKK","<--------------- ���ڶ�ȡ��ʷ FAULT ���� --------------->");

	for(uint32_t i=0;i<(FAULT_FLASH_LEN/FAULT_INFO_LEN);i++)
	{
		if(DEBUG_PRINT_FAULT(FAULT_START_ADDR1+i*FAULT_INFO_LEN)==false)
			break;
	}

	DEBUG_PRINT_NISR("KKSKK","<--------------- FAULT ��1��ȡ��� --------------->");

	for(uint32_t i=0;i<(FAULT_FLASH_LEN/FAULT_INFO_LEN);i++)
	{
		if(DEBUG_PRINT_FAULT(FAULT_START_ADDR2+i*FAULT_INFO_LEN)==false)
			break;
	}

	DEBUG_PRINT_NISR("KKSKK","<--------------- FAULT ��2��ȡ��� --------------->");

	xTaskResumeAll();
}
/************************************************************!
*Function: DEBUG_ECP_READ_FAULT
*Description:
*Input:
*Output: null
*Return: null
*************************************************************/
void DEBUG_ECP_READ_FAULT(void)
{
	uint32_t sn;
	FILEINFO FI;

	vTaskSuspendAll();

	Locate_Fault_FileInfo(&FI);

	if(((FI.READ-FAULT_START_ADDR1)/FAULT_FLASH_LEN)==0) //��1
		sn=((FI.READ-FAULT_START_ADDR1)/FAULT_INFO_LEN)+1;
	if(((FI.READ-FAULT_START_ADDR1)/FAULT_FLASH_LEN)==1) //��2
		sn=(FAULT_FLASH_LEN/FAULT_INFO_LEN)+((FI.READ-FAULT_START_ADDR1)/FAULT_INFO_LEN)+1;

	DEBUG_PRINT_NISR("KKNSKK","<--------------- ģ���ȡ��ʷ FAULT �ļ����� --------------->");
	DEBUG_PRINT_NISR("SDSDSESDSKK","<--------------- ��ǰFAULT����: ",FI.INFONUM," FAULT�ļ�����: ",FI.LENS," FAULTʱ��: ",FI.TIME," ��һ��FAULTΪMX25�еĵ�: ",sn," ��FAULT !");

	for(uint32_t i=0;i<FI.INFONUM;i++)
	{
		if(DEBUG_PRINT_FAULT(FI.READ)==false)
		{
			if(((FI.READ-FAULT_START_ADDR1)/FAULT_FLASH_LEN)==0) //��1
				sn=((FI.READ-FAULT_START_ADDR1)/FAULT_INFO_LEN)+1;
			if(((FI.READ-FAULT_START_ADDR1)/FAULT_FLASH_LEN)==1) //��2
				sn=(FAULT_FLASH_LEN/FAULT_INFO_LEN)+((FI.READ-FAULT_START_ADDR1)/FAULT_INFO_LEN)+1;

			DEBUG_PRINT_NISR("KKSDSKK","<--------------- ��ǰ��: ",sn," ��FAULT����Ϊ��! --------------->");
		}

		FI.READ+=FAULT_INFO_LEN;
	}

	DEBUG_PRINT_NISR("SKK","<--------------- ��ʷFAULT�ļ���ȡ��� --------------->");

	xTaskResumeAll();
}
/************************************************************!
*Function: DEBUG_PRINT_FAULT
*Description:
*Input:
*Output: null
*Return: null
*************************************************************/
bool DEBUG_PRINT_FAULT(uint32_t read)
{
	uint32_t sn;
	P101FAULT PF;

	if(((read-FAULT_START_ADDR1)/FAULT_FLASH_LEN)==0) //��1
	{
		if((FAULT_START_ADDR1+FAULT_FLASH_LEN-read)<FAULT_INFO_LEN)
			read=FAULT_START_ADDR2;
	}

	if(((read-FAULT_START_ADDR1)/FAULT_FLASH_LEN)==1) //��2
	{
		if((FAULT_START_ADDR2+FAULT_FLASH_LEN-read)<FAULT_INFO_LEN)
			read=FAULT_START_ADDR1;
	}

	Mx25_Read_U8_Array(read,PF.DATA,FAULT_INFO_LEN,false);

	if(PF.FAULT==0xFF)
		return false;

	if(((read-FAULT_START_ADDR1)/FAULT_FLASH_LEN)==0)
		sn=((read-FAULT_START_ADDR1)/FAULT_INFO_LEN)+1;
	if(((read-FAULT_START_ADDR1)/FAULT_FLASH_LEN)==1)
		sn=(FAULT_FLASH_LEN/FAULT_INFO_LEN)+((read-FAULT_START_ADDR2)/FAULT_INFO_LEN)+1;

	DEBUG_PRINT_NISR("KNSDSDSESHKK","��ǰ�� ",sn," ��������Ϣ,MX25ָ��λ��: ",read," ����ʱ��: ",PF.TIME," ����: ",PF.FAULT);

	return true;

}
/************************************************************!
*Function: DEBUG_READ_YK
*Description:
*Input:
*Output: null
*Return: null
*************************************************************/
void DEBUG_READ_YK(void)
{
	vTaskSuspendAll();

	DEBUG_PRINT_NISR("KKNSKK","<--------------- ���ڶ�ȡ��ʷ YK ���� --------------->");

	for(uint32_t i=0;i<(YK_FLASH_LEN/YK_INFO_LEN);i++)
	{
		if(DEBUG_PRINT_YK(YK_START_ADDR1+i*YK_INFO_LEN)==false)
			break;
	}

	DEBUG_PRINT_NISR("KKSKK","<--------------- YK ��1��ȡ��� --------------->");

	for(uint32_t i=0;i<(YK_FLASH_LEN/YK_INFO_LEN);i++)
	{
		if(DEBUG_PRINT_YK(YK_START_ADDR2+i*YK_INFO_LEN)==false)
			break;
	}

	DEBUG_PRINT_NISR("KKSKK","<--------------- YK ��2��ȡ��� --------------->");

	xTaskResumeAll();
}
/************************************************************!
*Function: DEBUG_ECP_READ_YK
*Description:
*Input:
*Output: null
*Return: null
*************************************************************/
void DEBUG_ECP_READ_YK(void)
{
	uint32_t sn;
	FILEINFO FI;

	vTaskSuspendAll();

	Locate_Yk_FileInfo(&FI);

	if(((FI.READ-YK_START_ADDR1)/YK_FLASH_LEN)==0) //��1
		sn=((FI.READ-YK_START_ADDR1)/YK_INFO_LEN)+1;
	if(((FI.READ-YK_START_ADDR1)/YK_FLASH_LEN)==1) //��2
		sn=(YK_FLASH_LEN/YK_INFO_LEN)+((FI.READ-YK_START_ADDR1)/YK_INFO_LEN)+1;

	DEBUG_PRINT_NISR("KKNSKK","<--------------- ģ���ȡ��ʷ YK �ļ����� --------------->");
	DEBUG_PRINT_NISR("SDSDSESDSKK","<--------------- ��ǰYK����: ",FI.INFONUM," YK�ļ�����: ",FI.LENS," YKʱ��: ",FI.TIME," ��һ��YKΪMX25�еĵ�: ",sn," ��YK !");

	for(uint32_t i=0;i<FI.INFONUM;i++)
	{
		if(DEBUG_PRINT_YK(FI.READ)==false)
		{
			if(((FI.READ-YK_START_ADDR1)/YK_FLASH_LEN)==0) //��1
				sn=((FI.READ-YK_START_ADDR1)/YK_INFO_LEN)+1;
			if(((FI.READ-YK_START_ADDR1)/YK_FLASH_LEN)==1) //��2
				sn=(YK_FLASH_LEN/YK_INFO_LEN)+((FI.READ-YK_START_ADDR1)/YK_INFO_LEN)+1;

			DEBUG_PRINT_NISR("KKSDSK","<--------------- ��ǰ��: ",sn," ��YK����Ϊ��! --------------->");
		}

		FI.READ+=YK_INFO_LEN;
	}

	DEBUG_PRINT_NISR("KKSKK","<--------------- ��ʷ YK �ļ���ȡ��� --------------->");

	xTaskResumeAll();
}
/************************************************************!
*Function: DEBUG_ECP_READ_YK
*Description:
*Input:
*Output: null
*Return: null
*************************************************************/
bool DEBUG_PRINT_YK(uint32_t read)
{
	P101YK YK;
	uint32_t sn;

	if(((read-YK_START_ADDR1)/YK_FLASH_LEN)==0) //��1
	{
		if((YK_START_ADDR1+YK_FLASH_LEN-read)<YK_INFO_LEN)
			read=YK_START_ADDR2;
	}

	if(((read-YK_START_ADDR1)/YK_FLASH_LEN)==1) //��2
	{
		if((YK_START_ADDR2+YK_FLASH_LEN-read)<YK_INFO_LEN)
			read=YK_START_ADDR1;
	}

	Mx25_Read_U8_Array(read,YK.DATA,YK_INFO_LEN,false);

	if(YK.TYPE==0xFF)
		return false;

	if(((read-YK_START_ADDR1)/YK_FLASH_LEN)==0)
		sn=((read-YK_START_ADDR1)/YK_INFO_LEN)+1;
	if(((read-YK_START_ADDR1)/YK_FLASH_LEN)==1)
		sn=(YK_FLASH_LEN/YK_INFO_LEN)+((read-YK_START_ADDR2)/YK_INFO_LEN)+1;

	DEBUG_PRINT_NISR("KSDSDSDSHSHSESHKK","��ǰ�� ",sn," ��YK,MX25ָ��λ��: ",read," YK����: ",YK.TYPE," YK��Ϣ���ַ: ",YK.MSGADDR.U16," YK����ԭ��: ",YK.COT.U16," ʱ��: ",YK.TIME," ����: ",YK.SCO);

	return true;
}
/************************************************************!
*Function: DEBUG_READ_WAVE
*Description:
*Input:
*Output: null
*Return: null
*************************************************************/
void DEBUG_READ_WAVE(void)
{
	vTaskSuspendAll();

	DEBUG_PRINT_NISR("KKNSKK","<--------------- ���ڶ�ȡ��ʷ WAVE ���� --------------->");

	for(uint32_t i=0;i<((2*WAVE_FLASH_LEN)/WAVE_FILE_LEN);i++)
	{
		DEBUG_PRINT_NISR("KKSDSKK","<--------------- ��ǰ��: ",i+1," ��WAVE ! --------------->");

		if(DEBUG_PRINT_WAVE(WAVE_START_ADDR1+i*WAVE_FILE_LEN)==false)
			break;
	}

	DEBUG_PRINT_NISR("KKSKK","<--------------- ��ʷ WAVE �ļ���ȡ��� --------------->");

	xTaskResumeAll();
}
/************************************************************!
*Function: DEBUG_ECP_READ_WAVE
*Description:
*Input:
*Output: null
*Return: null
*************************************************************/
bool DEBUG_ECP_READ_WAVE(uint16_t fileid)
{
	uint8_t sn;
	FILEINFO FI;

	FI.ID=fileid;

	vTaskSuspendAll();

	Locate_Wave_FileInfo(&FI);

	sn=((FI.READ-WAVE_START_ADDR1)/WAVE_FILE_LEN)+1;

	if(DEBUG_PRINT_WAVE(FI.READ)==false)
	{
		DEBUG_PRINT_NISR("KNSDSK","<--------------- ��ǰ��: ",sn," �� WAVE �ļ�,�ļ�Ϊ��! --------------->");
		return false;
	}

	DEBUG_PRINT_NISR("KNSDSDSESDSDSDSK","<----- ģ��ECP��ȡ�� WAVE �ļ���Ϊ: ",FI.ID," ΪMX25�е�: ",sn," ��WAVE�ļ�,�ļ�ʱ��: ",FI.TIME," �ļ�����: ",FI.INFONUM," �ļ�����: ",FI.LENS," �ļ�ָ��: ",FI.READ," ----->");

	xTaskResumeAll();

	return true;
}
/************************************************************!
*Function: DEBUG_PRINT_WAVE
*Description:
*Input:
*Output: null
*Return: null
*************************************************************/
bool DEBUG_PRINT_WAVE(uint32_t read)
{
	DOUBLEBYTE DB;
	uint8_t data[100];
	WAVE_DAT_FORMAT WDF;

	Mx25_Read_U8_Array(read,DB.U8,2,false);

	if(DB.U16==0xFFFF)
		return false;

	read+=2;

	vTaskSuspendAll();

	Mx25_Read_U8_Array(read,data,7,false);
	read+=7;

	DEBUG_PRINT_NISR("KKNSEK","<----- ���ϲ����ļ�ʱ��:",data);
	DEBUG_PRINT_NISR("KKNSK","<----- ��ǰ�����ļ���CFG�ļ�����:");
	DEBUG_PRINT_NISR("KKNSDKK","<----- ��ǰ�����ļ���CFG�ļ�����:",DB.U16);

	while(DB.U16>0)
	{
		if(DB.U16>=100)
		{
			Mx25_Read_U8_Array(read,data,100,false);
			DEBUG_PRINT_U8_ARRAY_NISR(data,100);
			read+=100;
			DB.U16-=100;
		}
		else
		{
			Mx25_Read_U8_Array(read,data,DB.U16,false);
			DEBUG_PRINT_U8_ARRAY_NISR(data,DB.U16);
			read+=DB.U16;
			DB.U16=0;
		}
	}

	DEBUG_PRINT_NISR("KKSKK","<--------------------------------- ��ǰ�����ļ���DATA�ļ�����:");

	for(uint32_t i=0;i<MAX_WAVE_LEN;i++)
	{
		Mx25_Read_U8_Array(read,WDF.DATA,WAVE_INFO_LEN,false);

		if(WDF.N==0xFFFFFFFF)
			break;

		DEBUG_PRINT_NISR("KSDSDS","��� ",WDF.N," ʱ��� ",WDF.TIMESTAMP," ����  ");
		DEBUG_PRINT_NISR("FSFSFSFSF",WDF.AU," ",WDF.BU," ",WDF.CU," ",WDF.ZU," ",WDF.AI);
		DEBUG_PRINT_NISR("SFSFSFSFS"," ",WDF.BI," ",WDF.CI," ",WDF.ZI," ",WDF.YX,"  ");

		DEBUG_PRINT_U8CHAR_ARRAY_NISR(WDF.DATA,WAVE_INFO_LEN);

		read+=WAVE_INFO_LEN;
	}

	DEBUG_PRINT_NISR("KKSKKK","<--------------------------------- �����ļ���ȡ���!");

	xTaskResumeAll();

	return true;
}
/************************************************************!
*Function: DEBUG_READ_NOWTIME
*Description:
*Input:
*Output: null
*Return: null
*************************************************************/
void DEBUG_READ_NOWTIME(void)
{
	uint32_t cnt;
	uint8_t data[6];

	while(RTC->CNT>32700);
	Get_R8025t_RtcTime(data,6);
	cnt=RTC->CNT;

	cnt=cnt*1000/32767;

	DEBUG_PRINT_NISR("KKSK",            "<--------------- �㼯��Ԫϵͳʱ������ --------------->");
	DEBUG_PRINT_NISR("SDSDSK",          "<--------------- ��ǰUNIXʱ��: ",gUNIXTIME.UNIX,".",cnt," --------------->");
	DEBUG_PRINT_NISR("SDSDSDSDSDSDSDSK","<--------------- ��ǰ����ʱ��: ",data[5],"-",data[4],"-",data[3]," ",data[2],":",data[1],":",data[0],".",cnt," --------------->");
}
/************************************************************!
*Function: DEBUG_READ_NOWTIME
*Description:
*Input:
*Output: null
*Return: null
*************************************************************/
void DEBUG_ERASE_PARABLOCK(void)
{
	vTaskSuspendAll();

	DEBUG_PRINT_NISR("KKSKK","<--------------- ���ڲ���ϵͳ������...");

	for(uint8_t i=0;i<10;i++)
	{
		Wdog_Feed();
		Mx25_Erase_Sector(i);
	}

	DEBUG_PRINT_NISR("KKSKK","<--------------- ϵͳ�������Ѳ������!!!");

	xTaskResumeAll();
}
/************************************************************!
*Function: DEBUG_READ_NOWTIME
*Description:
*Input:
*Output: null
*Return: null
*************************************************************/
bool DEBUG_ECP_START_WAVE(ICPFRAME *IF)
{
	UNIXTIME UT;

	Get_Sys_Time(&UT);

	Trigger_Start_Call_Wave(0,UT.DATA);

	return true;
}

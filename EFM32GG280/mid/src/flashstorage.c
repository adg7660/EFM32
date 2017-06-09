/******************************************************************!
*Copyright (c), 2008-2017, Qingdao Topscomm Communication Co .Ltd.
*File name: flashstorage.h
*Version: 0.1.0
*Date: 2016-09-20
*Author: WANGJIANHUI
*Description:
*******************************************************************/
#include "include.h"
#include "flashstorage.h"


/************************************************************!
*Function:
*Description:
*Input: null
*Output: null
*Return: null
*************************************************************/
void FlashPara_Init(void)
{
	gSYSFLAG.MFW.LOG=Locate_Log_Position();

	gSYSFLAG.MFW.SOE=Locate_Soe_Position();

	gSYSFLAG.MFW.YC=Locate_Yc_Position();

	gSYSFLAG.MFW.FAULT=Locate_Fault_Position();

	gSYSFLAG.MFW.YK=Locate_Yk_Position();

	gSYSFLAG.MFW.WAVE=Locate_Wave_Position();

	#ifdef PRINT_SYS_INIT_DEBUG    //��ӡ��ʼ��ָ��
	DEBUG_PRINT("NSHSHK","<----- ��ʼ ��־ ָ��: ",LOG_START_ADDR1,  " ----- ��ǰָ�� ----- ",gSYSFLAG.MFW.LOG);
	DEBUG_PRINT("NSHSHK","<----- ��ʼ ң�� ָ��: ",SOE_START_ADDR1,  " ----- ��ǰָ�� ----- ",gSYSFLAG.MFW.SOE);
	DEBUG_PRINT("NSHSHK","<----- ��ʼ ң�� ָ��: ",YC_START_ADDR1,   " ----- ��ǰָ�� ----- ",gSYSFLAG.MFW.YC);
	DEBUG_PRINT("NSHSHK","<----- ��ʼ ���� ָ��: ",FAULT_START_ADDR1," ----- ��ǰָ�� ----- ",gSYSFLAG.MFW.FAULT);
	DEBUG_PRINT("NSHSHK","<----- ��ʼ ң�� ָ��: ",YK_START_ADDR1,   " ----- ��ǰָ�� ----- ",gSYSFLAG.MFW.YK);
	DEBUG_PRINT("NSHSHK","<----- ��ʼ ���� ָ��: ",WAVE_START_ADDR1, " ----- ��ǰָ�� ----- ",gSYSFLAG.MFW.WAVE);
	#endif
}
/************************************************************!
*Function:
*Description:
*Output: null
*Return: null
*************************************************************/
void SysPara_Init(void)
{
	Get_R8025t_RtcTime(gUNIXTIME.DATA,6);                 //���R8025Tʱ��
	gUNIXTIME.UNIX=LocalTime2UnixTime(gUNIXTIME.DATA,6);  //������ϵͳʱ��


	Mx25_Read_U8_Array(SYSPARA_ADDR,gSYSPARA.DATA,SYSPARA_NUM,false);

	if((gSYSPARA.LINEGROUP.LINE[0].LINENO!=0xFF)&&gSYSPARA.LINEGROUP.LINE[0].LINENO!=0x00)  //��MX25��������ϵͳ����
	{
		gSYSPARA.LINEGROUP.LINENUM=0;  //�����

		for(uint8_t line=0;line<LINEGROUP_MAXNUM;line++)  //���²ɼ���Ԫ����Ŀ
		{
			if((gSYSPARA.LINEGROUP.LINE[line].LINENO!=0xFF)&&(gSYSPARA.LINEGROUP.LINE[line].LINENO!=0))
				gSYSPARA.LINEGROUP.LINENUM++;
		}
	}
	else
	{
		//��MX25����,����������Ĭ�ϵ�ϵͳ����

		memset(gSYSPARA.DATA,0,SYSPARA_NUM); //��ղ�����

		gSYSPARA.LINEGROUP.LINENUM=1;  //Ĭ�ϲɼ���Ԫ����
		gSYSPARA.LINEGROUP.LINE[0].LINENO=1; //Ĭ�ϲɼ���Ԫ����ߺ�,��Ч�ɼ���Ԫ����ߺ�Ӧ������Ϊ0
		memset(gSYSPARA.LINEGROUP.LINE[0].AU[0].ADDR,0x00,6); //Ĭ��A���ַ
		memset(gSYSPARA.LINEGROUP.LINE[0].AU[1].ADDR,0x00,6); //Ĭ��B���ַ
		memset(gSYSPARA.LINEGROUP.LINE[0].AU[2].ADDR,0x00,6); //Ĭ��C���ַ
		gSYSPARA.LINEGROUP.LINE[0].AU[0].ADDR[5]=0x01;
		gSYSPARA.LINEGROUP.LINE[0].AU[1].ADDR[5]=0x02;
		gSYSPARA.LINEGROUP.LINE[0].AU[2].ADDR[5]=0x03;

		gSYSPARA.LINEGROUP.LINE[1].LINENO=0; //Ĭ�ϲɼ���Ԫ����ߺ�,��Ч�ɼ���Ԫ����ߺ�Ӧ������Ϊ0
		memset(gSYSPARA.LINEGROUP.LINE[1].AU[0].ADDR,0x00,6); //Ĭ��A���ַ
		memset(gSYSPARA.LINEGROUP.LINE[1].AU[1].ADDR,0x00,6); //Ĭ��B���ַ
		memset(gSYSPARA.LINEGROUP.LINE[1].AU[2].ADDR,0x00,6); //Ĭ��C���ַ
		gSYSPARA.LINEGROUP.LINE[1].AU[0].ADDR[5]=0x11;
		gSYSPARA.LINEGROUP.LINE[1].AU[1].ADDR[5]=0x12;
		gSYSPARA.LINEGROUP.LINE[1].AU[2].ADDR[5]=0x13;

		memset(gSYSPARA.BENJI,0x01,6);      //Ĭ�ϱ�����ַ
		memset(gSYSPARA.WEIHU,0x00,6);      //Ĭ��ά����ַ
		memset(gSYSPARA.BROADCAST,0xFF,6);  //Ĭ�Ϲ㲥��ַ
		gSYSPARA.RADIO_CHANNEL=1;           //Ĭ����Ƶ�ŵ�

		//�˴�����ϵͳĬ�ϲ�����Ĭ��ֵ,ע���޸�SYSPARA_NUM�궨��!!!!!!!!
	}
}
/************************************************************!
*Function:
*Description:
*Output: null
*Return: null
*************************************************************/
void EcpPara_Init(void)
{
	Mx25_Read_U8_Array(ECPPARA_ADDR,gECPPARA.DATA,(ECPPARA_NUM*2),false);

	gECPPARA.YC_REPORT_CYCLE=(gECPPARA.YC_REPORT_CYCLE!=0xFFFF)?gECPPARA.YC_REPORT_CYCLE:60;                                 //����ң���ϱ�����
	gECPPARA.GPS_TIMING_MODE=(gECPPARA.GPS_TIMING_MODE!=0xFFFF)?gECPPARA.GPS_TIMING_MODE:0;                                  //���û㼯��ԪУʱģʽ
	gECPPARA.GPS_TIMING_CYCLE=(gECPPARA.GPS_TIMING_CYCLE!=0xFFFF)?gECPPARA.GPS_TIMING_CYCLE:14400;                           //����GPSУʱ����
	gECPPARA.BATT_VOL_THRESHOLD=(gECPPARA.BATT_VOL_THRESHOLD!=0xFFFF)?gECPPARA.BATT_VOL_THRESHOLD:12100;                     //���û㼯��Ԫ��ص͵�ѹ��ֵ
	gECPPARA.SUN_VOL_REPORT_THRESHOLD=(gECPPARA.SUN_VOL_REPORT_THRESHOLD!=0xFFFF)?gECPPARA.SUN_VOL_REPORT_THRESHOLD:500;     //����̫���ܵ�ص�ѹ�ϱ���ֵ
	gECPPARA.BATT_VOL_REPORT_THRESHOLD=(gECPPARA.BATT_VOL_REPORT_THRESHOLD!=0xFFFF)?gECPPARA.BATT_VOL_REPORT_THRESHOLD:500;  //�������ص�ѹ�ϱ���ֵ
	gECPPARA.I_REPORT_THRESHOLD=(gECPPARA.I_REPORT_THRESHOLD!=0xFFFF)?gECPPARA.I_REPORT_THRESHOLD:10;                        //���õ����ϱ���ֵ
	gECPPARA.U_REPORT_THRESHOLD=(gECPPARA.U_REPORT_THRESHOLD!=0xFFFF)?gECPPARA.U_REPORT_THRESHOLD:10;                        //���õ�ѹ�ϱ���ֵ
	gECPPARA.T_REPORT_THRESHOLD=(gECPPARA.T_REPORT_THRESHOLD!=0xFFFF)?gECPPARA.T_REPORT_THRESHOLD:1;                         //�����¶��ϱ���ֵ
	gECPPARA.B_REPORT_THRESHOLD=(gECPPARA.B_REPORT_THRESHOLD!=0xFFFF)?gECPPARA.B_REPORT_THRESHOLD:1;                         //���õ���ϱ���ֵ
	gECPPARA.ZIZHAN.U16=(gECPPARA.ZIZHAN.U16!=0xFFFF)?gECPPARA.ZIZHAN.U16:0x0001;                                            //���û㼯��Ԫ��վ��ַ
	gECPPARA.FAULT_WAVE_NUM=(gECPPARA.FAULT_WAVE_NUM!=0xFFFF)?gECPPARA.FAULT_WAVE_NUM:0x0509;                                //���ù��ϲ���¼��ģʽ
	gECPPARA.YC_REPORT_MODE=(gECPPARA.YC_REPORT_MODE!=0xFFFF)?gECPPARA.YC_REPORT_MODE:0;                                     //����ң���ϱ�ģʽ
	gECPPARA.RADIO_CHANNEL=(gECPPARA.RADIO_CHANNEL!=0xFFFF)?gECPPARA.RADIO_CHANNEL:0;
	gECPPARA.AU_OFFLINE_TIME=(gECPPARA.AU_OFFLINE_TIME!=0xFFFF)?gECPPARA.AU_OFFLINE_TIME:60;


	//����λ�����ECPPARA����Ĭ��ֵ,ע���޸�ECPPARA_NUM!!!!!!!!!!!!!!!
}
/************************************************************!
*Function:
*Description:
*Input: null
*Output: null
*Return: null
*************************************************************/
void SysFlag_Init(void)
{
	RADIOFRAME.CHANNEL=RADIO_CHANNEL; //ͨ����ʼ��
	WEIHUFRAME.CHANNEL=WEIHU_CHANNEL;


	gSYSFLAG.CIS.GPRS=TXC;
	gSYSFLAG.CIS.RADIO=RX;
	gSYSFLAG.CIS.WEIHU=TXC;

	for(uint8_t line=0;line<LINEGROUP_MAXNUM;line++)
	{
		gSYSFLAG.AWS.ASF[line].AU_TIMING_ASYNC=AU_TIMING_ASYNC_BUFFER;  //ϵͳ��ʼ��ֱ��Уʱ,�����첽����

		for(uint8_t phase=0;phase<3;phase++)
		{
			gSYSFLAG.STM.STC[line].AU_OFFLINE_MARK[phase]=gUNIXTIME.UNIX;
		}
	}
}
/************************************************************!
*Function:
*Description:
*Input: null
*Output: null
*Return: null
*************************************************************/
bool PointTable_Init(void)
{
	DOUBLEBYTE DB;
	uint32_t yxmaxspan=0;    //�ɼ���Ԫ��ң�����ݵ���Ϣ���ַ�������
	uint32_t ycmaxspan=0;    //�ɼ���Ԫ��ң�����ݵ���Ϣ���ַ�������
	uint32_t yxmaxnum=34-10;
	uint32_t ycmaxnum=17-2;
	uint32_t yxoffset=0x0000; //ң�ŵ����Ϣ���ַƫ��
	uint32_t ycoffset=0x4000; //ң������Ϣ���ַƫ��

	memset(gECPINFO.DATA,0,ECPINFO_LEN); //���ң��ң������

	Mx25_Read_U8_Array(POINTTABLE_ADDR,DB.U8,2,false);  //��ȡMX25�еĵ��

	if(DB.U16!=0xFFFF)
	{
		for(uint32_t num=0;num<ECPYX_NUM;num++)
		{
			Mx25_Read_U8_Array(POINTTABLE_ADDR+2*num,DB.U8,2,false);
			gECPINFO.YX.DATA[2*num]=DB.U16;
		}

		for(uint32_t num=0;num<ECPYC_NUM;num++)
		{
			Mx25_Read_U8_Array(POINTTABLE_ADDR+2*ECPYX_NUM+2*num,DB.U8,2,false);
			gECPINFO.YC.DATA[3*num]=DB.U16;
		}

		return true;
	}

	gECPINFO.YX.STATUS.ADDR.U16=yxoffset+1;
	gECPINFO.YX.LOW_POWER.ADDR.U16=yxoffset+2;
	gECPINFO.YX.POWER_SWITCH.ADDR.U16=yxoffset+3;
	gECPINFO.YX.RF_FAULT.ADDR.U16=yxoffset+4;
	gECPINFO.YX.GPS_LOCK.ADDR.U16=yxoffset+5;
	gECPINFO.YX.WAVEFILE.ADDR.U16=yxoffset+6;
	gECPINFO.YX.ALL_FAULT.ADDR.U16=yxoffset+7;
	gECPINFO.YX.LINE_WORKMODE[0].ADDR.U16=yxoffset+8;
	gECPINFO.YX.LINE_WORKMODE[1].ADDR.U16=yxoffset+9;
	gECPINFO.YX.LINE_WORKMODE[2].ADDR.U16=yxoffset+10;

	for(uint8_t line=0;line<gSYSPARA.LINEGROUP.LINENUM;line++)
	{
		yxmaxspan=yxoffset+(yxmaxnum*line);

		gECPINFO.YX.ECPYX[line].CUR_OVER[0].ADDR.U16=yxmaxspan+11;
		gECPINFO.YX.ECPYX[line].CUR_OVER[1].ADDR.U16=yxmaxspan+12;
		gECPINFO.YX.ECPYX[line].CUR_OVER[2].ADDR.U16=yxmaxspan+13;
		gECPINFO.YX.ECPYX[line].COMM_FAULT[0].ADDR.U16=yxmaxspan+14;
		gECPINFO.YX.ECPYX[line].COMM_FAULT[1].ADDR.U16=yxmaxspan+15;
		gECPINFO.YX.ECPYX[line].COMM_FAULT[2].ADDR.U16=yxmaxspan+16;
		gECPINFO.YX.ECPYX[line].SHUNSHI_FAULT[0].ADDR.U16=yxmaxspan+17;
		gECPINFO.YX.ECPYX[line].SHUNSHI_FAULT[1].ADDR.U16=yxmaxspan+18;
		gECPINFO.YX.ECPYX[line].SHUNSHI_FAULT[2].ADDR.U16=yxmaxspan+19;
		gECPINFO.YX.ECPYX[line].YONGJIU_FAULT[0].ADDR.U16=yxmaxspan+20;
		gECPINFO.YX.ECPYX[line].YONGJIU_FAULT[1].ADDR.U16=yxmaxspan+21;
		gECPINFO.YX.ECPYX[line].YONGJIU_FAULT[2].ADDR.U16=yxmaxspan+22;
		gECPINFO.YX.ECPYX[line].AU_LOW_POWER[0].ADDR.U16=yxmaxspan+23;
		gECPINFO.YX.ECPYX[line].AU_LOW_POWER[1].ADDR.U16=yxmaxspan+24;
		gECPINFO.YX.ECPYX[line].AU_LOW_POWER[2].ADDR.U16=yxmaxspan+25;
		gECPINFO.YX.ECPYX[line].AU_POWER_SWITCH[0].ADDR.U16=yxmaxspan+26;
		gECPINFO.YX.ECPYX[line].AU_POWER_SWITCH[1].ADDR.U16=yxmaxspan+27;
		gECPINFO.YX.ECPYX[line].AU_POWER_SWITCH[2].ADDR.U16=yxmaxspan+28;
		gECPINFO.YX.ECPYX[line].FUHE_OVER[0].ADDR.U16=yxmaxspan+29;
		gECPINFO.YX.ECPYX[line].FUHE_OVER[1].ADDR.U16=yxmaxspan+30;
		gECPINFO.YX.ECPYX[line].FUHE_OVER[2].ADDR.U16=yxmaxspan+31;
		gECPINFO.YX.ECPYX[line].ZHONGZAI[0].ADDR.U16=yxmaxspan+32;
		gECPINFO.YX.ECPYX[line].ZHONGZAI[1].ADDR.U16=yxmaxspan+33;
		gECPINFO.YX.ECPYX[line].ZHONGZAI[2].ADDR.U16=yxmaxspan+34;
	}

	gECPINFO.YC.SUN_VOL.ADDR.U16=ycoffset+1;
	gECPINFO.YC.BAT_VOL.ADDR.U16=ycoffset+2;

	for(uint8_t line=0;line<gSYSPARA.LINEGROUP.LINENUM;line++)
	{
		ycmaxspan=ycoffset+(ycmaxnum*line);

		gECPINFO.YC.ECPYC[line].CUR[0].ADDR.U16=ycmaxspan+3;
		gECPINFO.YC.ECPYC[line].CUR[1].ADDR.U16=ycmaxspan+4;
		gECPINFO.YC.ECPYC[line].CUR[2].ADDR.U16=ycmaxspan+5;
		gECPINFO.YC.ECPYC[line].VOL[0].ADDR.U16=ycmaxspan+6;
		gECPINFO.YC.ECPYC[line].VOL[1].ADDR.U16=ycmaxspan+7;
		gECPINFO.YC.ECPYC[line].VOL[2].ADDR.U16=ycmaxspan+8;
		gECPINFO.YC.ECPYC[line].TEM[0].ADDR.U16=ycmaxspan+9;
		gECPINFO.YC.ECPYC[line].TEM[1].ADDR.U16=ycmaxspan+10;
		gECPINFO.YC.ECPYC[line].TEM[2].ADDR.U16=ycmaxspan+11;
		gECPINFO.YC.ECPYC[line].AU_BAT_VOL[0].ADDR.U16=ycmaxspan+12;
		gECPINFO.YC.ECPYC[line].AU_BAT_VOL[1].ADDR.U16=ycmaxspan+13;
		gECPINFO.YC.ECPYC[line].AU_BAT_VOL[2].ADDR.U16=ycmaxspan+14;
		gECPINFO.YC.ECPYC[line].AU_GET_VOL[0].ADDR.U16=ycmaxspan+15;
		gECPINFO.YC.ECPYC[line].AU_GET_VOL[1].ADDR.U16=ycmaxspan+16;
		gECPINFO.YC.ECPYC[line].AU_GET_VOL[2].ADDR.U16=ycmaxspan+17;
	}


	gECPINFO.YX.GPS_LOCK.MSG.U16=gECPPARA.GPS_TIMING_MODE; //��GPSУʱ״̬��ֵ��ң��



	//���´������ڵ���ң��ң����

	for(uint32_t i=0;i<(7+3*8*gSYSPARA.LINEGROUP.LINENUM);i++) //ң�ŵ�����
	{
		//gECPINFO.YX.DATA[2*i]=i+1;
		//gECPINFO.YX.DATA[2*i+1]=i+1;
	}

	for(uint32_t i=0;i<(2+3*5*gSYSPARA.LINEGROUP.LINENUM);i++) //ң�������
	{
		//gECPINFO.YC.DATA[3*i]=i+1;
		//gECPINFO.YC.DATA[3*i+1]=i+1;
		//gECPINFO.YC.DATA[3*i+2]=i+1;
	}

	return true;
}
/************************************************************!
*Function:
*Description:
*Output: null
*Return: null
*************************************************************/
void Program_Storage(uint16_t sn,uint8_t *data,uint32_t lens)
{
	FOURBYTE FB;
	uint8_t len1,len2;

	len1=lens%4;
	len2=lens-len1;

	for(uint8_t i=0;i<len2;i+=4)
	{
		memcpy(FB.U8,data+i,4);

    	Msc_WriteWord(BACKUP_PROGRAM+(sn-1)*BACKUP_PRM_BLOCK+i,FB.U32);
	}

	if(len1>0) //��Ϊ4��������,����ֻ�������һ֡���ݲ�Ϊ4��������
	{
		FB.U32=0;

		memcpy(FB.U8,data+len2,len1);

    	Msc_WriteWord(BACKUP_PROGRAM+(sn-1)*BACKUP_PRM_BLOCK+len2,FB.U32);
	}
}
/************************************************************!
*Function:
*Description:
*Output: null
*Return: null
*************************************************************/
uint16_t Get_Program_Cs(uint32_t lens)
{
	FOURBYTE FB;
	uint16_t cs=0;

	for(uint32_t i=0;i<lens;i+=4)
	{
		FB.U32=Msc_ReadWord(BACKUP_PROGRAM+i);

		for(uint8_t j=0;j<4;j++)
			cs+=FB.U8[j];
	}

	return cs;
}
/************************************************************!
*Function:
*Description:
*Input: null
*Output: null
*Return:
*************************************************************/
uint32_t Locate_Log_Position(void)
{
	FOURBYTE FB;
	uint32_t pointer;

	pointer=((LOG_FLASH_LEN/LOG_INFO_LEN)-1)*LOG_INFO_LEN;  //������һ����¼���ݿռ���Ե�ַ

	Mx25_Read_U8_Array(LOG_START_ADDR1+pointer,FB.U8,4,false);

	if(FB.U32==0xFFFFFFFF) //��һ�������һ����¼���ݿռ�û������,������ָ���ڵ�һ������
	{
		for(uint32_t i=0;i<(LOG_FLASH_LEN/LOG_INFO_LEN);i++)
		{
			Mx25_Read_U8_Array(LOG_START_ADDR1+i*LOG_INFO_LEN,FB.U8,4,false);

			if(FB.U32==0xFFFFFFFF)
				return (LOG_START_ADDR1+i*LOG_INFO_LEN);
		}
	}

	Mx25_Read_U8_Array(LOG_START_ADDR2+pointer,FB.U8,4,false);

	if(FB.U32==0xFFFFFFFF) //�ڶ��������һ����¼���ݿռ�û������,������ָ���ڵڶ�������
	{
		for(uint32_t i=0;i<(LOG_FLASH_LEN/LOG_INFO_LEN);i++)
		{
			Mx25_Read_U8_Array(LOG_START_ADDR2+i*LOG_INFO_LEN,FB.U8,4,false);

			if(FB.U32==0xFFFFFFFF)
				return (LOG_START_ADDR2+i*LOG_INFO_LEN);
		}
	}

	for(uint32_t i=0;i<(2*LOG_SECTOR_NUM);i++) //������������һ����¼�ռ䶼���˵�ʱ��,��ǿ����Ϊ��д��һ������
		Mx25_Erase_Sector((LOG_START_ADDR1/MX25_SECTOR_LEN)+i); //�˴��Ǽ�С�����������,����������

	return LOG_START_ADDR1;
}
/************************************************************!
*Function:
*Description:
*Input: null
*Output: null
*Return:
*************************************************************/
uint32_t Locate_Soe_Position(void)
{
	FOURBYTE FB;
	uint32_t pointer;

	pointer=((SOE_FLASH_LEN/SOE_INFO_LEN)-1)*SOE_INFO_LEN;  //������һ����¼���ݿռ���Ե�ַ(ƫ��)

	Mx25_Read_U8_Array(SOE_START_ADDR1+pointer,FB.U8,4,false);

	if(FB.U32==0xFFFFFFFF) //��һ�������һ����¼���ݿռ�û������,������ָ���ڵ�һ������
	{
		for(uint32_t i=0;i<(SOE_FLASH_LEN/SOE_INFO_LEN);i++)
		{
			Mx25_Read_U8_Array(SOE_START_ADDR1+i*SOE_INFO_LEN,FB.U8,4,false);

			if(FB.U32==0xFFFFFFFF)
				return (SOE_START_ADDR1+i*SOE_INFO_LEN);
		}
	}

	Mx25_Read_U8_Array(SOE_START_ADDR2+pointer,FB.U8,4,false);

	if(FB.U32==0xFFFFFFFF) //�ڶ��������һ����¼���ݿռ�û������,������ָ���ڵڶ�������
	{
		for(uint32_t i=0;i<(SOE_FLASH_LEN/SOE_INFO_LEN);i++)
		{
			Mx25_Read_U8_Array(SOE_START_ADDR2+i*SOE_INFO_LEN,FB.U8,4,false);

			if(FB.U32==0xFFFFFFFF)
				return (SOE_START_ADDR2+i*SOE_INFO_LEN);
		}
	}

	for(uint32_t i=0;i<SOE_SECTOR_NUM;i++) //������������һ����¼�ռ䶼���˵�ʱ��,��ǿ����Ϊ��д��һ������
		Mx25_Erase_Sector((SOE_START_ADDR1/MX25_SECTOR_LEN)+i); //�˴��Ǽ�С�����������,����������

	return SOE_START_ADDR1;
}
/************************************************************!
*Function:
*Description:
*Input: null
*Output: null
*Return:
*************************************************************/
uint32_t Locate_Yc_Position(void)
{
	FOURBYTE FB;

	for(uint32_t i=0;i<((2*YC_SECTOR_NUM)/YC_FILE_SECTOR_NUM);i++)
	{
		Mx25_Read_U8_Array((YC_START_ADDR1+i*YC_FILE_LEN),FB.U8,4,false);

		if(i==0&&FB.U32==0xFFFFFFFF) //��һ���ļ�������
			return YC_START_ADDR1;

		if(i==(((2*YC_SECTOR_NUM)/YC_FILE_SECTOR_NUM)-1)&&FB.U32!=0xFFFFFFFF) //���һ���ļ�������
			return YC_START_ADDR1+i*YC_FILE_LEN;

		if(FB.U32!=0xFFFFFFFF) //�м���ļ�������
			continue;

		return YC_START_ADDR1+(i-1)*YC_FILE_LEN;
	}

	for(uint32_t i=0;i<(2*YC_SECTOR_NUM);i++)   //����,����
		Mx25_Erase_Sector((YC_START_ADDR1/MX25_SECTOR_LEN)+i);

	return YC_START_ADDR1;
}
/************************************************************!
*Function:
*Description:
*Input: null
*Output: null
*Return:
*************************************************************/
uint32_t Locate_Fault_Position(void)
{
	FOURBYTE FB;
	uint32_t pointer;

	pointer=((FAULT_FLASH_LEN/FAULT_INFO_LEN)-1)*FAULT_INFO_LEN;  //������һ����¼���ݿռ���Ե�ַ(ƫ��)

	Mx25_Read_U8_Array(FAULT_START_ADDR1+pointer,FB.U8,4,false);

	if(FB.U32==0xFFFFFFFF) //��һ�������һ����¼���ݿռ�û������,������ָ���ڵ�һ������
	{
		for(uint32_t i=0;i<(FAULT_FLASH_LEN/FAULT_INFO_LEN);i++)
		{
			Mx25_Read_U8_Array(FAULT_START_ADDR1+i*FAULT_INFO_LEN,FB.U8,4,false);

			if(FB.U32==0xFFFFFFFF)
				return (FAULT_START_ADDR1+i*FAULT_INFO_LEN);
		}
	}

	Mx25_Read_U8_Array(FAULT_START_ADDR2+pointer,FB.U8,4,false);

	if(FB.U32==0xFFFFFFFF) //�ڶ��������һ����¼���ݿռ�û������,������ָ���ڵڶ�������
	{
		for(uint32_t i=0;i<(FAULT_FLASH_LEN/FAULT_INFO_LEN);i++)
		{
			Mx25_Read_U8_Array(FAULT_START_ADDR2+i*FAULT_INFO_LEN,FB.U8,4,false);

			if(FB.U32==0xFFFFFFFF)
				return (FAULT_START_ADDR2+i*FAULT_INFO_LEN);
		}
	}

	for(uint32_t i=0;i<FAULT_SECTOR_NUM;i++) //������������һ����¼�ռ䶼���˵�ʱ��,��ǿ����Ϊ��д��һ������
		Mx25_Erase_Sector((FAULT_START_ADDR1/MX25_SECTOR_LEN)+i); //�˴��Ǽ�С�����������,����������

	return FAULT_START_ADDR1;
}
/************************************************************!
*Function:
*Description:
*Input: null
*Output: null
*Return:
*************************************************************/
uint32_t Locate_Yk_Position(void)
{
	FOURBYTE FB;
	uint32_t pointer;

	pointer=((YK_FLASH_LEN/YK_INFO_LEN)-1)*YK_INFO_LEN;  //������һ����¼���ݿռ���Ե�ַ(ƫ��)

	Mx25_Read_U8_Array(YK_START_ADDR1+pointer,FB.U8,4,false);

	if(FB.U32==0xFFFFFFFF) //��һ�������һ����¼���ݿռ�û������,������ָ���ڵ�һ������
	{
		for(uint32_t i=0;i<(YK_FLASH_LEN/YK_INFO_LEN);i++)
		{
			Mx25_Read_U8_Array(YK_START_ADDR1+i*YK_INFO_LEN,FB.U8,4,false);

			if(FB.U32==0xFFFFFFFF)
				return (YK_START_ADDR1+i*YK_INFO_LEN);
		}
	}

	Mx25_Read_U8_Array(YK_START_ADDR2+pointer,FB.U8,4,false);

	if(FB.U32==0xFFFFFFFF) //�ڶ��������һ����¼���ݿռ�û������,������ָ���ڵڶ�������
	{
		for(uint32_t i=0;i<(YK_FLASH_LEN/YK_INFO_LEN);i++)
		{
			Mx25_Read_U8_Array(YK_START_ADDR2+i*YK_INFO_LEN,FB.U8,4,false);

			if(FB.U32==0xFFFFFFFF)
				return (YK_START_ADDR2+i*YK_INFO_LEN);
		}
	}

	for(uint32_t i=0;i<(2*YK_SECTOR_NUM);i++) //������������һ����¼�ռ䶼���˵�ʱ��,��ǿ����Ϊ��д��һ������
		Mx25_Erase_Sector((YK_START_ADDR1/MX25_SECTOR_LEN)+i); //�˴��Ǽ�С�����������,����������

	return YK_START_ADDR1;
}
/************************************************************!
*Function:
*Description:
*Input: null
*Output: null
*Return:
*************************************************************/
uint32_t Locate_Wave_Position(void)
{
	FOURBYTE FB;

	for(uint32_t i=0;i<((2*WAVE_FLASH_LEN)/WAVE_FILE_LEN);i++) //���ҿ�1��2�в����ļ��׵�ַ����
	{
		Mx25_Read_U8_Array(WAVE_START_ADDR1+i*WAVE_FILE_LEN,FB.U8,4,false);

		if(i==0&&FB.U32==0xFFFFFFFF)
			return WAVE_START_ADDR1;

		if(FB.U32==0xFFFFFFFF)
			return (WAVE_START_ADDR1+(i-1)*WAVE_FILE_LEN);
	}

	for(uint32_t i=0;i<WAVE_SECTOR_NUM;i++) //ǿ�Ʋ�����1����,ָ��ָ���1�׵�ַ(��С����)
		Mx25_Erase_Sector((WAVE_START_ADDR1/MX25_SECTOR_LEN)+i);

	return WAVE_START_ADDR1;
}
/************************************************************!
*Function:
*Description:
*Input: null
*Output: null
*Return:
*************************************************************/
bool Log_Data_Record(uint8_t type,char *ind, ...)
{
	char *para;
	va_list vl;
	uint32_t U32;
	LOGRECORD LOG;
	uint8_t strlens;
	uint8_t data[23];

	LOG.LENS=0;
	LOG.TYPE=type;

	vTaskSuspendAll();
	Wdog_Feed();

	NowTime2P101Time(LOG.TIME.DATA,7);

	if(((gSYSFLAG.MFW.LOG-LOG_START_ADDR1)/LOG_FLASH_LEN)==0) //ָ���ڵ�һ������
	{
		if((LOG_START_ADDR1+LOG_FLASH_LEN-gSYSFLAG.MFW.LOG)<LOG_INFO_LEN)
		{
			gSYSFLAG.MFW.LOG=LOG_START_ADDR2;

			for(uint32_t i=0;i<LOG_SECTOR_NUM;i++)
				Mx25_Erase_Sector((LOG_START_ADDR2/MX25_SECTOR_LEN)+i);
		}
	}

	if(((gSYSFLAG.MFW.LOG-LOG_START_ADDR1)/LOG_FLASH_LEN)==1) //ָ���ڵڶ�������
	{
		if((LOG_START_ADDR2+LOG_FLASH_LEN-gSYSFLAG.MFW.LOG)<LOG_INFO_LEN)
		{
			gSYSFLAG.MFW.LOG=LOG_START_ADDR1;

			for(uint32_t i=0;i<LOG_SECTOR_NUM;i++)
				Mx25_Erase_Sector((LOG_START_ADDR1/MX25_SECTOR_LEN)+i);
		}
	}

	va_start(vl,ind);

	while(*ind!='\0')
	{
		switch(*(ind++))
		{
			case 'E':  //2017-03-14 12:31:45.123
				U32=va_arg(vl,uint32_t);
				strlens=Get_P101_Time((uint8_t *)U32,data);

				if(Check_Log_Lens(strlens,LOG.LENS)==false)
				{
					va_end(vl);
					xTaskResumeAll();

					return false;
				}

				memcpy(LOG.ASCII+LOG.LENS,data,strlens);
				LOG.LENS+=strlens;
				break;

			case 'S':  //�ַ���
				para=va_arg(vl,char*);
				strlens=strlen(para);

				if(Check_Log_Lens(strlens,LOG.LENS)==false)
				{
					va_end(vl);
					xTaskResumeAll();

					return false;
				}

				strcpy(LOG.ASCII+LOG.LENS,para);
				LOG.LENS+=strlens;
				break;

			case 'H':  //ʮ������
				U32=va_arg(vl,uint32_t);
				strlens=Get_U32_Hex(U32,data,11);

				if(Check_Log_Lens(strlens,LOG.LENS)==false)
				{
					va_end(vl);
					xTaskResumeAll();

					return false;
				}

				memcpy(LOG.ASCII+LOG.LENS,data,strlens);
				LOG.LENS+=strlens;
				break;

			case 'D':  //ʮ����
				U32=va_arg(vl,uint32_t);
				strlens=Get_U32_Dec(U32,data,10);

				if(Check_Log_Lens(10-strlens,LOG.LENS)==false)
				{
					va_end(vl);
					xTaskResumeAll();

					return false;
				}

				memcpy(LOG.ASCII+LOG.LENS,data+strlens,10-strlens);
				LOG.LENS+=10-strlens;
				break;

			case 'T': //2017-03-14
				U32=va_arg(vl,uint32_t);
				strlens=Get_U32_Time(U32,data,8);

				if(Check_Log_Lens(strlens,LOG.LENS)==false)
				{
					va_end(vl);
					xTaskResumeAll();

					return false;
				}

				memcpy(LOG.ASCII+LOG.LENS,data,strlens);
				LOG.LENS+=strlens;
				break;

			default :
				break;
		}
	}

	va_end(vl);

	strcpy(LOG.ASCII+LOG.LENS,"\r\n");

	LOG.LENS+=10; //1�ֽ�����+7�ֽ�ʱ��+2�ֽ�CRLF

	Mx25_Data_Storage(gSYSFLAG.MFW.LOG,LOG.DATA,LOG.LENS+1); //���ݴ洢,LENS���ȱ���δ�����Լ�����һ���ֽڴ�С

	gSYSFLAG.MFW.LOG+=LOG_INFO_LEN;

	#ifdef PRINT_MX25_LOG_DEBUG //��ӡ��־��Ϣ
	DEBUG_PRINT_LOG(gSYSFLAG.MFW.LOG-LOG_INFO_LEN);
	#endif

	Wdog_Feed();
	xTaskResumeAll();

	return true;
}
/************************************************************!
*Function:
*Description:
*Input: null
*Output: null
*Return:
*************************************************************/
bool Check_Log_Lens(uint32_t lens,uint32_t size)
{
	if((size+lens)>128)
	{
		#ifdef PRINT_MX25_LOG_DEBUG //��ӡ��־��Ϣ
		DEBUG_PRINT_NISR("KKNS","<----- ��־����Խ��!!!!!!!!!!!!!!!!!!!!!! ----->\r\n\r\n");
		#endif

		return false;
	}

	return true;
}
/************************************************************!
*Function:
*Description:
*Input: null
*Output: null
*Return:
*************************************************************/
void Soe_Data_Record(ECPDATA_YX *YX,uint8_t soe,bool updatetime,uint8_t *soetime)
{
	P101SOE PS;

	PS.TYPE=30; //������Ϣ
	PS.CRLF=0x0A0D; //�س�����

	YX->MSG.U16=soe;
	PS.SOE=YX->MSG.U16;
	PS.MSGADDR.U16=YX->ADDR.U16;

	vTaskSuspendAll();
	Wdog_Feed();

	if(((gSYSFLAG.MFW.SOE-SOE_START_ADDR1)/SOE_FLASH_LEN)==0) //ָ���ڵ�һ������
	{
		if((SOE_START_ADDR1+SOE_FLASH_LEN-gSYSFLAG.MFW.SOE)<SOE_INFO_LEN) //��һ��ռ�����
		{
			gSYSFLAG.MFW.SOE=SOE_START_ADDR2; //�л����ڶ���

			for(uint32_t i=0;i<SOE_SECTOR_NUM;i++) //�����ڶ���
				Mx25_Erase_Sector((SOE_START_ADDR2/MX25_SECTOR_LEN)+i);
		}
	}

	if(((gSYSFLAG.MFW.SOE-SOE_START_ADDR1)/SOE_FLASH_LEN)==1) //ָ���ڵڶ�������
	{
		if((SOE_START_ADDR2+SOE_FLASH_LEN-gSYSFLAG.MFW.SOE)<SOE_INFO_LEN) //�ڶ���ռ�����
		{
			gSYSFLAG.MFW.SOE=SOE_START_ADDR1; //�л�����һ��

			for(uint32_t i=0;i<SOE_SECTOR_NUM;i++) ////������һ��
				Mx25_Erase_Sector((SOE_START_ADDR1/MX25_SECTOR_LEN)+i);
		}
	}

	if(updatetime==false) //����ϵͳʱ��
		memcpy(PS.TIME,soetime,7);
	else
		NowTime2P101Time(PS.TIME,7);

	Mx25_Data_Storage(gSYSFLAG.MFW.SOE,PS.DATA,SOE_INFO_LEN);
	gSYSFLAG.MFW.SOE+=SOE_INFO_LEN;

	Wdog_Feed();
	xTaskResumeAll();

	Add_P101SoeQueue(&gSOEQUEUE,&PS);

	#ifdef PRINT_MX25_SOE_DEBUG //��ӡSOE��Ϣ
	DEBUG_PRINT_SOE(gSYSFLAG.MFW.SOE-SOE_INFO_LEN);
	#endif
}
/************************************************************!
*Function:
*Description:
*Input: null
*Output: null
*Return:
*************************************************************/
uint8_t Yc_Data_Record(void)
{
	FOURBYTE FB;

	if(((gUNIXTIME.UNIX-10)%900)!=0)
		return false;

	if(gUNIXTIME.UNIX==gSYSFLAG.STM.YC_RECORD_TIME)
		return false;

	gSYSFLAG.STM.YC_RECORD_TIME=gUNIXTIME.UNIX;

//	if(gYCFILE.TIMEOUT==0) //��ң�������ϱ�
//		return false;

//	if((gUNIXTIME.UNIX-gYCFILE.TIMEOUT)<5) //��ʱ120��,��Ϊ����һ��ң������
//		return false;

	gYCFILE.TIMEOUT+=28800; //���϶�����ʱ��8��Сʱ

	//gYCFILE.SN=((gYCFILE.TIMEOUT%(15*YC_INFO_NUM))/15)+1;
	gYCFILE.SN=((gUNIXTIME.UNIX%86400)/900)+1; //86400:24Сʱ  //900:15����

	gYCFILE.N=gSYSPARA.LINEGROUP.LINENUM*9;  //ͳ�Ƹýڶ������ݸ���
	gYCFILE.LENS=11+(5*gYCFILE.N)+2;
	gYCFILE.DATA[11+(5*gYCFILE.N)+1]=0x0D;
	gYCFILE.DATA[11+(5*gYCFILE.N)+2]=0x0A;

	for(uint8_t i=0;i<YC_INFO_NUM;i++) //�����Ч�Ķ��������ļ�ͷʱ��
	{
		Mx25_Read_U8_Array(gSYSFLAG.MFW.YC+i*YC_INFO_LEN+8,FB.U8,4,false); //+8:��ȡ�����ݵ������յ�ʱ��λ��

		if(FB.U32==0xFFFFFFFF||FB.U32!=0x00000000)
			break;
	}

	gYCFILE.OLDTIME=((FB.U32&0xFFFF1F00)>>8);
	gYCFILE.NEWTIME=(((uint32_t)gYCFILE.TIME.YEAR)<<16)+(((uint32_t)gYCFILE.TIME.MONTH)<<8)+(((uint32_t)gYCFILE.TIME.DAY.DAY)<<0);

	if(gYCFILE.NEWTIME!=gYCFILE.OLDTIME) //��ǰָ����ļ�ͷʱ���뵱ǰң��ʱ�䲻ƥ��
	{
		if(gYCFILE.OLDTIME!=0x00FFFF1F) //��ǰ�ļ����ļ�ͷ
		{
			#ifdef PRINT_YC_FILE_DEBUG //��ӡ������ң���ļ�
			DEBUG_PRINT_YC_FILE(gSYSFLAG.MFW.YC);
			#endif

			Switch_YaoCeFile();
		}

		#ifdef PRINT_YC_FILE_DEBUG //��ӡ�ļ���Ϣ
		uint32_t sn;
		sn=((gSYSFLAG.MFW.YC-YC_START_ADDR1)/YC_FILE_LEN)+1;
		if(sn!=1)
			DEBUG_PRINT("NSDSTSDSTS","�µ�һ��,���ɵ� ",sn-1," ��ң���ļ�(",gYCFILE.OLDTIME,"),���л����� ",sn," ��ң���ļ�(",gYCFILE.NEWTIME,")!\r\n");
		#endif
	}

	Mx25_Read_U8_Array(gSYSFLAG.MFW.YC+(gYCFILE.SN-1)*YC_INFO_LEN,FB.U8,4,false);

	if(FB.U32!=0xFFFFFFFF) //����д,�л��ļ�
	{
		#ifdef PRINT_YC_FILE_DEBUG
		DEBUG_PRINT("NSDSDS","<----- ��ǰ�� ",((gSYSFLAG.MFW.YC-YC_START_ADDR1)/YC_FILE_LEN)+1," ��ң���ļ��ĵ� ",gYCFILE.SN," �����������ظ�,���л�����һ�ļ�!\r\n");
		DEBUG_PRINT_YC_FILE(gSYSFLAG.MFW.YC);
		#endif

		Switch_YaoCeFile();
	}

	Mx25_Data_Storage(gSYSFLAG.MFW.YC+(gYCFILE.SN-1)*YC_INFO_LEN,gYCFILE.DATA,YC_INFO_LEN);

	Fill_YaoCeFile(gYCFILE.SN,gYCFILE.N);

	#ifdef PRINT_YC_FILE_DEBUG //��ӡ��ǰң���ļ�����Ϣ
	DEBUG_PRINT_YC_FILE_SECTION(gSYSFLAG.MFW.YC,gYCFILE.SN);
	#endif

	YaoCeFile_Init(&gYCFILE);

	return true;
}
/************************************************************!
*Function:
*Description:
*Input: null
*Output: null
*Return:
*************************************************************/
void Fill_YaoCeFile(uint8_t sn,uint8_t n)
{
	FOURBYTE FB;
	YAOCEFILE YCF;

	YaoCeFile_Init(&YCF);

	YCF.N=n;
	YCF.LENS=11+(5*YCF.N)+2;
	YCF.DATA[11+(5*YCF.N)+1]=0x0D;
	YCF.DATA[11+(5*YCF.N)+2]=0x0A;

	for(uint32_t i=0;i<sn;i++)
	{
		Mx25_Read_U8_Array(gSYSFLAG.MFW.YC+i*YC_INFO_LEN,FB.U8,4,false);

		if(FB.U32==0xFFFFFFFF)
		{
			YCF.SN=i+1;
			//YCF.TIME.DATA          //�յĶ�������ʱ��δ������,��Ϊ0
			Mx25_Data_Storage(gSYSFLAG.MFW.YC+i*YC_INFO_LEN,YCF.DATA,YC_INFO_LEN);
		}
	}
}
/************************************************************!
*Function:
*Description:
*Input: null
*Output: null
*Return:
*************************************************************/
void Switch_YaoCeFile(void)
{
	gSYSFLAG.MFW.YC+=YC_FILE_LEN;

	if(gSYSFLAG.MFW.YC==(YC_START_ADDR1+YC_FLASH_LEN))
	{
		for(uint32_t i=0;i<YC_SECTOR_NUM;i++)
			Mx25_Erase_Sector((YC_START_ADDR2/MX25_SECTOR_LEN)+i);
	}

	if(gSYSFLAG.MFW.YC==(YC_START_ADDR2+YC_FLASH_LEN))
	{
		gSYSFLAG.MFW.YC=YC_START_ADDR1;

		for(uint32_t i=0;i<YC_SECTOR_NUM;i++)
			Mx25_Erase_Sector((YC_START_ADDR1/MX25_SECTOR_LEN)+i);
	}
}
/************************************************************!
*Function:
*Description:
*Input: null
*Output: null
*Return:
*************************************************************/
void Yk_Data_Record(P101YK YK)
{
	YK.CRLF=0x0A0D; //�س�����
	NowTime2P101Time(YK.TIME,7);

	if(((gSYSFLAG.MFW.YK-YK_START_ADDR1)/YK_FLASH_LEN)==0) //ָ���ڵ�һ������
	{
		if((YK_START_ADDR1+YK_FLASH_LEN-gSYSFLAG.MFW.YK)<YK_INFO_LEN) //����һ��ռ�����
		{
			gSYSFLAG.MFW.YK=YK_START_ADDR2; //�л����ڶ�����

			for(uint32_t i=0;i<YK_SECTOR_NUM;i++) //�����ڶ���
				Mx25_Erase_Sector(((YK_START_ADDR2/MX25_SECTOR_LEN)+i));
		}
	}

	if(((gSYSFLAG.MFW.YK-YK_START_ADDR1)/YK_FLASH_LEN)==1) //ָ���ڵڶ�������
	{
		if((YK_START_ADDR2+YK_FLASH_LEN-gSYSFLAG.MFW.YK)<YK_INFO_LEN) //���ڶ���ռ�����
		{
			gSYSFLAG.MFW.YK=YK_START_ADDR1; //�л�����һ����

			for(uint32_t i=0;i<YK_SECTOR_NUM;i++) //������һ��
				Mx25_Erase_Sector(((YK_START_ADDR1/MX25_SECTOR_LEN)+i));
		}
	}

	Mx25_Data_Storage(gSYSFLAG.MFW.YK,YK.DATA,YK_INFO_LEN);
	gSYSFLAG.MFW.YK+=YK_INFO_LEN;

	#ifdef PRINT_MX25_YK_DEBUG //��ӡYK��Ϣ
	DEBUG_PRINT_YK(gSYSFLAG.MFW.YK-YK_INFO_LEN);
	#endif
}
/************************************************************!
*Function:
*Description:
*Input:
*Output: null
*Return:
*************************************************************/
void Fault_Data_Record(uint8_t fault,uint8_t *wavetime,uint16_t addr)
{
	UNIXTIME UT;
	P101FAULT PF;

	PF.CRLF=0x0A0D;
	memcpy(UT.DATA,wavetime,8);
	UnixTime2P101Time(&UT,PF.TIME,7);

	if(((gSYSFLAG.MFW.FAULT-FAULT_START_ADDR1)/FAULT_FLASH_LEN)==0) //ָ���ڵ�һ������
	{
		if((FAULT_START_ADDR1+FAULT_FLASH_LEN-gSYSFLAG.MFW.FAULT)<FAULT_INFO_LEN) //����һ��ռ�����
		{
			gSYSFLAG.MFW.FAULT=FAULT_START_ADDR2; //�л�����2����

			for(uint32_t i=0;i<FAULT_SECTOR_NUM;i++)
				Mx25_Erase_Sector((FAULT_START_ADDR2/MX25_SECTOR_LEN)+i);
		}
	}

	if(((gSYSFLAG.MFW.FAULT-FAULT_START_ADDR1)/FAULT_FLASH_LEN)==1) //ָ���ڵڶ�������
	{
		if((FAULT_START_ADDR2+FAULT_FLASH_LEN-gSYSFLAG.MFW.FAULT)<FAULT_INFO_LEN) //���ڶ���ռ�����
		{
			gSYSFLAG.MFW.FAULT=FAULT_START_ADDR1; //�л�����1����

			for(uint32_t i=0;i<FAULT_SECTOR_NUM;i++)
				Mx25_Erase_Sector((FAULT_START_ADDR1/MX25_SECTOR_LEN)+i);
		}
	}

	Mx25_Data_Storage(gSYSFLAG.MFW.FAULT,PF.DATA,FAULT_INFO_LEN);

	gSYSFLAG.MFW.FAULT+=FAULT_INFO_LEN;

	Add_P101FaultQueue(&gFAULTQUEUE,&PF);

	#ifdef PRINT_MX25_FAULT_DEBUG
	DEBUG_PRINT_FAULT(gSYSFLAG.MFW.FAULT-FAULT_INFO_LEN);
	#endif
}
/************************************************************!
*Function:
*Description:
*Input:
*Output: null
*Return: ��������״̬
*************************************************************/
void Wave_Data_Record(uint8_t *data,uint32_t lens)
{
	Mx25_Data_Storage(gSYSFLAG.MFW.WAVE,data,lens);

	gSYSFLAG.MFW.WAVE+=lens;
}
/************************************************************!
*Function:
*Description:
*Input: null
*Output: null
*Return:
*************************************************************/
uint32_t Switch_NextWave_Position(void)
{
	FOURBYTE FB;

	gSYSFLAG.MFW.WAVE=gSYSFLAG.MFW.WAVE-((gSYSFLAG.MFW.WAVE-WAVE_START_ADDR1)%WAVE_FILE_LEN);

	Mx25_Read_U8_Array(gSYSFLAG.MFW.WAVE,FB.U8,4,false);

	if(FB.U32==0xFFFFFFFF)
		return gSYSFLAG.MFW.WAVE;

	gSYSFLAG.MFW.WAVE+=WAVE_FILE_LEN;

	if(gSYSFLAG.MFW.WAVE==(WAVE_START_ADDR1+WAVE_FLASH_LEN))
	{
		gSYSFLAG.MFW.WAVE=WAVE_START_ADDR2; //ǿ�Ȱ�

		for(uint32_t i=0;i<WAVE_SECTOR_NUM;i++)
			Mx25_Erase_Sector((WAVE_START_ADDR2/MX25_SECTOR_LEN)+i);
	}

	if(gSYSFLAG.MFW.WAVE==(WAVE_START_ADDR2+WAVE_FLASH_LEN))
	{
		gSYSFLAG.MFW.WAVE=WAVE_START_ADDR1;

		for(uint32_t i=0;i<WAVE_SECTOR_NUM;i++)
			Mx25_Erase_Sector((WAVE_START_ADDR1/MX25_SECTOR_LEN)+i);
	}

	return gSYSFLAG.MFW.WAVE;
}
/************************************************************!
*Function:
*Description:
*Input: null
*Output: null
*Return:
*************************************************************/
void Locate_Log_FileInfo(FILEINFO *FI)
{
	FOURBYTE FB;
	LOGRECORD LOG;

	FI->MSGADDR.U16=0x6807;

	if(((gSYSFLAG.MFW.LOG-LOG_START_ADDR1)/LOG_FLASH_LEN)==0) //дָ���ڿ�1
	{
		FI->INFONUM=((gSYSFLAG.MFW.LOG-LOG_START_ADDR1)/LOG_INFO_LEN);

		if(FI->INFONUM>=READ_LOG_NUM) //��ȡ���µ�n����¼����
		{
			FI->READ=LOG_START_ADDR1+((FI->INFONUM-READ_LOG_NUM)*LOG_INFO_LEN);

			for(uint32_t i=0;i<READ_LOG_NUM;i++)
			{
				Mx25_Read_U8_Array(FI->READ+i*LOG_INFO_LEN,FB.U8,4,false);

				if(FB.U32==0xFFFFFFFF) //����,�������
					continue;

				FI->LENS+=FB.U8[0];
			}

			FI->INFONUM=READ_LOG_NUM;
		}

		if(FI->INFONUM<READ_LOG_NUM)
		{
			Mx25_Read_U8_Array(LOG_START_ADDR2,FB.U8,4,false); //�жϿ�2�Ƿ�������

			if(FB.U32==0xFFFFFFFF) //��2������
			{
				FI->READ=LOG_START_ADDR1;

				for(uint32_t i=0;i<FI->INFONUM;i++)
				{
					Mx25_Read_U8_Array(LOG_START_ADDR1+i*LOG_INFO_LEN,FB.U8,4,false);

					if(FB.U32==0xFFFFFFFF) //����,�������
						continue;

					FI->LENS+=FB.U8[0];
				}
			}
			else
			{
				for(uint32_t i=0;i<FI->INFONUM;i++) //��ȡ��1�����ݳ���
				{
					Mx25_Read_U8_Array(LOG_START_ADDR1+i*LOG_INFO_LEN,FB.U8,4,false);

					if(FB.U32==0xFFFFFFFF) //����,�������
						continue;

					FI->LENS+=FB.U8[0];
				}

				FI->INFONUM=READ_LOG_NUM-FI->INFONUM;

				FI->READ=LOG_START_ADDR2+(((LOG_FLASH_LEN/LOG_INFO_LEN)-FI->INFONUM)*LOG_INFO_LEN);

				for(uint32_t i=0;i<FI->INFONUM;i++) //��ȡ��2�����ݳ���
				{
					Mx25_Read_U8_Array(FI->READ+i*LOG_INFO_LEN,FB.U8,4,false);

					if(FB.U32==0xFFFFFFFF) //����,�������
						continue;

					FI->LENS+=FB.U8[0];
				}

				FI->INFONUM=READ_LOG_NUM;
			}
		}
	}

	if(((gSYSFLAG.MFW.LOG-LOG_START_ADDR1)/LOG_FLASH_LEN)==1) //дָ���ڿ�2
	{
		FI->INFONUM=((gSYSFLAG.MFW.LOG-LOG_START_ADDR2)/LOG_INFO_LEN);

		if(FI->INFONUM>=READ_LOG_NUM) //��ȡ���µ�n����¼����
		{
			FI->READ=LOG_START_ADDR2+((FI->INFONUM-READ_LOG_NUM)*LOG_INFO_LEN);

			for(uint32_t i=0;i<READ_LOG_NUM;i++)
			{
				Mx25_Read_U8_Array(FI->READ+i*LOG_INFO_LEN,FB.U8,4,false);

				if(FB.U32==0xFFFFFFFF) //����,�������
					continue;

				FI->LENS+=FB.U8[0];
			}

			FI->INFONUM=READ_LOG_NUM;
		}

		if(FI->INFONUM<READ_LOG_NUM)
		{
			Mx25_Read_U8_Array(LOG_START_ADDR1,FB.U8,4,false); //�жϿ�1�Ƿ�������

			if(FB.U32==0xFFFFFFFF) //��1������
			{
				FI->READ=LOG_START_ADDR2;

				for(uint32_t i=0;i<FI->INFONUM;i++)
				{
					Mx25_Read_U8_Array(LOG_START_ADDR2+i*LOG_INFO_LEN,FB.U8,4,false);

					if(FB.U32==0xFFFFFFFF) //����,�������
						continue;

					FI->LENS+=FB.U8[0];
				}
			}
			else
			{
				for(uint32_t i=0;i<FI->INFONUM;i++) //��ȡ��2�����ݳ���
				{
					Mx25_Read_U8_Array(LOG_START_ADDR2+i*LOG_INFO_LEN,FB.U8,4,false);

					if(FB.U32==0xFFFFFFFF) //����,�������
						continue;

					FI->LENS+=FB.U8[0];
				}

				FI->INFONUM=READ_LOG_NUM-FI->INFONUM;

				FI->READ=LOG_START_ADDR1+(((LOG_FLASH_LEN/LOG_INFO_LEN)-FI->INFONUM)*LOG_INFO_LEN);

				for(uint32_t i=0;i<FI->INFONUM;i++) //��ȡ��1�����ݳ���
				{
					Mx25_Read_U8_Array(FI->READ+i*LOG_INFO_LEN,FB.U8,4,false);

					if(FB.U32==0xFFFFFFFF) //����,�������
						continue;

					FI->LENS+=FB.U8[0];
				}

				FI->INFONUM=READ_LOG_NUM;
			}
		}
	}

	Mx25_Read_U8_Array(FI->READ,LOG.DATA,LOG_INFO_LEN,false);
	memcpy(FI->TIME,LOG.TIME.DATA,7);

	if(FI->INFONUM!=0)
		FI->LENS+=LOG_INFO_HEAD+1;
	else
		FI->LENS=0;

	FI->SENDNUM=FI->INFONUM;
}
/************************************************************!
*Function:
*Description:
*Input: null
*Output: null
*Return:
*************************************************************/
bool Locate_Soe_FileInfo(FILEINFO *FI)
{
	P101SOE PS;
	FOURBYTE FB;

	FI->MSGADDR.U16=0x6808;

	if(((gSYSFLAG.MFW.SOE-SOE_START_ADDR1)/SOE_FLASH_LEN)==0) //дָ���ڿ�1
	{
		FI->INFONUM=((gSYSFLAG.MFW.SOE-SOE_START_ADDR1)/SOE_INFO_LEN);

		if(FI->INFONUM>=READ_SOE_NUM) //��ȡ���µ�n����¼����
		{
			FI->READ=SOE_START_ADDR1+((FI->INFONUM-READ_SOE_NUM)*SOE_INFO_LEN);

			FI->INFONUM=READ_SOE_NUM;
			FI->LENS+=READ_SOE_NUM*SOE_INFO_LEN;
		}

		if(FI->INFONUM<READ_SOE_NUM)
		{
			Mx25_Read_U8_Array(SOE_START_ADDR2,FB.U8,4,false);//�жϿ�2�Ƿ�������

			if(FB.U32==0xFFFFFFFF) //��2������
			{
				FI->READ=SOE_START_ADDR1;
				FI->LENS+=FI->INFONUM*SOE_INFO_LEN;
			}

			if(FB.U32!=0xFFFFFFFF)
			{
				FI->INFONUM=READ_SOE_NUM-FI->INFONUM;

				FI->READ=SOE_START_ADDR2+(((SOE_FLASH_LEN/SOE_INFO_LEN)-FI->INFONUM)*SOE_INFO_LEN);

				FI->INFONUM=READ_SOE_NUM;
				FI->LENS+=READ_SOE_NUM*SOE_INFO_LEN;
			}
		}
	}

	if(((gSYSFLAG.MFW.SOE-SOE_START_ADDR1)/SOE_FLASH_LEN)==1) //дָ���ڿ�1
	{
		FI->INFONUM=((gSYSFLAG.MFW.SOE-SOE_START_ADDR2)/SOE_INFO_LEN);

		if(FI->INFONUM>=READ_SOE_NUM) //��ȡ���µ�n����¼����
		{
			FI->READ=SOE_START_ADDR2+((FI->INFONUM-READ_SOE_NUM)*SOE_INFO_LEN);

			FI->INFONUM=READ_SOE_NUM;
			FI->LENS+=READ_SOE_NUM*SOE_INFO_LEN;
		}

		if(FI->INFONUM<READ_SOE_NUM)
		{
			Mx25_Read_U8_Array(SOE_START_ADDR1,FB.U8,4,false);//�жϿ�2�Ƿ�������

			if(FB.U32==0xFFFFFFFF) //��2������
			{
				FI->READ=SOE_START_ADDR2;
				FI->LENS+=FI->INFONUM*SOE_INFO_LEN;
			}
			else
			{
				FI->INFONUM=READ_SOE_NUM-FI->INFONUM;

				FI->READ=SOE_START_ADDR1+(((SOE_FLASH_LEN/SOE_INFO_LEN)-FI->INFONUM)*SOE_INFO_LEN);

				FI->INFONUM=READ_SOE_NUM;
				FI->LENS+=READ_SOE_NUM*SOE_INFO_LEN;
			}
		}
	}

	Mx25_Read_U8_Array(FI->READ,PS.DATA,SOE_INFO_LEN,false);
	memcpy(FI->TIME,PS.TIME,7);

	if(FI->INFONUM==0)
		FI->LENS=0;
	else
	{
		if((FI->LENS%ECP_DATA_SEND_LEN)==0)
			FI->SENDNUM=FI->LENS/ECP_DATA_SEND_LEN;
		else
			FI->SENDNUM=(FI->LENS/ECP_DATA_SEND_LEN)+1;

		FI->LENS+=SOE_INFO_HEAD+1;
	}

	return true;
}
/************************************************************!
*Function:
*Description:
*Input: null
*Output: null
*Return:
*************************************************************/
bool Locate_Yc_FileInfo(FILEINFO *FI)
{
	FOURBYTE FB;
	YAOCEFILE YCF;
	uint8_t sn,block11,block12,block21,block22;

	FI->MSGADDR.U16=0x6806;

	if(((gSYSFLAG.MFW.YC-YC_START_ADDR1)/YC_FLASH_LEN)==0) //дָ���ڿ�1
	{
		sn=((gSYSFLAG.MFW.YC-YC_START_ADDR1)/YC_FILE_LEN)+1;

		if(sn==30)
		{
			FI->READ=YC_START_ADDR1+(FI->ID-22)*YC_FILE_LEN;
		}
		else
		{
			block11=51-sn+1;
			block12=51;
			block21=22;
			block22=51-sn;

			if(FI->ID>=block11&&FI->ID<=block12)
			{
				FI->READ=YC_START_ADDR1+(FI->ID-block11)*YC_FILE_LEN;
			}

			if(FI->ID>=block21&&FI->ID<=block22)
			{
				FI->READ=YC_START_ADDR2+(FI->ID-22+sn)*YC_FILE_LEN;
			}
		}
	}

	if(((gSYSFLAG.MFW.YC-YC_START_ADDR1)/YC_FLASH_LEN)==1) //дָ���ڿ�2
	{
		sn=((gSYSFLAG.MFW.YC-YC_START_ADDR2)/YC_FILE_LEN)+1;

		if(sn==30)
		{
			FI->READ=YC_START_ADDR2+(FI->ID-22)*YC_FILE_LEN;
		}
		else
		{
			block11=51-sn+1;
			block12=51;
			block21=22;
			block22=51-sn;

			if(FI->ID>=block11&&FI->ID<=block12)
			{
				FI->READ=YC_START_ADDR2+(FI->ID-block11)*YC_FILE_LEN;
			}

			if(FI->ID>=block21&&FI->ID<=block22)
			{
				FI->READ=YC_START_ADDR1+(FI->ID-22+sn)*YC_FILE_LEN;
			}
		}
	}

	for(uint32_t i=0;i<YC_INFO_NUM;i++)
	{
		Mx25_Read_U8_Array(FI->READ+i*YC_INFO_LEN,FB.U8,4,false);

		if(FB.U32!=0xFFFFFFFF)
			break;

		if(i==(YC_INFO_NUM-1))
		{
			FI->LENS=0;
			FI->INFONUM=0;
			memset(FI->TIME,0,7);

			return false;
		}
	}

	for(uint32_t i=0;i<YC_INFO_NUM;i++) //�����Ч�Ķ��������ļ�ͷʱ��
	{
		Mx25_Read_U8_Array(gSYSFLAG.MFW.YC+i*YC_INFO_LEN,YCF.DATA,YC_INFO_LEN+1,false); //+4:��ȡ�����ݵ������յ�ʱ��λ��

		if(YCF.TIME.YEAR!=0)
		{
			memcpy(FI->TIME,YCF.TIME.DATA,7);
			break;
		}
	}

	for(uint8_t i=0;i<YC_INFO_NUM;i++)
	{
		Mx25_Read_U8_Array(FI->READ+i*YC_INFO_LEN,YCF.DATA,YC_INFO_LEN+1,false);

		if(YCF.LENS==0xFF)
			continue;

		FI->INFONUM++;
		FI->LENS+=YCF.LENS;
	}

	FI->SENDNUM=FI->INFONUM;
	FI->LENS+=YC_FILEHEAD_LEN+1;

	return true;
}
/************************************************************!
*Function:
*Description:
*Input: null
*Output: null
*Return:
*************************************************************/
bool Locate_Fault_FileInfo(FILEINFO *FI)
{
	FOURBYTE FB;
	P101FAULT PF;

	FI->MSGADDR.U16=0x680B;

	if(((gSYSFLAG.MFW.FAULT-FAULT_START_ADDR1)/FAULT_FLASH_LEN)==0) //дָ���ڿ�1
	{
		FI->INFONUM=((gSYSFLAG.MFW.FAULT-FAULT_START_ADDR1)/FAULT_INFO_LEN);

		if(FI->INFONUM>=READ_FAULT_NUM) //��ȡ���µ�n����¼����
		{
			FI->READ=FAULT_START_ADDR1+((FI->INFONUM-READ_FAULT_NUM)*FAULT_INFO_LEN);

			FI->INFONUM=READ_FAULT_NUM;
			FI->LENS+=READ_FAULT_NUM*FAULT_INFO_LEN;
		}

		if(FI->INFONUM<READ_FAULT_NUM)
		{
			Mx25_Read_U8_Array(FAULT_START_ADDR2,FB.U8,4,false); //�жϿ�2�Ƿ�������

			if(FB.U32==0xFFFFFFFF) //��2������
			{
				FI->READ=FAULT_START_ADDR1;
				FI->LENS+=FI->INFONUM*FAULT_INFO_LEN;
			}

			if(FB.U32!=0xFFFFFFFF)
			{
				FI->INFONUM=READ_FAULT_NUM-FI->INFONUM;

				FI->READ=FAULT_START_ADDR2+(((FAULT_FLASH_LEN/FAULT_INFO_LEN)-FI->INFONUM)*FAULT_INFO_LEN);

				FI->INFONUM=READ_FAULT_NUM;
				FI->LENS+=READ_FAULT_NUM*FAULT_INFO_LEN;
			}
		}
	}

	if(((gSYSFLAG.MFW.FAULT-FAULT_START_ADDR1)/FAULT_FLASH_LEN)==1) //дָ���ڿ�1
	{
		FI->INFONUM=((gSYSFLAG.MFW.FAULT-FAULT_START_ADDR2)/FAULT_INFO_LEN);

		if(FI->INFONUM>=READ_FAULT_NUM) //��ȡ���µ�n����¼����
		{
			FI->READ=FAULT_START_ADDR2+((FI->INFONUM-READ_FAULT_NUM)*FAULT_INFO_LEN);

			FI->INFONUM=READ_FAULT_NUM;
			FI->LENS+=READ_FAULT_NUM*FAULT_INFO_LEN;
		}

		if(FI->INFONUM<READ_FAULT_NUM)
		{
			Mx25_Read_U8_Array(FAULT_START_ADDR1,FB.U8,4,false); //�жϿ�2�Ƿ�������

			if(FB.U32==0xFFFFFFFF) //��2������
			{
				FI->READ=FAULT_START_ADDR2;
				FI->LENS+=FI->INFONUM*FAULT_INFO_LEN;
			}
			else
			{
				FI->INFONUM=READ_FAULT_NUM-FI->INFONUM;

				FI->READ=FAULT_START_ADDR1+(((FAULT_FLASH_LEN/FAULT_INFO_LEN)-FI->INFONUM)*FAULT_INFO_LEN);

				FI->INFONUM=READ_FAULT_NUM;
				FI->LENS+=READ_FAULT_NUM*FAULT_INFO_LEN;
			}
		}
	}

	Mx25_Read_U8_Array(FI->READ,PF.DATA,FAULT_INFO_LEN,false);
	memcpy(FI->TIME,PF.TIME,7);

	if(FI->INFONUM==0)
		FI->LENS=0;
	else
	{
		if((FI->LENS%ECP_DATA_SEND_LEN)==0)
			FI->SENDNUM=FI->LENS/ECP_DATA_SEND_LEN;
		else
			FI->SENDNUM=(FI->LENS/ECP_DATA_SEND_LEN)+1;

		FI->LENS+=FAULT_INFO_HEAD+1;
	}

	return true;
}
/************************************************************!
*Function:
*Description:
*Input: null
*Output: null
*Return:
*************************************************************/
bool Locate_Yk_FileInfo(FILEINFO *FI)
{
	P101YK YK;
	FOURBYTE FB;

	FI->MSGADDR.U16=0x6809;

	if(((gSYSFLAG.MFW.YK-YK_START_ADDR1)/YK_FLASH_LEN)==0) //дָ���ڿ�1
	{
		FI->INFONUM=((gSYSFLAG.MFW.YK-YK_START_ADDR1)/YK_INFO_LEN);

		if(FI->INFONUM>=READ_YK_NUM) //��ȡ���µ�n����¼����
		{
			FI->READ=YK_START_ADDR1+((FI->INFONUM-READ_YK_NUM)*YK_INFO_LEN);

			FI->INFONUM=READ_YK_NUM;
			FI->LENS+=READ_YK_NUM*YK_INFO_LEN;
		}

		if(FI->INFONUM<READ_YK_NUM)
		{
			Mx25_Read_U8_Array(YK_START_ADDR2,FB.U8,4,false); //�жϿ�2�Ƿ�������

			if(FB.U32==0xFFFFFFFF) //��2������
			{
				FI->READ=YK_START_ADDR1;
				FI->LENS+=FI->INFONUM*YK_INFO_LEN;
			}

			if(FB.U32!=0xFFFFFFFF)
			{
				FI->INFONUM=READ_YK_NUM-FI->INFONUM;

				FI->READ=YK_START_ADDR2+(((YK_FLASH_LEN/YK_INFO_LEN)-FI->INFONUM)*YK_INFO_LEN);

				FI->INFONUM=READ_YK_NUM;
				FI->LENS+=READ_YK_NUM*YK_INFO_LEN;
			}
		}
	}

	if(((gSYSFLAG.MFW.YK-YK_START_ADDR1)/YK_FLASH_LEN)==1) //дָ���ڿ�1
	{
		FI->INFONUM=((gSYSFLAG.MFW.YK-YK_START_ADDR2)/YK_INFO_LEN);

		if(FI->INFONUM>=READ_YK_NUM) //��ȡ���µ�n����¼����
		{
			FI->READ=YK_START_ADDR2+((FI->INFONUM-READ_YK_NUM)*YK_INFO_LEN);

			FI->INFONUM=READ_YK_NUM;
			FI->LENS+=READ_YK_NUM*YK_INFO_LEN;
		}

		if(FI->INFONUM<READ_YK_NUM)
		{
			Mx25_Read_U8_Array(YK_START_ADDR1,FB.U8,4,false); //�жϿ�2�Ƿ�������

			if(FB.U32==0xFFFFFFFF) //��2������
			{
				FI->READ=YK_START_ADDR2;
				FI->LENS+=FI->INFONUM*YK_INFO_LEN;
			}
			else
			{
				FI->INFONUM=READ_YK_NUM-FI->INFONUM;

				FI->READ=YK_START_ADDR1+(((YK_FLASH_LEN/YK_INFO_LEN)-FI->INFONUM)*YK_INFO_LEN);

				FI->INFONUM=READ_YK_NUM;
				FI->LENS+=READ_YK_NUM*YK_INFO_LEN;
			}
		}
	}

	Mx25_Read_U8_Array(FI->READ,YK.DATA,YK_INFO_LEN,false);
	memcpy(FI->TIME,YK.TIME,7);

	if(FI->INFONUM==0)
		FI->LENS=0;
	else
	{
		if((FI->LENS%ECP_DATA_SEND_LEN)==0)
			FI->SENDNUM=FI->LENS/ECP_DATA_SEND_LEN;
		else
			FI->SENDNUM=(FI->LENS/ECP_DATA_SEND_LEN)+1;

		FI->LENS+=YK_INFO_HEAD+1;
	}

	return true;
}
/************************************************************!
*Function:
*Description:
*Input: null
*Output: null
*Return:
*************************************************************/
void Locate_Wave_FileInfo(FILEINFO *FI)
{
	FOURBYTE FB;
	DOUBLEBYTE DB;

	uint8_t sn,block11,block12,block21,block22;

	FI->INFONUM=0;
	FI->MSGADDR.U16=0x680A;

	if(((gSYSFLAG.MFW.WAVE-WAVE_START_ADDR1)/WAVE_FLASH_LEN)==0) //дָ���ڿ�1
	{
		sn=((gSYSFLAG.MFW.WAVE-WAVE_START_ADDR1)/WAVE_FILE_LEN)+1;

		if(sn==64)
		{
			FI->READ=WAVE_START_ADDR1+(FI->ID-52)*WAVE_FILE_LEN;
		}
		else
		{
			block11=115-sn+1;
			block12=115;
			block21=52;
			block22=115-sn;

			if(FI->ID>=block11&&FI->ID<=block12)
			{
				FI->READ=WAVE_START_ADDR1+(FI->ID-block11)*WAVE_FILE_LEN;
			}

			if(FI->ID>=block21&&FI->ID<=block22)
			{
				FI->READ=WAVE_START_ADDR2+(FI->ID-52+sn)*WAVE_FILE_LEN;
			}
		}
	}

	if(((gSYSFLAG.MFW.WAVE-WAVE_START_ADDR1)/WAVE_FLASH_LEN)==1) //дָ���ڿ�2
	{
		sn=((gSYSFLAG.MFW.WAVE-WAVE_START_ADDR2)/WAVE_FILE_LEN)+1;

		if(sn==64)
		{
			FI->READ=WAVE_START_ADDR2+(FI->ID-52)*WAVE_FILE_LEN;
		}
		else
		{
			block11=115-sn+1;
			block12=115;
			block21=52;
			block22=115-sn;

			if(FI->ID>=block11&&FI->ID<=block12)
			{
				FI->READ=WAVE_START_ADDR2+(FI->ID-block11)*WAVE_FILE_LEN;
			}

			if(FI->ID>=block21&&FI->ID<=block22)
			{
				FI->READ=WAVE_START_ADDR1+(FI->ID-52+sn)*WAVE_FILE_LEN;
			}
		}
	}

	Mx25_Read_U8_Array(FI->READ,DB.U8,2,false);

	if(DB.U16==0xFFFF)
	{
		FI->LENS=0;
		FI->INFONUM=0;
		memset(FI->TIME,0,7);
	}
	else
	{
		for(uint32_t i=0;i<MAX_WAVE_LEN;i++)
		{
			Mx25_Read_U8_Array(FI->READ+9+DB.U16+i*WAVE_INFO_LEN,FB.U8,4,false);

			if(FB.U32==0xFFFFFFFF)
				break;

			FI->INFONUM++;
		}

		FI->LENS=DB.U16+FI->INFONUM*WAVE_INFO_LEN+1;

		Mx25_Read_U8_Array(FI->READ+2,FI->TIME,7,false);

		if((FI->LENS-DB.U16)%ECP_DATA_SEND_LEN==0)
			FI->SENDNUM=(FI->LENS-DB.U16)/ECP_DATA_SEND_LEN;
		else
			FI->SENDNUM=((FI->LENS-DB.U16)/ECP_DATA_SEND_LEN)+1;
	}
}
/************************************************************!
*Function:
*Description:
*Input: null
*Output: null
*Return:
*************************************************************/
void Get_Log_Data(uint32_t read,uint8_t *data,uint32_t lens)
{
	if(((read-LOG_START_ADDR1)/LOG_FLASH_LEN)==0) //��1
	{
		if((LOG_START_ADDR1+LOG_FLASH_LEN-read)<LOG_INFO_LEN)
			read=LOG_START_ADDR2;
	}

	if(((read-LOG_START_ADDR1)/LOG_FLASH_LEN)==1)
	{
		if((LOG_START_ADDR2+LOG_FLASH_LEN-read)<LOG_INFO_LEN)
			read=LOG_START_ADDR1;
	}

	Mx25_Read_U8_Array(read,data,lens,false);
}
/************************************************************!
*Function:
*Description:
*Input: null
*Output: null
*Return:
*************************************************************/
void Get_Soe_Data(uint32_t read,uint8_t *data,uint32_t lens)
{
	if(((read-SOE_START_ADDR1)/SOE_FLASH_LEN)==0) //��1
	{
		if((SOE_START_ADDR1+SOE_FLASH_LEN-read)<SOE_INFO_LEN)
			read=SOE_START_ADDR2;
	}

	if(((read-SOE_START_ADDR1)/SOE_FLASH_LEN)==1)
	{
		if((SOE_START_ADDR2+SOE_FLASH_LEN-read)<SOE_INFO_LEN)
			read=SOE_START_ADDR1;
	}

	Mx25_Read_U8_Array(read,data,lens,false);
}
/************************************************************!
*Function:
*Description:
*Input: null
*Output: null
*Return:
*************************************************************/
void Get_Yk_Data(uint32_t read,uint8_t *data,uint32_t lens)
{
	if(((read-YK_START_ADDR1)/YK_FLASH_LEN)==0) //��1
	{
		if((YK_START_ADDR1+YK_FLASH_LEN-read)<YK_INFO_LEN)
			read=YK_START_ADDR2;
	}

	if(((read-YK_START_ADDR1)/YK_FLASH_LEN)==1)
	{
		if((YK_START_ADDR2+YK_FLASH_LEN-read)<YK_INFO_LEN)
			read=YK_START_ADDR1;
	}

	Mx25_Read_U8_Array(read,data,lens,false);
}
/************************************************************!
*Function:
*Description:
*Input: null
*Output: null
*Return:
*************************************************************/
void Get_Yc_Data(uint32_t read,uint8_t *data,uint32_t lens)
{
	Mx25_Read_U8_Array(read,data,lens,false);
}
/************************************************************!
*Function:
*Description:
*Input:
*Output: null
*Return:
*************************************************************/
void Get_Fault_Data(uint32_t read,uint8_t *data,uint32_t lens)
{
	Mx25_Read_U8_Array(read,data,lens,false);
}
/************************************************************!
*Function:
*Description:
*Input:
*Output: null
*Return:
*************************************************************/
void Get_Wave_Data(uint32_t read,uint8_t *data,uint32_t lens)
{
	Mx25_Read_U8_Array(read,data,lens,false);
}
/************************************************************!
*Function:
*Description:
*Input: null
*Output: null
*Return: null
*************************************************************/
void Mx25_Data_Storage(uint32_t read,uint8_t *data,uint32_t lens)
{
	Mx25_Write_U8_Array(read,data,lens,false);
}
/************************************************************!
*Function:
*Description:
*Input:
*Output: null
*Return:
*************************************************************/
uint8_t Get_U32_Hex(uint32_t u32,uint8_t *data,uint8_t lens)
{
	FOURBYTE FB;

	if(lens!=11)  //��ʱ��������
		while(1);

	FB.U32=u32;

	for(uint8_t i=0;i<4;i++)
	{
		if(FB.U4[i].U03>9)
			data[9-3*i]=FB.U4[i].U03+0x37;
		else
			data[9-3*i]=FB.U4[i].U03+0x30;

		if(FB.U4[i].U47>9)
			data[10-3*i]=FB.U4[i].U47+0x37;
		else
			data[10-3*i]=FB.U4[i].U47+0x30;

		if(i!=0)
			data[3*i-1]=0x20;
	}

	return 0x0B;
}
/************************************************************!
*Function:
*Description:
*Input:
*Output: null
*Return:
*************************************************************/
uint8_t Get_U32_Dec(uint32_t u32,uint8_t *data,uint8_t lens)
{
	uint32_t U32=u32;

	if(lens!=10)  //��ʱ��������
		while(1);

	memset(data,0,10*sizeof(uint8_t));

	for(uint8_t i=10;i>0;i--)
	{
		data[i-1]=(U32%10)+0x30;
		U32/=10;
	}

	for(uint8_t i=0;i<10;i++)
	{
		if(data[i]!=0x30)
			return i;

		if(i==9)
			return i;
	}

	return 0;
}
/************************************************************!
*Function:
*Description:
*Input:
*Output: null
*Return:
*************************************************************/
uint8_t Get_U32_Time(uint32_t u32,uint8_t *data,uint8_t lens)
{
	FOURBYTE FB;

	FB.U32=u32;

	for(uint8_t i=0;i<3;i++)
	{
		FB.U4[3].DATA=FB.U4[i].DATA;
		FB.U4[i].DATA=((FB.U4[3].DATA/10)<<4)+(FB.U4[3].DATA%10);
	}

	data[0]=FB.U4[2].U47+0x30;
	data[1]=FB.U4[2].U03+0x30;
	data[2]=0x2D;
	data[3]=FB.U4[1].U47+0x30;
	data[4]=FB.U4[1].U03+0x30;
	data[5]=0x2D;
	data[6]=FB.U4[0].U47+0x30;
	data[7]=FB.U4[0].U03+0x30;

	return 0x08;
}
/************************************************************!
*Function:
*Description:
*Input:
*Output: null
*Return:
*************************************************************/
uint8_t Get_P101_Time(uint8_t *time,uint8_t *data)
{
	uint8_t timestr[8];
	DOUBLEBYTE DB;

	memcpy(timestr+1,time,7);

	memcpy(DB.U8,timestr+1,2*sizeof(uint8_t));

	timestr[5]&=0x1F;           //���ε�����
	timestr[2]=DB.U16/1000;    //��
	DB.U16%=1000;
	timestr[1]=DB.U16/100;     //�����λ
	timestr[0]=DB.U16%100;     //�����λ

	for(uint8_t i=0;i<8;i++)
		timestr[i]=Byte2Bcd(timestr[i]);

	DB.U4[0].DATA=timestr[7];   //��
	data[0]=DB.U4[0].U47+0x30;
	data[1]=DB.U4[0].U03+0x30;
	data[2]=0x2D;
	DB.U4[0].DATA=timestr[6];
	data[3]=DB.U4[0].U47+0x30;
	data[4]=DB.U4[0].U03+0x30;
	data[5]=0x2D;
	DB.U4[0].DATA=timestr[5];
	data[6]=DB.U4[0].U47+0x30;
	data[7]=DB.U4[0].U03+0x30;
	data[8]=0x20;
	DB.U4[0].DATA=timestr[4];
	data[9]=DB.U4[0].U47+0x30;
	data[10]=DB.U4[0].U03+0x30;
	data[11]=0x3A;
	DB.U4[0].DATA=timestr[3];
	data[12]=DB.U4[0].U47+0x30;
	data[13]=DB.U4[0].U03+0x30;
	data[14]=0x3A;
	DB.U4[0].DATA=timestr[2];
	data[15]=DB.U4[0].U47+0x30;
	data[16]=DB.U4[0].U03+0x30;
	data[17]=0x2E;
	DB.U4[0].DATA=timestr[1];
	data[18]=DB.U4[0].U03+0x30;
	DB.U4[0].DATA=timestr[0];
	data[19]=DB.U4[0].U47+0x30;
	data[20]=DB.U4[0].U03+0x30;

	return 21;
}
/************************************************************!
*Function:
*Description:
*Input:
*Output: null
*Return:
*************************************************************/
void Print_Sys_Para(void)
{
	#ifdef PRINT_SYS_INIT_DEBUG

	DEBUG_PRINT("KKNSSK","<-------------------- �㼯��Ԫϵͳ��ǰ�汾��: ",SYS_VERSION);
	DEBUG_PRINT("KKNSK","<-------------------- �㼯��Ԫϵͳ��������������:");
	DEBUG_PRINT("KSDSK","<----- ��ǰ�㼯��Ԫ���� ",gSYSPARA.LINEGROUP.LINENUM," ��ɼ���Ԫ��:");

	for(uint8_t line=0;line<LINEGROUP_MAXNUM;line++)  //���²ɼ���Ԫ����Ŀ
	{
		if(gSYSPARA.LINEGROUP.LINE[line].LINENO==0||gSYSPARA.LINEGROUP.LINE[line].LINENO==0xFF)
			continue;

		DEBUG_PRINT("KSDSK","�� ",gSYSPARA.LINEGROUP.LINE[line].LINENO," �ɼ���Ԫ��ɼ���Ԫ��ַ:");

		for(uint8_t phase=0;phase<3;phase++)
				DEBUG_PRINT_U8CHAR_ARRAY(gSYSPARA.LINEGROUP.LINE[line].AU[phase].ADDR,6);
	}

	DEBUG_PRINT("KS","<----- �㼯��Ԫ������ַ:  ");
	DEBUG_PRINT_U8CHAR_ARRAY(gSYSPARA.BENJI,6);
	DEBUG_PRINT("KS","<----- �㼯��Ԫά����ַ:  ");
	DEBUG_PRINT_U8CHAR_ARRAY(gSYSPARA.WEIHU,6);
	DEBUG_PRINT("KS","<----- �㼯��Ԫ�㲥��ַ:  ");
	DEBUG_PRINT_U8CHAR_ARRAY(gSYSPARA.BROADCAST,6);

	DEBUG_PRINT("KSHK","<----- ��վ��ַ: ",gECPPARA.ZIZHAN.U16);
	DEBUG_PRINT("KSDK","<----- ��Ƶ�ŵ�: ",gECPPARA.RADIO_CHANNEL);

	DEBUG_PRINT("KS","<----- ң���ϱ�ģʽ: ");
	if(gECPPARA.YC_REPORT_MODE==0)
		DEBUG_PRINT("SK","ң��ͻ���ϱ�");
	if(gECPPARA.YC_REPORT_MODE==1)
		DEBUG_PRINT("SK","ң�������ϱ�");
	DEBUG_PRINT("KS","<----- ϵͳУʱģʽ: ");
	if(gECPPARA.GPS_TIMING_MODE==0)
		DEBUG_PRINT("SKKK","ECP��ԼУʱ");
	if(gECPPARA.GPS_TIMING_MODE==1)
		DEBUG_PRINT("SKKK","GPS����Уʱ");

	#endif
}


















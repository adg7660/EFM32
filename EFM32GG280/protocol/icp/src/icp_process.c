/******************************************************************!
*Copyright (c), 2008-2017, Qingdao Topscomm Communication Co .Ltd.
*File name: icp_process.c
*Version: 0.1.0
*Date: 2016-09-20
*Author: WANGJIANHUI
*Description:
*******************************************************************/
#include "include.h"


/************************************************************!
*Function: Icp_Process
*Description:
*Input:
*Output: null
*Return: null
*************************************************************/
bool Icp_Process(ICPFRAME *IF)
{
	if(IF->ISLOCK==false) //δ���һ������������֡���򲻽�������֡�Ĵ���
		return false;

	IF->ISLOCK=false; //�������֡������������һ֡

	gSYSFLAG.CWS.ICPRUNCOUNT++;

	if(Is_Valid_Icp_Address(IF)==false) //�ж�Դ��ַ��Ŀ�ĵ�ַ�Ƿ�Ϸ�
		return false;

	switch(IF->CTRL.PRM) //�ж������߹�ϵ
	{
		case PRMSEC: //�Ӷ���
			Icp_Prmsec_Process(IF);
			break;

		case PRMPRI: //������
			Icp_Prmpri_Process(IF);
			break;

		default:
			break;
	}

	return true;
}
/************************************************************!
*Function: Icp_Prmsec_Process
*Description:
*Input:
*Output: null
*Return: null
*************************************************************/
void Icp_Prmsec_Process(ICPFRAME *IF) //�Ӷ���
{
	switch(IF->CTRL.CC)
	{
		case FCCON: //ȷ��,�϶�ȷ��
			Icp_Fccon_Process(IF);
			break;

		case FCNOCON: //ȷ��,��ȷ��
			Icp_Fcnocon_Process(IF);
			break;

		case FCRESDATA: //��Ӧ֡,����
			Icp_Fcresdata_Process(IF);
			break;

		case FCNODATA: //��Ӧ֡,���Ͽɣ�������
			Icp_Fcnodata_Process(IF);
			break;

		default:
			break;
	}
}
/************************************************************!
*Function: Icp_Prmpri_Process
*Description:
*Input:
*Output: null
*Return: null
*************************************************************/
void Icp_Prmpri_Process(ICPFRAME *IF) //������
{
	switch(IF->CTRL.CC)
	{
		case FCRESETUSE: //����/��Ӧ��
			Icp_Fcresetuse_Process(IF);
			break;

		case FCSENDDATA: //����/ȷ��
			Icp_Fcsenddata_Process(IF);
			break;

		case FCREQUESTD: //����/��Ӧ
			Icp_Fcrequestd_Process(IF);
			break;

		default:
			break;
	}
}
/************************************************************!
*Function: Icp_Fccon_Process
*Description:
*Input:
*Output: null
*Return: null
*************************************************************/
void Icp_Fccon_Process(ICPFRAME *IF)
{
	Icp_PduType_Process(IF); //��������
}
/************************************************************!
*Function: Icp_Fcnocon_Process
*Description:
*Input:
*Output: null
*Return: null
*************************************************************/
void Icp_Fcnocon_Process(ICPFRAME *IF)
{
	//�˺�����ʱδ�õ�
}
/************************************************************!
*Function: Icp_Fcresdata_Process
*Description:
*Input:
*Output: null
*Return: null
*************************************************************/
void Icp_Fcresdata_Process(ICPFRAME *IF)
{
	Icp_PduType_Process(IF); //��������
}
/************************************************************!
*Function: Icp_Fcnodata_Process
*Description:
*Input:
*Output: null
*Return: null
*************************************************************/
void Icp_Fcnodata_Process(ICPFRAME *IF)
{
	//�˺�����ʱδ�õ�
}
/************************************************************!
*Function: Icp_Fcresetuse_Process
*Description:
*Input:
*Output: null
*Return: null
*************************************************************/
void Icp_Fcresetuse_Process(ICPFRAME *IF)
{
	Icp_PduType_Process(IF); //��������
}
/************************************************************!
*Function: Icp_Fcsenddata_Process
*Description:
*Input:
*Output: null
*Return: null
*************************************************************/
void Icp_Fcsenddata_Process(ICPFRAME *IF)
{
	Icp_PduType_Process(IF);
}
/************************************************************!
*Function: Icp_Fcrequestd_Process
*Description:
*Input:
*Output: null
*Return: null
*************************************************************/
void Icp_Fcrequestd_Process(ICPFRAME *IF)
{
	Icp_PduType_Process(IF); //��������
}
/************************************************************!
*Function: Fill_Icp_Frame
*Description:
*Input:
*Output: null
*Return: null
*************************************************************/
void Fill_Icp_Frame(uint8_t channel,uint8_t *addr,uint8_t ctrl,uint8_t type,uint8_t num,uint8_t seq,uint8_t *data,uint8_t lens)
{
	uint8_t sn=0xFF;

	while(sn==0xFF)
	{
		sn=Get_Empty_IcpFrame();

		if(sn!=0xFF)
			break;

		taskYIELD();
	}

	gICPFRAMELIST[sn].FRAME[0]=ICP_STARTBYTE;
	gICPFRAMELIST[sn].FRAME[1]=ICP_MINPDULEN+lens;
	gICPFRAMELIST[sn].FRAME[2]=ICP_MINPDULEN+lens;
	gICPFRAMELIST[sn].FRAME[3]=ICP_STARTBYTE;
	gICPFRAMELIST[sn].FRAME[4]=ctrl;

	memcpy(gICPFRAMELIST[sn].FRAME+5,gSYSPARA.BENJI,ICP_ADDRLEN);
	memcpy(gICPFRAMELIST[sn].FRAME+11,addr,ICP_ADDRLEN);

	gICPFRAMELIST[sn].FRAME[17]=type;
	gICPFRAMELIST[sn].FRAME[18]=num;
	gICPFRAMELIST[sn].FRAME[19]=seq;

	if(lens!=0)
		memcpy(gICPFRAMELIST[sn].FRAME+20,data,lens);

	gICPFRAMELIST[sn].FRAME[ICP_FRAMEHEAD+ICP_MINPDULEN+lens]=Check_Icp_Cs(gICPFRAMELIST[sn].FRAME+ICP_FRAMEHEAD,ICP_MINPDULEN+lens);
	gICPFRAMELIST[sn].FRAME[ICP_FRAMEHEAD+ICP_MINPDULEN+lens+1]=ICP_ENDBYTE;

	if(channel==RADIO_CHANNEL)
		gICPFRAMELIST[sn].ISLOCK=true;

	if(channel==WEIHU_CHANNEL)
	{
		taskENTER_CRITICAL();

		WriteDataCache(&WEIHU_TXDC,gICPFRAMELIST[sn].FRAME,ICP_MINFRAMELEN+lens);//д��MID���ȴ�����
		gICPFRAMELIST[sn].STATUS=false;

		taskEXIT_CRITICAL();
	}
}
/************************************************************!
*Function: Get_Empty_IcpFrame
*Description:
*Input:
*Output: null
*Return: null
*************************************************************/
uint8_t Get_Empty_IcpFrame(void)
{
	for(uint8_t i=2;i<MAX_ICPFRAME_NUM;i++)
	{
		if(gICPFRAMELIST[i].STATUS==true)
			continue;

		gICPFRAMELIST[i].STATUS=true;

		return i;
	}

	return 0xFF;
}
/************************************************************!
*Function: Is_Valid_Icp_Address
*Description:
*Input:
*Output: null
*Return: null
*************************************************************/
bool Is_Valid_Icp_Address(ICPFRAME *IF)
{
	IF->LINE=0xFF;
	IF->PHASE=0xFF; //�˴������жϲɼ���Ԫ�Ƿ�����

	if(!(memcmp(gSYSPARA.BROADCAST,IF->DSTADDR,ICP_ADDRLEN)==0||memcmp(gSYSPARA.BENJI,IF->DSTADDR,ICP_ADDRLEN)==0))
		return false;  //ȷ��Ŀ�ĵ�ַ�Ƿ�Ϊ������ַ���߹㲥��ַ

	for(uint8_t line=0;line<LINEGROUP_MAXNUM;line++)//�ж�Դ��ַ�Ƿ�Ϊ�ɼ���Ԫ��ַ
	{
		if(gSYSPARA.LINEGROUP.LINE[line].LINENO==0) //�ж��ߺŲ�Ϊ0,ȷ�ϸ��ߺ�Ϊ��Ч�Ĳɼ���Ԫ��
			continue;

		for(uint8_t phase=0;phase<3;phase++)
		{
			if(memcmp(gSYSPARA.LINEGROUP.LINE[line].AU[phase].ADDR,IF->SRCADDR,ICP_ADDRLEN)!=0)
				continue;

			IF->LINE=line;
			IF->PHASE=phase;

			return true;
		}
	}

	if(memcmp(gSYSPARA.WEIHU,IF->SRCADDR,ICP_ADDRLEN)==0) //�ж�Դ��ַ�Ƿ�Ϊά����ַ
		return true;

	return false;
}


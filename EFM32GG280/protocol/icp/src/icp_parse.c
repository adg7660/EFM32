/******************************************************************!
*Copyright (c), 2008-2017, Qingdao Topscomm Communication Co .Ltd.
*File name: icp_parse.c
*Version: 0.1.0
*Date: 2016-09-20
*Author: WANGJIANHUI
*Description:
*******************************************************************/
#include "include.h"


/************************************************************!
*Function: Icp_Parse
*Description:
*Input:
*Output: null
*Return: ��������״̬
*************************************************************/
//bool Icp_Parse(DATACACHE *DC,ICPFRAME *IF)
//{
//	if(IF->ISLOCK==true) //������һ֡,���Ҵ�֡��δ������,�򲻻������һ֡����
//		return false;
//
//	while(DataCacheLength(DC)>0)
//	{
//		if(IF->PARSE==false) //��δ��ʼ��������֡
//		{
//			if(DataCacheLength(DC)<ICP_FRAMEHEAD) //�ȴ����н���������֡ͷ
//				return false;
//
//			ReadDataCache(DC,IF->FRAME,1); //��ȡ���еĵ�һ���ֽ�
//
//			if(IF->STARTBYTE1!=ICP_STARTBYTE)
//				continue;
//
//			VirtualReadDataCache(DC,DC->READ,IF->FRAME+1,ICP_FRAMEHEAD-1);//�����ȡ����֡ͷ
//
//			if(!((IF->STARTBYTE1==IF->STARTBYTE2)&&(IF->LEN1==IF->LEN2)))
//			{
//				DEBUG_PRINT_NISR("KKNSKK","<----- ��ǰ����֡֡ͷ����!");
//				continue;
//			}
//
//			if(!((IF->LEN1>=ICP_MINPDULEN)&&(IF->LEN1<=ICP_MAXPDULEN))) //�жϳ������Ƿ���ȷ
//				continue;
//
//			IF->PARSE=true; //�ҵ�����֡ͷ,��ʼ��������
//		}
//
//		if(DataCacheLength(DC)<(IF->LEN1+ICP_FRAMETAIL)) //�ȴ���֡���ݽ�����
//			return false;
//
//		IF->PARSE=false;
//
//		VirtualReadDataCache(DC,DC->READ+ICP_FRAMEHEAD-1,IF->FRAME+ICP_FRAMEHEAD,IF->LEN1); //��ȡ������
//		VirtualReadDataCache(DC,DC->READ+ICP_FRAMEHEAD-1+IF->LEN1,IF->FRAME+ICP_FRAMEHEAD+ICP_MAXPDULEN,ICP_FRAMETAIL); //��ȡУ����ͽ�����
//
//		#ifdef PRINT_ICP_FRAME_PARSE_DEBUG
//		//PRINT_ICP_RECEIVE_FRAME_DEBUG(IF);
//		#endif
//
//		if(IF->ENDBYTE!=ICP_ENDBYTE)
//		{
//			#ifdef PRINT_ICP_FRAME_PARSE_DEBUG
//			DEBUG_PRINT_NISR("KKNSDKK","<----- ��ǰ����֡֡�����ַ�����!����Ľ�����  ",IF->ENDBYTE);
//			#endif
//
//			continue;
//		}
//
//		if(IF->CS!=Check_Icp_Cs(IF->FRAME+ICP_FRAMEHEAD,IF->LEN1))
//		{
//			#ifdef PRINT_ICP_FRAME_PARSE_DEBUG
//			DEBUG_PRINT_NISR("KKNSDKK","<----- ��ǰ����֡֡CS����!�����CS ",IF->CS);
//			#endif
//
//			continue;
//		}
//
//		ReadDataCache(DC,IF->FRAME+1,ICP_FRAMEHEAD-1+IF->LEN1); //��ȡ������
//		ReadDataCache(DC,IF->FRAME+ICP_FRAMEHEAD+ICP_MAXPDULEN,ICP_FRAMETAIL); //��ȡУ����ͽ�����
//
//		IF->ISLOCK=true; //����֡�������,����֡����
//
//		return true;
//	}
//
//	return false;
//}
bool Icp_Parse(DATACACHE *DC,ICPFRAME *IF)
{
	if(IF->ISLOCK==true) //������һ֡,���Ҵ�֡��δ������,�򲻻������һ֡����
		return false;

	while(DataCacheLength(DC)>0)
	{
		if(IF->PARSE==false) //��δ��ʼ��������֡
		{
			if(DataCacheLength(DC)<ICP_FRAMEHEAD) //�ȴ����н���������֡ͷ
				return false;

			ReadDataCache(DC,IF->FRAME,1); //��ȡ���еĵ�һ���ֽ�

			if(IF->STARTBYTE1!=ICP_STARTBYTE)
				continue;

			VirtualReadDataCache(DC,DC->READ,IF->FRAME+1,ICP_FRAMEHEAD-1);//�����ȡ����֡ͷ

			if(!((IF->STARTBYTE1==IF->STARTBYTE2)&&(IF->LEN1==IF->LEN2)))
				continue;

			if(!((IF->LEN1>=ICP_MINPDULEN)&&(IF->LEN1<=ICP_MAXPDULEN))) //�жϳ������Ƿ���ȷ
				continue;

			IF->PARSE=true; //�ҵ�����֡ͷ,��ʼ��������
			ReadDataCache(DC,IF->FRAME+1,ICP_FRAMEHEAD-1); //��ȡ����֡ͷ
		}

		if(DataCacheLength(DC)<(IF->LEN1+ICP_FRAMETAIL)) //�ȴ���֡���ݽ�����
			return false;

		IF->PARSE=false;

		ReadDataCache(DC,IF->FRAME+ICP_FRAMEHEAD,IF->LEN1); //��ȡ������
		ReadDataCache(DC,IF->FRAME+ICP_FRAMEHEAD+ICP_MAXPDULEN,ICP_FRAMETAIL); //��ȡУ����ͽ�����

		if(IF->ENDBYTE!=ICP_ENDBYTE)
			continue;

		if(IF->CS!=Check_Icp_Cs(IF->FRAME+ICP_FRAMEHEAD,IF->LEN1))
			continue;

		IF->ISLOCK=true; //����֡�������,����֡����

		return true;
	}

	return false;
}
/************************************************************!
*Function: Check_Icp_Cs
*Description:
*Output: null
*Return:
*************************************************************/
uint8_t Check_Icp_Cs(uint8_t *data,uint32_t lens)
{
	uint8_t cs=0;

	for(uint32_t i=0;i<lens;i++)
		cs+=data[i];

	return cs;
}
/************************************************************!
*Function:
*Description:
*Output: null
*Return:
*************************************************************/
void PRINT_ICP_RECEIVE_FRAME_DEBUG(ICPFRAME *IF)
{
	DEBUG_PRINT_NISR("KKNSK","<----- �ѽ���ICP����֡����:");
	DEBUG_PRINT_U8CHAR_ARRAY_NISR(IF->FRAME,ICP_FRAMEHEAD+IF->LEN1);
	DEBUG_PRINT_U8CHAR_ARRAY_NISR(IF->FRAME+ICP_FRAMEHEAD+ICP_MAXPDULEN,ICP_FRAMETAIL);

	DEBUG_PRINT_NISR("KK");
}



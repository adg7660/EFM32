/******************************************************************!
*Copyright (c), 2008-2017, Qingdao Topscomm Communication Co .Ltd.
*File name: datacache.c
*Version: 0.2.0
*Date: 2016-11-12
*Author: WANGJIANHUI
*Description:
*******************************************************************/
#include "datacache.h"


/************************************************************!
*Function: CreateDataCache
*Description: �������ݻ���
*Input: 1.DC: ���ݻ�����
*       2.length: ���ݻ��泤��
*Output: null
*Return: ��������״̬
*************************************************************/
bool CreateDataCache(DATACACHE *DC,uint32_t length)
{
	DC->READ=0;
	DC->WRITE=0;
	DC->LENGTH=length;

	DC->CACHE=(uint8_t *)malloc(DC->LENGTH*sizeof(uint8_t));

	if(DC->CACHE==NULL) //��ʱ����,������ֲ��Ҫע��
		while(1);

	memset(DC->CACHE,0,DC->LENGTH*sizeof(uint8_t));

	return true;
}
/************************************************************!
*Function: ReadDataCache
*Description: ��ȡ���ݻ�������
*Input: 1.DC: ���ݻ�����
*       2.data: �����׵�ַ
*       3.lens: ���鳤��.����ȡ�����ݳ��ȴ������ݻ����е�δ��
*               ȡ�����ݵĳ���,��δ���������ݸ�0.
*Output: null
*Return: ��������״̬
*************************************************************/
void ReadDataCache(DATACACHE *DC,uint8_t *data,uint32_t lens)
{
	for(uint32_t i=0;i<lens;i++)
	{
		if(((DC->LENGTH+DC->WRITE-DC->READ)%DC->LENGTH)>0)
		{
			data[i]=DC->CACHE[DC->READ++];

			DC->READ%=DC->LENGTH;

			continue;
		}

		data[i]=0;
	}
}
/************************************************************!
*Function: VirtualReadDataCache
*Description: �����ȡ���ݻ�������(����ı����ݻ���Ķ�ָ��)
*Input: 1.DC: ���ݻ�����
*       2.loc: Ҫ��ȡ�����ݵ���ʼλ��
*       3.data: �����׵�ַ
*       4.lens: ���鳤��.����ȡ�����ݳ��ȴ������ݻ�����
*               �����ݳ���,��δ����������λ��0,
*Output: null
*Return: ��������״̬
*************************************************************/
void VirtualReadDataCache(DATACACHE *DC,uint32_t loc,uint8_t *data,uint32_t lens)
{
	uint32_t newloc=loc;

	for(uint32_t i=0;i<lens;i++)
	{
		if(((DC->LENGTH+DC->WRITE-newloc)%DC->LENGTH)>0)
		{
			data[i]=DC->CACHE[newloc++];

			newloc%=DC->LENGTH;

			continue;
		}

		data[i]=0;
	}
}
//void VirtualReadDataCache(DATACACHE *DC,uint32_t loc,uint8_t *data,uint32_t lens)
//{
//	uint32_t newloc=loc;
//
//	for(uint32_t i=0;i<lens;i++)
//	{
//		newloc%=DC->LENGTH;
//
//		if(((DC->LENGTH+DC->WRITE-newloc)%DC->LENGTH)>0)
//		{
//			data[i]=DC->CACHE[newloc++];
//
//			continue;
//		}
//
//		data[i]=0;
//	}
//}
/************************************************************!
*Function: WriteDataCache
*Description: д�����ݻ�������
*Input: 1.DC: ���ݻ�����
*       2.data: �����׵�ַ
*       3.lens: ���鳤��
*Output: null
*Return: ��������״̬
*************************************************************/
bool WriteDataCache(DATACACHE *DC,uint8_t *data,uint32_t lens)
{
	if((DataCacheLength(DC)+lens)>=DC->LENGTH)
		return false;

	for(uint32_t i=0;i<lens;i++)
	{
		DC->CACHE[DC->WRITE++]=data[i];

		DC->WRITE%=DC->LENGTH;
	}

	return true;
}
//bool WriteDataCache(DATACACHE *DC,uint8_t *data,uint32_t lens)
//{
//	for(uint32_t i=0;i<lens;i++)
//	{
//		DC->WRITE=(DC->WRITE+1)%DC->LENGTH;
//
//		DC->CACHE[DC->WRITE]=data[i];
//
//		DC->READ=(DC->WRITE>=DC->READ)?(DC->WRITE+1):DC->READ; //+1:��ֹDataCacheLength����
//	}
//
//	return true;
//}
/************************************************************!
*Function: DataCacheLength
*Description: �õ����ݻ�����δ��ȡ�����ݵĳ���
*Input: DC: ���ݻ�����
*Output: null
*Return: ���ݻ�����δ��ȡ�����ݵĳ���
*************************************************************/
uint32_t DataCacheLength(DATACACHE *DC)
{
	return ((DC->LENGTH+DC->WRITE-DC->READ)%DC->LENGTH);
}
/************************************************************!
*Function: ClearDataCache
*Description: ������ݻ���
*Input: 1.DC: ���ݻ�����
*Output: null
*Return: null
*************************************************************/
void ClearDataCache(DATACACHE *DC)
{
	DC->READ=0;
	DC->WRITE=0;

	memset(DC->CACHE,0,DC->LENGTH*sizeof(uint8_t)); //��ն���
}
/************************************************************!
*Function: FreeDataCache
*Description: �ͷ����ݻ���
*Input: DC: ���ݻ�����
*Output: null
*Return: null
*************************************************************/
void FreeDataCache(DATACACHE *DC)
{
	DC->READ=0;
	DC->WRITE=0;
	DC->LENGTH=0;

	if(DC->CACHE!=NULL)
		free(DC->CACHE);
}


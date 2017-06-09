/******************************************************************!
*Copyright (c), 2008-2017, Qingdao Topscomm Communication Co .Ltd.
*File name: hal_msc.c
*Version: 0.1.0
*Date: 2016-09-20
*Author: WANGJIANHUI
*Description:
*******************************************************************/
#include "hal_msc.h"


/************************************************************!
*Function: Msc_Init
*Description: MSC��ʼ������
*Input: null
*Output: null
*Return: null
*************************************************************/
void Msc_Init(void)
{
	MSC_Init();
}
/************************************************************!
*Function: Msc_ReadWord
*Description: MSC���ֺ���,��RAM����,��ַ����Ϊ4�ı���,�������ַ��
*Input: null
*Output: null
*Return: null
*************************************************************/
MSC_RAMFUNC_DEFINITION_BEGIN
uint32_t Msc_ReadWord(uint32_t addr)
{
	uint32_t data;

	data = *((uint32_t *)addr);

	return data;
}
MSC_RAMFUNC_DEFINITION_END
/************************************************************!
*Function: Msc_WriteWord
*Description: MSCд�ֺ���,��RAM����,��ַ����Ϊ4�ı���,�������ַд
*Input: null
*Output: null
*Return: null
*************************************************************/
MSC_RAMFUNC_DEFINITION_BEGIN
MSC_Status_TypeDef Msc_WriteWord(uint32_t addr,uint32_t data)
{
	MSC_WriteWordFast((uint32_t *)addr,&data,4);

	return mscReturnOk;
}
MSC_RAMFUNC_DEFINITION_END
/************************************************************!
*Function: Msc_ErasePage
*Description: MSC�����麯��
*Input: null
*Output: null
*Return: null
*************************************************************/
MSC_RAMFUNC_DEFINITION_BEGIN
MSC_Status_TypeDef Msc_ErasePage(uint32_t addr)
{
	uint32_t and=0xFFFFFFFF;

	for(uint32_t i=addr;i<(addr+4096);i++)
		and&=*((uint32_t *)i);

	if(and!=0xFFFFFFFF)
		MSC_ErasePage((uint32_t *)addr);

	return mscReturnOk;
}
MSC_RAMFUNC_DEFINITION_END


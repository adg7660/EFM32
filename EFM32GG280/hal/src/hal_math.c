/******************************************************************!
*Copyright (c), 2008-2017, Qingdao Topscomm Communication Co .Ltd.
*File name: hal_math.c
*Version: 0.1.0
*Date: 2016-09-20
*Author: WANGJIANHUI
*Description:
*******************************************************************/
#include "include.h"
#include "hal_math.h"


/************************************************************!
*Function: Bcd2Byte
*Description: BCD��ת��Ϊ�ֽ�
*Input: 1.bcd��BCD��
*Output: null
*Return: �ֽ�����
*************************************************************/
uint8_t Bcd2Byte(uint8_t bcd)
{
	uint8_t data;

	data=(uint8_t)((bcd/16)*10+(bcd%16));

	return data;
}
/************************************************************!
*Function: Byte2Bcd
*Description: �ֽ�ת��ΪBCD��
*Input: 1.byte���ֽ�����
*Output: null
*Return: BCD��
*************************************************************/
uint8_t Byte2Bcd(uint8_t byte)
{
    uint8_t data;

    data=(uint8_t)(((byte/10)<<4)+(byte%10));

    return data;
}
/************************************************************!
*Function: Is_Valid_BCD
*Description: �ж������Ƿ��ǺϷ���BCD��
*Input: 1.data��BCD�������׵�ַ
*       2.lens�����鳤��
*Output: null
*Return: BCD���Ƿ�Ϸ�
*************************************************************/
bool Is_Valid_BCD(uint8_t *data,uint8_t lens)
{
   for(uint8_t i=0;i<lens;i++)
   {
      if((data[i]&0x0F)>0x09)
    	  return false;

      if((data[i]&0xF0)>0x90)
    	  return false;
   }

   return true;
}
/************************************************************!
*Function: Char2Uint8_t
*Description: �������ַ�ת��Ϊһ��Uint8_t,ֻ�����ڽ�10���Ƶ�ʱ���ʽ
*             ת��ΪUint8_t��
*Input: data����Ҫת����Uint8_t���ַ����׵�ַ
*Output: null
*Return: uint8_t
*************************************************************/
uint8_t Char2Uint8_t(uint8_t *data)
{
	uint8_t result;

	result=Get_Hex(data[0])*10+Get_Hex(data[1]);

	return result;
}
/************************************************************!
*Function: Get_Hex
*Description: �õ��ַ���HEXֵ
*Input: data����Ҫת����HEXֵ���ַ�
*Output: null
*Return: HEXֵ
*************************************************************/
uint8_t Get_Hex(uint8_t data)
{
	if(data>='0'&&data<='9')
		data=data-'0';

	if(data>='A'&&data<='F')
		data=data-'0'-7; //�˴�Ϊɶ-7���뿴ASCII���,лл

	return data;
}
/************************************************************!
*Function: Get_Hex
*Description: �õ��ַ���HEXֵ
*Input: data����Ҫת����HEXֵ���ַ�
*Output: null
*Return: HEXֵ
*************************************************************/
uint16_t uint8u2uint16u(uint8_t *data)
{
	return (((uint16_t)data[1])<<8)+data[0];
}


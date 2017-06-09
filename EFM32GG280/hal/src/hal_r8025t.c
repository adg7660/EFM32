/******************************************************************!
*Copyright (c), 2008-2017, Qingdao Topscomm Communication Co .Ltd.
*File name: hal_r8025t.c
*Version: 0.1.0
*Date: 2016-09-20
*Author: WANGJIANHUI
*Description:
*******************************************************************/
#include "include.h"
#include "hal_math.h"
#include "hal_r8025t.h"


/************************************************************!
*Function: Rx8025t_Init
*Description:
*Input: null
*Output: null
*Return: null
*************************************************************/
bool Rx8025t_Init(void)
{
	uint8_t data[16];

	data[0]=0x00;
	data[1]=0x00;
	data[2]=0x40;

	Rx8025t_WriteByte(0x0D,data,3); //�˴�ǿ�ƽ�8025T��������ص�,������

	if(Check_R8025t_Data(data,16)==false)
	{
		R8025t_Reset();

		return false;
	}

	Check_R8025t_Data(data,16);

	if((data[0x0E]&0x02)||(Is_Valid_R8025t_Clock(data,7)==false)) //VLF��λ����ʱ�Ӹ�ʽ����
	{
		R8025t_Reset();

		return false;
	}

	return true;
}
/************************************************************!
*Function: R8025t_Reset
*Description: R8025Tʱ�Ӹ�λ
*Input: null
*Output: null
*Return: null
*************************************************************/
void R8025t_Reset(void)
{
	uint8_t time[7]={0x00,0x33,0x16,0x00,0x15,0x02,0x17}; //BCD��SB!
	Rx8025t_WriteByte(0,time,7);

	time[0]=0x00;
	time[1]=0x00;
	time[2]=0x40;

	Rx8025t_WriteByte(0x0D,time,3);
}
/************************************************************!
*Function: Get_R8025t_RtcTime
*Description:
*Input: null
*Output: null
*Return: null
*************************************************************/
bool Get_R8025t_RtcTime(uint8_t *data,uint8_t lens)
{
	uint8_t time[16];

	if(lens<6)
		return false;

	Rx8025t_ReadByte(0,time,16);

	if((time[0x0E]&0x02)||(Is_Valid_R8025t_Clock(time,7)==false))
	{
		UnixTime2LocalTime(gUNIXTIME.UNIX,time,6);

		Set_R8025t_RtcTime(time,6);

		return false;
	}

	data[0]=Bcd2Byte(time[0]); //HEX��ʽ
	data[1]=Bcd2Byte(time[1]);
	data[2]=Bcd2Byte(time[2]);
	data[3]=Bcd2Byte(time[4]);
	data[4]=Bcd2Byte(time[5]);
	data[5]=Bcd2Byte(time[6]);

//	data[0]=time[0]; //BCD��ʽ
//	data[1]=time[1];
//	data[2]=time[2];
//	data[3]=time[4];
//	data[4]=time[5];
//	data[5]=time[6];

	return true;
}
/************************************************************!
*Function: Set_R8025t_RtcTime
*Description:
*Input: null
*Output: null
*Return: null
*************************************************************/
bool Set_R8025t_RtcTime(uint8_t *data,uint8_t lens)
{
	uint8_t time[7];

	if(lens<6)
		return false;

	time[0]=Byte2Bcd(data[0]);
	time[1]=Byte2Bcd(data[1]);
	time[2]=Byte2Bcd(data[2]);
	time[3]=1;
	time[4]=Byte2Bcd(data[3]);
	time[5]=Byte2Bcd(data[4]);
	time[6]=Byte2Bcd(data[5]);

	Rx8025t_WriteByte(0,time,7);

	time[0]=0x00;
	time[1]=0x00;
	time[2]=0x60;

	Rx8025t_WriteByte(0x0D,time,3);

	return false;
}
/************************************************************!
*Function: Check_R8025t_Data
*Description:
*Input: null
*Output: null
*Return: null
*************************************************************/
bool Check_R8025t_Data(uint8_t *data,uint8_t lens)
{
	uint8_t cnt=15;
	uint8_t buff[32];

	while(cnt--)
	{
		Rx8025t_ReadByte(0,buff,32);

		if(memcmp(buff,buff+16,16)!=0) //�ظ���ȡ����
			continue;

		if(Is_Valid_R8025t_Clock(buff,7)==false)
			continue;

		memcpy(data,buff,16);

		return true;
	}

	return false;
}
/************************************************************!
*Function: Is_Valid_R8025t_Clock
*Description: ���ж�ʱ�Ӹ�ʽ�Ƿ��ǺϷ���BCD��,Ȼ���ж�ʱ�Ӹ�ʽ�Ƿ�
*             ����������Χ��
*Input: null
*Output: null
*Return: ʱ�Ӹ�ʽ�Ƿ�Ϸ�
*************************************************************/
bool Is_Valid_R8025t_Clock(uint8_t *data,uint8_t lens)
{
	uint8_t isleapyear;
	R8025TTIME RTCTIME;
	R8025T_SINGLEBYTE RSB;

	uint8_t DAY[2][13]={{0,31,28,31,30,31,30,31,31,30,31,30,31},
			            {0,31,29,31,30,31,30,31,31,30,31,30,31}};

	if(lens<7) //��ֹ����Խ��
		return false;

	for(uint8_t i=0;i<7;i++) //BCD��ʽ�ж�
	{
		if(i==3) //���������ж�
			continue;

		RSB.DATA=data[i];

		if(!(RSB.U03<=9&&RSB.U47<=9))
			return false;
	}

	RTCTIME.DATA[0]=Bcd2Byte(data[0]); //��BCDʱ��ת��ΪHEXʱ���ʽ
	RTCTIME.DATA[1]=Bcd2Byte(data[1]);
	RTCTIME.DATA[2]=Bcd2Byte(data[2]);
	RTCTIME.DATA[3]=Bcd2Byte(data[4]);
	RTCTIME.DATA[4]=Bcd2Byte(data[5]);
	RTCTIME.DATA[5]=Bcd2Byte(data[6]);

	if(RTCTIME.YEAR>99) //���ж�
		return false;

	if(RTCTIME.MONTH==0||RTCTIME.MONTH>12) //���ж�
		return false;

	isleapyear=((RTCTIME.YEAR%4)==0?1:0); //�����ж�

    if(RTCTIME.DAY>DAY[isleapyear][RTCTIME.MONTH]) //���ж�
    	return false;

    //if(Rx8025t_week2data(RTCTIME.WEEK)==0) //�����ж�
    	//return false;

	if(RTCTIME.HOUR>23) //Сʱ�ж�
		return false;

	if(RTCTIME.MINUTE>59) //�����ж�
		return false;

	if(RTCTIME.SECOND>59) //���ж�
		return false;

	return true;
}
/************************************************************!
*Function: Rx8025t_week2data
*Description: ��8025t������ת��Ϊ16������,16�������ڵķ�ΧΪ1-7.
*Input: week: 8025t������
*Output: null
*Return: 16���Ƶ�����,���󷵻�0
*************************************************************/
uint8_t Rx8025t_week2data(uint8_t week)
{
	if(week==1) //������
		return 7;

	if(week==2) //����һ
		return 1;

	if(week==4) //���ڶ�
		return 2;

	if(week==8) //������
		return 3;

	if(week==16) //������
		return 4;

	if(week==32) //������
		return 5;

	if(week==64) //������
		return 6;

	return 0;
}
/************************************************************!
*Function: Rx8025t_week2data
*Description: ����ΧΪ1-7��16��������ת��Ϊ8025t������.
*Input: week: 16��������
*Output: null
*Return: 8025t������,���󷵻�0
*************************************************************/
uint8_t Rx8025t_data2week(uint8_t data)
{
	if(data==7) //������
		return 1;

	if(data==1) //����һ
		return 2;

	if(data==2) //���ڶ�
		return 4;

	if(data==3) //������
		return 8;

	if(data==4) //������
		return 16;

	if(data==5) //������
		return 32;

	if(data==6) //������
		return 64;

	return 0;
}
/************************************************************!
*Function: Rx8025t_ReadByte
*Description:
*Input: null
*Output: null
*Return: null
*************************************************************/
uint8_t Rx8025t_ReadByte(uint8_t addr,uint8_t *data,uint8_t lens)
{
	uint8_t result;

	I2C_TransferSeq_TypeDef i2ctransfer;

	i2ctransfer.addr       =RX8025T_SLAVE_ADDR;
	i2ctransfer.flags      =I2C_FLAG_WRITE_READ;
	i2ctransfer.buf[0].data=&addr;
	i2ctransfer.buf[0].len =1;
	i2ctransfer.buf[1].data=data;
	i2ctransfer.buf[1].len =lens;

	I2C_TransferInit(I2C0,&i2ctransfer);

	while(I2C_Transfer(I2C0)==i2cTransferInProgress){;}

	result=(sizeof(data)/sizeof(uint8_t));  //?????????????????����

	return result;
}
/************************************************************!
*Function: Rx8025t_WriteByte
*Description:
*Input: null
*Output: null
*Return: null
*************************************************************/
void Rx8025t_WriteByte(uint8_t addr,uint8_t *data,uint8_t lens)
{
	I2C_TransferSeq_TypeDef i2ctransfer;

	i2ctransfer.addr       =RX8025T_SLAVE_ADDR;
	i2ctransfer.flags      =I2C_FLAG_WRITE_WRITE;
	i2ctransfer.buf[0].data=&addr;
	i2ctransfer.buf[0].len =1;
	i2ctransfer.buf[1].data=data;
	i2ctransfer.buf[1].len =lens;

	I2C_TransferInit(I2C0,&i2ctransfer);

	while(I2C_Transfer(I2C0)==i2cTransferInProgress){;}
}


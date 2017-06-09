/******************************************************************!
*Copyright (c), 2008-2017, Qingdao Topscomm Communication Co .Ltd.
*File name: systime.c
*Version: 0.1.0
*Date: 2016-11-22
*Author: WANGJIANHUI
*Description: ��ϵͳ��R8025T��ϵͳ��RTC��Ϊһ������ʱ��,R8025Tά��ϵͳ
*             ������������ʱ����,ϵͳ��RTCά�����롣
*******************************************************************/
#include "include.h"
#include "systime.h"


/************************************************************!
*Function: GPSTime2R8025TRTCTime
*Description: ��GPSʱ����µ�R8025Tʱ�估RTC��CNT��
*Input: 1.data: ������׵�ַ
*       1.lens: ����ĳ���
*Output: null
*Return: null
*************************************************************/
void GPSTime2R8025TRTCTime(uint8_t *data,uint8_t lens)
{
	UTCTIME UTC;
	R8025TTIME R8025T;

	Set_Rtc_Cnt(0);

    memcpy(UTC.DATA,data,6);

    UTC=UTCTime2LocalTime(&UTC);

    for(uint8_t i=0;i<6;i++)
    	R8025T.DATA[i]=Hex2Bcd(UTC.DATA[i]);

    Set_R8025t_RtcTime(R8025T.DATA,6);
}
/************************************************************!
*Function: P101Time2R8025TRTCTime
*Description: ��101ʱ����µ�R8025Tʱ�估RTC��CNT��
*Input: 1.data: ������׵�ַ
*       1.lens: ����ĳ���
*Output: null
*Return: null
*************************************************************/
void P101Time2R8025TRTCTime(uint8_t *data,uint8_t lens)
{
	P101TIME P101T;
	R8025TTIME R8025T;

	memcpy(P101T.DATA,data,7);

	Set_Rtc_Cnt((P101T.MS%1000)*32768/1000);

	R8025T.YEAR=Hex2Bcd(P101T.YEAR);
	R8025T.MONTH=Hex2Bcd(P101T.MONTH);
	R8025T.DAY=Hex2Bcd(P101T.DAY.DAY);
    R8025T.HOUR=Hex2Bcd(P101T.HOUR);
    R8025T.MINUTE=Hex2Bcd(P101T.MINUTE);
    R8025T.SECOND=Hex2Bcd(P101T.MS/1000);

    R8025T.SECOND=Hex2Bcd(P101T.MS/1000);

    Set_R8025t_RtcTime(R8025T.DATA,6);
}
/************************************************************!
*Function: R8025TRTCTime2UnixTime
*Description: ��8025T��ʱ����µ�UNIXʱ�䡣
*Input: null
*Output: null
*Return: UNIXʱ��
*************************************************************/
uint32_t R8025TRTCTime2UnixTime(void)
{
	R8025TTIME R8025T;

	Get_R8025t_RtcTime(R8025T.DATA,6);

	return LocalTime2UnixTime(R8025T.DATA,6);
}
/************************************************************!
*Function: UnixTime2P101Time
*Description: ��UNIXʱ���ת��Ϊ101��Լʱ�����ʽ��
*Input: null
*Output: null
*Return: null
*************************************************************/
bool UnixTime2P101Time(UNIXTIME *UT,uint8_t *data,uint8_t lens)
{
	P101TIME PT;
	UTCTIME UTC;

	if(lens<7) //��ֹ����Խ��
		return false;

	UnixTime2LocalTime(UT->UNIX,UTC.DATA,6);

	PT.MS=((uint16_t)UTC.SECOND)*1000+(UT->CNT*1000/32768);
	PT.MINUTE=UTC.MINUTE;
	PT.HOUR=UTC.HOUR;
	PT.DAY.DAY=UTC.DAY;
	PT.DAY.WEEK=YMD2WeekDay(UTC.DATA,6);
	PT.MONTH=UTC.MONTH;
	PT.YEAR=UTC.YEAR;

	memcpy(data,PT.DATA,7);

	return true;
}
/************************************************************!
*Function: NowTime2P101Time
*Description:
*Input: null
*Output: null
*Return:
*************************************************************/
void NowTime2P101Time(uint8_t *data,uint8_t lens)
{
	UNIXTIME UT;

	Get_Sys_Time(&UT); //��ȡ��ǰϵͳʱ��

	UnixTime2P101Time(&UT,data,lens);
}
/************************************************************!
*Function: PrintOut_NowTime
*Description: ��UTCʱ�����8��Сʱ��ɶ�����ʱ�䡣
*Input: null
*Output: null
*Return: ������ʱ��
*************************************************************/
void PrintOut_NowTime(void)
{
	uint8_t data[8]; //������ʱ�������
	DOUBLEBYTE DB;

	NowTime2P101Time(data+1,7);

	memcpy(DB.U8,data+1,2);

	data[5]&=0x1F;           //���ε�����
	data[2]=DB.U16/1000;    //��
	DB.U16%=1000;
	data[1]=DB.U16/100;     //�����λ
	data[0]=DB.U16%100;     //�����λ

	Uart1_TxU8(0xAA); //��ʶ

	for(uint8_t i=0;i<8;i++)
		Uart1_TxU8(Byte2Bcd(data[7-i]));

	Uart1_TxU8(0xAA);
}
/************************************************************!
*Function: UTCTime2LocalTime
*Description: ��UTCʱ�����8��Сʱ��ɶ�����ʱ�䡣
*Input: null
*Output: null
*Return: ������ʱ��
*************************************************************/
UTCTIME UTCTime2LocalTime(UTCTIME *UTC)
{
	uint8_t isleapyear;
	uint8_t DAY[2][13]={{0,31,28,31,30,31,30,31,31,30,31,30,31},
			            {0,31,29,31,30,31,30,31,31,30,31,30,31}};

	UTC->HOUR+=8; //��UTCʱ�����8��Сʱ��ɱ���ʱ��

	if(UTC->HOUR>=24)
	{
		UTC->HOUR-=24;
		UTC->DAY++;
	}

	isleapyear=((UTC->YEAR%4)==0?1:0);

	if(UTC->DAY>DAY[isleapyear][UTC->MONTH])
	{
		UTC->DAY=1;
		UTC->MONTH++;

		if(UTC->MONTH>12)
		{
			UTC->MONTH=1;
			UTC->YEAR++;
		}
	}

	return *UTC;
}
/************************************************************!
*Function: Sys_Tick
*Description: RTC���ж�ά��UNIXʱ���.ÿ��4095(FFF)��ʹ��8025T
*             ����һ��UNIXʱ�����RTC��CNT����ֵ.
*Input: null
*Output: null
*Return: null
*************************************************************/
void Sys_Tick(void)
{
	gUNIXTIME.UNIX++;

	LETIMER0->CMD|=0x04; //���LETIMER��CNT���ۼ����

	gSYSFLAG.CWS.RADIOTICKS=0;

	Run_Led_Toggle();

//	if((gUNIXTIME.UNIX%gSYSPARA.SYSTIME_UPDATE)==0)  //600��Уʱһ��
//		return;
//
//	gUNIXTIME.UNIX=R8025TRTCTime2UnixTime();
}
/************************************************************!
*Function: Get_Sys_Time
*Description: ������С��8/32768=0.365ms����1S�жϵ�ʱ�򣬵Ȳ�
*             �����ж��ٿ���ʱ�꣬��ֹ�Ѿ�������CNT����û�п���
*             UNIXʱ�������1S�жϣ����²���ʱ�����(�����1S��
*             ���)��
*Input: null
*Output: null
*Return: null
*************************************************************/
void Get_Sys_Time(UNIXTIME *UT)
{
	while(RTC->CNT>32760);

	UT->CNT=RTC->CNT;
	UT->UNIX=gUNIXTIME.UNIX;
}
/************************************************************!
*Function: Get_YYMMDD
*Description: ��101ʱ���ʽת��Ϊ32λֵ
*Input: null
*Output: null
*Return: null
*************************************************************/
uint32_t Get_YYMMDD(uint8_t *data,uint8_t lens)
{
	uint32_t unxittime;

	unxittime=((uint32_t)(data[6]<<16))+((uint32_t)(data[5]<<8))+(data[2]&0x1F);

	return unxittime;
}
/************************************************************!
*Function:
*Description:
*Input:
*Output: null
*Return: null
*************************************************************/
bool Is_Valid_101Clock(uint8_t *data,uint8_t lens)
{
	P101TIME TIME;
	uint8_t  isleapyear;
	uint8_t DAY[2][13]={{0,31,28,31,30,31,30,31,31,30,31,30,31},
			            {0,31,29,31,30,31,30,31,31,30,31,30,31}};

	if(lens<7) //��ֹ����Խ��
		return false;

	memcpy(TIME.DATA,data,7);

	if(TIME.YEAR>99)
		return false;

	if(TIME.MONTH==0||TIME.MONTH>12)
		return false;

	isleapyear=((TIME.YEAR%4)==0?1:0);

	if(TIME.DAY.DAY==0||TIME.DAY.DAY>DAY[isleapyear][TIME.MONTH])  //��
		return false;

	if(TIME.DAY.WEEK==0) //����,���ڸ���Ϊ�ж��������Ƿ�����ڶ�Ӧ
		return false;

	if(TIME.HOUR>23)  //ʱ
		return false;

	if(TIME.MINUTE>59)  //��
		return false;

	if(TIME.MS>59999)  //MS���ܴ���59999
		return false;

	return true;
}


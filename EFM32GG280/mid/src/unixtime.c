/*************************************************************************!
*Copyright (c), 2008-2017, Qingdao Topscomm Communication Co .Ltd.
*File name: unixtime.c
*Version: 0.1.0
*Date: 2016-11-05
*Author: WANGJIANHUI
*Description:
*************************************************************************/
#include "include.h"
#include "unixtime.h"


/************************************************************!
*Function: UTCTime2UnixTime
*Description: ��UTCʱ���ʽת��ΪUNIXʱ�����ʽ��
*Input: 1.data: ����
*       2.lens: ���鳤��
*Output: null
*Return: UNIXʱ���
*************************************************************/
uint32_t UTCTime2UnixTime(uint8_t *data,uint8_t lens)
{
	UTCTIME UTC;
	uint8_t  isleapyear;
	uint32_t day,unixtime;
	uint32_t MONTH[2][13]={{0,0,31,59,90,120,151,181,212,243,273,304,334},
						   {0,0,31,60,91,121,152,182,213,244,274,305,335}};

	if(lens<6)
		return 0;

	memcpy(UTC.DATA,data,6);

	day=(UTC.YEAR/4)*(366+365*3);

	if((UTC.YEAR%4)>=1)
		day+=366+((UTC.YEAR%4)-1)*365;

	isleapyear=((UTC.YEAR%4)==0?1:0); //�����ж�

	day+=MONTH[isleapyear][UTC.MONTH];

	day+=UTC.DAY-1; //�մ�1�ſ�ʼ,����ǰ�����ȥ

	unixtime=day*24*3600+UTC.HOUR*3600+UTC.MINUTE*60+UTC.SECOND;

	unixtime+=23*365*24*3600+7*366*24*3600; //��unixtime��ʱ���׼��2000��1��1�ձ�Ϊ1970��1��1��

	return unixtime;
}
/************************************************************!
*Function: LocalTime2UnixTime
*Description: ��������ʱ��ת��ΪUNIXʱ�����ʽ
*Input: 1.data: ����
*       2.lens: ���鳤��
*Output: null
*Return: UNIXʱ���
*************************************************************/
uint32_t LocalTime2UnixTime(uint8_t *data,uint8_t lens)
{
	UTCTIME UTC;
	uint8_t  isleapyear;
	uint32_t day,unixtime;
	uint32_t MONTH[2][13]={{0,0,31,59,90,120,151,181,212,243,273,304,334},
						   {0,0,31,60,91,121,152,182,213,244,274,305,335}};

	memcpy(UTC.DATA,data,6);

	day=(UTC.YEAR/4)*(366+365*3);

	if((UTC.YEAR%4)>=1)
		day+=366+((UTC.YEAR%4)-1)*365;

	isleapyear=((UTC.YEAR%4)==0?1:0); //�����ж�

	day+=MONTH[isleapyear][UTC.MONTH];

	day+=UTC.DAY-1; //�մ�1�ſ�ʼ,����ǰ�����ȥ

	unixtime=day*24*3600+UTC.HOUR*3600+UTC.MINUTE*60+UTC.SECOND;

	unixtime+=23*365*24*3600+7*366*24*3600; //��unixtime��ʱ���׼��2000��1��1�ձ�Ϊ1970��1��1��

	unixtime-=8*3600; //����������ʱ���תΪ��׼ʱ���ʱ���

	return unixtime;
}
/************************************************************!
*Function: UnixTime2LocalTime
*Description: ��UNIXʱ���ת��Ϊ������ʱ�䡣
*Input: 1.unixtime: UNIXʱ���
*       2.data: ����
*       2.lens: ���鳤��
*Output: null
*Return: null
*************************************************************/
void UnixTime2LocalTime(uint32_t unixtime,uint8_t *data,uint8_t lens)
{
	uint8_t  isleapyear;
	UTCTIME UTC;
	uint32_t day;
	uint32_t LEAPYEAR=366*24*3600; //���������
	uint32_t COMMYEAR=365*24*3600; //ƽ�������
	uint32_t SOFY=LEAPYEAR+3*COMMYEAR; //2000�꿪ʼÿһ��4�������(seconds of four year)

	uint16_t month[2][14]={{0,0,31,59,90,120,151,181,212,243,273,304,334,365},
			               {0,0,31,60,91,121,152,182,213,244,274,305,335,366}};

	unixtime+=8*3600; //����׼ʱ��תΪ������ʱ��

	unixtime-=23*365*24*3600+7*366*24*3600; //��UNIX��׼��1970��1��1�ձ�Ϊ2000��1��1��

	UTC.YEAR=(unixtime/SOFY)*4;

	unixtime-=(UTC.YEAR/4)*SOFY;

	for(uint8_t i=1;i<4;i++)
	{
		if((unixtime>=(LEAPYEAR+(i-1)*COMMYEAR))&&(unixtime<(LEAPYEAR+i*COMMYEAR)))
		{
			UTC.YEAR+=i;

			unixtime-=LEAPYEAR+(i-1)*COMMYEAR;

			break;
		}
	}

	day=unixtime/(24*3600);

	isleapyear=(UTC.YEAR%4)==0?1:0;

	for(uint8_t i=1;i<13;i++)
	{
		if(day>=month[isleapyear][i]&&day<month[isleapyear][i+1])
		{
			UTC.MONTH=i;
			UTC.DAY=day-month[isleapyear][i]+1; //��ǰ����Ҫ��1
			unixtime-=day*24*3600;
			break;
		}
	}

	UTC.HOUR=unixtime/3600;

	UTC.MINUTE=((unixtime%3600)/60);

	UTC.SECOND=unixtime%60;

	memcpy(data,UTC.DATA,6);
}
/************************************************************!
*Function: YMD2WeekDay
*Description: ������ת�����ں���
*Input: 1.data: �����׵�ַ
*       2.lens: ����ĳ���
*Output: null
*Return: ����
*************************************************************/
uint8_t YMD2WeekDay(uint8_t *data,uint8_t lens)
{
	UTCTIME UTC;
	uint32_t day;
	uint8_t week,isleapyear;

	uint32_t MONTH[2][13]={{0,0,31,59,90,120,151,181,212,243,273,304,334},
						   {0,0,31,60,91,121,152,182,213,244,274,305,335}};

	memcpy(UTC.DATA,data,6);

	day=(UTC.YEAR/4)*(366+365*3);

	if((UTC.YEAR%4)>=1)
		day+=366+((UTC.YEAR%4)-1)*365;

	isleapyear=(((UTC.YEAR%4)==0)?1:0); //�����ж�

	day+=MONTH[isleapyear][UTC.MONTH];

	day+=UTC.DAY;

	week=(day+5)%7; //2000��1��1��Ϊ����5

	if(week==0) //���ڴ�1-7
		week=7;

	return week;
}
/************************************************************!
*Function: Is_Valid_Clock
*Description: �ж�ʱ���Ƿ�Ϸ�����.��Ҫ������ʽ�Ƿ���BCD��,������
*             ʱ�����Ƿ񳬳�������Χ��
*Input: 1.data: �����׵�ַ
*       2.lens: ����ĳ���
*Output: null
*Return: null
*************************************************************/
uint8_t Is_Valid_Clock(uint8_t *data,uint8_t lens)
{
	UTCTIME UTC;
	uint8_t isleapyear;
	uint8_t DAY[2][13]={{0,31,28,31,30,31,30,31,31,30,31,30,31},
			            {0,31,29,31,30,31,30,31,31,30,31,30,31}};

	if(lens<6) //��ֹ����Խ��
		return false;

	for(uint8_t i=0;i<lens;i++) //�ж�ÿһ���ֽ��Ƿ�����Ч��BCD��
	{
		if(Is_Valid_Bcd(data[i])==false)
			return false;
	}

	memcpy(UTC.DATA,data,6);

	if(UTC.YEAR>99)
		return false;

	if(UTC.MONTH==0||UTC.MONTH>12)
		return false;

	isleapyear=((UTC.YEAR%4)==0?1:0);

	if(UTC.DAY==0||UTC.DAY>DAY[isleapyear][UTC.MONTH])
		return false;

	if(UTC.HOUR>23)
		return false;

	if(UTC.MINUTE>59)
		return false;

	if(UTC.SECOND>59)
		return false;

	return true;
}
/************************************************************!
*Function: Is_Valid_Bcd
*Description: �ж��ֽ��Ƿ��ǺϷ���BCD�롣
*Input: bcd: BCD��
*Output: null
*Return: �Ƿ�Ϸ�
*************************************************************/
uint8_t Is_Valid_Bcd(uint8_t bcd)
{
	SINGLEBYTE SB;

	SB.DATA=bcd;

	if(SB.U03<=9&&SB.U47<=9)
		return true;

	return false;
}
/************************************************************!
*Function: Hex2Bcd
*Description: ��HEXת��ΪBCD��
*Input: hex: hex
*Output: null
*Return: BCD��
*************************************************************/
uint8_t Hex2Bcd(uint8_t hex)
{
	uint8_t bcd;

	bcd=(uint8_t)(((hex/16)<<4)+(hex%16));

	return bcd;
}
/************************************************************!
*Function: Bcd2Hex
*Description: ��BCD��ת��ΪHEX
*Input: bcd: BCD��
*Output: null
*Return:HEX
*************************************************************/
uint8_t Bcd2Hex(uint8_t bcd)
{
	uint8_t hex;

	hex=(uint8_t)((((bcd>>4)&0x0F)*10)+(bcd&0x0F));

	return hex;
}


/******************************************************************!
*Copyright (c), 2008-2017, Qingdao Topscomm Communication Co .Ltd.
*File name: icp.h
*Version: 0.1.0
*Date: 2016-09-20
*Author: WANGJIANHUI
*Description: Internal communication protocol
*******************************************************************/
#ifndef ICP_H_
#define ICP_H_


#include <stdint.h>


/**********ICPЭ����غ궨��(��ԼV1.0.3)**********/
#define ICP_STARTBYTE       0x68
#define ICP_ENDBYTE         0x16

#define ICP_ADDRLEN         6
#define ICP_FRAMELEN        261
#define ICP_FRAMEHEAD       4     //֡ͷ(68+lens+lens+68)
#define ICP_FRAMETAIL       2     //֡β(crc+16)
#define ICP_MINPDULEN       16
#define ICP_MAXPDULEN       255
#define ICP_MINFRAMELEN     22
/************************************************************!
*Function:
*Description:
*************************************************************/
#pragma pack(1)
typedef union
{
	uint8_t DATA;        //������
	struct
	{
		uint8_t CC:4;    //������
		uint8_t RES1:1;  //
		uint8_t RES2:1;  //
		uint8_t PRM:1;   //������־
		uint8_t RES3:1;  //
	};
}ICP_CTRL;

/************************************************************!
*Function: YAOXIN�ṹ��
*Description:
*************************************************************/
typedef union
{
	uint8_t DATA;
	struct
	{
		uint8_t COMMUNTION:1;  //ͨ��״̬
		uint8_t LOWPOWER:1;    //���Ƿѹ
		uint8_t IOVERRUN:1;    //��������
		uint8_t TOVERRUN:1;    //�¶ȳ���
		uint8_t JIEDI:1;       //���ƽӵ�
		uint8_t YONGJIU:1;     //�����Զ�·
		uint8_t SHUNSHI:1;     //˲ʱ�Զ�·
		uint8_t FUGUI:1;       //���ϸ���
	};
}YAOXIN;

typedef union
{
	uint8_t  DATA[ICP_MAXPDULEN-ICP_MINPDULEN];

	struct                   //ң������֡
	{
		uint16_t I;          //����
		uint16_t U;          //�糡
		uint16_t T;          //����
		uint16_t B;          //��ص�ѹ
		uint8_t  WORKMODE;   //����ģʽ
	};

	struct                   //SOE����֡
	{
		UNIXTIME TIME;
		YAOXIN  SOE;
	};

	struct                   //ң������֡
	{
		YAOXIN  YX;
	};

}ICP_FRAME_DATA;
/************************************************************!
*Function: ICPFRAME������
*Description:
*************************************************************/
typedef union
{
	uint8_t FRAME[ICP_FRAMELEN+6];
	struct
	{
		uint8_t         STARTBYTE1;            //��ʼ�ֽ�
		uint8_t         LEN1;    		        //����1
		uint8_t         LEN2;    		        //����2
		uint8_t         STARTBYTE2;            //��ʼ�ֽ�
		ICP_CTRL        CTRL;                  //������
		uint8_t         SRCADDR[ICP_ADDRLEN];  //Դ��ַ
		uint8_t         DSTADDR[ICP_ADDRLEN];	//Ŀ�ĵ�ַ
		uint8_t         TYPE;                  //��������
		uint8_t         FRAMENUM;              //֡����
		uint8_t         FRAMESEQ;              //֡���
		ICP_FRAME_DATA  IFD;
		uint8_t         CS;                    //У����
		uint8_t         ENDBYTE;               //�����ַ�

		uint8_t         LINE;                  //�����������ߺ�
		uint8_t         PHASE;                 //�������������

		uint8_t         PARSE;                 //���ݽ�����־
		uint8_t         ISLOCK;                //�ṹ��ռ�ñ�־
		uint8_t         STATUS;
		uint8_t         CHANNEL;               //����֡����
	};
}ICPFRAME;
#pragma pack()
/************************************************************!
*Function: ICP_PRMö��
*Description:
*************************************************************/
typedef enum
{
	PRMSEC=0, //������
	PRMPRI=1, //�Ӷ���
}ICP_PRM;
/************************************************************!
*Function: �Ӷ��߹����붨��PRM=0
*Description:
*************************************************************/
typedef enum
{
	FCCON=0,     //�϶�ȷ��
	FCNOCON=1,   //��ȷ��
	FCRESDATA=2, //����
	FCNODATA=3,  //���Ͽ�
}ICP_CC0;
/************************************************************!
*Function: �Ӷ��߹����붨��PRM=1
*Description:
*************************************************************/
typedef enum
{
	FCRESETUSE=0,  //����/��Ӧ��
	FCSENDDATA=1,  //����/ȷ��
	FCREQUESTD=2,  //����/��Ӧ
}ICP_CC1;
/************************************************************!
*Function: ���ͱ�ʶ����
*Description:
*************************************************************/
typedef enum
{
	AUTICKS=0,
	TIMESTAMP=1,    //ʱ��
	DBYC=2,         //ң��
	DBSOE=3,        //SOE
	DBWAVE=4,       //����¼������
	DBPARA=5,       //����
	DBPROG=6,       //����
	FAULTWRG=7,     //����¼��
	LED=8,          //��Ʋ���
	WAKEUP=10,
	DBYX=11,        //��ʱ��ң��
	RSTPROCESS=12,  //��λ����
	WORKMODE=14,    //����ģʽ
	ERASEFLASH=15,
	READLOG=16,
	ECPREADLOG=17,
	ECPREADSOE=19,
	NOWTIME=18,
	READSOE=20,
	READYC=21,
	READFAULT=22,
	ECPREADFAULT=23,
	ECPREADYC=24,
	READYK=25,
	ECPREADYK=26,
	READWAVE=27,
	ECPREADWAVE=28,
	ERASEPARA=29,
	ECPSTARTWAVE=30,
}ICP_TYPE;
/************************************************************!
*Function: ICP_CHANNEL
*Description:
*************************************************************/
typedef enum
{
	RADIO_CHANNEL=0,
	WEIHU_CHANNEL=1,
}ICP_CHANNEL;


#endif


/******************************************************************!
*Copyright (c), 2008-2017, Qingdao Topscomm Communication Co .Ltd.
*File name: esam.h
*Version: 0.1.0
*Date: 2017-05-12
*Author: WANGJIANHUI
*Description:
*******************************************************************/
#ifndef ESAM_H_
#define ESAM_H_


#include <stdint.h>
#include <stdbool.h>


#define ESAM_FRAME_MAX_LEN  1000    //ESAM����֡����󳤶�
#define ESAM_RES_MAX_NUM    5       //ESAMӦ��֡���������


#define ESAM_STARTBYTE      0xEB       //ESAM֡��ʼ�ֽ�
#define ESAM_ENDBYTE        0xD7       //ESAM֡�����ֽ�


#define ESAM_FRAMEHEAD_LEN  4     //ESAM����֡֡ͷ����
#define ESAM_FRAMETAIL_LEN  2     //ESAM����֡֡β����
#define ESAM_FRAME_CS_LOC   260   //ESAM֡��ECP101����֡��CS��־λ����


#define ESAM101_FIXFRAME_STARTBYTE   0x10
#define ESAM101_FIXFRAME_ENDBYTE     0x16
#define ESAM101_FIXFRAME_LEN         6
#define ESAM101_VARFRAME_STARTBYTE   0x68
#define ESAM101_VARFRAME_ENDBYTE     0x16
#define ESAM101_VARFRAME_FRAMEHEAD   4
/************************************************************!
*Function:
*Description:
*************************************************************/
typedef struct
{
	uint8_t U16;
}ESAM101_SINGLE_COT;
/************************************************************!
*Function:
*Description:
*************************************************************/
typedef union
{
	uint8_t DATA;
	struct
	{
		uint8_t U03:4;
		uint8_t U47:4;
	};
}ESAM_SINGLEBYTE;
/************************************************************!
*Function:
*Description:
*************************************************************/
typedef union
{
	uint16_t          U16;
	uint8_t           U8[2];
	ESAM_SINGLEBYTE   U4[2];
}ESAM_DOUBLEBYTE;
/************************************************************!
*Function:
*Description:
*************************************************************/
typedef union
{
	uint8_t DATA;
	struct
	{
		uint8_t FC:4;  //������
		uint8_t FCV:1; //֡������Чλ
		uint8_t FCB:1; //֡����λ
		uint8_t PRM:1; //������־
		uint8_t DIR:1; //���䷽��
	};
}ESAM101_CTRL;
/************************************************************!
*Function:
*Description:
*************************************************************/
typedef struct
{
	uint8_t           STARTBYTE;  //��ʼ�ַ�
	ESAM101_CTRL      CTRL;       //����λ
	ESAM_DOUBLEBYTE   LINKADDR;   //��·��ַ
	uint8_t           CS;         //У���
	uint8_t           ENDBYTE;    //�����ַ�
}ESAM101_FIXFRAME;
/************************************************************!
*Function:
*Description:
*************************************************************/
typedef union
{
	uint8_t DATA[246];                  //101Э��涨ASDU��󳤶�Ϊ255
	struct
	{
		uint8_t            TI;         //���ͱ�ʶ
		uint8_t            VSQ;        //�ɱ��޶�
		#ifdef SINGLE_COT_CTRL
		ESAM101_SINGLE_COT COT;        //���ֽڴ���ԭ��
		#else
		ESAM_DOUBLEBYTE    COT;        //˫�ֽڴ���ԭ��
		#endif
		ESAM_DOUBLEBYTE    CAOA;       //������ַ
		ESAM_DOUBLEBYTE    MSGADDR;    //��Ϣ���ַ
		#ifdef SINGLE_COT_CTRL
		uint8_t            MSG[239];   //��Ϣ��Ԫ��
		#else
		uint8_t            MSG[238];   //��Ϣ��Ԫ��
		#endif
	};
}ECP101_ASDU;
/************************************************************!
*Function:
*Description:
*************************************************************/
typedef struct
{
	uint8_t          STARTBYTE1;   //�����ַ�     0
	uint8_t          LEN1;         //����0-255  1
	uint8_t          LEN2;         //����0-255  2
	uint8_t          STARTBYTE2;   //�����ַ�    3
	ESAM101_CTRL     CTRL;         //����λ      4
	ESAM_DOUBLEBYTE  LINKADDR;     //��·��ַ   5 6
	ECP101_ASDU      ASDU;         //��·�û�����
	uint8_t          CS;           //У���
	uint8_t          ENDBYTE;      //�����ַ�
}ESAM101_VARFRAME;
/************************************************************!
*Function:
*Description:
*************************************************************/
typedef union
{
	uint8_t           DATA[255];  //֡����
	ESAM101_FIXFRAME  FF;         //�̶�����֡
	ESAM101_VARFRAME  VF;         //�ɱ䳤��֡
}ESAM101_FRAME;
/************************************************************!
*Function:
*Description:
*************************************************************/
typedef union
{
	uint16_t DATA;
	struct
	{
		uint8_t KEYMARK:3;     //�Գ���Կ��ʶ
		uint8_t ENCRYPTION:1;  //�Ƿ����
		uint8_t RES1:1;        //����
		uint8_t RES2:1;        //����
		uint8_t OBJECT:2;      //����ն����Ӷ���
		uint8_t RES3:8;        //����
	};
}PROTOCOL_TYPE;
/************************************************************!
*Function:
*Description:
*************************************************************/
typedef union
{
	uint8_t DATA[ESAM_FRAME_MAX_LEN-9];
	struct
	{
		uint8_t       APPLEN;     //���ĳ���
		ESAM101_FRAME EF;         //��������
		uint8_t       EXTEN[ESAM_FRAME_MAX_LEN-265];  //��Ϣ��ȫ����
	};
}ENCAPSULATE_DATA1;

typedef union
{
	ESAM_DOUBLEBYTE MSG;
	uint8_t         SAFEINFO[ESAM_FRAME_MAX_LEN-11];

	struct                     //֤����°��ṹ��
	{
		uint8_t CERFLAG;
		uint8_t FRAMENUM;
		uint8_t FRAMESEQ;
		uint8_t CIPHERTEXT[ESAM_FRAME_MAX_LEN-12];
	};

	struct
	{
		uint8_t FRAMENUM1;
		uint8_t FRAMESEQ1;
		uint8_t CIPHERTEXT1[ESAM_FRAME_MAX_LEN-11];
	};
}ENCAPSULATE_DATA2_UNION;
/************************************************************!
*Function:
*Description:
*************************************************************/
typedef union
{
	uint8_t DATA[ESAM_FRAME_MAX_LEN-9];
	struct
	{
		ESAM_DOUBLEBYTE          INFOLEN;   //��ȫ��Ϣ������
		ENCAPSULATE_DATA2_UNION  EDU;
	};
}ENCAPSULATE_DATA2;
/************************************************************!
*Function:
*Description:
*************************************************************/
typedef union
{
	uint8_t DATA[ESAM_FRAME_MAX_LEN-8];
	struct
	{
		uint8_t            APPTYPE;    //Ӧ������
		ENCAPSULATE_DATA1  ENCAP1;     //����Ӧ��������
		ENCAPSULATE_DATA2  ENCAP2;     //ֻ����Ϣ��ȫ��չ��
	};
}ENCAPSULATE_DATA;
/************************************************************!
*Function:
*Description:
*************************************************************/
typedef union
{
	uint8_t DATA[ESAM_FRAME_MAX_LEN];
	struct
	{
		uint8_t          STARTBYTE1; //��ʼ�ֽ�
		uint16_t         PROTOLEN;   //���ĳ���
		uint8_t          STARTBYTE2; //��ʼ�ֽ�
		PROTOCOL_TYPE    PROTOTYPE;  //��������
		ENCAPSULATE_DATA ENCAP;      //��װ������
        uint8_t          CS;         //У���
        uint8_t          ENDBYTE;    //�����ֽ�
	};
}ESAM_FRAME;
/************************************************************!
*Function:
*Description:
*************************************************************/
typedef struct
{
	uint8_t         PARSE;                //���ݽ�����־
	uint8_t         ISLOCK;               //����֡����־
	uint8_t         ESAM101_FRAMETYPE;    //ECP101����֡����
	ESAM_DOUBLEBYTE INFOLEN;              //��Ϣ��չ������

	ESAM_FRAME EF;    //ESAM����֡
}ECP101_REQ;
/************************************************************!
*Function:
*Description:
*************************************************************/
typedef struct
{
	uint16_t POS;
	uint8_t HAS_ESAM101;
	uint8_t ESAM101_FRAMELEN;
	uint8_t ESAM101_FRAMETYPE;
	uint8_t STATUS;
	uint8_t ISLOCK;
	uint16_t INFOLEN;      //��Ϣ��ȫ��չ������
	uint8_t  ESAM101LEN;   //Ӧ������������
	uint8_t ENCRYTYPE;
	ESAM_FRAME EF;    //ESAM����֡
}ECP101RES;
/************************************************************!
*Function:
*Description:
*************************************************************/
typedef struct
{
	uint8_t   SN;
	uint8_t   REQSN;
	uint8_t   RESSN;
	ECP101RES ETQ[ESAM_RES_MAX_NUM];
}ECP101_RES;
/************************************************************!
*Function:
*Description:
*************************************************************/
typedef struct
{
	uint8_t LINKSTATE;
	uint8_t MFCB;
	uint8_t SFCB;

	ECP101_REQ REQ;  //��������֡
	ECP101_RES RES;  //����Ӧ��֡
}ESAMFRAME;
/************************************************************!
*Function:
*Description:
*************************************************************/
typedef enum
{
	ESAM_MAINSITE=0,        //��վ
	ESAM_MAINTENANCETOOL=1, //�ֳ���ά����
	ESAM_GATEWAY=2,          //����
}ESAM_CONNECT_OBJECT_ENUM;

typedef enum
{
	ESAM101_FIXFRAME_TYPE=0,
	ESAM101_VARFRAME_TYPE=1,
}ESAM101_FRAMETYPE_ENUM;




#endif

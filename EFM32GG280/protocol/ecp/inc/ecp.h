/******************************************************************!
*Copyright (c), 2008-2017, Qingdao Topscomm Communication Co .Ltd.
*File name: ecp.h
*Version: 0.1.0
*Date: 2016-10-12
*Author: WANGJIANHUI
*Description: External communication protocol
*******************************************************************/
#ifndef ECP_H_
#define ECP_H_


/**********101��Լ��COT����**********/
//#define SINGLE_COT_CTRL         1    //���ֽ�COT
/**********101������ȼ�**********/
#define MAX_PRIORITY_NUM        11
/**********101���Ӧ��֡��**********/
#define MAX_REPLY_NUM           10
/**********101ң��ȡ������ʱ**********/
#define ECP_YK_TIME             30
/**********101�̶�֡�궨��**********/
#define ECP_FIXFRMAE_LEN        6
#define ECP_FIXFRMAE_STARTBYTE  0x10
#define ECP_FIXFRMAE_ENDBYTE    0x16
/**********101�ɱ�֡�궨��**********/
#define ECP_VARFRMAE_LEN        261
#define ECP_VARFRMAE_STARTBYTE  0x68
#define ECP_ESMFRMAE_STARTBYTE  0x69
#define ECP_VARFRMAE_ENDBYTE    0x16
#define ECP_VARFRAME_CS_LOC     259
#define ECP_VARFRMAE_HEAD       4      //֡ͷ4���ֽ�
#define ECP_VARFRMAE_TAIL       2      //֡β2���ֽ�
#define ECP_ESM_MAXLEN          252
/**********101������궨��**********/
#define ECP_RST_LINK            0       //��λ��·
#define ECP_RST_PROCESS         1       //��λԶ���ն˵��û�����
#define ECP_TICKS_TEST          2       //��������
#define ECP_CALL_DATA           3       //��������
#define ECP_CALL_LINKSTATE      9       //�ٻ���·״̬
#define ECP_MASTER_LINKSTATE    11
#define ECP_SET_PARA            48
#define ECP_REMOTE_CONTROL      45
#define ECP_ALL_CALL            100     //���ٻ�
#define ECP_READ_DATA           102
#define ECP_READ_MULTIPARA      202
#define ECP_TIMING              103     //��վ��ʱ
#define ECP_TEST_LINK           104     //����ƽ��ʽ����Ĳ�����·����
#define ECP_RESET_PROCESS       105
#define ECP_GET_DELAY           106
#define ECP_ACK                 0
#define ECP_NOACK               1
#define ECP_CALL_DIR            5
#define ECP_CALL_FILE           13
#define ECP_CALL_DIRFILE        122     //
#define ECP_REQUEST_FILE        121
#define ECP_FILE_ACK            124

#define ECP_SWITCH_FIXED_AREA   200
#define READ_FIXED_AREA         201
#define ECP_CALL_FILEDIR        210
/**********ESAM������궨��**********/
#define ECP_READ_SAFE_INFO            0xF0
#define ECP_AUTHENTICATION            0xF1
#define ECP_PUBLIC_KEY_VERIFICATION   0xF2
#define ECP_PUBLIC_KEY_UPDATE         0xF3
#define ECP_SYMMETRIC_KEY_UPDATE      0xF4
#define ECP_KEY_CONSULT               0xF5
#define ECP_GET_RANDOM                0xF6


#pragma pack(1)
/************************************************************!
*Function:
*Description:
*************************************************************/
typedef struct
{
	uint8_t U16;
}ECP_SINGLE_COT;
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
}ECP_SINGLEBYTE;
/************************************************************!
*Function:
*Description:
*************************************************************/
typedef union
{
	uint16_t       U16;
	uint8_t        U8[2];
	ECP_SINGLEBYTE U4[2];
}ECP_DOUBLEBYTE;
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
}ECP_CTRL;
/************************************************************!
*Function:
*Description:
*************************************************************/
typedef struct
{
	uint8_t        STARTBYTE;  //��ʼ�ַ�
	ECP_CTRL       CTRL;       //����λ
	ECP_DOUBLEBYTE LINKADDR;   //��·��ַ
	uint8_t        CS;         //У���
	uint8_t        ENDBYTE;    //�����ַ�
}ECP_FIXFRAME;
/************************************************************!
*Function:
*Description:
*************************************************************/
typedef union
{
	uint8_t DATA[252];                  //101Э��涨ASDU��󳤶�Ϊ255
	struct
	{
		uint8_t             TI;         //���ͱ�ʶ
		uint8_t             VSQ;        //�ɱ��޶�
		#ifdef SINGLE_COT_CTRL
		    ECP_SINGLE_COT  COT;        //���ֽڴ���ԭ��
		#else
			ECP_DOUBLEBYTE  COT;        //˫�ֽڴ���ԭ��
		#endif

		ECP_DOUBLEBYTE      CAOA;       //������ַ
		ECP_DOUBLEBYTE      MSGADDR;    //��Ϣ���ַ
		#ifdef SINGLE_COT_CTRL
			uint8_t         MSG[245];   //��Ϣ��Ԫ��
		#else
			uint8_t         MSG[244];   //��Ϣ��Ԫ��
		#endif
	};
}ECP_ASDU;
/************************************************************!
*Function:
*Description:
*************************************************************/
typedef struct
{
	uint8_t        STARTBYTE1;   //�����ַ�     0
	uint8_t        LEN1;         //����0-255  1
	uint8_t        LEN2;         //����0-255  2
	uint8_t        STARTBYTE2;   //�����ַ�    3
	ECP_CTRL       CTRL;         //����λ      4
	ECP_DOUBLEBYTE LINKADDR;     //��·��ַ   5 6
	ECP_ASDU       ASDU;         //��·�û�����
	uint8_t        CS;           //У���
	uint8_t        ENDBYTE;      //�����ַ�
}ECP_VARFRAME;
/************************************************************!
*Function:
*Description:
*************************************************************/
typedef union
{
	uint8_t       DATA[261];  //֡����
	ECP_FIXFRAME  FF;         //�̶�����֡
	ECP_VARFRAME  VF;         //�ɱ䳤��֡
}ECP_FRAME;
/************************************************************!
*Function:
*Description:
*************************************************************/
typedef struct
{
	ECP_FRAME EF;         //101����֡

	uint8_t   PARSE;      //���ݽ�����־
	uint8_t   ISLOCK;     //����֡ռ�ñ�־
	uint8_t   STATUS;     //����֡״̬��־
	uint8_t   PRIORITY;   //���ȼ���־
	uint8_t   ESMLEN;     //ESAM���ܳ���
	uint8_t   FRAMETYPE;  //�ǹ̶�֡���Ǳ䳤֡
}ECP_DATAFRAME;
/************************************************************!
*Function:
*Description:
*************************************************************/
typedef struct
{
	uint8_t        SN;
	ECP_DATAFRAME  ETQ[MAX_REPLY_NUM];
}ECP_TXQUEUE;
/************************************************************!
*Function:
*Description:
*************************************************************/
typedef union
{
	uint8_t DATA[11];
	struct
	{
		uint8_t        TYPE;
		ECP_DOUBLEBYTE MSGADDR;
		ECP_DOUBLEBYTE COT;
		P101SCO        SCO;
		uint32_t       TIMING;
		uint8_t        STATE;
	};
}P101REMOTECONTROL;
/************************************************************!
*Function:
*Description:
*************************************************************/
typedef union
{
	uint8_t DATA[9];
	struct
	{
		uint8_t        STATUS;
		ECP_DOUBLEBYTE MSGADDR;
		ECP_DOUBLEBYTE PARA;
		uint32_t       TIMEOUT;
	};
}TERMINAL_PARA;
/************************************************************!
*Function:
*Description:
*************************************************************/
typedef union
{
	uint8_t        DATA[140];
	ECP_DOUBLEBYTE PARA[70];
}READPARA;
/************************************************************!
*Function: ECPFRAME
*Description:
*************************************************************/
typedef struct
{
	uint8_t       M_FCB;        //��վFCB
	uint8_t       S_FCB;        //��վFCB
	uint8_t       INITRESET;    //��·��λ��־
	uint8_t       ESMSTATE;
	uint8_t       LINKRESET;
	uint8_t       LINKSTATE;    //��·״̬

	uint8_t       SN;
    P101YK        YK;
    AU_PARA       AP;
	uint8_t       ISLOCK;
	FILEINFO      FILE;
    TERMINAL_PARA TP;
	ECP_DATAFRAME REQ;                    //��������֡
	ECP_TXQUEUE   RES[MAX_PRIORITY_NUM];  //����Ӧ��֡
	uint8_t       PRIORITY[MAX_PRIORITY_NUM];
}ECPFRAME;
/************************************************************!
*Function: FLASHPARAARRAY
*Description:
*************************************************************/
typedef	struct
	{
		uint32_t PARAADDR;
		uint16_t MSGADDR;
		uint8_t TAG;
		uint8_t LEN;
}FLASHPARAARRAY;


#pragma pack()
/************************************************************!
*Function:
*Description:
*************************************************************/
typedef enum
{
	FIX_FRAME=0,    //�̶�֡
	VAR_FRAME=1,    //�ɱ�֡
	ESM_FRAME=2,    //ESAM����֡
}ECP_FRAME_FORMAT;
/************************************************************!
*Function:
*Description:
*************************************************************/
typedef enum
{
	LINKSTATE_START=0,    //��·δ����
	LINKSTATE_CONNECT=1,  //��·������
}ECP_LINKSTATE;
/************************************************************!
*Function:
*Description:
*************************************************************/
typedef enum
{
	YKINIT=0,    //��ʼ��
	YKSELECT=1,  //ѡ��
	YKEXEC=2,    //ִ��
}ECP_RC_TYPE;


#endif


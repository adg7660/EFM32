/******************************************************************!
*Copyright (c), 2008-2017, Qingdao Topscomm Communication Co .Ltd.
*File name: database.h
*Version: 0.1.0
*Date: 2016-09-20
*Author: WANGJIANHUI
*Description:
*******************************************************************/
#ifndef DATABASE_H_
#define DATABASE_H_


#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include "include.h"


/**********�㼯��Ԫ���ص��������(�ɼ���Ԫ����)**********/
#define LINEGROUP_MAXNUM     3
#define SYSPARA_NUM          (((1+3*6)*LINEGROUP_MAXNUM+1)+18+1)
#define ECPPARA_NUM          15
#define ECPYX_NUM            (10+((3*8)*LINEGROUP_MAXNUM))  //�˴�ע���޸�����ң��������!!!!!!!!!
#define ECPYC_NUM            (2+((3*5)*LINEGROUP_MAXNUM))  //�˴�ע���޸�����ң��������!!!!!!!!!
#define ECPINFO_LEN          (2*ECPYX_NUM+3*ECPYC_NUM)
/**********��Ƶ��������**********/
#define MAX_ICPFRAME_NUM     5
#define MAX_RADIO_FRAME      5
#define MAX_SOE_NUM          10
/**********�ɼ���Ԫ¼�����ݵ���󳤶�(�ֽ�)**********/
#define AU_ADC_SAMPLE        82
#define MAX_WAVE_NUM         16
#define MAX_WAVE_LEN         (AU_ADC_SAMPLE*MAX_WAVE_NUM)
#define WAVE_FRAME_LEN       104
/**********������Ϣ�ṹ�����󳤶�(�ֽ�)**********/
#define FAULT_DATA_LEN       ((16*MAX_WAVE_LEN)+8+9)


#pragma pack(1)
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
}SINGLEBYTE;
/************************************************************!
*Function:
*Description:
*************************************************************/
typedef union
{
	uint16_t   U16;
	uint8_t    U8[2];
	SINGLEBYTE U4[2];
}DOUBLEBYTE;
/************************************************************!
*Function:
*Description:
*************************************************************/
typedef union
{
	uint32_t   U32;
	uint8_t    U8[4];
	SINGLEBYTE U4[4];
	DOUBLEBYTE U16[2];
}FOURBYTE;
/************************************************************!
*Function:
*Description:
*************************************************************/
typedef union
{
	uint8_t DATA[8];
	struct
	{
		uint32_t CNT;
		uint32_t UNIX;
	};
}UNIXTIME;
/************************************************************!
*Function:
*Description:
*************************************************************/
typedef struct
{
	uint8_t ADDR[6]; //�ɼ���Ԫ��ַ
}AU_ADDR;
/************************************************************!
*Function:
*Description:
*************************************************************/
typedef struct
{
	uint8_t LINENO;  //�ɼ���Ԫ���ڵ��ߺ�
	AU_ADDR AU[3];   //����ɼ���Ԫ
}LINE_UNIT;
/************************************************************!
*Function:
*Description:
*************************************************************/
typedef struct
{
	uint8_t   LINENUM;                 //��Ч�Ĳɼ���Ԫ����
	LINE_UNIT LINE[LINEGROUP_MAXNUM];  //�ɼ���Ԫ��
}LINE_GROUP;
/************************************************************!
*Function:
*Description:
*************************************************************/
typedef union
{
	uint8_t DATA[SYSPARA_NUM];
	struct
	{
		LINE_GROUP LINEGROUP;        //�����ַ����,��3*(3*6+1)+1=58�ֽ�
		uint8_t    BENJI[6];         //������ַ
		uint8_t    WEIHU[6];         //ά����ַ
		uint8_t    BROADCAST[6];     //�㲥��ַ
		uint8_t    RADIO_CHANNEL;    //��Ƶͨ��
	};
}SYSPARA;
/************************************************************!
*Function:
*Description:
*************************************************************/
typedef union
{
	uint8_t DATA[ECPPARA_NUM*2];
	struct
	{
		uint16_t YC_REPORT_CYCLE;              //ң�������ϱ�����
		uint16_t GPS_TIMING_MODE;              //GPSУʱģʽ
		uint16_t GPS_TIMING_CYCLE;             //GPSУʱ����
		uint16_t BATT_VOL_THRESHOLD;           //�㼯��Ԫ��ص�ѹ��ֵ
		uint16_t SUN_VOL_REPORT_THRESHOLD;     //̫���ܵ�ѹ�ϱ���ֵ
		uint16_t BATT_VOL_REPORT_THRESHOLD;    //�㼯��Ԫ��ص�ѹ�ϱ���ֵ
		uint16_t I_REPORT_THRESHOLD;           //�����ϱ���ֵ
		uint16_t U_REPORT_THRESHOLD;           //��ѹ�ϱ���ֵ
		uint16_t T_REPORT_THRESHOLD;           //�¶��ϱ���ֵ
		uint16_t B_REPORT_THRESHOLD;           //�ɼ���Ԫ��ص�ѹ�ϱ���ֵ
		DOUBLEBYTE ZIZHAN;                     //��վ��ַ,2�ֽ�
		uint16_t FAULT_WAVE_NUM;               //���ϲ�������
		uint16_t YC_REPORT_MODE;               //ң���ϱ�ģʽ
		uint16_t RADIO_CHANNEL;                //��Ƶͨ����
		uint16_t AU_OFFLINE_TIME;              //�ɼ���Ԫ����ʱ��
	};
}ECPPARA;
/************************************************************!
*Function:
*Description:
*************************************************************/
typedef union
{
	uint8_t DATA[27];
	struct
	{
		uint16_t TFMIN;
		uint16_t TFMAX;
		uint16_t IFAULTSHORT;
		uint16_t IFAULTEARTH;
		uint16_t TEND;
		uint16_t IMIN;
		uint16_t UDOWNRATIO;
		uint8_t  FAULT_RESET_TIME;
		uint8_t  LINEPHASE;
		uint8_t  YC_PERIOD;
		uint8_t  FAULT_RESETTIME_HH;
		uint8_t  FAULT_RESETTIME_MM;
		uint8_t  CUADDR[6];
		DOUBLEBYTE MSGADDR;
	};
}AU_PARA;
/************************************************************!
*Function:
*Description:
*************************************************************/
typedef struct
{
	uint8_t  SYS_STATUS;
	uint8_t  POWER_SWITCH;   //��Դ�л���־
	uint8_t  ISCALLWAVE;     //�ٻ����α�־
	uint8_t  SYS_EMEN;       //ϵͳEMģʽ��־
	uint8_t  UPDATING;       //������±�־
	uint8_t  FAULTWRG;       //����¼����־
	uint8_t  CHARGE_STATUS;
	uint8_t  RUN_LED_STATUS; //����ָʾ��״̬
	uint32_t RADIOTICKS;     //��Ƶʱ��Ƭ����
	uint32_t RADIORECEIVECNT;//��Ƶ�����жϼ���
	uint32_t ICPSTATUS;
	uint32_t ECPSTATUS;
	uint32_t ICPRUNCOUNT;
	uint32_t ECPRUNCOUNT;
}CU_WORK_STATUS;
/************************************************************!
*Function:
*Description:
*************************************************************/
typedef struct
{
	uint16_t SUN;  //̫���ܵ�ص�ѹ
	uint16_t XDC;  //���ص�ص�ѹ
	uint16_t CAP;  //�������ݵ�ص�ѹ
}CU_SYS_VOL;
/************************************************************!
*Function:
*Description:
*************************************************************/
typedef struct
{
	uint8_t  GPRS;    //GPRS�˿�״̬��־
	uint8_t  WEIHU;   //ά���˿�״̬��־
	uint8_t  RADIO;   //��Ƶ�˿�״̬��־
}CU_INTERFACE_STATUS;
/************************************************************!
*Function:
*Description:
*************************************************************/
typedef struct
{
	uint32_t  AU_TIMING_ACK;      //�ɼ���ԪУʱӦ��ͳ��
	uint32_t  AU_TIMING_ASYNC;    //�ɼ���ԪУʱ�첽ͳ��
	uint32_t  AU_ENTER_LOW_POWER; //�ɼ���Ԫ
    uint32_t  AU_WORKMODE_ACK;    //�ɼ���Ԫ����ģʽӦ��ͳ��
    uint32_t  WORKMODE;           //�ɼ���Ԫ��Ĺ���ģ
    uint8_t   WORKMODE_SWITCH;
	uint8_t   AU_YC_REPORT;       //�ɼ���Ԫң���ϱ�ͳ��
	uint8_t   AU_WORKMODE[3];
	uint32_t  AU_OFFLINE[3];
}AU_STATUS_FLAG;
/************************************************************!
*Function:
*Description:
*************************************************************/
typedef struct
{
	AU_STATUS_FLAG  ASF[LINEGROUP_MAXNUM]; //�ɼ���Ԫ״̬��־
}AU_WORK_STATUS;
/************************************************************!
*Function:
*Description:
*************************************************************/
typedef struct
{
	uint32_t  AU_OFFLINE_MARK[3];    //�ɼ���Ԫ����ʱ��
	uint32_t  AU_WORKMODE_MARK[3];   //�ɼ���Ԫ����ģʽ�л�����ʱ��
	uint32_t  AU_SOE_TIME[3];        //�ɼ���ԪSOE����ʱ��
}SYS_TIME_COUNT;
/************************************************************!
*Function:
*Description:
*************************************************************/
typedef struct
{
	uint32_t       YC_RECEIVE;          //ң�����ʱ��
	uint32_t       AU_TIMING_TIME;      //�ɼ���ԪУʱʱ�̵ļ�ʱ
	uint32_t       YC_RECORD_TIME;      //�ɼ���Ԫң�����ݼ�¼ʱ��
	uint32_t       YC_REPORT_TIME;      //ң���ϱ���¼ʱ��
	uint32_t       GPS_TIMING_TIME;     //GPSУʱʱ���ʱ
	uint32_t       SYSFLAG_PRINT_TIME;  //ϵͳ��־��ӡʱ��
	uint32_t       CU_STOP_CHARGE_TIME; //
	SYS_TIME_COUNT STC[LINEGROUP_MAXNUM];
}SYS_TIME_MARK;
/************************************************************!
*Function:
*Description:
*************************************************************/
typedef struct
{
	uint32_t  LOG;   //��־д����ָ��
	uint32_t  SOE;   //ң��д����ָ��
	uint32_t  YC;    //ң��д����ָ��
    uint32_t  YK;    //ң��д����ָ��
    uint32_t  FAULT; //����д����ָ��
    uint32_t  WAVE;  //����д����ָ��
}MX25FLASH_WRITE;

typedef struct
{
	uint8_t REMOTE_RANDOM[16];
	uint8_t TOOL_RANDOM[16];
	uint8_t  REMOTE_VERI;
    uint8_t  TOOLID[8];
	uint8_t  TOOL_VERI;
}ESAM1161Y_PARA;
/************************************************************!
*Function:
*Description:
*************************************************************/
typedef struct
{
	CU_WORK_STATUS         CWS;   //�㼯��Ԫ����״̬
	CU_SYS_VOL             CBV;   //�㼯��Ԫϵͳ��ѹ
	CU_INTERFACE_STATUS    CIS;   //�㼯��Ԫ�ӿ�״̬
	AU_WORK_STATUS         AWS;   //�ɼ���Ԫ����״̬
	MX25FLASH_WRITE        MFW;   //MX25д����ָ��
	SYS_TIME_MARK          STM;   //ϵͳ��ʱ��־
	ESAM1161Y_PARA         EYP;   //ESAM�����
}SYSFLAG;
/************************************************************!
*Function:
*Description:
*************************************************************/
typedef struct
{
	DOUBLEBYTE ADDR; //��Ϣ���ַ
	DOUBLEBYTE MSG;  //��Ϣ����
}ECPDATA_YX;
/************************************************************!
*Function:
*Description:
*************************************************************/
typedef struct
{
	ECPDATA_YX  CUR_OVER[3];        //����
	ECPDATA_YX  COMM_FAULT[3];      //ͨ�Ź���
	ECPDATA_YX  SHUNSHI_FAULT[3];   //˲ʱ�Զ�·
	ECPDATA_YX  YONGJIU_FAULT[3];   //�����Զ�·
	ECPDATA_YX  AU_LOW_POWER[3];    //�ɼ���Ԫ���Ƿѹ
	ECPDATA_YX  AU_POWER_SWITCH[3]; //�ɼ���Ԫ����л�
	ECPDATA_YX  FUHE_OVER[3];       //����Խ��
	ECPDATA_YX  ZHONGZAI[3];        //����
}ECP_YX;
/************************************************************!
*Function:
*Description:
*************************************************************/
typedef union
{
	uint16_t DATA[ECPYX_NUM*2];
	struct
	{
		ECPDATA_YX  STATUS;                  //�㼯��Ԫ״̬
		ECPDATA_YX  LOW_POWER;               //�㼯��Ԫ�͵�ѹ
		ECPDATA_YX  POWER_SWITCH;            //�󱸵�ԴͶ��
		ECPDATA_YX  RF_FAULT;                //С����ģ�����
		ECPDATA_YX  GPS_LOCK;                //GPS������־
		ECPDATA_YX  WAVEFILE;                //��¼���ļ�����
		ECPDATA_YX  ALL_FAULT;               //���߹���
		ECPDATA_YX  LINE_WORKMODE[3];

		ECP_YX      ECPYX[LINEGROUP_MAXNUM]; //�ɼ���Ԫ��ң������
	};
}ECP_YX_DATA;
/************************************************************!
*Function:
*Description:
*************************************************************/
typedef struct
{
	DOUBLEBYTE ADDR; //��Ϣ���ַ
	DOUBLEBYTE MSG;  //��Ϣ����
	DOUBLEBYTE QDS;  //Ʒ��������
}ECPDATA_YC;
/************************************************************!
*Function:
*Description:
*************************************************************/
typedef struct
{
	ECPDATA_YC CUR[3];         //�ɼ���Ԫ����
	ECPDATA_YC VOL[3];         //�ɼ���Ԫ��ѹ
	ECPDATA_YC TEM[3];         //�ɼ���Ԫ�¶�
	ECPDATA_YC AU_BAT_VOL[3];  //�ɼ���Ԫ��ص�ѹ
	ECPDATA_YC AU_GET_VOL[3];  //�ɼ���Ԫȡ���ѹ
}ECP_YC;
/************************************************************!
*Function:
*Description:
*************************************************************/
typedef union
{
	uint16_t DATA[ECPYC_NUM*3];
	struct
	{
		ECPDATA_YC SUN_VOL;                 //̫���ܰ��ѹ
		ECPDATA_YC BAT_VOL;                 //��ص�ѹ
		ECP_YC     ECPYC[LINEGROUP_MAXNUM]; //�ɼ���Ԫ��ң������
	};
}ECP_YC_DATA;
/************************************************************!
*Function:
*Description:
*************************************************************/
typedef union
{
	uint16_t DATA[ECPINFO_LEN];
	struct
	{
		ECP_YX_DATA YX;  //ң������
		ECP_YC_DATA YC;  //ң������
	};
}ECPINFO;
/************************************************************!
*Function:
*Description:
*************************************************************/
typedef union
{
	uint8_t DATA;
	struct
	{
		uint8_t DAY:5;  //��
		uint8_t WEEK:3;	//����
	};
}P101DAY;
/************************************************************!
*Function:
*Description:
*************************************************************/
typedef union
{
	uint8_t DATA[7];
	struct
	{
		uint16_t MS;
		uint8_t  MINUTE;
		uint8_t  HOUR;
		P101DAY  DAY;
		uint8_t  MONTH;
		uint8_t  YEAR;
	};
}P101TIME;
/************************************************************!
*Function:
*Description:
*************************************************************/
typedef union
{
	uint8_t DATA[139];
	struct
	{
		uint8_t   LENS;
		uint8_t   TYPE;
		P101TIME  TIME;
		char      ASCII[130]; //Э��涨ASCII�������128�ֽ�+CRLF
	};
}LOGRECORD;
/************************************************************!
*Function: WAVE_DAT_FORMAT�ṹ��
*Description:
*************************************************************/
typedef union
{
	uint8_t DATA[26];
	struct
	{
		uint32_t N;
		uint32_t TIMESTAMP;
		uint16_t AU;
		uint16_t BU;
		uint16_t CU;
		uint16_t ZU;
		uint16_t AI;
		uint16_t BI;
		uint16_t CI;
		uint16_t ZI;
		uint16_t YX;
	};
}WAVE_DAT_FORMAT;
/************************************************************!
*Function: FAULTWAVE�ṹ��
*Description:�ɼ���Ԫ����ϲ���
*************************************************************/
typedef union
{
	uint8_t DATA[4*MAX_WAVE_LEN];
	struct
	{
		int16_t  VOL[MAX_WAVE_LEN];  //��ѹ����
		int16_t  CUR[MAX_WAVE_LEN];  //��������
	};
}FAULTWAVE;
/************************************************************!
*Function: FAULTINFO�ṹ��
*Description:�ɼ���Ԫ������Ϣ
*************************************************************/
typedef union
{
	uint8_t DATA[FAULT_DATA_LEN];
	struct
	{
		uint32_t    CNT;
		uint32_t    UNIXTIME;

		uint8_t     LINE;     //�����������ߺ�
		uint8_t     PHASE;    //�������������
		uint8_t     TYPE;     //��������,������Ϊ���ƽӵع���ʱ,��ֵΪ1,��������¶�Ϊ0
		uint8_t     FRAMESEQ; //����¼��������֡���
		uint8_t     FRAMENUM; //����¼��������֡��
		uint32_t    WAVELEN;  //����¼������(������*��������)
		SINGLEBYTE  WAVENUM;  //��4λΪ����ǰ������,��4λΪ���Ϻ�����
		FAULTWAVE   WAVE[3]; //������Ϣ
		int16_t     ZEROU[MAX_WAVE_LEN];
		int16_t     ZEROI[MAX_WAVE_LEN];
	};
}FAULTINFO;
/************************************************************!
*Function: P101SOE�ṹ��
*Description:
*************************************************************/
typedef union
{
	uint8_t DATA[15];
	struct
	{
		uint8_t    TYPE;        //���ͱ�ʶ
		DOUBLEBYTE MSGADDR;     //��Ϣ���ַ
		uint8_t    SOE;         //��Ʒ�������ĵ�����Ϣ
		uint8_t    TIME[7];     //CP56ʱ��
		uint16_t   CRLF;        //�س�����
		uint8_t    ISLOCK;      //֡����־
		uint8_t    STATUS;
	};
}P101SOE;
/************************************************************!
*Function: SOEQUEUE�ṹ��
*Description:
*************************************************************/
typedef struct
{
	uint8_t WRITE;
	P101SOE SOE[MAX_SOE_NUM];
}SOEQUEUE;
/************************************************************!
*Function: P101FAULT�ṹ��
*Description:
*************************************************************/
typedef union
{
	uint8_t DATA[13];
	struct
	{
		DOUBLEBYTE MSGADDR;   //��Ϣ���ַ
		uint8_t    FAULT;     //������Ϣ
		uint8_t    TIME[7];   //CP56ʱ��
		uint16_t   CRLF;
		uint8_t    ISLOCK;    //֡����־
	};
}P101FAULT;
/************************************************************!
*Function: FAULTQUEUE�ṹ��
*Description:
*************************************************************/
typedef struct
{
	uint8_t   WRITE;
	P101FAULT FAULT[20];
}FAULTQUEUE;
/************************************************************!
*Function: P101SCO
*Description:
*************************************************************/
typedef union
{
	uint8_t DATA;
	struct
	{
		uint8_t SCS:1; //0:��,1:��
		uint8_t BS1:1;
		uint8_t QU:5;
		uint8_t SE:1;  //0:ִ��1:ѡ��
	};
}P101SCO;
/************************************************************!
*Function: P101YK�ṹ��
*Description:
*************************************************************/
typedef union
{
	uint8_t DATA[20];
	struct
	{
		uint8_t    TYPE;      //���ͱ�ʶ
		DOUBLEBYTE MSGADDR;   //��Ϣ���ַ
		DOUBLEBYTE COT;       //����ԭ��
		P101SCO    SCO;       //��������
		uint8_t    TIME[7];   //CP56ʱ��
		uint16_t   CRLF;      //�س�����
		uint32_t   TIMING;    //�����ʱ
		uint8_t    STATE;     //����״̬
	};
}P101YK;
/************************************************************!
*Function: YCDATA�ṹ��
*Description:
*************************************************************/
typedef struct
{
	uint8_t     COMMA;
	DOUBLEBYTE  ADDR;
	uint16_t    DATA;
}YCDATA;
/************************************************************!
*Function: YAOCEFILE�ṹ��
*Description:
*************************************************************/
typedef union
{
	uint8_t DATA[164];
	struct
	{
		uint8_t  LENS;
		uint8_t  SN;       //����
		uint8_t  COMMA1;   //����
		uint8_t  N;        //����������Ŀ
		uint8_t  COMMA2;   //����
		P101TIME TIME;     //7�ֽ�
		YCDATA   YC[27];   //5*27�ֽ�
		uint16_t CRLF;     //�س�����

		uint32_t TIMEOUT;  //ң�ⳬʱ����
		uint32_t OLDTIME;
		uint32_t NEWTIME;
		uint8_t  CONNECTION[3];
	};
}YAOCEFILE;
/************************************************************!
*Function: YAOCEFILEHEAD�ṹ��
*Description:
*************************************************************/
typedef union
{
	uint8_t DATA[77]; //�淶�76�ֽڼ�һ���ֽڵ�LENS
	struct
	{
		char     FILENAME[20];
		uint8_t  COMMA1;
		char     FILEVERSION[20];
		uint16_t CRLF1;
		char     TERMINALNAME[20];
		uint8_t  COMMA2;
		uint8_t  DATE[3];           //CP56������
		uint8_t  COMMA3;
		uint8_t  K;
		uint8_t  COMMA4;
		uint8_t  ADDRLENS[2];
		uint8_t  COMMA5;
		uint8_t  TYPE;
		uint16_t CRLF2;
		uint8_t  LENS;
	};
}YAOCEFILEHEAD;
/************************************************************!
*Function:
*Description:
*************************************************************/
typedef union
{
	uint8_t DATA[22];
	struct
	{
		uint16_t   ID;      //�ļ�����
		uint8_t    CS;      //�ļ�У���
		uint16_t   LENS;    //�ļ�����
		uint32_t   READ;    //�ļ���ָ��
		uint8_t    STATE;   //�ļ�״̬
		uint32_t   INFONO;  //�ļ������
		uint8_t    SECTION; //�ں�
		uint16_t   SENDNUM;
		uint16_t   INFONUM; //�ļ�������
		uint8_t    TIME[7]; //�ļ�ʱ��
		DOUBLEBYTE MSGADDR; //��Ϣ���ַ
	};
}FILEINFO;
/************************************************************!
*Function: RESETCAUSE�ṹ��
*Description:
*************************************************************/
typedef union
{
	uint32_t DATA;
	struct
	{
		uint8_t POR:1;  //�ϵ縴λ
		uint8_t UBOR:1; //�쳣���縴λ
		uint8_t BOR:1;  //�������縴λ
		uint8_t ETR:1;  //�ⲿ��λ(�⹷)
		uint8_t WDR:1;  //���Ź���λ
		uint8_t LUR:1;  //M3����λ
		uint8_t SRR:1;  //ϵͳ����λ
	};
}RMU_RESETCAUSE;
/************************************************************!
*Function: ��һ��ֵ
*Description:
*************************************************************/
typedef union
{
	uint16_t F16;
	struct
	{
		uint16_t DATA:15;
		uint8_t  SIGN:1;
	};
}NVA;
#pragma pack()
/************************************************************!
*Function:
*Description:
*************************************************************/
typedef enum
{
	JIEDI=1,         //�ӵ�
	DIANLIANGDI=2,   //��ص�����
	DUANLU=3,        //��·
}SOE_TYPE_t;
/************************************************************!
*Function:
*Description:
*************************************************************/
typedef enum
{
	SLEEP=1,  //����
	RX=2,     //����
	RXC=3,    //�������
	TX=4,     //����
	TXC=5,    //�������
}CU_INTERFACE_STATUS_ENUM;


uint8_t Get_LinePara_Num(void);
void YaoCeFile_Init(YAOCEFILE *YCF);
void YaoCeFile_Clear(YAOCEFILE *YCF);
void YaoCeFileHead_Init(YAOCEFILEHEAD *YCFH);
void Wave_Dat_Format_Init(WAVE_DAT_FORMAT *WDF);


#endif


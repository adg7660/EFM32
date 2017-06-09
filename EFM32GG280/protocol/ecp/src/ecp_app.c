/******************************************************************!
*Copyright (c), 2008-2017, Qingdao Topscomm Communication Co .Ltd.
*File name: ecp_app.c
*Version: 0.1.0
*Date: 2016-09-20
*Author: WANGJIANHUI
*Description:
*******************************************************************/
#include "include.h"


const FLASHPARAARRAY PARA_AREA[]={
		{INHERENTPARA_ADDR+ 0x00,   0x8001,  4,  8},
		{INHERENTPARA_ADDR+ 0x04,   0x8002,  4,  8},
		{INHERENTPARA_ADDR+ 0x08,   0x8003,  4,  8},
		{INHERENTPARA_ADDR+ 0x0C,   0x8004,  4,  8},
		{INHERENTPARA_ADDR+ 0x10,   0x8005,  4,  8},
		{INHERENTPARA_ADDR+ 0x14,   0x8006,  4,  8},
		{INHERENTPARA_ADDR+ 0x18,   0x8007,  4,  8},
		{INHERENTPARA_ADDR+ 0x1C,   0x8008,  4,  8},
		{INHERENTPARA_ADDR+ 0x20,   0x8009,  4,  8},
		{INHERENTPARA_ADDR+ 0x24,   0x800A,  4,  8},

		{RUNPARA_ADDR+ 0x00,  0x8020,  4,  ECP_MULTIPARA_LEN},
		{RUNPARA_ADDR+ 0x04,  0x8021,  4,  ECP_MULTIPARA_LEN},
		{RUNPARA_ADDR+ 0x08,  0x8022,  4,  ECP_MULTIPARA_LEN},
		{RUNPARA_ADDR+ 0x0C,  0x8023,  4,  ECP_MULTIPARA_LEN},
		{RUNPARA_ADDR+ 0x10,  0x8024,  4,  ECP_MULTIPARA_LEN},
		{RUNPARA_ADDR+ 0x14,  0x8025,  4,  ECP_MULTIPARA_LEN},
		{RUNPARA_ADDR+ 0x18,  0x8026,  4,  ECP_MULTIPARA_LEN},
		{RUNPARA_ADDR+ 0x1C,  0x8027,  4,  ECP_MULTIPARA_LEN},
		{RUNPARA_ADDR+ 0x20,  0x8028,  4,  ECP_MULTIPARA_LEN},
		{RUNPARA_ADDR+ 0x24,  0x8029,  4,  ECP_MULTIPARA_LEN},
		{RUNPARA_ADDR+ 0x28,  0x802A,  4,  ECP_MULTIPARA_LEN},
		{RUNPARA_ADDR+ 0x2C,  0x802B,  4,  ECP_MULTIPARA_LEN},
		{RUNPARA_ADDR+ 0x30,  0x802C,  4,  ECP_MULTIPARA_LEN},
		{RUNPARA_ADDR+ 0x34,  0x802D,  4,  ECP_MULTIPARA_LEN},
		{RUNPARA_ADDR+ 0x38,  0x802E,  4,  ECP_MULTIPARA_LEN},
		{RUNPARA_ADDR+ 0x3C,  0x802F,  4,  ECP_MULTIPARA_LEN},
		{RUNPARA_ADDR+ 0x40,  0x8030,  4,  ECP_MULTIPARA_LEN},
		{RUNPARA_ADDR+ 0x44,  0x8031,  4,  ECP_MULTIPARA_LEN},
		{RUNPARA_ADDR+ 0x48,  0x8032,  4,  ECP_MULTIPARA_LEN},
		{RUNPARA_ADDR+ 0x4C,  0x8033,  4,  ECP_MULTIPARA_LEN},
		{RUNPARA_ADDR+ 0x50,  0x8034,  4,  ECP_MULTIPARA_LEN},
		{RUNPARA_ADDR+ 0x54,  0x8035,  4,  ECP_MULTIPARA_LEN},
		{RUNPARA_ADDR+ 0x58,  0x8036,  4,  ECP_MULTIPARA_LEN},
		{RUNPARA_ADDR+ 0x5C,  0x8037,  4,  ECP_MULTIPARA_LEN},
		{RUNPARA_ADDR+ 0x60,  0x8038,  4,  ECP_MULTIPARA_LEN},
		{RUNPARA_ADDR+ 0x64,  0x8039,  4,  ECP_MULTIPARA_LEN},
		{RUNPARA_ADDR+ 0x68,  0x803A,  4,  ECP_MULTIPARA_LEN},
		{RUNPARA_ADDR+ 0x6C,  0x803B,  4,  ECP_MULTIPARA_LEN},
		{RUNPARA_ADDR+ 0x70,  0x803C,  4,  ECP_MULTIPARA_LEN},
		{RUNPARA_ADDR+ 0x74,  0x803D,  4,  ECP_MULTIPARA_LEN},
		{RUNPARA_ADDR+ 0x78,  0x803E,  4,  ECP_MULTIPARA_LEN},
		{RUNPARA_ADDR+ 0x7C,  0x803F,  4,  ECP_MULTIPARA_LEN},
		{RUNPARA_ADDR+ 0x80,  0x8040,  4,  ECP_MULTIPARA_LEN},
		{RUNPARA_ADDR+ 0x84,  0x8041,  4,  ECP_MULTIPARA_LEN},
		{RUNPARA_ADDR+ 0x88,  0x8042,  4,  ECP_MULTIPARA_LEN},
		{RUNPARA_ADDR+ 0x8C,  0x8043,  4,  ECP_MULTIPARA_LEN},
		{RUNPARA_ADDR+ 0x90,  0x8044,  4,  ECP_MULTIPARA_LEN},
		{RUNPARA_ADDR+ 0x94,  0x8045,  4,  ECP_MULTIPARA_LEN},
		{RUNPARA_ADDR+ 0x98,  0x8046,  4,  ECP_MULTIPARA_LEN},
		{RUNPARA_ADDR+ 0x9C,  0x8047,  4,  ECP_MULTIPARA_LEN},
		{RUNPARA_ADDR+ 0xA0,  0x8048,  4,  ECP_MULTIPARA_LEN},
		{RUNPARA_ADDR+ 0xA4,  0x8049,  4,  ECP_MULTIPARA_LEN},
		{RUNPARA_ADDR+ 0xA8,  0x804A,  4,  ECP_MULTIPARA_LEN},
		{RUNPARA_ADDR+ 0xAC,  0x804B,  4,  ECP_MULTIPARA_LEN},
		{RUNPARA_ADDR+ 0xB0,  0x804C,  4,  ECP_MULTIPARA_LEN},
		{RUNPARA_ADDR+ 0xB4,  0x804D,  4,  ECP_MULTIPARA_LEN},
		{RUNPARA_ADDR+ 0xB8,  0x804E,  4,  ECP_MULTIPARA_LEN},
		{RUNPARA_ADDR+ 0xBC,  0x804F,  4,  ECP_MULTIPARA_LEN},
		{RUNPARA_ADDR+ 0xC0,  0x8050,  4,  ECP_MULTIPARA_LEN},
		{RUNPARA_ADDR+ 0xC4,  0x8051,  4,  ECP_MULTIPARA_LEN},
		{RUNPARA_ADDR+ 0xC8,  0x8052,  4,  ECP_MULTIPARA_LEN},
		{RUNPARA_ADDR+ 0xCC,  0x8053,  4,  ECP_MULTIPARA_LEN},
		{RUNPARA_ADDR+ 0xD0,  0x8054,  4,  ECP_MULTIPARA_LEN},
		{RUNPARA_ADDR+ 0xD4,  0x8055,  4,  ECP_MULTIPARA_LEN},
		{RUNPARA_ADDR+ 0xD8,  0x8056,  4,  ECP_MULTIPARA_LEN},
		{RUNPARA_ADDR+ 0xDC,  0x8057,  4,  ECP_MULTIPARA_LEN},
		{RUNPARA_ADDR+ 0xE0,  0x8058,  4,  ECP_MULTIPARA_LEN},
		{RUNPARA_ADDR+ 0xE4,  0x8059,  4,  ECP_MULTIPARA_LEN},
		{RUNPARA_ADDR+ 0xE8,  0x805A,  4,  ECP_MULTIPARA_LEN},
		{RUNPARA_ADDR+ 0xEC,  0x805B,  4,  ECP_MULTIPARA_LEN},
		{RUNPARA_ADDR+ 0xF0,  0x805C,  4,  ECP_MULTIPARA_LEN},
		{RUNPARA_ADDR+ 0xF4,  0x805D,  4,  ECP_MULTIPARA_LEN},
		{RUNPARA_ADDR+ 0xF8,  0x805E,  4,  ECP_MULTIPARA_LEN},
		{RUNPARA_ADDR+ 0xFC,  0x805F,  4,  ECP_MULTIPARA_LEN},

		{FIXVALUE_PARA+ 0x00,  0x8220,  4,  ECP_MULTIPARA_LEN},
		{FIXVALUE_PARA+ 0x04,  0x8221,  4,  ECP_MULTIPARA_LEN},
		{FIXVALUE_PARA+ 0x08,  0x8222,  4,  ECP_MULTIPARA_LEN},
		{FIXVALUE_PARA+ 0x0C,  0x8223,  4,  ECP_MULTIPARA_LEN},
		{FIXVALUE_PARA+ 0x10,  0x8224,  4,  ECP_MULTIPARA_LEN},
		{FIXVALUE_PARA+ 0x14,  0x8225,  4,  ECP_MULTIPARA_LEN},
		{FIXVALUE_PARA+ 0x18,  0x8226,  4,  ECP_MULTIPARA_LEN},
		{FIXVALUE_PARA+ 0x1C,  0x8227,  4,  ECP_MULTIPARA_LEN},
		{FIXVALUE_PARA+ 0x20,  0x8228,  4,  ECP_MULTIPARA_LEN},
		{FIXVALUE_PARA+ 0x24,  0x8229,  4,  ECP_MULTIPARA_LEN},
		{FIXVALUE_PARA+ 0x28,  0x822A,  4,  ECP_MULTIPARA_LEN},
		{FIXVALUE_PARA+ 0x2C,  0x822B,  4,  ECP_MULTIPARA_LEN},
		{FIXVALUE_PARA+ 0x30,  0x822C,  4,  ECP_MULTIPARA_LEN},
		{FIXVALUE_PARA+ 0x34,  0x822D,  4,  ECP_MULTIPARA_LEN},
		{FIXVALUE_PARA+ 0x38,  0x822E,  4,  ECP_MULTIPARA_LEN},
		{FIXVALUE_PARA+ 0x3C,  0x822F,  4,  ECP_MULTIPARA_LEN},
		{FIXVALUE_PARA+ 0x40,  0x8230,  4,  ECP_MULTIPARA_LEN},
		{FIXVALUE_PARA+ 0x44,  0x8231,  4,  ECP_MULTIPARA_LEN},
		{FIXVALUE_PARA+ 0x48,  0x8232,  4,  ECP_MULTIPARA_LEN},
		{FIXVALUE_PARA+ 0x4C,  0x8233,  4,  ECP_MULTIPARA_LEN},
		{FIXVALUE_PARA+ 0x50,  0x8234,  4,  ECP_MULTIPARA_LEN},
		{FIXVALUE_PARA+ 0x54,  0x8235,  4,  ECP_MULTIPARA_LEN},
		{FIXVALUE_PARA+ 0x58,  0x8236,  4,  ECP_MULTIPARA_LEN},
		{FIXVALUE_PARA+ 0x5C,  0x8237,  4,  ECP_MULTIPARA_LEN},
		{FIXVALUE_PARA+ 0x60,  0x8238,  4,  ECP_MULTIPARA_LEN},
		{FIXVALUE_PARA+ 0x64,  0x8239,  4,  ECP_MULTIPARA_LEN},
		{FIXVALUE_PARA+ 0x68,  0x823A,  4,  ECP_MULTIPARA_LEN},
		{FIXVALUE_PARA+ 0x6C,  0x823B,  4,  ECP_MULTIPARA_LEN},
		{FIXVALUE_PARA+ 0x70,  0x823C,  4,  ECP_MULTIPARA_LEN},
		{FIXVALUE_PARA+ 0x74,  0x823D,  4,  ECP_MULTIPARA_LEN},
		{FIXVALUE_PARA+ 0x78,  0x823E,  4,  ECP_MULTIPARA_LEN},
		{FIXVALUE_PARA+ 0x7C,  0x823F,  4,  ECP_MULTIPARA_LEN},
		{FIXVALUE_PARA+ 0x80,  0x8240,  4,  ECP_MULTIPARA_LEN},
		{FIXVALUE_PARA+ 0x84,  0x8241,  4,  ECP_MULTIPARA_LEN},
		{FIXVALUE_PARA+ 0x88,  0x8242,  4,  ECP_MULTIPARA_LEN},
		{FIXVALUE_PARA+ 0x8C,  0x8243,  4,  ECP_MULTIPARA_LEN},
		{FIXVALUE_PARA+ 0x90,  0x8244,  4,  ECP_MULTIPARA_LEN},
		{FIXVALUE_PARA+ 0x94,  0x8245,  4,  ECP_MULTIPARA_LEN},
		{FIXVALUE_PARA+ 0x98,  0x8246,  4,  ECP_MULTIPARA_LEN},
		{FIXVALUE_PARA+ 0x9C,  0x8247,  4,  ECP_MULTIPARA_LEN},
		{FIXVALUE_PARA+ 0xA0,  0x8248,  4,  ECP_MULTIPARA_LEN},
		{FIXVALUE_PARA+ 0xA4,  0x8249,  4,  ECP_MULTIPARA_LEN},
		{FIXVALUE_PARA+ 0xA8,  0x824A,  4,  ECP_MULTIPARA_LEN},
		{FIXVALUE_PARA+ 0xAC,  0x824B,  4,  ECP_MULTIPARA_LEN},
		{FIXVALUE_PARA+ 0xB0,  0x824C,  4,  ECP_MULTIPARA_LEN},
		{FIXVALUE_PARA+ 0xB4,  0x824D,  4,  ECP_MULTIPARA_LEN},
		{FIXVALUE_PARA+ 0xB8,  0x824E,  4,  ECP_MULTIPARA_LEN},
		{FIXVALUE_PARA+ 0xBC,  0x824F,  4,  ECP_MULTIPARA_LEN},
		{FIXVALUE_PARA+ 0xC0,  0x8250,  4,  ECP_MULTIPARA_LEN},
		{FIXVALUE_PARA+ 0xC4,  0x8251,  4,  ECP_MULTIPARA_LEN},
		{FIXVALUE_PARA+ 0xC8,  0x8252,  4,  ECP_MULTIPARA_LEN},
		{FIXVALUE_PARA+ 0xCC,  0x8253,  4,  ECP_MULTIPARA_LEN},
		{FIXVALUE_PARA+ 0xD0,  0x8254,  4,  ECP_MULTIPARA_LEN},
		{FIXVALUE_PARA+ 0xD4,  0x8255,  4,  ECP_MULTIPARA_LEN},
		{FIXVALUE_PARA+ 0xD8,  0x8256,  4,  ECP_MULTIPARA_LEN},
		{FIXVALUE_PARA+ 0xDC,  0x8257,  4,  ECP_MULTIPARA_LEN},
		{FIXVALUE_PARA+ 0xE0,  0x8258,  4,  ECP_MULTIPARA_LEN},
		{FIXVALUE_PARA+ 0xE4,  0x8259,  4,  ECP_MULTIPARA_LEN},
		{FIXVALUE_PARA+ 0xE8,  0x825A,  4,  ECP_MULTIPARA_LEN},
		{FIXVALUE_PARA+ 0xEC,  0x825B,  4,  ECP_MULTIPARA_LEN},
		{FIXVALUE_PARA+ 0xF0,  0x825C,  4,  ECP_MULTIPARA_LEN},
		{FIXVALUE_PARA+ 0xF4,  0x825D,  4,  ECP_MULTIPARA_LEN},
		{FIXVALUE_PARA+ 0xF8,  0x825E,  4,  ECP_MULTIPARA_LEN},
		{FIXVALUE_PARA+ 0xFC,  0x825F,  4,  ECP_MULTIPARA_LEN},
		{FIXVALUE_PARA+ 0x100,  0x8260,  4,  ECP_MULTIPARA_LEN},
		{FIXVALUE_PARA+ 0x104,  0x8261,  4,  ECP_MULTIPARA_LEN},
		{FIXVALUE_PARA+ 0x108,  0x8262,  4,  ECP_MULTIPARA_LEN},
		{FIXVALUE_PARA+ 0x10C,  0x8263,  4,  ECP_MULTIPARA_LEN},
		{FIXVALUE_PARA+ 0x110,  0x8264,  4,  ECP_MULTIPARA_LEN},
		{FIXVALUE_PARA+ 0x114,  0x8265,  4,  ECP_MULTIPARA_LEN},
		{FIXVALUE_PARA+ 0x118,  0x8266,  4,  ECP_MULTIPARA_LEN},
		{FIXVALUE_PARA+ 0x11C,  0x8267,  4,  ECP_MULTIPARA_LEN},
		{FIXVALUE_PARA+ 0x120,  0x8268,  4,  ECP_MULTIPARA_LEN},
		{FIXVALUE_PARA+ 0x124,  0x8269,  4,  ECP_MULTIPARA_LEN},
		{FIXVALUE_PARA+ 0x128,  0x826A,  4,  ECP_MULTIPARA_LEN},
		{FIXVALUE_PARA+ 0x12C,  0x826B,  4,  ECP_MULTIPARA_LEN},
		{FIXVALUE_PARA+ 0x130,  0x826C,  4,  ECP_MULTIPARA_LEN},
		{FIXVALUE_PARA+ 0x134,  0x826D,  4,  ECP_MULTIPARA_LEN},
		{FIXVALUE_PARA+ 0x138,  0x826E,  4,  ECP_MULTIPARA_LEN},
		{FIXVALUE_PARA+ 0x13C,  0x826F,  4,  ECP_MULTIPARA_LEN},
		{FIXVALUE_PARA+ 0x140,  0x8270,  4,  ECP_MULTIPARA_LEN},
		{FIXVALUE_PARA+ 0x144,  0x8271,  4,  ECP_MULTIPARA_LEN},
		{FIXVALUE_PARA+ 0x148,  0x8272,  4,  ECP_MULTIPARA_LEN},
		{FIXVALUE_PARA+ 0x14C,  0x8273,  4,  ECP_MULTIPARA_LEN},
		{FIXVALUE_PARA+ 0x150,  0x8274,  4,  ECP_MULTIPARA_LEN},
		{FIXVALUE_PARA+ 0x154,  0x8275,  4,  ECP_MULTIPARA_LEN},
		{FIXVALUE_PARA+ 0x158,  0x8276,  4,  ECP_MULTIPARA_LEN},
		{FIXVALUE_PARA+ 0x15C,  0x8277,  4,  ECP_MULTIPARA_LEN},
		{FIXVALUE_PARA+ 0x160,  0x8278,  4,  ECP_MULTIPARA_LEN},
		{FIXVALUE_PARA+ 0x164,  0x8279,  4,  ECP_MULTIPARA_LEN},
		{FIXVALUE_PARA+ 0x168,  0x827A,  4,  ECP_MULTIPARA_LEN},
		{FIXVALUE_PARA+ 0x16C,  0x827B,  4,  ECP_MULTIPARA_LEN},
		{FIXVALUE_PARA+ 0x170,  0x827C,  4,  ECP_MULTIPARA_LEN},
		{FIXVALUE_PARA+ 0x174,  0x827D,  4,  ECP_MULTIPARA_LEN},
		{FIXVALUE_PARA+ 0x178,  0x827E,  4,  ECP_MULTIPARA_LEN},
		{FIXVALUE_PARA+ 0x17C,  0x827F,  4,  ECP_MULTIPARA_LEN},
};
/************************************************************!
*Function:
*Description:
*Input:
*Output: null
*Return: null
*************************************************************/
void App_Send_Data(ECPFRAME *EF)
{
	switch (EF->REQ.EF.VF.ASDU.TI)
	{
		case ECP_ALL_CALL:  //����
			App_Send_AllCall(EF);
			break;

		case ECP_TIMING:   //Уʱͬ��
			App_Protocol_Timing(EF);
			break;

		case ECP_TEST_LINK: //������·
			App_Send_Test_Link(EF);
			break;

		case ECP_RESET_PROCESS: //��λ����
			App_Reset_Zizhan_Process(EF);
			break;

		case ECP_GET_DELAY:
			App_Get_Delay(EF);
			break;

		case ECP_CALL_DIRFILE:
			App_Call_DirFile(EF);
			break;

		case ECP_REQUEST_FILE:
			App_Request_File(EF);
			break;

		case ECP_CALL_FILEDIR:
			App_Call_FileDir(EF);
			break;

		case ECP_SET_PARA:
			App_Set_Para(EF);
			break;

		case ECP_READ_DATA:
			App_Read_Data(EF);
			break;

		case ECP_READ_MULTIPARA:
			App_Read_MultiPara(EF);
			break;

		case ECP_REMOTE_CONTROL:
			App_Remote_Control(EF);
			break;

		case ECP_FILE_ACK:
			App_Send_FileEnd(EF);
			break;

		case ECP_SWITCH_FIXED_AREA:
			App_Switch_Fixed_Area(EF);
			break;

		case READ_FIXED_AREA:
			App_Read_Fixed_Area(EF);
			break;

		case ECP_READ_SAFE_INFO:
			App_Read_Safe_Info(EF);
			break;

		case ECP_AUTHENTICATION:
			App_Authentication(EF);
			break;

		case ECP_PUBLIC_KEY_VERIFICATION:
			App_Public_Key_Verification(EF);
			break;

		case ECP_PUBLIC_KEY_UPDATE:
			App_Public_Key_Update(EF);
			break;

		case ECP_SYMMETRIC_KEY_UPDATE:
			App_Symmetric_key_Update(EF);
			break;

		case ECP_KEY_CONSULT:
			App_Key_Consult(EF);
			break;

		case ECP_GET_RANDOM:
			App_Get_Random(EF);
			break;

		default:
			break;
	}
}
/************************************************************!
*Function:
*Description:
*Input:
*Output: null
*Return: null
*************************************************************/
void App_Send_AllCall(ECPFRAME *EF)
{
	uint8_t lens;
	uint8_t priority,sn;

	for(uint8_t i=0;i<4;i++)
	{
//		if(EF->INITRESET==true)
			priority=2;   //��ʼ������
//		else
//			priority=5;   //�ǳ�ʼ������

		sn=Req_Empty_ResFrame(EF,priority);

		EF->RES[priority].ETQ[sn].EF.VF.CTRL.DATA=0xD3;

		//DEBUG_PRINT_NISR("KKNSDKK","<----- ���뵽��ǰ��֡��� ",sn);

		if(i==0) //����ȷ��
		{
			//DEBUG_PRINT_NISR("KKNSKK","<----- ���ٵ�һ֡ ");

			EF->RES[priority].ETQ[sn].EF.VF.ASDU.TI=EF->REQ.EF.VF.ASDU.TI;
			EF->RES[priority].ETQ[sn].EF.VF.ASDU.VSQ=EF->REQ.EF.VF.ASDU.VSQ;
			EF->RES[priority].ETQ[sn].EF.VF.ASDU.COT.U16=EF->REQ.EF.VF.ASDU.COT.U16+1; //����ȷ��
			EF->RES[priority].ETQ[sn].EF.VF.ASDU.MSGADDR.U16=EF->REQ.EF.VF.ASDU.MSGADDR.U16;
			EF->RES[priority].ETQ[sn].EF.VF.ASDU.MSG[0]=EF->REQ.EF.VF.ASDU.MSG[0];

			Fill_Ecp_Frame(EF,VAR_FRAME,priority,sn,1);
		}

		if(i==1) //ң���ϱ�
		{
			//DEBUG_PRINT_NISR("KKNSKK","<----- ���ٵڶ�֡ ");

			EF->RES[priority].ETQ[sn].EF.VF.ASDU.TI=1;
			EF->RES[priority].ETQ[sn].EF.VF.ASDU.COT.U16=20; //��Ӧվ�ٻ�

			lens=Get_AllCall_Yx(EF->RES[priority].ETQ[sn].EF.DATA+13);
			EF->RES[priority].ETQ[sn].EF.VF.ASDU.VSQ=0x80+lens;

			#ifdef ESAMC_FUNCTION_CTRL
			Fill_Ecp_Frame(EF,VAR_FRAME,priority,sn,lens);
			#else
			Fill_Ecp_Frame(EF,ESM_FRAME,priority,sn,lens);
			#endif
		}

		if(i==2) //ң���ϱ�
		{

			//DEBUG_PRINT_NISR("KKNSKK","<----- ���ٵ���֡ ");

			EF->RES[priority].ETQ[sn].EF.VF.ASDU.TI=9;
			EF->RES[priority].ETQ[sn].EF.VF.ASDU.COT.U16=20; //��Ӧվ�ٻ�

			lens=Get_AllCall_Yc(EF->RES[priority].ETQ[sn].EF.DATA+13); //����Ϣ���ַ��ʼ��������
			EF->RES[priority].ETQ[sn].EF.VF.ASDU.VSQ=0x80+(lens/3);

			#ifdef ESAMC_FUNCTION_CTRL
			Fill_Ecp_Frame(EF,VAR_FRAME,priority,sn,lens);
			#else
			Fill_Ecp_Frame(EF,ESM_FRAME,priority,sn,lens);
			#endif
		}

		if(i==3) //���ٻ�����
		{
			//DEBUG_PRINT_NISR("KKNSKK","<----- ���ٵ���֡ ");

			EF->RES[priority].ETQ[sn].EF.VF.ASDU.TI=100;
			EF->RES[priority].ETQ[sn].EF.VF.ASDU.VSQ=1;
			EF->RES[priority].ETQ[sn].EF.VF.ASDU.COT.U16=10; //������ֹ
			EF->RES[priority].ETQ[sn].EF.VF.ASDU.MSGADDR.U16=0;

			EF->RES[priority].ETQ[sn].EF.VF.ASDU.MSG[0]=20;

			Fill_Ecp_Frame(EF,VAR_FRAME,priority,sn,1);
		}
	}

	EF->ESMSTATE=true;     //������ɲſ��Խ���ESAM�������ݵĴ���
	EF->INITRESET=false;   //��ʼ�����ٱ�־
}
/************************************************************!
*Function:
*Description:
*Input:
*Output: null
*Return: null
*************************************************************/
bool App_Remote_Control(ECPFRAME *EF)
{
	P101YK YK;
	uint8_t priority,sn;    //Ӧ��֡��֡���

	priority=3; //������õ�Ӧ��֡
	sn=Req_Empty_ResFrame(EF,priority);

	EF->RES[priority].ETQ[sn].EF.VF.CTRL.DATA=0xD3;
	EF->RES[priority].ETQ[sn].EF.VF.ASDU.TI=EF->REQ.EF.VF.ASDU.TI;
	EF->RES[priority].ETQ[sn].EF.VF.ASDU.VSQ=EF->REQ.EF.VF.ASDU.VSQ;
	EF->RES[priority].ETQ[sn].EF.VF.ASDU.MSGADDR.U16=EF->REQ.EF.VF.ASDU.MSGADDR.U16;
	EF->RES[priority].ETQ[sn].EF.VF.ASDU.MSG[0]=EF->REQ.EF.VF.ASDU.MSG[0];

	if(!(EF->RES[priority].ETQ[sn].EF.VF.ASDU.TI==45||EF->RES[priority].ETQ[sn].EF.VF.ASDU.COT.U16==6||EF->RES[priority].ETQ[sn].EF.VF.ASDU.COT.U16==8)) //���Ϸ�������֡����
	{
		EF->RES[priority].ETQ[sn].EF.VF.ASDU.COT.U16=10; //������ֹ

		Fill_Ecp_Frame(EF,VAR_FRAME,priority,sn,1);

		return false;
	}

	YK.TIMING=gUNIXTIME.UNIX;
	YK.TYPE=EF->REQ.EF.VF.ASDU.TI;
	YK.MSGADDR.U16=EF->REQ.EF.VF.ASDU.MSGADDR.U16;
	YK.COT.U16=EF->REQ.EF.VF.ASDU.COT.U16;
	YK.SCO.DATA=EF->REQ.EF.VF.ASDU.MSG[0];

	if(EF->YK.STATE==YKINIT)   //��ʼ��״̬
	{
		if(YK.SCO.SE==0) //ִ��     //���㷨һ���ݲ��ж�MSGADDR����ȷ��
		{
			EF->RES[priority].ETQ[sn].EF.VF.ASDU.COT.U16=10; //������ֹ

			Fill_Ecp_Frame(EF,VAR_FRAME,priority,sn,1);

			#ifdef PRINT_ECP_YK_DEBUG
			DEBUG_PRINT_NISR("KKNSKK","<----- ң�ص�ǰΪ��ʼ��״̬,ң���������! ----->");
			#endif

			return false;
		}

		if(EF->REQ.EF.VF.ASDU.COT.U16==6) //ѡ��
		{
			EF->YK.STATE=YKSELECT;

			memcpy(EF->YK.DATA,YK.DATA,19);

			EF->RES[priority].ETQ[sn].EF.VF.ASDU.COT.U16=7; //����ȷ��

			Fill_Ecp_Frame(EF,VAR_FRAME,priority,sn,1);

			Yk_Data_Record(YK); //��¼YK����

			#ifdef PRINT_ECP_YK_DEBUG
			DEBUG_PRINT_NISR("KKNSKK","<----- ���յ�ң��ѡ������,ң�����л�Ϊѡ��״̬! ----->");
			#endif

			return true;
		}
	}

	if(EF->YK.STATE==YKSELECT)  //ѡ��״̬
	{
		if(YK.SCO.SE==1) //ѡ��
		{
			EF->YK.STATE=YKINIT;
			EF->RES[priority].ETQ[sn].EF.VF.ASDU.COT.U16=10; //������ֹ

			Fill_Ecp_Frame(EF,VAR_FRAME,priority,sn,1);

			#ifdef PRINT_ECP_YK_DEBUG
			DEBUG_PRINT_NISR("KKNSKK","<----- ң�ص�ǰΪѡ��״̬,ң���������! ----->");
			#endif

			return true;
		}

		if(EF->REQ.EF.VF.ASDU.COT.U16==8&&YK.SCO.SCS==0) //ֹͣ����
		{
			EF->YK.STATE=YKINIT;

			if((gUNIXTIME.UNIX-EF->YK.TIMING)>ECP_YK_TIME)
			{
				EF->RES[priority].ETQ[sn].EF.VF.ASDU.COT.U16=10; //������ֹ

				Fill_Ecp_Frame(EF,VAR_FRAME,priority,sn,1);

				#ifdef PRINT_ECP_YK_DEBUG
				DEBUG_PRINT_NISR("KKNSKK","<----- ң�ز���ʱ�䳬ʱ!���л�Ϊ��ʼ��״̬! ----->");
				#endif

				return false;
			}

			Yk_Data_Record(YK); //��¼YK����

			#ifdef PRINT_ECP_YK_DEBUG
			DEBUG_PRINT_NISR("KKNSKK","<----- ���յ�ң����ֹ����,ң�����л�Ϊ��ʼ��״̬! ----->");
			#endif

			return true;
		}

		if(EF->REQ.EF.VF.ASDU.COT.U16==6&&YK.SCO.SCS==0) //ִ������
		{
			EF->YK.STATE=YKINIT;

			if((gUNIXTIME.UNIX-EF->YK.TIMING)>ECP_YK_TIME)
			{
				EF->RES[priority].ETQ[sn].EF.VF.ASDU.COT.U16=10; //������ֹ

				Fill_Ecp_Frame(EF,VAR_FRAME,priority,sn,1);

				#ifdef PRINT_ECP_YK_DEBUG
				DEBUG_PRINT_NISR("KKNSKK","<----- ң�ز���ʱ�䳬ʱ!���л�Ϊ��ʼ��״̬! ----->");
				#endif

				return false;
			}

			Yk_Data_Record(YK); //��¼YK����

			if(EF->YK.MSGADDR.U8[0]<=3) //�ֶ�����¼��
			{

				Get_Sys_Time(&gUNIXTIME);

				Trigger_Start_Call_Wave(EF->YK.MSGADDR.U8[0]-1,gUNIXTIME.DATA);

				#ifdef PRINT_ECP_YK_DEBUG
				DEBUG_PRINT_NISR("KKNSKK","<----- ���ֶ��·�����¼��֡ ----->");
				#endif
			}

			if(EF->YK.MSGADDR.U8[0]>=0x11)
			{
				if(EF->YK.SCO.SCS==0)
					Fill_Icp_Frame(RADIOFRAME.CHANNEL,gSYSPARA.LINEGROUP.LINE[EF->YK.MSGADDR.U4[0].U47-1].AU[EF->YK.MSGADDR.U4[0].U03-1].ADDR,0x40,0x0D,1,1,0,0);

				if(EF->YK.SCO.SCS==1)
					Fill_Icp_Frame(RADIOFRAME.CHANNEL,gSYSPARA.LINEGROUP.LINE[EF->YK.MSGADDR.U4[0].U47-1].AU[EF->YK.MSGADDR.U4[0].U03-1].ADDR,0x40,0x08,1,1,0,0);
			}

			#ifdef PRINT_ECP_YK_DEBUG
			DEBUG_PRINT_NISR("KKNSKK","<----- ң��������ִ��! ----->");
			#endif
		}

		EF->RES[priority].ETQ[sn].EF.VF.ASDU.COT.U16=EF->REQ.EF.VF.ASDU.COT.U16+1; // ����ȷ�ϻ���ֹͣ����

		Fill_Ecp_Frame(EF,VAR_FRAME,priority,sn,1);

		priority=3; //������õ�Ӧ��֡
		sn=Req_Empty_ResFrame(EF,priority);

		EF->RES[priority].ETQ[sn].EF.VF.CTRL.DATA=0xD3;
		EF->RES[priority].ETQ[sn].EF.VF.ASDU.TI=EF->REQ.EF.VF.ASDU.TI;
		EF->RES[priority].ETQ[sn].EF.VF.ASDU.VSQ=EF->REQ.EF.VF.ASDU.VSQ;

		EF->RES[priority].ETQ[sn].EF.VF.ASDU.COT.U16=10;
		EF->RES[priority].ETQ[sn].EF.VF.ASDU.MSGADDR.U16=EF->REQ.EF.VF.ASDU.MSGADDR.U16;
		EF->RES[priority].ETQ[sn].EF.VF.ASDU.MSG[0]=EF->REQ.EF.VF.ASDU.MSG[0];

		Fill_Ecp_Frame(EF,VAR_FRAME,priority,sn,1);
	}

	return true;
}
/************************************************************!
*Function:
*Description:
*Input:
*Output: null
*Return: null
*************************************************************/
bool App_Protocol_Timing(ECPFRAME *EF)
{
	uint8_t priority,sn;

	if(!(EF->REQ.EF.VF.ASDU.COT.U16==5||EF->REQ.EF.VF.ASDU.COT.U16==6))
		return false;

	if(EF->REQ.EF.VF.ASDU.COT.U16==6) //ʱ��Уʱ
	{
		if(Is_Valid_101Clock(EF->REQ.EF.VF.ASDU.MSG,7)==true) //У��ʱ�Ӹ�ʽ
		{
			if(gECPPARA.GPS_TIMING_MODE==0) //��ԼУʱ����
			{
				P101Time2R8025TRTCTime(EF->REQ.EF.VF.ASDU.MSG,7); //У׼8025T��RTC��CNT

				gUNIXTIME.UNIX=R8025TRTCTime2UnixTime();

				#ifdef PRINT_ECP_TIMING_DEBUG
				DEBUG_PRINT_NISR("KKNSKK","<----- �����ڹ�ԼУʱģʽ");
				#endif
			}

			#ifdef PRINT_ECP_TIMING_DEBUG
			DEBUG_PRINT_NISR("KKNSEKK","<----- �ѽ�����վ�Ĺ�ԼУʱ,Уʱʱ��: ",EF->REQ.EF.VF.ASDU.MSG);
			#endif
		}
	}

	priority=7;
	sn=Req_Empty_ResFrame(EF,priority); //������õ�Ӧ��֡

	EF->RES[priority].ETQ[sn].EF.VF.CTRL.DATA=0xD3;

	EF->RES[priority].ETQ[sn].EF.VF.ASDU.TI=EF->REQ.EF.VF.ASDU.TI;
	EF->RES[priority].ETQ[sn].EF.VF.ASDU.VSQ=EF->REQ.EF.VF.ASDU.VSQ;

	if(EF->REQ.EF.VF.ASDU.COT.U16==5) //ʱ��ͬ��
		EF->RES[priority].ETQ[sn].EF.VF.ASDU.COT.U16=EF->REQ.EF.VF.ASDU.COT.U16;
	if(EF->REQ.EF.VF.ASDU.COT.U16==6) //ʱ�Ӷ�ȡ
		EF->RES[priority].ETQ[sn].EF.VF.ASDU.COT.U16=EF->REQ.EF.VF.ASDU.COT.U16+1;

	EF->RES[priority].ETQ[sn].EF.VF.ASDU.MSGADDR.U16=EF->REQ.EF.VF.ASDU.MSGADDR.U16;

	NowTime2P101Time(EF->RES[priority].ETQ[sn].EF.VF.ASDU.MSG,7);

	Fill_Ecp_Frame(EF,VAR_FRAME,priority,sn,7);

	#ifdef PRINT_ECP_TIMING_DEBUG
	DEBUG_PRINT_NISR("KKNSEKK","<----- �㼯��Ԫ���ϱ���վʱ��: ",EF->RES[priority].ETQ[sn].EF.VF.ASDU.MSG);
	#endif

	return true;
}
/************************************************************!
*Function:
*Description:
*Input:
*Output: null
*Return: null
*************************************************************/
void App_Send_Test_Link(ECPFRAME *EF)
{
	uint8_t priority,sn;

	priority=2;
	sn=Req_Empty_ResFrame(EF,priority); //������õ�Ӧ��֡

	EF->RES[priority].ETQ[sn].EF.VF.CTRL.DATA=0xD3;
	EF->RES[priority].ETQ[sn].EF.VF.ASDU.TI=EF->REQ.EF.VF.ASDU.TI;
	EF->RES[priority].ETQ[sn].EF.VF.ASDU.VSQ=EF->REQ.EF.VF.ASDU.VSQ;
	EF->RES[priority].ETQ[sn].EF.VF.ASDU.COT.U16=EF->REQ.EF.VF.ASDU.COT.U16+1; //����ȷ��
	EF->RES[priority].ETQ[sn].EF.VF.ASDU.MSGADDR.U16=EF->REQ.EF.VF.ASDU.MSGADDR.U16;
	memcpy(EF->RES[priority].ETQ[sn].EF.VF.ASDU.MSG,EF->REQ.EF.VF.ASDU.MSG,2); //���Ծ��� 55AA

	Fill_Ecp_Frame(EF,VAR_FRAME,priority,sn,2);
}
/************************************************************!
*Function:
*Description:
*Input:
*Output: null
*Return: null
*************************************************************/
void App_Reset_Zizhan_Process(ECPFRAME *EF)
{
	uint8_t priority,sn;

	priority=9;
	sn=Req_Empty_ResFrame(EF,priority); //������õ�Ӧ��֡

	EF->RES[priority].ETQ[sn].EF.VF.CTRL.DATA=0xD3;
	EF->RES[priority].ETQ[sn].EF.VF.ASDU.TI=EF->REQ.EF.VF.ASDU.TI;
	EF->RES[priority].ETQ[sn].EF.VF.ASDU.VSQ=EF->REQ.EF.VF.ASDU.VSQ;
	EF->RES[priority].ETQ[sn].EF.VF.ASDU.COT.U16=EF->REQ.EF.VF.ASDU.COT.U16+1;
	EF->RES[priority].ETQ[sn].EF.VF.ASDU.MSG[0]=0x02;

	Fill_Ecp_Frame(EF,VAR_FRAME,priority,sn,1);

	vTaskDelay(pdMS_TO_TICKS(5000)); //��Լ3��

	SCB->AIRCR=0x05FA0004;  //M3�ں˸�λ����
}
/************************************************************!
*Function:
*Description:
*Input:
*Output: null
*Return: null
*************************************************************/
void App_Get_Delay(ECPFRAME *EF)
{
	uint32_t CNT;
	DOUBLEBYTE DB,DB1;
	uint8_t priority,sn;

	if(EF->REQ.EF.VF.ASDU.COT.U16==6)
	{
		memcpy(DB.U8,EF->REQ.EF.VF.ASDU.MSG,2);  //����T1ʱ��

		CNT=RTC->CNT;

		priority=9;
		sn=Req_Empty_ResFrame(EF,priority); //������õ�Ӧ��֡

		EF->RES[priority].ETQ[sn].EF.VF.CTRL.DATA=0xD3;
		EF->RES[priority].ETQ[sn].EF.VF.ASDU.TI=EF->REQ.EF.VF.ASDU.TI;
		EF->RES[priority].ETQ[sn].EF.VF.ASDU.VSQ=EF->REQ.EF.VF.ASDU.VSQ;
		EF->RES[priority].ETQ[sn].EF.VF.ASDU.COT.U16=EF->REQ.EF.VF.ASDU.COT.U16+1;
		EF->RES[priority].ETQ[sn].EF.VF.ASDU.MSGADDR.U16=EF->REQ.EF.VF.ASDU.MSGADDR.U16;

		CNT=(32768+RTC->CNT-CNT)%32768;

		CNT=CNT*1000/32768;

		DB1.U16=CNT;

		DB.U16+=DB1.U16;

		memcpy(EF->RES[priority].ETQ[sn].EF.VF.ASDU.MSG,DB.U8,2);

		Fill_Ecp_Frame(EF,VAR_FRAME,priority,sn,2);
	}
}
/************************************************************!
*Function:
*Description:
*Input:
*Output: null
*Return: null
*************************************************************/
void App_Call_DirFile(ECPFRAME *EF)
{
	switch(EF->REQ.EF.VF.ASDU.COT.U16)
	{
		case ECP_CALL_DIR:
			App_Call_Dir(EF);
			break;

		case ECP_CALL_FILE:
			App_Call_File(EF);
			break;
	}
}
/************************************************************!
*Function:
*Description:
*Input:
*Output: null
*Return: null
*************************************************************/
void App_Call_Dir(ECPFRAME *EF)
{
	uint8_t priority,sn; //Ӧ��֡��֡���

	EF->FILE.ID=(((uint16_t)EF->REQ.EF.VF.ASDU.MSG[1])<<8)+EF->REQ.EF.VF.ASDU.MSG[0];

	Locate_File_Info(EF);

	priority=10;
	sn=Req_Empty_ResFrame(EF,priority); //������õ�Ӧ��֡

	EF->RES[priority].ETQ[sn].EF.VF.CTRL.DATA=0xD3;
	EF->RES[priority].ETQ[sn].EF.VF.ASDU.TI=126;
	EF->RES[priority].ETQ[sn].EF.VF.ASDU.VSQ=1;
	EF->RES[priority].ETQ[sn].EF.VF.ASDU.COT.U16=5;
	EF->RES[priority].ETQ[sn].EF.VF.ASDU.MSGADDR.U16=EF->FILE.MSGADDR.U16;
	memcpy(EF->RES[priority].ETQ[sn].EF.VF.ASDU.MSG,&EF->FILE.ID,sizeof(uint16_t)); //�ļ�����
	memcpy(EF->RES[priority].ETQ[sn].EF.VF.ASDU.MSG+2,&EF->FILE.LENS,sizeof(uint16_t)); //�ļ�����
	EF->RES[priority].ETQ[sn].EF.VF.ASDU.MSG[4]=0;
	EF->RES[priority].ETQ[sn].EF.VF.ASDU.MSG[5]=0; //SOF���壬�ο����°�101
	memcpy(EF->RES[priority].ETQ[sn].EF.VF.ASDU.MSG+6,EF->FILE.TIME,7);

	Fill_Ecp_Frame(EF,VAR_FRAME,priority,sn,13);
}
/************************************************************!
*Function:
*Description:
*Input:
*Output: null
*Return: null
*************************************************************/
void App_Call_2017Dir(ECPFRAME *EF)
{
	uint8_t priority,sn; //Ӧ��֡��֡���

	EF->FILE.ID=(((uint16_t)EF->REQ.EF.VF.ASDU.MSG[1])<<8)+EF->REQ.EF.VF.ASDU.MSG[0];

	Locate_File_Info(EF);

	priority=10;
	sn=Req_Empty_ResFrame(EF,priority); //������õ�Ӧ��֡

	EF->RES[priority].ETQ[sn].EF.VF.CTRL.DATA=0xD3;
	EF->RES[priority].ETQ[sn].EF.VF.ASDU.TI=126;
	EF->RES[priority].ETQ[sn].EF.VF.ASDU.VSQ=1;
	EF->RES[priority].ETQ[sn].EF.VF.ASDU.COT.U16=5;
	EF->RES[priority].ETQ[sn].EF.VF.ASDU.MSGADDR.U16=EF->FILE.MSGADDR.U16;
	memcpy(EF->RES[priority].ETQ[sn].EF.VF.ASDU.MSG,&EF->FILE.ID,sizeof(uint16_t)); //�ļ�����
	memcpy(EF->RES[priority].ETQ[sn].EF.VF.ASDU.MSG+2,&EF->FILE.LENS,sizeof(uint16_t)); //�ļ�����
	EF->RES[priority].ETQ[sn].EF.VF.ASDU.MSG[4]=0;
	EF->RES[priority].ETQ[sn].EF.VF.ASDU.MSG[5]=0; //SOF���壬�ο����°�101
	memcpy(EF->RES[priority].ETQ[sn].EF.VF.ASDU.MSG+6,EF->FILE.TIME,7);

	Fill_Ecp_Frame(EF,VAR_FRAME,priority,sn,13);
}
/************************************************************!
*Function:
*Description:
*Input:
*Output: null
*Return: null
*************************************************************/
bool App_Call_File(ECPFRAME *EF)
{
	SINGLEBYTE SCQ;
	uint8_t section;
	DOUBLEBYTE FILEID;

	memcpy(FILEID.U8,EF->REQ.EF.VF.ASDU.MSG,2);
	EF->FILE.ID=FILEID.U16;
	section=EF->REQ.EF.VF.ASDU.MSG[2];

	SCQ.DATA=EF->REQ.EF.VF.ASDU.MSG[3];

	if(SCQ.U03==1)
	{
		EF->FILE.ID=FILEID.U16;
		EF->FILE.SECTION=section;

		Locate_File_Info(EF);

		if(EF->FILE.LENS>0)
			App_File_Ready(EF);
		else
			App_Send_NoAck(EF);

		return true;
	}

	if(SCQ.U03==2)
	{
		if((!(EF->FILE.ID==FILEID.U16&&EF->FILE.SECTION==section))||EF->FILE.LENS==0)
			App_Send_NoAck(EF);
		else
			App_Section_Ready(EF);

		return true;
	}

	if(SCQ.U03==6)
	{
		if(!(EF->FILE.ID==FILEID.U16&&EF->FILE.SECTION==section))
			App_Send_NoAck(EF);
		else
			EF->FILE.STATE=1; //�ļ���ʼ����

		return true;
	}

	App_Send_NoAck(EF);

	return true;
}
/************************************************************!
*Function:
*Description:
*Input:
*Output: null
*Return: null
*************************************************************/
void App_File_Ready(ECPFRAME *EF)
{
	uint8_t priority,sn; //Ӧ��֡��֡���

	priority=10;
	sn=Req_Empty_ResFrame(EF,priority); //������õ�Ӧ��֡

	EF->RES[priority].ETQ[sn].EF.VF.CTRL.DATA=0xD3;
	EF->RES[priority].ETQ[sn].EF.VF.ASDU.TI=122;
	EF->RES[priority].ETQ[sn].EF.VF.ASDU.VSQ=1;
	EF->RES[priority].ETQ[sn].EF.VF.ASDU.COT.U16=13;
	EF->RES[priority].ETQ[sn].EF.VF.ASDU.MSGADDR.U16=EF->FILE.MSGADDR.U16;
	memcpy(EF->RES[priority].ETQ[sn].EF.VF.ASDU.MSG,&EF->FILE.ID,sizeof(uint16_t));
	memcpy(EF->RES[priority].ETQ[sn].EF.VF.ASDU.MSG+2,&EF->FILE.LENS,sizeof(uint16_t));
	EF->RES[priority].ETQ[sn].EF.VF.ASDU.MSG[4]=0;
	EF->RES[priority].ETQ[sn].EF.VF.ASDU.MSG[5]=128; //FRQ�޶���

	Fill_Ecp_Frame(EF,VAR_FRAME,priority,sn,6);
}
/************************************************************!
*Function:
*Description:
*Input:
*Output: null
*Return: null
*************************************************************/
void App_Request_File(ECPFRAME *EF)
{
	uint8_t section;
	DOUBLEBYTE FILEID;

	memcpy(FILEID.U8,EF->REQ.EF.VF.ASDU.MSG,2);
	section=EF->REQ.EF.VF.ASDU.MSG[2];

	if(!(EF->FILE.ID==FILEID.U16&&EF->FILE.SECTION==section))
		App_Send_NoAck(EF);
	else
		App_Section_Ready(EF);
}
/************************************************************!
*Function:
*Description:
*Input:
*Output: null
*Return: null
*************************************************************/
void App_Call_FileDir(ECPFRAME *EF)
{
	switch(EF->REQ.EF.VF.ASDU.COT.U16)
	{
		case ECP_CALL_DIR:
			App_Call_2017Dir(EF);
			break;

		default:
			break;
	}
}
/************************************************************!
*Function:
*Description:
*Input:
*Output: null
*Return: null
*************************************************************/
void App_Section_Ready(ECPFRAME *EF)
{
	uint8_t priority,sn; //Ӧ��֡��֡���

	priority=10;
	sn=Req_Empty_ResFrame(EF,priority); //������õ�Ӧ��֡

	EF->RES[priority].ETQ[sn].EF.VF.CTRL.DATA=0xD3;
	EF->RES[priority].ETQ[sn].EF.VF.ASDU.TI=121;
	EF->RES[priority].ETQ[sn].EF.VF.ASDU.VSQ=1;
	EF->RES[priority].ETQ[sn].EF.VF.ASDU.COT.U16=13;

	EF->RES[priority].ETQ[sn].EF.VF.ASDU.MSGADDR.U16=EF->FILE.MSGADDR.U16;
	memcpy(EF->RES[priority].ETQ[sn].EF.VF.ASDU.MSG,&EF->FILE.ID,sizeof(uint16_t));
	EF->RES[priority].ETQ[sn].EF.VF.ASDU.MSG[2]=EF->FILE.SECTION;
	memcpy(EF->RES[priority].ETQ[sn].EF.VF.ASDU.MSG+3,&EF->FILE.LENS,sizeof(uint16_t));
	EF->RES[priority].ETQ[sn].EF.VF.ASDU.MSG[5]=0;
	EF->RES[priority].ETQ[sn].EF.VF.ASDU.MSG[6]=0; //SRQ�޶���

	Fill_Ecp_Frame(EF,VAR_FRAME,priority,sn,7);
}
/************************************************************!
*Function:
*Description:
*Input:
*Output: null
*Return: null
*************************************************************/
void App_Send_FileEnd(ECPFRAME *EF)
{
	SINGLEBYTE AFQ;
	DOUBLEBYTE FILEID;

	EF->FILE.STATE=0;

	memcpy(FILEID.U8,EF->REQ.EF.VF.ASDU.MSG,2);
	AFQ.DATA=EF->REQ.EF.VF.ASDU.MSG[3];

	if(AFQ.U03==1)
		App_Send_Last_Section(EF);
	else
		App_Send_NoAck(EF);
}
/************************************************************!
*Function:
*Description:
*Input:
*Output: null
*Return: null
*************************************************************/
void App_Read_Fixed_Area(ECPFRAME *EF)
{
	uint8_t priority,sn; //Ӧ��֡��֡���

	priority=9;
	sn=Req_Empty_ResFrame(EF,priority); //������õ�Ӧ��֡

	EF->RES[priority].ETQ[sn].EF.VF.CTRL.DATA=0xD3;
	EF->RES[priority].ETQ[sn].EF.VF.ASDU.TI=EF->REQ.EF.VF.ASDU.TI;
	EF->RES[priority].ETQ[sn].EF.VF.ASDU.VSQ=EF->REQ.EF.VF.ASDU.VSQ;
	EF->RES[priority].ETQ[sn].EF.VF.ASDU.COT.U16=EF->REQ.EF.VF.ASDU.COT.U16+1;
	EF->RES[priority].ETQ[sn].EF.VF.ASDU.MSGADDR.U16=EF->REQ.EF.VF.ASDU.MSGADDR.U16;

	memset(EF->RES[priority].ETQ[sn].EF.VF.ASDU.MSG,0,11); //ȫ��Ϊ0

	Fill_Ecp_Frame(EF,VAR_FRAME,priority,sn,11);
}
/************************************************************!
*Function:
*Description:
*Input:
*Output: null
*Return: null
*************************************************************/
void App_Switch_Fixed_Area(ECPFRAME *EF)
{
	uint8_t priority,sn; //Ӧ��֡��֡���

	priority=9;
	sn=Req_Empty_ResFrame(EF,priority); //������õ�Ӧ��֡

	EF->RES[priority].ETQ[sn].EF.VF.CTRL.DATA=0xD3;
	EF->RES[priority].ETQ[sn].EF.VF.ASDU.TI=EF->REQ.EF.VF.ASDU.TI;
	EF->RES[priority].ETQ[sn].EF.VF.ASDU.VSQ=EF->REQ.EF.VF.ASDU.VSQ;
	EF->RES[priority].ETQ[sn].EF.VF.ASDU.COT.U16=EF->REQ.EF.VF.ASDU.COT.U16+1;
	EF->RES[priority].ETQ[sn].EF.VF.ASDU.MSGADDR.U16=EF->REQ.EF.VF.ASDU.MSGADDR.U16;

	Fill_Ecp_Frame(EF,VAR_FRAME,priority,sn,2);
}
/************************************************************!
*Function:
*Description:
*Input:
*Output: null
*Return: null
*************************************************************/
void App_Send_Last_Section(ECPFRAME *EF)
{
	uint8_t priority,sn; //Ӧ��֡��֡���

	priority=10;
	sn=Req_Empty_ResFrame(EF,priority); //������õ�Ӧ��֡

	EF->RES[priority].ETQ[sn].EF.VF.CTRL.DATA=0xD3;
	EF->RES[priority].ETQ[sn].EF.VF.ASDU.TI=123;
	EF->RES[priority].ETQ[sn].EF.VF.ASDU.VSQ=1;
	EF->RES[priority].ETQ[sn].EF.VF.ASDU.COT.U16=13;
	EF->RES[priority].ETQ[sn].EF.VF.ASDU.MSGADDR.U16=EF->FILE.MSGADDR.U16;
	memcpy(EF->RES[priority].ETQ[sn].EF.VF.ASDU.MSG,&EF->FILE.ID,sizeof(uint16_t));
	EF->RES[priority].ETQ[sn].EF.VF.ASDU.MSG[2]=EF->FILE.SECTION;
	EF->RES[priority].ETQ[sn].EF.VF.ASDU.MSG[3]=1; //LSQ�ڴ���
	EF->RES[priority].ETQ[sn].EF.VF.ASDU.MSG[4]=EF->FILE.CS;

	Fill_Ecp_Frame(EF,VAR_FRAME,priority,sn,5);
}
/************************************************************!
*Function:
*Description:
*Input:
*Output: null
*Return: null
*************************************************************/
void App_Send_Segment(ECPFRAME *EF)
{
	uint8_t priority,sn; //Ӧ��֡��֡���

	App_Send_FileHead(EF);

	for(uint32_t i=0;i<EF->FILE.SENDNUM;i++) //�����ļ�ͷ
	{
		if(EF->FILE.STATE==0)
			return;

		EF->FILE.INFONO++; //���͵Ķ����

		priority=10;
		sn=Req_Empty_ResFrame(EF,priority); //������õ�Ӧ��֡

		EF->RES[priority].ETQ[sn].EF.VF.CTRL.DATA=0xD3;
		EF->RES[priority].ETQ[sn].EF.VF.ASDU.TI=125;
		EF->RES[priority].ETQ[sn].EF.VF.ASDU.VSQ=1;
		EF->RES[priority].ETQ[sn].EF.VF.ASDU.COT.U16=13;

		EF->RES[priority].ETQ[sn].EF.VF.ASDU.MSGADDR.U16=EF->FILE.MSGADDR.U16;
		memcpy(EF->RES[priority].ETQ[sn].EF.VF.ASDU.MSG,&EF->FILE.ID,sizeof(uint16_t));

		App_Get_Segment(EF,priority,sn);

		if(EF->FILE.INFONO==EF->FILE.SENDNUM) //�ļ�������־0A
		{
			EF->FILE.CS+=0x0A;
			EF->RES[priority].ETQ[sn].EF.VF.ASDU.MSG[EF->RES[priority].ETQ[sn].EF.VF.LEN1]=0x0A;
			EF->RES[priority].ETQ[sn].EF.VF.ASDU.MSG[3]+=1;
			EF->RES[priority].ETQ[sn].EF.VF.LEN1+=1;
		}

		Fill_Ecp_Frame(EF,VAR_FRAME,priority,sn,EF->RES[priority].ETQ[sn].EF.VF.LEN1);
	}

	App_Send_Last_Segment(EF);
}
/************************************************************!
*Function:
*Description:
*Input:
*Output: null
*Return: null
*************************************************************/
void App_Send_FileHead(ECPFRAME *EF)
{
	DOUBLEBYTE DB;
	char data[100];
	uint8_t strlens;
	uint8_t priority,sn;

	priority=10;

	if(EF->FILE.ID==18) //�����ļ�
	{
		sn=Req_Empty_ResFrame(EF,priority); //������õ�Ӧ��֡

		EF->RES[priority].ETQ[sn].EF.VF.CTRL.DATA=0xD3;
		EF->RES[priority].ETQ[sn].EF.VF.ASDU.TI=125;
		EF->RES[priority].ETQ[sn].EF.VF.ASDU.VSQ=1;
		EF->RES[priority].ETQ[sn].EF.VF.ASDU.COT.U16=13;
		EF->RES[priority].ETQ[sn].EF.VF.ASDU.MSGADDR.U16=EF->FILE.MSGADDR.U16;
		memcpy(EF->RES[priority].ETQ[sn].EF.VF.ASDU.MSG,&EF->FILE.ID,sizeof(uint16_t));
		EF->RES[priority].ETQ[sn].EF.VF.ASDU.MSG[2]=1;  //LOG�Ľ����̶�Ϊ1

		strcpy(data,"FAULT_FILE,1.00\r\nCOLLECTION_UNIT,"); //33�ֽ�

		strlens=strlen(data);

		memcpy(EF->RES[priority].ETQ[sn].EF.VF.ASDU.MSG+4,data,strlens);

		memcpy(EF->RES[priority].ETQ[sn].EF.VF.ASDU.MSG+4+strlens,&EF->FILE.INFONUM,2);

		EF->RES[priority].ETQ[sn].EF.VF.ASDU.MSG[6+strlens]=0x2C;
		EF->RES[priority].ETQ[sn].EF.VF.ASDU.MSG[6+strlens+1]=0x02;
		EF->RES[priority].ETQ[sn].EF.VF.ASDU.MSG[6+strlens+2]=0x00;
		EF->RES[priority].ETQ[sn].EF.VF.ASDU.MSG[6+strlens+3]=0x0D;
		EF->RES[priority].ETQ[sn].EF.VF.ASDU.MSG[6+strlens+4]=0x0A;

		EF->RES[priority].ETQ[sn].EF.VF.ASDU.MSG[3]=strlens+7;
		EF->RES[priority].ETQ[sn].EF.VF.LEN1=EF->RES[priority].ETQ[sn].EF.VF.ASDU.MSG[3]+4;

		for(uint8_t i=0;i<EF->RES[priority].ETQ[sn].EF.VF.ASDU.MSG[3];i++)
			EF->FILE.CS+=EF->RES[priority].ETQ[sn].EF.VF.ASDU.MSG[4+i];

		Fill_Ecp_Frame(EF,VAR_FRAME,priority,sn,EF->RES[priority].ETQ[sn].EF.VF.LEN1);

		EF->FILE.STATE=2;

		EF->FILE.LENS-=FAULT_INFO_HEAD+1;
	}

	if(EF->FILE.ID==19)  //��־�ļ�
	{
		sn=Req_Empty_ResFrame(EF,priority); //������õ�Ӧ��֡

		EF->RES[priority].ETQ[sn].EF.VF.CTRL.DATA=0xD3;
		EF->RES[priority].ETQ[sn].EF.VF.ASDU.TI=125;
		EF->RES[priority].ETQ[sn].EF.VF.ASDU.VSQ=1;
		EF->RES[priority].ETQ[sn].EF.VF.ASDU.COT.U16=13;
		EF->RES[priority].ETQ[sn].EF.VF.ASDU.MSGADDR.U16=EF->FILE.MSGADDR.U16;
		memcpy(EF->RES[priority].ETQ[sn].EF.VF.ASDU.MSG,&EF->FILE.ID,sizeof(uint16_t));
		EF->RES[priority].ETQ[sn].EF.VF.ASDU.MSG[2]=1;  //LOG�Ľ����̶�Ϊ1

		strcpy(data,"LOG_FILE,1.00,COLLECTION_UNIT,"); //30�ֽ�

		strlens=strlen(data);

		memcpy(EF->RES[priority].ETQ[sn].EF.VF.ASDU.MSG+4,data,strlens);
		memcpy(EF->RES[priority].ETQ[sn].EF.VF.ASDU.MSG+4+strlens,&EF->FILE.INFONUM,2);

		EF->RES[priority].ETQ[sn].EF.VF.ASDU.MSG[6+strlens]=0x0D;
		EF->RES[priority].ETQ[sn].EF.VF.ASDU.MSG[6+strlens+1]=0x0A;

		EF->RES[priority].ETQ[sn].EF.VF.ASDU.MSG[3]=strlens+4;

		EF->RES[priority].ETQ[sn].EF.VF.LEN1=EF->RES[priority].ETQ[sn].EF.VF.ASDU.MSG[3]+4;

		for(uint8_t i=0;i<EF->RES[priority].ETQ[sn].EF.VF.ASDU.MSG[3];i++)
			EF->FILE.CS+=EF->RES[priority].ETQ[sn].EF.VF.ASDU.MSG[4+i];

		Fill_Ecp_Frame(EF,VAR_FRAME,priority,sn,EF->RES[priority].ETQ[sn].EF.VF.LEN1);

		EF->FILE.STATE=2;

		EF->FILE.LENS-=LOG_INFO_HEAD+1;
	}

	if(EF->FILE.ID==20) //SOE�ļ�
	{
		sn=Req_Empty_ResFrame(EF,priority); //������õ�Ӧ��֡

		EF->RES[priority].ETQ[sn].EF.VF.CTRL.DATA=0xD3;
		EF->RES[priority].ETQ[sn].EF.VF.ASDU.TI=125;
		EF->RES[priority].ETQ[sn].EF.VF.ASDU.VSQ=1;
		EF->RES[priority].ETQ[sn].EF.VF.ASDU.COT.U16=13;
		EF->RES[priority].ETQ[sn].EF.VF.ASDU.MSGADDR.U16=EF->FILE.MSGADDR.U16;
		memcpy(EF->RES[priority].ETQ[sn].EF.VF.ASDU.MSG,&EF->FILE.ID,sizeof(uint16_t));
		EF->RES[priority].ETQ[sn].EF.VF.ASDU.MSG[2]=1;  //LOG�Ľ����̶�Ϊ1

		strcpy(data,"SOE_FILE,1.00\r\nCOLLECTION_UNIT,"); //31�ֽ�

		strlens=strlen(data);

		memcpy(EF->RES[priority].ETQ[sn].EF.VF.ASDU.MSG+4,data,strlens);

		memcpy(EF->RES[priority].ETQ[sn].EF.VF.ASDU.MSG+4+strlens,&EF->FILE.INFONUM,2);

		EF->RES[priority].ETQ[sn].EF.VF.ASDU.MSG[6+strlens]=0x2C;
		EF->RES[priority].ETQ[sn].EF.VF.ASDU.MSG[6+strlens+1]=0x02;
		EF->RES[priority].ETQ[sn].EF.VF.ASDU.MSG[6+strlens+2]=0x00;
		EF->RES[priority].ETQ[sn].EF.VF.ASDU.MSG[6+strlens+3]=0x0D;
		EF->RES[priority].ETQ[sn].EF.VF.ASDU.MSG[6+strlens+4]=0x0A;

		EF->RES[priority].ETQ[sn].EF.VF.ASDU.MSG[3]=strlens+7;

		EF->RES[priority].ETQ[sn].EF.VF.LEN1=EF->RES[priority].ETQ[sn].EF.VF.ASDU.MSG[3]+4;

		for(uint8_t i=0;i<EF->RES[priority].ETQ[sn].EF.VF.ASDU.MSG[3];i++)
			EF->FILE.CS+=EF->RES[priority].ETQ[sn].EF.VF.ASDU.MSG[4+i];

		Fill_Ecp_Frame(EF,VAR_FRAME,priority,sn,EF->RES[priority].ETQ[sn].EF.VF.LEN1);

		EF->FILE.STATE=2;

		EF->FILE.LENS-=SOE_INFO_HEAD+1;
	}

	if(EF->FILE.ID==21) //ң���ļ�
	{
		sn=Req_Empty_ResFrame(EF,priority); //������õ�Ӧ��֡

		EF->RES[priority].ETQ[sn].EF.VF.CTRL.DATA=0xD3;
		EF->RES[priority].ETQ[sn].EF.VF.ASDU.TI=125;
		EF->RES[priority].ETQ[sn].EF.VF.ASDU.VSQ=1;
		EF->RES[priority].ETQ[sn].EF.VF.ASDU.COT.U16=13;
		EF->RES[priority].ETQ[sn].EF.VF.ASDU.MSGADDR.U16=EF->FILE.MSGADDR.U16;
		memcpy(EF->RES[priority].ETQ[sn].EF.VF.ASDU.MSG,&EF->FILE.ID,sizeof(uint16_t));
		EF->RES[priority].ETQ[sn].EF.VF.ASDU.MSG[2]=1;  //LOG�Ľ����̶�Ϊ1

		strcpy(data,"YK_FILE,1.00\r\nCOLLECTION_UNIT,"); //31�ֽ�

		strlens=strlen(data);

		memcpy(EF->RES[priority].ETQ[sn].EF.VF.ASDU.MSG+4,data,strlens);

		memcpy(EF->RES[priority].ETQ[sn].EF.VF.ASDU.MSG+4+strlens,&EF->FILE.INFONUM,2);

		EF->RES[priority].ETQ[sn].EF.VF.ASDU.MSG[6+strlens]=0x2C;
		EF->RES[priority].ETQ[sn].EF.VF.ASDU.MSG[6+strlens+1]=0x02;
		EF->RES[priority].ETQ[sn].EF.VF.ASDU.MSG[6+strlens+2]=0x00;
		EF->RES[priority].ETQ[sn].EF.VF.ASDU.MSG[6+strlens+3]=0x0D;
		EF->RES[priority].ETQ[sn].EF.VF.ASDU.MSG[6+strlens+4]=0x0A;

		EF->RES[priority].ETQ[sn].EF.VF.ASDU.MSG[3]=strlens+7;

		EF->RES[priority].ETQ[sn].EF.VF.LEN1=EF->RES[priority].ETQ[sn].EF.VF.ASDU.MSG[3]+4;

		for(uint8_t i=0;i<EF->RES[priority].ETQ[sn].EF.VF.ASDU.MSG[3];i++)
			EF->FILE.CS+=EF->RES[priority].ETQ[sn].EF.VF.ASDU.MSG[4+i];

		Fill_Ecp_Frame(EF,VAR_FRAME,priority,sn,EF->RES[priority].ETQ[sn].EF.VF.LEN1);

		EF->FILE.STATE=2;

		EF->FILE.LENS-=YK_INFO_HEAD+1;
	}

	if(EF->FILE.ID>=22&&EF->FILE.ID<=51) //ң���ļ�
	{
		sn=Req_Empty_ResFrame(EF,priority); //������õ�Ӧ��֡

		EF->RES[priority].ETQ[sn].EF.VF.CTRL.DATA=0xD3;
		EF->RES[priority].ETQ[sn].EF.VF.ASDU.TI=125;
		EF->RES[priority].ETQ[sn].EF.VF.ASDU.VSQ=1;
		EF->RES[priority].ETQ[sn].EF.VF.ASDU.COT.U16=13;
		EF->RES[priority].ETQ[sn].EF.VF.ASDU.MSGADDR.U16=EF->FILE.MSGADDR.U16;
		memcpy(EF->RES[priority].ETQ[sn].EF.VF.ASDU.MSG,&EF->FILE.ID,sizeof(uint16_t));
		EF->RES[priority].ETQ[sn].EF.VF.ASDU.MSG[2]=1;  //�����̶�Ϊ1

		strcpy(data,"YC_FILE,1.00\r\nCOLLECTION_UNIT,"); //30�ֽ�

		strlens=strlen(data);

		memcpy(EF->RES[priority].ETQ[sn].EF.VF.ASDU.MSG+4,data,strlens);

		EF->RES[priority].ETQ[sn].EF.VF.ASDU.MSG[4+strlens+0]=EF->FILE.TIME[6];
		EF->RES[priority].ETQ[sn].EF.VF.ASDU.MSG[4+strlens+1]=EF->FILE.TIME[5];
		EF->RES[priority].ETQ[sn].EF.VF.ASDU.MSG[4+strlens+2]=EF->FILE.TIME[4]&0x1F;
		EF->RES[priority].ETQ[sn].EF.VF.ASDU.MSG[7+strlens]=0x2C;

		memcpy(EF->RES[priority].ETQ[sn].EF.VF.ASDU.MSG+8+strlens,&EF->FILE.INFONUM,1);

		EF->RES[priority].ETQ[sn].EF.VF.ASDU.MSG[9+strlens]=0x2C;
		EF->RES[priority].ETQ[sn].EF.VF.ASDU.MSG[9+strlens+1]=0x02;
		EF->RES[priority].ETQ[sn].EF.VF.ASDU.MSG[9+strlens+2]=0x00;
		EF->RES[priority].ETQ[sn].EF.VF.ASDU.MSG[9+strlens+3]=0x2C;
		EF->RES[priority].ETQ[sn].EF.VF.ASDU.MSG[9+strlens+4]=0x03; //���ͱ�ʶ
		EF->RES[priority].ETQ[sn].EF.VF.ASDU.MSG[9+strlens+5]=0x0D;
		EF->RES[priority].ETQ[sn].EF.VF.ASDU.MSG[9+strlens+6]=0x0A;

		EF->RES[priority].ETQ[sn].EF.VF.ASDU.MSG[3]=strlens+12;

		EF->RES[priority].ETQ[sn].EF.VF.LEN1=EF->RES[priority].ETQ[sn].EF.VF.ASDU.MSG[3]+4;

		for(uint8_t i=0;i<EF->RES[priority].ETQ[sn].EF.VF.ASDU.MSG[3];i++)
			EF->FILE.CS+=EF->RES[priority].ETQ[sn].EF.VF.ASDU.MSG[4+i];

		Fill_Ecp_Frame(EF,VAR_FRAME,priority,sn,EF->RES[priority].ETQ[sn].EF.VF.LEN1);

		EF->FILE.STATE=2;

		EF->FILE.LENS-=YC_FILEHEAD_LEN+1;
	}

	if(EF->FILE.ID>=52&&EF->FILE.ID<=115) //�����ļ�
	{
		Mx25_Read_U8_Array(EF->FILE.READ,DB.U8,2,false);

		EF->FILE.READ+=9;

		EF->FILE.LENS-=DB.U16+1;

		while(DB.U16>0)
		{
			if(EF->FILE.STATE==0)
				return;

			sn=Req_Empty_ResFrame(EF,priority); //������õ�Ӧ��֡

			EF->RES[priority].ETQ[sn].EF.VF.CTRL.DATA=0xD3;
			EF->RES[priority].ETQ[sn].EF.VF.ASDU.TI=125;
			EF->RES[priority].ETQ[sn].EF.VF.ASDU.VSQ=1;
			EF->RES[priority].ETQ[sn].EF.VF.ASDU.COT.U16=13;
			EF->RES[priority].ETQ[sn].EF.VF.ASDU.MSGADDR.U16=EF->FILE.MSGADDR.U16;
			memcpy(EF->RES[priority].ETQ[sn].EF.VF.ASDU.MSG,&EF->FILE.ID,sizeof(uint16_t));
			EF->RES[priority].ETQ[sn].EF.VF.ASDU.MSG[2]=1;  //�����̶�Ϊ1

			if(DB.U16>=ECP_DATA_SEND_LEN)
			{
				EF->RES[priority].ETQ[sn].EF.VF.ASDU.MSG[3]=ECP_DATA_SEND_LEN;
				Mx25_Read_U8_Array(EF->FILE.READ,EF->RES[priority].ETQ[sn].EF.VF.ASDU.MSG+4,ECP_DATA_SEND_LEN,false);

				DB.U16-=ECP_DATA_SEND_LEN;
				EF->FILE.READ+=ECP_DATA_SEND_LEN;

				DEBUG_PRINT_NISR("KKNSDKK","<----- ��ǰ�ļ�ָ�� ",EF->FILE.READ);
				DEBUG_PRINT_U8CHAR_ARRAY_NISR(EF->RES[priority].ETQ[sn].EF.VF.ASDU.MSG+4,ECP_DATA_SEND_LEN);
			}
			else
			{
				EF->RES[priority].ETQ[sn].EF.VF.ASDU.MSG[3]=DB.U16;
				Mx25_Read_U8_Array(EF->FILE.READ,EF->RES[priority].ETQ[sn].EF.VF.ASDU.MSG+4,DB.U16,false);

				EF->FILE.READ+=DB.U16;

				DEBUG_PRINT_NISR("KKNSDKK","<----- ��ǰ�ļ�ָ�� ",EF->FILE.READ);
				DEBUG_PRINT_U8CHAR_ARRAY_NISR(EF->RES[priority].ETQ[sn].EF.VF.ASDU.MSG+4,ECP_DATA_SEND_LEN);


				DB.U16=0;
			}

			EF->RES[priority].ETQ[sn].EF.VF.LEN1=EF->RES[priority].ETQ[sn].EF.VF.ASDU.MSG[3]+4;

			for(uint8_t i=0;i<EF->RES[priority].ETQ[sn].EF.VF.ASDU.MSG[3];i++)
				EF->FILE.CS+=EF->RES[priority].ETQ[sn].EF.VF.ASDU.MSG[4+i];

			Fill_Ecp_Frame(EF,VAR_FRAME,priority,sn,EF->RES[priority].ETQ[sn].EF.VF.LEN1);

			EF->FILE.STATE=2;
		}
	}
}
/************************************************************!
*Function:
*Description:
*Input:
*Output: null
*Return: null
*************************************************************/
void App_Get_Segment(ECPFRAME *EF,uint8_t priority,uint8_t sn)
{
	LOGRECORD LOG;
	YAOCEFILE YCF;

	EF->RES[priority].ETQ[sn].EF.VF.ASDU.MSG[2]=1;  //�����̶�Ϊ1

	if(EF->FILE.ID==18) //�����ļ�
	{
		if(EF->FILE.LENS>=ECP_DATA_SEND_LEN)
		{
			Get_Fault_Data(EF->FILE.READ,EF->RES[priority].ETQ[sn].EF.VF.ASDU.MSG+4,ECP_DATA_SEND_LEN);

			EF->RES[priority].ETQ[sn].EF.VF.ASDU.MSG[3]=ECP_DATA_SEND_LEN;

			for(uint8_t i=0;i<ECP_DATA_SEND_LEN;i++)
				EF->FILE.CS+=EF->RES[priority].ETQ[sn].EF.VF.ASDU.MSG[4+i];

			EF->RES[priority].ETQ[sn].EF.VF.LEN1=4+EF->RES[priority].ETQ[sn].EF.VF.ASDU.MSG[3];

			EF->FILE.LENS-=ECP_DATA_SEND_LEN;
			EF->FILE.READ+=ECP_DATA_SEND_LEN;
		}
		else
		{
			Get_Fault_Data(EF->FILE.READ,EF->RES[priority].ETQ[sn].EF.VF.ASDU.MSG+4,EF->FILE.LENS);

			EF->RES[priority].ETQ[sn].EF.VF.ASDU.MSG[3]=EF->FILE.LENS;

			for(uint8_t i=0;i<EF->FILE.LENS;i++)
				EF->FILE.CS+=EF->RES[priority].ETQ[sn].EF.VF.ASDU.MSG[4+i];

			EF->RES[priority].ETQ[sn].EF.VF.LEN1=4+EF->RES[priority].ETQ[sn].EF.VF.ASDU.MSG[3];

			EF->FILE.LENS=0;
			EF->FILE.READ+=EF->FILE.LENS;
		}
	}

	if(EF->FILE.ID==19) //LOG�ļ�
	{
		Get_Log_Data(EF->FILE.READ,LOG.DATA,LOG_INFO_LEN);

		EF->RES[priority].ETQ[sn].EF.VF.ASDU.MSG[3]=LOG.LENS;

		memcpy(EF->RES[priority].ETQ[sn].EF.VF.ASDU.MSG+4,LOG.DATA+1,LOG.LENS);

		for(uint8_t i=0;i<LOG.LENS;i++)
			EF->FILE.CS+=EF->RES[priority].ETQ[sn].EF.VF.ASDU.MSG[4+i];

		EF->RES[priority].ETQ[sn].EF.VF.LEN1=4+LOG.LENS;

		EF->FILE.READ+=LOG_INFO_LEN;
	}

	if(EF->FILE.ID==20)  //SOE�ļ�
	{
		if(EF->FILE.LENS>=ECP_DATA_SEND_LEN)
		{
			Get_Soe_Data(EF->FILE.READ,EF->RES[priority].ETQ[sn].EF.VF.ASDU.MSG+4,ECP_DATA_SEND_LEN);

			EF->RES[priority].ETQ[sn].EF.VF.ASDU.MSG[3]=ECP_DATA_SEND_LEN;

			for(uint8_t i=0;i<ECP_DATA_SEND_LEN;i++)
				EF->FILE.CS+=EF->RES[priority].ETQ[sn].EF.VF.ASDU.MSG[4+i];

			EF->RES[priority].ETQ[sn].EF.VF.LEN1=4+ECP_DATA_SEND_LEN;

			EF->FILE.READ+=ECP_DATA_SEND_LEN;
			EF->FILE.LENS-=ECP_DATA_SEND_LEN;
		}
		else
		{
			Get_Soe_Data(EF->FILE.READ,EF->RES[priority].ETQ[sn].EF.VF.ASDU.MSG+4,EF->FILE.LENS);

			EF->RES[priority].ETQ[sn].EF.VF.ASDU.MSG[3]=EF->FILE.LENS;

			for(uint8_t i=0;i<EF->FILE.LENS;i++)
				EF->FILE.CS+=EF->RES[priority].ETQ[sn].EF.VF.ASDU.MSG[4+i];

			EF->RES[priority].ETQ[sn].EF.VF.LEN1=4+EF->FILE.LENS;

			EF->FILE.LENS=0;
			EF->FILE.READ+=EF->FILE.LENS;
		}
	}

	if(EF->FILE.ID==21) //ң���ļ�
	{
		if(EF->FILE.LENS>=ECP_DATA_SEND_LEN)
		{
			Get_Yk_Data(EF->FILE.READ,EF->RES[priority].ETQ[sn].EF.VF.ASDU.MSG+4,ECP_DATA_SEND_LEN);

			EF->RES[priority].ETQ[sn].EF.VF.ASDU.MSG[3]=ECP_DATA_SEND_LEN;

			for(uint8_t i=0;i<ECP_DATA_SEND_LEN;i++)
				EF->FILE.CS+=EF->RES[priority].ETQ[sn].EF.VF.ASDU.MSG[4+i];

			EF->RES[priority].ETQ[sn].EF.VF.LEN1=4+ECP_DATA_SEND_LEN;

			EF->FILE.LENS-=ECP_DATA_SEND_LEN;
			EF->FILE.READ+=ECP_DATA_SEND_LEN;
		}
		else
		{
			Get_Yk_Data(EF->FILE.READ,EF->RES[priority].ETQ[sn].EF.VF.ASDU.MSG+4,EF->FILE.LENS);

			EF->RES[priority].ETQ[sn].EF.VF.ASDU.MSG[3]=EF->FILE.LENS;

			for(uint8_t i=0;i<EF->FILE.LENS;i++)
				EF->FILE.CS+=EF->RES[priority].ETQ[sn].EF.VF.ASDU.MSG[4+i];

			EF->RES[priority].ETQ[sn].EF.VF.LEN1=4+EF->FILE.LENS;

			EF->FILE.LENS=0;
			EF->FILE.READ+=EF->FILE.LENS;
		}
	}

	if(EF->FILE.ID>=22&&EF->FILE.ID<=51) //ң���ļ�
	{
		Get_Yc_Data(EF->FILE.READ,YCF.DATA,YC_INFO_LEN);

		memcpy(EF->RES[priority].ETQ[sn].EF.VF.ASDU.MSG+3,YCF.DATA,YCF.LENS+1);

		for(uint8_t i=0;i<YCF.LENS;i++)
			EF->FILE.CS+=EF->RES[priority].ETQ[sn].EF.VF.ASDU.MSG[4+i];

		EF->RES[priority].ETQ[sn].EF.VF.LEN1=3+YCF.LENS+1;

		EF->FILE.READ+=YC_INFO_LEN;
	}

	if(EF->FILE.ID>=52&&EF->FILE.ID<=115) //�����ļ�
	{
		if(EF->FILE.LENS>=ECP_DATA_SEND_LEN)
		{
			vTaskSuspendAll();
			Mx25_Read_U8_Array(EF->FILE.READ,EF->RES[priority].ETQ[sn].EF.VF.ASDU.MSG+4,ECP_DATA_SEND_LEN,false);
			xTaskResumeAll();

			EF->RES[priority].ETQ[sn].EF.VF.ASDU.MSG[3]=ECP_DATA_SEND_LEN;

			for(uint32_t i=0;i<ECP_DATA_SEND_LEN;i++)
				EF->FILE.CS+=EF->RES[priority].ETQ[sn].EF.VF.ASDU.MSG[4+i];

			EF->RES[priority].ETQ[sn].EF.VF.LEN1=4+EF->RES[priority].ETQ[sn].EF.VF.ASDU.MSG[3];

			EF->FILE.READ+=ECP_DATA_SEND_LEN;
			EF->FILE.LENS-=ECP_DATA_SEND_LEN;

//			DEBUG_PRINT_NISR("KKNSDKK","<----- ��ǰ�ļ�ָ�� ",EF->FILE.READ);
//			DEBUG_PRINT_U8CHAR_ARRAY_NISR(EF->RES[priority].ETQ[sn].EF.VF.ASDU.MSG+4,ECP_DATA_SEND_LEN);

		}
		else
		{
			vTaskSuspendAll();
			Mx25_Read_U8_Array(EF->FILE.READ,EF->RES[priority].ETQ[sn].EF.VF.ASDU.MSG+4,EF->FILE.LENS,false);
			xTaskResumeAll();

			EF->RES[priority].ETQ[sn].EF.VF.ASDU.MSG[3]=EF->FILE.LENS;

			for(uint32_t i=0;i<EF->FILE.LENS;i++)
				EF->FILE.CS+=EF->RES[priority].ETQ[sn].EF.VF.ASDU.MSG[4+i];

			EF->RES[priority].ETQ[sn].EF.VF.LEN1=4+EF->RES[priority].ETQ[sn].EF.VF.ASDU.MSG[3];

			EF->FILE.READ+=EF->FILE.LENS;

//			DEBUG_PRINT_NISR("KKNSDKK","<----- ��ǰ�ļ�ָ�� ",EF->FILE.READ);
//			DEBUG_PRINT_U8CHAR_ARRAY_NISR(EF->RES[priority].ETQ[sn].EF.VF.ASDU.MSG+4,ECP_DATA_SEND_LEN);

			EF->FILE.LENS=0;
		}
	}
}
/************************************************************!
*Function:
*Description:
*Input:
*Output: null
*Return: null
*************************************************************/
void App_Send_Last_Segment(ECPFRAME *EF)
{
	uint8_t priority,sn; //Ӧ��֡��֡���

	priority=10;
	sn=Req_Empty_ResFrame(EF,priority); //������õ�Ӧ��֡

	EF->RES[priority].ETQ[sn].EF.VF.CTRL.DATA=0xD3;
	EF->RES[priority].ETQ[sn].EF.VF.ASDU.TI=123;
	EF->RES[priority].ETQ[sn].EF.VF.ASDU.VSQ=1;
	EF->RES[priority].ETQ[sn].EF.VF.ASDU.COT.U16=13;

	EF->RES[priority].ETQ[sn].EF.VF.ASDU.MSGADDR.U16=EF->FILE.MSGADDR.U16;
	memcpy(EF->RES[priority].ETQ[sn].EF.VF.ASDU.MSG,&EF->FILE.ID,sizeof(uint16_t));
	EF->RES[priority].ETQ[sn].EF.VF.ASDU.MSG[2]=EF->FILE.SECTION;
	EF->RES[priority].ETQ[sn].EF.VF.ASDU.MSG[3]=3; //�ڴ���LSQ
	EF->RES[priority].ETQ[sn].EF.VF.ASDU.MSG[4]=EF->FILE.CS;
	Fill_Ecp_Frame(EF,VAR_FRAME,priority,sn,5);

	EF->FILE.STATE=4;
}
/************************************************************!
*Function:
*Description:
*Input:
*Output: null
*Return: null
*************************************************************/
bool App_Set_Para(ECPFRAME *EF)
{
	uint8_t priority,sn; //Ӧ��֡��֡���

	priority=9;
	sn=Req_Empty_ResFrame(EF,priority); //������õ�Ӧ��֡

	EF->RES[priority].ETQ[sn].EF.VF.CTRL.DATA=0xD3;

	EF->RES[priority].ETQ[sn].EF.VF.ASDU.TI=EF->REQ.EF.VF.ASDU.TI;
	EF->RES[priority].ETQ[sn].EF.VF.ASDU.VSQ=EF->REQ.EF.VF.ASDU.VSQ;
	memcpy(EF->RES[priority].ETQ[sn].EF.VF.ASDU.MSG,EF->REQ.EF.VF.ASDU.MSG,3);

	if(EF->TP.STATUS==0)
	{
		if(EF->REQ.EF.VF.ASDU.MSG[2]==0x00) //ִ�в���
		{
			EF->RES[priority].ETQ[sn].EF.VF.ASDU.COT.U16=10; //ֹͣ����ȷ��

			Fill_Ecp_Frame(EF,VAR_FRAME,priority,sn,3);

			return false;
		}
	}

	if(EF->TP.STATUS==1)
	{
		if(EF->REQ.EF.VF.ASDU.MSG[2]==0x80) //Ԥ�ò���
		{
			EF->RES[priority].ETQ[sn].EF.VF.ASDU.COT.U16=10; //ֹͣ����ȷ��

			Fill_Ecp_Frame(EF,VAR_FRAME,priority,sn,3);

			return false;
		}
	}

	if(EF->TP.STATUS==2) //��δ��ȡ�ɼ���Ԫ����
	{
		EF->RES[priority].ETQ[sn].EF.VF.ASDU.COT.U16=10; //ֹͣ����ȷ��

		Fill_Ecp_Frame(EF,VAR_FRAME,priority,sn,3);

		return false;
	}

	if(EF->REQ.EF.VF.ASDU.MSG[2]==0x80) //Ԥ�ò���
	{
		EF->TP.TIMEOUT=gUNIXTIME.UNIX;

		memcpy(EF->TP.MSGADDR.U8,EF->REQ.EF.VF.ASDU.MSGADDR.U8,2);
		memcpy(EF->TP.PARA.U8,EF->RES[priority].ETQ[sn].EF.VF.ASDU.MSG,2);
		EF->RES[priority].ETQ[sn].EF.VF.ASDU.COT.U16=EF->REQ.EF.VF.ASDU.COT.U16+1;

		if(EF->REQ.EF.VF.ASDU.MSGADDR.U16>=0x5001&&EF->REQ.EF.VF.ASDU.MSGADDR.U16<=0x5100) //�㼯��Ԫ����
		{
			EF->TP.STATUS=1;

			Fill_Ecp_Frame(EF,VAR_FRAME,priority,sn,3);
		}

		if(EF->REQ.EF.VF.ASDU.MSGADDR.U16>=0x5101&&EF->REQ.EF.VF.ASDU.MSGADDR.U16<=0x5A00) //�ɼ���Ԫ����
		{
			EF->TP.STATUS=2; //��ȡ�ɼ���Ԫ����

			Fill_Icp_Frame(RADIOFRAME.CHANNEL,gSYSPARA.LINEGROUP.LINE[(EF->REQ.EF.VF.ASDU.MSGADDR.U4[2].U03-1)/3].AU[(EF->REQ.EF.VF.ASDU.MSGADDR.U4[2].U03-1)%3].ADDR,0x42,0x05,1,1,0,0);

			vTaskDelay(pdMS_TO_TICKS(1000)); //��ʱ1��
		}

		Fill_Ecp_Frame(EF,VAR_FRAME,priority,sn,3);

		return false;
	}

	if(EF->REQ.EF.VF.ASDU.MSG[2]==0x00) //ִ�в���
	{
		EF->TP.STATUS=0;

		if(gUNIXTIME.UNIX-EF->TP.TIMEOUT>30) //���ʱ
		{
			EF->RES[priority].ETQ[sn].EF.VF.ASDU.COT.U16=10; //ֹͣ����ȷ��

			Fill_Ecp_Frame(EF,VAR_FRAME,priority,sn,3);

			return false;
		}

		EF->RES[priority].ETQ[sn].EF.VF.ASDU.COT.U16=EF->REQ.EF.VF.ASDU.COT.U16+1;

		if(EF->REQ.EF.VF.ASDU.MSGADDR.U16>=0x5001&&EF->REQ.EF.VF.ASDU.MSGADDR.U16<=0x5100) //�㼯��Ԫ����
		{
			memcpy(gECPPARA.DATA+(EF->TP.MSGADDR.U16-0x5001)*2,EF->TP.PARA.U8,2);

			Mx25_Erase_Sector(ECPPARA_ADDR/MX25_SECTOR_LEN);

			Mx25_Data_Storage(ECPPARA_ADDR,gECPPARA.DATA,(ECPPARA_NUM*2)); //���ݴ洢

			gECPINFO.YX.GPS_LOCK.MSG.U16=gECPPARA.GPS_TIMING_MODE; //��GPSУʱ״̬��ֵ��ң��
		}

		if(EF->REQ.EF.VF.ASDU.MSGADDR.U16>=0x5101&&EF->REQ.EF.VF.ASDU.MSGADDR.U16<=0x5A00) //�ɼ���Ԫ����
		{
			if(EF->AP.MSGADDR.U8[0]<=7) //ǰ7������Ϊ16λ,��ַ��01-14
			{
				memcpy(EF->AP.DATA+(EF->AP.MSGADDR.U8[0]-1)*2,EF->TP.PARA.U8,2);

				Fill_Icp_Frame(RADIOFRAME.CHANNEL,gSYSPARA.LINEGROUP.LINE[(EF->AP.MSGADDR.U4[1].U03-1)/3].AU[(EF->AP.MSGADDR.U4[1].U03-1)%3].ADDR,0x42,0x05,1,1,EF->AP.DATA,25);
			}

			if(gECPFRAMELIST.AP.MSGADDR.U8[0]>7)//����Ĳ���Ϊ8λ,��15-
			{
				memcpy(EF->AP.DATA+6+EF->AP.MSGADDR.U8[0],&EF->TP.PARA.U8[0],1);

				memcpy(gECPFRAMELIST.RES[priority].ETQ[sn].EF.VF.ASDU.MSG,gECPFRAMELIST.AP.DATA+6+gECPFRAMELIST.AP.MSGADDR.U8[0],1);

				Fill_Icp_Frame(RADIOFRAME.CHANNEL,gSYSPARA.LINEGROUP.LINE[(EF->AP.MSGADDR.U4[1].U03-1)/3].AU[(EF->AP.MSGADDR.U4[1].U03-1)%3].ADDR,0x42,0x05,1,1,EF->AP.DATA,25);
			}
		}

		Fill_Ecp_Frame(EF,VAR_FRAME,priority,sn,3);
	}

	return true;
}
/************************************************************!
*Function:
*Description:
*Input:
*Output: null
*Return: null
*************************************************************/
void App_Read_Data(ECPFRAME *EF)
{
	uint8_t priority,sn; //Ӧ��֡��֡���

	priority=8;
	sn=Req_Empty_ResFrame(EF,priority); //������õ�Ӧ��֡

	if(EF->REQ.EF.VF.ASDU.MSGADDR.U16>=0x5001&&EF->REQ.EF.VF.ASDU.MSGADDR.U16<=0x5100) //�㼯��Ԫ������Ϣ
	{
		EF->RES[priority].ETQ[sn].EF.VF.CTRL.DATA=0xD3;
		EF->RES[priority].ETQ[sn].EF.VF.ASDU.TI=EF->REQ.EF.VF.ASDU.TI;
		EF->RES[priority].ETQ[sn].EF.VF.ASDU.VSQ=EF->REQ.EF.VF.ASDU.VSQ;
		EF->RES[priority].ETQ[sn].EF.VF.ASDU.COT.U16=EF->REQ.EF.VF.ASDU.COT.U16+1;
		EF->RES[priority].ETQ[sn].EF.VF.ASDU.MSGADDR.U16=EF->REQ.EF.VF.ASDU.MSGADDR.U16;

		memcpy(EF->RES[priority].ETQ[sn].EF.VF.ASDU.MSG,gECPPARA.DATA+(EF->REQ.EF.VF.ASDU.MSGADDR.U16-0x5001)*2,2);

		Fill_Ecp_Frame(EF,VAR_FRAME,priority,sn,2);
	}

	if(EF->REQ.EF.VF.ASDU.MSGADDR.U16>=0x5101&&EF->REQ.EF.VF.ASDU.MSGADDR.U16<=0x5A00) //�ɼ���Ԫ������Ϣ
	{
		if(gECPFRAMELIST.TP.STATUS==2)
			gECPFRAMELIST.TP.STATUS=1;

		EF->AP.MSGADDR.U16=EF->REQ.EF.VF.ASDU.MSGADDR.U16;
		Fill_Icp_Frame(RADIOFRAME.CHANNEL,gSYSPARA.LINEGROUP.LINE[(EF->REQ.EF.VF.ASDU.MSGADDR.U4[1].U03-1)/3].AU[(EF->REQ.EF.VF.ASDU.MSGADDR.U4[1].U03-1)%3].ADDR,0x42,0x05,1,1,0,0);
	}
}
/************************************************************!
*Function:
*Description:
*Input:
*Output: null
*Return: null
*************************************************************/
void App_Read_MultiPara(ECPFRAME *EF)
{
	FOURBYTE FB;
	uint8_t priority,sn; //Ӧ��֡��֡���
	uint16_t paralens=0,pos=0;
	uint8_t SYSPARA[1100];


	paralens=Ecp_Get_MultiPara(EF->REQ.EF.VF.ASDU.VSQ,EF->REQ.EF.VF.ASDU.MSG,SYSPARA);

	while((paralens-pos)>=ECP_DATA_SEND_LEN)
	{
		priority=6;
		sn=Req_Empty_ResFrame(EF,priority); //������õ�Ӧ��֡

		EF->RES[priority].ETQ[sn].EF.VF.CTRL.DATA=0xD3;
		EF->RES[priority].ETQ[sn].EF.VF.ASDU.TI=EF->REQ.EF.VF.ASDU.TI;
		EF->RES[priority].ETQ[sn].EF.VF.ASDU.COT.U16=EF->REQ.EF.VF.ASDU.COT.U16+1;
		EF->RES[priority].ETQ[sn].EF.VF.ASDU.MSGADDR.U16=EF->REQ.EF.VF.ASDU.MSGADDR.U16;

		FB.U32=Search_MultiPara_Pos(SYSPARA,paralens,pos);


		EF->RES[priority].ETQ[sn].EF.VF.ASDU.VSQ=FB.U16[1].U16;

		memcpy(EF->RES[priority].ETQ[sn].EF.VF.ASDU.MSG,SYSPARA+pos,FB.U16[0].U16);

		Fill_Ecp_Frame(EF,VAR_FRAME,priority,sn,FB.U16[0].U16);

		pos+=FB.U16[0].U16;
	}

	if(pos!=paralens)
	{
		priority=8;
		sn=Req_Empty_ResFrame(EF,priority); //������õ�Ӧ��֡

		EF->RES[priority].ETQ[sn].EF.VF.CTRL.DATA=0xD3;
		EF->RES[priority].ETQ[sn].EF.VF.ASDU.TI=EF->REQ.EF.VF.ASDU.TI;
		EF->RES[priority].ETQ[sn].EF.VF.ASDU.COT.U16=EF->REQ.EF.VF.ASDU.COT.U16+1;
		EF->RES[priority].ETQ[sn].EF.VF.ASDU.MSGADDR.U16=EF->REQ.EF.VF.ASDU.MSGADDR.U16;

		FB.U32=Search_MultiPara_Pos(SYSPARA,paralens,pos);


		EF->RES[priority].ETQ[sn].EF.VF.ASDU.VSQ=FB.U16[1].U16;

		memcpy(EF->RES[priority].ETQ[sn].EF.VF.ASDU.MSG,SYSPARA+pos,FB.U16[0].U16);

		Fill_Ecp_Frame(EF,VAR_FRAME,priority,sn,FB.U16[0].U16);
	}
}
/************************************************************!
*Function:
*Description:
*Input:
*Output: null
*Return: null
*************************************************************/
void App_Read_Safe_Info(ECPFRAME *EF)
{
	uint8_t priority,sn;

	#ifdef PRINT_ESAM_INFO_DEBUG
	DEBUG_PRINT_NISR("KKNSKK","<-------- ��ǰ�߳����ڶ�ȡESAM��ȫ��Ϣ!");
	#endif

	priority=8;
	sn=Req_Empty_ResFrame(EF,priority); //������õ�Ӧ��֡

	EF->RES[priority].ETQ[sn].EF.VF.CTRL.DATA=0xD3;
	EF->RES[priority].ETQ[sn].EF.VF.ASDU.TI=EF->REQ.EF.VF.ASDU.TI;
	EF->RES[priority].ETQ[sn].EF.VF.ASDU.VSQ=EF->REQ.EF.VF.ASDU.VSQ;
	EF->RES[priority].ETQ[sn].EF.VF.ASDU.COT.U16=EF->REQ.EF.VF.ASDU.COT.U16;
	EF->RES[priority].ETQ[sn].EF.VF.ASDU.MSGADDR.U16=EF->REQ.EF.VF.ASDU.MSGADDR.U16;

	if(EF->REQ.EF.VF.ASDU.MSG[0]==0x01) //���ն˰�ȫ��Ϣ
	{
		Esam1120a_Get_Key_Version(EF->RES[priority].ETQ[sn].EF.VF.ASDU.MSG);
		Esam1120a_Get_Chip_Id(EF->RES[priority].ETQ[sn].EF.VF.ASDU.MSG+1);
	}

	Fill_Ecp_Frame(EF,VAR_FRAME,priority,sn,9); //9���ֽ�
}
/************************************************************!
*Function:
*Description:
*Input:
*Output: null
*Return: null
*************************************************************/
void App_Authentication(ECPFRAME *EF)
{
	uint8_t priority,sn;

	#ifdef PRINT_ESAM_INFO_DEBUG
	DEBUG_PRINT_NISR("KKNSKK","<-------- ��ǰ�߳����ڽ� ESAM�����֤!");
	#endif

	priority=8;
	sn=Req_Empty_ResFrame(EF,priority); //������õ�Ӧ��֡

	EF->RES[priority].ETQ[sn].EF.VF.CTRL.DATA=0xD3;
	EF->RES[priority].ETQ[sn].EF.VF.ASDU.TI=EF->REQ.EF.VF.ASDU.TI;
	EF->RES[priority].ETQ[sn].EF.VF.ASDU.VSQ=EF->REQ.EF.VF.ASDU.VSQ;
	EF->RES[priority].ETQ[sn].EF.VF.ASDU.COT.U16=EF->REQ.EF.VF.ASDU.COT.U16+1;
	EF->RES[priority].ETQ[sn].EF.VF.ASDU.MSGADDR.U16=EF->REQ.EF.VF.ASDU.MSGADDR.U16;

	memcpy(EF->RES[priority].ETQ[sn].EF.VF.ASDU.MSG,EF->REQ.EF.VF.ASDU.MSG,8);

	if(Esam1120a_Authentication(EF->RES[priority].ETQ[sn].EF.VF.ASDU.MSG)!=0)
	{
		Fill_Ecp_Frame(EF,VAR_FRAME,priority,sn,16);
	}
	else
	{
		EF->RES[priority].ETQ[sn].EF.VF.ASDU.TI=0xF7;
		EF->RES[priority].ETQ[sn].EF.VF.ASDU.COT.U16=7;
		EF->RES[priority].ETQ[sn].EF.VF.ASDU.MSG[0]=0x00;
		EF->RES[priority].ETQ[sn].EF.VF.ASDU.MSG[1]=0x08; //�����֤ʧ��

		Fill_Ecp_Frame(EF,VAR_FRAME,priority,sn,2);
	}
}
/************************************************************!
*Function:
*Description:
*Input:
*Output: null
*Return: null
*************************************************************/
void App_Public_Key_Verification(ECPFRAME *EF) //��Կ��֤
{
	uint8_t priority,sn;

	#ifdef PRINT_ESAM_INFO_DEBUG
	DEBUG_PRINT_NISR("KKNSKK","<-------- ��ǰ�߳����ڽ���ESAM��Կ��֤!");
	#endif

	priority=8;
	sn=Req_Empty_ResFrame(EF,priority); //������õ�Ӧ��֡

	EF->RES[priority].ETQ[sn].EF.VF.CTRL.DATA=0xD3;
	EF->RES[priority].ETQ[sn].EF.VF.ASDU.TI=EF->REQ.EF.VF.ASDU.TI;
	EF->RES[priority].ETQ[sn].EF.VF.ASDU.VSQ=EF->REQ.EF.VF.ASDU.VSQ;
	EF->RES[priority].ETQ[sn].EF.VF.ASDU.COT.U16=EF->REQ.EF.VF.ASDU.COT.U16+1;
	EF->RES[priority].ETQ[sn].EF.VF.ASDU.MSGADDR.U16=EF->REQ.EF.VF.ASDU.MSGADDR.U16;

	memcpy(EF->RES[priority].ETQ[sn].EF.VF.ASDU.MSG,EF->REQ.EF.VF.ASDU.MSG,9);

	if(Esam1120a_Public_Key_Verification(EF->RES[priority].ETQ[sn].EF.VF.ASDU.MSG)!=0)
	{
		Fill_Ecp_Frame(EF,VAR_FRAME,priority,sn,104);
	}
	else
	{
		EF->RES[priority].ETQ[sn].EF.VF.ASDU.TI=0xF7;
		EF->RES[priority].ETQ[sn].EF.VF.ASDU.COT.U16=7;
		EF->RES[priority].ETQ[sn].EF.VF.ASDU.MSG[0]=0x01;
		EF->RES[priority].ETQ[sn].EF.VF.ASDU.MSG[1]=0x00; //��ʱ��Ϊ������ʧ��

		Fill_Ecp_Frame(EF,VAR_FRAME,priority,sn,2);
	}
}
/************************************************************!
*Function:
*Description:
*Input:
*Output: null
*Return: null
*************************************************************/
void App_Public_Key_Update(ECPFRAME *EF)
{
	uint8_t priority,sn;

	#ifdef PRINT_ESAM_INFO_DEBUG
	DEBUG_PRINT_NISR("KKNSKK","<-------- ��ǰ�߳����ڽ���ESAM��Կ����!");
	#endif

	priority=8;
	sn=Req_Empty_ResFrame(EF,priority); //������õ�Ӧ��֡

	EF->RES[priority].ETQ[sn].EF.VF.CTRL.DATA=0xD3;
	EF->RES[priority].ETQ[sn].EF.VF.ASDU.TI=EF->REQ.EF.VF.ASDU.TI;
	EF->RES[priority].ETQ[sn].EF.VF.ASDU.VSQ=EF->REQ.EF.VF.ASDU.VSQ;
	EF->RES[priority].ETQ[sn].EF.VF.ASDU.COT.U16=EF->REQ.EF.VF.ASDU.COT.U16+1;
	EF->RES[priority].ETQ[sn].EF.VF.ASDU.MSGADDR.U16=EF->REQ.EF.VF.ASDU.MSGADDR.U16;

	memcpy(EF->RES[priority].ETQ[sn].EF.VF.ASDU.MSG,EF->REQ.EF.VF.ASDU.MSG,138);

	if(Esam1120a_Public_Key_Update(EF->RES[priority].ETQ[sn].EF.VF.ASDU.MSG)!=0)
	{
		Fill_Ecp_Frame(EF,VAR_FRAME,priority,sn,104);
	}
	else
	{
		EF->RES[priority].ETQ[sn].EF.VF.ASDU.TI=0xF7;
		EF->RES[priority].ETQ[sn].EF.VF.ASDU.COT.U16=7;
		EF->RES[priority].ETQ[sn].EF.VF.ASDU.MSG[0]=0x40;
		EF->RES[priority].ETQ[sn].EF.VF.ASDU.MSG[1]=0x00; //д�빫Կʧ��

		Fill_Ecp_Frame(EF,VAR_FRAME,priority,sn,2);
	}

}
/************************************************************!
*Function:
*Description:
*Input:
*Output: null
*Return: null
*************************************************************/
void App_Symmetric_key_Update(ECPFRAME *EF)
{
	uint8_t priority,sn;

	#ifdef PRINT_ESAM_INFO_DEBUG
	DEBUG_PRINT_NISR("KKNSKK","<-------- ��ǰ�߳����ڽ���ESAM�Գ���Կ����!");
	#endif

	priority=8;
	sn=Req_Empty_ResFrame(EF,priority); //������õ�Ӧ��֡

	EF->RES[priority].ETQ[sn].EF.VF.CTRL.DATA=0xD3;
	EF->RES[priority].ETQ[sn].EF.VF.ASDU.TI=EF->REQ.EF.VF.ASDU.TI;
	EF->RES[priority].ETQ[sn].EF.VF.ASDU.VSQ=EF->REQ.EF.VF.ASDU.VSQ;
	EF->RES[priority].ETQ[sn].EF.VF.ASDU.COT.U16=EF->REQ.EF.VF.ASDU.COT.U16+1;
	EF->RES[priority].ETQ[sn].EF.VF.ASDU.MSGADDR.U16=EF->REQ.EF.VF.ASDU.MSGADDR.U16;

	memcpy(EF->RES[priority].ETQ[sn].EF.VF.ASDU.MSG,EF->REQ.EF.VF.ASDU.MSG,197);

	if(Esam1120a_Symmetric_key_Update(EF->RES[priority].ETQ[sn].EF.VF.ASDU.MSG)==true)
	{
		EF->RES[priority].ETQ[sn].EF.VF.ASDU.MSG[0]=0; //д��Գ���Կ�ɹ�
		EF->RES[priority].ETQ[sn].EF.VF.ASDU.MSG[1]=0;
	}
	else
	{
		EF->RES[priority].ETQ[sn].EF.VF.ASDU.TI=0xF7;
		EF->RES[priority].ETQ[sn].EF.VF.ASDU.COT.U16=7;
		EF->RES[priority].ETQ[sn].EF.VF.ASDU.MSG[0]=0x20; //д��Գ���Կʧ��
		EF->RES[priority].ETQ[sn].EF.VF.ASDU.MSG[1]=0;
	}

	Fill_Ecp_Frame(EF,VAR_FRAME,priority,sn,2);
}
/************************************************************!
*Function:
*Description:
*Input:
*Output: null
*Return: null
*************************************************************/
void App_Key_Consult(ECPFRAME *EF)
{
	uint8_t priority,sn;

	#ifdef PRINT_ESAM_INFO_DEBUG
	DEBUG_PRINT_NISR("KKNSKK","<-------- ��ǰ�߳����ڽ���ESAM��Կ�ỰЭ��!");
	#endif

	priority=8;
	sn=Req_Empty_ResFrame(EF,priority); //������õ�Ӧ��֡

	EF->RES[priority].ETQ[sn].EF.VF.CTRL.DATA=0xD3;
	EF->RES[priority].ETQ[sn].EF.VF.ASDU.TI=EF->REQ.EF.VF.ASDU.TI;
	EF->RES[priority].ETQ[sn].EF.VF.ASDU.VSQ=EF->REQ.EF.VF.ASDU.VSQ;
	EF->RES[priority].ETQ[sn].EF.VF.ASDU.COT.U16=EF->REQ.EF.VF.ASDU.COT.U16+1;
	EF->RES[priority].ETQ[sn].EF.VF.ASDU.MSGADDR.U16=EF->REQ.EF.VF.ASDU.MSGADDR.U16;

	memcpy(EF->RES[priority].ETQ[sn].EF.VF.ASDU.MSG,EF->REQ.EF.VF.ASDU.MSG,73);

	if(Esam1120a_Key_Consult(EF->RES[priority].ETQ[sn].EF.VF.ASDU.MSG)==true)
	{
		Fill_Ecp_Frame(EF,VAR_FRAME,priority,sn,120);
	}
	else
	{
		EF->RES[priority].ETQ[sn].EF.VF.ASDU.TI=0xF7;
		EF->RES[priority].ETQ[sn].EF.VF.ASDU.COT.U16=7;
		EF->RES[priority].ETQ[sn].EF.VF.ASDU.MSG[0]=0x00;
		EF->RES[priority].ETQ[sn].EF.VF.ASDU.MSG[1]=0x04; //��ԿЭ��ʧ��

		Fill_Ecp_Frame(EF,VAR_FRAME,priority,sn,2);
	}
}
/************************************************************!
*Function:
*Description:
*Input:
*Output: null
*Return: null
*************************************************************/
void App_Get_Random(ECPFRAME *EF)
{
	uint8_t priority,sn;

	#ifdef PRINT_ESAM_INFO_DEBUG
	DEBUG_PRINT_NISR("KKNSKK","<-------- ��ǰ�߳����ڽ���ESAM�������ȡ!");
	#endif

	priority=8;
	sn=Req_Empty_ResFrame(EF,priority); //������õ�Ӧ��֡

	EF->RES[priority].ETQ[sn].EF.VF.CTRL.DATA=0xD3;
	EF->RES[priority].ETQ[sn].EF.VF.ASDU.TI=EF->REQ.EF.VF.ASDU.TI;
	EF->RES[priority].ETQ[sn].EF.VF.ASDU.VSQ=EF->REQ.EF.VF.ASDU.VSQ;
	EF->RES[priority].ETQ[sn].EF.VF.ASDU.COT.U16=EF->REQ.EF.VF.ASDU.COT.U16+1;
	EF->RES[priority].ETQ[sn].EF.VF.ASDU.MSGADDR.U16=EF->REQ.EF.VF.ASDU.MSGADDR.U16;

	if(Esam1120a_Get_Random(EF->RES[priority].ETQ[sn].EF.VF.ASDU.MSG)!=0)
	{
		Fill_Ecp_Frame(EF,VAR_FRAME,priority,sn,8); //8λ�����
	}
	else
	{
		EF->RES[priority].ETQ[sn].EF.VF.ASDU.TI=0xF7;
		EF->RES[priority].ETQ[sn].EF.VF.ASDU.COT.U16=7;
		EF->RES[priority].ETQ[sn].EF.VF.ASDU.MSG[0]=0x80;
		EF->RES[priority].ETQ[sn].EF.VF.ASDU.MSG[1]=0x00; //���������ʧ��

		Fill_Ecp_Frame(EF,VAR_FRAME,priority,sn,2);
	}
}
/************************************************************!
*Function:
*Description:
*Input:
*Output: null
*Return: null
*************************************************************/
void Locate_File_Info(ECPFRAME *EF)
{
	EF->FILE.CS=0;
	EF->FILE.LENS=0;
	EF->FILE.INFONO=0;
	EF->FILE.INFONUM=0;

	if(EF->FILE.ID==18) //�����ļ�
		Locate_Fault_FileInfo(&EF->FILE);

	if(EF->FILE.ID==19)  //��־�ļ�
		Locate_Log_FileInfo(&EF->FILE);

	if(EF->FILE.ID==20) //SOE�ļ�
		Locate_Soe_FileInfo(&EF->FILE);

	if(EF->FILE.ID==21) //ң���ļ�
		Locate_Yk_FileInfo(&EF->FILE);

	if(EF->FILE.ID>=22&&EF->FILE.ID<=51) //ң���ļ�
		Locate_Yc_FileInfo(&EF->FILE);

	if(EF->FILE.ID>=52&&EF->FILE.ID<=115) //�����ļ�
		Locate_Wave_FileInfo(&EF->FILE);

	#ifdef PRINT_ECP_READ_FILE_DEBUG
	DEBUG_PRINT_NISR("NSDSDSESDS","<--------------- ��ǰ�ļ�����: ",EF->FILE.LENS," ������: ",EF->FILE.INFONUM," �ļ�ʱ��: ",EF->FILE.TIME," ��־�ļ�ָ��: ",EF->FILE.READ,"\r\n");
	#endif
}
/************************************************************!
*Function:
*Description:
*Input:
*Output: null
*Return: null
*************************************************************/
void Ecp_Search_File_Dir(ECPFRAME *EF,uint8_t sn)
{

}
/************************************************************!
*Function:
*Description:
*Input:
*Output: null
*Return: null
*************************************************************/
uint16_t Get_AllCall_Yx(uint8_t *data)
{
	uint16_t minaddr=0xFFFF;
	uint16_t minaddrindex=0;
	uint32_t realnum=0,totalnum=0;
	uint32_t yxnum=(7+((3*8)*gSYSPARA.LINEGROUP.LINENUM));

	for(uint32_t i=0;i<yxnum;i++)  //��õ�ַ����Сֵ
	{
		if(gECPINFO.YX.DATA[2*i]<minaddr)
		{
			minaddrindex=2*i;
			minaddr=gECPINFO.YX.DATA[2*i];
		}
	}

	memcpy(data,&minaddr,sizeof(uint16_t)); //����ʼ��ַ��������Ϣ���ַ

	data[2]=gECPINFO.YX.DATA[minaddrindex+1];

	realnum++;
	totalnum++;

	for(uint32_t sn=0;sn<10000;sn++)
	{
		minaddr++;

		for(uint32_t i=0;i<yxnum;i++)  //��õ�ַ����Сֵ
		{
			if(gECPINFO.YX.DATA[2*i]==minaddr)
			{
				data[3+totalnum-1]=gECPINFO.YX.DATA[2*i+1];

				realnum++;
				totalnum++;

				break;
			}

			if(i==(yxnum-1))
			{
				data[3+totalnum-1]=0;

				totalnum++;
			}
		}

		if(realnum==yxnum)
			break;
	}

	return (totalnum);
}
/************************************************************!
*Function:
*Description:
*Input:
*Output: null
*Return: null
*************************************************************/
uint16_t Get_AllCall_Yc(uint8_t *data)
{
	uint16_t minaddr=0xFFFF;
	uint16_t minaddrindex=0;
	uint32_t realnum=0,totalnum=0;
	uint32_t ycnum=(2+(3*5*gSYSPARA.LINEGROUP.LINENUM));


	for(uint32_t i=0;i<ycnum;i++)  //���ң���ַ����Сֵ
	{
		if(gECPINFO.YC.DATA[3*i]<minaddr)
		{
			minaddrindex=3*i;
			minaddr=gECPINFO.YC.DATA[3*i];
		}
	}

	memcpy(data,&minaddr,sizeof(uint16_t)); //����ʼ��ַ��������Ϣ���ַ

	memcpy(data+2,gECPINFO.YC.DATA+minaddrindex+1,sizeof(uint16_t));
	data[4]=gECPINFO.YC.DATA[minaddrindex+2];

	realnum++;
	totalnum++;

	for(uint32_t sn=0;sn<100000;sn++)
	{
		minaddr++;

		for(uint32_t i=0;i<ycnum;i++)
		{
			if(gECPINFO.YC.DATA[3*i]==minaddr)
			{
				memcpy(data+5+(totalnum-1)*3,gECPINFO.YC.DATA+3*i+1,sizeof(uint16_t)); //����ʼ��ַ��������Ϣ���ַ
				data[5+(totalnum-1)*3+2]=gECPINFO.YC.DATA[3*i+2];

				realnum++;
				totalnum++;

				break;
			}

			if(i==(ycnum-1))
			{
				memset(data+5+(totalnum-1)*3,0,3);

				totalnum++;
			}
		}

		if(realnum==ycnum)
			break;
	}

	return (totalnum*3);
}
/************************************************************!
*Function:
*Description:
*Input:
*Output: null
*Return: null
*************************************************************/
bool Ecp_File_Send(ECPFRAME *EF)
{
	#ifndef ECP_LINKSTATE_CONTROL
	if(EF->LINKSTATE==LINKSTATE_START)
		return false;
	#endif

	if(EF->FILE.STATE==1)
	{
		#ifdef PRINT_ECP_READ_FILE_DEBUG
		DEBUG_PRINT_NISR("SESDSDSDS","<--------------- ��ǰ�ļ�ʱ��: ",EF->FILE.TIME," �ļ�����: ",EF->FILE.LENS," �ļ�����: ",EF->FILE.INFONUM," �ļ�ָ��: ",EF->FILE.READ,"\r\n");
		#endif

		App_Send_Segment(EF);

		if(gECPINFO.YX.WAVEFILE.MSG.U16==1)
			Soe_Data_Record(&gECPINFO.YX.WAVEFILE,0,true,0);
	}

	return true;
}
/************************************************************!
*Function:
*Description:
*Input:
*Output: null
*Return: null
*************************************************************/
bool App_Send_Reply(ECPFRAME *EF)
{
	#ifndef ECP_LINKSTATE_CONTROL
	if(EF->LINKSTATE==LINKSTATE_START)
		return false;
	#endif

	for(uint8_t priority=1;priority<MAX_PRIORITY_NUM;priority++) //���ȼ���ѯ
	{
		for(uint8_t sn=EF->PRIORITY[priority];sn<(EF->PRIORITY[priority]+MAX_REPLY_NUM);sn++) //���Ͷ�����ѯ
		{
			EF->SN=sn%MAX_REPLY_NUM;

			if(EF->RES[priority].ETQ[EF->SN].ISLOCK==false)
				continue;

			if(priority==2)
				DEBUG_PRINT_NISR("KKNSDSKK","<------- ���ڷ������ٵ� ",EF->SN," ֡����");

			Ecp_Fcb_Flip(EF,priority,EF->SN); //����FCB��ת

			vTaskDelay(pdMS_TO_TICKS(100));

			for(uint8_t retrans=0;retrans<5;retrans++) //�ط�����
			{
				Fill_Ecp_DataCache(EF,priority,EF->SN);

				#ifdef DEBUG_ECP_SEND_FRAME_PRINT
				PRINT_ECP_SEND_FRAME(EF,priority,EF->SN);
				#endif

				if(ulTaskNotifyTake(pdTRUE,pdMS_TO_TICKS(10000))==pdTRUE) //�ȴ�5S��ʱ�ط�
				{
					if(EF->RES[priority].ETQ[(EF->SN+1)%MAX_REPLY_NUM].ISLOCK==false)
						EF->PRIORITY[priority]=0;
					else
						EF->PRIORITY[priority]=EF->SN+1;

					EF->RES[priority].ETQ[EF->SN].ISLOCK=false;
					EF->RES[priority].ETQ[EF->SN].STATUS=false;

					return true;
				}

				if(retrans==4) //���ʹ�������
				{
					EF->SN=0;
					EF->ISLOCK=false;
					EF->FILE.STATE=0;
					memset(EF->FILE.DATA,0,22);
					EF->LINKSTATE=LINKSTATE_START; //��·�Ͽ�

					for(uint8_t i=1;i<MAX_PRIORITY_NUM;i++)
					{
						EF->PRIORITY[i]=0;

						for(uint8_t j=0;j<MAX_REPLY_NUM;j++) //���������͵ı���
						{
							EF->RES[i].ETQ[j].ISLOCK=false;
							EF->RES[i].ETQ[j].STATUS=false;
						}
					}

					memset(gFAULTINFO.DATA,0,FAULT_DATA_LEN); //���gFAULTINFO

					Log_Data_Record(0x07,"S","101��·���ͱ��ĳ�ʱ,101��·�ѶϿ�!"); //��·�Ͽ��¼���־

					#ifdef STATUS_LED2_ECP_LINKSTATE_CONTROL
					Status_Led2_Set();
					#endif

					return false;
				}
			}
		}
	}

	return false;
}
/************************************************************!
*Function:
*Description:
*Input:
*Output: null
*Return: null
*************************************************************/
bool Ecp_Yc_Timing_Report(ECPFRAME *EF)
{
	uint8_t lens;
	uint8_t priority,sn;

	#ifndef ECP_LINKSTATE_CONTROL
	if(EF->LINKSTATE==LINKSTATE_START)
		return false;
	#endif

	if(gECPPARA.YC_REPORT_MODE==0)  //0:ң��ͻ���ϱ� 1: ң�������ϱ�
		return false;

	#ifndef ESAMC_FUNCTION_CTRL
	if(EF->ESMSTATE==false)
		return false;
	#endif

	if(((gUNIXTIME.UNIX-10)%gECPPARA.YC_REPORT_CYCLE)!=0)
		return false;

	if(gUNIXTIME.UNIX==gSYSFLAG.STM.YC_REPORT_TIME)
		return false;

	gSYSFLAG.STM.YC_REPORT_TIME=gUNIXTIME.UNIX;


	priority=8;
	sn=Req_Empty_ResFrame(EF,priority); //������õ�Ӧ��֡

	EF->RES[priority].ETQ[sn].EF.VF.CTRL.DATA=0xD3;
	EF->RES[priority].ETQ[sn].EF.VF.ASDU.TI=9;     //��һ��ֵ
	EF->RES[priority].ETQ[sn].EF.VF.ASDU.COT.U16=1; //����/ѭ��

	lens=Get_AllCall_Yc(EF->RES[priority].ETQ[sn].EF.DATA+13);
	EF->RES[priority].ETQ[sn].EF.VF.ASDU.VSQ=0x80+(lens/3);

	#ifdef ESAMC_FUNCTION_CTRL
	Fill_Ecp_Frame(EF,VAR_FRAME,priority,sn,lens);
	#else
	Fill_Ecp_Frame(EF,ESM_FRAME,priority,sn,lens);
	#endif

	#ifdef PRINT_YC_DEPORT_DEBUG //��ӡ�ϱ���ң����Ϣ
	DEBUG_PRINT_NISR("KKNSKK","<---------- ���ϱ���վң������!ң����������: ---------->\r\n");
	DEBUG_PRINT_U8CHAR_ARRAY_NISR(EF->RES[priority].ETQ[sn].EF.DATA+13,lens);
	#endif

	return true;
}
/************************************************************!
*Function:
*Description:
*Input:
*Output: null
*Return: null
*************************************************************/
bool Yc_Sudden_Report(ECPDATA_YC *YC,uint16_t value,uint16_t threshold)
{
	uint8_t priority,sn;

	if(gECPPARA.YC_REPORT_MODE==1) //�����ϱ�ң��,ֻ��Ҫ����ң������
	{
		YC->MSG.U16=value; //���±仯��ң��ֵ

		return false;
	}

	if(abs(value-YC->MSG.U16)<threshold) //�仯��ң��ֵС��֮ǰ��Ҫ��ֵ,��ͻ���ϱ�ң��,Ҳ������ң��ֵ
		return false;

	#ifdef PRINT_YC_REPORT_DEBUG
	DEBUG_PRINT_NISR("KNSK","<-------- �ѽ���ͻ���ϱ�YC�߳�,���ڴ���ͻ���ϱ�����:");
	DEBUG_PRINT_NISR("NSDSDSDK","<-------- δ����ң��ֵ ",YC->MSG.U16," ����ң��ֵ ",value," ��ֵ ",threshold);
	#endif

	#ifndef ESAMC_FUNCTION_CTRL
	if(gECPFRAMELIST.ESMSTATE==false) //
		return false;
	#endif

	YC->MSG.U16=value; //���±仯��ң��ֵ

	priority=8;
	sn=Req_Empty_ResFrame(&gECPFRAMELIST,priority); //������õ�Ӧ��֡

	gECPFRAMELIST.RES[priority].ETQ[sn].EF.VF.CTRL.DATA=0xD3;
	gECPFRAMELIST.RES[priority].ETQ[sn].EF.VF.ASDU.TI=9;     //��һ��ֵ
	gECPFRAMELIST.RES[priority].ETQ[sn].EF.VF.ASDU.VSQ=1;
	gECPFRAMELIST.RES[priority].ETQ[sn].EF.VF.ASDU.COT.U16=3; //ͻ��
	gECPFRAMELIST.RES[priority].ETQ[sn].EF.VF.ASDU.MSGADDR.U16=YC->ADDR.U16;
	memcpy(gECPFRAMELIST.RES[priority].ETQ[sn].EF.VF.ASDU.MSG,&YC->MSG.U16,sizeof(uint16_t));
	gECPFRAMELIST.RES[priority].ETQ[sn].EF.VF.ASDU.MSG[2]=YC->QDS.U16;

	#ifdef ESAMC_FUNCTION_CTRL
	Fill_Ecp_Frame(&gECPFRAMELIST,VAR_FRAME,priority,sn,3);
	#else
	Fill_Ecp_Frame(&gECPFRAMELIST,ESM_FRAME,priority,sn,3);
	#endif

	return true;
}
/************************************************************!
*Function:
*Description:
*Input:
*Output: null
*Return: null
*************************************************************/
uint16_t Ecp_Get_MultiPara(uint8_t vsq,uint8_t *addr, uint8_t *para)
{
	DOUBLEBYTE DB;
	uint16_t pos=0;
	uint16_t paranum=(sizeof(PARA_AREA)/sizeof(FLASHPARAARRAY));

	if(vsq==0)
	{
		for(uint16_t i=0;i<paranum;i++)
		{
			memcpy(para+pos,&PARA_AREA[i].MSGADDR,sizeof(uint16_t));
			pos+=2;

			para[pos++]=PARA_AREA[i].TAG;
			para[pos++]=PARA_AREA[i].LEN;

			Mx25_Read_U8_Array(PARA_AREA[i].PARAADDR,para+pos,PARA_AREA[i].LEN,false);
			pos+=PARA_AREA[i].LEN;
		}
	}

	if(vsq>0)
	{
		for(uint8_t i=0;i<vsq;i++)
		{
			memcpy(DB.U8,addr+2*i,2);

			for(uint16_t i=0;i<paranum;i++)
			{
				if(DB.U16==PARA_AREA[i].MSGADDR)  //δ����û�е���Ϣ���ַ
				{
					memcpy(para+pos,&PARA_AREA[i].MSGADDR,sizeof(uint16_t));
					pos+=2;

					para[pos++]=PARA_AREA[i].TAG;
					para[pos++]=PARA_AREA[i].LEN;

					Mx25_Read_U8_Array(PARA_AREA[i].PARAADDR,para+pos,PARA_AREA[i].LEN,false);
					pos+=PARA_AREA[i].LEN;

					break;
				}
			}
		}
	}

	return pos;
}
/************************************************************!
*Function:
*Description:
*Input:
*Output: null
*Return: null
*************************************************************/
uint32_t Search_MultiPara_Pos(uint8_t *para,uint16_t lens,uint16_t pos)
{
	FOURBYTE FB;    //FB.U16[0] ��POS    FB.U16[1]:VSQ
	DOUBLEBYTE DB;
	uint16_t paranum=(sizeof(PARA_AREA)/sizeof(FLASHPARAARRAY));

	FB.U32=0;

	while((pos+FB.U16[0].U16)!=lens)
	{
		memcpy(DB.U8,para+FB.U16[0].U16,2);

		for(uint16_t i=0;i<paranum;i++)
		{
			if(DB.U16==PARA_AREA[i].MSGADDR)
			{
				FB.U16[1].U16+=1;
				FB.U16[0].U16+=4+PARA_AREA[i].LEN;

				if(FB.U16[0].U16>ECP_DATA_SEND_LEN)
			 	{
					FB.U16[1].U16-=1;
					FB.U16[0].U16-=4+PARA_AREA[i].LEN;

					return FB.U32;
			 	}
			}
		}
	}

	return FB.U32;
}




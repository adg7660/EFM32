/******************************************************************!
*Copyright (c), 2008-2017, Qingdao Topscomm Communication Co .Ltd.
*File name: hal_rtc.c
*Version: 0.1.0
*Date: 2016-11-22
*Author: WANGJIANHUI
*Description:
*******************************************************************/
#include "hal_rtc.h"
#include "include.h"


/**********RTC�жϻص�ע�����**********/
RTC_INT_CB RtcIntCb=NULL;
/************************************************************!
*Function: Rtc_Init
*Description: RTC��ʼ������,����RTCģʽΪ���ж�,ʱ��Ϊ32768
*Input: null
*Output: null
*Return: null
*************************************************************/
void Rtc_Init(void)
{
	CMU_ClockSelectSet(cmuClock_LFA,cmuSelect_LFXO); //RTCʱ��

	CMU_ClockEnable(cmuClock_RTC,true);

	RTC_Init_TypeDef rtcinit=RTC_INIT_DEFAULT;

	rtcinit.comp0Top=true;

	RTC_CompareSet(0,32767); //����COMP0Ϊ32768,��ɼ���Ԫ��CNTͬ��

	RTC_Init(&rtcinit);

	RTC_IntEnable(RTC_IF_COMP0);

	NVIC_ClearPendingIRQ(RTC_IRQn);
	NVIC_EnableIRQ(RTC_IRQn);

	//NVIC_SetPriority(RTC_IRQn,16);
}
/************************************************************!
*Function: Get_Rtc_Cnt
*Description: ��ȡRTC��CNT����ֵ,����ֵ��ΧΪ0-32767
*Input: null
*Output: null
*Return: CNT����ֵ
*************************************************************/
uint16_t Get_Rtc_Cnt(void)
{
	return (uint16_t)RTC->CNT;
}
/************************************************************!
*Function: Set_Rtc_Cnt
*Description: ����RTC��CNT����ֵ,����ֵ��ΧΪ0-32767
*Input: null
*Output: null
*Return: null
*************************************************************/
void Set_Rtc_Cnt(uint16_t cnt)
{
	RTC->CNT=(uint32_t)cnt;
}
/************************************************************!
*Function: Rtc_Int_CallBack
*Description:
*Input: null
*Output: null
*Return: null
*************************************************************/
void Rtc_Int_CallBack(RTC_INT_CB func)
{
	RtcIntCb=func;
}
/************************************************************!
*Function: RTC_IRQHandler
*Description: RTC���жϺ���
*Input: null
*Output: null
*Return: null
*************************************************************/
void RTC_IRQHandler(void)
{
	RTC_IntClear(RTC_IF_COMP0);

	if(RtcIntCb!=NULL)
		(*RtcIntCb)();
}


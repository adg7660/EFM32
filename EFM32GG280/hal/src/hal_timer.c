/******************************************************************!
*Copyright (c), 2008-2017, Qingdao Topscomm Communication Co .Ltd.
*File name: hal_timer.c
*Version: 0.1.0
*Date: 2016-09-20
*Author: WANGJIANHUI
*Description:
*******************************************************************/
#include "include.h"
#include "hal_timer.h"

/**********TIMER0�жϻص�ע�����**********/
TIMER0_INT_CB Timer0IntCb=NULL;
/**********LEUART0 TX�жϻص�ע�����**********/
LETIMER0_INT_CB Letimer0IntCb=NULL;
/************************************************************!
*Function: Timer0_Init
*Description: TIMER0��ʼ������,����1ms�ж�
*Input: null
*Output: null
*Return: null
*************************************************************/
void Timer0_Init(void)
{
	CMU_ClockEnable(cmuClock_TIMER0,true);

	TIMER_Init_TypeDef timer0init=TIMER_INIT_DEFAULT;

	timer0init.debugRun=true;
	timer0init.prescale=timerPrescale1;
	timer0init.clkSel=timerClkSelHFPerClk;

	TIMER_InitCC_TypeDef timer0initcc2=TIMER_INITCC_DEFAULT;

	timer0initcc2.edge=timerEdgeBoth;
	timer0initcc2.mode=timerCCModePWM;
	timer0initcc2.cmoa=timerOutputActionToggle;

	TIMER_InitCC(TIMER0,2,&timer0initcc2);

	TIMER_Init(TIMER0,&timer0init);

	TIMER_TopSet(TIMER0,7000000/1000); //PWMƵ���趨Ϊ40K

	TIMER_CompareBufSet(TIMER0,2,((7000000/1000)*5/100)); //ռ�ձ�10%

	TIMER0->ROUTE|=TIMER_ROUTE_CC2PEN|TIMER_ROUTE_LOCATION_LOC0;

	GPIO_PinModeSet(gpioPortA,2,gpioModePushPull,1); //PA2���PWM����RUN_LED

	TIMER0->CMD=0b10; //0b:������,�ر�PWM
}
/************************************************************!
*Function: Timer0_Int_CallBack
*Description:
*Input: null
*Output: null
*Return: null
*************************************************************/
void Timer0_Int_CallBack(TIMER0_INT_CB func)
{
	Timer0IntCb=func;
}
/************************************************************!
*Function: Timer0_Start
*Description: TIMER0��������
*Input: null
*Output: null
*Return: null
*************************************************************/
void Timer0_Start(void)
{
	TIMER0->CMD=0b01; //0b:������
}
/************************************************************!
*Function: Timer0_Stop
*Description: TIMER0ֹͣ����
*Input: null
*Output: null
*Return: null
*************************************************************/
void Timer0_Stop(void)
{
	TIMER0->CMD=0b10;
}
/************************************************************!
*Function: Timer2_Init
*Description: TIMER1��ʼ�������������̶�ռ�ձȵ�PWM�����
*Input: null
*Output: null
*Return: null
*************************************************************/
void Timer2_Init(void)
{
	CMU_ClockEnable(cmuClock_TIMER2,true);

	TIMER_Init_TypeDef timer2init=TIMER_INIT_DEFAULT;

	timer2init.debugRun=true;
	timer2init.prescale=timerPrescale2; //2��Ƶ,14M
	timer2init.clkSel=timerClkSelHFPerClk; //28M

	TIMER_InitCC_TypeDef timer2initCC2=TIMER_INITCC_DEFAULT;

	timer2initCC2.edge=timerEdgeBoth;
	timer2initCC2.mode=timerCCModePWM;
	timer2initCC2.cmoa=timerOutputActionToggle;

	TIMER_InitCC(TIMER2,2,&timer2initCC2);

	TIMER_Init(TIMER2,&timer2init);

	TIMER_TopSet(TIMER2,7000000/40000); //PWMƵ���趨Ϊ40K

	TIMER_CompareBufSet(TIMER2,2,((7000000/40000)*10/100)); //ռ�ձ�50%

	TIMER2->ROUTE|=TIMER_ROUTE_CC2PEN|TIMER_ROUTE_LOCATION_LOC2;

	GPIO_PinModeSet(gpioPortC,10,gpioModePushPull,1); //PC13���PWM

	TIMER2->CMD=0b10; //0b:������,�ر�PWM
}
/************************************************************!
*Function: Letimer0_Init
*Description: LETIMER0��ʼ��������LETIMER0ֻ�谴��32768Ƶ�ʼ򵥼���
*             ���ɣ�CNT�Ĵ���ֵ���Զ���������д������Ļ�����CMD�Ĵ�
*             ����CLEAR���
*Input: null
*Output: null
*Return: null
*************************************************************/
void Letimer0_Init(void)
{
	CMU_ClockSelectSet(cmuClock_LFA,cmuSelect_LFXO); //LETIMER0ʱ��

	CMU_ClockEnable(cmuClock_LETIMER0,true);

	LETIMER_Init_TypeDef letimer0init=LETIMER_INIT_DEFAULT;
	letimer0init.enable=false;
	letimer0init.rtcComp0Enable=true;
	letimer0init.debugRun=true;
	letimer0init.comp0Top=true;

	LETIMER_CompareSet(LETIMER0,0,511);
	LETIMER_RepeatSet(LETIMER0,0,1);

	LETIMER_Init(LETIMER0,&letimer0init);

	LETIMER_IntEnable(LETIMER0,LETIMER_IF_COMP0);
	NVIC_ClearPendingIRQ(LETIMER0_IRQn);
	NVIC_EnableIRQ(LETIMER0_IRQn);
}
/************************************************************!
*Function: Letimer0_Int_CallBack
*Description:
*Input: null
*Output: null
*Return: null
*************************************************************/
void Letimer0_Int_CallBack(LETIMER0_INT_CB func)
{
	Letimer0IntCb=func;
}
/************************************************************!
*Function: Timer2_Start
*Description: TIMER2��������
*Input: null
*Output: null
*Return: null
*************************************************************/
void Timer2_Start(void)
{
	TIMER2->CMD=0b01; //0b:������
}
/************************************************************!
*Function: Timer2_Stop
*Description: TIMER2ֹͣ����
*Input: null
*Output: null
*Return: null
*************************************************************/
void Timer2_Stop(void)
{
	TIMER2->CMD=0b10;
}
/************************************************************!
*Function: TIMER0_IRQHandler
*Description: TIMER0�жϺ���
*Input: null
*Output: null
*Return: null
*************************************************************/
void TIMER0_IRQHandler(void)
{
	TIMER_IntClear(TIMER0,TIMER_IF_OF);

	if(Timer0IntCb!=NULL)
		(*Timer0IntCb)();
}
/************************************************************!
*Function: LETIMER0_IRQHandler
*Description: LETIMER0�жϺ���
*Input: null
*Output: null
*Return: null
*************************************************************/
void LETIMER0_IRQHandler(void)
{
	LETIMER_IntClear(LETIMER0,LETIMER_IF_COMP0);

	if(Letimer0IntCb!=NULL)
		(*Letimer0IntCb)();
}


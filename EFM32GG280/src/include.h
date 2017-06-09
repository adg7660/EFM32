/******************************************************************!
*Copyright (c), 2008-2017, Qingdao Topscomm Communication Co .Ltd.
*File name: include.h
*Version: 0.1.0
*Date: 2016-09-20
*Author: WANGJIANHUI
*Description:
*******************************************************************/
#ifndef INCLUDE_H_
#define INCLUDE_H_


#define SYS_VERSION "SOFTWARE_VERSION: 0.7.11_201706021823"

//��Ƶ����ģʽ
#define RADIO_LDC_MODE 1
//��Ƶ���ͼ��ܺ���,����:����,�ر�:������
//#define RADIO_AES_ENCRYPTION 1
//������ϳ�ʼ����·���ֳ���
//#define HUNAN_101INIT 1

//ESAM���ܿ���,����:�ر�ESAM,�ر�:����ESAM����
#define ESAMC_FUNCTION_CTRL

#define DEFAULT_FAULT_WAVE_NUM 0x6A
//ϵͳ������Ϣ�궨��
#define ABOS_DEBUG 1

#ifdef ABOS_DEBUG

//��ӡϵͳ��ʼ��������Ϣ,����:��ӡ,�ر�:����ӡ
#define PRINT_SYS_INIT_DEBUG 1

//Ĭ�ϲ�������,����:Ĭ�ϲ���,�ر�:MX25����
#define DEFAULT_PARA_DEBUG 1

//��ӡICP����֡������Ϣ,����:��ӡ,�ر�:����ӡ
#define PRINT_ICP_FRAME_PARSE_DEBUG 1

//��ӡ����MX25��Ϣ,����:��ӡ,�ر�:����ӡ
#define PRINT_MX25_ERASE_DEBUG 1

//��ӡESAM������Ϣ,����:��ӡ,�ر�:����ӡ
//#define PRINT_ESAM_INFO_DEBUG 1

//RTOS�����ջ�ռ���,����:���,�ر�:�����
#define TASKSTACK_HIGHWATERMARK  1

//LED1��Ϊ��Ƶ������ʾ,����:��ʾ,�ر�:����ʾ
#define STATUS_LED1_RADIO_STATE_DEBUG 1

//LED1��Ϊϵͳ�ڹ���λ��ʾ,����:��ʾ,�ر�:����ʾ
#define STATUS_LED1_SYS_RESET_DEBUG 1

//LED2��Ϊ��·״̬��ʾ,����:��ʾ,�ر�:����ʾ
//#define STATUS_LED2_ECP_LINKSTATE_CONTROL 1

//LED2��Ϊϵͳ�ڹ���λ��ʾ,����:��ʾ,�ر�:����ʾ
#define STATUS_LED2_SYS_RESET_DEBUG 1

//LED2��Ϊ�ɼ���Ԫ������ʾ,����:��ʾ,�ر�:����ʾ
//#define STATUS_LED2_AU_TIMING_ASYNC 1

//LED2��ΪGPSУʱ�ɹ���ת��ʾ,����:��ʾ,�ر�:����ʾ
//#define STATUS_LED2_GPS_TIMING_DEBUG 2

//��ӡ�ɼ���Ԫ������Ϣ,����:��ӡ,�ر�:����ӡ
#define PRINT_AU_ONLINE_OFFLINE_DEBUG 1

//ͳ�Ʋɼ���ԪУʱӦ��,����:ͳ��,�ر�:��ͳ��
#define PRINT_AU_TIMING_ASYNC_DEBUG 1

//��ӡ�ɼ���Ԫʱ���ʱ��,����:��ӡ,�ر�:����ӡ
//#define PRINT_AUTIMING_TIMESTAMP_DEBUG 1

//��ӡ�ɼ���Ԫ����ģʽ�л���Ϣ,����:��ӡ,�ر�:����ӡ
#define PRINT_AU_WORKMODE_DEBUG 1

//��ӡϵͳ��ѹ��Ϣ,����:��ӡ,�ر�:����ӡ
#define PRINT_SYS_VOL_DEBUG 1

//��ӡ����¼��������Ϣ,����:��ӡ,�ر�:����ӡ
#define PRINT_TRIGGER_CALL_WAVE_DEBUG 1

//��ӡ�ɼ���Ԫң�����ݵ���ͳ��,����:��ӡ,�ر�:����ӡ
#define AU_YC_LOST_STATS_DEBUG 1

//��ӡң���ϱ���Ϣ,����:��ӡ,�ر�:����ӡ
//#define PRINT_YC_REPORT_DEBUG 1

//��ӡ�ɼ���Ԫң������,����:��ӡ,�ر�:����ӡ
#define PRINT_AU_YC_DATA_DEBUG 1

//��ӡMX25 ��־��Ϣ,����:��ӡ,�ر�:����ӡ
#define PRINT_MX25_LOG_DEBUG

//��ӡMX25 SOE��Ϣ,����:��ӡ,�ر�:����ӡ
#define PRINT_MX25_SOE_DEBUG 1

//��ӡMX25 SOE��Ϣ,����:��ӡ,�ر�:����ӡ
#define PRINT_MX25_YK_DEBUG 1

//��ӡMX25 FAULT��Ϣ,����:��ӡ,�ر�:����ӡ
#define PRINT_MX25_FAULT_DEBUG 1

//��ӡECPң����Ϣ,����:��ӡ,�ر�:����ӡ
#define PRINT_ECP_YK_DEBUG 1

//��ӡ�ɼ���Ԫ¼������֡,����:��ӡ,�ر�:����ӡ
//#define PRINT_AU_WAVE_DATA_DEBUG 1

//��ӡ���ϵ�ѹ������������,����:��ӡ,�ر�:����ӡ
//#define PRINT_WAVE_DEBUG 1

//��ӡ�����ļ���Ϣ,����:��ӡ,�ر�:����ӡ
//#define PRINT_WAVE_FILE_DEBUG 1

//��ӡң���ļ�����,����:��ӡ,�ر�:����ӡ
//#define PRINT_YC_FILE_DEBUG 1

//��ӡң���ϱ�����,����:��ӡ,�ر�:����ӡ
#define PRINT_YC_DEPORT_DEBUG 1

//��ӡ��̵�����Ϣ,����:��ӡ,�ر�:����ӡ
#define PRINT_PROGRAM_DEBUG 1

//GPSУʱ����,����:����,�ر�:������
//#define PRINT_GPS_TIMMING_INFO_DEBUG 1

//��ӡ����ABC�����������������Ϣ,����:��ӡ,�ر�:����ӡ
#define PRINT_CORRECT_PHASE_DEBUG 1

//��ӡECP��������֡,����:��ӡ,�ر�:����ӡ
//#define DEBUG_ECP_RECEIVE_FRAME_PRINT 1

//��ӡECP��������֡,����:��ӡ,�ر�:����ӡ
//#define DEBUG_ECP_SEND_FRAME_PRINT 1

//ECP��·����,����:�ر���·����,�ر�:������·����
//#define ECP_LINKSTATE_CONTROL 1

//��ӡ��·״̬��Ϣ,����:��ӡ,�ر�:����ӡ
#define PRINT_LINKSTATE_DEBUG 1

//��ӡSOE�ϱ���վ��Ϣ,����:��ӡ,�ر�:����ӡ
//#define ECP_SOE_REPORT_DEBUG 1

//��ӡ��վУʱ��Ϣ,����:��ӡ,�ر�:����ӡ
#define PRINT_ECP_TIMING_DEBUG 1

//��ӡ�ļ��ϱ���Ϣ,����:��ӡ,�ر�:����ӡ
#define PRINT_ECP_READ_FILE_DEBUG 1

#endif


/***************************ϵͳ�����궨��***********************************/
#define AU_TIMING_ASYNC_BUFFER      2      //Уʱ�첽����:ֻ������N��û���յ�УʱACK�ŶԸ��߽��л���
#define AU_ASYNC_ENTER_LPOWER_MODE  12     //������ʧN��УʱӦ��,���߽���͹���ģʽ


/**********��׼C�ļ����⺯��**********/
#include <stddef.h>
#include <string.h>
#include "em_chip.h"
#include "em_device.h"
/**********����ϵͳͷ�ļ�**********/
#include "FreeRTOSConfig.h"
#include "FreeRTOS.h"
#include "task.h"
#include "timers.h"
#include "queue.h"
#include "semphr.h"
/**********TASK��ͷ�ļ�**********/
#include "init.h"
#include "mytask.h"
/**********MID��ͷ�ļ�**********/
#include "datacache.h"
#include "database.h"
#include "flashstorage.h"
#include "fault_algorithm.h"
#include "unixtime.h"
#include "systime.h"
#include "mid.h"
#include "print.h"
/**********PROCOTOL��ͷ�ļ�**********/
#include "icp.h"
#include "icp_parse.h"
#include "icp_process.h"
#include "icp_app.h"
#include "ecp.h"
#include "ecp_parse.h"
#include "ecp_process.h"
#include "ecp_app.h"
#include "esam.h"
#include "esam_parse.h"
#include "esam_process.h"
#include "esam_app.h"
/**********SYSDEFͷ�ļ�**********/
#include "sysdef.h"
/**********��Ƶ����ͷ�ļ�**********/
#include "radio_hal.h"
#include "rf_spi.h"
/**********�ײ�����ͷ�ļ�**********/
#include "hal_esam.h"
#include "hal_adc.h"
#include "hal_cmu.h"
#include "hal_dma.h"
#include "hal_gpio.h"
#include "hal_gps.h"
#include "hal_math.h"
#include "hal_mx25.h"
#include "hal_r8025t.h"
#include "hal_timer.h"
#include "hal_usart.h"
#include "hal_wdog.h"
#include "hal_msc.h"
#include "hal_i2c.h"
#include "hal_rtc.h"
#include "hal_aes.h"
#include "hal_emu.h"
#include "em_rmu.h"


#endif


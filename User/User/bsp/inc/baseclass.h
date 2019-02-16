/**
	|-------------------------------- Copyright ----------------------------------------|
	|                                                                                   |
	|                        (C) Copyright 2018,����ƽͷ��,                              |
	|            1 Xuefu Rd, Huadu Qu, Guangzhou Shi, Guangdong Sheng, China            |
	|                            All Rights Reserved                                    |
	|                                                                                   |
	|            By(GCU The wold of team | ����������ѧ����ѧԺ������Ұ�Ƕ�)               |
	|                     https://github.com/GCUWildwolfteam                            |
	|-----------------------------------------------------------------------------------|
	|--FileName    : baseclass.h                                                
	|--Version     : v1.0                                                            
	|--Author      : ����ƽͷ��                                                       
	|--Date        : 2018-11-27 
	|-- Libsupports: STM32CubeF1 Firmware Package V1.6.0 / 17-May-2017(�ñ�Ŀ�����������)              
	|--Description : 1��֧�ְ���f103vetx                                                     
	|--FunctionList                                                       
	|-------1. ....                                                       
	|          <version>:                                                       
	|     <modify staff>:                                                       
	|             <data>:                                                       
	|      <description>:                                                        
	|-------2. ...                                                       
	|---------------------------------declaration of end---------------------------------|
 **/
#ifndef __BASECLASS_H 
#define __BASECLASS_H 
/* -------- stm32 ��ѡ�� 1�ǿ�����0�ǿ���--------- */
#define HAL_F1 0
#define HAL_F4 1
#if HAL_F1 
	// #include "stm32f1xx_hal.h"
	// #include <stdlib.h>
#elif HAL_F4
		#include "stm32f4xx_hal.h"
		#include "cmsis_os.h"
		#include <stdlib.h>
    #include <string.h>
#endif 
	#define MAX(X,Y) (X)>(Y)?(Y):(X)  //������ֵ
	#define MIN(X,Y) (X)<(Y)?(Y):(X)  //����Сֵ
	#define ABS(X) (X)<0?(-X):(X)    //ȡ����ֵ

/* ----------------- ��־λ�����ⲿ���� -------------------- */
	extern unsigned int e_periphera_interface_flag; 	//����ӿ�ʹ��״̬��������
	extern unsigned int e_periphera_error_flag;		//����ӿڴ���״̬��������
	extern unsigned int e_objects_flag;     //����ʹ�ñ�־
/* ----------------- ����ʹ�ñ�־λ��  -------------------- */
	#define USART1_BY_USED    						0x0001U//����1��ʹ��
	#define USART2_BY_USED    						0x0002U//����2��ʹ��
	#define USART3_BY_USED    						0x0004U//����3��ʹ��
	#define UART4_BY_USED    							0x0008U//����4��ʹ��
	#define UART5_BY_USED    							0x0010U//����5��ʹ��
	#define UART6_BY_USED    							0x0020U//����6��ʹ��
	#define USART1_DMA_BY_USED    						0x0040U//����1��ʹ��
	#define USART2_DMA_BY_USED    						0x0080U//����2��ʹ��
	#define USART3_DMA_BY_USED    						0x0100U//����3��ʹ��
	#define UART4_DMA_BY_USED    							0x0200U//����4��ʹ��
	#define UART5_DMA_BY_USED    							0x0400U//����5��ʹ��
	#define UART6_DMA_BY_USED    							0x0800U//����6��ʹ��
	#define CAN1_BY_USED      						0x01000U//can1��ʹ��
	#define CAN2_BY_USED      						0x02000U//can2��ʹ��
	#define WHOLEPOSITOM_CLEAN							0x04000U//ȫ����λ�����ɹ�
/* ----------------- ����ӿڴ���״̬�������� -------------------- */
	#define NO_ERROR   														 0x0000U
	#define FRAME_DROP  													 0x0001U
	#define RX_ERROR    													0x0002U
	#define GET_USART_ADDR_FAIL													0x0004U
	#define GET_CAN_ADDR_FAIL													0x0004U
/* ----------------- ����ʹ�ñ�־�� -------------------- */
	#define NO_CREATE_OBJECTS_OF_WHOLEPOSITION        0x0000U //����ȫ����λ�Ķ���
	#define CREATE_OBJECTS_OF_WHOLEPOSITION        0x0001U //����ȫ����λ�Ķ���
	#define CREATE_OBJECTS_OF_CHASSIS 						0x0002U //������̵Ķ���
	// #define (x,y)
	/* --��������һ��Ҫһ���ã�����֮��һ��Ҫ�ͷ� -- */
	#define CACHE_ADDR(CACHES,ADDRS) 	(CACHES = ADDRS) //�����ַ
	#define FREE_ADDR(CACHES) 	(CACHES = NULL)		//�ͷŵ�ַ  	
	UART_HandleTypeDef* RecognizeUSARTType(UART_HandleTypeDef* huartx);//ʶ�𴮿�����
  CAN_HandleTypeDef* RecognizeCanType(CAN_HandleTypeDef* hcanx);//ʶ��can����
	void SetFrameDropflag(int16_t flag);
	void SetNormalflag(int16_t flag);
	HAL_StatusTypeDef RCREncryption(uint8_t *pdata, uint8_t size);
	HAL_StatusTypeDef RCRDecryption(uint8_t *pdata, uint8_t size);

#endif	// __BASECLASS_H
	
 /*------------------------------------file of end------------------------------------*/


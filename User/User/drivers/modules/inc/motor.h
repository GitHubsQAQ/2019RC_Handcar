/**
	|-------------------------------- Copyright -----------------------------------|
	|                                                                              |
	|                        (C) Copyright 2018,����ƽͷ��,                         |
	|            1 Xuefu Rd, Huadu Qu, Guangzhou Shi, Guangdong Sheng, China       |
	|                            All Rights Reserved                               |
	|                                                                              |
	|            By(GCU The wold of team | ��������ѧ����ѧԺ������Ұ�Ƕ�)          |
	|                     https://github.com/GCUWildwolfteam                       |
	|------------------------------------------------------------------------------|
	|--FileName    : motor.h                                                
	|--Version     : v1.0                                                            
	|--Author      : ����ƽͷ��                                                       
	|--Date        : 2018-12-31               
	|--Libsupports : ��׼���HAL��
	|--Description : 1��maxion���+RoboModule���� 
	|								 2��3508���+c610���
	|								 3��6623���
	|                4��6002���                                  
	|--FunctionList                                                       
	|-------1. ....                                                       
	|          <version>:                                                       
	|     <modify staff>:                                                       
	|             <data>:                                                       
	|      <description>:                                                        
	|-------2. ...                                                       
	|---------------------------------declaration of end----------------------------|
 **/
#ifndef __MOTOR_H 
#define __MOTOR_H
	#include "baseclass.h"
	#include "bsp_can.h" 
/* ================================== maxion of begin ================================= */
		 /* -------- ID�� --------- */
	typedef enum
	{
		openloop_mode_id_e                       = 0x01,//����ģʽid��
		current_mode_id_e                        = 0x02,//����ģʽid��
		velocity_mode_id_e                       = 0x03,//�ٶ�ģʽid��
		position_mode_id_e                       = 0x04,//λ��ģʽid��
		velocity_position_mode_id_e              = 0x05,//�ٶ�λ��ģʽid��
		current_velocity_mode_id_e               = 0x06,//�����ٶ�ģʽid��
		current_position_mode_id_e               = 0x07,//����λ��ģʽid��
		current_velocity_position_mode_id_e      = 0x08 //����λ���ٶ�ģʽid�� 
	}motorIDEnum;
		/* -------- ����ģʽ --------- */
	typedef enum
	{
		openloop_mode_e                       = 0x01,//����ģʽ
		current_mode_e                        = 0x02,//����ģʽ
		velocity_mode_e                       = 0x03,//�ٶ�ģʽ
		position_mode_e                       = 0x04,//λ��ģʽ
		velocity_position_mode_e              = 0x05,//�ٶ�λ��ģʽ
		current_velocity_mode_e               = 0x06,//�����ٶ�ģʽ
		current_position_mode_e               = 0x07,//����λ��ģʽ
		current_velocity_position_mode_e      = 0x08//����λ���ٶ�ģʽ
	}motorModeEnum;
	typedef struct maxionStruct
	{
		int16_t real_current; //��ʵ����
		int16_t real_position;//��ʵ�Ƕ�
		int16_t real_velocity;//��ʵ�ٶ�
		int16_t module_id;
		CAN_HandleTypeDef* hcanx;
	}maxionStruct;
	HAL_StatusTypeDef CAN_RoboModule_DRV_Velocity_Mode(maxionStruct* mst,\
	unsigned char Group,unsigned char Number,short Temp_PWM,short Temp_Velocity);
	void MaxionParseData(maxionStruct*maxion,uint8_t *data);
/* ================================== maxion of end =================================== */

	
/* ----------------- maxion��� -------------------- */




	///* ----------------- �������� -------------------- */
	//	HAL_StatusTypeDef CAN_RoboModule_DRV_Reset(CAN_HandleTypeDef* hcan,\
	//		unsigned char Group,unsigned char Number);
	//	HAL_StatusTypeDef CAN_RoboModule_DRV_Mode_Choice(CAN_HandleTypeDef* hcan,\
	//		unsigned char Group,unsigned char Number,unsigned char Mode);
	//	HAL_StatusTypeDef CAN_RoboModule_DRV_OpenLoop_Mode(CAN_HandleTypeDef* hcan,\
	//		unsigned char Group,unsigned char Number,short Temp_PWM);
	//	HAL_StatusTypeDef CAN_RoboModule_DRV_Current_Mode(CAN_HandleTypeDef* hcan,\
	//		unsigned char Group,unsigned char Number,short Temp_PWM,short Temp_Current);
	//	HAL_StatusTypeDef CAN_RoboModule_DRV_Velocity_Mode(CAN_HandleTypeDef* hcan,\
	//		unsigned char Group,unsigned char Number,short Temp_PWM,short Temp_Velocity);
	//	HAL_StatusTypeDef CAN_RoboModule_DRV_Position_Mode(CAN_HandleTypeDef* hcan,\
	//		unsigned char Group,unsigned char Number,short Temp_PWM,long Temp_Position);
	//	HAL_StatusTypeDef CAN_RoboModule_DRV_Velocity_Position_Mode(CAN_HandleTypeDef* hcan,\
	//		unsigned char Group,unsigned char Number,short Temp_PWM,short Temp_Velocity,long Temp_Position);
	//	HAL_StatusTypeDef CAN_RoboModule_DRV_Current_Velocity_Mode(CAN_HandleTypeDef* hcan,\
	//		unsigned char Group,unsigned char Number,short Temp_Current,short Temp_Velocity);
	//	HAL_StatusTypeDef CAN_RoboModule_DRV_Current_Position_Mode(CAN_HandleTypeDef* hcan,\
	//		unsigned char Group,unsigned char Number,short Temp_Current,long Temp_Position);
	//	HAL_StatusTypeDef CAN_RoboModule_DRV_Current_Velocity_Position_Mode(CAN_HandleTypeDef* hcan,\
	//		unsigned char Group,unsigned char Number,short Temp_Current,short Temp_Velocity,long Temp_Position);
	//	HAL_StatusTypeDef CAN_RoboModule_DRV_Config(CAN_HandleTypeDef* hcan,\
	//		unsigned char Group,unsigned char Number,unsigned char Temp_Time,unsigned char Ctl1_Ctl2);
	//	HAL_StatusTypeDef CAN_RoboModule_DRV_Online_Check(CAN_HandleTypeDef* hcan,\
	//		unsigned char Group,unsigned char Number);

/* ================================== RM6623 of begin ================================= */
	typedef struct RM6623Struct
	{
		uint16_t id;//���can��ip
		int16_t target;		 //Ŀ��ֵ
		int16_t tem_target;//��ʱĿ��ֵ
		int16_t real_current; //��ʵ����
		int16_t real_angle;//��ʵ�Ƕ�
		int16_t tem_angle;//��ʱ�Ƕ�
		int16_t zero;			 //������
		int16_t Percentage;//ת������������ǰ�Ƕ�:���ٺ�ĽǶ� = x:1
		int16_t thresholds; //�����ת��ֵ
		CAN_HandleTypeDef *hcanx;
	} RM6623Struct;
	void RM6623StructInit(RM6623Struct *RM6623,CAN_HandleTypeDef *hcanx);
	void RM6623ParseData(RM6623Struct*RM6623,uint8_t *data);
	/* ================================== RM6623 of end =================================== */
	/* ================================== Rm3508 of begin ================================= */
	typedef struct RM3508Struct
	{
		uint16_t id;//���can��ip
		int16_t target; //Ŀ��ֵ
		int16_t real_current;//��ʵ����
		int16_t real_angle;//��ʵ�Ƕ�
		int16_t real_speed;//��ʵ�ٶ�
		CAN_HandleTypeDef *hcanx;
	}RM3508Struct;
	void RM3508StructInit(RM3508Struct *RM3508,CAN_HandleTypeDef *hcanx);
	void RM3508ParseData(RM3508Struct *RM3508,uint8_t *data);
/* ================================== Rm3508 of end =================================== */
int16_t RatiometricConversion(int16_t real,int16_t threshold,int16_t percentage);
int16_t zeroArgument(int16_t real,int16_t threshold);
#endif	// __MOTOR_H
	
 /*------------------------------------file of end-------------------------------*/



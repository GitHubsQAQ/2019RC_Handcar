/**
	|------------------------------- Copyright ----------------------------------|
	|                                                                            |
	|                        (C) Copyright 2019,����ƽͷ��,                       |
	|          1 Xuefu Rd, Huadu Qu, Guangzhou Shi, Guangdong Sheng, China       |
	|                            All Rights Reserved                             |
	|                                                                            |
	|           By(GCU The wold of team | ����������ѧ����ѧԺ������Ұ�Ƕ�)         |
	|                    https://github.com/GCUWildwolfteam                      |
	|----------------------------------------------------------------------------|
	|--FileName    : chassis.c                                                
	|--Version     : v1.0                                                            
	|--Author      : ����ƽͷ��                                                       
	|--Date        : 2019-01-19               
	|--Libsupports : 
	|--Description :                                                       
	|--FunctionList                                                       
	|-------1. ....                                                       
	|          <version>:                                                       
	|     <modify staff>:                                                       
	|             <data>:                                                       
	|      <description>:                                                        
	|-------2. ...                                                       
	|-------------------------------declaration of end---------------------------|
 **/
#include "chassis.h"
/* -------------- �ṹ������ ----------------- */
  chassisStruct chassis_t;//����
  maxionStruct maxion1_t;
	maxionStruct maxion2_t;
	maxionStruct maxion3_t;
	wholePositionStruct wholePosition_t;
/* -------------- �ⲿ���� ----------------- */
	extern CAN_HandleTypeDef hcan1;
	extern UART_HandleTypeDef huart6;//����1
/* -------------- ˽�к� ----------------- */
#define MODILE_ID1 1
#define MODILE_ID2 2
#define MODILE_ID3 3
#define SPEED_LOOP_PWM			0//�ٶ�ģʽ������ֵ
/*   Group   ȡֵ��Χ 0-7
    Number  ȡֵ��Χ 0-15
	����Number==0ʱ��Ϊ�㲥����*/
#define MOTOR1_GROUP				0//���1�����
#define MOTOR1_NUMBER				1//���1�ĳ�Ա��
#define MOTOR2_GROUP				0//���2�����
#define MOTOR2_NUMBER				2//���2�ĳ�Ա��
#define MOTOR3_GROUP				0//���3�����
#define MOTOR3_NUMBER				3//���3�ĳ�Ա��
	/**
	* @Data    2019-01-19 11:45
	* @brief   �������ݽ���
	* @param   chassisStruct* css ���̽ṹ��ָ��
	* @retval  void
	*/
	void ChassisInit(void)
	{
		chassis_t.pmaxion1_t = &maxion1_t;
		chassis_t.pmaxion2_t = &maxion2_t;
		chassis_t.pmaxion3_t = &maxion3_t;
		chassis_t.pwholePosition_t = &wholePosition_t;
		chassis_t.pmoter_can = &hcan1;
		/* -------- maxion_t1 --------- */
			maxion1_t.hcanx = NULL;
			maxion1_t.real_current = 0;
			maxion1_t.real_velocity = 0;
			maxion1_t.module_id =        \
		  MOTOR_CAN_ID_CAL(MOTOR1_GROUP,MOTOR1_NUMBER); //���1����id
		/* -------- maxion_t2 --------- */
			maxion2_t.hcanx = NULL;
			maxion2_t.real_current = 0;
			maxion2_t.real_velocity = 0;
			maxion2_t.module_id =        \
		  MOTOR_CAN_ID_CAL(MOTOR2_GROUP,MOTOR2_NUMBER); //���2����id
		/* -------- maxion_t3 --------- */
			maxion3_t.hcanx = NULL;
			maxion3_t.real_current = 0;
			maxion3_t.real_velocity = 0;
	   	maxion3_t.module_id =        \
		  MOTOR_CAN_ID_CAL(MOTOR3_GROUP,MOTOR3_NUMBER); //���3����id
			UserCanConfig(chassis_t.pmoter_can);
			WholePositioningInit(&wholePosition_t, &huart6);//ȫ����λ��ʼ��
      ChassisMotorInit(openloop_mode_e);
	}
	/**
	* @Data    2019-01-19 12:01
	* @brief   �������ݽ���
	* @param   Peripheral type��������,����CAN_HandleTypeDef,can�� CAN_HandleTypeDef
	* @retval  void
	*/
	HAL_StatusTypeDef ChassisParseDate(uint32_t id,uint8_t *data)
	{
   	// MotorParseDate(id,data);//can���ݽ���
		ParseWholePositioningInfo(chassis_t.pwholePosition_t);//ȫ����λ���ݽ���
    return HAL_OK;
	}
/**
	* @Data    2019-02-16 10:40
	* @brief   ����can���ݽ��� (�������)
	* @param   void
	* @retval  void
	*/
	HAL_StatusTypeDef MotorParseDate(uint32_t id,uint8_t *data)
	{
		if(id != MODILE_ID1 && id != MODILE_ID2 && id != MODILE_ID3)
      return HAL_BUSY;
		switch (id) 
		{
			case MODILE_ID1:
			  MaxionParseData(&maxion1_t,data);
				break;
			case MODILE_ID2:
				MaxionParseData(&maxion2_t,data);
				break;
			case MODILE_ID3:
				MaxionParseData(&maxion3_t,data);
				break;
			default:
				break;
		}
    return HAL_OK;
	}
/**
	* @Data    2019-02-16 09:53
	* @brief   ���̿��Ʒ�����
	* @param   void
	* @retval  void
	*/
	void ChassisControl(dbusStruct* rc)
	{
//		MotorCanTx(20,20,20);
	}
	/**
	* @Data    2019-02-15 14:15
	* @brief   �ٶȻ����ݷ���
	* @param   void
	* @retval  void
	*/
	void MotorCanTx(int16_t w1,int16_t w2,int16_t w3)
	{
		uint8_t s[8]={0};
    SpeedLoopMode(SPEED_LOOP_PWM,w1,s);
		CanTxMsg(chassis_t.pmoter_can,maxion1_t.module_id,s);
		DataFilling(s,0,8);
		SpeedLoopMode(SPEED_LOOP_PWM,w2,s);
		CanTxMsg(chassis_t.pmoter_can,maxion2_t.module_id,s);
		DataFilling(s,0,8);
		SpeedLoopMode(SPEED_LOOP_PWM,w2,s);
		CanTxMsg(chassis_t.pmoter_can,maxion3_t.module_id,s);
		DataFilling(s,0,8);
	}
 /**
	 * @Data    2019-02-16 16:52 
	 * @brief   ���̵����ʼ��
	 * @param   void
	 * @retval  void
	 */
	 void ChassisMotorInit(uint8_t mode)
	 {
		 	 (chassis_t.pmoter_can,maxion1_t.module_id);//���͸�λָ��
		  ResetMode(chassis_t.pmoter_can,maxion2_t.module_id);//���͸�λָ��
		  ResetMode(chassis_t.pmoter_can,maxion3_t.module_id);//���͸�λָ��
			osDelay(500);//�ȴ�500ms
			ModeSelectionMode(chassis_t.pmoter_can,maxion1_t.module_id,mode);
			ModeSelectionMode(chassis_t.pmoter_can,maxion2_t.module_id,mode);
			ModeSelectionMode(chassis_t.pmoter_can,maxion3_t.module_id,mode);
			osDelay(500);//�ȴ�500ms
		 	// MotorInit(chassis_t.pmoter_can,maxion1_t.module_id,mode);//���1��ʼ��
			// MotorInit(chassis_t.pmoter_can,maxion2_t.module_id,mode);//���2��ʼ��
			// MotorInit(chassis_t.pmoter_can,maxion3_t.module_id,mode);//���3��ʼ��
	 }
/*----------------------------------file of end-------------------------------*/
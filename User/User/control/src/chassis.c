/**
	|-------------------------------- Copyright -----------------------------------|
	|                                                                              |
	|                        (C) Copyright 2019,����ƽͷ��,                         |
	|            1 Xuefu Rd, Huadu Qu, Guangzhou Shi, Guangdong Sheng, China       |
	|                            All Rights Reserved                               |
	|                                                                              |
	|            By(GCU The wold of team | ��������ѧ����ѧԺ������Ұ�Ƕ�)          |
	|                     https://github.com/GCUWildwolfteam                       |
	|------------------------------------------------------------------------------|
	|--FileName    : chassis.c                                                
	|--Version     : v1.0                                                            
	|--Author      : ����ƽͷ��                                                       
	|--Date        : 2019-01-19               
	|--Libsupports : STM32CubeF1 Firmware Package V1.6.0(�ñ�Ŀ�����������)
	|--Description :                                                       
	|--FunctionList                                                       
	|-------1. ....                                                       
	|          <version>:                                                       
	|     <modify staff>:                                                       
	|             <data>:                                                       
	|      <description>:                                                        
	|-------2. ...                                                       
	|---------------------------------declaration of end----------------------------|
 **/
#include "chassis.h"
  maxionStruct maxion_t1;
	maxionStruct maxion_t2;
	maxionStruct maxion_t3;
	wholePositionStruct wholePosition_t;
	extern CAN_HandleTypeDef hcan1;
	extern UART_HandleTypeDef huart6;//����1
#define MODILE_ID1 1
#define MODILE_ID2 2
#define MODILE_ID3 3
	/*---------------------------------80�ַ�����-----------------------------------*/
	/**
	* @Data    2019-01-19 11:45
	* @brief   �������ݽ���
	* @param   chassisStruct* css ���̽ṹ��ָ��
	* @retval  void
	*/
	void ChassisInit(chassisStruct* css)
	{
		css->pmaxion_t1 = &maxion_t1;
		css->pmaxion_t2 = &maxion_t2;
		css->pmaxion_t3 = &maxion_t3;
		css->pwholePosition_t = &wholePosition_t;
		/* -------- maxion_t1 --------- */
		maxion_t1.hcanx = &hcan1;
		maxion_t1.real_current = 0;
		maxion_t1.real_velocity = 0;
		maxion_t1.module_id = MODILE_ID1; //�������
		/* -------- maxion_t2 --------- */
			maxion_t2.hcanx = &hcan1;
			maxion_t2.real_current = 0;
			maxion_t2.real_velocity = 0;
			maxion_t2.module_id =MODILE_ID2;//�������
		/* -------- maxion_t3 --------- */
			maxion_t3.hcanx = &hcan1;
			maxion_t3.real_current = 0;
			maxion_t3.real_velocity = 0;
	    maxion_t3.module_id = MODILE_ID3;//�������
			UserCanConfig(&hcan1);

			WholePositioningInit(&wholePosition_t, &huart6);

	}
/*---------------------------------80�ַ�����-----------------------------------*/
	/**
	* @Data    2019-01-19 12:01
	* @brief   �������ݽ���
	* @param   Peripheral type��������,����CAN_HandleTypeDef,can��CAN_HandleTypeDef
	* @retval  void
	*/
	HAL_StatusTypeDef ChassisParseDate(uint8_t *data)
	{
    uint32_t id =0;
    id = (uint32_t)(data[0]<<24|data[1]<<16|data[2]<<8|data[3]);
    if(id != MODILE_ID1 && id != MODILE_ID2 && id != MODILE_ID3)
      return HAL_BUSY;
		switch (id) 
		{
			case MODILE_ID1:
			MaxionParseData(&maxion_t1,data);
				break;
			case MODILE_ID2:
				MaxionParseData(&maxion_t2,data);
				break;
			case MODILE_ID3:
				MaxionParseData(&maxion_t3,data);
				break;
			default:
				break;
		}
    return HAL_OK;
	}
	/*------------------------------------file of end-------------------------------*/

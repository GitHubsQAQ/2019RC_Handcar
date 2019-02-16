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
	|--FileName    : motor.c                                                
	|--Version     : v1.0                                                            
	|--Author      : ����ƽͷ��                                                       
	|--Date        : 2018-12-31               
	|--Libsupports : ��׼���HAL��
	|--Description : 1��maxion���+RoboModule���� 
	|								 2��3508���+c610���
	|								 3��6623���
	|                4��6002���
	|								 5��                                                        
	|--FunctionList                                                       
	|-------1. ....                                                       
	|          <version>:                                                       
	|     <modify staff>:                                                       
	|             <data>:                                                       
	|      <description>:                                                        
	|-------2. ...                                                       
	|---------------------------------declaration of end----------------------------|
 **/
#include "motor.h" 
	/* ================================== maxion of begin ================================= */
	/*---------------------------------80�ַ�����-----------------------------------*/
		/**
		* @Data    2019-01-04 13:27
		* @brief   �ٶ�ģʽ�µ�����ָ��
		* @param   Group   ȡֵ��Χ 0-7
		* @param	 Number  ȡֵ��Χ 0-15������Number==0ʱ��Ϊ�㲥����
		* @param	 temp_pwm��ȡֵ��Χ���£�
								0 ~ +5000����ֵ5000������temp_pwm = 5000ʱ����������ѹΪ��Դ��ѹ
		* @param	 temp_velocity��ȡֵ��Χ���£�
								-32768 ~ +32767����λRPM
		* @retval  HAL_StatusTypeDef
		*/
		HAL_StatusTypeDef CAN_RoboModule_DRV_Velocity_Mode(maxionStruct* mst,\
		unsigned char Group,unsigned char Number,short Temp_PWM,short Temp_Velocity)
		{
		uint32_t can_id=0x004;
			if((Group<=7)&&(Number<=15))
			{
					can_id |= Group<<8;
					can_id |= Number<<4;
			}
			else
			{
					return HAL_ERROR;
			}
			
			if(Temp_PWM > 5000)
			{
					Temp_PWM = 5000;
			}
			else if(Temp_PWM < -5000)
			{
					Temp_PWM = -5000;
			}
			
			if(Temp_PWM < 0)
			{
					Temp_PWM = abs(Temp_PWM);
			}
			return(UserCanTx(mst->hcanx,can_id,Temp_PWM,Temp_Velocity,0,0));
		}
	/*---------------------------------80�ַ�����-----------------------------------*/
		/**
		* @Data    2019-01-23 00:00
		* @brief   maxioncan���Ľ���
		* @param   void
		* @retval  void
		*/
		void MaxionParseData(maxionStruct*maxion,uint8_t *data)
		{
			maxion->real_current  = (data[0]<<8)|data[1];
			maxion->real_velocity = (data[2]<<8)|data[3];
			maxion->real_position = (data[4]<<24)| (data[5]<<16)| (data[6]<<8)| data[7];

		}
/* ================================== maxion of end =================================== */

//
		/*---------------------------------80�ַ�����-----------------------------------*/
			/**
			* @Data    2019-01-04 12:45
			* @brief  ��λָ�� 
			* @param   Group   ȡֵ��Χ 0-7
			* @param	 Number  ȡֵ��Χ 0-15������Number==0ʱ��Ϊ�㲥����
			* @retval  HAL_StatusTypeDef
			*/
	// HAL_StatusTypeDef CAN_RoboModule_DRV_Reset(CAN_HandleTypeDef* hcan,\
	// unsigned char Group,unsigned char Number)
	// {
	//    unsigned short can_id = 0x000;
	//    hcan->pTxMsg->IDE = CAN_ID_STD;    //��׼֡
	//    hcan->pTxMsg->RTR = CAN_RTR_DATA;  //����֡
	//    hcan->pTxMsg->DLC = 0x08;          //֡����Ϊ8
		
	//    if((Group<=7)&&(Number<=15))
	//    {
	//        can_id |= Group<<8;
	//        can_id |= Number<<4;
	//    }
	//    else
	//    {
	//        return HAL_ERROR;
	//    }
		
	//    hcan->pTxMsg->StdId = can_id;      //֡IDΪ���������CAN_ID
		
	//    hcan->pTxMsg->Data[0] = 0x55;
	//    hcan->pTxMsg->Data[1] = 0x55;
	//    hcan->pTxMsg->Data[2] = 0x55;
	//    hcan->pTxMsg->Data[3] = 0x55;
	//    hcan->pTxMsg->Data[4] = 0x55;
	//    hcan->pTxMsg->Data[5] = 0x55;
	//    hcan->pTxMsg->Data[6] = 0x55;
	//    hcan->pTxMsg->Data[7] = 0x55;
	
	//    return (HAL_CAN_Transmit(hcan,200));
	// //    while(can_tx_success_flag == 0); //���CANоƬ��TJA1050��ע�͵�����жϡ�
	// }
	///*---------------------------------80�ַ�����-----------------------------------*/
	//	/**
	//	* @Data    2019-01-04 13:15
	//	* @brief   ģʽѡ��ָ��
	//	* @param   Group   ȡֵ��Χ 0-7
	//	* @param	 Number  ȡֵ��Χ 0-15������Number==0ʱ��Ϊ�㲥����
	//	* @param	 Mode   ��motor  motorModeEnumö��
	//	* @retval  HAL_StatusTypeDef
	//	*/
	//HAL_StatusTypeDef CAN_RoboModule_DRV_Mode_Choice(CAN_HandleTypeDef* hcan,\
	//unsigned char Group,unsigned char Number,unsigned char Mode)
	//{
	//    unsigned short can_id = 0x001;
	//    
	//    hcan->pTxMsg->IDE = CAN_ID_STD;    //��׼֡
	//    hcan->pTxMsg->RTR = CAN_RTR_DATA;  //����֡
	//    hcan->pTxMsg->DLC = 0x08;          //֡����Ϊ8
	//    
	//    if((Group<=7)&&(Number<=15))
	//    {
	//        can_id |= Group<<8;
	//        can_id |= Number<<4;
	//    }
	//    else
	//    {
	//        return HAL_ERROR;
	//    }
	//    
	//    hcan->pTxMsg->StdId = can_id;      //֡IDΪ���������CAN_ID
	//    
	//    hcan->pTxMsg->Data[0] = Mode;
	//    hcan->pTxMsg->Data[1] = 0x55;
	//    hcan->pTxMsg->Data[2] = 0x55;
	//    hcan->pTxMsg->Data[3] = 0x55;
	//    hcan->pTxMsg->Data[4] = 0x55;
	//    hcan->pTxMsg->Data[5] = 0x55;
	//    hcan->pTxMsg->Data[6] = 0x55;
	//    hcan->pTxMsg->Data[7] = 0x55;
	//    
	//    return (HAL_CAN_Transmit(hcan,200));
	//    //while(can_tx_success_flag == 0); //���CANоƬ��TJA1050��ע�͵�����жϡ�
	//}
	///*---------------------------------80�ַ�����-----------------------------------*/
	//	/**
	//	* @Data    2019-01-04 13:24
	//	* @brief   ����ģʽ�µ�����ָ��
	//	* @param   Group   ȡֵ��Χ 0-7
	//	* @param	 Number  ȡֵ��Χ 0-15������Number==0ʱ��Ϊ�㲥����
	//	* @param	 temp_pwm��ȡֵ��Χ���£�
	//						-5000 ~ +5000����ֵ5000������temp_pwm = ��5000ʱ����������ѹΪ��Դ��ѹ
	//	* @retval  HAL_StatusTypeDef
	//	*/
	//HAL_StatusTypeDef CAN_RoboModule_DRV_OpenLoop_Mode(CAN_HandleTypeDef* hcan,\
	//unsigned char Group,unsigned char Number,short Temp_PWM)
	//{
	//    unsigned short can_id = 0x002;
	//    
	//    hcan->pTxMsg->IDE = CAN_ID_STD;    //��׼֡
	//    hcan->pTxMsg->RTR = CAN_RTR_DATA;  //����֡
	//    hcan->pTxMsg->DLC = 0x08;          //֡����Ϊ8
	//    
	//    if((Group<=7)&&(Number<=15))
	//    {
	//        can_id |= Group<<8;
	//        can_id |= Number<<4;
	//    }
	//    else
	//    {
	//        return HAL_ERROR;
	//    }
	//    
	//    hcan->pTxMsg->StdId = can_id;      //֡IDΪ���������CAN_ID

	//    if(Temp_PWM > 5000)
	//    {
	//        Temp_PWM = 5000;
	//    }
	//    else if(Temp_PWM < -5000)
	//    {
	//        Temp_PWM = -5000;
	//    }
	//    
	//    hcan->pTxMsg->Data[0] = (unsigned char)((Temp_PWM>>8)&0xff);
	//    hcan->pTxMsg->Data[1] = (unsigned char)(Temp_PWM&0xff);
	//    hcan->pTxMsg->Data[2] = 0x55;
	//    hcan->pTxMsg->Data[3] = 0x55;
	//    hcan->pTxMsg->Data[4] = 0x55;
	//    hcan->pTxMsg->Data[5] = 0x55;
	//    hcan->pTxMsg->Data[6] = 0x55;
	//    hcan->pTxMsg->Data[7] = 0x55;
	//    
	//    return (HAL_CAN_Transmit(hcan,200));
	//    //while(can_tx_success_flag == 0); //���CANоƬ��TJA1050��ע�͵�����жϡ�
	//}
	///*---------------------------------80�ַ�����-----------------------------------*/
	//	/**
	//	* @Data    2019-01-04 13:25
	//	* @brief   ����ģʽ�µ�����ָ��
	//	* @param   Group   ȡֵ��Χ 0-7
	//	* @param 	 Number  ȡֵ��Χ 0-15������Number==0ʱ��Ϊ�㲥����
	//	* @param 	 temp_pwm��ȡֵ��Χ���£�
	//							0 ~ +5000����ֵ5000������temp_pwm = 5000ʱ����������ѹΪ��Դ��ѹ
	//	* @param 	 temp_current��ȡֵ��Χ���£�
	//							-32768 ~ +32767����λmA
	//	* @retval  HAL_StatusTypeDef
	//	*/
	//HAL_StatusTypeDef CAN_RoboModule_DRV_Current_Mode(CAN_HandleTypeDef* hcan,\
	//unsigned char Group,unsigned char Number,short Temp_PWM,short Temp_Current)
	//{
	//    unsigned short can_id = 0x003;
	//    
	//    hcan->pTxMsg->IDE = CAN_ID_STD;    //��׼֡
	//    hcan->pTxMsg->RTR = CAN_RTR_DATA;  //����֡
	//    hcan->pTxMsg->DLC = 0x08;          //֡����Ϊ8
	//    
	//    if((Group<=7)&&(Number<=15))
	//    {
	//        can_id |= Group<<8;
	//        can_id |= Number<<4;
	//    }
	//    else
	//    {
	//        return HAL_ERROR;
	//    }
	//    
	//    hcan->pTxMsg->StdId = can_id;      //֡IDΪ���������CAN_ID

	//    if(Temp_PWM > 5000)
	//    {
	//        Temp_PWM = 5000;
	//    }
	//    else if(Temp_PWM < -5000)
	//    {
	//        Temp_PWM = -5000;
	//    }
	//    
	//    if(Temp_PWM < 0)
	//    {
	//        Temp_PWM = abs(Temp_PWM);
	//    }
	//    
	//    hcan->pTxMsg->Data[0] = (unsigned char)((Temp_PWM>>8)&0xff);
	//    hcan->pTxMsg->Data[1] = (unsigned char)(Temp_PWM&0xff);
	//    hcan->pTxMsg->Data[2] = (unsigned char)((Temp_Current>>8)&0xff);
	//    hcan->pTxMsg->Data[3] = (unsigned char)(Temp_Current&0xff);
	//    hcan->pTxMsg->Data[4] = 0x55;
	//    hcan->pTxMsg->Data[5] = 0x55;
	//    hcan->pTxMsg->Data[6] = 0x55;
	//    hcan->pTxMsg->Data[7] = 0x55;
	//    
	//    return (HAL_CAN_Transmit(hcan,200));
	//    //while(can_tx_success_flag == 0); //���CANоƬ��TJA1050��ע�͵�����жϡ�
	//}
	///*---------------------------------80�ַ�����-----------------------------------*/
	//	/**
	//	* @Data    2019-01-04 13:27
	//	* @brief   �ٶ�ģʽ�µ�����ָ��
	//	* @param   Group   ȡֵ��Χ 0-7
	//	* @param	 Number  ȡֵ��Χ 0-15������Number==0ʱ��Ϊ�㲥����
	//	* @param	 temp_pwm��ȡֵ��Χ���£�
	//							 0 ~ +5000����ֵ5000������temp_pwm = 5000ʱ����������ѹΪ��Դ��ѹ
	//	* @param	 temp_velocity��ȡֵ��Χ���£�
	//							 -32768 ~ +32767����λRPM
	//	* @retval  HAL_StatusTypeDef
	//	*/
	//HAL_StatusTypeDef CAN_RoboModule_DRV_Velocity_Mode(CAN_HandleTypeDef* hcan,\
	//unsigned char Group,unsigned char Number,short Temp_PWM,short Temp_Velocity)
	//{
	//    unsigned short can_id = 0x004;
	//    
	//    hcan->pTxMsg->IDE = CAN_ID_STD;    //��׼֡
	//    hcan->pTxMsg->RTR = CAN_RTR_DATA;  //����֡
	//    hcan->pTxMsg->DLC = 0x08;          //֡����Ϊ8
	//    
	//    if((Group<=7)&&(Number<=15))
	//    {
	//        can_id |= Group<<8;
	//        can_id |= Number<<4;
	//    }
	//    else
	//    {
	//        return HAL_ERROR;
	//    }
	//    
	//    hcan->pTxMsg->StdId = can_id;      //֡IDΪ���������CAN_ID

	//    if(Temp_PWM > 5000)
	//    {
	//        Temp_PWM = 5000;
	//    }
	//    else if(Temp_PWM < -5000)
	//    {
	//        Temp_PWM = -5000;
	//    }
	//    
	//    if(Temp_PWM < 0)
	//    {
	//        Temp_PWM = abs(Temp_PWM);
	//    }
	//    
	//    hcan->pTxMsg->Data[0] = (unsigned char)((Temp_PWM>>8)&0xff);
	//    hcan->pTxMsg->Data[1] = (unsigned char)(Temp_PWM&0xff);
	//    hcan->pTxMsg->Data[2] = (unsigned char)((Temp_Velocity>>8)&0xff);
	//    hcan->pTxMsg->Data[3] = (unsigned char)(Temp_Velocity&0xff);
	//    hcan->pTxMsg->Data[4] = 0x55;
	//    hcan->pTxMsg->Data[5] = 0x55;
	//    hcan->pTxMsg->Data[6] = 0x55;
	//    hcan->pTxMsg->Data[7] = 0x55;
	//    
	//    return (HAL_CAN_Transmit(hcan,200));
	//    //while(can_tx_success_flag == 0); //���CANоƬ��TJA1050��ע�͵�����жϡ�
	//}
	///*---------------------------------80�ַ�����-----------------------------------*/
	//	/**
	//	* @Data    2019-01-04 13:28
	//	* @brief   λ��ģʽ�µ�����ָ��
	//	* @param   Group   ȡֵ��Χ 0-7
	//	* @param	Number  ȡֵ��Χ 0-15������Number==0ʱ��Ϊ�㲥����
	//	* @param	temp_pwm��ȡֵ��Χ���£�
	//							0 ~ +5000����ֵ5000������temp_pwm = 5000ʱ����������ѹΪ��Դ��ѹ
	//	* @param	temp_position��ȡֵ��Χ���£�
	//							-2147483648~+2147483647����λqc
	//	* @retval  HAL_StatusTypeDef
	//	*/
	//HAL_StatusTypeDef CAN_RoboModule_DRV_Position_Mode(CAN_HandleTypeDef* hcan,\
	//unsigned char Group,unsigned char Number,short Temp_PWM,long Temp_Position)
	//{
	//    unsigned short can_id = 0x005;
	//    
	//    hcan->pTxMsg->IDE = CAN_ID_STD;    //��׼֡
	//    hcan->pTxMsg->RTR = CAN_RTR_DATA;  //����֡
	//    hcan->pTxMsg->DLC = 0x08;          //֡����Ϊ8
	//    
	//    if((Group<=7)&&(Number<=15))
	//    {
	//        can_id |= Group<<8;
	//        can_id |= Number<<4;
	//    }
	//    else
	//    {
	//        return HAL_ERROR;
	//    }
	//    
	//    hcan->pTxMsg->StdId = can_id;      //֡IDΪ���������CAN_ID

	//    if(Temp_PWM > 5000)
	//    {
	//        Temp_PWM = 5000;
	//    }
	//    else if(Temp_PWM < -5000)
	//    {
	//        Temp_PWM = -5000;
	//    }
	//    
	//    if(Temp_PWM < 0)
	//    {
	//        Temp_PWM = abs(Temp_PWM);
	//    }
	//    
	//    hcan->pTxMsg->Data[0] = (unsigned char)((Temp_PWM>>8)&0xff);
	//    hcan->pTxMsg->Data[1] = (unsigned char)(Temp_PWM&0xff);
	//    hcan->pTxMsg->Data[2] = 0x55;
	//    hcan->pTxMsg->Data[3] = 0x55;
	//    hcan->pTxMsg->Data[4] = (unsigned char)((Temp_Position>>24)&0xff);
	//    hcan->pTxMsg->Data[5] = (unsigned char)((Temp_Position>>16)&0xff);
	//    hcan->pTxMsg->Data[6] = (unsigned char)((Temp_Position>>8)&0xff);
	//    hcan->pTxMsg->Data[7] = (unsigned char)(Temp_Position&0xff);
	//    
	//    return (HAL_CAN_Transmit(hcan,200));
	//    //while(can_tx_success_flag == 0); //���CANоƬ��TJA1050��ע�͵�����жϡ�
	//}
	///*---------------------------------80�ַ�����-----------------------------------*/
	//	/**
	//	* @Data    2019-01-04 13:30
	//	* @brief   �ٶ�λ��ģʽ�µ�����ָ��
	//	* @param   Group   ȡֵ��Χ 0-7
	//	* @param	Number  ȡֵ��Χ 0-15������Number==0ʱ��Ϊ�㲥����
	//	* @param	temp_pwm��ȡֵ��Χ���£�
	//							0 ~ +5000����ֵ5000������temp_pwm = 5000ʱ����������ѹΪ��Դ��ѹ
	//	* @param	temp_velocity��ȡֵ��Χ���£�
	//								0 ~ +32767����λRPM
	//	* @param	temp_position��ȡֵ��Χ���£�
	//							-2147483648~+2147483647����λqc
	//	* @retval  HAL_StatusTypeDef
	//	*/
	//HAL_StatusTypeDef CAN_RoboModule_DRV_Velocity_Position_Mode(CAN_HandleTypeDef* hcan,\
	//unsigned char Group,unsigned char Number,short Temp_PWM,short Temp_Velocity,long Temp_Position)
	//{
	//    unsigned short can_id = 0x006;
	//    
	//    hcan->pTxMsg->IDE = CAN_ID_STD;    //��׼֡
	//    hcan->pTxMsg->RTR = CAN_RTR_DATA;  //����֡
	//    hcan->pTxMsg->DLC = 0x08;          //֡����Ϊ8
	//    
	//    if((Group<=7)&&(Number<=15))
	//    {
	//        can_id |= Group<<8;
	//        can_id |= Number<<4;
	//    }
	//    else
	//    {
	//        return HAL_ERROR;
	//    }
	//    
	//    hcan->pTxMsg->StdId = can_id;      //֡IDΪ���������CAN_ID

	//    if(Temp_PWM > 5000)
	//    {
	//        Temp_PWM = 5000;
	//    }
	//    else if(Temp_PWM < -5000)
	//    {
	//        Temp_PWM = -5000;
	//    }
	//    
	//    if(Temp_PWM < 0)
	//    {
	//        Temp_PWM = abs(Temp_PWM);
	//    }
	//    
	//    if(Temp_Velocity < 0)
	//    {
	//        Temp_Velocity = abs(Temp_Velocity);
	//    }
	//    
	//    hcan->pTxMsg->Data[0] = (unsigned char)((Temp_PWM>>8)&0xff);
	//    hcan->pTxMsg->Data[1] = (unsigned char)(Temp_PWM&0xff);
	//    hcan->pTxMsg->Data[2] = (unsigned char)((Temp_Velocity>>8)&0xff);
	//    hcan->pTxMsg->Data[3] = (unsigned char)(Temp_Velocity&0xff);
	//    hcan->pTxMsg->Data[4] = (unsigned char)((Temp_Position>>24)&0xff);
	//    hcan->pTxMsg->Data[5] = (unsigned char)((Temp_Position>>16)&0xff);
	//    hcan->pTxMsg->Data[6] = (unsigned char)((Temp_Position>>8)&0xff);
	//    hcan->pTxMsg->Data[7] = (unsigned char)(Temp_Position&0xff);
	//    
	//    return (HAL_CAN_Transmit(hcan,200));
	//    //while(can_tx_success_flag == 0); //���CANоƬ��TJA1050��ע�͵�����жϡ�
	//}

	///*---------------------------------80�ַ�����-----------------------------------*/
	//	/**
	//	* @Data    2019-01-04 13:31
	//	* @brief   �����ٶ�ģʽ�µ�����ָ��
	//	* @param   Group   ȡֵ��Χ 0-7
	//	* @param	 Number  ȡֵ��Χ 0-15������Number==0ʱ��Ϊ�㲥����
	//	* @param	 temp_current��ȡֵ��Χ���£�
	//							 0 ~ +32767����λmA
	//	* @param	 temp_velocity��ȡֵ��Χ���£�
	//							 -32768 ~ +32767����λRPM
	//	* @retval  HAL_StatusTypeDef
	//	*/
	//HAL_StatusTypeDef CAN_RoboModule_DRV_Current_Velocity_Mode(CAN_HandleTypeDef* hcan,\
	//unsigned char Group,unsigned char Number,short Temp_Current,short Temp_Velocity)
	//{
	//    unsigned short can_id = 0x007;
	//    
	//    hcan->pTxMsg->IDE = CAN_ID_STD;    //��׼֡
	//    hcan->pTxMsg->RTR = CAN_RTR_DATA;  //����֡
	//    hcan->pTxMsg->DLC = 0x08;          //֡����Ϊ8
	//    
	//    if((Group<=7)&&(Number<=15))
	//    {
	//        can_id |= Group<<8;
	//        can_id |= Number<<4;
	//    }
	//    else
	//    {
	//        return HAL_ERROR;
	//    }
	//    
	//    hcan->pTxMsg->StdId = can_id;      //֡IDΪ���������CAN_ID
	//    
	//    if(Temp_Current < 0)
	//    {
	//        Temp_Current = abs(Temp_Current);
	//    }
	//    
	//    hcan->pTxMsg->Data[0] = (unsigned char)((Temp_Current>>8)&0xff);
	//    hcan->pTxMsg->Data[1] = (unsigned char)(Temp_Current&0xff);
	//    hcan->pTxMsg->Data[2] = (unsigned char)((Temp_Velocity>>8)&0xff);
	//    hcan->pTxMsg->Data[3] = (unsigned char)(Temp_Velocity&0xff);
	//    hcan->pTxMsg->Data[4] = 0x55;
	//    hcan->pTxMsg->Data[5] = 0x55;
	//    hcan->pTxMsg->Data[6] = 0x55;
	//    hcan->pTxMsg->Data[7] = 0x55;
	//    
	//    return (HAL_CAN_Transmit(hcan,200));
	//    //while(can_tx_success_flag == 0); //���CANоƬ��TJA1050��ע�͵�����жϡ�
	//}
	///*---------------------------------80�ַ�����-----------------------------------*/
	//	/**
	//	* @Data    2019-01-04 13:32
	//	* @brief   ����λ��ģʽ�µ�����ָ��
	//	* @param   Group   ȡֵ��Χ 0-7
	//	* @param	 Number  ȡֵ��Χ 0-15������Number==0ʱ��Ϊ�㲥����
	//	* @param	 temp_current��ȡֵ��Χ���£�
	//							 0 ~ +32767����λmA
	//	* @param	 temp_position��ȡֵ��Χ���£�
	//							 -2147483648~+2147483647����λqc
	//	* @retval  HAL_StatusTypeDef
	//	*/
	//HAL_StatusTypeDef CAN_RoboModule_DRV_Current_Position_Mode(CAN_HandleTypeDef* hcan,\
	//unsigned char Group,unsigned char Number,short Temp_Current,long Temp_Position)
	//{
	//    unsigned short can_id = 0x008;
	//    
	//    hcan->pTxMsg->IDE = CAN_ID_STD;    //��׼֡
	//    hcan->pTxMsg->RTR = CAN_RTR_DATA;  //����֡
	//    hcan->pTxMsg->DLC = 0x08;          //֡����Ϊ8
	//    
	//    if((Group<=7)&&(Number<=15))
	//    {
	//        can_id |= Group<<8;
	//        can_id |= Number<<4;
	//    }
	//    else
	//    {
	//        return HAL_ERROR;
	//    }
	//    
	//    hcan->pTxMsg->StdId = can_id;      //֡IDΪ���������CAN_ID

	//    
	//    if(Temp_Current < 0)
	//    {
	//        Temp_Current = abs(Temp_Current);
	//    }
	//    
	//    hcan->pTxMsg->Data[0] = (unsigned char)((Temp_Current>>8)&0xff);
	//    hcan->pTxMsg->Data[1] = (unsigned char)(Temp_Current&0xff);
	//    hcan->pTxMsg->Data[2] = 0x55;
	//    hcan->pTxMsg->Data[3] = 0x55;
	//    hcan->pTxMsg->Data[4] = (unsigned char)((Temp_Position>>24)&0xff);
	//    hcan->pTxMsg->Data[5] = (unsigned char)((Temp_Position>>16)&0xff);
	//    hcan->pTxMsg->Data[6] = (unsigned char)((Temp_Position>>8)&0xff);
	//    hcan->pTxMsg->Data[7] = (unsigned char)(Temp_Position&0xff);
	//    
	//    return (HAL_CAN_Transmit(hcan,200));
	//    //while(can_tx_success_flag == 0); //���CANоƬ��TJA1050��ע�͵�����жϡ�
	//}
	///*---------------------------------80�ַ�����-----------------------------------*/
	//	/**
	//	* @Data    2019-01-04 13:33
	//	* @brief   �����ٶ�λ��ģʽ�µ�����ָ��
	//	* @param   Group   ȡֵ��Χ 0-7
	//	* @param	 Number  ȡֵ��Χ 0-15������Number==0ʱ��Ϊ�㲥����
	//	* @param	 temp_current��ȡֵ��Χ���£�
	//						 	0 ~ +32767����λmA
	//	* @param	 temp_velocity��ȡֵ��Χ���£�
	//						 	0 ~ +32767����λRPM
	//	* @param	 temp_position��ȡֵ��Χ���£�
	//						 	-2147483648~+2147483647����λqc
	//	* @retval  HAL_StatusTypeDef
	//	*/
	//HAL_StatusTypeDef CAN_RoboModule_DRV_Current_Velocity_Position_Mode(CAN_HandleTypeDef* hcan,\
	//unsigned char Group,unsigned char Number,short Temp_Current,short Temp_Velocity,long Temp_Position)
	//{
	//    unsigned short can_id = 0x009;
	//    
	//    hcan->pTxMsg->IDE = CAN_ID_STD;    //��׼֡
	//    hcan->pTxMsg->RTR = CAN_RTR_DATA;  //����֡
	//    hcan->pTxMsg->DLC = 0x08;          //֡����Ϊ8
	//    
	//    if((Group<=7)&&(Number<=15))
	//    {
	//        can_id |= Group<<8;
	//        can_id |= Number<<4;
	//    }
	//    else
	//    {
	//        return HAL_ERROR;
	//    }
	//    
	//    hcan->pTxMsg->StdId = can_id;      //֡IDΪ���������CAN_ID
	//    
	//    if(Temp_Current < 0)
	//    {
	//        Temp_Current = abs(Temp_Current);
	//    }
	//    
	//    if(Temp_Velocity < 0)
	//    {
	//        Temp_Velocity = abs(Temp_Velocity);
	//    }
	//    
	//    hcan->pTxMsg->Data[0] = (unsigned char)((Temp_Current>>8)&0xff);
	//    hcan->pTxMsg->Data[1] = (unsigned char)(Temp_Current&0xff);
	//    hcan->pTxMsg->Data[2] = (unsigned char)((Temp_Velocity>>8)&0xff);
	//    hcan->pTxMsg->Data[3] = (unsigned char)(Temp_Velocity&0xff);
	//    hcan->pTxMsg->Data[4] = (unsigned char)((Temp_Position>>24)&0xff);
	//    hcan->pTxMsg->Data[5] = (unsigned char)((Temp_Position>>16)&0xff);
	//    hcan->pTxMsg->Data[6] = (unsigned char)((Temp_Position>>8)&0xff);
	//    hcan->pTxMsg->Data[7] = (unsigned char)(Temp_Position&0xff);
	//    
	//    return (HAL_CAN_Transmit(hcan,200));
	//    //while(can_tx_success_flag == 0); //���CANоƬ��TJA1050��ע�͵�����жϡ�
	//}
	///*---------------------------------80�ַ�����-----------------------------------*/
	//	/**
	//	* @Data    2019-01-04 13:35
	//	* @brief   ����ָ��
	//	* @param   Temp_Time��ȡֵ��Χ: 0 ~ 255��Ϊ0ʱ��Ϊ�رյ����ٶ�λ�÷�������
	//	* @param	 Ctl1_Ctl2��ȡֵ��Χ��0 or 1 ������Ϊ0 or 1������Ϊ��0��Ϊ�ر�������λ��⹦��
	//						 �ر���ʾ��Ctl1��Ctl2�Ĺ��ܽ�������102 301������汾��������Ctl1_Ctl2 = 0 ����
	//	* @retval  HAL_StatusTypeDef
	//	*/
	//HAL_StatusTypeDef CAN_RoboModule_DRV_Config(CAN_HandleTypeDef* hcan,\
	//unsigned char Group,unsigned char Number,unsigned char Temp_Time,unsigned char Ctl1_Ctl2)
	//{
	//    unsigned short can_id = 0x00A;
	//    
	//    hcan->pTxMsg->IDE = CAN_ID_STD;    //��׼֡
	//    hcan->pTxMsg->RTR = CAN_RTR_DATA;  //����֡
	//    hcan->pTxMsg->DLC = 0x08;          //֡����Ϊ8
	//    
	//    if((Group<=7)&&(Number<=15))
	//    {
	//        can_id |= Group<<8;
	//        can_id |= Number<<4;
	//    }
	//    else
	//    {
	//        return HAL_ERROR;
	//    }
	//    
	//    if((Ctl1_Ctl2 != 0x00)&&(Ctl1_Ctl2 != 0x01))
	//    {
	//        Ctl1_Ctl2 = 0x00;
	//    }
	//    
	//    hcan->pTxMsg->StdId = can_id;      //֡IDΪ���������CAN_ID
	//    
	//    hcan->pTxMsg->Data[0] = Temp_Time;
	//    hcan->pTxMsg->Data[1] = Ctl1_Ctl2;
	//    hcan->pTxMsg->Data[2] = 0x55;
	//    hcan->pTxMsg->Data[3] = 0x55;
	//    hcan->pTxMsg->Data[4] = 0x55;
	//    hcan->pTxMsg->Data[5] = 0x55;
	//    hcan->pTxMsg->Data[6] = 0x55;
	//    hcan->pTxMsg->Data[7] = 0x55;
	//    
	//    return (HAL_CAN_Transmit(hcan,200));
	//    //while(can_tx_success_flag == 0); //���CANоƬ��TJA1050��ע�͵�����жϡ�
	//}
	///*---------------------------------80�ַ�����-----------------------------------*/
	//	/**
	//	* @Data    2019-01-04 13:36
	//	* @brief   ���߼��
	//	* @param   Group   ȡֵ��Χ 0-7
	//	* @param	 Number  ȡֵ��Χ 0-15������Number==0ʱ��Ϊ�㲥����
	//	* @retval  HAL_StatusTypeDef
	//	*/
	//HAL_StatusTypeDef CAN_RoboModule_DRV_Online_Check(CAN_HandleTypeDef* hcan,\
	//unsigned char Group,unsigned char Number)
	//{
	//    unsigned short can_id = 0x00F;
	//    
	//    hcan->pTxMsg->IDE = CAN_ID_STD;    //��׼֡
	//    hcan->pTxMsg->RTR = CAN_RTR_DATA;  //����֡
	//    hcan->pTxMsg->DLC = 0x08;          //֡����Ϊ8
	//    
	//    if((Group<=7)&&(Number<=15))
	//    {
	//        can_id |= Group<<8;
	//        can_id |= Number<<4;
	//    }
	//    else
	//    {
	//        return HAL_ERROR;
	//    }
	//    
	//    hcan->pTxMsg->StdId = can_id;      //֡IDΪ���������CAN_ID
	//    
	//    hcan->pTxMsg->Data[0] = 0x55;
	//    hcan->pTxMsg->Data[1] = 0x55;
	//    hcan->pTxMsg->Data[2] = 0x55;
	//    hcan->pTxMsg->Data[3] = 0x55;
	//    hcan->pTxMsg->Data[4] = 0x55;
	//    hcan->pTxMsg->Data[5] = 0x55;
	//    hcan->pTxMsg->Data[6] = 0x55;
	//    hcan->pTxMsg->Data[7] = 0x55;
	//    
	//    return (HAL_CAN_Transmit(hcan,200));
	//    //while(can_tx_success_flag == 0); //���CANоƬ��TJA1050��ע�͵�����жϡ�
	//}
/* ================================== RM6623 of begin ================================= */
	static int16_t s_max_motor_lines = 8192 ;//���һȦ�������
	/*---------------------------------80�ַ�����-----------------------------------*/
	/**
		* @Data    2019-01-18 19:59
		* @brief   RM6623�ṹ���ʼ��
		* @param   RM6623����ṹ���ַ
		* @retval  void
		*/
	void RM6623StructInit(RM6623Struct *RM6623,CAN_HandleTypeDef *hcanx)
	{
		RM6623->id = 0;
		RM6623->target = 0;				//Ŀ��ֵ
		RM6623->tem_target = 0;		//��ʱĿ��ֵ
		RM6623->real_current = 0; //��ʵ����
		RM6623->real_angle = 0;		//��ʵ�Ƕ�
		RM6623->tem_angle = 0;		//��ʱ�Ƕ�
		RM6623->zero = 0;					//������
		RM6623->Percentage = 0;		//ת������������ǰ�Ƕ�:���ٺ�ĽǶ� = x:1��
		RM6623->hcanx = hcanx;
		/*���ݶ�ȡʱ�������������ת������p��thresholds = p -s_max_motor_lines */
		RM6623->thresholds = 1200 - s_max_motor_lines;//1200��Ϲ���ģ���ƽ�
	}
	/*---------------------------------80�ַ�����-----------------------------------*/
		/**
		* @Data    2019-01-18 20:03
		* @brief   6623���ݽ���
		* @param   RM6623����ṹ���ַ
		* @retval  HAL Status
		*/
	void RM6623ParseData(RM6623Struct*RM6623,uint8_t *data)
	{
		int16_t tem_angle = 0;
		RM6623->real_current = ((int16_t)(data[4] << 8) | data[5]);
		tem_angle = ((int16_t)(data[0] << 8) | data[1]);
		tem_angle = RatiometricConversion(tem_angle, RM6623->thresholds, RM6623->Percentage);
		RM6623->real_angle = zeroArgument(tem_angle, RM6623->thresholds);
	}

/* ================================== RM6623 of end =================================== */
/* ================================== 3508 of begin ================================= */
	/*---------------------------------80�ַ�����-----------------------------------*/
	/**
		* @Data    2019-01-18 19:59
		* @brief   RM3508�ṹ���ʼ��
		* @param   RM3508����ṹ���ַ
		* @retval  void
		*/
	void RM3508StructInit(RM3508Struct *RM3508,CAN_HandleTypeDef *hcanx)
	{
			RM3508->id = 0;
			RM3508->target = 0;
			RM3508->real_current = 0;
			RM3508->real_angle = 0;
			RM3508->real_speed = 0;
			RM3508->hcanx = hcanx;
	}
	/*---------------------------------80�ַ�����-----------------------------------*/
		/**
		* @Data    2019-01-19 00:42
		* @brief   3508���ݽ���
		* @param   void
		* @retval  void
		*/
		void RM3508ParseData(RM3508Struct *RM3508,uint8_t *data)
		{
			RM3508->real_angle=((int16_t)(data[0]<<8)|data[1]);
			RM3508->real_speed=((int16_t)(data[2]<<8)|data[3]);
			RM3508->real_current=((int16_t)(data[4]<<8)|data[5]);
		}
/* ================================== 3508 of end =================================== */
/*---------------------------------80�ַ�����-----------------------------------*/
	/**
	* @Data    2019-01-18 20:14
	* @brief   ����ת��  
	* @param   real ��ʵֵ
	* @param   threshold һȦ��������ķ�ֵ
	* @param   percentage //ת������������ǰ�Ƕ�:���ٺ�ĽǶ� = x:1
	* @retval  int16_t ������Ŀ��ֵ
	*/
int16_t RatiometricConversion(int16_t real,int16_t threshold,int16_t percentage)
{

		static int32_t last_real,tem=0;
		static uint16_t  coefficient=0;
		if (real - last_real < threshold)
		{
			/*�Ƕ�ϵ��ѭ������,����ת36Ȧ����ϵ��,���÷�Χ[0,Percentage] */
			coefficient =(coefficient+1)%(percentage);
		}
		else if(last_real - real < threshold)
		{
			coefficient = (percentage-1)-((((percentage-1) - coefficient)+1)%(percentage));
		}
		last_real = real;//��������ֵ
		tem = real + (s_max_motor_lines* coefficient); //ת���ܽǶ�
		return ((int16_t)(tem/(percentage)));//���������תһȦ
}
/*---------------------------------80�ַ�����-----------------------------------*/
	/**
	* @Data    2019-01-18 20:48
	* @brief   ��㴦��
	* @param   real ��ʵֵ
	* @param   threshold һȦ��������ķ�ֵ
	* @retval  int16_t ����֮���Ŀ��ֵ
	*/
	int16_t zeroArgument(int16_t real,int16_t threshold)
	{
		static int16_t last_realdata = 0,counter = 0;
		if(real - last_realdata < threshold) 
			counter = 1;
		if(last_realdata - real <threshold)
			counter = -1;
			else counter = 0;
		last_realdata = real;
		return (real + (s_max_motor_lines * counter));
	}


	/*------------------------------------file of end-------------------------------*/

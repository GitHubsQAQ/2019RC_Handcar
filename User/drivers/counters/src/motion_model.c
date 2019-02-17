/**
	|--------------------------------- Copyright --------------------------------|
	|                                                                            |
	|                      (C) Copyright 2019,����ƽͷ��,                         |
	|           1 Xuefu Rd, Huadu Qu, Guangzhou Shi, Guangdong Sheng, China      |
	|                           All Rights Reserved                              |
	|                                                                            |
	|           By(GCU The wold of team | ��������ѧ����ѧԺ������Ұ�Ƕ�)         |
	|                    https://github.com/GCUWildwolfteam                      |
	|----------------------------------------------------------------------------|
	|--FileName    : motion_model.c                                              
	|--Version     : v1.0                                                          
	|--Author      : ����ƽͷ��                                                     
	|--Date        : 2019-02-17             
	|--Libsupports : 
	|--Description :�����˶�ģ���㷨                                                     
	|--FunctionList                                                     
	|-------1. ....                                                     
	|          <version>:                                                     
	|     <modify staff>:                                                       
	|             <data>:                                                       
	|      <description>:                                                        
	|-------2. ...                                                       
	|-----------------------------declaration of end-----------------------------|
 **/
#include "motion_model.h" 
#include "Math.h"
/* ======================== ȫ���������˶�ģ�� of begin ======================= */
//	static float value[3] = {0};
#define VX_VALUE           (0.5f)
#define VY_VALUE           (sqrt(3)/2.f)      
#define L_value            (350*0.01f)  
	// /**
	// 	* @Data    2019-02-17 21:24
	// 	* @brief  ��ȡ���Ӱ뾶���ȣ���������ͻ���������Ƕ����
	// 	* @param   void
	// 	* @retval  void
	// 	*/
	// 	void GetRadiusAndTheta(uint8_t radius,char theta)
	// 	{
	// 		value[V_X] = (float)(-cos(60+theta));

	// 	}
	/**
		* @Data    2019-02-17 20:17
		* @brief  ȫ�������ֵ����˶�ģ��
		* @param   void
		* @retval  void
		*/
		void ThreeWheelMotionModel(int16_t motorspeed[],float vx,float vy,float w)
		{
			motorspeed[0] = (int16_t)(-VX_VALUE*vx + VY_VALUE*vy + L_value*w);
			motorspeed[1] = (int16_t)(-VX_VALUE*vx - VY_VALUE*vy + L_value*w);
			motorspeed[2] = (vx + L_value*w);
		}
/* ======================== ȫ���������˶�ģ�� of end ======================== */
/*-----------------------------------file of end------------------------------*/



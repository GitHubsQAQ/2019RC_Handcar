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
	|--FileName    : bsp_can.c                                                
	|--Version     : v1.0                                                            
	|--Author      : ����ƽͷ��                                                       
	|--Date        : 2019-01-18               
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
#include "bsp_can.h" 
/* ----------------- �ṹ���ַ�б� -------------------- */
canDataStrcut *pcan1_t = NULL;
canDataStrcut *pcan2_t = NULL;
/* -------------------------------- begin -------------------------------- */
/**
  * @brief  can���ó�ʼ��
  * @param  hcanx (x=1,2)
  * @retval HAL Status
 **/
/* -------------------------------- end -------------------------------- */
HAL_StatusTypeDef UserCanConfig(CAN_HandleTypeDef* hcanx)   
{
	canDataStrcut *addr;
	addr = GetCantAddr(hcanx);
	if(AllocateCanxSpace(hcanx) != HAL_OK)//�û�can�ṹ��ռ����
	{
		free(addr);
		return HAL_ERROR;
	}
	addr->can_queue = NULL;
	if(CanFilterInit(hcanx) != HAL_OK)
		return HAL_ERROR;
	if(CanTxInit(hcanx) != HAL_OK)
		return HAL_ERROR;
	if(CanRxInit(hcanx) != HAL_OK)
		return HAL_ERROR;
	if(CanQueueCreate(addr,5,13) != HAL_OK) //��������
	{
		//��Ӵ������
		free(addr);
		return HAL_ERROR;
	}
	 HAL_CAN_Start(hcanx);
	 HAL_CAN_ActivateNotification(hcanx, CAN_IT_RX_FIFO0_MSG_PENDING); //�����ж�
	 return HAL_OK;
}

/* -------------------------------- begin -------------------------------- */
/**
  * @brief  can��������
  * @param CAN_HandleTypeDef *hcanx(x=1,2)
  * @retval HAL Status
 **/
/* -------------------------------- end -------------------------------- */
HAL_StatusTypeDef CanFilterInit(CAN_HandleTypeDef* hcanx)
{
	canDataStrcut *addr;
	addr = GetCantAddr(hcanx);
	addr->filter.FilterIdHigh = 0x0000;									 //Ҫ���˵�ID��λ
	addr->filter.FilterIdLow = 0x0000;										 //Ҫ���˵�ID��λ
	addr->filter.FilterMaskIdHigh = 0x0000;							 //��������16λÿλ����ƥ��
	addr->filter.FilterMaskIdLow = 0x0000;								 //��������16λÿλ����ƥ��
	addr->filter.FilterFIFOAssignment = CAN_FILTER_FIFO0; //��������������FIFO 0
	addr->filter.FilterBank = 0;
	addr->filter.FilterScale = CAN_FILTERSCALE_32BIT;
	addr->filter.FilterMode = CAN_FILTERMODE_IDMASK;
	addr->filter.FilterActivation = ENABLE; //ʹ�ܹ�����
	addr->filter.SlaveStartFilterBank = 14;
	return (HAL_CAN_ConfigFilter(hcanx, &addr->filter)); //ʹ��ɸѡ��
}


/* -------------------------------- begin -------------------------------- */
/**
  * @brief  can ���ͽṹ���ʼ��
  * @param  CanTxMsgTypeDef* TxMsg
  * @retval HAL Status
 **/
/* -------------------------------- end -------------------------------- */
HAL_StatusTypeDef CanTxInit(CAN_HandleTypeDef* hcanx)
{
	canDataStrcut *addr;
	addr = GetCantAddr(hcanx);//��ȡ��Ӧ�û�can�ṹ���ַ
	if(addr == NULL)
	{
		return HAL_ERROR;
	}
	addr->txMsg.StdId = 0x000; //����id
	addr->txMsg.IDE = CAN_ID_STD; //ѡ���׼id
	addr->txMsg.RTR = CAN_RTR_DATA; //0Ϊ����֡��1ΪԶ��֡
	addr->txMsg.DLC = 8; //�������ݳ���Ϊ8���ֽ�
	addr->txdata[0] = 0x00; //��������λ������
	addr->txdata[1] = 0x00;
	addr->txdata[2] = 0x00;
	addr->txdata[3] = 0x00;
	addr->txdata[4] = 0x00;
	addr->txdata[5] = 0x00;
	addr->txdata[6] = 0x00;
	addr->txdata[7] = 0x00;
	return HAL_OK;
}


/* -------------------------------- begin -------------------------------- */
/**
  * @brief  can ���ܽṹ���ʼ��
  * @param  CanRxMsgTypeDef* RxMsg
  * @retval void
 **/
/* -------------------------------- end -------------------------------- */
HAL_StatusTypeDef CanRxInit(CAN_HandleTypeDef* hcanx)
{
		canDataStrcut *addr;
	  addr = GetCantAddr(hcanx); //��ȡ��Ӧ�û�can�ṹ���ַ
		if(addr == NULL)
		{
			return HAL_ERROR;
		}
    addr->rxMsg.StdId=0x00;
    addr->rxMsg.ExtId=0x00;
    addr->rxMsg.DLC=0x00;
    addr->rxdata[0] = 0x00; //��������λ������
    addr->rxdata[1] = 0x00;
    addr->rxdata[2] = 0x00;
    addr->rxdata[3] = 0x00;
    addr->rxdata[4] = 0x00;
    addr->rxdata[5] = 0x00;
    addr->rxdata[6] = 0x00;
    addr->rxdata[7] = 0x00;
		return HAL_OK;
}
/*---------------------------------80�ַ�����-----------------------------------*/
	/**
	* @Data    2019-01-16 10:54
	* @brief   ������Ӧcan�������ݵĿռ�
	* @param   hcanx ��x=1,2��
	* @retval  HAL Status
	*/
	HAL_StatusTypeDef AllocateCanxSpace(CAN_HandleTypeDef *hcanx)
	{
		
			if (hcanx->Instance == CAN1) 
			{
				pcan1_t	= (struct canDataStrcut*)malloc(sizeof(struct canDataStrcut));
				if(pcan1_t == NULL)
				return HAL_ERROR;
				return HAL_OK;
			} 
			else if (hcanx->Instance == CAN2) 
			{
				pcan2_t	= (struct canDataStrcut*)malloc(sizeof(struct canDataStrcut));
				if(pcan2_t== NULL)
				return HAL_ERROR;
				return HAL_OK;
			}
			else	return HAL_ERROR;
	}
/*---------------------------------80�ַ�����-----------------------------------*/
	/**
	* @Data    2019-01-16 11:08
	* @brief   �Զ��б�can���ͻ�ȡ��Ӧ�û�can�ṹ���ַ
	* @param   hcanx ��x=1,2��
	* @retval  canDataStrcut* �û����ڽṹ��ָ��
	*/
	canDataStrcut* GetCantAddr(CAN_HandleTypeDef *hcanx)
	{
		if(hcanx->Instance == CAN1)
		{
			return pcan1_t;
		} 
		else if(hcanx->Instance == CAN2)  
		{
			return pcan2_t;
		} 
		else	return NULL;
	}
/*---------------------------------80�ַ�����-----------------------------------*/
	/**
	* @Data    2019-01-19 00:58
	* @brief   can���ܻص�����
	* @param   void
	* @retval  void
	*/
	void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan)
	{
		uint8_t tem_data[13]={0};
		uint8_t *p;
		canDataStrcut *addr;
	  addr = GetCantAddr(hcan); //��ȡ��Ӧ�û�can�ṹ���ַ
		HAL_CAN_GetRxMessage(hcan,CAN_RX_FIFO0,&addr->rxMsg,addr->rxdata);
		p = (uint8_t*)&addr->rxMsg.StdId;
		tem_data[0] = p[3];
		tem_data[1] = p[2];
		tem_data[2] = p[1];
		tem_data[3] = p[0];
		memcpy(&tem_data[4],&addr->rxdata,8);
    tem_data[12] = 0x55;
		xQueueSendToBackFromISR(addr->can_queue,tem_data, 0);
	}
/*---------------------------------80�ַ�����-----------------------------------*/
	/**
	* @Data    2019-01-19 00:58
	* @brief   can�����ж϶��д���
	* @param   void
	* @retval  void
	*/
	HAL_StatusTypeDef CanQueueCreate(canDataStrcut *canx,uint8_t len,uint8_t deep)
	{
		canx->can_queue = xQueueCreate(len,deep);//�������len����deep����
		if(canx->can_queue == NULL)
			return HAL_ERROR;
		return HAL_OK;
	}
/*---------------------------------80�ַ�����-----------------------------------*/
	/**
	* @Data    2019-01-16 15:22
	* @brief   ���н���
	* @param   hcanx��1,2,3,6��
	* @param 	 pvBuffer �������ݵ�ַ
	* @retval  HAL Status
	*/
	HAL_StatusTypeDef UserCanQueueRX(CAN_HandleTypeDef *hcanx,void* const pvBuffer)
	{
//				portBASE_TYPE xStatus;
		canDataStrcut *addr;
		addr = GetCantAddr(hcanx);
//				xStatus = 
		xQueueReceive(addr->can_queue, pvBuffer, 1);
//				if(pdPASS != xStatus)
//				{
//					return HAL_ERROR;
//				}
		return HAL_OK;
	}
	/*---------------------------------80�ַ�����-----------------------------------*/
		/**
		* @Data    2019-01-22 22:59
		* @brief   can���ͺ���
		* @param   uint32_t id  can����id
		* @param   int16_t mess1  ��Ϣ1
		* @param   int16_t mess2  ��Ϣ2
		* @param   int16_t mess3	��Ϣ3
		* @param   int16_t mess4	��Ϣ4
		* @retval  HAL Status
		*/
HAL_StatusTypeDef UserCanTx(CAN_HandleTypeDef *hcanx,\
														uint32_t id,\
														int16_t mess1,\
														int16_t mess2,\
														int16_t mess3,\
														int16_t mess4)
{
		canDataStrcut *addr;
		addr = GetCantAddr(hcanx);
		addr->txMsg.IDE = CAN_ID_STD;    //��׼֡
		addr->txMsg.RTR = CAN_RTR_DATA;  //����֡
		addr->txMsg.DLC = 0x08;          //֡����Ϊ8
		addr->txMsg.StdId = id;
		addr->txdata[0] = (uint8_t)((mess1>>8)&0xff);
		addr->txdata[1] = (uint8_t)(mess1&0xff);
		addr->txdata[2] = (uint8_t)((mess2>>8)&0xff);
		addr->txdata[3] = (uint8_t)(mess2&0xff);
		addr->txdata[4] = (uint8_t)((mess3>>8)&0xff);
		addr->txdata[5] = (uint8_t)(mess3&0xff);
		addr->txdata[6] = (uint8_t)((mess4>>8)&0xff);
		addr->txdata[7] = (uint8_t)(mess4&0xff);
		return(HAL_CAN_AddTxMessage(hcanx,&addr->txMsg,addr->txdata,(uint32_t*)CAN_TX_MAILBOX0));
}
/*------------------------------------file of end-------------------------------*/



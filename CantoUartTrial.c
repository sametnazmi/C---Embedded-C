/**
  ******************************************************************************
  * File Name          : main.c
  * Description        : Main program body
  ******************************************************************************
  ** This notice applies to any and all portions of this file
  * that are not between comment pairs USER CODE BEGIN and
  * USER CODE END. Other portions of this file, whether 
  * inserted by the user or by software development tools
  * are owned by their respective copyright owners.
  *
  * COPYRIGHT(c) 2017 STMicroelectronics
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32f0xx_hal.h"
#include "string.h"

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private variables ---------------------------------------------------------*/
CAN_HandleTypeDef hcan1;

UART_HandleTypeDef huart1;
UART_HandleTypeDef huart2;

/* USER CODE BEGIN PV */
/* Private variables ---------------------------------------------------------*/

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_CAN_Init(void);
static void MX_USART1_UART_Init(void);
static void MX_USART2_UART_Init(void);
char Rx_indx, Rx_data[2], Rx_Buffer[100], Transfer_cplt;
char Rx_indx1, Rx_data1[2], Rx_Buffer1[100], Transfer_cplt1;
char buffer[256];
unsigned char samet;


CanTxMsgTypeDef myTxMessage;
CanRxMsgTypeDef myRxMessage;
CAN_FilterConfTypeDef myFilter;

uint8_t led,led1;

void HAL_CAN_RxCpltCallback(CAN_HandleTypeDef* hcan) {
    uint32_t j,k;
	if(myRxMessage.StdId<1000)
		
	{
		sprintf(buffer,"StdId:%d DLC:%d %x %x %x %x %x %x %x %x\n",myRxMessage.StdId,myRxMessage.DLC,
	 myRxMessage.Data[0]
  ,myRxMessage.Data[1]
	,myRxMessage.Data[2]
	,myRxMessage.Data[3]
	,myRxMessage.Data[4]
	,myRxMessage.Data[5]
	,myRxMessage.Data[6]
	,myRxMessage.Data[7]
	); 
      HAL_UART_Transmit(&huart1,(uint8_t *) buffer,strlen(buffer),100);
       
}

	 __HAL_CAN_ENABLE_IT(&hcan1, CAN_IT_FMP0);
    
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) 
{
               uint8_t i;
               if ((huart->Instance == USART1)&&(Transfer_cplt==0))
                              {
                              if (Rx_indx==0) {for (i=0;i<100;i++) Rx_Buffer[i]=0;}
                             
                              if (Rx_data[0]!=13)
                                            {
                                            Rx_Buffer[Rx_indx++]=Rx_data[0];
                                            }
                                else                                  
                                            {
                                            Rx_indx=0;
                                            Transfer_cplt=1;
                                            }
 
                              HAL_UART_Receive_IT(&huart1,(uint8_t *)Rx_data, 1);
                              }
															
															
							if ((huart->Instance == USART2)&&(Transfer_cplt1==0))
                              {
                              if (Rx_indx1==0) {for (i=0;i<100;i++) Rx_Buffer1[i]=0;}
                             
                              if (Rx_data1[0]!=13)
                                            {
                                            Rx_Buffer1[Rx_indx1++]=Rx_data1[0];
                                            }
                                else                                  
                                            {
                                            Rx_indx1=0;
                                            Transfer_cplt1=1;
                                            }
 
                              HAL_UART_Receive_IT(&huart2,(uint8_t *)Rx_data1, 1);
                              }
 
}

/* USER CODE BEGIN PFP */
/* Private function prototypes -----------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/


/* USER CODE END PFP */

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

int main(void)
{
  HAL_Init();
  SystemClock_Config();

  MX_GPIO_Init();

  MX_CAN_Init();
  MX_USART1_UART_Init();
  MX_USART2_UART_Init();
	hcan1.pRxMsg = &myRxMessage;
  hcan1.pTxMsg = &myTxMessage;
  myFilter.FilterNumber           = 0;
  myFilter.FilterMode             = CAN_FILTERMODE_IDMASK;
  myFilter.FilterScale            = CAN_FILTERSCALE_32BIT;
  myFilter.FilterIdHigh           = 0x0000;
  myFilter.FilterIdLow            = 0x0001;
  myFilter.FilterMaskIdHigh       = 0x0000;
  myFilter.FilterMaskIdLow        = 0x0000;
  myFilter.FilterFIFOAssignment   = 0;
  myFilter.FilterActivation       = ENABLE;
	
 if(HAL_CAN_ConfigFilter(&hcan1,&myFilter)!=HAL_OK)
 {
  HAL_GPIO_WritePin(GPIOA,GPIO_PIN_1,1);
 }	 

	 led=0;
	 led1=0;
  HAL_UART_Receive_IT(&huart1,(uint8_t *)Rx_data, 1);
	HAL_UART_Receive_IT(&huart2,(uint8_t *)Rx_data1, 1);
	if (HAL_CAN_Receive_IT(&hcan1, CAN_FIFO0)!=HAL_OK)
 {
  HAL_GPIO_WritePin(GPIOA,GPIO_PIN_0,1);
 }
__HAL_CAN_ENABLE_IT(&hcan1, CAN_IT_FMP0);
	
  samet=0;	
  while (1)
  {
	samet++;
	
                                myTxMessage.StdId = 0x1C;
																myTxMessage.ExtId = 0x01;
		                            myTxMessage.IDE = CAN_ID_STD;
																myTxMessage.RTR = CAN_RTR_DATA;

                                myTxMessage.DLC = 8;
                                
		                            myTxMessage.Data[0]=samet;
																myTxMessage.Data[1]=samet+1;
																myTxMessage.Data[2]=samet+2;
																myTxMessage.Data[3]=samet+3;
																myTxMessage.Data[4]=samet+4;
																myTxMessage.Data[5]=samet+5;
																myTxMessage.Data[6]=samet+6;
																myTxMessage.Data[7]=samet+7;
                                // the tesmesssag is now sent here
                                HAL_CAN_Transmit(&hcan1,50);	

	 HAL_Delay(80);
  /* USER CODE END WHILE */
 if (Transfer_cplt==1)
    {
      sprintf(buffer,"%s diko\r\n",Rx_Buffer); 
      HAL_UART_Transmit(&huart1,(uint8_t *) buffer,strlen(buffer),1000);
      Transfer_cplt=0;       
      led=!led;  
 //  HAL_GPIO_WritePin(GPIOA,GPIO_PIN_0,led);
		
    }             
if (Transfer_cplt1==1)
    {
      sprintf(buffer,"%s diko\r\n",Rx_Buffer1); 
      HAL_UART_Transmit(&huart2,(uint8_t *) buffer,strlen(buffer),1000);
      Transfer_cplt1=0;       
      led1=!led1;  
 
		HAL_GPIO_WritePin(GPIOA,GPIO_PIN_1,led1);			
    }                                      		
 

  }
  /* USER CODE BEGIN 3 */

  }
  /* USER CODE END 3 */



/** System Clock Configuration
*/
void SystemClock_Config(void)
{

  RCC_OscInitTypeDef RCC_OscInitStruct;
  RCC_ClkInitTypeDef RCC_ClkInitStruct;
  RCC_PeriphCLKInitTypeDef PeriphClkInit;

    /**Initializes the CPU, AHB and APB busses clocks 
    */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI48;
  RCC_OscInitStruct.HSI48State = RCC_HSI48_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Initializes the CPU, AHB and APB busses clocks 
    */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI48;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USART1;
  PeriphClkInit.Usart1ClockSelection = RCC_USART1CLKSOURCE_PCLK1;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Configure the Systick interrupt time 
    */
  HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000);

    /**Configure the Systick 
    */
  HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

  /* SysTick_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);
}

/* CAN init function */
static void MX_CAN_Init(void)
{

  hcan1.Instance = CAN;
  hcan1.Init.Prescaler = 16;
  hcan1.Init.Mode = CAN_MODE_NORMAL;
  hcan1.Init.SJW = CAN_SJW_1TQ;
  hcan1.Init.BS1 = CAN_BS1_8TQ;
  hcan1.Init.BS2 = CAN_BS2_3TQ;
  hcan1.Init.TTCM = DISABLE;
  hcan1.Init.ABOM = ENABLE;
  hcan1.Init.AWUM = DISABLE;
  hcan1.Init.NART = DISABLE;
  hcan1.Init.RFLM = DISABLE;
  hcan1.Init.TXFP = DISABLE;
  if (HAL_CAN_Init(&hcan1) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

}

/* USART1 init function */
static void MX_USART1_UART_Init(void)
{

  huart1.Instance = USART1;
  huart1.Init.BaudRate = 115200;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  huart1.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart1.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

}

/* USART2 init function */
static void MX_USART2_UART_Init(void)
{

  huart2.Instance = USART2;
  huart2.Init.BaudRate = 115200;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  huart2.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart2.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

}

/** Configure pins as 
        * Analog 
        * Input 
        * Output
        * EVENT_OUT
        * EXTI
*/
static void MX_GPIO_Init(void)
{

  GPIO_InitTypeDef GPIO_InitStruct;

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0|GPIO_PIN_1, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7, GPIO_PIN_RESET);

  /*Configure GPIO pins : PA0 PA1 */
  GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : PB5 PB6 PB7 */
  GPIO_InitStruct.Pin = GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @param  None
  * @retval None
  */
void _Error_Handler(char * file, int line)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  while(1) 
  {
  }
  /* USER CODE END Error_Handler_Debug */ 
}

#ifdef USE_FULL_ASSERT

/**
   * @brief Reports the name of the source file and the source line number
   * where the assert_param error has occurred.
   * @param file: pointer to the source file name
   * @param line: assert_param error line source number
   * @retval None
   */
void assert_failed(uint8_t* file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
    ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */

}

#endif

/**
  * @}
  */ 

/**
  * @}
*/ 

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

/* USER CODE BEGIN Header */
/**
*******************************************************************************
* @brief   		Main class
* @file    		main.c
* @author  		Anton Åbonde
* @version 		1.0
* @date    		2019-04-05
* @brief 		This class initializes all peripherals that are used in the
* 				program. In the infinite loop the unit listens for new data
* 				from the WiFi-module and if it is updated the new data will
* 				be printed.
*******************************************************************************
*/
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "spi.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

#include "clockinit.h"
#include "display_functions.h"
#include "distance_sensor_functions.h"
#include "wifi_functions.h"

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */
  // Initialize use of printf
  initialise_monitor_handles();
  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_TIM1_Init();
  MX_SPI1_Init();
  MX_USART1_UART_Init();
  /* USER CODE BEGIN 2 */
  HAL_SPI_MspInit(&hspi1);
  HAL_UART_MspInit(&huart1);
  LCD_Init();
//  Backlight_On();

  // Test of the LCD display, writes an A on the bottom of the display
//  printf("Test: LCD display\n");
//  LCD_Write(0,0x80+0x22);//0x80 + 0x"antal tecken" == position på skärmen
//  LCD_Write(1,'A');
//  HAL_Delay(500);
//  LCD_Write(0,1); //Clear display
//  printf("Test: LCD display is done\n");

  // Test the WiFi-module, set up internet connection
//  List_Nearby_WiFis();
//  WiFi_Init();
//  Get_Message();
//  Disconnect_From_WiFi();

  float distance;
  int 	backlight_counter = 0,
		update_counter = 1000;

  // Test the distance sensor and writes the result to the terminal.
  while(1){
	  distance = Measure_Distance();
	  if(distance < 300){
		  if(update_counter > 50){
			  Get_Message();
			  update_counter = 0;
		  }
		  Backlight_On();
	  }
	  else if(backlight_counter > 30){
		  Backlight_Off();
		  backlight_counter = 0;
	  }
//	  gcvt(distance,7,distance_as_chars);
//	  LCD_Write(0,0x80+0x20);
//	  for(int i = 0; i < sizeof(distance_as_chars); i++)
//		  LCD_Write(1,distance_as_chars[i]);
	  backlight_counter++;
	  update_counter++;
//	  HAL_Delay(500);
  }

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

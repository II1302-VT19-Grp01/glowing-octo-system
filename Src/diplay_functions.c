/**
*******************************************************************************
* @brief   		Display functions
* @file    		display_functions.c
* @author  		"Anton Åbonde"
* @version 		1.0
* @date    		2019-05-02
* @brief		This class handles all functions that are involved with the LCD display.
*******************************************************************************
*/

#include "spi.h"

/**
 * @brief LCD_Write Writes one byte of data to the display.
 * @param RS: 0 for instructions, 1 for data input
 * @param DATA: The instruction/data that will be transmitted to the display.
 * @retval void
 */
void LCD_Write(uint8_t RS, uint32_t DATA){

	uint8_t Start_Byte = 0x1F | (RS<<6);
	uint8_t Lower_Byte = DATA & 0x0F;
	uint8_t Upper_Byte = (DATA & 0xF0)>>4;
	uint8_t buffer[3] = {Start_Byte,Lower_Byte,Upper_Byte};

	HAL_SPI_Transmit_IT(&hspi1,buffer,3);
}

/**
 * @brief LCD_Init Initializes the LCD display
 * @param void
 * @retval void
 */
void LCD_Init(){

	LCD_Write(0,0x3A);		// Function Set
	LCD_Write(0,0x09);		// Extended Function Set
	LCD_Write(0,0x01);		// Clear Display
	LCD_Write(0,0x06);		// Entry Mode Set
	LCD_Write(0,0x1E);		// Bias Setting
	LCD_Write(0,0x39);		// Function Set 2
	LCD_Write(0,0x1B);		// Internal OSC
	LCD_Write(0,0x6E);		// Follower Control
	LCD_Write(0,0x57);		// Power Control
	LCD_Write(0,0x3A);		// Function Set
	LCD_Write(0,0x72);		// Contrast Set
	LCD_Write(1,0x00);		// Set characters to ROM A
	LCD_Write(0,0x38);		// Function Set 3
	LCD_Write(0,0x0C);		// Display ON

}

/**
 * @brief Backlight_On Activates the backlight
 * @param void
 * @retval void
 */
void Backlight_On(){

	HAL_GPIO_WritePin(GPIOA, BKLGT1_Pin|BKLGT2_Pin|BKLGT3_Pin, GPIO_PIN_SET);

}

/**
 * @brief Backlight_Off Deactivates the backlight
 * @param void
 * @retval void
 */
void Backlight_Off(){

	HAL_GPIO_WritePin(GPIOA, BKLGT1_Pin|BKLGT2_Pin|BKLGT3_Pin, GPIO_PIN_RESET);

}

/**
 * @brief HAL_SPI_TxCpltCallback callback function for transfer complete
 * @param *hspi pointer to the handle that contains configuration information for the SPI module
 * @retval void
 */
void HAL_SPI_TxCpltCallback(SPI_HandleTypeDef *hspi){

}

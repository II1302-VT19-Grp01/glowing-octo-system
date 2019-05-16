/**
*******************************************************************************
* @brief   		WiFi functions
* @file    		wifi_functions.c
* @author  		"Anton Åbonde"
* @version 		1.1
* @date    		2019-05-02
* @brief		This class handles all functions that are involved with the WiFi module.
*******************************************************************************
*/

#include "usart.h"

extern UART_HandleTypeDef huart1;

#define BUFFERSIZE 2000

void Connect_To_WiFi(){

	int buffer[BUFFERSIZE] = {};

	uint8_t setMode[] = "AT+CWMODE=1\r\n";
	uint8_t joinNetwork[] = "AT+CWJAP=\"iPhone\",\"e346a51srwj5i\"\r\n";		// "AT+CWJAP=\"SSID\",\"PASSWORD\"\r\n"
	uint8_t showIP[] = "AT+CIFSR\r\n";

	while(HAL_UART_GetState(&huart1) != HAL_UART_STATE_READY);
	HAL_UART_Transmit(&huart1,setMode,sizeof(setMode),200);
	HAL_UART_Transmit(&huart1,joinNetwork,sizeof(joinNetwork),200);
	HAL_UART_Transmit(&huart1,showIP,sizeof(showIP),200);
	HAL_UART_Receive(&huart1,buffer,BUFFERSIZE,400);
	while(HAL_UART_GetState(&huart1) != HAL_UART_STATE_READY);

}

void Disconnect_From_WiFi(){

	uint8_t disconnect[] = "AT+CWQAP\r\n";
	uint8_t buffer[BUFFERSIZE] = {};

	HAL_UART_Transmit(&huart1,disconnect,sizeof(disconnect),200);
	HAL_UART_Receive(&huart1,buffer,BUFFERSIZE,400);

}

void List_Nearby_WiFis(){

	uint8_t a[] = "AT+CWLAP\r\n";
	uint8_t buffer[BUFFERSIZE] = {};

	HAL_UART_Transmit(&huart1,a,sizeof(a),200);
	HAL_UART_Receive(&huart1,buffer,BUFFERSIZE,400);

}

void Get_Message(){

	char buffer[BUFFERSIZE] = {};
	char message[80] = {};
	char transmit[] = "AT+CIPSTART=\"TCP\",\"169.50.73.249\",80\r\n";
	char ammount[] = "AT+CIPSEND=70\r\n";
	char send[] = "GET /status HTTP/1.1\r\nHOST:availability-device.eu-gb.mybluemix.net\r\n\r\n";
	char close[] = "AT+CIPCLOSE\r\n";

	while(HAL_UART_GetState(&huart1) != HAL_UART_STATE_READY);
	HAL_UART_Transmit(&huart1,transmit,sizeof(transmit),200);
	HAL_UART_Receive(&huart1,buffer,BUFFERSIZE,400);
	HAL_UART_Transmit(&huart1,ammount,sizeof(ammount),200);
	HAL_UART_Receive(&huart1,buffer,BUFFERSIZE,400);
	HAL_UART_Transmit(&huart1,send,sizeof(send),200);
	HAL_UART_Receive(&huart1,buffer,BUFFERSIZE,400);

	uint32_t i = 3;
	uint8_t j = 0;

	while(!(buffer[i-3] == '-' && buffer[i-2] == '4' && buffer[i-1] == '"' && buffer[i] == '>') && i < 2000) i++; //HARDFAULT ERROR HERE OBS
	if(i < 2000){
		while(!(buffer[++i] == '<' && buffer[i+1] == '/' && buffer[i+2] == 'h' && buffer[i+3] == '1' && buffer[i+4] == '>') && j < 80){
			switch(buffer[i]){
				case 195: 				// if å, ä or ö
					continue;
				case 133:				// Å
					message[i] = 0xAE;
					break;
				case 165:				// å
					message[i] = 0xAF;
					break;
				case 132:				// Ä
					message[i] = 0x5B;
					break;
				case 164:				// ä
					message[i] = 0x7B;
					break;
				case 150:				// Ö
					message[i] = 0x5C;
					break;
				case 182:				// ö
					message[i] = 0x7C;
					break;
				default:
					message[j++] = buffer[i];
					break;
			}

		}
		printf("%s\n",message);
		LCD_Write(0,0x80);
		for(int i = 0; i < sizeof(message); i++){
			if(message[i] == 0)
				break;

			LCD_Write(1,message[i]);
		}
	}

	HAL_UART_Transmit(&huart1,close,sizeof(close),400);
	HAL_UART_Receive(&huart1,buffer,BUFFERSIZE,400);
	while(HAL_UART_GetState(&huart1) != HAL_UART_STATE_READY);

}

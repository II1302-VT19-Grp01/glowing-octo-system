/**
*******************************************************************************
@brief   	Header file for clock initialization
@file    	clockinit.h
@author  	Anton Åbonde
@version 	1.0
@date    	2019-04-05
@brief		Declaration of the clock initialization functions.
*******************************************************************************
*/

void SystemClock_Config(void);
void Error_Handler(void);
void assert_failed(char *file, uint32_t line);

/**
*******************************************************************************
* @brief   		Distance sensor functions
* @file    		distance_sensor_functions.c
* @author  		"Anton Åbonde"
* @version 		1.0
* @date    		2019-05-02
* @brief		This class handles all functions that are involved with the distance sensor.
*******************************************************************************
*/

#include "main.h"

void Delay(uint8_t delay){
	uint32_t i = 0, j = 0;
	for(i = 0; i < delay; i++)
		for(j = 0; j < delay; j++);
}

float Measure_Distance(){

	uint32_t time;
	float distance;

	DIST_TRIGG_GPIO_Port->BRR = DIST_TRIGG_Pin;
	HAL_Delay(1);
	DIST_TRIGG_GPIO_Port->BSRR = DIST_TRIGG_Pin;
	HAL_Delay(1);
	DIST_TRIGG_GPIO_Port->BRR = DIST_TRIGG_Pin;

	while((DIST_ECHO_GPIO_Port->IDR & DIST_ECHO_Pin) == 0x00);
	time = 0;
	while((DIST_ECHO_GPIO_Port->IDR & DIST_ECHO_Pin) != 0x00){
		time++;
	}

	distance = (float) time * 2 * 0.0171821;
	printf("Measured distance: %.2f\n",distance);
	HAL_Delay(2);
	return distance;
}

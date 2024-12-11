/*
 * 7seg_display.c
 *
 *  Created on: Dec 10, 2024
 *      Author: Admin
 */
#include "7seg_display.h"
#include "global.h"
int led_NB;
int led_DT;
int led_Tg;
int indx=0;
int counter6=0;
int led_buffer[4]={0,0,0,0};
void display7SEG_NB(int num) {
  uint8_t segmentPattern[] = {
    0b00111111,
    0b00000110,
    0b01011011,
    0b01001111,
    0b01100110,
    0b01101101,
    0b01111101,
    0b00000111,
    0b01111111,
    0b01101111 };
  if (num < 0 || num > 9) {
    num = 0;
  }
  uint8_t pattern = segmentPattern[num];
  	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, (pattern & 0x01) ? GPIO_PIN_RESET : GPIO_PIN_SET); //A
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, (pattern & 0x02) ? GPIO_PIN_RESET : GPIO_PIN_SET); //B
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_2, (pattern & 0x04) ? GPIO_PIN_RESET : GPIO_PIN_SET); //C
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3, (pattern & 0x08) ? GPIO_PIN_RESET : GPIO_PIN_SET); //D
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, (pattern & 0x10) ? GPIO_PIN_RESET : GPIO_PIN_SET); //E
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, (pattern & 0x20) ? GPIO_PIN_RESET : GPIO_PIN_SET); //F
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, (pattern & 0x40) ? GPIO_PIN_RESET : GPIO_PIN_SET); //G
  }
void update_7seg(int indx){
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_9, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_10, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_11, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_12, GPIO_PIN_SET);
	switch(indx)
	{
	case 1:
		 display7SEG_NB(led_buffer[0]);
		 HAL_GPIO_WritePin(GPIOA, GPIO_PIN_9, GPIO_PIN_RESET);
		 HAL_GPIO_WritePin(GPIOA, GPIO_PIN_10, GPIO_PIN_SET);
		 HAL_GPIO_WritePin(GPIOA, GPIO_PIN_11, GPIO_PIN_SET);
		 HAL_GPIO_WritePin(GPIOA, GPIO_PIN_12, GPIO_PIN_SET);
		 break;
	case 2:
		display7SEG_NB(led_buffer[1]);
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_9, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_10, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_11, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_12, GPIO_PIN_SET);
		break;
	case 3:
		display7SEG_NB(led_buffer[2]);
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_9, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_10, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_11, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_12, GPIO_PIN_SET);
		break;
	case 4:
		display7SEG_NB(led_buffer[3]);
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_9, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_10, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_11, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_12, GPIO_PIN_RESET);
		break;
	default:
		break;
	}
}
void quet_7SEG(){
	if(counter6==0){
		update_7seg(indx);
		indx=(indx+1)%5;
		counter6=2;
	}
}
void updateLedBuffer(int mode) {
	if(mode>=cd1 && mode<=cd4){
		led_buffer[0] = led_NB/10;
		led_buffer[1] = led_NB % 10;
		led_buffer[2] = led_DT/10;
		led_buffer[3] = led_DT%10;
	}else if(mode>=mode1 && mode<=mode4){
		led_buffer[0] = a/10;
		led_buffer[1] = a%10;
		led_buffer[2] = c/10;
		led_buffer[3] = c%10;
	}else if(mode == MODE_2){
		led_buffer[0] = t_red/10;
		led_buffer[1] = t_red%10;
		led_buffer[2] = 0;
		led_buffer[3] = MODE_2;
	}else if(mode == MODE_3){
		led_buffer[0] = t_yellow/10;
		led_buffer[1] = t_yellow%10;
		led_buffer[2] = 0;
		led_buffer[3] = MODE_3;
	}else if(mode == MODE_4){
		led_buffer[0] = t_green/10;
		led_buffer[1] = t_green%10;
		led_buffer[2] = 0;
		led_buffer[3] = MODE_4;
	}
}


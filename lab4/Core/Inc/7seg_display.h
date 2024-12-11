/*
 * 7seg_display.h
 *
 *  Created on: Dec 10, 2024
 *      Author: Admin
 */

#ifndef INC_7SEG_DISPLAY_H_
#define INC_7SEG_DISPLAY_H_
#include "main.h"
extern int led_NB;
extern int led_DT;
extern int led_buffer[4];

void display7SEG_NB(int num);
void update_7seg(int indx);
void updateLedBuffer(int mode);
void quet_7SEG();


#endif /* INC_7SEG_DISPLAY_H_ */

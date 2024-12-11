/*
 * global.h
 *
 *  Created on: Dec 10, 2024
 *      Author: Admin
 */

#ifndef INC_GLOBAL_H_
#define INC_GLOBAL_H_
#include "Button.h"
#include "main.h"
#include "trafficlight.h"
#include "7seg_display.h"
#define cd1				5
#define cd2				6
#define cd3				7
#define cd4				8
#define INIT			1
#define MODE_2			2
#define MODE_3			3
#define MODE_4			4

#define mode1			9
#define mode2			10
#define mode3			11
#define mode4			12
extern int status;
extern int t_red;
extern int t_yellow;
extern int t_green;
extern int a;
extern int b;
extern int c;
extern int counter0;
extern int counter1;
extern int counter2;
extern int counter4;
extern int counter5;
extern int counter6;

#endif /* INC_GLOBAL_H_ */

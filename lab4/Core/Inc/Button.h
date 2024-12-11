/*
 * Button.h
 *
 *  Created on: Dec 10, 2024
 *      Author: Admin
 */

#ifndef INC_BUTTON_H_
#define INC_BUTTON_H_
#include "main.h"

#define NORMAL_STATE SET
#define PRESSED_STATE RESET

#define NUM_BUTTONS 3
int isButton1Pressed(int index);
void getKeyInput();



#endif /* INC_BUTTON_H_ */

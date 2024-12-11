/*
 * Button.c
 *
 *  Created on: Dec 10, 2024
 *      Author: Admin
 */
#include "Button.h"
int KeyReg0[NUM_BUTTONS];
int KeyReg1[NUM_BUTTONS];
int KeyReg2[NUM_BUTTONS];
int KeyReg3[NUM_BUTTONS];

int TimeOutForKeyPress[NUM_BUTTONS]=  {500,500,500};
int button1_pressed[NUM_BUTTONS] = {0,0,0};
int button1_long_pressed[NUM_BUTTONS] = {0,0,0};

int isButton1Pressed(int index){
	if(button1_pressed[index] == 1){
		button1_pressed[index] = 0;
		return 1;
	}
	return 0;
}

int isButton1LongPressed(int index){
	if(button1_long_pressed[index] == 1){
		button1_long_pressed[index] = 0;
		return 1;
	}
	return 0;
}

void subKeyProcess(int index){
	//TODO
	button1_pressed[index] = 1;
}

void getKeyInput(){
for(int i=0; i<NUM_BUTTONS;i++){
  KeyReg0[i] = KeyReg1[i];
  KeyReg1[i] = KeyReg2[i];
  // Add your key
  if(i==0)
  {
	  KeyReg2[0] = HAL_GPIO_ReadPin(BUTTON_GPIO_Port, BUTTON_Pin);
  }
  else if(i==1){
	  KeyReg2[1] = HAL_GPIO_ReadPin(BUTTON1_GPIO_Port, BUTTON1_Pin);
  }
  else if(i==2){
	  KeyReg2[2] = HAL_GPIO_ReadPin(BUTTON2_GPIO_Port, BUTTON2_Pin);
  }

  if ((KeyReg0[i] == KeyReg1[i]) && (KeyReg1[i] == KeyReg2[i])) {
              if (KeyReg3[i] != KeyReg2[i]) {
                  KeyReg3[i] = KeyReg2[i];
                  if (KeyReg2[i] == PRESSED_STATE) {
                      TimeOutForKeyPress[i] = 500;  // Reset timeout khi nút nhấn
                      subKeyProcess(i);  // Gọi xử lý khi nhấn nút
                  }
              } else {
                  TimeOutForKeyPress[i]--;
                  if (TimeOutForKeyPress[i] == 0) {
                      TimeOutForKeyPress[i] = 500;  // Reset timeout
                      if (KeyReg2[i] == PRESSED_STATE) {
                          subKeyProcess(i);  // Gọi lại khi nút được giữ lâu
                      }
                  }
              }
          }
      }
  }



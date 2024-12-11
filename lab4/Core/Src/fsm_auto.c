/*
 * fsm_auto.c
 *
 *  Created on: Dec 10, 2024
 *      Author: Admin
 */
#include "fsm_auto.h"
#include "schedule.h"

int status;
int t_red;
int t_yellow;
int t_green;
int a, b, c;
int counter0;
int counter1;
int counter2;

void fsm_auto_run() {
    switch (status) {
    case cd1:
        redgreen_state();
        if (counter0 == 0) {
            updateLedBuffer(5);
            quet_7SEG();
            led_NB--;
            led_DT--;
            counter0 = 100; // Reset counter for 1 second
        }
        if (counter1 == 0) {
            led_DT = 2;
            counter1 = 200; // Reset counter for 2 seconds
            status = cd2;
        }
        if (isButton1Pressed(0)) {
            status = MODE_2;
        }
        break;
    case cd2:
        redyellow_state();
        if (counter0 == 0) {
            updateLedBuffer(6);
            quet_7SEG();
            led_NB--;
            led_DT--;
            counter0 = 100;
        }
        if (counter1 == 0) {
            led_NB = 3;
            led_DT = 5;
            counter1 = 300;
            status = cd3;
        }
        if (isButton1Pressed(0)) {
            status = MODE_2;
        }
        break;
    case cd3:
        greenred_state();
        if (counter0 == 0) {
            updateLedBuffer(7);
            quet_7SEG();
            led_NB--;
            led_DT--;
            counter0 = 100;
        }
        if (counter1 == 0) {
            led_NB = 2;
            counter1 = 200;
            status = cd4;
        }
        if (isButton1Pressed(0)) {
            status = MODE_2;
        }
        break;
    case cd4:
        yellowred_state();
        if (counter0 == 0) {
            updateLedBuffer(8);
            quet_7SEG();
            led_NB--;
            led_DT--;
            counter0 = 100;
        }
        if (counter1 == 0) {
            led_NB = 5;
            led_DT = 3;
            counter0 = 0;
            counter1 = 300;
            status = cd1;
        }
        if (isButton1Pressed(0)) {
            status = MODE_2;
        }
        break;
    case MODE_2:
        run_ledblink();
        if (isButton1Pressed(1)) {
            t_red++;
            if (t_red > 99) {
                t_red = 1;
            }
            updateLedBuffer(2);
            quet_7SEG();
        }
        if (isButton1Pressed(0)) {
            status = MODE_3;
        }
        if (isButton1Pressed(2)) {
            a = t_red;
        }
        break;
    case MODE_3:
        run_ledblink();
        if (isButton1Pressed(1)) {
            t_yellow++;
            if (t_yellow > 99) {
                t_yellow = 1;
            }
            updateLedBuffer(3);
            quet_7SEG();
        }
        if (isButton1Pressed(0)) {
            status = MODE_4;
        }
        if (isButton1Pressed(2)) {
            b = t_yellow;
        }
        break;
    case MODE_4:
        run_ledblink();
        if (isButton1Pressed(1)) {
            t_green++;
            if (t_green > 99) {
                t_green = 0;
            }
            updateLedBuffer(4);
            quet_7SEG();
        }
        if (isButton1Pressed(0)) {
            status = mode1;
            counter4 = 0;
            counter5 = c * 100;
        }
        if (isButton1Pressed(2)) {
            c = t_green;
        }
        break;
    default:
        break;
    }
}

void run_ledblink() {
    if (counter2 == 0) {
        HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_0);
        HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_3);
        HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_1);
        HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_4);
        HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_2);
        HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_6);
        counter2 = 50; // Reset counter for 0.5 seconds
    }
}

void decrement_counters(void) {
    if (counter0 > 0) counter0--;
    if (counter1 > 0) counter1--;
    if (counter2 > 0) counter2--;
    if (counter4 > 0) counter4--;
    if (counter5 > 0) counter5--;
    if (counter6 > 0) counter6--;
}

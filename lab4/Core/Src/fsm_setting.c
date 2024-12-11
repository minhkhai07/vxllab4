/*
 * fsm_setting.c
 *
 *  Created on: Dec 10, 2024
 *      Author: Admin
 */
#include "fsm_setting.h"
#include "schedule.h"
int counter4;
int counter5;
void fsm_set() {
    switch (status) {
    case mode1:
        redgreen_state();
        if (counter4 == 0) {
            updateLedBuffer(9);
            quet_7SEG();
            a--;
            c--;
            counter4 = 100; // Reset counter for 1 second
        }
        if (counter5 == 0) {
            counter5 = b * 100; // Reset counter for b seconds
            status = mode2;
        }
        if (isButton1Pressed(0)) {
            status = MODE_2;
        }
        break;

    case mode2:
        c = t_yellow;
        redyellow_state();
        if (counter4 == 0) {
            updateLedBuffer(10);
            quet_7SEG();
            a--;
            c--;
            counter4 = 100; // Reset counter for 1 second
        }
        if (counter5 == 0) {
            a = t_green;
            c = t_red;
            counter5 = a * 100; // Reset counter for a seconds
            status = mode3;
        }
        if (isButton1Pressed(0)) {
            status = MODE_2;
        }
        break;

    case mode3:
        greenred_state();
        if (counter4 == 0) {
            updateLedBuffer(11);
            quet_7SEG();
            a--;
            c--;
            counter4 = 100; // Reset counter for 1 second
        }
        if (counter5 == 0) {
            a = t_yellow;
            counter5 = b * 100; // Reset counter for b seconds
            status = mode4;
        }
        if (isButton1Pressed(0)) {
            status = MODE_2;
        }
        break;

    case mode4:
        yellowred_state();
        if (counter4 == 0) {
            updateLedBuffer(12);
            quet_7SEG();
            a--;
            c--;
            counter4 = 100; // Reset counter for 1 second
        }
        if (counter5 == 0) {
            a = t_red;
            c = t_green;
            counter5 = a * 100; // Reset counter for a seconds
            status = mode1;
        }
        if (isButton1Pressed(0)) {
            status = MODE_2;
        }
        break;

    default:
        break;
    }
}





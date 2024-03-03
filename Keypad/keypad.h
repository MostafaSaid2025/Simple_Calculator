/* 
 * File:   keypad.h
 * Author: mostafa
 *
 * Created on December 20, 2023, 10:55 PM
 */

#ifndef KEYPAD_H
#define	KEYPAD_H

/* Section includes */

#include "keypad_cfg.h"
#include "../../MCAL_Layer/GPIO/hal_gpio.h"

/* Section Macro declarations */

#define ECU_KEYPAD_ROWS    4 
#define ECU_KEYPAD_COLUMNS 4

/* Section Macro Function declarations */

/* Section Data types declarations  */

typedef struct
{
    pin_config_t ECU_KEYPAD_ROWS_PINS[ECU_KEYPAD_ROWS];
    pin_config_t ECU_KEYPAD_COLUMNS_PINS[ECU_KEYPAD_COLUMNS];

}keypad_t;

/* Section of software interfaces */

Std_ReturnType keypad_initialize(const keypad_t* _keypad);
Std_ReturnType keypad_get_value(const keypad_t* _keypad , uint8 *value);


#endif	/* KEYPAD_H */


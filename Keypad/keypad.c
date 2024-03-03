/* 
 * File:   keypad.c
 * Author: mostafa
 *
 * Created on December 20, 2023, 10:55 PM
 */

#include "keypad.h"
#define _XTAL_FREQ 8000000

const uint8 keypad_value [ECU_KEYPAD_ROWS][ECU_KEYPAD_COLUMNS] = {
                                                            {7 , 8 , 9 , '/'},
                                                            {4 , 5 , 6 , '*'},
                                                            {1 , 2 , 3 , '-'},
                                                            {'#' , 0 , '=' , '+'}
                                                            };

Std_ReturnType keypad_initialize(const keypad_t* _keypad)
{
    Std_ReturnType ret = E_OK;
    uint8 row_counter  = ZERO_INIT , column_counter = ZERO_INIT;
    if (NULL == _keypad)
    {
        ret = E_NOT_OK;
    }
    else
    {
        for (row_counter = ZERO_INIT ; row_counter < ECU_KEYPAD_ROWS ; row_counter++)
        {
            ret = gpio_pin_initialize(&(_keypad->ECU_KEYPAD_ROWS_PINS[row_counter]));  
        }
        for (column_counter = ZERO_INIT ; column_counter < ECU_KEYPAD_COLUMNS ; column_counter++)
        {
            ret = gpio_pin_initialize(&(_keypad->ECU_KEYPAD_COLUMNS_PINS[column_counter]));
        }
    }
    return ret;

}
Std_ReturnType keypad_get_value(const keypad_t* _keypad , uint8 *value)
{
    Std_ReturnType ret = E_OK;
    uint8 l_row_counter = ZERO_INIT , l_column_counter = ZERO_INIT , l_counter = ZERO_INIT , column_value = ZERO_INIT;
    if (NULL == _keypad || NULL == value)
    {
        ret = E_NOT_OK;
    }
    else
    {
        for (l_row_counter = ZERO_INIT ; l_row_counter < ECU_KEYPAD_ROWS ; l_row_counter++)
        {
            for (l_counter = ZERO_INIT ; l_counter < ECU_KEYPAD_ROWS ; l_counter++)
            {
                ret = gpio_pin_write_logic(&(_keypad->ECU_KEYPAD_ROWS_PINS[l_counter]), GPIO_LOW);
            }
            ret = gpio_pin_write_logic(&(_keypad->ECU_KEYPAD_ROWS_PINS[l_row_counter]), GPIO_HIGH);
            __delay_ms(10);
            
            for (l_column_counter = ZERO_INIT ; l_column_counter < ECU_KEYPAD_COLUMNS ; l_column_counter++)
            {
                ret = gpio_pin_read_logic(&(_keypad->ECU_KEYPAD_COLUMNS_PINS[l_column_counter]) , &column_value);
                 if (GPIO_HIGH == column_value)
                 {
                     *value =  keypad_value[l_row_counter][l_column_counter];
                 }
      
            }

        }  
    }
    return ret;

}

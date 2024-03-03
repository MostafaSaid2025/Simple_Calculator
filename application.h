/* 
 * File:   application.h
 * Author: mostafa
 *
 * Created on October 30, 2023, 11:51 AM
 */

#ifndef APPLICATION_H
#define	APPLICATION_H



/* Section includes */

#include "ECU_Layer/ECU_layer_initialization.h"


/* Section Macro declarations */

#define _XTAL_FREQ 8000000

/* Section Macro Function declarations */

/* Section Data types declarations  */

extern keypad_t keypad1;
extern lcd_4bit_t LCD1 ;

/* Section of Software interfaces */
void Welcome_Fn(void);
void application_initialize (void);

Std_ReturnType Get_First_Number(uint32 *Number1 , char *operation);
Std_ReturnType Get_Second_Number(uint32 *Number2 , char *operation);
void convert_float_to_string(float num, char* str);
Std_ReturnType Calculation_FN (void);


#endif	/* APPLICATION_H */


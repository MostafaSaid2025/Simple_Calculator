/*
 * File:   application.c
 * Author: mostafa
 *
 * Created on October 30, 2023, 11:24 AM
 */

#include "application.h"

// Global variables
Std_ReturnType ret = E_NOT_OK; // Return status
volatile uint32 number1 = 0;   // First input number
volatile uint32 number2 = 0;   // Second input number
volatile float result = 0;     // Result of calculation
char operation_type1[2];       // Operation type for first input
char operation_type2[2];       // Operation type for second input
#define MAX_DIGITS 4            // Maximum number of digits for input

// Main function
void main() 
{
    uint8 num = 0; 
    application_initialize();
    Welcome_Fn();

    // Main loop
    while(1) {
        Calculation_FN();
        
        // Display message to try again
        ret = lcd_4bit_send_string_pos(&LCD1 , 3 , 7 , "Press 'ON' ");
        ret = lcd_4bit_send_string_pos(&LCD1 , 2 , 7 , "To Try Again ");
        
        // Wait for 'ON' press to try again
        while(1) {
            ret = keypad_get_value(&keypad1, &num);
            if ('#' == num) 
            {
                lcd_4bit_send_command(&LCD1 , _LCD_CLEAR);
                number1 = 0; 
                number2 = 0;
                while ('\0' != operation_type2[0])
                {
                    operation_type2[0] = '\0';
                }
                while ('\0' != operation_type1[0])
                {
                    operation_type1[0] = '\0';
                }
                break; // Break out of the inner loop to repeat calculation
            }
        }
    }
}

// Function to display a welcome message
void Welcome_Fn(void)
{
    lcd_4bit_send_string_pos(&LCD1 , 2 , 7 , "Welcome");
    __delay_ms(1000);
    lcd_4bit_send_command(&LCD1 , _LCD_CLEAR);
}

// Function to initialize the application
void application_initialize (void)
{
    ecu_initialization();  
}

// Function to get the first number from the user input
Std_ReturnType Get_First_Number(uint32 *Number1 , char *operation)
{
    Std_ReturnType ret = E_OK;
    uint8 array_numbers1[6] = { 0 ,0 ,0 ,0 ,0}; // Array to store digits
    uint8 n = 0;                                 // Counter for digits
    uint8 str1[MAX_DIGITS];                      // String to store digit as string
    uint8 num1 = 10;                              // Initial value for input number

    // Loop to get digits from user input
    for(n = 0 ; n < MAX_DIGITS+1 ; n++)
    {
        // Get input from keypad until a digit or operator is entered
        while (num1 == 10)
        {
            ret = keypad_get_value(&keypad1, &num1);

            // Check for operator input
            if (num1 == '*' || num1 == '/' || num1 == '-' || num1 == '+' || num1 == '=')
            {
                *operation = num1;
                ret |= lcd_4bit_send_char_data(&LCD1, num1);
                return ret;
            }
            // Check for clear input
            else if (num1 == '#')
            {
                ret = lcd_4bit_send_command(&LCD1 , _LCD_CLEAR);
                *operation = num1;
                number1 = 0;
                return ret;
            }
            else
            {/* NOTHING */}
        }
    
        // Convert digit to string and display on LCD
        array_numbers1[n] = num1;
        *Number1 = (*Number1*10+ array_numbers1[n]);
        ret |= convert_uint8_to_string(num1, str1);
        ret |= lcd_4bit_send_string(&LCD1, str1);
        num1 = 10;
        

        __delay_ms(240);
    }
    return ret;
}

// Function to get the second number from the user input
Std_ReturnType Get_Second_Number(uint32 *Number2 , char *operation)
{
    Std_ReturnType ret = E_OK;
    uint8 array_numbers2[6] = { 0 ,0 ,0 ,0 ,0}; // Array to store digits
    uint8 n = 0;                                 // Counter for digits
    uint8 str1[MAX_DIGITS];                      // String to store digit as string
    uint8 num1 = 10;                              // Initial value for input number

    // Check if the previous operation was '='
    if ('=' == operation_type1[0])
    {
        return ret; // Return without getting the second number
    }
    else{/* NOTHING */}
        
    // Loop to get digits from user input
    for(n = 0 ; n < MAX_DIGITS+1 ; n++)
    {
        // Get input from keypad until a digit or operator is entered
        while (num1 == 10)
        {
            ret = keypad_get_value(&keypad1, &num1);
            
            // Check for operator input
            if (num1 == '*' || num1 == '/' || num1 == '-' || num1 == '+' || num1 == '=')
            {
                *operation = num1;
                ret |= lcd_4bit_send_char_data(&LCD1, num1);            
                return ret; 
            }
            // Check for clear input
            else if (num1 == '#')
            {
                ret = lcd_4bit_send_command(&LCD1 , _LCD_CLEAR);
                *operation = num1;
                number1 = 0;
                number2 = 0;
                return ret;
            }
            else
            {/* NOTHING */}
        }
        
        // Convert digit to string and display on LCD
        array_numbers2[n] = num1;
        *Number2 = (*Number2*10+ array_numbers2[n]);
        ret |= convert_uint8_to_string(num1, str1);
        ret |= lcd_4bit_send_string(&LCD1, str1);
        num1 = 10;
        
        __delay_ms(240);
    }
    return ret;
}

// Function to convert a floating point number to string
void convert_float_to_string(float num, char *str) 
{
    sprintf(str, "%.*f", 2, num); // Convert to string with 2 decimal places
}

// Function to perform the calculation based on the operation type
Std_ReturnType Calculation_FN(void) {
    char str1[20]; // String to store result
    ret = Get_First_Number(&number1, operation_type1); // Get first number
    __delay_ms(220);
    ret = Get_Second_Number(&number2, operation_type2); // Get second number
    
    // Perform calculation based on operation type
    if ('+' == operation_type1[0]) 
    {
        result = number1 + number2;
    } 
    else if ('-' == operation_type1[0]) 
    {
        result = number1 - number2;
    } 
    else if ('/' == operation_type1[0]) 
    {
        result = (float)number1 / (float)number2;
    } 
    else if ('*' == operation_type1[0]) 
    {
        result = number1 * number2;
    }

    // Convert result to string and send to LCD
    convert_float_to_string(result, str1);
    ret |= lcd_4bit_send_string(&LCD1, str1);
}

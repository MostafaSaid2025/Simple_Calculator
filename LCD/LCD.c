/* 
 * File:   LCD.c
 * Author: mostafa
 *
 * Created on December 21, 2023, 8:28 PM
 */

#include "LCD.h"
#define _XTAL_FREQ 4000000


static Std_ReturnType lcd_send_4bits(const lcd_4bit_t* lcd , uint8 command);
static Std_ReturnType lcd_4bit_send_enable_signal(const lcd_4bit_t* lcd);
static Std_ReturnType lcd_8bit_send_enable_signal(const lcd_8bit_t* lcd);
static Std_ReturnType lcd_4bit_set_cursor(const lcd_4bit_t* lcd , uint8 row , uint8 column);
static Std_ReturnType lcd_8bit_set_cursor(const lcd_8bit_t* lcd , uint8 row , uint8 column);


Std_ReturnType lcd_4bit_initialize(const lcd_4bit_t* lcd)
{
     Std_ReturnType ret = E_OK;
     uint8 lcd_counter = ZERO_INIT;
     if (NULL == lcd)
     {
         ret = E_NOT_OK;
     }
     else
     {
         ret = gpio_pin_initialize(&(lcd->lcd_rs));
         ret = gpio_pin_initialize(&(lcd->lcd_en));
         for (lcd_counter = 0 ; lcd_counter < 4 ; lcd_counter++)
         {
             ret = gpio_pin_initialize(&(lcd->lcd_pin[lcd_counter]));
         }
         __delay_ms(20);
         ret = lcd_4bit_send_command(lcd , _LCD_8BIT_MODE_2_LINE);
         __delay_ms(5);
         ret = lcd_4bit_send_command(lcd , _LCD_8BIT_MODE_2_LINE);
         __delay_us(150);
         ret = lcd_4bit_send_command(lcd , _LCD_8BIT_MODE_2_LINE);
         
         ret = lcd_4bit_send_command(lcd , _LCD_CLEAR);
         ret = lcd_4bit_send_command(lcd , _LCD_RETURN_HOME);
         ret = lcd_4bit_send_command(lcd , _LCD_ENTRY_MODE_INC_SHIFT_OFF);
         ret = lcd_4bit_send_command(lcd , _LCD_DISPLAY_ON_UNDERLINE_OFF_CURSOR_OFF);
         ret = lcd_4bit_send_command(lcd , _LCD_4BIT_MODE_2_LINE);
         ret = lcd_4bit_send_command(lcd , 0x80);
         
 
     }
     return ret;

}
Std_ReturnType lcd_4bit_send_command(const lcd_4bit_t* lcd , uint8 command)
{
    Std_ReturnType ret = E_OK;
     if (NULL == lcd)
     {
         ret = E_NOT_OK;
     }
     else
     {
         ret = gpio_pin_write_logic(&(lcd->lcd_rs) , GPIO_LOW);
         ret = lcd_send_4bits(lcd , (command >> 4));
         ret = lcd_4bit_send_enable_signal(lcd);
         ret = lcd_send_4bits(lcd , (command));
         ret = lcd_4bit_send_enable_signal(lcd); 
     }
     return ret;

}
Std_ReturnType lcd_4bit_send_char_data(const lcd_4bit_t* lcd , uint8 data)
{
    Std_ReturnType ret = E_OK;
     if (NULL == lcd)
     {
         ret = E_NOT_OK;
     }
     else
     {
         ret = gpio_pin_write_logic(&(lcd->lcd_rs) , GPIO_HIGH);
         ret = lcd_send_4bits(lcd , (data >> 4));
         ret = lcd_4bit_send_enable_signal(lcd);
         ret = lcd_send_4bits(lcd , (data));
         ret = lcd_4bit_send_enable_signal(lcd); 
         
     }
     return ret;

}
Std_ReturnType lcd_4bit_send_char_data_pos(const lcd_4bit_t* lcd ,uint8 row , uint8 column , uint8 data)
{
    Std_ReturnType ret = E_OK;
     if (NULL == lcd)
     {
         ret = E_NOT_OK;
     }
     else
     {
         ret = lcd_4bit_set_cursor(lcd , row , column);
         ret = lcd_4bit_send_char_data(lcd , data);
     }
     return ret;

}
Std_ReturnType lcd_4bit_send_string(const lcd_4bit_t* lcd , uint8 *str)
{
    Std_ReturnType ret = E_OK;
     if (NULL == lcd || NULL == str)
     {
         ret = E_NOT_OK;
     }
     else
     {
         ret = gpio_pin_write_logic(&(lcd->lcd_rs) , GPIO_HIGH);
         while(*str)
         {
             ret = lcd_4bit_send_char_data(lcd , *str++);
         }
     }
     return ret;


}
Std_ReturnType lcd_4bit_send_string_pos(const lcd_4bit_t* lcd ,uint8 row , uint8 column , uint8 *str)
{
    Std_ReturnType ret = E_OK;
     if (NULL == lcd || NULL == str)
     {
         ret = E_NOT_OK;
     }
     else
     {
         ret = lcd_4bit_set_cursor(lcd , row , column);
         while(*str)
         {
            ret = lcd_4bit_send_char_data(lcd , *str++);
         }
     }
     return ret;
}


Std_ReturnType lcd_4bit_send_custom_char(const lcd_4bit_t* lcd ,uint8 row , uint8 column ,const uint8 _chr[] , uint8 mem_pos)
{
    Std_ReturnType ret = E_OK;
    uint8 lcd_counter = ZERO_INIT;
     if (NULL == lcd)
     {
         ret = E_NOT_OK;
     }
     else
     {
         ret = lcd_4bit_send_command(lcd , (_LCD_CGRAM_START + (mem_pos*8)));
         for (lcd_counter = 0 ; lcd_counter < 8 ; lcd_counter++)
         {
             ret = lcd_4bit_send_char_data(lcd ,_chr[lcd_counter]);
         }
         ret = lcd_4bit_send_char_data_pos(lcd , row , column , mem_pos); 
     }
     return ret;

}


Std_ReturnType lcd_8bit_initialize(const lcd_8bit_t* lcd)
{
    Std_ReturnType ret = E_OK;
     uint8 lcd_counter = ZERO_INIT;
     if (NULL == lcd)
     {
         ret = E_NOT_OK;
     }
     else
     {
         ret = gpio_pin_initialize(&(lcd->lcd_rs));
         ret = gpio_pin_initialize(&(lcd->lcd_en));
         for (lcd_counter = 0 ; lcd_counter < 8 ; lcd_counter++)
         {
             ret = gpio_pin_initialize(&(lcd->lcd_pin[lcd_counter]));
         }
         __delay_ms(20);
         ret = lcd_8bit_send_command(lcd , _LCD_8BIT_MODE_2_LINE);
         __delay_ms(5);
         ret = lcd_8bit_send_command(lcd , _LCD_8BIT_MODE_2_LINE);
         __delay_us(150);
         ret = lcd_8bit_send_command(lcd , _LCD_8BIT_MODE_2_LINE);
         
         ret = lcd_8bit_send_command(lcd , _LCD_CLEAR);
         ret = lcd_8bit_send_command(lcd , _LCD_RETURN_HOME);
         ret = lcd_8bit_send_command(lcd , _LCD_ENTRY_MODE_INC_SHIFT_OFF);
         ret = lcd_8bit_send_command(lcd , _LCD_DISPLAY_ON_UNDERLINE_OFF_CURSOR_OFF);
         ret = lcd_8bit_send_command(lcd , _LCD_8BIT_MODE_2_LINE);
         ret = lcd_8bit_send_command(lcd , 0x80);

     }
     return ret;

}
Std_ReturnType lcd_8bit_send_command(const lcd_8bit_t* lcd , uint8 command)
{
    Std_ReturnType ret = E_OK;
    uint8 lcd_counter = ZERO_INIT;
     if (NULL == lcd)
     {
         ret = E_NOT_OK;
     }
     else
     {
         ret = gpio_pin_write_logic(&(lcd->lcd_rs) , GPIO_LOW);
         for (lcd_counter = 0 ; lcd_counter < 8 ; lcd_counter++)
         {
             ret = gpio_pin_write_logic(&(lcd->lcd_pin[lcd_counter]) , (command>> lcd_counter) & (uint8)0x01);
         }
         ret = lcd_8bit_send_enable_signal(lcd);
     }
     return ret;

}
Std_ReturnType lcd_8bit_send_char_data(const lcd_8bit_t* lcd , uint8 data)
{
    Std_ReturnType ret = E_OK;
    uint8 lcd_counter = ZERO_INIT;
     if (NULL == lcd)
     {
         ret = E_NOT_OK;
     }
     else
     {
         ret = gpio_pin_write_logic(&(lcd->lcd_rs) , GPIO_HIGH);
         for (lcd_counter = 0 ; lcd_counter < 8 ; lcd_counter++)
         {
             ret = gpio_pin_write_logic(&(lcd->lcd_pin[lcd_counter]) , (data>> lcd_counter) & (uint8)0x01);
         }
         ret = lcd_8bit_send_enable_signal(lcd);
     }
     return ret;
}
Std_ReturnType lcd_8bit_send_char_data_pos(const lcd_8bit_t* lcd ,uint8 row , uint8 column , uint8 data)
{
    Std_ReturnType ret = E_OK;
     if (NULL == lcd)
     {
         ret = E_NOT_OK;
     }
     else
     {
         ret = lcd_8bit_set_cursor(lcd , row , column);
         ret = lcd_8bit_send_char_data(lcd , data);
     }
     return ret;

}
Std_ReturnType lcd_8bit_send_string(const lcd_8bit_t* lcd , uint8 *str)
{
    Std_ReturnType ret = E_OK;
     if (NULL == lcd || NULL == str)
     {
         ret = E_NOT_OK;
     }
     else
     {
         ret = gpio_pin_write_logic(&(lcd->lcd_rs) , GPIO_HIGH);
         while(*str)
         {
             ret = lcd_8bit_send_char_data(lcd , *str++);

         }
     }
     return ret;
}
Std_ReturnType lcd_8bit_send_string_pos(const lcd_8bit_t* lcd ,uint8 row , uint8 column , uint8 *str)
{
     Std_ReturnType ret = E_OK;
     if (NULL == lcd || NULL == str)
     {
         ret = E_NOT_OK;
     }
     else
     {
         ret = gpio_pin_write_logic(&(lcd->lcd_rs) , GPIO_HIGH);
         ret = lcd_8bit_set_cursor(lcd , row , column);
         while(*str)
         {
             ret = lcd_8bit_send_char_data(lcd , *str++);
         }
     }
     return ret;
}
Std_ReturnType lcd_8bit_send_custom_char(const lcd_8bit_t* lcd ,uint8 row , uint8 column ,const uint8 _chr[] , uint8 mem_pos)
{
    Std_ReturnType ret = E_OK;
    uint8 lcd_counter = ZERO_INIT;
     if (NULL == lcd)
     {
         ret = E_NOT_OK;
     }
     else
     {
         ret = lcd_8bit_send_command(lcd , (_LCD_CGRAM_START + (mem_pos*8)));
         for (lcd_counter = 0 ; lcd_counter < 8 ; lcd_counter++)
         {
             ret = lcd_8bit_send_char_data(lcd ,_chr[lcd_counter]);
         }
         ret = lcd_8bit_send_char_data_pos(lcd , row , column , mem_pos); 
     }
     return ret;
}


Std_ReturnType convert_uint8_to_string(uint8 value , uint8 *str)
{
    Std_ReturnType ret = E_OK;
     if (NULL == str)
     {
         ret = E_NOT_OK;
     }
     else
     {
         memset(str , '\0' , 4);
         sprintf(str , "%i" , value);  
     }
     return ret;


}
Std_ReturnType convert_uint16_to_string(uint16 value , uint8 *str)
{
    Std_ReturnType ret = E_OK;
     if (NULL == str)
     {
         ret = E_NOT_OK;
     }
     else
     {
         memset(str , '\0' , 6);
         sprintf(str , "%i" , value);  
     }
     return ret;
     
}
Std_ReturnType convert_uint32_to_string(uint32 value , uint8 *str)
{
    Std_ReturnType ret = E_OK;
     if (NULL == str)
     {
         ret = E_NOT_OK;
     }
     else
     {
         memset(str , '\0' , 11);
         sprintf(str , "%i" , value);  
     }
     return ret;

}
/************  Helper functions   *************/

static Std_ReturnType lcd_send_4bits(const lcd_4bit_t* lcd , uint8 command)
{
    Std_ReturnType ret = E_OK;
     if (NULL == lcd)
     {
         ret = E_NOT_OK;
     }
     else
     {
         ret = gpio_pin_write_logic(&(lcd->lcd_pin[0]), (command >> 0)& (uint8)0x01);
         ret = gpio_pin_write_logic(&(lcd->lcd_pin[1]), (command >> 1)& (uint8)0x01);
         ret = gpio_pin_write_logic(&(lcd->lcd_pin[2]), (command >> 2)& (uint8)0x01);
         ret = gpio_pin_write_logic(&(lcd->lcd_pin[3]), (command >> 3)& (uint8)0x01);
         
     }
     return ret;
}

static Std_ReturnType lcd_4bit_send_enable_signal(const lcd_4bit_t* lcd)
{
    Std_ReturnType ret = E_OK;
     if (NULL == lcd)
     {
         ret = E_NOT_OK;
     }
     else
     {
        ret = gpio_pin_write_logic(&(lcd->lcd_en) , GPIO_HIGH); 
        __delay_us(5);
        ret = gpio_pin_write_logic(&(lcd->lcd_en) , GPIO_LOW); 
         
     }
     return ret;

}

static Std_ReturnType lcd_8bit_send_enable_signal(const lcd_8bit_t* lcd)
{
    Std_ReturnType ret = E_OK;
     if (NULL == lcd)
     {
         ret = E_NOT_OK;
     }
     else
     {
        ret = gpio_pin_write_logic(&(lcd->lcd_en) , GPIO_HIGH); 
        __delay_us(5);
        ret = gpio_pin_write_logic(&(lcd->lcd_en) , GPIO_LOW); 
         
     }
     return ret;

}

static Std_ReturnType lcd_4bit_set_cursor(const lcd_4bit_t* lcd , uint8 row , uint8 column)
{
    Std_ReturnType ret = E_OK;
    column--;
     if (NULL == lcd)
     {
         ret = E_NOT_OK;
     }
     else
     {
         switch (row)
         {
             case ROW1:
                 ret = lcd_4bit_send_command(lcd , (0x80 + column));break;
            case ROW2:
                 ret = lcd_4bit_send_command(lcd , (0xC0 + column));break;
            case ROW3:
                 ret = lcd_4bit_send_command(lcd , (0x94 + column));break;
            case ROW4:
                 ret = lcd_4bit_send_command(lcd , (0xD4 + column));break;   
            default: ;    
         }
     }
     return ret;

}

static Std_ReturnType lcd_8bit_set_cursor(const lcd_8bit_t* lcd , uint8 row , uint8 column)
{
    Std_ReturnType ret = E_OK;
    column--;
     if (NULL == lcd)
     {
         ret = E_NOT_OK;
     }
     else
     {
         switch (row)
         {
             case ROW1:
                 ret = lcd_8bit_send_command(lcd , (0x80 + column));break;
            case ROW2:
                 ret = lcd_8bit_send_command(lcd , (0xC0 + column));break;
            case ROW3:
                 ret = lcd_8bit_send_command(lcd , (0x94 + column));break;
            case ROW4:
                 ret = lcd_8bit_send_command(lcd , (0xD4 + column));break;
            default: ;     
         }
     }
     return ret;

}
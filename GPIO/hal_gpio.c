/* 
 * File:   hal_gpio.c
 * Author: mostafa
 *
 * Created on October 30, 2023, 11:24 AM
 */

#include "hal_gpio.h"

uint8 *tris_registers[] = {&TRISA,&TRISB , &TRISC , &TRISD ,&TRISE}; 
uint8 *lat_registers[] =  {&LATA, &LATB , &LATC , &LATD ,&LATE}; 
uint8 *port_registers[] = {&PORTA, &PORTB , &PORTC , &PORTD ,&PORTE}; 


Std_ReturnType gpio_pin_direction_initialize(const pin_config_t *pin_config)
{
    Std_ReturnType ret = E_OK;
    if (NULL == pin_config || pin_config->pin > PORT_PIN_MAX_NUMBER-1)
    {
        ret = E_NOT_OK;
    }
    else
    {
        switch(pin_config->direction)
        {
            case GPIO_Direction_Output :
                CLEAR_BIT(*tris_registers[pin_config->port] ,pin_config->pin);
                break;
            case GPIO_Direction_Input  :
                SET_BIT(*tris_registers[pin_config->port] ,pin_config->pin);
                break;
                
            default :  ret = E_NOT_OK;
        }
        return ret;
    }
}
Std_ReturnType gpio_pin_direction_status(const pin_config_t *pin_config ,direction_t *direction_status)
{
     Std_ReturnType ret = E_OK;
    if (NULL == pin_config || pin_config->pin > PORT_PIN_MAX_NUMBER-1 || NULL == direction_status)
    {
        ret = E_NOT_OK;
    }
    else
    {
        *direction_status = pin_config->direction;
    }
     return ret;
    
}
Std_ReturnType gpio_pin_write_logic(const pin_config_t *pin_config ,logic_t logic)
{
     Std_ReturnType ret = E_OK;
    if (NULL == pin_config || pin_config->pin > PORT_PIN_MAX_NUMBER-1)
    {
        ret = E_NOT_OK;
    }
    else
    {
        switch (logic)
        {
            case GPIO_LOW :
                
                CLEAR_BIT(*lat_registers[pin_config->port] ,pin_config->pin);
                break;
            case GPIO_HIGH :
                
                SET_BIT(*lat_registers[pin_config->port] ,pin_config->pin);
                break;
            default : ret = E_NOT_OK;
        }
    }
     return ret;
}
Std_ReturnType gpio_pin_read_logic(const pin_config_t *pin_config ,logic_t *logic_status)
{
     Std_ReturnType ret = E_OK;
    if (NULL == pin_config || pin_config->pin > PORT_PIN_MAX_NUMBER-1 || NULL == logic_status)
    {
        ret = E_NOT_OK;
    }
    else
    {
        *logic_status = READ_BIT(*port_registers[pin_config->port] , pin_config->pin);
    }
     return ret;
}
Std_ReturnType gpio_pin_toggle_logic(const pin_config_t *pin_config)
{
     Std_ReturnType ret = E_OK;
    if (NULL == pin_config || pin_config->pin > PORT_PIN_MAX_NUMBER-1)
    {
        ret = E_NOT_OK;
    }
    else
    {   
        TOGGLE_BIT(*lat_registers[pin_config->port] ,pin_config->pin);
    }
     return ret;
}
Std_ReturnType gpio_pin_initialize(const pin_config_t *pin_config)
{
    Std_ReturnType ret = E_OK;
    if (NULL == pin_config || pin_config->pin > PORT_PIN_MAX_NUMBER-1)
    {
        ret = E_NOT_OK;
    }
    else
    {   
         switch(pin_config->direction)
        {
            case GPIO_Direction_Output :
                CLEAR_BIT(*tris_registers[pin_config->port] ,pin_config->pin);
                if (pin_config->logic == GPIO_LOW)
                {
                   CLEAR_BIT(*lat_registers[pin_config->port] ,pin_config->pin);
                }
                else if (pin_config->logic == GPIO_HIGH)
                {
                   SET_BIT(*lat_registers[pin_config->port] ,pin_config->pin);
                }
                else
                {
                   ret = E_NOT_OK;   
                }
                break;
            case GPIO_Direction_Input  :
                SET_BIT(*tris_registers[pin_config->port] ,pin_config->pin);
                break;
                
            default :  ret = E_NOT_OK;
        }
        
    }
     return ret;
    
}


Std_ReturnType gpio_port_direction_initialize(port_index_t port ,uint8 direction)
{
    Std_ReturnType ret = E_OK;
    if (port > PORT_MAX_NUMBER-1)
    {
        ret = E_NOT_OK;   
    }
    else
    {
        *tris_registers[port] = direction;
    }
    return ret;
    
}
Std_ReturnType gpio_port_direction_status(port_index_t port ,uint8 *direction_status)
{
    Std_ReturnType ret = E_OK;
    if (port > PORT_MAX_NUMBER-1 || NULL == direction_status)
    {
        ret = E_NOT_OK;   
    }
    else
    {
        *direction_status = *tris_registers[port];
    }
    return ret;
}
Std_ReturnType gpio_port_write_logic(port_index_t port ,uint8 logic)
{
    Std_ReturnType ret = E_OK;
    if (port > PORT_MAX_NUMBER-1)
    {
        ret = E_NOT_OK;   
    }
    else
    {
        *lat_registers[port] = logic;
    }
    return ret;
}
Std_ReturnType gpio_port_read_logic(port_index_t port ,uint8 *logic_status)
{
    Std_ReturnType ret = E_OK;
    if (port > PORT_MAX_NUMBER-1 || NULL == logic_status)
    {
        ret = E_NOT_OK;   
    }
    else
    {
        *logic_status = *lat_registers[port];
    }
    return ret;
    
}
Std_ReturnType gpio_port_toggle_logic(port_index_t port)
{
    Std_ReturnType ret = E_OK;
    if (port > PORT_MAX_NUMBER-1)
    {
        ret = E_NOT_OK;   
    }
    else
    {
        *lat_registers[port] ^= 0xFF;
    }
    return ret;   
}

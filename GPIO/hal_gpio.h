/* 
 * File:   hal_gpio.h
 * Author: mostafa
 *
 * Created on October 30, 2023, 11:35 AM
 */

#ifndef HAL_GPIO_H
#define	HAL_GPIO_H

/* Section includes */

#include "../proc/pic18f4620.h"
#include "../mcal_std_types.h"
#include "../device_config.h"

/* Section Macro declarations */
#define BIT_MASK  1

#define PORT_MAX_NUMBER  5
#define PORT_PIN_MAX_NUMBER  8


/* Section Macro Function declarations */

#define HWREG(_x)    (*(volatile uint8*)_x)

#define SET_BIT(REG , BIT_POSN)       REG |= (BIT_MASK<< BIT_POSN)
#define CLEAR_BIT(REG , BIT_POSN)     REG &= ~(BIT_MASK<< BIT_POSN)
#define TOGGLE_BIT(REG , BIT_POSN)    REG ^= (BIT_MASK<< BIT_POSN)
#define READ_BIT(REG , BIT_POSN)     ((REG >>  BIT_POSN)  && BIT_MASK)

/* Section Data types declarations  */

typedef enum 
{
    GPIO_LOW = 0 ,
    GPIO_HIGH        
}logic_t;

typedef enum 
{
    GPIO_Direction_Output = 0,
    GPIO_Direction_Input        
}direction_t;

typedef enum 
{
    PORTA_INDEX = 0,
    PORTB_INDEX,
    PORTC_INDEX,
    PORTD_INDEX,
    PORTE_INDEX     
}port_index_t;

typedef enum
{
    GPIO_PIN0 = 0,
    GPIO_PIN1,
    GPIO_PIN2,
    GPIO_PIN3,
    GPIO_PIN4,        
    GPIO_PIN5,        
    GPIO_PIN6,        
    GPIO_PIN7        
}pin_index_t;

typedef struct
{
    uint8 port : 3;
    uint8 pin  :  3;
    uint8 logic : 1;
    uint8 direction : 1;

}pin_config_t;

/* Section Function declarations */

Std_ReturnType gpio_pin_direction_initialize(const pin_config_t *pin_config);
Std_ReturnType gpio_pin_direction_status(const pin_config_t *pin_config ,direction_t *direction_status);
Std_ReturnType gpio_pin_write_logic(const pin_config_t *pin_config ,logic_t logic);
Std_ReturnType gpio_pin_read_logic(const pin_config_t *pin_config ,logic_t *logic_status);
Std_ReturnType gpio_pin_toggle_logic(const pin_config_t *pin_config);
Std_ReturnType gpio_pin_initialize(const pin_config_t *pin_config);


Std_ReturnType gpio_port_direction_initialize(port_index_t port ,uint8 direction);
Std_ReturnType gpio_port_direction_status(port_index_t port ,uint8 *direction_status);
Std_ReturnType gpio_port_write_logic(port_index_t port ,uint8 logic);
Std_ReturnType gpio_port_read_logic(port_index_t port ,uint8 *logic_status);
Std_ReturnType gpio_port_toggle_logic(port_index_t port);



#endif	/* HAL_GPIO_H */


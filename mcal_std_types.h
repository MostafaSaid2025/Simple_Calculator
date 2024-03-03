/* 
 * File:   mcal_std_types.h
 * Author: mostafa
 *
 * Created on October 30, 2023, 11:41 AM
 */

#ifndef MCAL_STD_TYPES_H
#define	MCAL_STD_TYPES_H
/* Section includes */

#include "std_libraries.h"
#include "compiler.h"

/* Section Macro declarations */


/* Section Macro Function declarations */

#define STD_HIGH       0x01
#define STD_LOW        0x00

#define STD_ON         0x01
#define STD_OFF        0x00

#define STD_ACTIVE     0x01
#define STD_IDLE       0x00

#define E_OK         (Std_ReturnType)0x00
#define E_NOT_OK     (Std_ReturnType)0x01

#define ZERO_INIT 0

/* Section Data types declarations  */

typedef unsigned char uint8;
typedef long long  uint32;
typedef unsigned short uint16;
typedef signed char sint8;
typedef signed int sint32;
typedef signed short sint16;

typedef uint8 Std_ReturnType;

#endif	/* MCAL_STD_TYPES_H */


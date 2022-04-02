#ifndef TYPEDEFS_H
#define TYPEDEFS_H

/* Incluldes */

/* Defines */
typedef signed char					S1;		/* Signed 1byte data type				*/
typedef signed short				S2;		/* Signed 2byte data type				*/
typedef signed long					S4;		/* Signed 4byte data type				*/
typedef unsigned char				U1;		/* Unsigned 1byte data type				*/
typedef unsigned short				U2;		/* Unsigned 2byte data type				*/
typedef unsigned long				U4;		/* Unsigned 4byte data type				*/
typedef volatile signed char		VS1;	/* Volatile signed 1byte data type		*/
typedef volatile signed short		VS2;	/* Volatile signed 2byte data type		*/
typedef volatile signed long		VS4;	/* Volatile signed 4byte data type		*/
typedef volatile unsigned char		VU1;	/* Volatile unsigned 1byte data type	*/
typedef volatile unsigned short		VU2;	/* Volatile unsigned 2byte data type	*/
typedef volatile unsigned long		VU4;	/* Volatile unsigned 4byte data type	*/
typedef float						F4;		/* Floating point 4byte data type		*/
typedef double						F8;		/* Floating point 8byte data type		*/
typedef int							BL;		/* Boolean data type					*/

/* Enum */
enum EN_COLOR{
    White,
    Black,
};

/* Macro Functions */

/* Variables */

/* Constants */

/* Prototypes */

#endif /* #ifndef TYPEDEFS_H */
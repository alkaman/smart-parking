/*******************************************************************************************************************************//**
 *
 * @file		DR_EINT.h
 * @brief		Encabezados, Includes y Defines
 * @date		11 de nov. de 2016
 * @author		Alan Kinast, Marcos Trautman
 *
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** MODULO
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** INCLUDES GLOBALES
 **********************************************************************************************************************************/
#include "DR_tipos.h"
#include "DR_pinsel.h"
/***********************************************************************************************************************************
 *** DEFINES GLOBALES
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** MACROS GLOBALES
 **********************************************************************************************************************************/
//0xE000E100UL : Direccion de inicio de los registros de habilitación (set) de interrupciones en el NVIC:
#define		ISER		( ( uint32_t * ) 0xE000E100UL )
//0xE000E180UL : Direccion de inicio de los registros de deshabilitacion (clear) de interrupciones en el NVIC:
#define		ICER		( (  uint32_t * ) 0xE000E180UL )


//Registros ISER: Para habilitar las Interupciones Se activan con 1 Escribiendo un 0 no hace nada
#define		ISER0		ISER[0]
#define		ISER1		ISER[1]
#define		ISE_EINT3	ISER[0] |= (0x00000001 << 21)  //ISER0->bit21 pongo un 1 en el bit 21 para habilitar la INT EINT3
#define     ISE_EINT2	ISER[0] |= (0x00000001 << 20)  //ISER0->bit20 pongo un 1 en el bit 20 para habilitar la INT EINT2
#define     ISE_EINT1	ISER[0] |= (0x00000001 << 19)  //ISER0->bit19 pongo un 1 en el bit 19 para habilitar la INT EINT1
#define     ISE_EINT0	ISER[0] |= (0x00000001 << 18)  //ISER0->bit18 pongo un 1 en el bit 18 para habilitar la INT EINT1
#define		ISE_ADC		ISER[0] |= (0x00000001 << 22)

// Registro EXTMODE : Para seleccionar si la ISR Externa activa por flanco ó nivel
#define		EXTMODE 		( (uint32_t  * ) 0x400FC148 )
#define		EXTMODE3_F		EXTMODE[0] |= 0x00000001 << 3  // EINT3 por flanco
#define		EXTMODE2_F		EXTMODE[0] |= 0x00000001 << 2  // EINT2 por flanco
#define		EXTMODE1_F		EXTMODE[0] |= 0x00000001 << 1  // EINT1 por flanco
#define		EXTMODE0_F		EXTMODE[0] |= 0x00000001       // EINT0 por flanco

// Registro EXTPOLAR : selecciona Polaridad del EXTMODE
#define    EXTPOLAR        ( (uint32_t  * ) 0x400FC14C )
#define    EXTPOLAR3_P      EXTPOLAR[0] |= 0X00000001 << 3 // Flanco ó Nivel Positivo
#define    EXTPOLAR2_P      EXTPOLAR[0] |= 0X00000001 << 2 // Flanco ó Nivel Positivo
#define    EXTPOLAR1_P      EXTPOLAR[0] |= 0X00000001 << 1 // Flanco ó Nivel Positivo
#define    EXTPOLAR0_P      EXTPOLAR[0] |= 0X00000001      // Flanco ó Nivel Positivo


//Registros ICER: Para deshabilitar las Interupciones Se desactivan con 1 Escribiendo un 0 no hace nada
//Registros ICER:

#define		ICER0		ICER[0]
#define		ICER1		ICER[1]
#define		ICE_EINT3	ICER0 |= (0x00000001 << 21) // deshabilito a EINT3
#define		ICE_EINT2	ICER0 |= (0x00000001 << 20) // deshabilito a EINT2
#define		ICE_EINT1	ICER0 |= (0x00000001 << 19) // deshabilito a EINT1
#define		ICE_EINT0	ICER0 |= (0x00000001 << 18) // deshabilito a EINT0
#define		ICE_ADC		ICER0 |= (0x00000001 << 22)


#define		EXTINT 		( (uint32_t  * ) 0x400FC140UL ) // Reg de Flags para limpiar la ISR

#define		CLR_EINT3		EXTINT[0] |= 0x00000001 << 3 // bajo el flag de EINT3
#define		CLR_EINT2		EXTINT[0] |= 0x00000001 << 2 // bajo el flag de EINT2
#define		CLR_EINT1		EXTINT[0] |= 0x00000001 << 1 // bajo el flag de EINT1
#define		CLR_EINT0		EXTINT[0] |= 0x00000001      // bajo el flag de EINT0

/***********************************************************************************************************************************
 *** TIPO DE DATOS GLOBALES
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** VARIABLES GLOBALES
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** PROTOTIPOS DE FUNCIONES GLOBALES
 **********************************************************************************************************************************/
void EXT0_Inicializacion( void );
void Emergency_STOP (void);

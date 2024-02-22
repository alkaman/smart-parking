/*******************************************************************************************************************************//**
 *
 * @file		DR_Adc.h
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
#include"DR_tipos.h"
#include "DR_pinsel.h"
/***********************************************************************************************************************************
 *** DEFINES GLOBALES
 **********************************************************************************************************************************/
#define 	PCONP	(* ( ( __RW uint32_t  * ) 0x400FC0C4UL ))
#define 	PCADC	12
#define		PCLKSEL		( ( __RW uint32_t  * ) 0x400FC1A8UL )
#define		PCLKSEL0	PCLKSEL[0]
#define		PCLKSEL1	PCLKSEL[1]
#define		DIR_SCS			( (uint32_t *) 0x400FC1A0UL)
//0x400FC104UL: Registro de configuracion del clock:
#define		DIR_CCLKCFG		( (uint32_t *) 0x400FC104UL)
//0x400FC10CUL: Registro de seleccion del clock:
#define		DIR_CLKSRCSEL	( (uint32_t *) 0x400FC10CUL)
//0x400FC1C8UL: Clock Output Config register:
#define		DIR_CLKOUTCFG	( (uint32_t *) 0x400FC1C8UL)
//0x400FC000UL: Flash access configuration:
#define		DIR_FLASHCFG	( (uint32_t *) 0x400FC000UL)

/**********************Registros de los PLL*******************************************************************************************/

//0x400FC080UL: Registro de control del PLL0:
#define		DIR_PLL0CON		( (uint32_t *) 0x400FC080UL)
//0x400FC084UL: Registro de configuracion del PLL0:
#define		DIR_PLL0CFG		( (uint32_t *) 0x400FC084UL)
//0x400FC088UL: Registro de estado del PLL0:
#define		DIR_PLL0STAT	( (uint32_t *) 0x400FC088UL)
//0x400FC08CUL: Registro de control del PLL0:
#define		DIR_PLL0FEED	( (uint32_t *) 0x400FC08CUL)
//0x400FC0A0UL: Registro de control del PLL1:
#define		DIR_PLL1CON		( (uint32_t *) 0x400FC0A0UL)
//0x400FC0A4UL: Registro de configuracion del PLL1:
#define		DIR_PLL1CFG		( (uint32_t *) 0x400FC0A4UL)
//0x400FC0A8UL: Registro de estado del PLL1:
#define		DIR_PLL1STAT	( (uint32_t *) 0x400FC0A8UL)
//0x400FC0ACUL: Registro de control del PLL1:
#define		DIR_PLL1FEED	( (uint32_t *) 0x400FC0ACUL)

//Registro de status y configuracion del sistema:
#define		SCS			DIR_SCS[0]
#define 	FLASHCFG	DIR_FLASHCFG[0]

//Registros de control del CLOCK:
#define		CCLKCFG		DIR_CCLKCFG[0]
#define		CLKSRCSEL	DIR_CLKSRCSEL[0]
#define		CLKOUTCFG	DIR_CLKOUTCFG[0]


/***********************************************************************************************************************************
 *** MACROS GLOBALES
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** TIPO DE DATOS GLOBALES
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** VARIABLES GLOBALES
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** PROTOTIPOS DE FUNCIONES GLOBALES
 **********************************************************************************************************************************/
void ADC_Init (void);



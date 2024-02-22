/*******************************************************************************************************************************//**
 *
 * @file        DR_adc.c
 * @brief       Descripcion del modulo
 * @date        5 de jul. de 2016
 * @author      Ing. Marcelo Trujillo
 *
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** INCLUDES
 **********************************************************************************************************************************/
#include "DR_Adc.h"
#include "DR_EINT.h"
#include "DR_PLL.h"
#include "DR_gpio.h"


/***********************************************************************************************************************************
 *** DEFINES PRIVADOS AL MODULO
 **********************************************************************************************************************************/
//puerto y pin de los canales
#define AD0_0	0,23
#define AD0_1	0,24
#define AD0_2	0,25
#define AD0_3	0,26
#define AD0_4	1,30
#define AD0_5	1,31
#define AD0_6	0,3
#define AD0_7	0,2


#define     ADC                 ( ( __RW unsigned int  * ) 0x40034000UL )

#define     AD0CR               ADC[0]
#define     AD0GDR              ADC[1]
#define     AD0INTEN            ADC[3]

#define         ADINTEN         8
#define         ADINTEN0        0
#define         ADINTEN1        1
#define         ADINTEN2        2
#define         ADINTEN3        3
#define         ADINTEN4        4
#define         ADINTEN5        5
#define         ADINTEN6        6
#define         ADINTEN7        7

#define     AD0DR0              ADC[4]
#define     AD0DR1              ADC[5]
#define     AD0DR2              ADC[6]
#define     AD0DR3              ADC[7]
#define     AD0DR4              ADC[8]
#define     AD0DR5              ADC[9]
#define     AD0DR6              ADC[10]
#define     AD0DR7              ADC[11]
#define     AD0STAT             ADC[12]
#define     AD0TRM              ADC[13]

#define     AD0CR_SEL( x )      ( ADC[0] |= (1 << x ) )
#define     AD0CR_CLKDIV ( x )  ( ADC[0] |= (x << 8 ) )

#define     CHN0                0
#define     CHN1                1
#define     CHN2                2
#define     CHN3                3
#define     CHN4                4
#define     CHN5                5
#define     CHN6                6
#define     CHN7                7
#define     BURST               16
#define     PDN                 21

#define     AD0DR_RESULT( x )       ( ( ADC[ 4 + x ] >> 4) & 0xfff )
#define     AD0DR_OVERRUN( x )      ( ( ADC[ 4 + x ] >> 30 ) & 1 )
#define     AD0DR_DONE( x )         ( ( ADC[ 4 + x ] >> 31 ) & 1 )


/***********************************************************************************************************************************
 *** MACROS PRIVADAS AL MODULO
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** TIPOS DE DATOS PRIVADOS AL MODULO
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** TABLAS PRIVADAS AL MODULO
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** VARIABLES GLOBALES PUBLICAS
 **********************************************************************************************************************************/
uint32_t    Vlr_Mdd;

/***********************************************************************************************************************************
 *** VARIABLES GLOBALES PRIVADAS AL MODULO
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** PROTOTIPO DE FUNCIONES PRIVADAS AL MODULO
 **********************************************************************************************************************************/

 /***********************************************************************************************************************************
 *** FUNCIONES PRIVADAS AL MODULO
 **********************************************************************************************************************************/

 /***********************************************************************************************************************************
 *** FUNCIONES GLOBALES AL MODULO
 **********************************************************************************************************************************/
/**
    \fn  void ADC_IRQHandler(void)
    \brief Interrupcion del adc
    \author Ing. Marcelo Trujillo
    \date 5 de jul. de 2016
    \param void
    \return void
*/
void ADC_IRQHandler(void)
{
    static uint32_t Ultima_conver=0xfff;
	//Vlr_Mdd = 0xfff & (AD0DR5 >> 4 );//carga en el buffer global la ultima medicion del channel 5 del adc
    Ultima_conver=AD0DR5;
    Ultima_conver ++;
    Ultima_conver --;
    Vlr_Mdd = 0xfff & (AD0DR5 >> 4 );

	AD0CR |=  ( 1 << 24 );//que vuelva a convertir una medicion
}

/**
    \fn  void ADC_Init (void)
    \brief Inicializacion del adc
    \author Ing. Marcelo Trujillo
    \date 5 de jul. de 2016
    \param void
    \return void
*/


void ADC_Init (void)
{
	//!<configuro los canales de ADC que voy a utilizar como tales

	//!<hay que poner las otras salidas de adc como gpio salida pulldown para disminuir el ruido
	SetPINSEL(AD0_0,0);//las pongo como gpio
	SetPINSEL(AD0_1,0);
	SetPINSEL(AD0_2,0);

	SetMODE (AD0_0,3);//las pongo en modo pulldown
	SetMODE (AD0_1,3);
	SetMODE (AD0_2,3);

	SetDIR (AD0_0,1);//configuro como salida
	SetDIR (AD0_0,1);//configuro como salida
	SetDIR (AD0_0,1);//configuro como salida


	//SetPINSEL(AD0_0,1);
	//SetPINSEL(AD0_1,1);//CH 1
	//SetPINSEL(AD0_2,1);//CH 2
	//SetPINSEL(AD0_3,1);
	//SetPINSEL(AD0_4,4);
	SetPINSEL(AD0_5,4);//CH 5
	//SetPINSEL(AD0_6,3);
	//SetPINSEL(AD0_7,3);






	//!< ADC
	PCONP |= 1 << PCADC ;           // Activo la alimentacion del dispositivo desde el registro PCONP pag 63:
	PCLKSEL0 &= ~( 0x03 << 24 );    // Selecciono el clock del ADC como 25MHz: Pag 57 CLK/4 (100Mhz/4)
	//PCLKSEL0 |= 0x03 << 24 ;  // Selecciono el clock del ADC como 25MHz: Pag 57 CLK/4 (100Mhz/4)
	AD0CR |= 0x000fe00;             // Y el divisor como 1, para muestrear a <= 200kHz: Pag 577 CLKDIV bits 8 a 15---> [25Mhz/65(CLKDIV+1)]
	//AD0CR |= ( 1 << CHN5 ) | ( 1 << BURST ) | ( 1 << PDN );
	AD0CR  &= ~(7 << 24 );//resetea el ADC
	AD0CR |= ( 1 << CHN5 ) | ( 1 << PDN ) | ( 1 << 24 );//bit 5 bit 21 y bit 24 pone un 1

    //bit 5 habilita el CHN5 para ser sampleado
    //bit 21 pone en modo operacional el conversor ad
    //bit 24 empieza la conversion

	AD0INTEN |= ( 1 << ADINTEN5 ) | ( 1 << ADINTEN );//habilita la interrupcion dentro del adc en channel 5 y como no es modo burst va un 1 en el bit 8
	ISE_ADC ;


}


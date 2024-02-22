/*******************************************************************************************************************************//**
 *
 * @file		DR_SysTick.c
 * @brief		Descripcion del modulo
 * @date		4 de may. de 2016
 * @author		Ing. Marcelo Trujillo
 *
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** INCLUDES
 **********************************************************************************************************************************/
#include "DR_SysTick.h"


/***********************************************************************************************************************************
 *** DEFINES PRIVADOS AL MODULO
 **********************************************************************************************************************************/


/***********************************************************************************************************************************
 *** MACROS PRIVADAS AL MODULO
 **********************************************************************************************************************************/


uint8_t vector_flag[CANT_AUTOS]={0,0,0,0,0,0,0,0};
uint16_t vector_estadia[CANT_AUTOS]={0,0,0,0,0,0,0,0};

extern uint16_t volatile contadorseg;

extern uint16_t volatile contadormin[CANT_AUTOS];
extern uint16_t volatile contadorhs[CANT_AUTOS];
extern uint16_t volatile contadordias[CANT_AUTOS];

/***********************************************************************************************************************************
 *** TIPOS DE DATOS PRIVADOS AL MODULO
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** TABLAS PRIVADAS AL MODULO
 **********************************************************************************************************************************/


/***********************************************************************************************************************************
 *** VARIABLES GLOBALES PUBLICAS
 **********************************************************************************************************************************/
extern uint8_t FlagFreq[2];
extern volatile int DemoraLCD;
extern volatile int DemoraCartel;
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
/** @fn void SysTickInic ( void )
 * @details Inicializacion del systick
 * @details Portable Cortex
 * @param 	void
 * @return 	void.
 */
void SysTickInit ( void )
{
	STRELOAD = ( STCALIB / 4) - 1; //Si el micro esta andando a 100Mhz
									//cargo STCALIB en STRELOAD, interrupcion cada 10ms
									//STCALIB/4 interrupcion cada 10/4ms=2,5 ms
	//STRELOAD = ( STCALIB ) - 1;//cada 10ms
	STCURR = 0;//Reseteo el numero actual a cero y el flag en STCRL?
	CLKSOURCE = 1;//pongo 1 utilizo PCLK como fuente de pulsos, 0 para fuente externa
	ENABLE = 1;//habilito el comienzo del conteo
	TICKINT = 1;//habilito la interrupcion dentro del systick
}

/** @fn void SysTick_Handler( void )
 * @details Interrupcion del Systick
 * @details Portable Cortex
 * @param 	void
 * @return 	void.
 */



void SysTick_Handler( void )
{
	static uint8_t a;
	a++;

	debounce();//!< Debounce teclas placa base
	BarridoDisplay();//!<Barrido Display 7 segmentos expansion 2
	//debounce_EntradaDigital();//!<Debounce entradas externas digitales
	//BarridoDisplay_Expansion3();//!<Driver Display 7 segmentos expansion 3
	//DriverTeclado_Expansion3();//!<Driver teclado matricial expansion 3

	PopServo ();//!< cambia el periodo correspondiente a cada match

	if ( DemoraLCD )//para DR lcd
	{
		DemoraLCD--;
	}
	if(DemoraCartel)//para PR lcd
	{
		DemoraCartel--;
	}
	if ( contadorseg )//para estadia
	{
		contadorseg --;
	}
	a = STCTRL;//Reseteo el flag del systick leyendolo
}


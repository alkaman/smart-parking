/*******************************************************************************************************************************//**
 *
 * @file		PR_Timer.c
 * @brief		Descripcion del modulo
 * @date		7 de may. de 2016
 * @author		Ing. Marcelo Trujillo
 *
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** INCLUDES
 **********************************************************************************************************************************/
#include "PR_Timer.h"
#include  <stdio.h>

/***********************************************************************************************************************************
 *** DEFINES PRIVADOS AL MODULO
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** MACROS PRIVADAS AL MODULO
 **********************************************************************************************************************************/
#define		MINUTOS			60
#define		SEGUNDOS		10
#define		DECIMAS			100

/***********************************************************************************************************************************
 *** TIPOS DE DATOS PRIVADOS AL MODULO
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** TABLAS PRIVADAS AL MODULO
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** VARIABLES GLOBALES PUBLICAS
 **********************************************************************************************************************************/
uint16_t volatile contadorseg=SEGUNDOS_ESTADIA;


uint16_t volatile contadormin[CANT_AUTOS]={0};
uint16_t volatile contadorhs[CANT_AUTOS]={0};
uint16_t volatile contadordias[CANT_AUTOS]={0};

extern uint16_t volatile vector_estadia[CANT_AUTOS];
extern uint8_t vector_flag[CANT_AUTOS];
/***********************************************************************************************************************************
 *** VARIABLES GLOBALES PRIVADAS AL MODULO
 **********************************************************************************************************************************/
static volatile uint32_t TmrRun[ N_TIMERS ];
static volatile uint8_t TmrEvents[ N_TIMERS ];
static volatile uint8_t TmrStandBy[ N_TIMERS ];
static void ( *TmrHandlers[ N_TIMERS ] )( void );
static uint8_t TmrBase[ N_TIMERS ];

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
	\fn void TimerStart(uint8_t event, timer_t t,  uint8_t , void (*handler)(void) )
	\brief Inicia un timer
 	\details Inicia el timer \a e al transcurrir el tiempo especificado por \a t se llama a la funcion apuntada por \a handler
 	\param [in] event Numero de evento entre 0 y 31
 	\param [in] t Tiempo del evento. Dependiente de la base de tiempos
 	\param [in] base de tiempo ( DEC, SEG, MIN )
 	\param [in] handler Callback del evento
	\return void
*/
void TimerStart( uint8_t event , uint32_t time , uint8_t base , TmrHandler handler )
{
	switch ( base )
	{
		case DEC:
			time *= DECIMAS;
			break;
		case SEG:
			time *= ( SEGUNDOS * DECIMAS );
			break;
		case MIN:
			time *= ( MINUTOS * SEGUNDOS * DECIMAS );
			break;
	}

	TmrBase[ event ] = base;

	if( time != 0 )	//el tiempo no es 0, lo cargo
	{
		TmrRun[ event ] = time;
		TmrEvents[ event ] = 0;
	}
	else	//el tiempo es cero, el timer vence automáticamente
	{
		TmrRun[ event ] = 0;
		TmrEvents[ event ] = 1;
	}
	TmrHandlers[ event ] = handler;
}

/**
	\fn void TimerSet( uint8_t event , timer_t t )
	\brief Inicia un timer
 	\details Reinicia el timer con el valor t (no lo resetea)
 	\param [in] event Numero de evento entre 0 y 31
 	\param [in] t Tiempo del evento. Dependiente de la base de tiempos
 	\return void
*/
void TimerSet( uint8_t event , uint32_t time )
{
	switch ( TmrBase[ event ] )
	{
		case DEC:
			time *= DECIMAS;
			break;
		case SEG:
			time *= ( SEGUNDOS * DECIMAS );
			break;
		case MIN:
			time *= ( MINUTOS * SEGUNDOS * DECIMAS );
			break;
	}
	TmrRun[ event ] = time;
}

/**
	\fn  TimerGet( uint8_t event )
	\brief Toma el valor al vuelo del timer en cuestion
 	\details Lee el timer
 	\param [in] event Numero de evento entre 0 y 31
 	\return valor del timer
*/
uint32_t TimerGet( uint8_t event )
{
	uint32_t time = TmrRun[ event ];

	switch ( TmrBase[ event ] )
	{
		case DEC:
			time /= DECIMAS;
			break;
		case SEG:
			time /= ( SEGUNDOS * DECIMAS );
			break;
		case MIN:
			time /= ( MINUTOS * SEGUNDOS * DECIMAS );
			break;
	}
	return time;
}

/**
	\fn  void TimerStandBy( uint8_t event , uint8_t accion)
	\brief Detiene/Arranca el timer, NO lo resetea
 	\details lo pone o lo saca de stand by
 	\param [in] event Numero de evento entre 0 y 31
 	\param [in] accion RUN lo arranca, STOP lo pone en stand by
 	\return valor del timer
*/
void TimerStandBy( uint8_t event , uint8_t accion )
{
	TmrStandBy[ event ] = accion;
}

/**
	\fn void Timer Stop(uint8_t e)
	\brief Detiene un timer
 	\details Detiene el timer event
 	\param [in] e Numero de evento entre 0 y 31
	\return void
*/
void TimerStop( uint8_t event )
{
	TmrRun[ event ] = 0;
	TmrEvents[ event ] = 0;
	TmrHandlers[ event ] = NULL;
	TmrBase[ event ] = 0;
	TmrStandBy[ event ] = RUN;
}

/**
	\fn void TimerClose( void )
	\brief Detiene todos los timers
 	\details Detiene todos los timers
	\return void
*/
void TimerClose(void)
{
	uint32_t i;

	for( i = 0 ; i < N_TIMERS ; i++ )
		TimerStop( i );
}

/**
	\fn void TimerCheck( void )
	\brief Decremento periodico de los contadores
 	\details Decrementa los contadores de los timers en ejecucion. Debe ser llamada periodicamente con la base de tiempos
	\return void
*/
void TimerCheck( void )
{
	uint32_t i;

	for( i = 0 ; i < N_TIMERS ; i++ )
	{
		if(TmrRun[i])
		{
			if ( !TmrStandBy[ i ] )
			{
				TmrRun[ i ]--;
				if(!TmrRun[ i ])
					TmrEvents[ i ] = 1;
			}
		}
	}
}

/**
	\fn void TimerEvent(void)
	\brief Chequeo de timers vencidos
 	\details Llama a los callbacks de los timers vencidos. Debe llamarse desde el lazo principal del programa
	\return void
*/
void TimerEvent( void )
{
	uint8_t i;

	for( i = 0 ; i < N_TIMERS ; i++ )
	{
		if( TmrEvents[ i ] )
		{
			TmrHandlers[ i ]( );
			TmrEvents[ i ] = 0;
		}
	}
}

/**
	\fn void EstadiaCheck(void)
	\brief Primitiva que lee el buffer contadorseg e incrementa vector estadia,contadormin,
	 	   contadorhs,contadordias si el codigo correspondiente esta ocupado
	\return void
*/

void EstadiaCheck(void)   //Cuenta si el codigo esta ocupado
{
	int i;
	if(!contadorseg)
	{
		contadorseg=SEGUNDOS_ESTADIA;
		for(i=0;i<CANT_AUTOS;i++)
		{
			if(vector_flag[i]==1)
			{
				if(vector_estadia[i]<60)
				{
					vector_estadia[i]++;
				}

				if(vector_estadia[i]==60)
				{
					contadormin[i]++;
					vector_estadia[i]=0;
				}


				if(contadormin[i]==60)
				{
					contadorhs[i]++;
					contadormin[i]=0;
				}

				if(contadorhs[i]==24)
				{
					contadordias[i]++;
					contadorhs[i]=0;
				}
			}
		}
	}
}

/**
	\fn SetEstadia(uint8_t codigo, uint16_t d, uint16_t h, uint16_t m, uint16_t s)
	\brief Primitiva que le da un valor de día,hora,minuto y segundos al codigo correspondiente
	\param uint8_t: codigo al cual se le quiere cambiar el tiempo de estadia
		   uint16_t d: cantidad de días de estadia a setear
		   uint16_t h: cantidad de horas de estadia a setear
		   uint16_t m: cantidad de minutos de estadia a setear
		   uint16_t s: cantidad de segundos	 de estadia a setear
	\return void
*/

void SetEstadia(uint8_t codigo, uint16_t d, uint16_t h, uint16_t m, uint16_t s)
{
	contadordias[codigo]=d;
	contadorhs[codigo]=h;
	contadormin [codigo]=m;
	vector_estadia[codigo]=s;

}

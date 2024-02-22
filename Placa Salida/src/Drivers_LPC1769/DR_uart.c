/*******************************************************************************************************************************//**
 *
 * @file		DR_uart.c
 * @brief		Descripcion del modulo
 * @date		31 de ago. de 2016
 * @author		Ing. Marcelo Trujillo
 *
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** INCLUDES
 **********************************************************************************************************************************/
#include "DR_uart.h"


/***********************************************************************************************************************************
 *** DEFINES PRIVADOS AL MODULO
 **********************************************************************************************************************************/
#define 	MAX_TX		100
#define 	MAX_RX		100
#define		FUNCION_1	01

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
volatile uint8_t bufferTX[MAX_TX];
volatile uint8_t bufferRX[MAX_RX];
volatile uint8_t inx_TX_out=0;
volatile uint8_t inx_TX_in=0;
volatile uint8_t inx_RX_out=0;
volatile uint8_t inx_RX_in=0;
volatile uint8_t fEnviando=0;

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
extern uint8_t vector_flag[CANT_AUTOS];

/**
	\fn  void UART0_IRQHandler (void)
	\brief Interrupcion de UART0
 	\author Ing. Marcelo Trujillo
 	\date 31 de ago. de 2016
 	\param void
	\return void
*/
void UART0_IRQHandler (void)
{
	uint8_t iir;
	int16_t aux;
	do
	{
		//IIR es reset por HW, una vez que lo lei se resetea.
		iir = U0IIR;

		if ( iir & 0x04 ) 							//Data ready
		{
			//Display_lcd ("LLEGO msj -UART0", 0 , 0);
			aux = U0RBR;
			Push_RX ( aux );   	//guardo en buffer e incremento índice
									//garantizo el buffer circular

		}

		if ( iir & 0x02 ) //THRE
		{
			aux=Pop_TX();
			if(aux!=-1)
			{
				U0THR=aux;
			}
			if(aux==-1)
			{
				fEnviando=0;
			}
		}
	}
	while( ! ( iir & 0x01 ) ); /* me fijo si cuando entre a la ISR habia otra
						     	int. pendiente de atencion: b0=1 (ocurre unicamente si dentro del mismo
								espacio temporal lleguan dos interrupciones a la vez) */
}

/**
	\fn  void UART0_IRQHandler (void)
	\brief Interrupcion de UART0
 	\author Ing. Marcelo Trujillo
 	\date 31 de ago. de 2016
 	\param void
	\return void
*/
void UART0_Inicializacion (void)
{
	//1.- Registro PCONP (0x400FC0C4) - bit 3 en 1 prende la UART:
	PCONP |= 0x01<<3;
	//2.- Registro PCLKSEL0 (0x400FC1A8) - bits 6 y 7 en 0 seleccionan que el clk de la UART0 sea CCLK/4:
	PCLKSEL0 &= ~(0x03<<6);	//con un CCLOK=100Mhz, nos queda PCLOCK=25Mhz
	//3.- Registro U1LCR (0x4001000C) - transmision de 8 bits, 1 bit de stop, sin paridad, sin break cond, DLAB = 1:
	U0LCR = 0x00000083;
	//4.- Registros U1DLL (0x40010000) y U1DLM (0x40010004) - 9600 baudios:
	U0DLM = 0;
	U0DLL = 0xA3;//0xA3 para 9600
	//5.- Registros PINSEL0 (0x4002C000) y PINSEL1 (0x4002C004) - habilitan las funciones especiales de los pines:
	//TX1D : PIN ??	-> 		P0[2]	-> PINSEL0: 04:05
	SetPINSEL( TX0 , FUNCION_1 );
	//RX1D : PIN ??	-> 		P0[3]	-> PINSEL1: 06:07
	SetPINSEL( RX0 , FUNCION_1 );
	//6.- Registro U1LCR, pongo DLAB en 0:
	U0LCR = 0x03;
	//7. Habilito las interrupciones (En la UART -IER- y en el NVIC -ISER)
	U0IER = 0x03;
	ISER0 |= (1<<5);
}

/**
	\fn void Push_RX ( uint8_t dato)
	\brief Carga en el buffer de recepcion de la UART
 	\param uint8_t dato
	\return void
	\author Alan Kinast, Marcos Trautman
 	\date 2016.11.25
*/

void Push_RX ( uint8_t dato)
{
	bufferRX[inx_RX_in] = dato;
	inx_RX_in++;
	inx_RX_in %= MAX_RX;

}

/**
	\fn int16_t Pop_RX ( void )
	\brief Lee el buffer de recepcion de la UART y lo devuelve
 	\param void
	\return int16_t
			-1	en caso de que no haya nada que leer
			>=0	en caso de que haya un dato
	\author Alan Kinast, Marcos Trautman
 	\date 2016.11.25
*/

int16_t Pop_RX ( void )
{
	uint8_t aux;
	//int16_t aux;

	if (inx_RX_in == inx_RX_out)
		return -1;

	aux = bufferRX[inx_RX_out];
	inx_RX_out++;
	inx_RX_out %= MAX_RX;

	return ( int16_t ) aux;
	//return aux;

}

/**
	\fn Push_TX ( uint8_t dato)
	\brief Carga en el buffer de envio de la UART0, para su posterior envio.
		   En el caso de que sea el primer dato lo fuerza cargandolo directo al registro.
 	\param uint8_t dato
 		   Dato a enviar
	\return void
	\author Alan Kinast, Marcos Trautman
 	\date 2016.11.25
*/

void Push_TX ( uint8_t dato)
{

	if(fEnviando==0)//if(inx_TX_in==inx_TX_out)
	{
		fEnviando = 1;
		U0THR=dato;
	}
	else
	{
		bufferTX[inx_TX_in] = dato;
		inx_TX_in++;
		inx_TX_in %= MAX_RX;
	}
}

/**
	\fn int16_t Pop_TX ( void )
	\brief Lee el buffer de envio de la UART0 y lo devuelve como uint16_t
 	\param void
	\return int16_t
			-1 si no hay nada que enviar
			>=0 si hay un dato a enviar
	\author Alan Kinast, Marcos Trautman
 	\date 2016.11.25
*/

int16_t Pop_TX ( void )
{
	int16_t aux;

	if (inx_TX_out == inx_TX_in)
		return -1;

	aux = bufferTX[inx_TX_out];
	inx_TX_out++;
	inx_TX_out %= MAX_TX;

	return aux;

}

/**
	\fn void transmitir (char * S)
	\brief Envia un string por puerto serie
 	\param char * S
 		   String a enviar
	\return void
	\author Alan Kinast, Marcos Trautman
 	\date 2016.11.25
*/

void transmitir (char * S)
{
	while(*S)
	{
		Push_TX(*S);
		S++;
	}
}

/**
	\fn void Desentramado_Entrada (void)
	\brief Analiza lo recibido por puerto serie de la barrera de Entrada y toma decisiones respecto
	 	   a lo recibido.
 	\param void
	\return void
	\author Alan Kinast, Marcos Trautman
 	\date 2016.11.25
*/

void Desentramado_Entrada (void)
{
	static int16_t aux=-1;
	static char caracter='0';
	static uint8_t flagS=0,flagE=0;
	int codigo=0;
	aux=Pop_RX();
	if(aux!=-1)
	{
		//itoa((int)aux,& caracter,10);
		caracter=(char)aux;
		if(caracter == 'S')
		{
			flagS=1;
		}
		if((caracter>='0')&&(caracter<='9')&&(flagS==1))
		{
			codigo=atoi(&caracter);
			timerOFF(codigo);
			flagS=0;
		}
		if(caracter != 'S')
		{
			flagS=0;
		}
		if(caracter == 'E')
		{
			flagE=1;
		}
		if((caracter>='0')&&(caracter<='9')&&(flagE==1))
		{
			codigo=atoi(&caracter);
			if(codigo<=CANT_AUTOS)
			vector_flag[codigo]=1;//agregar primitiva que toque el buffer
			flagE=0;
		}
		if(caracter != 'E')
		{
			flagE=0;
		}
	}
}

/**
	\fn void Desentramado_Entrada_2 (void)
	\brief Analiza lo recibido por puerto serie de la barrera de Entrada y toma decisiones respecto
	 	   a lo recibido.
 	\param void
	\return void
	\author Alan Kinast, Marcos Trautman
 	\date 2016.11.25
*/

void Desentramado_Entrada_2 (void)
{
	static uint8_t estado,estado_hora,estado_fecha;
	static int16_t aux=-1;
	char caracter;
	int codigo=0;
	aux=Pop_RX();
	if(aux!=-1)
	{
		caracter=(char)aux;
		switch(estado)
		{
			case estado0:
				if(aux=='E')
				{
					estado=estado1;
				}
				if(aux=='S')
				{
					estado=estado2;
				}
				if(aux=='H')
				{
					estado=estado3;
				}
				if(aux=='F')
				{
					estado=estado4;
				}
				if(aux=='I')
				{
					estado=estado5;
				}
				if(aux=='L')
				{
					estado=estado6;
				}
				if(aux=='B')
				{
					estado=estado7;
				}
				break;
			case estado1:
				if((caracter>='0')&&(caracter<='9'))//!< Proteccion para que sea un caracter del 0 al 9
				{
					codigo=atoi(&caracter);
					timerON(codigo);
				}
				estado=estado0;
				break;
			case estado2:
				if((caracter>='0')&&(caracter<='9'))//!< Proteccion para que sea un caracter del 0 al 9
				{
					codigo=atoi(&caracter);
					timerOFF(codigo);
				}
				estado=estado0;
				break;
			case estado3:
				estado_hora=Maquina_SetHora(caracter);
				if(estado_hora==1)//!< Seteo la hora de forma correcta
				{
					ShowHoraFecha();//!<Actualizo la hora en el display
					estado=estado0;
				}
				if(estado_hora==2)//! Sali por error en trama
				{
					estado=estado0;
				}
				break;
			case estado4:
				estado_fecha=Maquina_SetFecha(caracter);
				if(estado_fecha==1)//!< Seteo la hora de forma correcta
				{
					ShowHoraFecha();//!<Actualizo la Fecha en el display
					estado=estado0;
				}
				if(estado_fecha==2)//! Sali por error en trama
				{
					estado=estado0;
				}
				break;
			case estado5:
				if((caracter>='0')&&(caracter<='9'))//!< Proteccion para que sea un caracter del 0 al 9
				{
					codigo=atoi(&caracter);
					Inhabilitar(codigo);
				}
				estado=estado0;
				break;
			case estado6:
				if(caracter=='L')//!< Si recibo la segunda L, le respondo a la Aplicación
				{
					transmitir("JJ");
					estado=estado0;
				}
				estado=estado0;
				break;
			case estado7:
				if(caracter=='B')//!< Si recibo la segunda L, le respondo a la Aplicación
				{
					transmitir("OK");
					estado=estado0;
				}
				estado=estado0;
				break;
			default:
				estado=estado0;
				break;
		}
	}
}

/**
	\fn void Desentramado_Salida (void)
	\brief Analiza lo recibido por puerto serie de la barrera de Salida y toma decisiones respecto
	 	   a lo recibido.
 	\param void
	\return void
	\author Alan Kinast, Marcos Trautman
 	\date 2016.11.25
*/

void Desentramado_Salida (void)
{
	static int16_t aux=-1;
	static char caracter='0';
	static uint8_t flagE=0,flagS=0;
	int codigo=0;
	aux=Pop_RX();
	if(aux!=-1)
	{
		caracter=(char)aux;
		if(caracter == 'E')
		{
			flagE=1;
		}
		if((caracter>='0')&&(caracter<='9')&&(flagE==1))
		{
			codigo=atoi(&caracter);
			if(codigo<=CANT_AUTOS)
				vector_flag[codigo]=1;//agregar primitiva que toque el buffer
			flagE=0;
		}
		if(caracter != 'E')
		{
			flagE=0;
		}
		if(caracter == 'S')
		{
			flagS=1;
		}
		if((caracter>='0')&&(caracter<='9')&&(flagS==1))
		{
			codigo=atoi(&caracter);
			timerOFF(codigo);
			flagS=0;
		}
		if(caracter != 'S')
		{
			flagS=0;
		}
	}
}

/**
	\fn void void Desentramado_Salida_2 (void)
	\brief Analiza lo recibido por puerto serie de la barrera de Salida y toma decisiones respecto
	 	   a lo recibido.
	 	   estado0
 	\param void
	\return void
	\author Alan Kinast, Marcos Trautman
 	\date 2016.11.25
*/

void Desentramado_Salida_2 (void)
{
	static uint8_t estado,estado_hora,estado_fecha;
	static int16_t aux=-1;
	char caracter;
	int codigo=0,i;
	aux=Pop_RX();
	if(aux!=-1)
	{
		caracter=(char)aux;
		switch(estado)
		{
			case estado0:
				if(aux=='E')
				{
					estado=estado1;
				}
				if(aux=='S')
				{
					estado=estado2;
				}
				if(aux=='H')
				{
					estado=estado3;
				}
				if(aux=='F')
				{
					estado=estado4;
				}
				if(aux=='I')
				{
					estado=estado5;
				}
				if(aux=='L')
				{
					estado=estado6;
				}
				if(aux=='B')
				{
					estado=estado7;
				}
				break;
			case estado1:
				if((caracter>='0')&&(caracter<='9'))//!< Proteccion para que sea un caracter del 0 al 9
				{
					codigo=atoi(&caracter);
					timerON(codigo);
				}
				estado=estado0;
				break;
			case estado2:
				if((caracter>='0')&&(caracter<='9'))//!< Proteccion para que sea un caracter del 0 al 9
				{
					codigo=atoi(&caracter);
					timerOFF(codigo);
				}
				estado=estado0;
				break;
			case estado3:
				estado_hora=Maquina_SetHora(caracter);
				if(estado_hora==1)//!< Seteo la hora de forma correcta
				{
					ShowHoraFecha();//!<Actualizo la hora en el display
					estado=estado0;
				}
				if(estado_hora==2)//! Sali por error en trama
				{
					estado=estado0;
				}
				break;
			case estado4:
				estado_fecha=Maquina_SetFecha(caracter);
				if(estado_fecha==1)//!< Seteo la hora de forma correcta
				{
					ShowHoraFecha();//!<Actualizo la Fecha en el display
					estado=estado0;
				}
				if(estado_fecha==2)//! Sali por error en trama
				{
					estado=estado0;
				}
				break;
			case estado5:
				if((caracter>='0')&&(caracter<='9'))//!< Proteccion para que sea un caracter del 0 al 9
				{
					codigo=atoi(&caracter);
					Inhabilitar(codigo);
				}
				estado=estado0;
				break;
			case estado6:
				if(caracter=='L')//!< Si recibo la segunda L, le respondo a la Aplicación
				{
					transmitir("NN");
					for(i=0;i<8;i++)//!< Reseteo los timer por las inhabilitaciones
						timerOFF(i);
					estado=estado0;
				}
				estado=estado0;
				break;
			case estado7:
				if(caracter=='B')//!< Si recibo la segunda L, le respondo a la Aplicación
				{
					transmitir("OK");
					estado=estado0;
				}
				estado=estado0;
				break;
			default:
				estado=estado0;
				break;
		}
	}
}


/*******************************************************************************************************************************//**
 	\file DR_Teclado_Expansion3.c
 	\brief Drivers Teclado expansion 3 e inicializacion expansion 3
 	\details Trabajo Practico Obligatorio
 	\author Marcos Trautman, Alan Kinast
 	\date 2016.11.25
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** INCLUDES
 **********************************************************************************************************************************/
#include "DR_Teclado_Expansion3.h"

/***********************************************************************************************************************************
 *** DEFINES PRIVADOS AL MODULO
 **********************************************************************************************************************************/

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
volatile unsigned char key_Expansion3=NO_KEY;	//!< Buffer de teclado

volatile unsigned char BufferEntradas;				//!< Buffer de Entradas Digitales
/***********************************************************************************************************************************
 *** VARIABLES GLOBLES PRIVADAS AL MODULO
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
	\fn void DriverTeclado_Expansion3(void)
	\brief Driver de teclado matricial expansion 3
 	\param void
	\return void
	\author Alan Kinast, Marcos Trautman
 	\date 2016.11.25
*/
void DriverTeclado_Expansion3(void)
{
	unsigned char CodigoActual ;

	CodigoActual = DriverTecladoHW_Expansion3( );
	DriverTecladoSW_Expansion3( CodigoActual );
}

/**
	\fn  void DriverTecladoSW_Expansion3 ( unsigned char CodigoActual )
	\brief filtrado del rebote de tecla del teclado matricial expansion 3
 	\param [in] c codigo de tecla a analizar
	\return void
	\author Alan Kinast, Marcos Trautman
 	\date 2016.11.25
*/
void DriverTecladoSW_Expansion3 ( unsigned char CodigoActual )
{
	static unsigned char CodigoAnterior = NO_KEY;
	static unsigned char EstadosEstables;

	if( CodigoActual == NO_KEY )
	{
		CodigoAnterior = NO_KEY;
		EstadosEstables = 0;
		return;
	}

	if( EstadosEstables == 0  )
	{
		CodigoAnterior = CodigoActual;
		EstadosEstables = 1;
		return;
	}

	if( CodigoActual != CodigoAnterior )
	{
		CodigoAnterior = NO_KEY;
		EstadosEstables = 0;
		return;
	}

	if( EstadosEstables == REBOTES )
	{
		key_Expansion3 = CodigoActual;
		EstadosEstables++;

		return;
	}

	if( EstadosEstables == REBOTES + 1)
		return;

	EstadosEstables ++;

	return;
}

/**
	\fn unsigned char DriverTecladoHW_Expansion3( void )
	\brief lectura de los microswitch del teclado
 	\param void
	\return el codigo de tecla leido
	\author Alan Kinast, Marcos Trautman
 	\date 2016.11.25
*/
unsigned char DriverTecladoHW_Expansion3( void )
{
	unsigned char Codigo = NO_KEY;

	SetPIN(EX3_columna0 , OFF);
	SetPIN(EX3_columna1 , ON);
	SetPIN(EX3_columna1 , ON);
	SetPIN(EX3_columna1 , ON);
	SetPIN(EX3_columna1 , ON);
	SetPIN(EX3_columna1 , ON);
	SetPIN(EX3_columna1 , ON);
	SetPIN(EX3_columna1 , ON);
	SetPIN(EX3_columna1 , ON);
	SetPIN(EX3_columna1 , ON);
	SetPIN(EX3_columna1 , ON);

	if(!GetPIN ( EX3_fila0 , ALTO))//if ( !EX3_fila0 )
		return 3 ;

	if(!GetPIN ( EX3_fila1 , ALTO))//if ( !EX3_fila1 )
		return 0 ;

	if(!GetPIN ( EX3_fila2 , ALTO))//if ( !EX3_fila2 )
		return 2 ;

	if(!GetPIN ( EX3_fila3 , ALTO))//if ( !EX3_fila3 )
		return 1 ;

	SetPIN(EX3_columna0 , ON);
	SetPIN(EX3_columna1 , OFF);
	SetPIN(EX3_columna1 , OFF);
	SetPIN(EX3_columna1 , OFF);
	SetPIN(EX3_columna1 , OFF);
	SetPIN(EX3_columna1 , OFF);
	SetPIN(EX3_columna1 , OFF);
	SetPIN(EX3_columna1 , OFF);
	SetPIN(EX3_columna1 , OFF);
	SetPIN(EX3_columna1 , OFF);
	SetPIN(EX3_columna1 , OFF);


	if(!GetPIN ( EX3_fila0 , ALTO))//if ( !EX3_fila0 )
		return 4 ;

	if(!GetPIN ( EX3_fila1 , ALTO))//if ( !EX3_fila1 )
		return 7 ;

	if(!GetPIN ( EX3_fila2 , ALTO))//if ( !EX3_fila2 )
		return 5 ;

	if(!GetPIN ( EX3_fila3 , ALTO))//if ( !EX3_fila3 )
		return 6 ;

	return Codigo ;
}

/**
	\fn void Inic_Expansion2( void )
	\brief Inicializacion de la Expansion 2
 	\param void
	\return void
	\author Alan Kinast, Marcos Trautman
 	\date 2016.11.25
*/


void Inic_Expansion3( void )
{
	//!< BCD
	SetPINSEL ( EX3_BCDA , FUNCION_GPIO );
	SetPINSEL ( EX3_BCDB , FUNCION_GPIO );
	SetPINSEL ( EX3_BCDC , FUNCION_GPIO );
	SetPINSEL ( EX3_BCDD , FUNCION_GPIO );

	SetDIR ( EX3_BCDA , SALIDA );
	SetDIR ( EX3_BCDB , SALIDA );
	SetDIR ( EX3_BCDC , SALIDA );
	SetDIR ( EX3_BCDD , SALIDA );

	//!< dp
	SetPINSEL ( EX3_dp , FUNCION_GPIO );
	SetDIR ( EX3_dp , SALIDA );

	//!< Teclado
	//!<Filas
	SetPINSEL ( EX3_fila0 , FUNCION_GPIO );
	SetPINSEL ( EX3_fila1 , FUNCION_GPIO );
	SetPINSEL ( EX3_fila2 , FUNCION_GPIO );
	SetPINSEL ( EX3_fila3 , FUNCION_GPIO );

	SetDIR ( EX3_fila0 , ENTRADA );
	SetDIR ( EX3_fila1 , ENTRADA );
	SetDIR ( EX3_fila2 , ENTRADA );
	SetDIR ( EX3_fila3 , ENTRADA );

	//!<Columnas
	SetPINSEL(EX3_columna0 , FUNCION_GPIO);
	SetPINSEL(EX3_columna1 , FUNCION_GPIO);

	SetDIR ( EX3_columna0 , SALIDA );
	SetDIR ( EX3_columna1 , SALIDA );

	//!< Control de BCD
	SetPINSEL ( EX3_CLOCK , FUNCION_GPIO );
	SetPINSEL ( EX3_MRS , FUNCION_GPIO );

	SetDIR ( EX3_CLOCK , SALIDA );
	SetDIR ( EX3_MRS , SALIDA );

}



/**
	\fn void Debounce(void)
	\brief Filtrado de entradas digitales
 	\param void
	\return void
	\author Alan Kinast, Marcos Trautman
 	\date 2016.11.25
*/

void Debounce_Expansion3(void)
{
	unsigned char cambios,j = 0;

	static char ContadorEstados[ 4 ];

	j = GetPIN(in1,ON);
	if ( GetPIN(in2,ON) )
	{
		j |= 0x02;
		j=j;
	}
	cambios = ( BufferEntradas ^ j );

	if( cambios )
	{
		for( j = 0 ; j < ENTRADAS_EXPANSION3 ; j++ )
		{
			if( cambios & (0x01 << j) )
			{
				ContadorEstados[ j ] ++;

				if(ContadorEstados[ j ] == ACEPTAReSTADO)
				{
					ContadorEstados[ j ] = 0;
					BufferEntradas = BufferEntradas ^ (0x01 << j);
				}
			}
			else
				ContadorEstados[ j ] = 0;
		}
	}
	else
	{
		for( j = 0 ; j < ENTRADAS_EXPANSION3 ; j++ )
			ContadorEstados[ j ] = 0;
	}
}

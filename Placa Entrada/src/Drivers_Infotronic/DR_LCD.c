
/*******************************************************************************************************************************//**
 	\file DR_LCD.c
 	\brief Drivers/primitivas con privilegios del LCD
 	\details Trabajo Practico Obligatorio
 	\author Marcos Trautman, Alan Kinast
 	\date 2016.11.25
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** INCLUDES
 **********************************************************************************************************************************/
#include "DR_LCD.h"

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
volatile int DemoraLCD;
extern RTC_HoraFecha horafecha;
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
	\fn  void LCDDelay(uint16_t demora)
	\brief Es una funcion Bloqueante, hay que usarla con cuidado
 	\details
 	\author Alan Kinast, Marcos Trautman
 	\date 2016.11.25
*/

void LCDDelay(uint16_t demora){

	DemoraLCD = demora;
	while(DemoraLCD);

}


/**
	\fn  void void LatchLcd(void)
	\brief Señal de latch LCD
 	\details
 	\author Alan Kinast, Marcos Trautman
 	\date 2016.11.25
*/

void LatchLcd(void){
	SetPIN(LCD_E,ON);
	LCDDelay(2);
	SetPIN(LCD_E,OFF);
}


/**
	\fn  void Display_lcd( char *msg , char r , char p )
	\brief Imprime texto en LCD
 	\details Imprime texto en LCD y lo posiciona. HAy que pasarle un buffer con el texto que debe ser un string
 	\param 	[in]  char *msg (Buffer con texto), char r (renglon) , char p (posición en el renglon)
 	\author Alan Kinast, Marcos Trautman
 	\date 2016.11.25
*/

void Display_lcd( char *msg , char r , char p ){
	unsigned char i ;

	if( r )
        p = p + 0xc0 ;
	else
		p = p + 0x80 ;

	WComando8(p);
	for( i = 0 ; msg[ i ] != '\0' ; i++ )
		WDato(msg[ i ]);

}

/**
	\fn  void Inic_PinesLCD(void)
	\brief Inicializa pines del LCD
 	\details Imprime texto en LCD y lo posiciona. HAy que pasarle un buffer con el texto que debe ser un string
 	\author Alan Kinast, Marcos Trautman
 	\date 2016.11.25
*/

void Inic_PinesLCD(void){
	SetPINSEL(LCD_RS,PINSEL_GPIO);
	SetDIR(LCD_RS,SALIDA);
	SetMODE_OD(LCD_RS,OPEN_DRAIN);
	SetPIN(LCD_RS,OFF);

	SetPINSEL(LCD_E,PINSEL_GPIO);
	SetDIR(LCD_E,SALIDA);
	SetMODE_OD(LCD_E,OPEN_DRAIN);
	SetPIN(LCD_E,OFF);

	SetPINSEL(LCD_D4,PINSEL_GPIO);
	SetDIR(LCD_D4,SALIDA);
	SetMODE_OD(LCD_D4,OPEN_DRAIN);
	SetPIN(LCD_D4,OFF);

	SetPINSEL(LCD_D5,PINSEL_GPIO);
	SetDIR(LCD_D5,SALIDA);
	SetMODE_OD(LCD_D5,OPEN_DRAIN);
	SetPIN(LCD_D5,OFF);

	SetPINSEL(LCD_D6,PINSEL_GPIO);
	SetDIR(LCD_D6,SALIDA);
	SetMODE_OD(LCD_D6,OPEN_DRAIN);
	SetPIN(LCD_D6,OFF);

	SetPINSEL(LCD_D7,PINSEL_GPIO);
	SetDIR(LCD_D7,SALIDA);
	SetMODE_OD(LCD_D7,OPEN_DRAIN);
	SetPIN(LCD_D7,OFF);
}

/**
	\fn  void WComando8(uint8_t comando)
	\brief Escribe comando en LCD
 	\details
 	\param 	[in] uint8_t comando (Comando que quiero ejecutar)
 	\author Alan Kinast, Marcos Trautman
 	\date 2016.11.25
*/

void WComando8(uint8_t comando){
	SetPIN(LCD_RS,OFF);
	// Parte Alta del comando
	SetPIN(LCD_D4,((comando & 0x10) >> 4));
	SetPIN(LCD_D5,((comando & 0x20) >> 5));
	SetPIN(LCD_D6,((comando & 0x40) >> 6));
	SetPIN(LCD_D7,((comando & 0x80) >> 7));
	LatchLcd();
	LCDDelay(2);

	// Parte Baja del comando
	SetPIN(LCD_D4,(comando & 0x01));
	SetPIN(LCD_D5,((comando & 0x02) >> 1));
	SetPIN(LCD_D6,((comando & 0x04) >> 2));
	SetPIN(LCD_D7,((comando & 0x08) >> 3));
	LatchLcd();
	LCDDelay(2);
}

/**
	\fn  void WComando4(uint8_t comando)
	\brief Escribe comando en LCD cuando todavía no está en modo 4 bits
 	\details
 	\param 	[in] uint8_t comando (Comando de inicial)
 	\author Alan Kinast, Marcos Trautman
 	\date 2016.11.25
*/


void WComando4(uint8_t comando){
	SetPIN(LCD_RS,OFF);
	SetPIN(LCD_D4,((comando & 0x10) >> 4));
	SetPIN(LCD_D5,((comando & 0x20) >> 5));
	SetPIN(LCD_D6,((comando & 0x40) >> 6));
	SetPIN(LCD_D7,((comando & 0x80) >> 7));
	LatchLcd();
	LCDDelay(2);
}

/**
	\fn  void WDato(uint8_t dato)
	\brief Escribe dato en LCD para imprimir
 	\details
 	\param 	[in] uint8_t dato (Valor ASCII que quiero imprimir)
 	\author Alan Kinast, Marcos Trautman
 	\date 2016.11.25
*/

void WDato (uint8_t dato)
{
	SetPIN(LCD_RS,ON);
	//!< Parte Alta del comando
	SetPIN(LCD_D4,((dato & 0x10) >> 4));
	SetPIN(LCD_D5,((dato & 0x20) >> 5));
	SetPIN(LCD_D6,((dato & 0x40) >> 6));
	SetPIN(LCD_D7,((dato & 0x80) >> 7));
	LatchLcd();
	LCDDelay(2);

	//!< Parte Baja del comando
	SetPIN(LCD_D4,(dato & 0x01));
	SetPIN(LCD_D5,((dato & 0x02) >> 1));
	SetPIN(LCD_D6,((dato & 0x04) >> 2));
	SetPIN(LCD_D7,((dato & 0x08) >> 3));
	LatchLcd();
	LCDDelay(2);

}

/**
	\fn  void void WString (uint8_t *ptr)
	\brief Imprime string en LCD usando un loop de Wdato()
 	\details
 	\param 	[in] uint8_t *ptr (Puntero a string a imprimir en LCD)
 	\author Alan Kinast, Marcos Trautman
 	\date 2016.11.25
*/

void WString (uint8_t *ptr)
{
	while(*ptr != 0x00)
	{
		WDato(*ptr++);
	}
}

/**
	\fn  void Inic_LCD(void)
	\brief Inicializa LCD
 	\details
 	\param 	[in] void
 	\author Alan Kinast, Marcos Trautman
 	\date 2016.11.25
*/

void Inic_LCD(void)
{
	Inic_PinesLCD();		// Configura pines de interfaz con LCD
	LCDDelay(100);			// 400 Demora inicial para dejatr que todo se estabilice

	LCDDelay(10); 			// 25ms
	WComando4(0x30);

	LCDDelay(3);			// 7,5ms
	WComando4(0x30);

	LCDDelay(2);			// 5ms
	WComando4(0x30);

	// A partir de aca se puede chequear BF
	LCDDelay(2);			// 5ms
	WComando4(0x20);		// 4 bits

	LCDDelay(2);			// 5ms
	WComando4(0x20);		// 4 bits

	LCDDelay(2);			// 5ms
	WComando4(0x80);		// Clear del LCD

	LCDDelay(2);			// 5ms
	WComando4(0x00);		// Display y cursos off

	LCDDelay(2);			// 5ms
	WComando4(0xC0);		// Display de dos lineas caractetes de 5x11

	LCDDelay(2);			// 5ms
	WComando8(LCD_CLEAR);	// Limpia LCd y va a Home

}

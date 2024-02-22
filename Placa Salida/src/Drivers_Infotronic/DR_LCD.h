/*******************************************************************************************************************************//**
 	\file DR_LCD.h
 	\brief Headers, defines y prototipos de DR_LCD.c
 	\details Trabajo Practico Obligatorio
 	\author Marcos Trautman, Alan Kinast
 	\date 2016.11.25
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** MODULO
 **********************************************************************************************************************************/


/***********************************************************************************************************************************
 *** INCLUDES GLOBALES
 **********************************************************************************************************************************/
#include "DR_gpio.h"
#include "DR_pinsel.h"

/***********************************************************************************************************************************
 *** DEFINES GLOBALES
 **********************************************************************************************************************************/
#define		LCD_D4		0,5			//GPIO0
#define		LCD_D5		0,10		//GPIO0
#define		LCD_D6		2,4			//GPIO2
#define		LCD_D7		2,5			//GPIO2
#define		LCD_RS		2,6			//GPIO2
#define		LCD_BF		0,28		//GPIO1
#define		LCD_E		0,4			//GPIO0



#define		TOPE_BUFFER_LCD		160

#define		LCD_CONTROL			1
#define		LCD_DATA			0

#define 	RENGLON_1			0
#define 	RENGLON_2			1


#define		LCD_OFF				0x08
#define		LCD_ON				0x0C		// cursor off blink off
#define		LCD_CLEAR			0x01
#define 	CURSOR_ON			0x0E
#define		BLINK_ON			0x0D
#define 	LCD_CURSORON		0x0F
#define 	LCD_CURSOROFF		0x0C
#define 	LCD_CURSORDEC		0x10
#define 	LCD_CURSORINC		0x14
#define 	LCD_DEC				0x18
#define 	LCD_INC				0x1C
#define 	CURSOR				0x7E
#define		LCD_HOME1			0x80
#define		LCD_HOME2			0xA8

#define		IDLE				0
#define		NIBLE1_CMD			1
#define		NIBLE2_CMD			2
#define		LATCH_CMD			3
#define		NIBLE1_POS			4
#define		NIBLE2_POS			5
#define		LATCH_POS			6
#define		NIBLE1_DATO			7
#define		NIBLE2_DATO			8
#define		LATCH_DATO			9
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
void Inic_LCD(void);			//!< Inicialización del LCD
void WComando8(uint8_t);
void WDato(uint8_t);
void WString (uint8_t *);
void LCDDelay(uint16_t);
void Display_lcd( char *, char, char);
void DisplayInt_lcd(uint16_t, uint8_t, uint8_t);
void Push_BufferLCD(char, char *, char, char);
void ImprimeLCD(void);
void Inic_PinesLCD(void);

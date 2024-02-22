/*******************************************************************************************************************************//**
 *
 * @file		PR_EntradaDigital.h
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
#include "DR_LCD.h"
#include "stdlib.h"
#include "string.h"
/***********************************************************************************************************************************
 *** DEFINES GLOBALES
 **********************************************************************************************************************************/
#define 	ENERO		1
#define 	FEBRERO		2
#define 	MARZO		3
#define 	ABRIL		4
#define 	MAYO		5
#define 	JUNIO		6
#define 	JULIO		7
#define 	AGOSTO		8
#define 	SEPTIEMBRE	9
#define 	OCTUBRE		10
#define 	NOVIEMBRE	11
#define 	DICIEMBRE	12

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
int GetDemoraCartel(void);
void SetDemoraCartel(int );

void SetHora(char *);
void SetFecha(char *);
void SetFechaHora(void);
void ShowHoraFecha(void);
void ActualizaHora(void);
void ActualizaFecha(void);
void ConversionhoraFecha(char *);

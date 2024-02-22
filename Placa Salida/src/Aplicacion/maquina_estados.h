#ifndef DR_MAQUINA_ESTADOS_H_
#define DR_MAQUINA_ESTADOS_H_
/*******************************************************************************************************************************//**
 	\file maquina_estados.h
 	\brief Headers, defines y prototipos de maquina_estados.c
 	\details Trabajo Practico Obligatorio
 	\author Marcos Trautman, Alan Kinast
 	\date 2016.11.25
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** INCLUDES
 **********************************************************************************************************************************/
#include "DR_tipos.h"
#include "DR_SysTick.h"
#include "PR_Sensores.h"
#include "DR_Teclado.h"
#include "PR_7seg.h"
#include "PR_Teclado.h"
#include "DR_uart.h"
#include "stdio.h"//aca esta NULL para los punteros
#include "string.h"
#include "stdlib.h"
#include "PR_Pwm.h"
#include "PR_7Seg_Expansion3.h"
#include "PR_Teclado_Expansion3.h"
#include "DR_LCD.h"
#include "PR_EntradaDigital.h"
#include "PR_Timer.h"
#include "PR_LCD.h"

/***********************************************************************************************************************************
 *** DEFINES PRIVADOS AL MODULO
 **********************************************************************************************************************************/
#define		NO_OCUPACION	NO_KEY

//estados maquina de sensores
#define E_00	0
#define E_01	1
#define E_10	2
#define E_11	3
#define RESET	10

#define ENTROAUTO		1


//estados maquina entrada
#define ESTADO0	0
#define ESTADO1	1
#define ESTADO2	2
#define ESTADO3	3

#define COCHERALLENA	0xff

//estados maquina salida
#define ES_0	0
#define ES_1	1

//defines función comprobación
#define	CODIGOVALIDO	1
#define	CODIGOINVALIDO	0

//defines función confirmocodigo
#define	CONFIRMOCODIGO		1
#define NOCONFIRMOCODIGO	0

//defines Estados de Maquina Set Hora
#define H0	0
#define H1	1
#define H2	2
#define H3	3
#define H4	4
#define H5	5
#define H6	6
#define H7	7

//defines Estados de Maquina Set Fecha
#define F0	0
#define F1	1
#define F2	2
#define F3	3
#define F4	4
#define F5	5
#define F6	6
#define F7	7

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

/***********************************************************************************************************************************
 *** VARIABLES GLOBLES PRIVADAS AL MODULO
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** PROTOTIPO DE FUNCIONES PRIVADAS AL MODULO
 **********************************************************************************************************************************/
uint8_t Maquina_estados_sensores(void);
uint8_t Maquina_estados_sensores_salida(void);
void Maquina_estados_entrada(void);
void Maquina_estados_salida(void);
void abrirbarrera(void);
void cerrarbarrera(void);
uint8_t GetCodigo(void);
void timerON(uint8_t codigo);
uint8_t comprobacion(uint8_t );
void timerOFF(uint8_t );
uint8_t IngresoCodigo(void);
uint8_t confirmocodigo(void);
void entrocodigo(uint8_t );
void saliocodigo(uint8_t );
void Maquina_Estacionamiento(void);
void Maquina_Estacionamiento_Digital(void);
uint8_t Maquina_SetHora(char );
uint8_t Maquina_SetFecha(char );
void Inhabilitar(uint8_t );
/***********************************************************************************************************************************
 *** FUNCIONES PRIVADAS AL MODULO
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** FUNCIONES GLOBALES AL MODULO
 **********************************************************************************************************************************/

#endif /* DR_MAQUINA_ESTADOS_H_ */

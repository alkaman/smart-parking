//includes
#include "DR_Pwm.h"

volatile uint32_t Buff_PWM [CANT_CANALES_PWM] = { VALOR_NULL, VALOR_NULL };

void InicializarPWM2 ( void )
{
	PCONP = PCONP | (1<<6);		// Energizo el PWM1

	// Selecciono el PCLK del PWM1: PCLK_PWM1 = CCLK
	PCLKSEL0 = PCLKSEL0 & ( ~(3<<12) );
	PCLKSEL0 = PCLKSEL0 | (1<<12);

	// Le doy la Funcionalidad de los Pines como Salidas/Canales de PWM.
	SetPINSEL (PWM2, PINSEL_FUNC1);		// Giro en Sentido Horario. *****  MARCHA
	SetPINSEL (PWM3, PINSEL_FUNC1);		// Giro en Sentido Antihorario.  ******* REVERSA
	SetPINSEL (PWM4, PINSEL_FUNC1);

	// Selecciono a los Canales de PWM como Salidas.
	SetDIR (PWM2, SALIDA);
	SetDIR (PWM3, SALIDA);

	PWM1PR = PWM1_PRESCALER;		// Base de Tiempo: microsegundos.

	// Selecciono la Frencuencia del Motor:
	PWM1MR0 = FRECUENCIA_GIRO;				// Frecuencia de Giro del Motor: 250Hz

	// Selecciono los Valores del Duty Cycle (Tiempo de Trabajo):
	PWM1MR2 = PWM1_MATCH2;
	PWM1MR3 = PWM1_MATCH3;

	// Para que Interrumpa y Resetee el Timer cuando hay un Evento por MATCH0 e Interrumpa por MATCH2 y MATCH3
	PWM1MCR = PWM1MCR | 0x00000243;

	// Registro para Actualización de los Valores de MATCHx (Actualización de MATCH0, MATCH2, MATCH3).
	PWM1LER = PWM1LER | 0x0000000D;

	// Habilito Canales de Salida
	PWM1PCR = PWM1PCR & ( ~(1<<2) );	// Salida PWM2: Simple Edge
	PWM1PCR = PWM1PCR | (1<<10);	// The PWM2 Output Enabled.
	PWM1PCR = PWM1PCR & ( ~(1<<3) );	// Salida PWM3: Simple Edge
	PWM1PCR = PWM1PCR | (1<<11);	// The PWM3 Output Enabled.

	PWM1TCR = PWM1TCR & 0x00000004;		// Limpio los Bits de Timer/Counter, Reset, PWM1 Enable.
	PWM1TCR = PWM1TCR | 0x02;		// Reseteo el Timer.
	PWM1TCR = PWM1TCR & (~(0x02));	// Limpio Bit de Reset.

	// Habilito el Counter/Timer y Habilito el PWM1. ===> Counter Enable Y PWM Enable.
	PWM1TCR = PWM1TCR | 0x00000009;

	ISER0 = ISER0 | (1<<9);		// Habilito la Interrupción del PWM en el NVIC.
}

// ISR del PWM1:
void PWM1_IRQHandler ( void )
{
	if ( PWM1IR & 1 )		// Pregunto si Interrumpió por MATCH0.
	{
		PWM1IR = PWM1IR | 0x00000001;	// Limpio Flag.
	}

	if ( PWM1IR & 4 )		// Pregunto si Interrumpió por MATCH2.
	{
		PWM1IR = PWM1IR | 0x00000004;	// Limpio Flag.
	}

	if ( PWM1IR & 8 )		// Pregunto si Interrumpió por MATCH3.
	{
		PWM1IR = PWM1IR | 0x00000008;	// Limpio Flag.
	}
}


// Funciones que Son Drivers Utilizadas para el Desarrollo del PWM:
void ActualizarValoresMatchs ( void )
{
	uint32_t aux [ CANT_CANALES_PWM ];

	aux [ 0 ] = Buff_PWM [ 0 ];

	aux [ 1 ] = Buff_PWM [ 1 ];

	PWM1MR2 = aux [ 0 ];

	PWM1MR3 = aux [ 1 ];

	PWM1LER = PWM1LER | 0x0000000C;
}


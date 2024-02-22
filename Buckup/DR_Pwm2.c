//includes
#include "DR_Pwm.h"

//variables globales
uint32_t Buffer_PWM[CANT_SALIDAS_PWM]={198,199};
uint8_t FLAG_PWM[CANT_CANALES_PWM]={0,0};


//funciones
void InicializarPWM1 (void)
{
	PCONP = PCONP | (1<<6); // Enciendo el Periférico PWM1

	// Selecciono el Clock para el Periférico
	//bit 13 y 12 de PCLKSEL es el divisor de clock para el pwm 1
	// 0 en el bit 13 y 0 en el bit 12  ===> PCLK_PWM1 = CCLK/4
	PCLKSEL0 = PCLKSEL0 & (~(3<<12));

	// Elijo los Pines para las Salidas de PWM --- Canales de PWM
	// SetPINSEL (PWM1_1, FUNCION_1);
	SetPINSEL (PWM1_0, PINSEL_FUNC1); // Led RGBB ---- ContraMarcha o Bajada del Motor de CC. ---- Canal 2 del PWM1
	SetPINSEL (PWM1_1, PINSEL_FUNC1); // Led RGBR ---- Marcha o Subida del Motor de CC. ---- Canal 3 del PWM1
	SetPINSEL (PWM1_2, PINSEL_FUNC1); // Led RGBG
	// SetPINSEL (PWM1_5, FUNCION_1);
	// SetPINSEL (PWM1_6, FUNCION_1);
	// Declaro Los Canales de PWM Como Salida?
	SetDIR (PWM1_0, SALIDA);
	SetDIR (PWM1_1, SALIDA);
	SetDIR (PWM1_2, SALIDA);
	//SetDIR (PWM1_3, SALIDA);

	PWM1PR = PRESCALER_PWM; // Le Cargo el Valor de Preescaler para que el TC Incremente cada 1mSeg.
	// Frecuencia del Motor
	PWM1MR0 = PERIODO_T0_PWM; // MATCH0 = 1000 uSeg que equivale a una Frecuencia de 200Hz
	// Duty Cycle --- Ciclo de Trabajo
	PWM1MR2 = MATCH2_PWM; // MATCH2 = 0
	PWM1MR3 = MATCH3_PWM; // MATCH3 = 0
	// Para que Interrumpa y Resetee el Timer cuando hay un Evento por MATCH0 e Interrumpa por MATCH2 y MATCH3
	PWM1MCR = PWM1MCR | 0x00000243;
	// Registro para Actualización de los Valores de MATCHx (Actualización de MATCH0, MATCH2, MATCH3).
	PWM1LER = PWM1LER | 0x0000000D;//permite actualizar los registros de los match
	// Habilito Canales de Salida
	PWM1PCR = PWM1PCR & ( ~(1<<0) ); // Salida PWM1_0: Simple Edge
	PWM1PCR = PWM1PCR | (1<<10); // The PWM1_2 Output Enabled.
	PWM1PCR = PWM1PCR & ( ~(1<<1) ); // Salida PWM1_1: Simple Edge
	PWM1PCR = PWM1PCR | (1<<10); // The PWM1_2 Output Enabled.
	PWM1PCR = PWM1PCR & ( ~(1<<2) ); // Salida PWM1_2: Simple Edge
	PWM1PCR = PWM1PCR | (1<<10); // The PWM1_2 Output Enabled.
	//PWM1PCR = PWM1PCR & ( ~(1<<3) ); // Salida PWM1_3: Simple Edge
	//PWM1PCR = PWM1PCR | (1<<11); // The PWM1_3 Output Enabled.
	//PWM1PCR = PWM1PCR & ( ~(1<<4) ); // Salida PWM1_4: Simple Edge
	//PWM1PCR = PWM1PCR | (1<<12); // The PWM1_4 Output Enabled.

	PWM1TCR = PWM1TCR & 0x00000004; // Limpio los Bits de Timer/Counter, Reset, PWM1 Enable.
	PWM1TCR = PWM1TCR | 0x02; // Reseteo el Timer.
	PWM1TCR = PWM1TCR & (~(0x02)); // Limpio Bit de Reset.
	// Habilito el Counter/Timer y Habilito el PWM1. ===> Counter Enable Y PWM Enable.
	PWM1TCR = PWM1TCR | 0x00000009;
	ISER0 = ISER0 | (1<<9); // Habilito la Interrupción del PWM en el NVIC.
	//ISE_PWM;
}
// Función que Lee los Valores de un Buffer y los Carga A los Registros MRx del PWM.
// Es llamada con una Cierta Periodicidad ( cada 2.5 mseg ).
// Función que Carga los Valores a los Correspondientes Matchs desde el Buffer del PWM.
void Pop_PWM ( void )
{
	uint32_t aux[CANT_SALIDAS_PWM];
	aux [ 0 ] = Buffer_PWM [ 0 ];
	aux [ 1 ] = Buffer_PWM [ 1 ];
	PWM1MR2 = aux [ 0 ]; // Cargo el Valor al Registro MR2.
	PWM1MR3 = aux [ 1 ]; // Cargo el Valor al Registro MR3.
	PWM1LER = PWM1LER | 0x0000000C; // Registro que Permite Actualizar los Valores de los MATCHS.




}
// Función que Carga los Valores a un Buffer que Luego Van a Utilizar los MATCHS.
// Posicion 0 del Buffer_PWM Representa el MATCH2; la Posición 1 el MATCH3.
void Push_PWM (uint8_t caso)
{
	//ICER0 = ICER0 | (1<<9); // Deshabilito la Interrupción del PWM en el NVIC.
	switch ( caso )
	{//azul,rojo,verde
		case AZUL:
			FLAG_PWM[0] = ENCENDIDO;
			FLAG_PWM[1] = APAGADO;
			FLAG_PWM[2] = APAGADO;
			break;
		case ROJO:
			FLAG_PWM[0] = APAGADO;
			FLAG_PWM[1] = ENCENDIDO;
			FLAG_PWM[2] = APAGADO;
			break;
		case VERDE:
			FLAG_PWM[0] = APAGADO;
			FLAG_PWM[1] = APAGADO;
			FLAG_PWM[2] = ENCENDIDO;
			break;
		case VIOLETA:
			FLAG_PWM[0] = ENCENDIDO;
			FLAG_PWM[1] = AZUL;
			FLAG_PWM[2] = ENCENDIDO;
			break;
		case AMARILLO:
			FLAG_PWM[0] = ENCENDIDO;
			FLAG_PWM[1] = APAGADO;
			FLAG_PWM[2] = ENCENDIDO;
			break;
		case BLANCO:
			FLAG_PWM[0] = ENCENDIDO;
			FLAG_PWM[1] = ENCENDIDO;
			FLAG_PWM[2] = ENCENDIDO;
			break;
		case NO_COLOR:
			FLAG_PWM[0] = APAGADO;
			FLAG_PWM[1] = APAGADO;
			FLAG_PWM[2] = APAGADO;
			break;
		default:
			FLAG_PWM[0] = ENCENDIDO;
			FLAG_PWM[1] = ENCENDIDO;
			FLAG_PWM[2] = ENCENDIDO;
			break;
		//falta default
	}
}
//ISER0 = ISER0 | (1<<9); // Habilito la Interrupción del PWM en el NVIC.

//habilita o deshabilita salida del pwm
void Set_PWM (void)
{
	int i;
	uint32_t aux=PWM1PCR;
	for(i=0;i<CANT_CANALES_PWM;i++)
	{
		if(FLAG_PWM[i]!=((aux>>(10+i)) & 0x0001))
		{
			if(FLAG_PWM[i]==ENCENDIDO)
			{
				PWM1PCR = PWM1PCR | (1<<(10+i)); // The PWM1_2 Output Enabled.
			}
			if(FLAG_PWM[i]==APAGADO)
			{
				PWM1PCR = PWM1PCR & (~(1<<(10+i))); // The PWM1_2 Output Enabled.
			}
		}
	}
}


/*
void push_PWM (uint8_t caso)
{
	//ICER0 = ICER0 | (1<<9); // Deshabilito la Interrupción del PWM en el NVIC.
	switch ( caso )
	{
		case MAX_MARCHA:
			Buffer_PWM[0] = VALOR_NULL;
			Buffer_PWM[1] = MAX_VALOR_MARCHA;
			break;
		case MIN_MARCHA:
			Buffer_PWM[0] = VALOR_NULL;
			Buffer_PWM[1] = MIN_VALOR_MARCHA;
			break;
		case MAX_CONTRAMARCHA:
			Buffer_PWM[0] = MAX_VALOR_CONTRAMARCHA;
			Buffer_PWM[1] = VALOR_NULL;
			break;
		case MIN_CONTRAMARCHA:
			Buffer_PWM[0] = MIN_VALOR_CONTRAMARCHA;
			Buffer_PWM[1] = VALOR_NULL;
			break;
		case FRENADO:
			Buffer_PWM[0] = VALOR_NULL;
			Buffer_PWM[1] = VALOR_NULL;
			break;
		//falta default
	}
}
*/


/*
 * DR_Timer.c
 *
 *  Created on: 25/9/2016
 *      Author: Alka
 */

/*
void timerinit (void)
{
	PCONP|=(1<<1);//habilito alimentacion
	ISER0|=(1<<1);//habilito interrupciones para el T0

	PCLKSEL0 |= (1<<2);
	PCLKSEL0 &= ~(1<<3);//configuro clock del timer CLCK
	//T0TCR=(1<<1);//reseteo y pongo en estado de reset
	TIMER0.CTCR&=~(1<<0);
	TIMER0.CTCR&=~(1<<1);//elijo el timer como timer y no como contador

	//no se usan
	TIMER0.TC;//contador del timer, se incrementa cuando PC llega a PR
	T0PC;//Prescale counter, se incrementa con cada PCLK
	TIMER0.PR=1000 - 1;//max de PC, default 0
	//como CLCK es 4Mhz, le aplico un divisor que cuente cada 1000
	//
	//T0MCR|=(1<<0)|(1<<3)|(1<<4);//habilito match interrupt 0 y 1 y que resetee cuando llegue al 1

	T0MCR|=(1<<0);//T0MR0I=(1<<0);//habilito interrupcion del match register 0 del timer 0
	T0MCR|=(1<<3);//T0MR1I=(1<<0);//habilito interrupcion del match register 1 del timer 0
	T0MCR|=(1<<4);//resetea al llegar al match 1

	T0MR0=4000;//que se active cuando TC llega a 4000, cada 1 seg
	T0MR1=8000;//que se active cuando TC llega a 8000, cada 2 seg


	//T0TCR&=~(1<<1);//saco de estado de reset
	T0TCR|=(1<<0);// empiezo a contar
}

void TIMER0_IRQHandler(void)//T: tiempo cada cual se realiza la interrupcion tiene que ser >>>>> t:tiempo de ejecucion de la interrupcion  (tiene que ser mucho mas chico t )
{
	if(T0IR&(1<<0))
	{
		T0IR = (1<<0);//escribo un 1 para que se resetee el registro
		GPIO_SET(LED,1);
	}
	if(T0IR&(1<<1))
	{
		T0IR =(1<<1);//escribo un 1 para que se resetee el registro
		GPIO_SET(LED,0);
	}
}

*/

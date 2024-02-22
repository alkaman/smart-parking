/*******************************************************************************************************************************//**
 	\file #include PR_LCD.c
 	\brief Primitivas del LCD
 	\details Trabajo Practico Obligatorio
 	\author Marcos Trautman, Alan Kinast
 	\date 2016.11.25
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** INCLUDES
 **********************************************************************************************************************************/
#include "PR_LCD.h"


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
volatile int DemoraCartel=0;
RTC_HoraFecha horafecha;
extern uint32_t f_tick_rtc;
uint8_t dia_tick=0;
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
	\fn  int GetDemoraCartel(void)
	\brief Lee el valor del buffer de Demora de Cartel del LCD y lo retorna
 	\details
 	\param 	[in] void
 	\return int
 			valor de demora actual, en 0 ya se cumplio la demora solicitada
 	\author Alan Kinast, Marcos Trautman
 	\date 2016.11.25
*/

int GetDemoraCartel(void)
{
	return DemoraCartel;
}

/**
	\fn  void SetDemoraCartel(int demora)
	\brief Le da un valor a la demora necesaria para los carteles del LCD
 	\details
 	\param 	[in] void
 	\return int
 			valor de demora actual, en 0 ya se cumplio la demora solicitada
 	\author Alan Kinast, Marcos Trautman
 	\date 2016.11.25
*/

void SetDemoraCartel(int demora)
{
	DemoraCartel=demora;
}


/**
	\fn  void SetHora(char * hora)
	\brief Recibe un String con la hora y se lo asigna a variables de una estructura Global
 	\details
 			La hora se recibe en el formato hh:mm:ss y le asigna hora, minutos y segundos a
 			las variables que corresponda de la estructura global horafecha.
 	\param 	[in] char * hora
 	\return void
 	\author Alan Kinast, Marcos Trautman
 	\date 2016.11.25
*/

void SetHora(char * hora)
{
	char aux_hora[3]={0};

	if(hora != NULL)
	{
		hora[2]='\0';
		strcpy(aux_hora,&hora[0]);
		horafecha.hora=atoi(aux_hora);
		hora[5]='\0';
		strcpy(aux_hora,&hora[3]);
		horafecha.min=atoi(aux_hora);
		hora[8]='\0';
		strcpy(aux_hora,&hora[6]);
		horafecha.seg=atoi(aux_hora);
	}
}

/**
	\fn  void SetFecha(char * fecha)
	\brief Recibe un String con la fecha y se lo asigna a variables de una estructura Global
 	\details
 			La fecha se recibe en el formato dd:mm:yy y le asigna dia, mes y año a
 			las variables que corresponda de la estructura global horafecha.
 	\param 	[in] char * fecha
 	\return void
 	\author Alan Kinast, Marcos Trautman
 	\date 2016.11.25
*/

void SetFecha(char * fecha)
{
	char aux_fecha[3]={0};
	if(fecha != NULL)
	{
		fecha[2]='\0';
		strcpy(aux_fecha,&fecha[0]);
		horafecha.dia=atoi(aux_fecha);
		fecha[5]='\0';
		strcpy(aux_fecha,&fecha[3]);
		horafecha.mes=atoi(aux_fecha);
		fecha[8]='\0';
		strcpy(aux_fecha,&fecha[6]);
		horafecha.anio=atoi(aux_fecha);
	}
}

/**
	\fn  void SetFechaHora(void)
	\brief Funcion que le da valores iniciales al dia,mes,año, hora, minutos y segundos de la
		   estructura global de la hora y la fecha
 	\details
 	\param 	[in] char * fecha
 	\return void
 	\author Alan Kinast, Marcos Trautman
 	\date 2016.11.25
*/

void SetFechaHora(void)
{
	horafecha.dia=14;
	horafecha.mes=12;
	horafecha.anio=16;
	horafecha.hora=17;
	horafecha.min=30;
	horafecha.seg=30;
}

/**
	\fn  void ShowHoraFecha(void)
	\brief Funcion que llama a una funcion para convertir la hora y fecha a un string y luego
		   pasarsela como argumento a la funcion que muestra por lcd dicho string.
 	\details
 	\param 	[in] void
 	\return void
 	\author Alan Kinast, Marcos Trautman
 	\date 2016.11.25
*/

void ShowHoraFecha(void)
{
	char cartel[16]={0};
	ConversionhoraFecha(cartel);
	Display_lcd(cartel,1,0);
}

/**
	\fn  void ConversionhoraFecha(char * cartel)
	\brief Funcion que recibe un puntero en el cual le carga la hora y fecha actual en formato de
		   string.
 	\details
 	\param 	[in] char * cartel
 	\return void
 	\author Alan Kinast, Marcos Trautman
 	\date 2016.11.25
*/

void ConversionhoraFecha(char * cartel)
{
	if(horafecha.dia<10)
	{
		cartel[0]='0';
		itoa(horafecha.dia,&cartel[1],10);
	}
	else
	{
		itoa(horafecha.dia,&cartel[0],10);
	}
	cartel[2]='/';
	if(horafecha.mes<10)
	{
		cartel[3]='0';
		itoa(horafecha.mes,&cartel[4],10);
	}
	else
	{
		itoa(horafecha.mes,&cartel[3],10);
	}
	cartel[5]='/';
	if(horafecha.anio<10)
	{
		cartel[6]='0';
		itoa(horafecha.anio,&cartel[7],10);
	}
	else
	{
		itoa(horafecha.anio,&cartel[6],10);
	}
	cartel[8]=' ';
	cartel[9]=' ';
	if(horafecha.hora<10)
	{
		cartel[10]='0';
		itoa(horafecha.hora,&cartel[11],10);
	}
	else
	{
		itoa(horafecha.hora,&cartel[10],10);
	}
	cartel[12]=':';
	if(horafecha.min<10)
	{
		cartel[13]='0';
		itoa(horafecha.min,&cartel[14],10);
	}
	else
	{
		itoa(horafecha.min,&cartel[13],10);
	}
	cartel[15]='\0';
}

/**
	\fn  void ActualizaHora(void)
	\brief Funcion que analiza un flag que se activa cada un segundo desde el rtc para llevar el
		   conteo de la hora actual y actualiza el display cada vez que se modifica.
 	\details
 	\param 	[in] void
 	\return void
 	\author Alan Kinast, Marcos Trautman
 	\date 2016.11.25
*/

void ActualizaHora(void)
{
	if(f_tick_rtc == 1)
	{
		f_tick_rtc=0;
		if(horafecha.seg<59)
		{
			horafecha.seg++;
		}
		else
		{
			horafecha.seg=0;
			if(horafecha.min<59)
			{
				horafecha.min++;
				ShowHoraFecha();
			}
			else
			{
				horafecha.min=0;
				if(horafecha.hora<23)
				{
					horafecha.hora++;
				}
				else
				{
					horafecha.hora=0;
					dia_tick=1;
				}
				ShowHoraFecha();
			}
		}
	}
}

/**
	\fn  void ActualizaFecha(void)
	\brief Funcion que analiza un flag que se activa cada vez que pasa un dia para llevar la cuenta
		   de la fecha y actualiza el display cada vez que se modifica.
 	\details
 	\param 	[in] void
 	\return void
 	\author Alan Kinast, Marcos Trautman
 	\date 2016.11.25
*/

void ActualizaFecha(void)
{
	if(dia_tick==1)
	{
		dia_tick=0;
		switch(horafecha.mes)
		{
			case ENERO:
				if(horafecha.dia<31)
					horafecha.dia++;
				else
				{
					horafecha.dia=1;
					horafecha.mes++;
				}
			case FEBRERO:
				if(horafecha.dia<28)
					horafecha.dia++;
				else
				{
					horafecha.dia=1;
					horafecha.mes++;
				}
			case MARZO:
				if(horafecha.dia<31)
					horafecha.dia++;
				else
				{
					horafecha.dia=1;
					horafecha.mes++;
				}
			case ABRIL:
				if(horafecha.dia<30)
					horafecha.dia++;
				else
				{
					horafecha.dia=1;
					horafecha.mes++;
				}
			case MAYO:
				if(horafecha.dia<31)
					horafecha.dia++;
				else
				{
					horafecha.dia=1;
					horafecha.mes++;
				}
			case JUNIO:
				if(horafecha.dia<30)
					horafecha.dia++;
				else
				{
					horafecha.dia=1;
					horafecha.mes++;
				}
			case JULIO:
				if(horafecha.dia<31)
					horafecha.dia++;
				else
				{
					horafecha.dia=1;
					horafecha.mes++;
				}
			case AGOSTO:
				if(horafecha.dia<31)
					horafecha.dia++;
				else
				{
					horafecha.dia=1;
					horafecha.mes++;
				}
			case SEPTIEMBRE:
				if(horafecha.dia<30)
					horafecha.dia++;
				else
				{
					horafecha.dia=1;
					horafecha.mes++;
				}
			case OCTUBRE:
				if(horafecha.dia<31)
					horafecha.dia++;
				else
				{
					horafecha.dia=1;
					horafecha.mes++;
				}
			case NOVIEMBRE:
				if(horafecha.dia<30)
					horafecha.dia++;
				else
				{
					horafecha.dia=1;
					horafecha.mes++;
				}
			case DICIEMBRE:
				if(horafecha.dia<31)
					horafecha.dia++;
				else
				{
					horafecha.dia=1;
					horafecha.mes=1;
					if(horafecha.anio<100)
						horafecha.anio++;
					else
					{
						horafecha.anio=0;
					}
				}
		}
		ShowHoraFecha();
	}
}

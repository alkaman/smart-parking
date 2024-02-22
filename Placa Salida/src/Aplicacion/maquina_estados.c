
/*******************************************************************************************************************************//**
 	\file maquina_estados.c
 	\brief Control acceso de vehículos de un estacionamiento
 	\details Trabajo Practico Obligatorio
 	\author Marcos Trautman, Alan Kinast
 	\date 2016.11.25
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** INCLUDES
 **********************************************************************************************************************************/
#include "maquina_estados.h"

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
uint32_t autos=0;//!<Variable global, cantidad autos
extern uint8_t vector_flag[CANT_AUTOS];
extern uint32_t vector_estadia[CANT_AUTOS];
extern uint32_t f_tick_rtc;
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
	\fn  uint8_t Maquina_estados_sensores(void)
	\brief Maquina de estado de los sensores de la barrera de entrada
 	\details Funcion que se encarga de sensar si un auto entro al estacionamiento
 			 Devuelve 1 solo cuando completa la secuencia correctamente
 	\author Alan Kinast, Marcos Trautman
 	\date 2016.11.25
*/

uint8_t Maquina_estados_sensores(void)
{
	static uint8_t estados=RESET,sentido=0,teclas=0;
	uint8_t A=0,B=0;
	teclas=GetKey_Debounce_Sensores ();
	A=0x01&(teclas>>1);
	B=0x01&teclas;
	switch(estados)
    	{
    		case RESET:
				sentido=0;
				autos=0;
				estados=E_00;
				break;
    		case E_00:
    			Display_Expansion3(1,DSP1);
    			if(A==ON&&B==OFF)
    			{
    				sentido++;
    				estados=E_01;
    			}
    			if(A==OFF&&B==ON)
    			{
    				sentido--;
    				estados=E_10;
    			}
    			if(sentido==4)
    			{
    				sentido=0;
    				autos++;
    				return ENTROAUTO;
    			}
    			if(sentido==-4)
    			{
    				sentido=0;
    				autos--;
    			}
    			break;
    		case E_01:
    			Display_Expansion3(2,DSP1);
    			if(A==ON&&B==ON)
    			{
    				sentido++;
    				estados=E_11;
    			}
    			if(A==OFF&&B==OFF)
    			{
    				sentido--;
    				estados=E_00;
    			}
    			break;
    		case E_11:
    			Display_Expansion3(3,DSP1);
    			if(A==OFF&&B==ON)
    			{
    				sentido++;
    				estados=E_10;
    			}
    			if(A==ON&&B==OFF)
    			{
    				sentido--;
    				estados=E_01;
    			}
    			break;
    		case E_10:
    			Display_Expansion3(4,DSP1);
    		    if(A==OFF&&B==OFF)
    		    {
    		    	sentido++;
    		    	estados=E_00;
    		    }
    		    if(A==ON&&B==ON)
    		    {
    		    	sentido--;
    		    	estados=E_11;
    		    }
		    	break;

    		default:
    			estados=RESET;
    			break;
    	}
	return 0;
}

/**
	\fn  uint8_t Maquina_estados_sensores_salida(void)
	\brief Maquina de estado de los sensores de la barrera de salida
 	\details Funcion que se encarga de sensar si un auto entro al estacionamiento
 			 Devuelve 1 solo cuando completa la secuencia correctamente
 	\author Alan Kinast, Marcos Trautman
 	\date 2016.11.25
*/

uint8_t Maquina_estados_sensores_salida(void)
{
	static uint8_t estados=RESET,sentido=0,teclas=0;
	uint8_t A=0,B=0;
	teclas=GetKey_Debounce_Sensores ();
	A=0x01&(teclas>>1);
	B=0x01&teclas;
	switch(estados)
    	{
    		case RESET:
				sentido=0;
				autos=0;
				estados=E_00;
				break;
    		case E_00:
    			Display(1,DSP1);
    			if(A==ON&&B==OFF)
    			{
    				sentido++;
    				estados=E_01;
    			}
    			if(A==OFF&&B==ON)
    			{
    				sentido--;
    				estados=E_10;
    			}
    			if(sentido==4)
    			{
    				sentido=0;
    				autos++;
    				return ENTROAUTO;
    			}
    			if(sentido==-4)
    			{
    				sentido=0;
    				autos--;
    			}
    			break;
    		case E_01:
    			Display(2,DSP1);
    			if(A==ON&&B==ON)
    			{
    				sentido++;
    				estados=E_11;
    			}
    			if(A==OFF&&B==OFF)
    			{
    				sentido--;
    				estados=E_00;
    			}
    			break;
    		case E_11:
    			Display(3,DSP1);
    			if(A==OFF&&B==ON)
    			{
    				sentido++;
    				estados=E_10;
    			}
    			if(A==ON&&B==OFF)
    			{
    				sentido--;
    				estados=E_01;
    			}
    			break;
    		case E_10:
    			Display(4,DSP1);
    		    if(A==OFF&&B==OFF)
    		    {
    		    	sentido++;
    		    	estados=E_00;
    		    }
    		    if(A==ON&&B==ON)
    		    {
    		    	sentido--;
    		    	estados=E_11;
    		    }
		    	break;

    		default:
    			estados=RESET;
    			break;
    	}
	return 0;
}



/**
*	\fn       void Maquina_estados_entrada(void)
*   \brief    lector de tecla 0
*	\details  funcion que recibe el pulso de la tecla 0, si hay lugar: entrega codigo, abre barrera y saluda.
*			  Inicia timer en placa 1.
*			  la cierra despues que los sensores de presencia indiquen que el auto se fue.
*	\author   Alan Kinast, Marcos Trautman
*	\date     2016.11.25

*/

void Maquina_estados_entrada(void)
{
	static uint8_t estado=RESET;
	uint8_t codigo=0,tecla=0;
	static uint8_t aux=0;
	static uint8_t FlagAntiBloqueo=0,FlagAntiBloqueo2=1;

	tecla=(GetKey_Debounce()>>2)&0x01;//!< estado= 0,1,2 dependiendo de que tecla toco (0xff si no toco nada)

	switch (estado)
	{
		case ESTADO0:
			if((FlagAntiBloqueo==0)||(FlagAntiBloqueo2==1))//!<Proteccion por metodos bloqueantes del lcd
			{
				if(FlagAntiBloqueo==0)
				{
					Display_lcd("Bienvenido     ",0,0);
				}
				FlagAntiBloqueo2=1;
				if(!GetDemoraCartel())
				{
					//Display_lcd("              ",1,0);
					ShowHoraFecha();
					FlagAntiBloqueo2=0;
				}
				FlagAntiBloqueo=1;
			}
			Display_Expansion3(1,DSP0);
			if(tecla==1)
			{
				codigo=GetCodigo();
				if(codigo==COCHERALLENA)
				{
					Display_lcd("Cochera Llena",1,0);
					SetDemoraCartel(1600);
					FlagAntiBloqueo2=1;
				}
				else
				{
					abrirbarrera();
					Display_Expansion3(100+codigo,DSP1);//muestro por pantalla el código
					aux=codigo;
					Display_lcd("Disfrute su",0,0);//!<Muestro por pantalla "Disfrute su estadia"
					Display_lcd("estadia        ",1,0);
					estado=ESTADO1;
					transmitir("Abrio Barrera\n");
				}
			}

			break;
		case ESTADO1:
			Display_Expansion3(200+aux,DSP0);
			if(Maquina_estados_sensores())//!<solo devuelve 1 cuando efectivamente el auto salio
			{
				entrocodigo(aux);//!< Primitiva que convierte el codigo a ascii y lo envia
				cerrarbarrera();
				estado=ESTADO0;
				transmitir("Cerro barrera\n");
				FlagAntiBloqueo=0;
			}
			break;
		case RESET:
			estado=ESTADO0;
			break;
		default:
			estado=RESET;
			break;
	}
}



/**
*	\fn       void Maquina_estados_salida(void)
*
*	\brief    barrera de salida
*
*	\details  recibe el codigo ingresado por teclado para habilitar la salida.
*			  Una vez habilitada abre barrera, notifica a la aplicacion que salio el codigo correspondiente
*			  maneja los sensores de presencia
*
*	\author   Alan Kinast, Marcos Trautman
*	\date     2016.11.25
*/
void Maquina_estados_salida(void)
{
	static uint8_t estado=RESET;
	static uint8_t FlagAntiBloqueo=0,FlagAntiBloqueo2=0;
	uint8_t validez=CODIGOINVALIDO,codigo=0;//inicio codigo en NO INGRESO CODIGO (0) y validez en CODIGO INVALIDO


	switch(estado)
	{
	case ES_0:
		if((FlagAntiBloqueo==0)||(FlagAntiBloqueo2==1))//!<Proteccion por meotodos bloqueantes del lcd
		{
			if(FlagAntiBloqueo==0)
			{
				Display_lcd("Ingrese Codigo",0,0);
			}
			FlagAntiBloqueo2=1;
			if(!GetDemoraCartel())
			{
				//Display_lcd("               ",1,0);
				ShowHoraFecha();
				FlagAntiBloqueo2=0;
			}
			FlagAntiBloqueo=1;
		}
		codigo=IngresoCodigo();
		Display(100+codigo,DSP0);
		if(confirmocodigo())
		{
			validez=comprobacion(codigo);
		}
		if(validez==CODIGOVALIDO)//!< significa que ingreso bien el codigo
		{
			Display_lcd("Gracias       ",0,0);
			Display_lcd("Hasta luego    ",1,0);
			transmitir("Codigo Valido\n");
			abrirbarrera(); //!< funcion que abre barrera
			timerOFF(codigo); //!< primitiva que finaliza timer de ese codigo
			saliocodigo(codigo);// envia por uart el codigo que finalizo
			estado=ES_1;
			transmitir("Abrio Barrera\n");
		}
		if(validez==CODIGOINVALIDO&&confirmocodigo())//!< significa que ingreso un codigo invalido
		{
			Display_lcd("Codigo Invalido",1,0);
			SetDemoraCartel(1600);
			FlagAntiBloqueo2=1;
		}
		break;
	case ES_1:
		Display((200+codigo),DSP0);
		if(Maquina_estados_sensores_salida())//!<solo devuelve 1 cuando efectivamente el auto salio
		{
			cerrarbarrera();
			estado=ES_0;
			transmitir("Cerro barrera\n");
			FlagAntiBloqueo=0;
		}
		break;
	case RESET:
		estado=ES_0;
		break;
	default:
		estado=RESET;
		break;
	}
}





/**
*	\fn       uint8_t GetCodigo(void)
*
*	\brief    Devuelve codigo disponible del estacionamiento
*
*	\details  Revisa que codigo de estacionamiento esta libre y lo devuelve.
*			  Si no hay codigo libre, devuelve cocherallena
*
*	\author   Grupo 1
*/

uint8_t GetCodigo(void)
{
	uint8_t i;
	for(i=0;i<CANT_AUTOS;i++)
	{
		if(vector_flag[i]==0)
		{
			timerON(i);
			return i;
		}
	}
	return COCHERALLENA;//hay que hacer return de estacionamiento lleno
}

/**
*	\fn       uint8_t IngresoCodigo(void)
*
*	\brief    Me devuelve el codigo ingresado
*
*	\details  Si presione Sw4 incremento en uno el codigo que deseo ingresar
*			  Si presione Sw3 decremento en uno el codigo que deseo ingresar
*
*	\author   Grupo 1
*/


uint8_t IngresoCodigo(void)
{
	static uint8_t codigo=0,yapresione=0;
	uint8_t teclas4=((GetKey_Debounce()>>3)&0x01);
	uint8_t teclas3=((GetKey_Debounce()>>2)&0x01);
	if(teclas4&&(yapresione==0))
	{
		yapresione=1;
		codigo++;
	}
	if(teclas3&&(yapresione==0))
	{
		yapresione=1;
		codigo--;
	}
	if((teclas4==0)&&(teclas3==0))
	{
		yapresione=0;
	}
	if(codigo>=CANT_AUTOS)
	{
		codigo=0;
	}
	return codigo;
}

/**
*	\fn       uint8_t confirmocodigo(void)
*
*	\brief    Confirmo el codigo que deseo ingresar
*
*	\details  Si presione Sw5 confirmo el codigo que deseo ingresar para salir
*
*	\author   Grupo 1
*/

uint8_t confirmocodigo(void)
{
	uint8_t teclas=(GetKey_Debounce()>>4)&0x01;
	if(teclas==1)
	{
		return CONFIRMOCODIGO;
	}
	return NOCONFIRMOCODIGO;
}

/**
*	\fn       uint8_t comprobacion(uint8_t codigo)
*
*	\brief    Confirmo que el codigo ingresado es un codigo activo
*
*	\details  Compara el codigo ingresado contra el vector de ocupacion de codigo vector_flag
*
*	\author   Grupo 1
*/

uint8_t comprobacion(uint8_t codigo)
{
	if(codigo<CANT_AUTOS)//!<proteccion por si le mando un codigo superior al posible
	{
		if(vector_flag[codigo]==1)
		{
			return CODIGOVALIDO;
		}
	}
	return CODIGOINVALIDO;
}

/**
*	\fn       void timerON(uint8_t codigo)
*
*	\brief    Pone como activo el codigo correspondiente
*
*	\details  Al poner un uno en vector_flag esta poniendo como activo el codigo correspondiente
*			  Luego en la aplicacion de los timer se encarga de contar
*
*	\author   Grupo 1
*/

void timerON(uint8_t codigo)
{
	if(codigo<=CANT_AUTOS)
		vector_flag[codigo]=1;
}

/**
*	\fn       void timerOFF(uint8_t codigo)
*
*	\brief    Pone como inactivo el codigo correspondiente
*
*	\details  Al poner un cero en vector_flag esta poniendo como inactivo el codigo correspondiente
*			  Luego llama a SetEstadia
*
*	\author   Grupo 1
*/

void timerOFF(uint8_t codigo)
{
	if(codigo<=CANT_AUTOS)
		vector_flag[codigo]=0;
	SetEstadia(codigo, 0, 0, 0, 0);//!< reseteo el timer
}

/**
*	\fn       void Inhabilitar(uint8_t codigo)
*
*	\brief    Deshabilita o habilita el codigo especificado
*
*	\details  Al poner un dos en vector_flag esta poniendo como inhabilitado el codigo
*			  correspondiente. Al poner un cero lo vuelve a poner como disponible.
*
*	\author   Grupo 1
*/

void Inhabilitar(uint8_t codigo)
{
	if(codigo<=CANT_AUTOS)
	{
		if(vector_flag[codigo]==0)
		{
			vector_flag[codigo]=2;
		}
		else
		{
			if(vector_flag[codigo]==2)
				vector_flag[codigo]=0;
		}
	}
	SetEstadia(codigo, 0, 0, 0, 0);//!< reseteo el timer
}

/**
*	\fn       void abrirbarrera(void)
*
*	\brief    Abre la barrera
*
*	\details  Llama a la primitiva PushServo con el valor correspondiente para abrir la barrera
*
*	\author   Grupo 1
*/

void abrirbarrera(void)
{
	PushServo (ABREBARRERA);
}

/**
*	\fn       void cerrarbarrera(void)
*
*	\brief    Cierra la barrera
*
*	\details  Llama a la primitiva PushServo con el valor correspondiente para cerrar la barrera
*
*	\author   Grupo 1
*/

void cerrarbarrera(void)
{
	PushServo (CIERRABARRERA);
}

/**
*	\fn       void entrocodigo(uint8_t codigo)
*
*	\brief    Envia por puerto serie "Ei\n\0" donde i es igual al codigo que ingreso
*
*	\details  Carga en un vector "Ei\n\0" donde i es el codigo ingresado
*			  Luego con la funcion transmitir envia todo el vector por puerto serie
*
*	\author   Grupo 1
*/

void entrocodigo(uint8_t codigo)
{
	static char c2[4]={'\0'};
	c2[0]='E';
	c2[1]=(char)((int)codigo + 48);
	c2[2]='\n';
	c2[3]='\0';
	transmitir(c2);
}

/**
*	\fn       void saliocodigo(uint8_t codigo)
*
*	\brief    Envia por puerto serie "Si\n\0" donde i es igual al codigo que salio
*
*	\details  Carga en un vector "Si\n\0" donde i es el codigo ingresado
*			  Luego con la funcion transmitir envia todo el vector por puerto serie
*
*	\author   Grupo 1
*/

void saliocodigo(uint8_t codigo)
{
	static char c2[4]={'\0'};
	c2[0]='S';
	c2[1]=(char)((int)codigo + 48);
	c2[2]='\n';
	c2[3]='\0';
	transmitir(c2);
}

/**
*	\fn       void Maquina_Estacionamiento(void)
*
*	\brief    Envia por puerto serie "Ai" donde i es la ubicacion del estacionamiento ocupada
*
*	\details  Llama a la primitiva del teclado matricial la cual devuelve un numero del 0 al 7
*			  segun que tecla este presionada. De estar presionada alguna tecla envia por puerto
*			  serie a traves de la funcion Push_TX "Ai" donde i es la tecla presionada más 1
*			  (Ya que los estacionamientos van del A1 al A8).
*
*	\author   Grupo 1
*/

void Maquina_Estacionamiento(void)
{
	uint8_t Posicion;

	Posicion = Get_Teclado_Matricial();

	if(Posicion != NO_OCUPACION)
	{
		Push_TX('A');
		Push_TX((char)((int)Posicion + 49));//es +49 pq queremos que subirle uno mas que la conversio a char
	}
}

/**
*	\fn       void Maquina_Estacionamiento_Digital(void)
*
*	\brief    Envia por puerto serie "Ai" donde i es 1 o 2 dependiendo de la entrada digital
*
*	\details  Llama a la primitiva que devuelve el estado de dos entradas digitales,
*			  bit 0 entrada 0
*			  bit 1 entrada 1
*			  1 Estado alto
*			  0 estado bajo
*			  Luego envia por puerto serie a traves de la funcion Push_TX "Ai" donde i es la tecla presionada más 1
*			  (Ya que los estacionamientos van del A1 al A8).
*
*	\author   Grupo 1
*/

void Maquina_Estacionamiento_Digital(void)
{
	uint8_t Posicion2;
	static int flag=0;
	static int flag2=0;

	Posicion2 =GetKey_Debounce_Digital();

	if(((Posicion2 & 0x01) ) && (flag==0) )

	{
		flag=1;
		Push_TX('A');
		Push_TX((char)((int)1+ 48));//es +49 pq queremos que subirle uno mas que la conversio a char
	}

	if((!(Posicion2 & 0x01) ) && (flag==1) )
	{
		flag=0;
		Push_TX('A');
		Push_TX((char)((int)1 + 48));//es +49 pq queremos que subirle uno mas que la conversio a char
	}
	if(((Posicion2 & 0x02) ) && (flag2==0) )
	{
		flag2=1;
		Push_TX('A');
		Push_TX((char)((int)2 + 48));//es +49 pq queremos que subirle uno mas que la conversio a char
	}
	if((!(Posicion2 & 0x02) ) && (flag2==1) )
	{
		flag2=0;
		Push_TX('A');
		Push_TX((char)((int)2 + 48));//es +49 pq queremos que subirle uno mas que la conversio a char
	}
}

/**
*	\fn       uint8_t Maquina_SetHora(char caracter)
*
*	\brief    Recibe de a un caracter y si se completa la secuencia correcta actualiza la hora del
*			  sistema.
*
*	\details  Maquina de 8 estados la secuencia correcta es "hh:mm:ss" ej: "22:55:33"
*			  donde hh es la hora actual, mm los minutos actuales y ss los segundos actuales.
*
*	\return	  uint8_t
*			  Devuelve 1 si se completo la secuencia de forma exitosa
*			  Devuelve 2 si hubo un error en la trama recibida
*			  Devuelve 0 si se encuentra en un paso intermedio
*
*	\author   Grupo 1
*/

uint8_t Maquina_SetHora(char caracter)
{
	static char hora[9]={0};
	static uint8_t estado=H0;
	switch(estado)
	{
		case H0:
			if((caracter>='0')&&(caracter<='9'))
			{
				hora[0]=caracter;
				estado=H1;
			}
			else
			{
				estado=H0;
				return 2;
			}
			break;
		case H1:
			if((caracter>='0')&&(caracter<='9'))
			{
				hora[1]=caracter;
				estado=H2;
			}
			else
			{
				estado=H0;
				return 2;
			}
			break;
		case H2:
			if(caracter==':')
			{
				hora[2]=caracter;
				estado=H3;
			}
			else
			{
				estado=H0;
				return 2;
			}
			break;
		case H3:
			if((caracter>='0')&&(caracter<='9'))
			{
				hora[3]=caracter;
				estado=H4;
			}
			else
			{
				estado=H0;
				return 2;
			}
			break;
		case H4:
			if((caracter>='0')&&(caracter<='9'))
			{
				hora[4]=caracter;
				estado=H5;
			}
			else
			{
				estado=H0;
				return 2;
			}
			break;
		case H5:
			if(caracter==':')
			{
				hora[5]=caracter;
				estado=H6;
			}
			else
			{
				estado=H0;
				return 2;
			}
			break;
		case H6:
			if((caracter>='0')&&(caracter<='9'))
			{
				hora[6]=caracter;
				estado=H7;
			}
			else
			{
				estado=H0;
				return 2;
			}
			break;
		case H7:
			if((caracter>='0')&&(caracter<='9'))
			{
				hora[7]=caracter;
				SetHora(hora);
				estado=H0;
				return 1;//!< Se completo la secuencia de forma correcta
			}
			else
			{
				estado=H0;
				return 2;
			}
			break;
	}
	return 0;
}

/**
*	\fn       uint8_t Maquina_SetFecha(char caracter)
*
*	\brief    Recibe de a un caracter y si se completa la secuencia correcta actualiza la hora del
*			  sistema.
*
*	\details  Maquina de 8 estados la secuencia correcta es "dd:mm:yy" ej: "03/11/16"
*			  donde dd es el día actual, mm el mes e yy el año.
*
*	\return	  uint8_t
*			  Devuelve 1 si se completo la secuencia de forma exitosa
*			  Devuelve 2 si hubo un error en la trama recibida
*			  Devuelve 0 si se encuentra en un paso intermedio
*
*	\author   Grupo 1
*/

uint8_t Maquina_SetFecha(char caracter)
{
	static char fecha[9]={0};
	static uint8_t estado=F0;
	switch(estado)
	{
		case F0:
			if((caracter>='0')&&(caracter<='9'))
			{
				fecha[0]=caracter;
				estado=F1;
			}
			else
			{
				estado=F0;
				return 2;
			}
			break;
		case F1:
			if((caracter>='0')&&(caracter<='9'))
			{
				fecha[1]=caracter;
				estado=F2;
			}
			else
			{
				estado=F0;
				return 2;
			}
			break;
		case F2:
			if(caracter=='/')
			{
				fecha[2]=caracter;
				estado=F3;
			}
			else
			{
				estado=F0;
				return 2;
			}
			break;
		case F3:
			if((caracter>='0')&&(caracter<='9'))
			{
				fecha[3]=caracter;
				estado=F4;
			}
			else
			{
				estado=F0;
				return 2;
			}
			break;
		case F4:
			if((caracter>='0')&&(caracter<='9'))
			{
				fecha[4]=caracter;
				estado=F5;
			}
			else
			{
				estado=F0;
				return 2;
			}
			break;
		case F5:
			if(caracter=='/')
			{
				fecha[5]=caracter;
				estado=F6;
			}
			else
			{
				estado=F0;
				return 2;
			}
			break;
		case F6:
			if((caracter>='0')&&(caracter<='9'))
			{
				fecha[6]=caracter;
				estado=F7;
			}
			else
			{
				estado=F0;
				return 2;
			}
			break;
		case F7:
			if((caracter>='0')&&(caracter<='9'))
			{
				fecha[7]=caracter;
				SetFecha(fecha);
				estado=F0;
				return 1;//!< Se completo la secuencia de forma correcta
			}
			else
			{
				estado=F0;
				return 2;
			}
			break;
	}
	return 0;
}

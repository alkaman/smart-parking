#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

/**
    \file mainwindow.cpp
    \brief Control acceso de vehículos de un garaje
    \details Trabajo Practico Obligatorio
    \author Trautman Marcos, Alan Kinast
    \date 2016.11.25
*/

int vectorLugares[8]={0};      //!<vector donde el micro me avisa que ubicacion esta libre y cual no
int vectorFlags[8]={0};         //!<vector donde el micro me avisa que codigos estan andando y cuales terminan
int vectorInhabili[8]={0};     //!<vector para inhabilitaciones
unsigned int vectorTiempos[8]={0};       //!<8 contadores que llevan la cuenta del tiempo de cada codigo
int libre=0;                    //!< variable que guardo proxima codigo libre. REEMPLAZAR POR PUNTERO
int ocupadasGlobal;             //!< variable que guardo cantidad de codigos activos
int inhabiliGlobal;
int vectorLocal[8]={0};


QTime tiempo; QString texto;    //!< variables globales para el reloj
QString fecha2;


char PuertoSerieRecepcion[100]={};  //!<Vector donde se ubica caracter por caracter recibido del puerto serie de la barrera de Entrada
char PuertoSerieRecepcion2[100]={};  //!<Vector donde se ubica caracter por caracter recibido del puerto serie de la barrera de Salida

int RX_Flag=0;  //!<Indice de ingreso en el vector PuertoSerieRecepcion de la barrera de entrada
int RX_Flag2=0; //!<Indice de ingreso en el vector PuertoSerieRecepcion2 de la barrera de salida
int flagOK_entrada=0;//!< mando LL hasta que recibo un ok del micro de entrada
int flagOK_salida=0;//!<Imando LL hasta que recibo un ok del micro de salida

int aux[8]={10,10,10,10,10,10,10,10};




/**
    \fn MainWindow (QWidget)
    \brief Constructor
    \details Inicia el timer, realiza los connects, busca puertos disponibles e inicializa el reloj
    \author Marcos Trautman, Alan Kinast
    \date 2016.11.25
    \return (void)
*/

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    //!<Timer
    ui->setupUi(this);
    my_timer= new QTimer (this);

    //!<Slots que se ejecutan con el vencimiento
    connect(my_timer,SIGNAL(timeout()),this,SLOT(Lugares()));
    connect(my_timer,SIGNAL(timeout()),this,SLOT(SumaTimer()));
    connect(my_timer,SIGNAL(timeout()),this,SLOT(Barrer()));
    connect(my_timer,SIGNAL(timeout()),this,SLOT(Mostrarlcd()));
    connect(my_timer,SIGNAL(timeout()),this,SLOT(Estadisticas()));
    connect(my_timer,SIGNAL(timeout()),this,SLOT(Reloj()));
    connect(my_timer,SIGNAL(timeout()),this,SLOT(Activos()));
    connect(my_timer,SIGNAL(timeout()),this,SLOT(LL_entrada()));
    connect(my_timer,SIGNAL(timeout()),this,SLOT(LL_salida()));

    //!<Conteo de a 1000 milisegundos
    my_timer->start(1000);
    Reloj();  //!< Inicializo fecha y hora


    //!<Puerto Serie
    puerto=NULL;
    puerto2=NULL;

    QList<QSerialPortInfo> ports= QSerialPortInfo::availablePorts();

    qDebug() <<"Availableports:"<<ports.size();

    //!<Reseteo Combobox
    ui->comboBox_PuertoSerie->clear();
    ui->comboBox_PuertoSerie_marcos->clear();

    for(int i=0;i<ports.size();i++)
    {
        //!<Agrego item al combobox
        ui->comboBox_PuertoSerie->addItem(ports.at(i).portName());
        ui->comboBox_PuertoSerie_marcos->addItem(ports.at(i).portName());

        //!<Lo muestro por consola de Debug
        qDebug() <<"Descripcion:"<<ports.at(i).description();
        qDebug() <<"Manufacturer:"<<ports.at(i).manufacturer();
        qDebug() <<"SerialNumber:"<<ports.at(i).serialNumber();
        qDebug() <<"ProductIdentifier:"<<ports.at(i).productIdentifier();
    }

    //!<Lectura buckup

    char String[150]={0},aux[150]={0};
    char aux_horario[10]={0},aux_fecha[10]={0};
    char cochera_aux[2]={0};
    QString cochera;
    int cochera_numero;
    int i=0,j,k;
    unsigned int hora,min,seg,dia,diaactual,seg_actual;

    PrimeraLectura.open("Activos.txt", std::fstream::out | std::fstream::app);//!<Apertura Archivo
    if(PrimeraLectura.good())//!<Chequeo el estado de PrimeraLectura
    {
        while(!PrimeraLectura.eof())//!<Cargo en String los caracteres del archivo
        {
            PrimeraLectura >> aux;
            strcat(String,aux);//!< Concatena el reglon cargado en aux sobre String
        }
        PrimeraLectura.close();
        if(String[0]!=0)//!<Chequeo de que el archivo no este vacio
        {
            for(i=0;i<8;i++)//!<"descifrado" del archivo
            {
                if((String[1+(18*i)]!='l')&&(String[1+(18*i)]!='i'))//!< Si no esta libre ni inhabilitado, entonces ocupado
                {
                    for(k=0,j=1+18*i;j<18+18*i;j++,k++)//!< Cargo fecha y horario de ingreso en aux
                    {
                        aux[k]=String[j];
                    }
                    aux[k-9]='\0';
                    aux[k]='\0';
                    for(j=0;j<8;j++)//copio el horario
                    {
                        aux_horario[j]=aux[j];
                    }
                    for(j=9,k=0;j<18;j++,k++)//copio la fecha
                    {
                        aux_fecha[k]=aux[j];
                    }



                    switch(i)//!<Cargo la hora en el qlabel de la interfaz gráfica
                    {
                        case 0:
                            ui->label_00_hora->setText(aux_horario);
                            ui->label_00_dia->setText(aux_fecha);
                            break;
                        case 1:
                            ui->label_01_hora->setText(aux_horario);
                            ui->label_01_dia->setText(aux_fecha);
                            break;
                        case 2:
                            ui->label_02_hora->setText(aux_horario);
                            ui->label_02_dia->setText(aux_fecha);
                            break;
                        case 3:
                            ui->label_03_hora->setText(aux_horario);
                            ui->label_03_dia->setText(aux_fecha);
                            break;
                        case 4:
                            ui->label_04_hora->setText(aux_horario);
                            ui->label_04_dia->setText(aux_fecha);
                            break;
                        case 5:
                            ui->label_05_hora->setText(aux_horario);
                            ui->label_05_dia->setText(aux_fecha);
                            break;
                        case 6:
                            ui->label_06_hora->setText(aux_horario);
                            ui->label_06_dia->setText(aux_fecha);
                            break;
                        case 7:
                            ui->label_07_hora->setText(aux_horario);
                            ui->label_07_dia->setText(aux_fecha);
                            break;
                    }
                    //aux_fecha[2]='\0';
                    dia=(atoi(&aux_fecha[0]));
                    diaactual=(atoi(fecha2.toStdString().c_str()));
                    dia=  diaactual-dia;

                    //!<Conversion de hora a entero
                    hora=(unsigned int)(atoi(&aux[0]));
                    min=(unsigned int)(atoi(&aux[3]));
                    seg=(unsigned int)(atoi(&aux[6]));

                    seg=seg+(60*min)+(3600*hora);//!< Guardo en seg la cantidad en segundos del horario que levante del archivo
                    seg_actual=tiempo.second()+(60*tiempo.minute())+(3600*tiempo.hour());//!< Cantidad en segundos del horario actual

                    if(seg_actual >= seg)
                    {
                        seg=seg_actual-seg;
                        hora=seg/3600;
                        min=(seg-3600*hora)/60;
                        seg=seg-((3600*hora)+(60*min));
                    }
                    else
                    {
                        //!<86400seg=24h
                        seg=86400-seg+seg_actual;
                        hora=seg/3600;
                        min=(seg-3600*hora)/60;
                        seg=seg-((3600*hora)+(60*min));
                    }
                    vectorTiempos[i]=(hora*3600)+(min*60)+seg;//!<Cargo la hora en el vector de tiempos
                    vectorFlags[i]=1;//!<Activo el conteo para el codigo correspondiente

                }
                //else//!<Si la posicion estaba libre
                if(String[1+(18*i)]=='l')
                {
                    TimerOff(i);
                }
                if(String[1+(18*i)]=='i')//!< Si la posicion estaba inhabilitada
                {
                    cochera_numero=atoi(&String[1+(18*i)+14]);
                    qDebug()<< cochera_numero;
                    itoa(cochera_numero,&cochera_aux[1],10);
                    qDebug()<< cochera_aux;
                    cochera.fromStdString(cochera_aux);
                    qDebug()<< cochera;
                    Inhabilitar_archivo(i,cochera_numero);
                }
            }
            Activos();//!<Llamo al metodo para hacer una nueva copia
        }
    }
}

/**
    \fn ~MainWindow (QWidget)
    \brief Destructor
    \details Cierra la interfaz grafica, los archivos y libera memoria de los punteros
    \author Marcos Trautman, Alan Kinast
    \date 2016.11.25
    \return (void)
*/

MainWindow::~MainWindow()
{
    delete ui;
    Activos ();
    fs.close();

    PrimeraLectura.close();
    delete my_timer;
    delete puerto;
    delete puerto2;
}

/**
    \fn  void Estadisticas (void)
    \brief Control del panel de estadisticas
    \details Funcion que barre los vectores de ocupacion e inhabilitacion para saber sus estados
             y los muestra en el panel de estadisticas.
    \author Marcos Trautman, Alan Kinast
    \date 2016.11.25
    \return (void)
*/

void MainWindow:: Estadisticas (void)
{
    int i;
    int libres=0; int ocupadas=0; int inhabilitadas = 0;
    for (i=0;i<8;i++)
    {
        if(vectorFlags[i]==0)
            libres++;

        if (vectorInhabili[i]==1)
            inhabilitadas++;

        ocupadas=8-libres - inhabilitadas;

        ui->lcd_libres->display(libres);
        ui->lcd_ocupadas->display(ocupadas);
        ui->lcd_inhabilitadas->display(inhabilitadas);
    }
    ocupadasGlobal=ocupadas;

    inhabiliGlobal=inhabilitadas;




}

/**
    \fn  void Reloj (void)
    \brief hora y fecha real
    \details Funcion que se encarga de mostrar Fecha y Hora reales
    \author Marcos Trautman, Alan Kinast
    \date 2016.11.25
    \return (void)
*/

void MainWindow:: Reloj (void)
{
    QDate fecha;


    fecha=QDate::currentDate();
    fecha2= fecha.toString("dd/MM/yy");
    ui->label_fecha->setText(fecha2);


    tiempo = QTime::currentTime();
    texto = tiempo.toString("hh:mm:ss");

    ui->lcd_reloj->display(texto);
}

/**
    \fn  void GuardaBorra (char)
    \brief Borra los tiempos y libera la ocupacion del timer que corresponda
    \details Pone a cero el tiempo de estadia y libera la ocupacion del codigo que se le diga
    \author Marcos Trautman, Alan Kinast
    \date 2016.11.25
    \return (void)
*/

void MainWindow:: GuardaBorra (char objetivo)//Ver de cambiar por un switch case
{
    if(objetivo==0)
    {
        vectorTiempos[int(objetivo)]=0;
        vectorFlags[0]=0;
        ui->label_00_hora->setText("");
        ui->label_00_dia->setText("");
    }
    if(objetivo==1)
    {
         vectorTiempos[int(objetivo)]=0;
         vectorFlags[1]=0;
         ui->label_01_hora->setText("");
         ui->label_01_dia->setText("");
    }
    if(objetivo==2)
    {
         vectorTiempos[int(objetivo)]=0;
         vectorFlags[2]=0;
         ui->label_02_hora->setText("");
         ui->label_02_dia->setText("");
    }
    if(objetivo==3)
    {
         vectorTiempos[int(objetivo)]=0;
         vectorFlags[3]=0;
         ui->label_03_hora->setText("");
         ui->label_03_dia->setText("");
    }
    if(objetivo==4)
    {
         vectorTiempos[int(objetivo)]=0;
         vectorFlags[4]=0;
         ui->label_04_hora->setText("");
         ui->label_04_dia->setText("");
    }
    if(objetivo==5)
    {
         vectorTiempos[int(objetivo)]=0;
         vectorFlags[5]=0;
         ui->label_05_hora->setText("");
         ui->label_05_dia->setText("");
    }
    if(objetivo==6)
    {
         vectorTiempos[int(objetivo)]=0;
         vectorFlags[6]=0;
         ui->label_06_hora->setText("");
         ui->label_06_dia->setText("");
    }
    if(objetivo==7)
    {
         vectorTiempos[int(objetivo)]=0;
         vectorFlags[7]=0;
         ui->label_07_hora->setText("");
         ui->label_07_dia->setText("");
    }
}

/**
    \fn  void Mostrarlcd (void)
    \brief muestra tiempos por lcd
    \details Funcion que controla los lcd de los 8 codigos, mostrando los tiempos actuales de cada uno
    \author Marcos Trautman, Alan Kinast
    \date 2016.11.25
    \return (void)
*/

void MainWindow :: Mostrarlcd (void)
{
    unsigned int seg, min, hora, dia;


        dia=  (vectorTiempos [0]/86400);
        hora= ((unsigned int)(vectorTiempos [0] / 3600));
        min= (unsigned int)((vectorTiempos [0] - hora * 3600) / 60);
        seg=  vectorTiempos [0] - (hora * 3600 + min * 60);

        ui->lcd_00_seg->display((int)seg);
        ui->lcd_00_min->display((int)min);
        ui->lcd_00_horas->display((int)hora);
        ui->lcd_00_dias->display((int)dia);

        dia=  (vectorTiempos [1]/86400);
        hora= (unsigned int)(vectorTiempos [1] / 3600);
        min= (unsigned int)((vectorTiempos [1] - hora * 3600) / 60);
        seg=  vectorTiempos [1] - (hora * 3600 + min * 60);

        ui->lcd_01_seg->display((int)seg);
        ui->lcd_01_min->display((int)min);
        ui->lcd_01_horas->display((int)hora);
        ui->lcd_01_dias->display((int)dia);

        dia=  (vectorTiempos [2]/86400);
        hora= (unsigned int)(vectorTiempos [2] / 3600);
        min= (unsigned int)((vectorTiempos [2] - hora * 3600) / 60);
        seg=  vectorTiempos [2] - (hora * 3600 + min * 60);

        ui->lcd_02_seg->display((int)seg);
        ui->lcd_02_min->display((int)min);
        ui->lcd_02_horas->display((int)hora);
        ui->lcd_02_dias->display((int)dia);

        dia=  (vectorTiempos [3]/86400);
        hora= (unsigned int)(vectorTiempos [3] / 3600);
        min= (unsigned int)((vectorTiempos [3] - hora * 3600) / 60);
        seg=  vectorTiempos [3] - (hora * 3600 + min * 60);

        ui->lcd_03_seg->display((int)seg);
        ui->lcd_03_min->display((int)min);
        ui->lcd_03_horas->display((int)hora);
        ui->lcd_03_dias->display((int)dia);

        dia=  (vectorTiempos [4]/86400);
        hora= (unsigned int)(vectorTiempos [4] / 3600);
        min= (unsigned int)((vectorTiempos [4] - hora * 3600) / 60);
        seg=  vectorTiempos [4] - (hora * 3600 + min * 60);

        ui->lcd_04_seg->display((int)seg);
        ui->lcd_04_min->display((int)min);
        ui->lcd_04_horas->display((int)hora);
        ui->lcd_04_dias->display((int)dia);

        dia=  (vectorTiempos [5]/86400);
        hora= (unsigned int)(vectorTiempos [5] / 3600);
        min= (unsigned int)((vectorTiempos [5] - hora * 3600) / 60);
        seg=  vectorTiempos [5] - (hora * 3600 + min * 60);

        ui->lcd_05_seg->display((int)seg);
        ui->lcd_05_min->display((int)min);
        ui->lcd_05_horas->display((int)hora);
        ui->lcd_05_dias->display((int)dia);

        dia=  (vectorTiempos [6]/86400);
        hora= (unsigned int)(vectorTiempos [6] / 3600);
        min= (unsigned int)((vectorTiempos [6] - hora * 3600) / 60);
        seg=  vectorTiempos [6] - (hora * 3600 + min * 60);

        ui->lcd_06_seg->display((int)seg);
        ui->lcd_06_min->display((int)min);
        ui->lcd_06_horas->display((int)hora);
        ui->lcd_06_dias->display((int)dia);

        dia=  (vectorTiempos [7]/86400);
        hora= (unsigned int)(vectorTiempos [7] / 3600);
        min= (unsigned int)((vectorTiempos [7] - hora * 3600) / 60);
        seg=  vectorTiempos [7] - (hora * 3600 + min * 60);

        ui->lcd_07_seg->display((int)seg);
        ui->lcd_07_min->display((int)min);
        ui->lcd_07_horas->display((int)hora);
        ui->lcd_07_dias->display((int)dia);
}

/**
    \fn  void Barrer (void)
    \brief barre el vector de flags y me deja apuntado el primer lugar libre
    \details Funcion que me deja apuntado el proximo codigo libre a ser entregado
    \author Marcos Trautman, Alan Kinast
    \date 2016.11.25
    \return (void)
*/

void MainWindow:: Barrer (void) // barre el vector de flags y me deja apuntado el primer lugar libre
{
    int i;
    for (i=0;i<8;i++)
    {
       if(vectorFlags[i]==0)//!<si esa posicion del vector esta libre,lo dejo apuntado
       {
           libre=i;
           ui->label_pantalla->setText("");
           return;//!<dejo apuntado y salgo de la función
       }
    }
    ui->label_pantalla->setText("NO HAY MAS LUGAR");
}

/**
    \fn  void SumaTimer (void)
    \brief Aumenta un segundo en los tiempos
    \details Funcion que suma un segundo al tiempo de estadia de los codigos que corresponda
    \author Marcos Trautman, Alan Kinast
    \date 2016.11.25
    \return (void)
*/
void MainWindow:: SumaTimer (void)
{
    int i;
    for(i=0;i<8;i++)
    {
        if (vectorFlags[i]==1)//si ese codigo esta activo
        {
            vectorTiempos[i]++;
        }
    }
}

/**
    \fn  void Lugares (void)
    \brief Pone los frames en rojo o verde
    \details Funcion que barre vectorLugares. si esta ocupado, pone el frame en rojo
    \author Marcos Trautman, Alan Kinast
    \date 2016.11.25
    \return (void)
*/



void MainWindow::Lugares (void)
{
    int i;


    for(i=0;i<8;i++)
    {
        if(vectorInhabili[i]==0)
        {
            if(vectorLugares[i]==1)//!< si esta ocupado lo pongo en rojo
            {
                    if (i==0)
                    {
                         ui->frame_A1->setStyleSheet("background-color:red;");

                    }

                    if (i==1)
                    {
                         ui->frame_A2->setStyleSheet("background-color:red;");

                    }
                    if (i==2)
                    {
                         ui->frame_A3->setStyleSheet("background-color:red;");

                    }
                    if (i==3)
                    {
                         ui->frame_A4->setStyleSheet("background-color:red;");

                    }
                    if (i==4)
                    {
                         ui->frame_A5->setStyleSheet("background-color:red;");

                    }
                    if (i==5)
                    {
                         ui->frame_A6->setStyleSheet("background-color:red;");

                    }
                    if (i==6)
                    {
                         ui->frame_A7->setStyleSheet("background-color:red;");

                    }
                    if (i==7)
                    {
                         ui->frame_A8->setStyleSheet("background-color:red;");

                    }
            }

            if(vectorLugares[i]==0)//!< si esta libre lo pongo verde
            {

                if (i==0)
                {
                     ui->frame_A1->setStyleSheet("background-color:green;");

                }
                if (i==1)
                {
                     ui->frame_A2->setStyleSheet("background-color:green;");

                }
                if (i==2)
                {
                     ui->frame_A3->setStyleSheet("background-color:green;");

                }
                if (i==3)
                {
                     ui->frame_A4->setStyleSheet("background-color:green;");

                }
                if (i==4)
                {
                     ui->frame_A5->setStyleSheet("background-color:green;");

                }
                if (i==5)
                {
                     ui->frame_A6->setStyleSheet("background-color:green;");

                }
                if (i==6)
                {
                     ui->frame_A7->setStyleSheet("background-color:green;");

                }
                if (i==7)
                {
                     ui->frame_A8->setStyleSheet("background-color:green;");

                }

            }
        }//!<fin if inhabilita

       if(vectorInhabili[i]==1)//!<si esta inhabilitado pongo en amarillo
        {
            if (i==0)
                 ui->frame_A1->setStyleSheet("background-color:yellow;");
            if (i==1)
                 ui->frame_A2->setStyleSheet("background-color:yellow;");
            if (i==2)
                 ui->frame_A3->setStyleSheet("background-color:yellow;");
            if (i==3)
                 ui->frame_A4->setStyleSheet("background-color:yellow;");
            if (i==4)
                 ui->frame_A5->setStyleSheet("background-color:yellow;");
            if (i==5)
                 ui->frame_A6->setStyleSheet("background-color:yellow;");
            if (i==6)
                 ui->frame_A7->setStyleSheet("background-color:yellow;");
            if (i==7)
                 ui->frame_A8->setStyleSheet("background-color:yellow;");
        }
    }

}

/**
    \fn  void on_pushButton_PuertoSerie_clicked (void)
    \brief Conecta con Puerto Serie
    \details Funcion que conecta con el COM seleccionado en la combobox
    \author Marcos Trautman, Alan Kinast
    \date 2016.11.25
    \return (void)
*/

void MainWindow::on_pushButton_PuertoSerie_clicked()
{
    if(!puerto)
     {
         puerto= new QSerialPort(ui->comboBox_PuertoSerie->currentText());


             puerto->setBaudRate(QSerialPort::Baud9600);
             puerto->setDataBits(QSerialPort::Data8);
             puerto->setFlowControl(QSerialPort::NoFlowControl);
             puerto->setStopBits(QSerialPort::OneStop);
             puerto->setParity(QSerialPort::NoParity);

             if(puerto->open(QIODevice::ReadWrite)==true)
             {
                 ui->label_PuertoSerie->setStyleSheet("font-weight: bold; color: red;");
                 ui->label_PuertoSerie->setText("CONECTADO");


                 connect(puerto, SIGNAL(readyRead()),this,SLOT(PuertoSerie_Recepcion()));
             }
     }

    else
    {
        ui->label_PuertoSerie->setStyleSheet("font: 8pt MS Shell Dlg 2;color: rgb(0, 0, 0);");
        ui->label_PuertoSerie->setText("DESCONECTADO");
         flagOK_entrada=0;

        puerto->close();

        puerto=NULL;
    }
}

/**
    \fn  void PuertoSerie_Recepcion (void)
    \brief Guarda lo recibido en bytes
    \details Funcion que almacena lo recibido por Puerto en Bytes
    \author Marcos Trautman, Alan Kinast
    \date 2016.11.25
    \return (void)
*/

void MainWindow::PuertoSerie_Recepcion()
{
    QByteArray bytes;
    int cant= puerto->bytesAvailable();     //analizo datos disponibles en el buffer de Rx
    bytes.resize(cant);                   //Redimensiono el QbyteArray considerando '\0'
    QByteArray send;

    puerto->read(bytes.data(),bytes.size());  //Leo y lo guarda en el QbyteArray
                                             //data() devuelve un char*

    ui->plainTextEdit_PuertoSerie->appendPlainText(bytes.data());
    ui->plainTextEdit_PuertoSerie->moveCursor(QTextCursor::End);

    PuertoSerie_Pop_Rx(bytes);

    ui->label_PuertoSerie_2->setText(QString::number(RX_Flag));
    ui->label_PuertoSerie_3->setText(QString(PuertoSerieRecepcion[RX_Flag]));
    ui->plainTextEdit_PuertoSerie_2->appendPlainText("pto serie recepcion() llama a desentramado_entrada");
    PuertoSerie_Desentramado_Entrada();

}

/**
    \fn  void PuertoSerie_Pop_Rx (QByteArray)
    \brief Funcion que almacena Bytes en PuertoSerieRecepcion
    \details Lo que tengo en bytes lo guarda en vector PuertoSerieRecepcion[]
    \author Marcos Trautman, Alan Kinast
    \date 2016.11.25
    \return (void)
*/

void MainWindow::PuertoSerie_Pop_Rx(QByteArray bytes)
{
    int j;

    if(RX_Flag>=100)
    {
        RX_Flag=0;
    }
    for(j=0;j<bytes.size();j++)
    {

        if((bytes.data()[j]!='\n')&&(bytes.data()[j]!='\0')&&(bytes.data()[j]!=' '))
        {

            PuertoSerieRecepcion[RX_Flag]=(bytes.data()[j]);
            ui->plainTextEdit_PuertoSerie_2->appendPlainText(&PuertoSerieRecepcion[RX_Flag]);
            ui->plainTextEdit_PuertoSerie_2->moveCursor(QTextCursor::End);
            RX_Flag++;//solo sumo cuando cargo un caracter
            if(RX_Flag>=100)
            {
                RX_Flag=0;
            }

        }
    }
}


/**
    \fn  void PuertoSerie_Desentramado_Entrada (void)
    \brief Analiza la trama recibida por puerto serie de la placa de la barrera de entrada
    \details  Funcion que procesa el string recibido: si recibo E1, comienza el timer 1. Si recibo S1, finaliza el timer 1
    \author Marcos Trautman, Alan Kinast
    \date 2016.11.25
    \return (void)
*/

void MainWindow:: PuertoSerie_Desentramado_Entrada()
{
    static int RX_DESENTRAMADO=0;
    static int estado=ESTADO0;
    int codigo,posicion;

    if(RX_DESENTRAMADO>=100)//!< si se pasa del máximo del vector  resetea
    {
        RX_DESENTRAMADO=0;
    }


    while(RX_DESENTRAMADO!=RX_Flag)//!< Solo accedo si son distintos, RX_FLAG es 
    {
        switch(estado)
        {

            case ESTADO0:
                if(PuertoSerieRecepcion[RX_DESENTRAMADO]=='E')
                {
                    estado=ESTADO1;
                }
                if(PuertoSerieRecepcion[RX_DESENTRAMADO]=='A')
                {
                    estado=ESTADO2;
                }
                if(PuertoSerieRecepcion[RX_DESENTRAMADO]=='J')
                 {
                    estado= ESTADO3;
                 }
                if(PuertoSerieRecepcion[RX_DESENTRAMADO]=='O')
                 {
                    estado= ESTADO4;
                 }
                break;

            case ESTADO1:
                codigo=atoi(&PuertoSerieRecepcion[RX_DESENTRAMADO]);
                TimerOn(codigo);
                EnviaIngreso(codigo);
                estado=ESTADO0;
                break;
            case ESTADO2:
                posicion=atoi(&PuertoSerieRecepcion[RX_DESENTRAMADO]);
                EstacionamientoSet(posicion);
                estado=ESTADO0;
                break;

            case ESTADO3:
                if(PuertoSerieRecepcion[RX_DESENTRAMADO]=='J')
                 {
                    altanto_entrada();
                    estado=ESTADO0;
                 }
                 if(PuertoSerieRecepcion[RX_DESENTRAMADO]!='J')
                     estado=ESTADO0;
            break;
        case ESTADO4:
            if(PuertoSerieRecepcion[RX_DESENTRAMADO]=='K')
             {
                flagOK_entrada=1;//dejo de mandar LL
                estado=ESTADO0;
             }
             if(PuertoSerieRecepcion[RX_DESENTRAMADO]!='K')
                 estado=ESTADO0;
            break;

                default:
                    estado=ESTADO0;
                    break;
        }
        RX_DESENTRAMADO++;
        if(RX_DESENTRAMADO>=100)//!< si se pasa del máximo del vector  resetea
        {
            RX_DESENTRAMADO=0;
        }

    }
}

/**
    \fn  void TimerOn(int codigo)
    \brief Analiza la trama recibida por puerto serie de la placa de la barrera de entrada
    \details  Funcion que procesa el string recibido: si recibo E1, comienza el timer 1. Si recibo S1, finaliza el timer 1
    \author Marcos Trautman, Alan Kinast
    \date 2016.11.25
    \return (void)
*/

void MainWindow::TimerOn(int codigo)
{
    vectorFlags[codigo]=1;//!<Activo el codigo para el timer

    switch(codigo)//!< pongo a disposicion la informacion del ingreso a los labels correspondientes
    {
    case 0:
        ui->label_00_hora->setText(texto);
        ui->label_00_dia->setText(ui->label_fecha->text());
        break;
    case 1:
        ui->label_01_hora->setText(texto);
        ui->label_01_dia->setText(ui->label_fecha->text());
        break;
    case 2:
        ui->label_02_hora->setText(texto);
        ui->label_02_dia->setText(ui->label_fecha->text());
        break;
    case 3:
        ui->label_03_hora->setText(texto);
        ui->label_03_dia->setText(ui->label_fecha->text());
        break;
    case 4:
        ui->label_04_hora->setText(texto);
        ui->label_04_dia->setText(ui->label_fecha->text());
        break;
    case 5:
        ui->label_05_hora->setText(texto);
        ui->label_05_dia->setText(ui->label_fecha->text());
        break;
    case 6:
        ui->label_06_hora->setText(texto);
        ui->label_06_dia->setText(ui->label_fecha->text());
        break;
    case 7:
        ui->label_07_hora->setText(texto);
        ui->label_07_dia->setText(ui->label_fecha->text());
        break;
    }
}

/**
    \fn  void MainWindow::EnviaIngreso(int)
    \brief Envia por puerto serie a la placa de salida el codigo que ingreso
    \details  Recibe el codigo a notificar a la placa de salida
    \author Marcos Trautman, Alan Kinast
    \date 2016.11.25
    \return (void)
*/

void MainWindow::EnviaIngreso(int codigo)
{
    QByteArray send;
    if(puerto2!=NULL)
    {
        send.resize(2);
        send.data()[0]='E';
        send.data()[1]=(char)((int)codigo + 48);
        puerto2->write(send);
    }
}


/**
    \fn void EstacionamientoSet(int)
    \brief modifica frames de ocupacion
    \details Recibe del 1 al 8 que sensor de ocupacion se activo, comprueba conndiciones y modifica frames
    \author Marcos Trautman, Alan Kinast
    \date 2016.11.25
    \return (void)
*/
void MainWindow::EstacionamientoSet(int Posicion)//recibe del 1 al 8 de desentramado_entrada
{
    int i;
    int LugaresOcupados=0;

    for(i=0;i<8;i++)//!<Conteo de cantidad cocheras ocupadas
    {
        if(vectorLugares[i]==1)
        {
            LugaresOcupados++;
        }
    }

    if(vectorLugares[Posicion-1]==0)//!< Si voy a ocupar la posicion
    {
        if(LugaresOcupados>=ocupadasGlobal)//!< Y ademas la cantidad de lugares ocupados es igual o supera a la cantidad de codigos activos
            return;

    }

        if(vectorInhabili[Posicion-1]==0)//!< chequeo que no este inhabilitada la cochera a ocupar/desocupar
        {
            switch(Posicion)
            {
            case 1:
                on_push_A1_clicked();
                break;
            case 2:
                on_push_A2_clicked();
                break;
            case 3:
                on_push_A3_clicked();
                break;
            case 4:
                on_push_A4_clicked();
                break;
            case 5:
                on_push_A5_clicked();
                break;
            case 6:
                on_push_A6_clicked();
                break;
            case 7:
                on_push_A7_clicked();
                break;
            case 8:
                on_push_A8_clicked();
                break;
            }
        }
    //}
}


/**
    \fn  void PuertoSerie_Recepcion2 (void)
    \brief Guarda lo recibido en bytes2
    \details Funcion que almacena lo recibido por Puerto2 en Bytes2
    \author Marcos Trautman, Alan Kinast
    \date 2016.11.25
    \return (void)
*/

void MainWindow::PuertoSerie_Recepcion2()
{
    QByteArray bytes2;
    int cant= puerto2->bytesAvailable();     //analizo datos disponibles en el buffer de Rx
    bytes2.resize(cant);                   //Redimensiono el QbyteArray considerando '\0'
    QByteArray send;

    puerto2->read(bytes2.data(),bytes2.size());  //Leo y lo guarda en el QbyteArray
                                             //data() devuelve un char*




    ui->plainTextEdit_PuertoSerie_marcos->appendPlainText(bytes2.data());
    ui->plainTextEdit_PuertoSerie_marcos->moveCursor(QTextCursor::End);
    PuertoSerie_Pop_Rx2(bytes2);

    ui->plainTextEdit_PuertoSerie_2->appendPlainText("pto serie recepcion2() llama a desentramado");
    PuertoSerie_Desentramado_Salida();

}

/**
    \fn  void PuertoSerie_Pop_Rx2 (QByteArray)
    \brief Funcion que almacena Bytes2 en PuertoSerieRecepcion2
    \details Lo que tengo en bytes2 lo guarda en vector PuertoSerieRecepcion2[]
    \author Marcos Trautman, Alan Kinast
    \date 2016.11.25
    \return (void)
*/


void MainWindow:: PuertoSerie_Pop_Rx2(QByteArray bytes2)

{
    int j;

    if(RX_Flag2>=100)
    {
        RX_Flag2=0;
    }

    for(j=0;j<bytes2.size();j++)
    {

        if((bytes2.data()[j]!='\n')&&(bytes2.data()[j]!='\0')&&(bytes2.data()[j]!=' '))
        {

            PuertoSerieRecepcion2[RX_Flag2]=(bytes2.data()[j]);

            RX_Flag2++;//solo sumo cuando cargo un caracter
            if(RX_Flag2>=100)
            {
                RX_Flag2=0;
            }

        }
    }
}



/**
    \fn  void PuertoSerie_Desentramado_Salida()
    \brief Analiza la trama recibida por puerto serie de la placa de la barrera de entrada
    \details  Funcion que procesa el string recibido: si recibo E1, comienza el timer 1. Si recibo S1, finaliza el timer 1
    \author Marcos Trautman, Alan Kinast
    \date 2016.11.25
    \return (void)
*/

void MainWindow::PuertoSerie_Desentramado_Salida()
{
    static int RX_DESENTRAMADO2=0;
    static int estado=ESTADO0;
    int codigo;

    if(RX_DESENTRAMADO2>=100)//!< si se pasa del máximo del vector  resetea
    {
        RX_DESENTRAMADO2=0;
    }


    while(RX_DESENTRAMADO2!=RX_Flag2)//!< Solo accedo si son distintos, RX_FLAG es
    {
        switch(estado)
        {

            case ESTADO0:
                if(PuertoSerieRecepcion2[RX_DESENTRAMADO2]=='S')
                {
                    estado=ESTADO1;
                }

                if(PuertoSerieRecepcion2[RX_DESENTRAMADO2]=='N')
                {

                    estado=ESTADO2;

                }
                if(PuertoSerieRecepcion2[RX_DESENTRAMADO2]=='O')
                {

                    estado=ESTADO3;

                }

                break;
            case ESTADO1:
                codigo=atoi(&PuertoSerieRecepcion2[RX_DESENTRAMADO2]);

                TimerOff(codigo);
                EnviaEgreso(codigo);
                estado=ESTADO0;
                break;
            case ESTADO2:
                if(PuertoSerieRecepcion2[RX_DESENTRAMADO2]=='N')
                 {

                    altanto_salida();
                    estado=ESTADO0;
                 }
                if(PuertoSerieRecepcion2[RX_DESENTRAMADO2]!='N')
                    estado=ESTADO0;
            break;
        case ESTADO3:


            if(PuertoSerieRecepcion2[RX_DESENTRAMADO2]=='K')
             {

                flagOK_salida=1;
                estado=ESTADO0;
             }
            if(PuertoSerieRecepcion2[RX_DESENTRAMADO2]!='K')
                estado=ESTADO0;
            break;



            default:
                estado=ESTADO0;
                break;
        }
        RX_DESENTRAMADO2++;
        if(RX_DESENTRAMADO2>=100)//!< si se pasa del máximo del vector  resetea
        {
            RX_DESENTRAMADO2=0;
        }

    }
}

/**
    \fn  void TimerOff(int codigo)
    \brief Da por finalizado el timer del codigo que se le pasa como argumento
    \details  Funcion que procesa el string recibido: si recibo E1, comienza el timer 1. Si recibo S1, finaliza el timer 1
    \author Marcos Trautman, Alan Kinast
    \date 2016.11.25
    \return (void)
*/

void MainWindow::TimerOff(int codigo)
{
    GuardaBorra(codigo);

}

/**
    \fn  void EnviaEgreso (int)
    \brief avisa que un codigo se fue
    \details  Funcion  que envia a la placa de entrada los codigos que quedan libres
    \author Marcos Trautman, Alan Kinast
    \date 2016.11.25
    \return (void)
*/
void MainWindow::EnviaEgreso(int codigo)
{
    QByteArray send;
    if(puerto!=NULL)
    {
        send.resize(2);
        send.data()[0]='S';
        send.data()[1]=(char)((int)codigo + 48);
        puerto->write(send);
    }
}

/**
    \fn  void on_pushButton_PuertoSerie_marcos_clicked (void)
    \brief Conecta con Puerto Serie
    \details Funcion que conecta con el COM seleccionado en la combobox
    \author Marcos Trautman, Alan Kinast
    \date 2016.11.25
    \return (void)
*/

void MainWindow::on_pushButton_PuertoSerie_marcos_clicked()
{
    if(!puerto2)
     {
         puerto2= new QSerialPort(ui->comboBox_PuertoSerie_marcos->currentText());


             puerto2->setBaudRate(QSerialPort::Baud9600);
             puerto2->setDataBits(QSerialPort::Data8);
             puerto2->setFlowControl(QSerialPort::NoFlowControl);
             puerto2->setStopBits(QSerialPort::OneStop);
             puerto2->setParity(QSerialPort::NoParity);

             if(puerto2->open(QIODevice::ReadWrite)==true)
             {
                 ui->label_PuertoSerie_marcos->setStyleSheet("font-weight: bold; color: red;");
                 ui->label_PuertoSerie_marcos->setText("CONECTADO");


                 connect(puerto2, SIGNAL(readyRead()),this,SLOT(PuertoSerie_Recepcion2()));
             }
     }

    else
    {
        ui->label_PuertoSerie_marcos->setStyleSheet("font: 8pt MS Shell Dlg 2;color: rgb(0, 0, 0);");
        ui->label_PuertoSerie_marcos->setText("DESCONECTADO");
        flagOK_salida=0;

        puerto2->close();

        puerto2=NULL;
    }
}

/**
    \fn  void Inhabilitar_archivo(int codigo, int cochera)
    \brief Inhabilita Cocheras y codigo correspondiente en el startup
    \details Ingresando el codigo y cochera correspondiente
    \author Marcos Trautman, Alan Kinast
    \date 2016.11.25
    \return (void)
*/

void MainWindow::Inhabilitar_archivo(int codigo, int cochera)
{
    vectorInhabili[cochera-1]=1; //!< que cochera esta inhabilitada
    aux[cochera-1]=codigo;
    vectorFlags[codigo]=2;
    vectorLocal[cochera-1]=1;
}

/**
    \fn  void Inhabilitar (QString)
    \brief Inhabilita Cocheras
    \details Ingresando el nombre de la cochera se la inhabilita para su uso
    \author Marcos Trautman, Alan Kinast
    \date 2016.11.25
    \return (void)
*/

void MainWindow::Inhabilitar(QString opcion)
{
    //static int vectorLocal[8]={0};
    //static int vectorLocal[8]={0};

    char opcion_aux[2]={0};
    int cochera;

    strcpy(opcion_aux,opcion.toStdString().c_str());

    cochera=atoi(&opcion_aux[1]);

    qDebug()<<"cochera vale: "<<cochera;


    if(((inhabiliGlobal+ocupadasGlobal)<8) ||(vectorInhabili[cochera-1]==1) )
    {
        if(opcion == "A1")
        {
               if(vectorLocal[0]==0)//si esta disponible lo inhabilito
                        {

                            vectorInhabili[0]=1;
                            vectorLocal[0]=1;
                            aux[0]=libre;
                            vectorFlags[libre]=2;//anulo un codigo

                            mandainhabili_entrada(aux[0]);
                            mandainhabili_salida(aux[0]);
                            return;
                        }
                if (vectorLocal[0]==1)//si esta inhabilitado, lo habilito
                       {

                           vectorInhabili[0]=0;
                           vectorLocal[0]=0;
                           vectorFlags[aux[0]]=0;//habilito codigo

                           mandainhabili_entrada(aux[0]);
                           mandainhabili_salida(aux[0]);

                           aux[0]=10;
                           return;
                       }
        }

        if(opcion == "A2")
        {
               if(vectorLocal[1]==0)//si esta disponible lo inhabilito
                        {

                            vectorInhabili[1]=1;
                            vectorLocal[1]=1;
                            aux[1]=libre;
                            vectorFlags[libre]=2;//anulo un codigo

                             mandainhabili_entrada(aux[1]);
                             mandainhabili_salida(aux[1]);
                            return;
                        }
                if (vectorLocal[1]==1)//si esta inhabilitado, lo habilito
                       {

                           vectorInhabili[1]=0;
                           vectorLocal[1]=0;
                           vectorFlags[aux[1]]=0;//habilito codigo

                           mandainhabili_entrada(aux[1]);
                           mandainhabili_salida(aux[1]);
                           aux[1]=10;
                           return;
                       }
        }

        if(opcion == "A3")
        {
               if(vectorLocal[2]==0)//si esta disponible lo inhabilito
                        {

                            vectorInhabili[2]=1;
                            vectorLocal[2]=1;
                            aux[2]=libre;
                            vectorFlags[libre]=2;//anulo un codigo

                            mandainhabili_entrada(aux[2]);
                            mandainhabili_salida(aux[2]);
                            return;
                        }
                if (vectorLocal[2]==1)//si esta inhabilitado, lo habilito
                       {

                           vectorInhabili[2]=0;
                           vectorLocal[2]=0;
                           vectorFlags[aux[2]]=0;//habilito codigo

                           mandainhabili_entrada(aux[2]);
                           mandainhabili_salida(aux[2]);
                           aux[2]=10;
                           return;
                       }
        }

        if(opcion == "A4")
        {
               if(vectorLocal[3]==0)//si esta disponible lo inhabilito
                        {

                            vectorInhabili[3]=1;
                            vectorLocal[3]=1;
                            aux[3]=libre;
                            vectorFlags[libre]=2;//anulo un codigo

                            mandainhabili_entrada(aux[3]);
                            mandainhabili_salida(aux[3]);
                            return;
                        }
                if (vectorLocal[3]==1)//si esta inhabilitado, lo habilito
                       {

                           vectorInhabili[3]=0;
                           vectorLocal[3]=0;
                           vectorFlags[aux[3]]=0;//habilito codigo

                           mandainhabili_entrada(aux[3]);
                           mandainhabili_salida(aux[3]);
                           aux[3]=10;
                           return;
                       }
        }

        if(opcion == "A5")
        {
               if(vectorLocal[4]==0)//si esta disponible lo inhabilito
                        {

                            vectorInhabili[4]=1;
                            vectorLocal[4]=1;
                            aux[4]=libre;
                            vectorFlags[libre]=2;//anulo un codigo

                            mandainhabili_entrada(aux[4]);
                            mandainhabili_salida(aux[4]);
                            return;
                        }
                if (vectorLocal[4]==1)//si esta inhabilitado, lo habilito
                       {

                           vectorInhabili[4]=0;
                           vectorLocal[4]=0;
                           vectorFlags[aux[4]]=0;//habilito codigo

                           mandainhabili_entrada(aux[4]);
                           mandainhabili_salida(aux[4]);
                           aux[4]=10;
                           return;
                       }
        }

        if(opcion == "A6")
        {
               if(vectorLocal[5]==0)//si esta disponible lo inhabilito
                        {

                            vectorInhabili[5]=1;
                            vectorLocal[5]=1;
                            aux[5]=libre;
                            vectorFlags[libre]=2;//anulo un codigo

                            mandainhabili_entrada(aux[5]);
                            mandainhabili_salida(aux[5]);
                            return;
                        }
                if (vectorLocal[5]==1)//si esta inhabilitado, lo habilito
                       {

                           vectorInhabili[5]=0;
                           vectorLocal[5]=0;
                           vectorFlags[aux[5]]=0;//habilito codigo

                           mandainhabili_entrada(aux[5]);
                           mandainhabili_salida(aux[5]);
                           aux[5]=10;
                           return;
                       }
        }

        if(opcion == "A7")
        {
               if(vectorLocal[6]==0)//si esta disponible lo inhabilito
                        {

                            vectorInhabili[6]=1;
                            vectorLocal[6]=1;
                            aux[6]=libre;
                            vectorFlags[libre]=2;//anulo un codigo

                            mandainhabili_entrada(aux[6]);
                            mandainhabili_salida(aux[6]);
                            return;
                        }
                if (vectorLocal[6]==1)//si esta inhabilitado, lo habilito
                       {

                           vectorInhabili[6]=0;
                           vectorLocal[6]=0;
                           vectorFlags[aux[6]]=0;//habilito codigo

                           mandainhabili_entrada(aux[6]);
                           mandainhabili_salida(aux[6]);
                           aux[6]=10;
                           return;
                       }
        }
        if(opcion == "A8")
        {
               if(vectorLocal[7]==0)//si esta disponible lo inhabilito
                        {

                            vectorInhabili[7]=1;
                            vectorLocal[7]=1;
                            aux[7]=libre;
                            vectorFlags[libre]=2;//anulo un codigo

                             mandainhabili_entrada(aux[7]);
                             mandainhabili_salida(aux[7]);
                            return;
                        }
                if (vectorLocal[7]==1)//si esta inhabilitado, lo habilito
                       {

                           vectorInhabili[7]=0;
                           vectorLocal[7]=0;
                           vectorFlags[aux[7]]=0;//habilito codigo

                           mandainhabili_entrada(aux[7]);
                           mandainhabili_salida(aux[7]);
                           aux[7]=10;
                           return;
                       }
        }
    }
}



void MainWindow::on_push_A1_clicked()
{
    static bool flag = true;
    if (flag==true)//lo ocupo
    {
        vectorLugares[0]=1;
        flag=false;
        return;
    }
    if (flag==false) // lo libero
    {
        vectorLugares[0]=0;
        flag=true;
        return;
    }
}

void MainWindow::on_push_A2_clicked()
{

    static bool flag = true;
    if (flag==true)//lo ocupo
    {
        vectorLugares[1]=1;
        flag=false;
        return;
    }
    if (flag==false) // lo libero
    {
        vectorLugares[1]=0;
        flag=true;
        return;
    }
}

void MainWindow::on_push_A3_clicked()
{

    static bool flag = true;
    if (flag==true)//lo ocupo
    {
        vectorLugares[2]=1;
        flag=false;
        return;
    }
    if (flag==false) // lo libero
    {
        vectorLugares[2]=0;
        flag=true;
        return;
    }
}

void MainWindow::on_push_A4_clicked()
{

    static bool flag = true;
    if (flag==true)//lo ocupo
    {
        vectorLugares[3]=1;
        flag=false;
        return;
    }
    if (flag==false) // lo libero
    {
        vectorLugares[3]=0;
        flag=true;
        return;
    }
}

void MainWindow::on_push_A5_clicked()
{

    static bool flag = true;
    if (flag==true)//lo ocupo
    {
        vectorLugares[4]=1;
        flag=false;
        return;
    }
    if (flag==false) // lo libero
    {
        vectorLugares[4]=0;
        flag=true;
        return;
    }
}

void MainWindow::on_push_A6_clicked()
{

    static bool flag = true;
    if (flag==true)//lo ocupo
    {
        vectorLugares[5]=1;
        flag=false;
        return;
    }
    if (flag==false) // lo libero
    {
        vectorLugares [5]=0;
        flag=true;
        return;
    }
}

void MainWindow::on_push_A7_clicked()
{

    static bool flag = true;
    if (flag==true)//lo ocupo
    {
        vectorLugares[6]=1;
        flag=false;
        return;
    }
    if (flag==false) // lo libero
    {
        vectorLugares[6]=0;
        flag=true;
        return;
    }
}

void MainWindow::on_push_A8_clicked()
{

    static bool flag = true;
    if (flag==true)//lo ocupo
    {
        vectorLugares[7]=1;
        flag=false;
        return;
    }
    if (flag==false) // lo libero
    {
        vectorLugares[7]=0;
        flag=true;
        return;
    }
}

void MainWindow::on_pushButton_entra_auto_clicked()
{
   TimerOn(libre);
}

void MainWindow::on_push_chau_0_clicked()
{
 GuardaBorra(0);
 }

void MainWindow::on_push_chau_1_clicked()
{
    GuardaBorra(1);
}

void MainWindow::on_push_chau_2_clicked()
{
    GuardaBorra(2);
}

void MainWindow::on_push_chau_3_clicked()
{
    GuardaBorra(3);
}

void MainWindow::on_push_chau_4_clicked()
{
    GuardaBorra(4);
}

void MainWindow::on_push_chau_5_clicked()
{
    GuardaBorra(5);
}

void MainWindow::on_push_chau_6_clicked()
{
    GuardaBorra(6);
}

void MainWindow::on_push_chau_7_clicked()
{
    GuardaBorra(7);
}

void MainWindow::on_lineEdit_returnPressed()
{
  Inhabilitar(ui->lineEdit->displayText()); // le mando el QString que escribi en el line edit
}


/**
    \fn  void Activos (Void)
    \brief Guarda en un archivo los codigos activos y sus tiempos actuales
    \details Funcion que genera un archivo .txt en el que guarda por un cualquier
             problema, los codigos activos y tiempos de estadia
    \author Marcos Trautman, Alan Kinast
    \date 2016.11.25
    \return (void)
*/


void MainWindow:: Activos (void)
{
    static int estadoAnt[8]={0};
    int i,j,flagCambio=0,CocheraNumero;


    for(i=0;i<8;i++)
    {
        if(estadoAnt[i] != vectorFlags[i])//si hubp un cambio en vectorFlags, o sea de que un codigo se libero ocupo o inhabilito
        {
            flagCambio=1;
            estadoAnt[i]= vectorFlags[i];
        }
    }
    if(flagCambio==1)
    {
        fs.open("Activos.txt");
        for(i=0;i<8;i++)
        {
            if (vectorFlags[i]==1)//!< Si el codigo esta activo
            {
                switch(i)
                {
                    case 0:
                        fs << (char)((int)i + 48) <<" "<< ui->label_00_hora->text().toStdString();
                        fs   << ":" << ui->label_00_dia->text().toStdString() << endl;
                        break;
                    case 1:
                        fs << (char)((int)i + 48) <<" "<< ui->label_01_hora->text().toStdString();
                        fs   << ":" << ui->label_01_dia->text().toStdString() << endl;
                        break;
                    case 2:
                        fs << (char)((int)i + 48) <<" "<< ui->label_02_hora->text().toStdString();
                        fs   << ":" << ui->label_02_dia->text().toStdString() << endl;
                        break;
                    case 3:
                        fs << (char)((int)i + 48) <<" "<< ui->label_03_hora->text().toStdString();
                        fs   << ":" << ui->label_03_dia->text().toStdString() << endl;
                        break;
                    case 4:
                        fs << (char)((int)i + 48) <<" "<< ui->label_04_hora->text().toStdString();
                        fs   << ":" << ui->label_04_dia->text().toStdString() << endl;
                        break;
                    case 5:
                        fs << (char)((int)i + 48) <<" "<< ui->label_05_hora->text().toStdString();
                        fs   << ":" << ui->label_05_dia->text().toStdString() << endl;
                        break;
                    case 6:
                        fs << (char)((int)i + 48) <<" "<< ui->label_06_hora->text().toStdString();
                        fs   << ":" << ui->label_06_dia->text().toStdString() << endl;
                        break;
                    case 7:
                        fs << (char)((int)i + 48) <<" "<< ui->label_07_hora->text().toStdString();
                        fs   << ":" << ui->label_07_dia->text().toStdString() << endl;
                        break;
                }

            }
            if(vectorFlags[i]==0)//!<Desocupado
            {
                fs <<(char)((int)i + 48)<<" "<<"libre" << "------------" << endl;
            }
            if(vectorFlags[i]==2)//!<Esta inhabilitado, por ende desocupado
            {
                for(j=0;j<8;j++)//!< Busco que cochera corresponde al código
                {
                    if(aux[j]==i)
                    {
                        CocheraNumero=j+1;
                        qDebug() << CocheraNumero;
                    }
                }
                fs <<(char)((int)i + 48)<<" "<<"inhabilitado" << "-A" << CocheraNumero << "--" << endl;
                //fs <<(char)((int)i + 48)<<" "<<"inhabilitado" << "-----" << endl;
            }
        }
        flagCambio=0;
    }
    fs.close();
}

/**
    \fn  void mandahora_entrada(void)
    \brief envia la hora a la placa de entrada
    \details  Funcion que envia la hora para que se actualice el lcd de la placa de entrada
    \author Marcos Trautman, Alan Kinast
    \date 2016.11.25
    \return (void)
*/
void MainWindow:: mandahora_entrada (void)
{
    char vector[9];

    QByteArray send;

    strcpy(vector, texto.toStdString().c_str());

    if(puerto!=NULL)
    {
        send.resize(9);
        send.data()[0]='H';
        send.data()[1]=vector[0];
        send.data()[2]=vector[1];
        send.data()[3]=vector[2];
        send.data()[4]=vector[3];
        send.data()[5]=vector[4];
        send.data()[6]=vector[5];
        send.data()[7]=vector[6];
        send.data()[8]=vector[7];

        puerto->write(send);
    }
}





/**
    \fn  void mandahora_salida(void)
    \brief envia la hora a la placa de salida
    \details  Funcion que envia la hora para que se actualice el lcd de la placa de salida
    \author Marcos Trautman, Alan Kinast
    \date 2016.11.25
    \return (void)
*/


void MainWindow::mandahora_salida (void)
{
    char vector[9];

    QByteArray send;


    strcpy(vector, texto.toStdString().c_str());

    if(puerto2!=NULL)
    {
        send.resize(9);
        send.data()[0]='H';
        send.data()[1]=vector[0];
        send.data()[2]=vector[1];
        send.data()[3]=vector[2];
        send.data()[4]=vector[3];
        send.data()[5]=vector[4];
        send.data()[6]=vector[5];
        send.data()[7]=vector[6];
        send.data()[8]=vector[7];

        puerto2->write(send);
    }
}



/**
    \fn  void mandafecha_entrada(void)
    \brief envia la fecha a la placa de entrada
    \details  Funcion que envia la fecha para que se actualice el lcd de la placa de entrada
    \author Marcos Trautman, Alan Kinast
    \date 2016.11.25
    \return (void)
*/

void MainWindow:: mandafecha_entrada (void)
{
    char vector[9];

    QByteArray send;


    strcpy(vector, fecha2.toStdString().c_str());

    if(puerto!=NULL)
    {
        send.resize(9);
        send.data()[0]='F';
        send.data()[1]=vector[0];
        send.data()[2]=vector[1];
        send.data()[3]=vector[2];
        send.data()[4]=vector[3];
        send.data()[5]=vector[4];
        send.data()[6]=vector[5];
        send.data()[7]=vector[6];
        send.data()[8]=vector[7];

        puerto->write(send);

    }

}


/**
    \fn  void mandafecha_salida(void)
    \brief envia la fecha a la placa de salida
    \details  Funcion que envia la fecha para que se actualice el lcd de la placa de salida
    \author Marcos Trautman, Alan Kinast
    \date 2016.11.25
    \return (void)
*/

void MainWindow:: mandafecha_salida(void)
{
    char vector[9];

    QByteArray send;


    strcpy(vector, fecha2.toStdString().c_str());

    if(puerto2!=NULL)
    {
        send.resize(9);
        send.data()[0]='F';
        send.data()[1]=vector[0];
        send.data()[2]=vector[1];
        send.data()[3]=vector[2];
        send.data()[4]=vector[3];
        send.data()[5]=vector[4];
        send.data()[6]=vector[5];
        send.data()[7]=vector[6];
        send.data()[8]=vector[7];

        puerto2->write(send);

        qDebug()<<"mandafecha envio: "<<send;
     }
}





/**
    \fn  void mandainhabili_entrada(int)
    \brief envia la inhabilitaciones a la placa de entrada
    \details  Funcion que envia las inhabilitaciones para que se actualice la placa de entrada
    \author Marcos Trautman, Alan Kinast
    \date 2016.11.25
    \return (void)
*/

void  MainWindow:: mandainhabili_entrada (int x)
{


    QByteArray send;

    if(puerto!=NULL)
    {
        send.resize(2);
        send.data()[0]='I';
       itoa(x,&send.data()[1],10);



        puerto->write(send);

     }

        qDebug()<<"mandainhabili envio: "<<send;
}





/**
    \fn  void mandainhabili_salida(int)
    \brief envia la inhabilitaciones a la placa de salida
    \details  Funcion que envia las inhabilitaciones para que se actualice la placa de salida
    \author Marcos Trautman, Alan Kinast
    \date 2016.11.25
    \return (void)
*/

void  MainWindow:: mandainhabili_salida (int x)
{


    QByteArray send;

    if(puerto2!=NULL)
    {
        send.resize(2);
        send.data()[0]='I';
       itoa(x,&send.data()[1],10);



        puerto2->write(send);

     }

        qDebug()<<"mandainhabili envio: "<<send;
}




/**
    \fn  void altanto_salida(void)
    \brief actualiza placa de salida
    \details  Funcion que envia los codigos ocupados, inhabilitados, libres, hora y fecha a la placa de salida
    \author Marcos Trautman, Alan Kinast
    \date 2016.11.25
    \return (void)
*/
 void MainWindow :: altanto_salida (void)
 {

     int i;
     QByteArray send;

        if (puerto2 != NULL)
        {
             for(i=0;i<8;i++)
             {
                 if (vectorFlags[i]==2)
                 {
                     send.resize(2);
                     send.data()[0]='I';
                     send.data()[1]=(char)((int)i + 48);
                     puerto2->write(send);

                 }

                 if(vectorFlags[i]==0)
                 {
                     send.resize(2);
                     send.data()[0]='S';
                     send.data()[1]=(char)((int)i + 48);
                     puerto2->write(send);
                 }
                 if(vectorFlags[i]==1)
                 {
                     send.resize(2);
                     send.data()[0]='E';
                     send.data()[1]=(char)((int)i + 48);
                     puerto2->write(send);
                 }
             }
             mandahora_salida();

             mandafecha_salida();


             send.resize(2);
             send.data()[0]='B';

             send.data()[1]='B';

             puerto2->write(send);
        }
    }




 /**
     \fn  void altanto_entrada(void)
     \brief actualiza placa de entrada
     \details  Funcion que envia los codigos ocupados, inhabilitados, libres, hora y fecha a la placa de entrada
     \author Marcos Trautman, Alan Kinast
     \date 2016.11.25
     \return (void)
 */
 void MainWindow:: altanto_entrada (void)
 {
     int i;
     QByteArray send;

    if (puerto != NULL)
    {
         for(i=0;i<8;i++)
         {
             if (vectorFlags[i]==2)

             {

                 send.resize(2);
                 send.data()[0]='I';
                 send.data()[1]=(char)((int)i + 48);
                 puerto->write(send);

             }

             if(vectorFlags[i]==0)
             {
                 send.resize(2);
                 send.data()[0]='S';
                 send.data()[1]=(char)((int)i + 48);
                 puerto->write(send);
             }
             if(vectorFlags[i]==1)
             {
                 send.resize(2);
                 send.data()[0]='E';
                 send.data()[1]=(char)((int)i + 48);
                 puerto->write(send);
             }
         }
         mandahora_entrada();
         mandafecha_entrada();

         send.resize(2);
         send.data()[0]='B';

         send.data()[1]='B';

         puerto->write(send);
    }

 }





 /**
     \fn  void LL_entrada(void)
     \brief envia LL a la placa de entrada
     \details  Funcion que envia LL para comenzar la conexion con la placa de entrada
     \author Marcos Trautman, Alan Kinast
     \date 2016.11.25
     \return (void)
 */
void MainWindow:: LL_entrada (void)
{

     QByteArray send;

    if(flagOK_entrada==0)
    {
        if(puerto != NULL)
        {
            send.resize(2);
            send.data()[0]='L';
            send.data()[1]='L';
            puerto->write(send);
        }
    }

}



/**
    \fn  void LL_salida(void)
    \brief envia LL a la placa de salida
    \details  Funcion que envia LL para comenzar la conexion con la placa de salida
    \author Marcos Trautman, Alan Kinast
    \date 2016.11.25
    \return (void)
*/
void MainWindow:: LL_salida (void)
{

     QByteArray send;

    {
        if(flagOK_salida==0)
        {
            if(puerto2 != NULL)
            {
                send.resize(2);
                send.data()[0]='L';
                send.data()[1]='L';
                puerto2->write(send);
            }
        }
    }

}

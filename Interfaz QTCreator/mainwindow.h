#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "qtimer.h"
#include <QDateTimeEdit>
#include <QtSerialPort>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <qstring.h>

using namespace std;


#include <QFile>

#define ESTADO0 0
#define ESTADO1 1
#define ESTADO2 2
#define ESTADO3 3
#define ESTADO4 4





using namespace std;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    QTimer * my_timer;
    QSerialPort *puerto;
    QSerialPort *puerto2;
    ofstream fs;
    ifstream PrimeraLectura;


private slots:

    void Lugares (void);
    void Barrer (void);
    void SumaTimer (void);
    void Mostrarlcd (void);
    void GuardaBorra (char);
    void Estadisticas (void);
    void Reloj (void);
    void Inhabilitar(QString);
    void Activos (void);
    void PuertoSerie_Recepcion();
    void PuertoSerie_Recepcion2();
    void PuertoSerie_Pop_Rx(QByteArray);
    void PuertoSerie_Pop_Rx2(QByteArray);
    void PuertoSerie_Desentramado_Entrada();
    void TimerOn(int);
    void TimerOff(int);
    void EnviaIngreso(int );
    void EstacionamientoSet(int);
    void PuertoSerie_Desentramado_Salida();
    void EnviaEgreso(int);
    void mandahora_entrada (void);
    void mandahora_salida (void);
    void mandafecha_entrada (void);
    void mandafecha_salida (void);
    void mandainhabili_entrada(int);
    void mandainhabili_salida (int );
    void altanto_salida (void);
    void altanto_entrada (void);
    void LL_entrada (void);
    void LL_salida(void);
    void Inhabilitar_archivo(int , int );


    void on_push_A1_clicked();

    void on_push_A2_clicked();

    void on_push_A3_clicked();

    void on_push_A4_clicked();

    void on_push_A5_clicked();

    void on_push_A6_clicked();

    void on_push_A7_clicked();

    void on_push_A8_clicked();

    void on_pushButton_entra_auto_clicked();

    void on_push_chau_0_clicked();

    void on_push_chau_1_clicked();

    void on_push_chau_2_clicked();

    void on_push_chau_3_clicked();

    void on_push_chau_4_clicked();

    void on_push_chau_5_clicked();

    void on_push_chau_6_clicked();

    void on_push_chau_7_clicked();

    void on_lineEdit_returnPressed();

    void on_pushButton_PuertoSerie_clicked();

    void on_pushButton_PuertoSerie_marcos_clicked();


private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H

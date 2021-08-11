#include "Principal.h"
#include "ui_principal.h"
#include <QDate>
#include <QDebug>
#include <QFile>
#include <QDir>
#include <QMessageBox>

Principal::Principal(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Principal)
{
    ui->setupUi(this);
    ui->groupReg->setVisible(true);
    ui->groupDato->setVisible(false);
    ui->groupRegistro->setVisible(false);
    inicializar();
    registro();
}

Principal::~Principal()
{
    delete ui;
}

void Principal::datos()
{
    QString fecha;
    float peso[50];
    float altura[50];
    float imc[50];

    QDate fecha1;
    fecha = fecha1.currentDate().toString("dd/MM/yyyy");

    for(int i=0; i<total; i++){
        peso[i] = persona[i]->peso();
        altura[i] = persona[i]->altura();
        persona[i]->calcular();
        imc[i] = persona[i]->imc();
    }
    QString _peso[50];
    QString _altura[50];
    QString _IMC[50];
    for(int i=0; i<total; i++){
        _peso[i] = QString::number(persona[i]->peso(), 'f', 2);
        _altura[i] = QString::number(persona[i]->altura(), 'f', 2);
        persona[i]->calcular();
        _IMC[i] = QString::number(persona[i]->imc(), 'f', 2);
    }
    QString file = QDir::currentPath() + "/michael.csv";
    QFile archivo(file);
    if(archivo.open(QFile::WriteOnly | QFile::Truncate)){
        for(int i=0; i<total; i++){
            QTextStream out(&archivo);
            out << fecha << ";" << peso[i] << ";" << altura[i] << ";" << imc[i] << "\n";
        }
        qDebug() << "Archivo almacenado en:" << QDir::currentPath();
        archivo.close();
    }
}

void Principal::inicializar()
{
    QStringList cabecera = {"Fecha", "Peso", "Altura", "IMC"};
    ui->outRegistro->setColumnCount(4);
    ui->outRegistro->setHorizontalHeaderLabels(cabecera);
}

void Principal::registro()
{
    QString nombre = QDir::currentPath() + "sherlyn";

    QFile file(nombre);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;
    QStringList datos;
    QTextStream in(&file);
    while (!in.atEnd()) {
        QString linea = in.readLine();
        datos << linea;
    }
    QStringList partes[50];
    for(int i=0; i<datos.size(); i++){
        partes[i]= datos[i].split(";");
    }
    for(int i=0; i<datos.size(); i++){

        ui->outRegistro->insertRow(i);

        ui->outRegistro->setItem(i,0, new QTableWidgetItem(partes[i][0]));
        ui->outRegistro->setItem(i,1, new QTableWidgetItem(partes[i][1]));
        ui->outRegistro->setItem(i,2, new QTableWidgetItem(partes[i][2]));
        ui->outRegistro->setItem(i,3, new QTableWidgetItem(partes[i][3]));

        int indice = total;
        persona[indice] = new Calculo(partes[i][0],partes[i][1].toFloat(),partes[i][2].toFloat());
        this->total++;
    }
    file.close();
}


void Principal::on_Calcular_clicked()
{
    float peso = ui->intPeso->value();
    float altura = ui->intAltura->value();
    float imc;
    float mayor = 0;
    float menor;
    QString estado;

    QDate fecha;
    QString date = fecha.currentDate().toString("dd/MM/yyyy");

    int indice = total;
    persona[indice] = new Calculo(date, peso, altura);
    this->total++;
    persona[indice]->calcular();
    imc = persona[indice]->imc();
    estado = persona[indice]->estado();
    QString actual = QString::number(peso,'f',2);
    QString ind = QString::number(imc,'f',2);
    ui->outActual->setText(actual + " Kg");
    ui->outIMC->setText(ind);
    ui->outEstado->setText(estado);

    for(int i=0; i<total; i++){
        menor = persona[0]->peso();
        float pes = persona[i]->peso();
        if(pes > mayor){
            mayor = pes;
        }
    }
    for(int i=0; i<total; i++){
        menor = persona[0]->peso();
        float men = persona[i]->peso();
        if(menor > men){
            menor = men;
        }
    }
    QString max = QString::number(mayor, 'f', 2);
    ui->outMax->setText(max + " Kg");
    QString min = QString::number(menor, 'f', 2);
    ui->outMin->setText(min + " Kg");

     ui->outRegistro->setRowCount(0);
    for(int i=0; i<total; i++){
        persona[i]->calcular();
        int posicion = ui->outRegistro->rowCount();
        ui->outRegistro->insertRow(posicion);
        ui->outRegistro->setItem(posicion,0,new QTableWidgetItem(date));
        ui->outRegistro->setItem(posicion,1,new QTableWidgetItem(QString::number(persona[i]->peso())));
        ui->outRegistro->setItem(posicion,2,new QTableWidgetItem(QString::number(persona[i]->altura())));
        ui->outRegistro->setItem(posicion,3,new QTableWidgetItem(QString::number(persona[i]->imc())));
    }
    ui->groupReg->setVisible(false);
    ui->groupDato->setVisible(true);
    ui->groupRegistro->setVisible(true);
  }

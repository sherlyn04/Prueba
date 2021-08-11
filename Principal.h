#ifndef PRINCIPAL_H
#define PRINCIPAL_H

#include <QMainWindow>
#include "calculo.h"


QT_BEGIN_NAMESPACE
namespace Ui { class Principal; }
QT_END_NAMESPACE

class Principal : public QMainWindow
{
    Q_OBJECT
public:
    Principal(QWidget *parent = nullptr);
    ~Principal();
    void datos();
    void inicializar();
    void registro();

private slots:

    void on_Calcular_clicked();

private:
    Ui::Principal *ui;
    Calculo *persona[50];
    int total=0;


};
#endif // PRINCIPAL_H

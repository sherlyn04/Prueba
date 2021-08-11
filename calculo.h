#ifndef CALCULO_H
#define CALCULO_H

#include <QObject>

class Calculo : public QObject
{
    Calculo();
    Q_OBJECT
    Q_PROPERTY(float altura READ altura)
    Q_PROPERTY(float imc READ imc)
    Q_PROPERTY(float peso READ peso)
private:
    float m_imc;
    QString m_fecha;
    float m_peso;
    float m_altura;
    QString m_estado;
public:
    explicit Calculo(QObject *parent = nullptr);
    Calculo(QString fecha, float peso, float altura);

    void calcular();
    float peso() const;
    float altura() const;
    float imc() const;
    QString fecha() const;
    QString estado() const;

signals:

};

#endif // CALCULO_H

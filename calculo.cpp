#include "calculo.h"
#include <math.h>

Calculo::Calculo(QObject *parent) : QObject(parent)
{

}


float Calculo::peso() const
{
    return m_peso;
}

float Calculo::altura() const
{
    return m_altura;
}

float Calculo::imc() const
{
    return m_imc;
}

QString Calculo::fecha() const
{
    return m_fecha;
}

QString Calculo::estado() const
{
    return m_estado;
}

Calculo::Calculo(QString fecha, float peso, float altura)
{
    this->m_peso = peso;
    this->m_altura = altura;
    this->m_fecha = fecha;
}

void Calculo::calcular()
{
    m_imc = m_peso / (pow(m_altura,2));

    if(m_imc >= 0 && m_imc <18.5){
        m_estado = "Delgado¿¿";
    }else if(m_imc >= 18.5 && m_imc <= 24.9){
        m_estado = "Normal";
    }else if(m_imc >= 25 && m_imc <= 29.9){
        m_estado = "Sobrepeso";
    }else if(m_imc >= 30){
        m_estado = "Obesidad";
    }

}

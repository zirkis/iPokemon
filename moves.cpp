#include "moves.h"

Moves::Moves(QString name, QString type, int typeInt, int power, int pp, int accuracy, int priority, QString damageClass)
{
    m_name = name;
    m_type = type;
    m_typeInt = typeInt;
    m_power = power;
    m_pp = pp;
    m_ppmax = pp;
    m_accuracy = accuracy;
    m_priority = priority;
    m_damageClass = damageClass;
}
void Moves::consumePp()
{
    m_pp--;
}

QString Moves::getName()const
{
    return m_name;
}
QString Moves::getType()const
{
    return m_type;
}
int Moves::getTypeInt()const
{
    return m_typeInt;
}
int Moves::getPp()const
{
    return m_pp;
}
int Moves::getPpMax()const
{
    return m_ppmax;
}
QString Moves::getDamageClass()const
{
    return m_damageClass;
}
int Moves::getPower()const
{
    return m_power;
}

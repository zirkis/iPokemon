#ifndef MOVES_H
#define MOVES_H
#include <QtWidgets>

class Moves
{
public:
    Moves(QString name, QString type, int typeInt, int power, int pp, int accuracy, int priority, QString damageClass);
    QString getName()const;
    QString getType()const;
    int getTypeInt()const;
    int getPp()const;
    int getPpMax()const;
    QString getDamageClass()const;
    int getPower()const;

    void consumePp();
private:
    QString m_name;
    QString m_type;
    int m_typeInt;
    int m_power;
    int m_pp;
    int m_ppmax;
    int m_accuracy;
    int m_priority;
    QString m_damageClass;
};

#endif // MOVES_H

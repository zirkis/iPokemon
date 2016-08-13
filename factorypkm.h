#ifndef FACTORYPKM_H
#define FACTORYPKM_H
#include <QtSql>
#include <pokemon.h>

class FactoryPkm
{
public:
    FactoryPkm(QSqlDatabase &db);
    Pokemon* create(const int& id);
    QString typeIntToString(const int &typeId)const;
    QString damageClassIntToString(const int &damageId)const;
private:
    QSqlDatabase m_db;
};

#endif // FACTORYPKM_H

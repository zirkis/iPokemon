#ifndef POKEMON_H
#define POKEMON_H

#include <moves.h>
#include <QtWidgets>
#include <QtSql>

class Pokemon
{
public:
    Pokemon(const int &number, const QString &name, const int &height, const int &weight, const int &base_exp);

    void setBaseStats(const int &pv, const int &attack, const int &defense, const int &speAtt, const int &speDef, const int &speed);
    void setStats();
    void setTypes(const int &type1, const int &type2);
    void setTypeStr(const QString &type1, const QString &type2);
    void setNature(const QString &nature, const int &stat1, const int &stat2);
    void setAbility(const QString &ability);
    void setAbilityDescription(const QString &description);
    void setGrowthRate(const int &rate);
    void setExp(const int &rate);
    void setMoves(const int &number, const QString &name,const QString &type,const int &typeInt,const int &power,const int &pp,const int &accuracy,const int &priority, const QString &damageClass);

    void receiveDamages(const int &damages);
    void receiveExp(const int &exp);

    int getNumber()const;
    QString getName()const;
    int getPv()const;
    int getPvMax()const;
    int getLevel()const;
    int getType(const int &i)const;
    QString getTypeStr(const int &i)const;
    QString getOrginalTrainer()const;
    int getId()const;
    QString getNature()const;
    QString getPlaceFound()const;
    int getLvlWhenFound()const;
    int getAttack()const;
    int getDefense()const;
    int getSpeAttack()const;
    int getSpeDefense()const;
    int getSpeed()const;
    int getExp()const;
    int getExpToNextLvl()const;
    int getExpPercent()const;
    QString getAbility()const;
    QString getAbilityDescription()const;
    Moves *getMove(const int& i)const;
    int getNbMoves()const;
    QString getSexe()const;
    QString getPokeball()const;
    int getHeight()const;
    int getBaseExperience()const;

private:
    int m_number;
    int m_pvMax;
    int m_level;
    QString m_name;
    int m_pv;
    int m_types[2];
    QString m_typeStr[2];
    QString m_originalTrainer;
    int m_id;
    QString m_nature;
    QString m_placeFound;
    int m_lvlWhenFound;
    int m_attack;
    int m_defense;
    int m_speAttack;
    int m_speDefense;
    int m_speed;
    int m_basePv;
    int m_baseAtt;
    int m_baseDef;
    int m_baseSpeA;
    int m_baseSpeD;
    int m_baseSpeed;
    int m_IvAtt;
    int m_IvDef;
    int m_IvSpeAtt;
    int m_IvSpeDef;
    int m_IvSpeed;
    int m_IvPv;
    int m_exp;
    int m_expToNextLvl;
    int m_expLvlPlusOne;
    int m_expBeginingLevel;
    int m_baseExp;
    QString m_ability;
    QString m_abilityDescription;
    Moves *m_moveSet[4];
    QString m_sexe;
    QString m_pokeball;
    int m_height;
    int m_weight;
    int m_growthRate;
    int *m_statBonus;
    int *m_statMalus;
};

#endif // POKEMON_H

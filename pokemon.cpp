#include "pokemon.h"

Pokemon::Pokemon(const int &number, const QString &name, const int &height, const int &weight, const int &base_exp)
{
    m_number = number;
    m_name = name;
    m_height = height;
    m_weight = weight;
    m_baseExp = base_exp;
    m_level = 30;
    m_originalTrainer = "RED";
    m_id = 65432;
    m_placeFound = "Pallet Town";
    m_lvlWhenFound = 5;
    m_pokeball = "pokeball";
    if (rand()%2==1)
        m_sexe = "male";
    else
        m_sexe = "female";
    m_IvAtt = rand()%32;
    m_IvDef = rand()%32;
    m_IvSpeAtt = rand()%32;
    m_IvSpeDef = rand()%32;
    m_IvSpeed = rand()%32;
    m_IvPv = rand()%32;

}
void Pokemon::setBaseStats(const int &pv, const int &attack, const int &defense, const int &speAtt, const int &speDef, const int &speed)
{
    m_basePv = pv;
    m_baseAtt = attack;
    m_baseDef = defense;
    m_baseSpeA = speAtt;
    m_baseSpeD = speDef;
    m_baseSpeed = speed;
    m_pv = ((2*m_basePv+m_IvPv)*m_level/100)+(m_level+10);
}

void Pokemon::setStats()
{
    m_pvMax = ((2*m_basePv+m_IvPv)*m_level/100)+(m_level+10);
    m_attack = ((2*m_baseAtt+m_IvAtt)*m_level/100)+5;
    m_defense = ((2*m_baseDef+m_IvDef)*m_level/100)+5;
    m_speAttack = ((2*m_baseSpeA+m_IvSpeAtt)*m_level/100)+5;
    m_speDefense = ((2*m_baseSpeD+m_IvSpeDef)*m_level/100)+5;
    m_speed = ((2*m_baseSpeed+m_IvSpeed)*m_level/100)+5;
    if (*m_statBonus != *m_statMalus){
        *m_statBonus *= 1.1;
        *m_statMalus *= 0.9;
    }
}
void Pokemon::setTypes(const int &type1, const int &type2)
{
    m_types[0] = type1;
    m_types[1] = type2;
}
void Pokemon::setTypeStr(const QString &type1, const QString &type2)
{
    m_typeStr[0] = type1;
    m_typeStr[1] = type2;
}
void Pokemon::setNature(const QString &nature, const int &stat1, const int &stat2)
{
    m_nature = nature;
    switch(stat1){
    case 2:
        m_statBonus = &m_attack;
        break;
    case 3:
        m_statBonus = &m_defense;
        break;
    case 4:
        m_statBonus = &m_speAttack;
        break;
    case 5:
        m_statBonus = &m_speDefense;
        break;
    case 6:
        m_statBonus = &m_speed;
        break;
    }
    switch(stat2){
    case 2:
        m_statMalus = &m_attack;
        break;
    case 3:
        m_statMalus = &m_defense;
        break;
    case 4:
        m_statMalus = &m_speAttack;
        break;
    case 5:
        m_statMalus = &m_speDefense;
        break;
    case 6:
        m_statMalus = &m_speed;
        break;
    }

}
void Pokemon::setAbility(const QString &ability)
{
    m_ability = ability.toUpper();
}
void Pokemon::setAbilityDescription(const QString &description)
{
    m_abilityDescription = "Abilities effects not supported yet";
}
void Pokemon::setGrowthRate(const int &rate)
{
    m_growthRate = rate;
    setExp(m_growthRate);
}
void Pokemon::setExp(const int &rate)
{
    if (rate == 1){
        m_expBeginingLevel = 1.25*pow(m_level,3);
        m_exp = m_expBeginingLevel;
        m_expLvlPlusOne = 1.25*pow((m_level+1),3);
        m_expToNextLvl = 1.25*pow((m_level+1),3)-m_exp;
    }
    else if (rate == 2){
        m_expBeginingLevel = pow(m_level,3);
        m_exp = m_expBeginingLevel;
        m_expLvlPlusOne = pow((m_level+1),3);
        m_expToNextLvl = pow((m_level+1),3)-m_exp;
    }
    else if (rate == 3){
        m_expBeginingLevel = 0.8*pow(m_level,3);
        m_exp = m_expBeginingLevel;
        m_expLvlPlusOne = 0.8*pow((m_level+1),3);
        m_expToNextLvl = 0.8*pow((m_level+1),3)-m_exp;
    }
    else if (rate == 4){
        m_expBeginingLevel = 1.2*pow(m_level,3)-15*pow(m_level,2)+100*m_level-140;
        m_exp = m_expBeginingLevel;
        m_expLvlPlusOne = 1.2*pow((m_level+1),3)-15*pow(m_level+1,2)+100*(m_level+1)-140;
        m_expToNextLvl = 1.2*pow((m_level+1),3)-15*pow(m_level+1,2)+100*(m_level+1)-140-m_exp;
    }

}

void Pokemon::setMoves(const int &number, const QString &name, const QString &type, const int &typeInt, const int &power, const int &pp, const int &accuracy, const int &priority, const QString &damageClass)
{
    m_moveSet[number] = new Moves(name,type,typeInt,power,pp,accuracy,priority,damageClass);
}

void Pokemon::receiveDamages(const int &damages)
{
    if (m_pv > 0){
        if (m_pv - damages > 0)
            m_pv -= damages;
        else
            m_pv = 0;
    }
}

void Pokemon::receiveExp(const int &exp)
{
    if (exp > m_expToNextLvl){
        int tmp = exp;
        while(tmp > m_expToNextLvl){
            tmp -= m_expToNextLvl;
            m_level++;
            setExp(m_growthRate);
            setStats();
        }
        m_exp += tmp;
        m_expToNextLvl -= tmp;
    }
    else {
        m_exp += exp;
        m_expToNextLvl -= exp;
    }
}

int Pokemon::getNumber()const
{
    return m_number;
}
QString Pokemon::getName()const
{
    return m_name;
}
int Pokemon::getPv()const
{
    return m_pv;
}
int Pokemon::getPvMax()const
{
    return m_pvMax;
}
int Pokemon::getLevel()const
{
    return m_level;
}
int Pokemon::getType(const int &i)const
{
    return m_types[i];
}
QString Pokemon::getTypeStr(const int &i)const
{
    return m_typeStr[i];
}
QString Pokemon::getOrginalTrainer()const
{
    return m_originalTrainer;
}
int Pokemon::getId()const
{
    return m_id;
}
QString Pokemon::getNature()const
{
    return m_nature;
}
QString Pokemon::getPlaceFound()const
{
    return m_placeFound;
}
int Pokemon::getLvlWhenFound()const
{
    return m_lvlWhenFound;
}
int Pokemon::getAttack()const
{
    return m_attack;
}
int Pokemon::getDefense()const
{
    return m_defense;
}
int Pokemon::getSpeAttack()const
{
    return m_speAttack;
}
int Pokemon::getSpeDefense()const
{
    return m_speDefense;
}
int Pokemon::getSpeed()const
{
    return m_speed;
}
int Pokemon::getExp()const
{
    return m_exp;
}
int Pokemon::getExpToNextLvl()const
{
    return m_expToNextLvl;
}
int Pokemon::getExpPercent()const
{
    return float((m_exp-m_expBeginingLevel))/float((m_expLvlPlusOne-m_expBeginingLevel))*100;
}

QString Pokemon::getAbility()const
{
    return m_ability;
}
QString Pokemon::getAbilityDescription()const
{
    return m_abilityDescription;
}
Moves *Pokemon::getMove(const int &i) const
{
    return m_moveSet[i];
}
int Pokemon::getNbMoves()const
{
    int cpt = 0;
    for (int i=0; i<4;i++){
        if (m_moveSet[i] != 0)
            cpt ++;
    }
    return cpt;
}
QString Pokemon::getSexe()const
{
    return m_sexe;
}
QString Pokemon::getPokeball()const
{
    return m_pokeball;
}
int Pokemon::getHeight()const
{
    return m_height;
}
int Pokemon::getBaseExperience()const
{
    return m_baseExp;
}

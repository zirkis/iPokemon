#include "factorypkm.h"

FactoryPkm::FactoryPkm(QSqlDatabase &db)
{
    m_db = db;
}

Pokemon *FactoryPkm::create(const int &id)
{
    m_db.open();
    Pokemon *product;
    QSqlQuery query;
    query.prepare("SELECT * FROM pokemon where id=?");
    query.addBindValue(id);
    if(query.exec())
    {
        while(query.next())
            {
             product = new Pokemon(query.value(0).toInt(),query.value(1).toString(),query.value(3).toInt(),query.value(4).toInt(),query.value(5).toInt());
            }
    }

    query.prepare("SELECT * FROM natures where id=?");
    query.addBindValue(rand()%25+1);
    if(query.exec())
    {
        while(query.next())
            {
                product->setNature(query.value(1).toString(),query.value(3).toInt(),query.value(2).toInt());
            }
    }

    query.prepare("SELECT * FROM pokemon_stats where pokemon_id=?");
    query.addBindValue(id);
    int stats[6];
    int cpt=0;
    if(query.exec())
    {
        while(query.next())
            {
                stats[cpt] = query.value(2).toInt();
                cpt++;
            }
        product->setBaseStats(stats[0],stats[1],stats[2],stats[3],stats[4],stats[5]);
        product->setStats();
    }

    query.prepare("SELECT * FROM pokemon_types where pokemon_id=?");
    query.addBindValue(id);
    int types[2]={0};
    cpt=0;
    if(query.exec())
    {
        while(query.next())
            {
                types[cpt] = query.value(1).toInt();
                cpt++;
            }
        product->setTypes(types[0],types[1]);
    }

    query.prepare("SELECT * FROM types where id=?");
    query.addBindValue(product->getType(0));
    QString typeStr[2]={0};
    if(query.exec())
    {
        while(query.next())
            {
                typeStr[0] = query.value(1).toString();
            }
    }

    query.prepare("SELECT * FROM types where id=?");
    query.addBindValue(product->getType(1));
    if(query.exec())
    {
        while(query.next())
            {
                typeStr[1] = query.value(1).toString();
            }
    }
    product->setTypeStr(typeStr[0],typeStr[1]);

    query.prepare("SELECT * FROM pokemon_abilities where pokemon_id=?");
    query.addBindValue(id);
    int abilityId;
    cpt = 0;
    int randomAb = rand()%2;
    if(query.exec())
    {
        while(query.next())
            {
                if (cpt == randomAb)
                    abilityId = query.value(1).toInt();
                cpt++;
            }
    }

    query.prepare("SELECT * FROM abilities where id=?");
    query.addBindValue(abilityId);
    if(query.exec())
    {
        while(query.next())
            {
                product->setAbility(query.value(1).toString());
            }
    }

    query.prepare("SELECT * FROM ability_prose where ability_id=?");
    query.addBindValue(abilityId);
    if(query.exec())
    {
        while(query.next())
            {
                product->setAbilityDescription(query.value(2).toString());
            }
    }

    query.prepare("SELECT id, growth_rate_id FROM pokemon_species where id=?");
    query.addBindValue(id);
    if(query.exec())
    {
        while(query.next())
            {
                if (query.value(1).toInt() == 5)
                    product->setGrowthRate(3);
                else if (query.value(1).toInt() == 6)
                    product->setGrowthRate(1);
                else
                    product->setGrowthRate(query.value(1).toInt());
            }
    }

    query.prepare("select * from pokemon_moves where version_group_id=10 and pokemon_move_method_id=1 and pokemon_id=? and level<=30 order by level desc");
    query.addBindValue(id);
    cpt=0;
    int moves[4]={0};
    if(query.exec())
    {
        while(query.next())
            {
                moves[cpt] = query.value(2).toInt();
                cpt++;
                if (cpt == 4)
                    break;
            }
    }

    query.prepare("select * from moves where id=? or id=? or id=? or id=?");
    query.addBindValue(moves[0]);
    query.addBindValue(moves[1]);
    query.addBindValue(moves[2]);
    query.addBindValue(moves[3]);
    cpt=0;
    if(query.exec())
    {
        while(query.next())
        {
            product->setMoves(cpt,query.value(1).toString(),typeIntToString(query.value(3).toInt()),query.value(3).toInt(),query.value(4).toInt(),query.value(5).toInt(),query.value(6).toInt(),query.value(7).toInt(),damageClassIntToString(query.value(9).toInt()));
            cpt++;
        }
    }


    m_db.close();
    return product;
}
QString FactoryPkm::typeIntToString(const int &typeId)const
{
    QSqlQuery query;
    query.prepare("SELECT * FROM types where id=?");
    query.addBindValue(typeId);
    if(query.exec())
    {
        while(query.next())
            {
             return query.value(1).toString();
            }
    }
}

QString FactoryPkm::damageClassIntToString(const int &damageId)const
{
    QSqlQuery query;
    query.prepare("SELECT * FROM move_damage_classes where id=?");
    query.addBindValue(damageId);
    if(query.exec())
    {
        while(query.next())
            {
             return query.value(1).toString();
            }
    }
}

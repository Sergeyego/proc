#include "rels.h"

Rels* Rels::rels_instance=nullptr;

Rels *Rels::instance()
{
    if (rels_instance==nullptr)
        rels_instance = new Rels();
    return rels_instance;
}

Rels::Rels(QObject *parent) : QObject(parent)
{
    relOwen = new DbSqlRelation("owens","id","num",this);// QString("select id, num from owens order by num"),0,1,this);
    relOwen->setSort("num");
    relElDim = new DbSqlRelation("dry_els","ide","fnam",this);// QString("select ide, fnam from dry_els order by fnam"),0,1,this);
    relElDim->setSort("fnam");
    relRab = new DbSqlRelation("rab_rab","id","snam",this);//QString("select id, snam from rab_rab order by snam"),0,1,this);
    relRab->setSort("snam");
    relProg = new DbSqlRelation("dry_reg","id","nam",this);//QString("select id, nam from dry_reg order by nam"),0,1,this);
    relProg->setSort("nam");
}

void Rels::refresh()
{
    relOwen->refreshModel();
    relElDim->refreshModel();
    relRab->refreshModel();
    relProg->refreshModel();
}

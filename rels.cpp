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
    relOwen = new DbSqlRelation("owens","id","num",this);
    relOwen->setSort("num");
    relElDim = new DbSqlRelation("dry_els","ide","fnam",this);
    relElDim->setSort("fnam");
    relRab = new DbSqlRelation("rab_rab","id","snam",this);
    relRab->setSort("snam");
    relProg = new DbSqlRelation("dry_reg","id","nam",this);
    relProg->setSort("nam");
}

void Rels::refresh()
{
    relOwen->refreshModel();
    relElDim->refreshModel();
    relRab->refreshModel();
    relProg->refreshModel();
}

#ifndef BASEDONNE_H
#define BASEDONNE_H
#include <QtSql>
#include <QSqlDatabase>

bool connexion()
{
    QSqlDatabase bd = QSqlDatabase::addDatabase("QSQLITE");
    bd.setDatabaseName("Mychat.db");
    if(bd.open())
        return true;
    else
        return false;
}

#endif // BASEDONNE_H

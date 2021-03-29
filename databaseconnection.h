#ifndef DATABASECONNECTION_H
#define DATABASECONNECTION_H

#include <QSqlDatabase>

class DatabaseConnection
{
public:
    DatabaseConnection();

    QSqlDatabase mydb;

    void connClose()
    {
        mydb.close();
        mydb.removeDatabase(QSqlDatabase::defaultConnection);
    }
    bool connOpen()
    {
        mydb = QSqlDatabase::addDatabase("QSQLITE");
        mydb.setDatabaseName("C:/SQLite/supermarketstock.db");
        if(!mydb.open())
        {
            return false;
        }
        else
        {
            return true;
        }
    }
};

#endif // DATABASECONNECTION_H

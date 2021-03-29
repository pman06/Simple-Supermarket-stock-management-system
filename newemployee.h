#ifndef NEWEMPLOYEE_H
#define NEWEMPLOYEE_H
#include "databaseconnection.h"

#include <QMainWindow>

namespace Ui {
class NewEmployee;
}

class NewEmployee : public QMainWindow
{
    Q_OBJECT

public:
    explicit NewEmployee(QWidget *parent = 0);
    ~NewEmployee();

private slots:
    void on_registerButton_clicked();

    void on_backButton_clicked();

private:
    Ui::NewEmployee *ui;
    DatabaseConnection
    con;
};

#endif // NEWEMPLOYEE_H

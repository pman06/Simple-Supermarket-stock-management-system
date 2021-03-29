#include "newemployee.h"
#include "ui_newemployee.h"
#include "mainwindow.h"

#include <QSqlQuery>
#include <QMessageBox>

NewEmployee::NewEmployee(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::NewEmployee)
{
    ui->setupUi(this);
    if(!con.connOpen())
    {
        return;
    }
    else
    {
        con.connOpen();
    }
}

NewEmployee::~NewEmployee()
{
    delete ui;
    con.connClose();
}

void NewEmployee::on_registerButton_clicked()
{
    QString fname, lname, username,password;

    fname = ui->firstNameEdit->text();
    lname = ui->lastNameEdit->text();
    username = ui->usernameEdit->text();
    password = ui->passwordEdit->text();

    QSqlQuery qry;
    qry.prepare("insert into Admin(firstName,lastName,username,password) values('"+fname+"','"+lname+"','"+username+"','"+password+"')");
    if(qry.exec())
    {
        QMessageBox::information(this,"Success", "Admin added Successfully");
        on_backButton_clicked();
    }
    else
    {
        QMessageBox::critical(this,"Error", qry.lastError().text());
    }
}

void NewEmployee::on_backButton_clicked()
{
    this->close();
    MainWindow *form = new MainWindow();
    form->show();
}

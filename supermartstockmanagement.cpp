#include "supermartstockmanagement.h"
#include "ui_supermartstockmanagement.h"
#include "mainwindow.h"

#include <QMessageBox>
#include <QDebug>
#include <QSqlQuery>
#include <QSqlError>

SupermartStockManagement::SupermartStockManagement(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SupermartStockManagement)
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
    ui->statusLabel->hide();
}

SupermartStockManagement::~SupermartStockManagement()
{
    delete ui;
    con.connClose();
}


void SupermartStockManagement::on_loginButton_clicked()
{


    QString username = ui->usernameEdit->text();
    QString password = ui->passwordEdit->text();

    QSqlQuery qry;

    if((!username.isEmpty()) && (!password.isEmpty()))
    {
        qry.prepare("Select * from Admin where username='"+username+"' AND password='"+password+"'");
        if(qry.exec())
        {
            int count =0;
            while(qry.next())
            {
                count++;
            }
            if(count>0)
            {
                this->hide();
                MainWindow *win = new MainWindow();
                win->show();
            }
            else
            {
                ui->statusLabel->show();
                ui->statusLabel->setText("Username or Password is not correct");
            }
        }
        else
        {
            QMessageBox::critical(this,"Error",qry.lastError().text());
        }

    }
    else
    {
        ui->statusLabel->show();
        ui->statusLabel->setText("Please Supply Username and Password");
    }

}

void SupermartStockManagement::on_usernameEdit_textEdited(const QString &arg1)
{
    ui->statusLabel->hide();
}

void SupermartStockManagement::on_passwordEdit_returnPressed()
{
    on_loginButton_clicked();
}

void SupermartStockManagement::on_passwordEdit_textEdited(const QString &arg1)
{
    ui->statusLabel->hide();
}

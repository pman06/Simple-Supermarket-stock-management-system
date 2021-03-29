#include "transactions.h"
#include "ui_transactions.h"
#include "mainwindow.h"

#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QMessageBox>

Transactions::Transactions(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Transactions)
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

Transactions::~Transactions()
{
    delete ui;
}

void Transactions::on_backButton_clicked()
{
    this->hide();
    MainWindow *form = new MainWindow;
    form->show();
}

void Transactions::on_transactionButton_clicked()
{
    QSqlQuery qry;
    QSqlQueryModel *model = new QSqlQueryModel();

    qry.prepare("Select * from Orders");
    if(qry.exec())
    {
        model->setQuery(qry);
        ui->transactionView->setModel(model);
    }
    else
    {
        QMessageBox::critical(this,"Error", qry.lastError().text());
    }
}

void Transactions::on_transactionView_clicked(const QModelIndex &index)
{
    QString ProdId = ui->transactionView->model()->index(index.row(),0).data().toString();

    QSqlQueryModel *model = new QSqlQueryModel();
    QSqlQuery qry;
    qry.prepare("Select Product_name, Quantity, Price from Ordered_Items where Order_Id= '"+ProdId+"'");
    if(qry.exec())
    {
        model->setQuery(qry);
        ui->itemsTableView->setModel(model);
    }
    else
    {
        QMessageBox::critical(this,"Error",qry.lastError().text());
    }
}

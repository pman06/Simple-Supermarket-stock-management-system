#include "viewproductsform.h"
#include "ui_viewproductsform.h"
#include "mainwindow.h"

#include <QSqlQuery>
#include <QSqlQueryModel>

ViewProductsForm::ViewProductsForm(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ViewProductsForm)
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

ViewProductsForm::~ViewProductsForm()
{
    delete ui;
    con.connClose();
}

void ViewProductsForm::on_loadPushButton_clicked()
{
    QSqlQuery qry;
    QSqlQueryModel *model = new QSqlQueryModel();

    qry.prepare("Select * from products");
    if(qry.exec())
    {
        model->setQuery(qry);
        ui->productsTableView->setModel(model);
    }
}

void ViewProductsForm::on_backPushButton_clicked()
{
    this->hide();
    MainWindow *win = new MainWindow;
    win->show();
}

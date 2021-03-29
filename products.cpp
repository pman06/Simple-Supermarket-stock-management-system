#include "products.h"
#include "ui_products.h"
#include "mainwindow.h"

#include <QMessageBox>
#include <QSqlQuery>
#include <QDebug>
#include <QDate>

Products::Products(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Products)
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

Products::~Products()
{
    delete ui;
    con.connClose();
}

void Products::on_saveButton_clicked()
{
    QString name,manufactureName,productType,expiry, production,productId,price,quantity;

    productId = ui->productID->text();
    name = ui->productNameEdit->text();
    manufactureName = ui->manufactureeName->text();
    price = ui->productPrice->text();
    quantity = ui->quantityEdit->text();
    productType = ui->typeComboBox->currentText();
    expiry = ui->expiryDateEdit->date().toString("dd/MM/yyyy");
    production = ui->productionDateEdit->date().toString("dd/MM/yyyy");

    if(!productId.isEmpty() && !name.isEmpty() && !manufactureName.isEmpty() && !price.isEmpty() && !quantity.isEmpty() && !production.isEmpty() && !productType.isEmpty() && !expiry.isEmpty())
    {
        QSqlQuery qry;

        if(qry.exec("SELECT * FROM Products where Product_ID='"+productId+"'"))
        {
            if(!qry.next())
            {
                qry.prepare("INSERT INTO Products(Product_ID,Product_Name,Product_Price,Manufacturer_Name,Production_Date,Expiry_Date,Quantity,Product_Type) values('"+productId+"','"+name+"','"+price+"','"+manufactureName+"','"+production+"','"+expiry+"','"+quantity+"','"+productType+"')");
                if(qry.exec())
                {
                    QMessageBox::information(this,"Success!","Product Added Successfully!");
                }
                else
                {
                    QMessageBox::critical(this,"Error!",qry.lastError().text());
                }
            }
            else
            {
                QMessageBox::critical(this,"Error!","Product ID Already Exists!");
            }
        }
        else
        {
            QMessageBox::critical(this,"Error!",qry.lastError().text());
        }
    }
    else
    {
        ui->statusLabel->show();
    }
}

void Products::on_cancelButton_clicked()
{
    this->close();
    MainWindow *win = new MainWindow();
    win->show();
}

void Products::on_productID_textEdited(const QString &arg1)
{
    ui->statusLabel->hide();
}

void Products::on_productNameEdit_textEdited(const QString &arg1)
{
    ui->statusLabel->hide();
}

void Products::on_productPrice_textEdited(const QString &arg1)
{
    ui->statusLabel->hide();
}

void Products::on_manufactureeName_textEdited(const QString &arg1)
{
    ui->statusLabel->hide();
}

void Products::on_quantityEdit_textEdited(const QString &arg1)
{
    ui->statusLabel->hide();
}

void Products::on_quantityEdit_returnPressed()
{
    on_saveButton_clicked();
}

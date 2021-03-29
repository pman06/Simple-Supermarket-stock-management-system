#include "editproduct.h"
#include "ui_editproduct.h"
#include "mainwindow.h"

#include <QSqlQuery>
#include <QMessageBox>
#include <QDesktopWidget>
#include <QStyle>

EditProduct::EditProduct(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::EditProduct)
{
    if(!con.connOpen())
    {
        return;
    }
    else
    {
        con.connOpen();
    }
    ui->setupUi(this);
    ui->formLayou->hide();
    ui->buttonFormWidget->hide();
    ui->statusLabel->hide();
    this->setGeometry(
        QStyle::alignedRect(
            Qt::LeftToRight, Qt::AlignCenter, this->size(), qApp->desktop()->availableGeometry()
        )
   );
}

EditProduct::~EditProduct()
{
    delete ui;
    con.connClose();
}

void EditProduct::on_backButton_clicked()
{
    this->close();
    MainWindow *win = new MainWindow();
    win->show();
}

void EditProduct::on_goButton_clicked()
{
    QSqlQuery qry;
    QString prodID = ui->productIdEdit->text();

    if(!prodID.isEmpty())
    {
        if(qry.exec("SELECT * FROM PRODUCTS WHERE PRODUCT_ID='"+prodID+"'"))
        {
            if(qry.next())
            {
                ui->productID->setText(qry.value(0).toString());
                ui->productNameEdit->setText(qry.value(1).toString());
                ui->productPrice->setText(qry.value(2).toString());
                ui->manufactureeName->setText(qry.value(3).toString());
                ui->productionDateEdit->setDate(qry.value(4).toDate());
                ui->expiryDateEdit->setDate(qry.value(5).toDate());
                ui->quantityEdit->setText(qry.value(6).toString());
                ui->typeComboBox->setCurrentText(qry.value(7).toString());
                ui->formLayou->show();
                ui->buttonFormWidget->show();
            }
            else
            {
                QMessageBox::critical(this,"Error!","No Product With ID "+prodID+" found");
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

void EditProduct::on_productIdEdit_textEdited(const QString &arg1)
{
    ui->statusLabel->hide();
}

void EditProduct::on_saveButton_clicked()
{
    QSqlQuery qry;
    QString name,manufactureName,productType,expiry, production,productId,price,quantity;

    productId = ui->productID->text();
    name = ui->productNameEdit->text();
    manufactureName = ui->manufactureeName->text();
    price = ui->productPrice->text();
    quantity = ui->quantityEdit->text();
    productType = ui->typeComboBox->currentText();
    expiry = ui->expiryDateEdit->date().toString("dd/MM/yyyy");
    production = ui->productionDateEdit->date().toString("dd/MM/yyyy");
    qry.prepare("update products set Product_ID='"+productId+"',Product_Name='"+name+"',Product_Price='"+price+"',Manufacturer_Name='"+manufactureName+"',Production_Date='"+production+"',Expiry_Date='"+expiry+"',Quantity='"+quantity+"',Product_Type='"+productType+"' where Product_ID ='"+productId+"'");
    if(qry.exec())
    {
        QMessageBox::information(this,"Success", "Product Successfully Updated!");
        ui->formLayou->hide();
        ui->buttonFormWidget->hide();
    }
    else
    {
        QMessageBox::critical(this,"Error", qry.lastError().text());
    }
}

void EditProduct::on_cancelButton_clicked()
{
    on_backButton_clicked();
}

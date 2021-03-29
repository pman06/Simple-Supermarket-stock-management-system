#include "deleteproducts.h"
#include "ui_deleteproducts.h"
#include "mainwindow.h"

#include <QSqlQuery>
#include <QMessageBox>
#include <QSqlQueryModel>

DeleteProducts::DeleteProducts(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::DeleteProducts)
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
    ui->infoLabel->hide();
    ui->pidLabel->hide();
    ui->pNameLabel->hide();
    ui->manuLabel->hide();
    ui->priceLabel->hide();
    ui->deleteLAbel->hide();
    ui->sizeLabel->hide();
}

DeleteProducts::~DeleteProducts()
{
    delete ui;
    con.connClose();
}

void DeleteProducts::on_loadButton_clicked()
{
    QString option= ui->optionComboBox->currentText();
    QString product = ui->productLineEdit->text();

    QSqlQuery qry;
    if(!product.isEmpty())
    {
        if(option=="Product ID")
        {
            qry.prepare("SELECT * from Products Where Product_ID ='"+product+"'");
            if(qry.exec())
            {
                if(qry.next())
                {
                    ui->pidLabel->setText(qry.value(0).toString());
                    ui->pNameLabel->setText(qry.value(1).toString());
                    ui->manuLabel->setText(qry.value(3).toString());
                    ui->priceLabel->setText(qry.value(2).toString());
                    ui->sizeLabel->setText(qry.value(7).toString());

                    ui->pidLabel->show();
                    ui->pNameLabel->show();
                    ui->manuLabel->show();
                    ui->priceLabel->show();
                    ui->sizeLabel->show();
                }
                else
                {
                    QMessageBox::critical(this,"Error", "No Product with ID ("+product+") in Database!");
                }
            }
            else
            {
                QMessageBox::critical(this,"Error", qry.lastError().text());
            }
        }
        else if(option=="Product Name")
        {
            qry.prepare("SELECT * from Products Where Product_Name ='"+product+"'");
            if(qry.exec())
            {
                if(qry.next())
                {
                    ui->pidLabel->setText(qry.value(0).toString());
                    ui->pNameLabel->setText(qry.value(1).toString());
                    ui->manuLabel->setText(qry.value(3).toString());
                    ui->priceLabel->setText(qry.value(2).toString());
                    ui->sizeLabel->setText(qry.value(7).toString());

                    ui->pidLabel->show();
                    ui->pNameLabel->show();
                    ui->manuLabel->show();
                    ui->priceLabel->show();
                    ui->sizeLabel->show();
                }
                else
                {
                    QMessageBox::critical(this,"Error", "No Product with Name ("+product+") in Database!");
                }
            }
            else
            {
                QMessageBox::critical(this,"Error", qry.lastError().text());
            }
        }
    }
    else
    {
        ui->infoLabel->show();

        ui->pidLabel->hide();
        ui->pNameLabel->hide();
        ui->manuLabel->hide();
        ui->priceLabel->hide();
        ui->sizeLabel->hide();
    }
}

void DeleteProducts::on_cancelButton_clicked()
{
    this->close();
    MainWindow *form = new MainWindow;
    form->show();
}

void DeleteProducts::on_deleteButton_clicked()
{
    QMessageBox msgBox;
    msgBox.setText("Are you sure you want to Delete Product from Records?");
    QPushButton *dele = msgBox.addButton(tr("Delete"),QMessageBox::ActionRole);
    QPushButton *cancel = msgBox.addButton(QMessageBox::Abort);

    if((ui->pidLabel->text()!="") || (ui->pNameLabel->text()!=""))
    {
    msgBox.exec();

    if(msgBox.clickedButton()== dele)
    {
        QString product = ui->pidLabel->text();
        QSqlQuery qry;
        qry.prepare("DELETE FROM PRODUCTS WHERE PRODUCT_ID='"+product+"'");
        if(qry.exec())
        {
            QMessageBox::information(this,"Deleted","Product Succefully Deleted!");
        }
        else
        {
            QMessageBox::critical(this,tr("Error"),qry.lastError().text());
        }

    }
    else if(msgBox.clickedButton()== cancel)
    {
        return;
    }
    }
    else
    {
        ui->deleteLAbel->show();
    }
}

void DeleteProducts::on_productLineEdit_textEdited(const QString &arg1)
{
    ui->infoLabel->hide();
    ui->deleteLAbel->hide();
}

void DeleteProducts::on_productLineEdit_returnPressed()
{
    on_loadButton_clicked();
}

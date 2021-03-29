#include "order.h"
#include "ui_order.h"
#include "mainwindow.h"

#include <QModelIndexList>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QMessageBox>
#include <QList>
#include <QDebug>

Order::Order(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Order)
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

    ui->errorLabel->hide();
    ui->quantityErrorLabel->hide();
    ui->itemInCartLabel->hide();
    ui->selectitemLabel->hide();
    ui->payLabel->hide();

    total = 0;
    QSqlQuery qry;
    QSqlQueryModel *model = new QSqlQueryModel;
    qry.prepare("Select Product_name from Products");
    if(qry.exec())
    {
        model->setQuery(qry);
        ui->productCComboBox->setModel(model);
    }
    else
    {
        QMessageBox::critical(this,"Error",qry.lastError().text());
    }
}

Order::~Order()
{
    delete ui;
    con.connClose();
}

void Order::on_productCComboBox_currentTextChanged(const QString &textChanged)
{
    QSqlQuery qry;
    qry.prepare("Select * from products where Product_Name = '"+textChanged+"'");
    if(qry.exec())
    {
        while(qry.next())
        {
            ui->quantityLabel->setText(qry.value(6).toString());
            ui->priceLabel->setText(qry.value(2).toString());
        }
    }
    else
    {
        QMessageBox::critical(this,"Error", qry.lastError().text());
    }
}

void Order::on_addToCartButton_clicked()
{
    double quantity,price;
    int purchasedQuantity;
    QString product;

    purchasedQuantity = ui->quantityLineEdiit->text().toInt();
    quantity = ui->quantityLabel->text().toInt();
    product = ui->productCComboBox->currentText();
    price = ui->priceLabel->text().toInt();

    double cost = purchasedQuantity * price;


    QList <QTableWidgetItem*> itemList = ui->tableWidget->findItems(product,Qt::MatchExactly);

    QString addItem = product+" #"+QString::number(cost)+" ";


    if(!ui->quantityLineEdiit->text().isEmpty())
    {
        if(purchasedQuantity <= quantity)
        {
            if(itemList.count()==0)
            {
                total = total + cost;
                ui->totalLabel->setText(QString::number(total));
                ui->tableWidget->insertRow(ui->tableWidget->rowCount());
                ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,0, new QTableWidgetItem(product));
                ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,1, new QTableWidgetItem(QString::number(purchasedQuantity)));
                ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,2, new QTableWidgetItem(QString::number(cost)));
            }
            else
            {

                ui->itemInCartLabel->show();
            }
        }
        else
        {
            ui->errorLabel->show();
        }
    }
    else
    {
        ui->quantityErrorLabel->show();
    }
}

void Order::on_quantityLineEdiit_textChanged(const QString &arg1)
{
    ui->errorLabel->hide();
    ui->itemInCartLabel->hide();
    ui->quantityErrorLabel->hide();
    ui->payLabel->hide();
}

void Order::on_productCComboBox_currentIndexChanged(const QString &arg1)
{
    ui->errorLabel->hide();
    ui->itemInCartLabel->hide();
    ui->quantityErrorLabel->hide();
    ui->payLabel->hide();
}

void Order::on_cancelPushButton_clicked()
{
    this->close();
    MainWindow *win = new MainWindow;
    win->show();
}

void Order::on_removeButton_clicked()
{
    if(ui->tableWidget->rowCount()>0)
    {
        if(!ui->tableWidget->selectedItems().isEmpty())
        {
            QModelIndexList indexes = ui->tableWidget->selectionModel()->selection().indexes();
            for (int i = 0; i < indexes.count(); ++i)
            {
                QModelIndex index = indexes.at(i);
                QTableWidgetItem *item = ui->tableWidget->item(index.row(),2);
                double tests = item->text().toDouble();
                total = total - tests;
                ui->tableWidget->removeRow(index.row());
                ui->totalLabel->setText(QString::number(total));
            }
        }
        else
        {
            ui->selectitemLabel->show();
        }
    }
    else
    {
        ui->payLabel->show();
    }
}

void Order::on_quantityLineEdiit_cursorPositionChanged(int arg1, int arg2)
{
    ui->errorLabel->hide();
    ui->itemInCartLabel->hide();
    ui->quantityErrorLabel->hide();
    ui->payLabel->hide();
}

void Order::on_productCComboBox_activated(const QString &arg1)
{
    ui->errorLabel->hide();
    ui->itemInCartLabel->hide();
    ui->quantityErrorLabel->hide();
    ui->payLabel->hide();
}

void Order::on_tableWidget_clicked(const QModelIndex &index)
{
    ui->selectitemLabel->hide();
    ui->payLabel->hide();
}


void Order::on_tableWidget_itemChanged(QTableWidgetItem *item)
{
    ui->selectitemLabel->hide();
    ui->payLabel->hide();
}


void Order::on_payButton_clicked()
{
    QMessageBox infoBox;
    infoBox.setText("Do You Want To Commit This Transaction?");
    QPushButton *yes = infoBox.addButton(tr("Yes"),QMessageBox::ActionRole);
    QPushButton *cancel = infoBox.addButton(QMessageBox::Abort);

    if(ui->tableWidget->rowCount()>0)
    {
        infoBox.exec();
        QString totalCosts = ui->totalLabel->text();
        QString numberOfProducts = QString::number(ui->tableWidget->rowCount());
        QSqlQuery qry;

        if(infoBox.clickedButton()== yes)
        {
            //Update product quantity in database
            for(int i = 0; i < ui->tableWidget->rowCount(); i++)
            {
                QString quantity = ui->tableWidget->item(i,1)->text();
                QString product = ui->tableWidget->item(i,0)->text();

                qry.prepare("Update products set Quantity=Quantity-'"+quantity+"' where Product_Name ='"+product+"'");
                if(qry.exec())
                {
                    qDebug()<<("Quantity Updated");
                }
                else
                {
                    QMessageBox::critical(this,"Error", qry.lastError().text());
                }
            }

            //Add transaction to database
            qry.prepare("insert into orders(Total_Costs,numberOfitems) values('"+totalCosts+"','"+numberOfProducts+"') ");
            if(qry.exec())
            {
                qry.prepare("Select MAX(Order_Id) from orders"); //Select the
                if(qry.exec())
                {
                    while(qry.next())
                    {
                        QString lastID = qry.value(0).toString();
                        for(int i = 0; i < ui->tableWidget->rowCount(); i++)
                        {
                            QString quantity = ui->tableWidget->item(i,1)->text();
                            QString product = ui->tableWidget->item(i,0)->text();
                            QString price = ui->tableWidget->item(i,2)->text();
                            qry.prepare("insert into ordered_Items(Order_Id, Product_Name, Quantity, Price) values('"+lastID+"', '"+product+"', '"+quantity+"', '"+price+"')");
                            if(qry.exec())
                            {
                                qDebug()<<("Each Product Successfully Added!");

                            }
                            else
                            {
                                QMessageBox::critical(this,"Error", "Each Items not Added to database!");
                            }
                        }
                        QMessageBox::information(this, "Success", "Order Successfully Placed! Thanks for Shoping with us!");

                        ui->tableWidget->setRowCount(0);
                        total = 0;
                        ui->quantityLineEdiit->clear();
                        ui->totalLabel->setText("");
                        if(!ui->productCComboBox->currentIndex()==0)
                        {
                            ui->productCComboBox->setCurrentIndex(0);
                        }
                        else
                        {
                            ui->productCComboBox->setCurrentIndex(1);
                        }
                    }
                }
                else
                {
                    QMessageBox::critical(this,"Error", "No Item Selected In Order Table!");
                }
            }
            else
            {
                QMessageBox::critical(this,"Error", "Transaction not successfully Recorded!");
            }
        }
        else if(infoBox.clickedButton()== cancel)
        {
            return;
        }
    }
    else
    {
        ui->payLabel->show();
    }
}

#ifndef ORDER_H
#define ORDER_H
#include "databaseconnection.h"
#include <QMainWindow>

#include <QTableWidgetItem>

namespace Ui {
class Order;
}

class Order : public QMainWindow
{
    Q_OBJECT

public:
    explicit Order(QWidget *parent = 0);
    ~Order();

private slots:
    void on_productCComboBox_currentTextChanged(const QString &arg1);

    void on_addToCartButton_clicked();

    void on_quantityLineEdiit_textChanged(const QString &arg1);

    void on_productCComboBox_currentIndexChanged(const QString &arg1);

    void on_cancelPushButton_clicked();

    void on_removeButton_clicked();

    void on_quantityLineEdiit_cursorPositionChanged(int arg1, int arg2);

    void on_productCComboBox_activated(const QString &arg1);

    void on_tableWidget_clicked(const QModelIndex &index);

    void on_tableWidget_itemChanged(QTableWidgetItem *item);

    void on_payButton_clicked();

private:
    Ui::Order *ui;
    DatabaseConnection con;
    double total;
};

#endif // ORDER_H

#ifndef PRODUCTS_H
#define PRODUCTS_H
#include "databaseconnection.h"

#include <QMainWindow>

namespace Ui {
class Products;
}

class Products : public QMainWindow
{
    Q_OBJECT

public:
    explicit Products(QWidget *parent = 0);
    ~Products();

private slots:
    void on_saveButton_clicked();

    void on_cancelButton_clicked();

    void on_productID_textEdited(const QString &arg1);

    void on_productNameEdit_textEdited(const QString &arg1);

    void on_productPrice_textEdited(const QString &arg1);

    void on_manufactureeName_textEdited(const QString &arg1);

    void on_quantityEdit_textEdited(const QString &arg1);

    void on_quantityEdit_returnPressed();

private:
    Ui::Products *ui;
    DatabaseConnection con;
};

#endif // PRODUCTS_H

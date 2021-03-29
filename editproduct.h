#ifndef EDITPRODUCT_H
#define EDITPRODUCT_H
#include "databaseconnection.h"
#include <QMainWindow>

namespace Ui {
class EditProduct;
}

class EditProduct : public QMainWindow
{
    Q_OBJECT

public:
    explicit EditProduct(QWidget *parent = 0);
    ~EditProduct();

private slots:
    void on_backButton_clicked();

    void on_goButton_clicked();

    void on_productIdEdit_textEdited(const QString &arg1);

    void on_saveButton_clicked();

    void on_cancelButton_clicked();

private:
    Ui::EditProduct *ui;
    DatabaseConnection con;
};

#endif // EDITPRODUCT_H

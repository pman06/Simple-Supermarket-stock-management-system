#ifndef DELETEPRODUCTS_H
#define DELETEPRODUCTS_H
#include "databaseconnection.h"
#include <QMainWindow>

namespace Ui {
class DeleteProducts;
}

class DeleteProducts : public QMainWindow
{
    Q_OBJECT

public:
    explicit DeleteProducts(QWidget *parent = 0);
    ~DeleteProducts();

private slots:
    void on_loadButton_clicked();

    void on_cancelButton_clicked();

    void on_deleteButton_clicked();

    void on_productLineEdit_textEdited(const QString &arg1);

    void on_productLineEdit_returnPressed();

private:
    Ui::DeleteProducts *ui;
    DatabaseConnection con;
};

#endif // DELETEPRODUCTS_H

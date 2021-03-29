#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "editproduct.h"
#include "products.h"
#include "deleteproducts.h"
#include "viewproductsform.h"
#include "order.h"
#include "transactions.h"
#include "newemployee.h"

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_processOrderButton_clicked();

    void on_addButton_clicked();

    void on_editButton_clicked();

    void on_deleteButton_clicked();

    void on_viewButton_clicked();

    void on_transactionsButton_clicked();

    void on_adminButton_clicked();

private:
    Ui::MainWindow *ui;
    Products *product;
    EditProduct *editForm;
    DeleteProducts *delForm;
    ViewProductsForm *viewForm;
    Order *form;
    Transactions *transaction;
    NewEmployee *adminReg;
};

#endif // MAINWINDOW_H

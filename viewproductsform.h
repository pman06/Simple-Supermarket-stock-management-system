#ifndef VIEWPRODUCTSFORM_H
#define VIEWPRODUCTSFORM_H
#include "databaseconnection.h"
#include <QMainWindow>

namespace Ui {
class ViewProductsForm;
}

class ViewProductsForm : public QMainWindow
{
    Q_OBJECT

public:
    explicit ViewProductsForm(QWidget *parent = 0);
    ~ViewProductsForm();

private slots:
    void on_loadPushButton_clicked();

    void on_backPushButton_clicked();

private:
    Ui::ViewProductsForm *ui;
    DatabaseConnection con;
};

#endif // VIEWPRODUCTSFORM_H

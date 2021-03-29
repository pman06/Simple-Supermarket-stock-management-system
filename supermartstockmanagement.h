#ifndef SUPERMARTSTOCKMANAGEMENT_H
#define SUPERMARTSTOCKMANAGEMENT_H
#include <databaseconnection.h>

#include <QMainWindow>

namespace Ui {
class SupermartStockManagement;
}

class SupermartStockManagement : public QMainWindow
{
    Q_OBJECT

public:
    explicit SupermartStockManagement(QWidget *parent = 0);
    ~SupermartStockManagement();

private slots:
    void on_loginButton_clicked();
    
    void on_usernameEdit_textEdited(const QString &arg1);

    void on_passwordEdit_returnPressed();

    void on_passwordEdit_textEdited(const QString &arg1);

private:
    Ui::SupermartStockManagement *ui;
    DatabaseConnection con;
};

#endif // SUPERMARTSTOCKMANAGEMENT_H

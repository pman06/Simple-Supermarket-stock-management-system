#ifndef TRANSACTIONS_H
#define TRANSACTIONS_H
#include "databaseconnection.h"

#include <QMainWindow>


namespace Ui {
class Transactions;
}

class Transactions : public QMainWindow
{
    Q_OBJECT

public:
    explicit Transactions(QWidget *parent = 0);
    ~Transactions();

private slots:
    void on_backButton_clicked();

    void on_transactionButton_clicked();

    void on_transactionView_clicked(const QModelIndex &index);

private:
    Ui::Transactions *ui;
    DatabaseConnection con;
};

#endif // TRANSACTIONS_H

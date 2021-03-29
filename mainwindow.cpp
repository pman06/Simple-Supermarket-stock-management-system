#include "mainwindow.h"
#include "ui_mainwindow.h"



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_processOrderButton_clicked()
{
    this->hide();
    form = new Order();
    form->show();
}

void MainWindow::on_addButton_clicked()
{
    this->close();
    product = new Products();
    product->show();
}

void MainWindow::on_editButton_clicked()
{
    this->close();
    editForm = new EditProduct();
    editForm->show();
}

void MainWindow::on_deleteButton_clicked()
{
    this->close();
    delForm = new DeleteProducts;
    delForm->show();
}

void MainWindow::on_viewButton_clicked()
{
    this->close();
    viewForm = new ViewProductsForm();
    viewForm->show();
}

void MainWindow::on_transactionsButton_clicked()
{
    this->hide();
    transaction = new Transactions;
    transaction->show();
}

void MainWindow::on_adminButton_clicked()
{
    this->hide();
    adminReg = new NewEmployee;
    adminReg->show();
}

#include "paymentsummary.h"
#include "ui_paymentsummary.h"

PaymentSummary::PaymentSummary(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PaymentSummary)
{
    ui->setupUi(this);
}

PaymentSummary::~PaymentSummary()
{
    delete ui;
}

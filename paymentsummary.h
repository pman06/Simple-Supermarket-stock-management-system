#ifndef PAYMENTSUMMARY_H
#define PAYMENTSUMMARY_H

#include <QDialog>

namespace Ui {
class PaymentSummary;
}

class PaymentSummary : public QDialog
{
    Q_OBJECT

public:
    explicit PaymentSummary(QWidget *parent = 0);
    ~PaymentSummary();

private:
    Ui::PaymentSummary *ui;
};

#endif // PAYMENTSUMMARY_H

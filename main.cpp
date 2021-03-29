#include "supermartstockmanagement.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    SupermartStockManagement w;
    w.show();

    return a.exec();
}

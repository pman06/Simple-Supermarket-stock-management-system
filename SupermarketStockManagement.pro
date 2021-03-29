#-------------------------------------------------
#
# Project created by QtCreator 2018-04-24T05:28:19
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SupermarketStockManagement
TEMPLATE = app


SOURCES += main.cpp\
        supermartstockmanagement.cpp \
    databaseconnection.cpp \
    mainwindow.cpp \
    order.cpp \
    products.cpp \
    editproduct.cpp \
    deleteproducts.cpp \
    viewproductsform.cpp \
    paymentsummary.cpp \
    transactions.cpp \
    newemployee.cpp

HEADERS  += supermartstockmanagement.h \
    databaseconnection.h \
    mainwindow.h \
    order.h \
    products.h \
    editproduct.h \
    deleteproducts.h \
    viewproductsform.h \
    paymentsummary.h \
    transactions.h \
    newemployee.h

FORMS    += supermartstockmanagement.ui \
    mainwindow.ui \
    order.ui \
    products.ui \
    editproduct.ui \
    deleteproducts.ui \
    viewproductsform.ui \
    paymentsummary.ui \
    transactions.ui \
    newemployee.ui

RESOURCES += \
    resources.qrc

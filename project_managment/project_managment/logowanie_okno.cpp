#include "logowanie_okno.h"
#include <qmessagebox.h>
#include <QLineEdit>
#include <qstring.h>
#include "klasy.h"



logowanie_okno::logowanie_okno(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
}

logowanie_okno::~logowanie_okno()
{
}

void logowanie_okno::on_pushButton_login_clicked()
{
    Fun_okno_logowania logowanie;
    QString username = ui.lineEdit_username->text();
    QString password = ui.lineEdit_password->text();
    
    if (logowanie.logowanie(username.toStdString(), password.toStdString()))
    {

        //tutaj bêdzie logowanie
        QMessageBox::information(this, "Login", "correct");
    }
    else
    {
        QMessageBox::information(this, "Login", "incorrect, try again");
    }
    
}

void logowanie_okno::on_pushButton_register_clicked()
{
    ui.stackedWidget->setCurrentIndex(1);
}

void logowanie_okno::on_pushButton_register_2_clicked()
{
    //TODO 
    //Dodawanie u¿ytkownika do bazy danych
}

void logowanie_okno::on_pushButton_cancel_clicked()
{
    ui.stackedWidget->setCurrentIndex(0);
}
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
    QString username = ui.lineEdit_username->text();
    QString password = ui.lineEdit_password->text();
    
    if (Fun_okno_logowania::logowanie(username.toStdString(), password.toStdString()))
    {
        string msg = "zalogowano jako " + username.toStdString();
        char temp2[35];
        strcpy(temp2, msg.c_str());
        QMessageBox::information(this, "Login", temp2);
        this->hidden->show();
        this->close();
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
    QString imie = ui.lineEdit_1_imie->text();
    QString nazwisko = ui.lineEdit_2_nazwisko->text();
    QString login = ui.lineEdit_3_login->text();
    QString haslo = ui.lineEdit_4_haslo->text();
    QString powtorz_haslo = ui.lineEdit_5_powtorz_haslo->text();

    //TODO
    //Sprawdzanie poprawnosci danych i wyswietlanie komunikatow
    if (haslo == powtorz_haslo)
    {
       if (Fun_okno_logowania::rejestracja(imie.toStdString(), nazwisko.toStdString(), login.toStdString(), haslo.toStdString()));
        ui.stackedWidget->setCurrentIndex(0);
    }

}

void logowanie_okno::on_pushButton_cancel_clicked()
{
    ui.stackedWidget->setCurrentIndex(0);
}


void logowanie_okno::setwindow(project_managment* newhidden)
{
    this->hidden = newhidden;
}

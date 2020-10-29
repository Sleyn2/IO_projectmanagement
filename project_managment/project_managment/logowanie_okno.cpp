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
        //TODO
        //przejscie do bastepnego okna

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
  
    Fun_okno_logowania rejestracja;
    QString imie = ui.lineEdit_imie->text();
    QString nazwisko = ui.lineEdit_nazwisko->text();
    QString login = ui.lineEdit_login->text();
    QString haslo = ui.lineEdit_haslo->text();
    QString powtorz_haslo = ui.lineEdit_powtorz_haslo->text();

    //TODO
    //Sprawdzanie poprawnosci danych i wyswietlanie komunikatow
    if (haslo == powtorz_haslo)
    {
       if ( rejestracja.rejestracja(imie.toStdString(), nazwisko.toStdString(), login.toStdString(), haslo.toStdString()));
        ui.stackedWidget->setCurrentIndex(0);
    }

}

void logowanie_okno::on_pushButton_cancel_clicked()
{
    ui.stackedWidget->setCurrentIndex(0);
}
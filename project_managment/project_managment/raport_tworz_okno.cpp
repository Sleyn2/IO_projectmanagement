#include <QMessageBox>

#include "raport_tworz_okno.h"
#include "klasy.h"

raport_tworz_okno::raport_tworz_okno(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
}

raport_tworz_okno::~raport_tworz_okno()
{
}

void raport_tworz_okno::ustawWyswietlRaport(Raport raport)
{
	string dane = raport.pobierz_tytul();
	ui.labelTytul->setText(QString::fromStdString(dane));
	dane = raport.pobierz_status();
	ui.labelStatus->setText(QString::fromStdString(dane));
	dane = raport.pobierz_opis();
	ui.textTresc->setPlainText(QString::fromStdString(dane));
	ui.stackedWidget->setCurrentIndex(0);
	/*
	ui.labelTytul->setText(QString::fromStdString(raport.pobierz_tytul()));
	ui.labelStatus->setText(QString::fromStdString(raport.pobierz_status()));
	ui.textTresc->setPlainText(QString::fromStdString(raport.pobierz_opis()));
	ui.stackedWidget->setCurrentIndex(0);*/
}



void raport_tworz_okno::ustawNapiszRaport()
{
	//ui.labelStatus->clear();
	ui.lineEdit->clear();
	ui.textEdit->clear();
	ui.stackedWidget->setCurrentIndex(1);
}

void raport_tworz_okno::on_pushButtonAnuluj_clicked() {
	this->close();
}

void raport_tworz_okno::on_pushButtonWyslij_clicked()
{
	QString wiadomosc = ui.textEdit->toPlainText();
	QString tytul = ui.lineEdit->text();
	if (tytul == "")
	{
		QMessageBox::information(this, "Error", "Prosze podac tytul");
		return;
	}
	if (wiadomosc == "")
	{
		QMessageBox::information(this, "Error", "Tresc wiadomosci jest pusta");
		return;
	}
	if (Fun_raport::dodaj_raport(wiadomosc.toStdString(), tytul.toStdString())) {}
	else
		QMessageBox::information(this, "Error", QString::fromStdString(Dane_zalogowanego_pracownika::instancja()->pobierz_wyjatek()));
	this->close();
	ui.textEdit->clear();
}

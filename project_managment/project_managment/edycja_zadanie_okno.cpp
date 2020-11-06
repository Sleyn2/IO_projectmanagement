#include "edycja_zadanie_okno.h"

edycja_zadanie_okno::edycja_zadanie_okno(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
}

edycja_zadanie_okno::~edycja_zadanie_okno()
{
}

void edycja_zadanie_okno::wczytaj_dane()
{
	QString nazwa = QString::fromStdString(Dane_zalogowanego_pracownika::instancja()->pobierz_nazwe_zadania());
	QString	data_roz = QString::fromStdString(Fun_projekty::pobierz_dane_zadania().pobierz_data_rozpoczecia());
	QString	data_zak = QString::fromStdString(Fun_projekty::pobierz_dane_zadania().pobierz_data_zakonczenia());
	QString	status = QString::fromStdString(Fun_projekty::pobierz_dane_zadania().pobierz_status());
	QString	opis = QString::fromStdString(Fun_projekty::pobierz_dane_zadania().pobierz_opis());

	ui.textEdit_opis->setText(opis);
	ui.lineEdit_nazwa->setText(nazwa);
	//TODO naprawic import daty
	ui.dateEdit_start->setDate(QDate::fromString(data_roz, "yyy-MM-dd"));
	ui.dateEdit_finish->setDate(QDate::fromString(data_zak, "yyy-MM-dd"));
	if (status == "Rozpoczety")
		ui.comboBox_status->setCurrentIndex(0);
	else if (status == "Zawieszony")
		ui.comboBox_status->setCurrentIndex(1);
	else if (status == "Zamkniêty")
		ui.comboBox_status->setCurrentIndex(2);
}

void edycja_zadanie_okno::on_pushButton_clicked()
{
	this->dodaj_nowych_uzytkownikow.show();
}

void edycja_zadanie_okno::on_pushButton_anuluj_clicked()
{
	this->close();
}

void edycja_zadanie_okno::on_pushButton_potwierdz_clicked()
{
	QString nazwa = ui.lineEdit_nazwa->text();
	QString status = ui.comboBox_status->currentText();
	QString start_date = ui.dateEdit_start->text();
	QString finish_date = ui.dateEdit_finish->text();
	QString opis = ui.textEdit_opis->toPlainText();
	
	Fun_projekty::zaktualizuj_zadanie(nazwa.toStdString(), opis.toStdString(), start_date.toStdString(), finish_date.toStdString(), status.toStdString());
	this->close();
}

void edycja_zadanie_okno::on_pushButton_usun_clicked()
{
	//Fun_projekty::usun_zadanie();
}

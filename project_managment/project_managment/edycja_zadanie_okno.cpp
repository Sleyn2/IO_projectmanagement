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
	
	
	
	
	
	ui.lineEdit_nazwa->setText(nazwa);
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
}

void edycja_zadanie_okno::on_pushButton_usun_clicked()
{
	//Fun_projekty::usun_zadanie();
}

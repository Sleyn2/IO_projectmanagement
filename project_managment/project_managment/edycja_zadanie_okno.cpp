#include "edycja_zadanie_okno.h"

edycja_zadanie_okno::edycja_zadanie_okno(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
}

edycja_zadanie_okno::~edycja_zadanie_okno()
{
}

void wczytaj_dane()
{

}

void edycja_zadanie_okno::on_pushButton_anuluj_clicked()
{
	this->close();
}

void edycja_zadanie_okno::on_pushButton_potwierdz_clicked()
{
	//TODO zapisz zmienione zadanie

	QString nazwa = ui.lineEdit_nazwa->text();
	QString status = ui.comboBox_status->currentText();
	QString start_date = ui.dateEdit_start->text();
	QString finish_date = ui.dateEdit_finish->text();
	QString opis = ui.textEdit_opis->toPlainText();
}

void edycja_zadanie_okno::on_pushButton_usun_clicked()
{
	//TODO usuñ zaznaczone zadanie
}

#include "projekty_zadania_okno.h"

Projekty_zadania_okno::Projekty_zadania_okno(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
}

Projekty_zadania_okno::~Projekty_zadania_okno()
{
}

void Projekty_zadania_okno::ustaw_tryb(bool czy_projekt)
{
	this->projekt = czy_projekt;
	if (czy_projekt)
		ui.pushButton_add->setText("Dodaj projekt");
	else
		ui.pushButton_add->setText("Dodaj zadanie");

}

void Projekty_zadania_okno::on_pushButton_cancel_clicked()
{
	this->close();
}

void Projekty_zadania_okno::on_pushButton_add_clicked()
{
	QString nazwa = ui.lineEdit_nazwa->text();
	QString status = ui.comboBox_status->currentText();
	QString start_date = ui.dateEdit_start->text();
	QString finish_date = ui.dateEdit_finish->text();
	QString opis = ui.textEdit_opis->toPlainText();
	
	if (this->projekt)
	{
		if(Fun_projekty::utworz_projekt(nazwa.toStdString(), opis.toStdString(), start_date.toStdString(), finish_date.toStdString(), status.toStdString()))
			QMessageBox::information(this, "Projekt", "Dodano projekt");
		else
			QMessageBox::information(this, "Projekt", "Projekt o takiej nazwie ju¿ istnieje");
	}
	else
	{
		if (Fun_projekty::utworz_zadanie(nazwa.toStdString(), opis.toStdString(), start_date.toStdString(), finish_date.toStdString(), status.toStdString()))
			QMessageBox::information(this, "Zadanie", "Dodano zadanie");
		else
			QMessageBox::information(this, "Zadanie", "Zadanie o takiej nazwie ju¿ istnieje");
	}
	
}
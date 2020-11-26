#include "wiadomosci_okno.h"
#include <QMessageBox>
#include <QDateTime>

wiadomosci_okno::wiadomosci_okno(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
}

wiadomosci_okno::~wiadomosci_okno()
{
}
void wiadomosci_okno::ustawTryb(int i)
{
	ui.stackedWidget->setCurrentIndex(i);
	if (i == 0)
		this->odswiezListe();
}
void wiadomosci_okno::ustawWiadomosc(QString temp)
{
	this->messageInfo = temp;
}
void wiadomosci_okno::on_pushButton_send_clicked()
{
	QString tytul = ui.lineEdit_Title->text();
	QString wiadomosc = ui.textEdit->toPlainText();
	QString adresat = ui.comboBox->currentText();
	if (wiadomosc == "")
	{
		QMessageBox::information(this, "Error", "Tresc wiadomosci jest pusta");
		return;
	}
	if (tytul == "")
	{
		QMessageBox::information(this, "Error", "Prosze wstawic tytul");
		return;
	}
	vector<string> name = podzial_stringa_na_slowa(adresat.toStdString());
	if (Fun_wiadomosci::dodaj_wiadomosc(name[0], QDateTime::currentDateTime().toString().toStdString(), wiadomosc.toStdString(), tytul.toStdString())){}
	else
		QMessageBox::information(this, "Error", QString::fromStdString(Dane_zalogowanego_pracownika::instancja()->pobierz_wyjatek()));
}
void wiadomosci_okno::on_pushButton_cancel_clicked()
{
	this->close();
}
void wiadomosci_okno::odswiezListe()
{
	users.clear();
	users = Fun_projekty::pobierz_liste_pracownikow();
	users.sort();
	ui.comboBox->addItems(users);
}

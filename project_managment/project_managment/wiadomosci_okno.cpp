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
void wiadomosci_okno::ustawTryb(int i, bool czy_wyslana)
{
	ui.stackedWidget->setCurrentIndex(i);
	if (i == 0)
		this->odswiezListe();
	else if (i == 1)
	{
		vector<string> text = podzial_stringa_na_slowa(messageInfo.toStdString());
		
		//QString tresc = Fun_wiadomosci::pobierz_tresc(id, text[3], czy_wyslana);
		ui.topic_label->setText(QString::fromStdString(text[0]));
		//ui.textBrowser->setPlainText(tresc);
		if (czy_wyslana)
		{
			ui.writer_label->setText(QString::fromStdString(Dane_zalogowanego_pracownika::instancja()->pobierz_imie() + Dane_zalogowanego_pracownika::instancja()->pobierz_nazwisko()));
			ui.reciver_label->setText(QString::fromStdString(text[2] + text[3]));
		}
		else
		{
			ui.reciver_label->setText(QString::fromStdString(Dane_zalogowanego_pracownika::instancja()->pobierz_imie() + Dane_zalogowanego_pracownika::instancja()->pobierz_nazwisko()));
			ui.writer_label->setText(QString::fromStdString(text[2] + text[3]));
		}
	}
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
	if (Fun_wiadomosci::dodaj_wiadomosc(seperacja_stringa_od_kropki(name[0]), QDateTime::currentDateTime().toString().toStdString(), wiadomosc.toStdString(), tytul.toStdString())){}
	else
		QMessageBox::information(this, "Error", QString::fromStdString(Dane_zalogowanego_pracownika::instancja()->pobierz_wyjatek()));
}
void wiadomosci_okno::on_pushButton_cancel_clicked()
{
	this->close();
}
void wiadomosci_okno::on_pushButton_cancel2_clicked()
{
	this->close();
}
void wiadomosci_okno::on_pushButton_answer_clicked()
{
	//TODO odpowiedŸ z kopi¹ tematu + Re: 
}
void wiadomosci_okno::odswiezListe()
{
	users.clear();
	users = Fun_projekty::pobierz_liste_pracownikow();
	users.sort();
	ui.comboBox->addItems(users);
}

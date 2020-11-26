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
		int n = text.size();
		//QString tresc = Fun_wiadomosci::pobierz_tresc(seperacja_stringa_od_kropki(text[n-7]), text[n-5], czy_wyslana);
		string topic = "";
		for (int i = 0; i < (n-7); i++)
		{
			topic += text[i];
		}
		ui.topic_label->setText(QString::fromStdString(topic));
		this->msgTopic = topic;
		ui.textBrowser->setPlainText("tresc");
		ui.date_label->setText(QString::fromStdString(text[n - 4] + text[n - 3] + text[n - 2] + text[n-1]));

		if (czy_wyslana)
		{
			ui.pushButton_answer->hide();
			ui.writer_label->setText(QString::fromStdString(Dane_zalogowanego_pracownika::instancja()->pobierz_id_pracownika() + Dane_zalogowanego_pracownika::instancja()->pobierz_imie() + Dane_zalogowanego_pracownika::instancja()->pobierz_nazwisko()));
			ui.reciver_label->setText(QString::fromStdString(text[n-7] + text[n-6] + text[n-5]));
		}
		else
		{
			ui.pushButton_answer->show();
			ui.reciver_label->setText(QString::fromStdString(Dane_zalogowanego_pracownika::instancja()->pobierz_id_pracownika() + Dane_zalogowanego_pracownika::instancja()->pobierz_imie() + Dane_zalogowanego_pracownika::instancja()->pobierz_nazwisko()));
			ui.writer_label->setText(QString::fromStdString(text[n-7] + text[n-6] + text[n-5]));
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
void wiadomosci_okno::on_pushButton_cancel_2_clicked()
{
	this->close();
}
void wiadomosci_okno::on_pushButton_answer_clicked()
{
	ui.stackedWidget->setCurrentIndex(0);
	//TODO ustaw odbiorce
	ui.lineEdit_Title->setText(QString::fromStdString("Re: " + this->msgTopic));
}
void wiadomosci_okno::odswiezListe()
{
	users.clear();
	users = Fun_projekty::pobierz_liste_pracownikow();
	users.sort();
	ui.comboBox->addItems(users);
}

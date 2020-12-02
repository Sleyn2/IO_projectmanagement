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
		string date = text[n-5] + " " + text[n - 4] + " " + text[n - 3] + " " + text[n - 2] + " " + text[n - 1];
		string id = seperacja_stringa_od_kropki(text[n - 8]);
		string name1 = text[n - 8] + " " + text[n - 7] + " " + text[n - 6];
		string name2 = 
			Dane_zalogowanego_pracownika::instancja()->pobierz_id_pracownika() + ". " +
			Dane_zalogowanego_pracownika::instancja()->pobierz_imie() + " " +
			Dane_zalogowanego_pracownika::instancja()->pobierz_nazwisko();
		QString tresc = Fun_wiadomosci::pobierz_tresc(id, date, czy_wyslana);
		string topic = "";
		for (int i = 0; i < (n-8); i++)
		{
			topic += text[i];
		}
		ui.topic_label->setText(QString::fromStdString(topic));
		this->msgTopic = topic;
		ui.textBrowser->setPlainText(tresc);
		ui.date_label->setText(QString::fromStdString(date));

		if (czy_wyslana)
		{
			ui.pushButton_answer->hide();
			ui.writer_label->setText(QString::fromStdString(name2));
			ui.reciver_label->setText(QString::fromStdString(name1));
		}
		else
		{
			ui.pushButton_answer->show();
			ui.reciver_label->setText(QString::fromStdString(name2));
			this->answerAdress = name1;
			ui.writer_label->setText(QString::fromStdString(name1));
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
	this->close();
	ui.lineEdit_Title->clear();
	ui.textEdit->clear();
	ui.comboBox->setCurrentIndex(0);
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
	this->odswiezListe();
	for (int i = 0; i < 10; i++)
	{
		if (this->users[i].toStdString() == answerAdress)
			ui.comboBox->setCurrentIndex(i);
	}
	ui.lineEdit_Title->setText(QString::fromStdString("Re: " + this->msgTopic));
}
void wiadomosci_okno::odswiezListe()
{
	users.clear();
	users = Fun_projekty::pobierz_liste_pracownikow();
	users.sort();
	ui.comboBox->addItems(users);
}

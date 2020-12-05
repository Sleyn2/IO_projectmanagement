#include "raport_edycja_okno.h"
#include <QMessageBox>
#include <QDateTime>

raport_edycja_okno::raport_edycja_okno(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
}

raport_edycja_okno::~raport_edycja_okno()
{
}

void raport_edycja_okno::ustawVectorRaportow(vector<Raport>* pRaporty)
{
	this->pRaporty = pRaporty;
}

void raport_edycja_okno::ustawIndex(int idx) {
	index = idx;
}

void raport_edycja_okno::wczytajDane()
{
	vector<Pracownik> pracownik = Pobieranie_bazy::pobierz_pracownik("select * from pracownicy where id_pracownika = '" + (*pRaporty)[index].pobierz_id_nadawcy() + "'");
	vector<Projekt> projekt = Pobieranie_bazy::pobierz_projekt("select * from projekt where id_projektu = '" + (*pRaporty)[index].pobierz_id_projektu() + "'");
	if (projekt[0].pobierz_zadanie() == "false")
		ui.labelTematCzego->setText(QString::fromStdString("Projekt"));
	else
		ui.labelTematCzego->setText(QString::fromStdString("Zadanie"));
	ui.labelNadawca->setText(QString::fromStdString(pracownik[0].pobierz_imie() + " " + pracownik[0].pobierz_nazwisko()));
	ui.labelTemat->setText(QString::fromStdString(projekt[0].pobierz_nazwa()));
	ui.labelTytul->setText(QString::fromStdString((*pRaporty)[0].pobierz_tytul()));
	ui.textRaportTresc->setPlainText(QString::fromStdString((*pRaporty)[index].pobierz_opis()));
}

void raport_edycja_okno::ustawPierwszaStrone()
{
	ui.stackedWidget->setCurrentIndex(0);
}

void raport_edycja_okno::on_pushButtonRaportZaakceptuj_clicked()
{
	zwrot = 1;
	ui.stackedWidget->setCurrentIndex(1);
}

void raport_edycja_okno::on_pushButtonRaportZwroc_clicked()
{
	zwrot = 2;
	ui.stackedWidget->setCurrentIndex(1);
}

void raport_edycja_okno::on_pushButtonOdpowiedzRaport_clicked()
{
	QString tytul;
	if (zwrot == 2)
		tytul = QString("Raport zostal zwrocony");
	else if (zwrot == 1)
		tytul = QString("Raport zostal zatwierdzony");
	else
		return;
	QString wiadomosc = ui.textEditOdpowiedzTresc->toPlainText();
	if (wiadomosc == "")
	{
		QMessageBox::information(this, "Error", "Tresc wiadomosci jest pusta");
		return;
	}
	if (Fun_wiadomosci::dodaj_wiadomosc((*pRaporty)[index].pobierz_id_nadawcy(), QDateTime::currentDateTime().toString().toStdString(), wiadomosc.toStdString(), tytul.toStdString(), std::to_string(zwrot))) {}
	else
		QMessageBox::information(this, "Error", QString::fromStdString(Dane_zalogowanego_pracownika::instancja()->pobierz_wyjatek()));
	this->close();
	ui.textEditOdpowiedzTresc->clear();
}

void raport_edycja_okno::on_pushButtonOdpowiedzAnuluj_clicked()
{
	ui.textEditOdpowiedzTresc->clear();
	ui.stackedWidget->setCurrentIndex(0);
}

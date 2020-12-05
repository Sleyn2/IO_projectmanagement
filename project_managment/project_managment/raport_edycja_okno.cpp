#include "raport_edycja_okno.h"

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
	ui.textTresc->setPlainText(QString::fromStdString((*pRaporty)[index].pobierz_opis()));
}

void raport_edycja_okno::on_pushButtonZaakceptuj_clicked()
{
	zwrot = false;
	ui.stackedWidget->currentIndex(1);
}

void raport_edycja_okno::on_pushButtonZwroc_clicked()
{
	zwrot = true;
	ui.stackedWidget->setCurrentIndex(1);
}

void raport_edycja_okno::on_pushButtonOdpowiedzRaport_clicked()
{

}

void raport_edycja_okno::on_pushButtonOdpowiedzAnuluj_clicked()
{
	ui.textEditTresc->clean();
	ui.stackedWidget->setCurrentIndex(0);
}

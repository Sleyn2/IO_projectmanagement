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
	//ui.labelNadawca
}

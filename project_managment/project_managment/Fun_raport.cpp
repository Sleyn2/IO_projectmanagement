#include "klasy.h"
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <set>

bool Fun_raport::dodaj_raport(string tresc, string tytul) 
{
	//zmiana z id_projektu_nadrzednego na id_proektu
	Raport raport(Dane_zalogowanego_pracownika::instancja()->pobierz_id_pracownika(), tytul, tresc, string("nowy"),
		Dane_zalogowanego_pracownika::instancja()->pobierz_id_projektu());
	if(Modyfikator_bazy::dodaj_raport(&raport))
		return true;
	else
		return false;
}

QStringList Fun_raport::vectorRaportowNaQStringList(vector<Raport> raporty)
{
	QStringList lista;
	for (auto elem : raporty)
		lista.append(QString::fromStdString(elem.pobierz_tytul()));
	return lista;
}

vector<Raport> Fun_raport::sprawdzRaport()
{
	vector<Raport> raporty = Pobieranie_bazy::pobierz_jeden_raport(string("select * from raporty where id_projektu = '" +
		Dane_zalogowanego_pracownika::instancja()->pobierz_id_projektu() + "' and status!='zwrocony';"));
	/*
	vector<Raport> raporty = Pobieranie_bazy::pobierz_jeden_raport(string("select * from raporty where id_nadawcy = '" +
		Dane_zalogowanego_pracownika::instancja()->pobierz_id_pracownika() + "' and id_projektu = '" +
		Dane_zalogowanego_pracownika::instancja()->pobierz_id_projektu_nadrzednego() + "' and status!='zwrocony';"));
	*/
	return raporty;
}

bool Fun_raport::sprawdzCzyJestKorzeniem() {
	vector<Projekt> projekty = Pobieranie_bazy::pobierz_projekt(string("select * from projekt where id_projektu = " +
		Dane_zalogowanego_pracownika::instancja()->pobierz_id_projektu() + " ;"));
	if (projekty.size())
		if (projekty[0].pobierz_id_projektu_nadrzednego() != "")
			return false;
		else
			return true;
	return true;
}

void Fun_raport::zmienStanRaportu(int stan, string id_raportu)
{
	if (stan == 2)
		Modyfikator_bazy::zaktualizuj_raport("zwrocony", id_raportu);
	else if (stan == 1)
		Modyfikator_bazy::zaktualizuj_raport("zaakceptowany", id_raportu);
}

#include "klasy.h"
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

bool Fun_raport::dodaj_raport(string tytul, string tresc) {
	///* initialize random seed: */
	//srand(time(NULL));

	///* generate secret number between 1 and 10: */
	//string id_raportu = std::to_string(rand());

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

bool Fun_raport::sprawdŸRaport()
{
	vector<Raport> raporty = Pobieranie_bazy::pobierz_jeden_raport(string("select * from raporty where id_nadawcy = '" +
		Dane_zalogowanego_pracownika::instancja()->pobierz_id_pracownika() + "' and id_projektu = '" +
		Dane_zalogowanego_pracownika::instancja()->pobierz_id_projektu() + "'"));
	for (auto elem : raporty)
		if (elem.pobierz_status() == "nowy")
			return true;
		else
			return false;
}

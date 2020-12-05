#include "klasy.h"
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

bool Fun_raport::dodaj_raport(string tresc) {
	/* initialize random seed: */
	srand(time(NULL));

	/* generate secret number between 1 and 10: */
	string id_raportu = std::to_string(rand());

	Raport raport(id_raportu,tresc, string("nowy"), Dane_zalogowanego_pracownika::instancja()->pobierz_id_projektu());
	if(Modyfikator_bazy::dodaj_raport(&raport))
		return true;
	else
		return false;
}

QStringList Fun_raport::vectorRaportowNaQStringList(vector<Raport> raporty)
{
	QStringList lista;
	for (auto elem : raporty)
		lista.append(QString::fromStdString(elem.pobierz_opis()));
	return lista;
}


#include "klasy.h"

bool Fun_wiadomosci::dodaj_wiadomosc(string id_odb, string data_wys, string tresc, string temat)
{
	Wiadomosc wiadomosc(id_odb, data_wys, tresc, Dane_zalogowanego_pracownika::instancja()->pobierz_id_pracownika(), temat);
	if (Modyfikator_bazy::dodaj_wiadomosc(&wiadomosc)) return true;
	else return false;
}

bool Fun_wiadomosci::usun_wiadomosc(string id_odb, string data_wys)
{
	if (Modyfikator_bazy::usun_wiadomosc(id_odb, data_wys, Dane_zalogowanego_pracownika::instancja()->pobierz_id_pracownika())) return true;
	else return false;
}

QStringList Fun_wiadomosci::pobierz_wiadomosci()
{
	vector<Wiadomosc>wiadomosci = Pobieranie_bazy::pobierz_wiadomosc("select * from Wiadomosci where Id_nadawcy = " + Dane_zalogowanego_pracownika::instancja()->pobierz_id_pracownika()+  "");
	QStringList lista;

	for (auto i = wiadomosci.begin(); i != wiadomosci.end(); ++i)
	{
		QStringList lista;
		vector<Pracownik>pracownik = Pobieranie_bazy::pobierz_pracownik("select * from Pracownicy where Id_pracownika = " + i->pobierz_id_nadawcy() + "");

		lista.append(QString::fromStdString(i->pobierz_temat() + " " + pracownik[0].pobierz_imie()+ " " + pracownik[0].pobierz_nazwisko() + " " + i->pobierz_data_wyslania()));
	}
	if (lista.empty()) lista.append(QString::fromStdString("Brak wiadomosc"));
	else return lista;
}
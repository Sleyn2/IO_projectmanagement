#include "klasy.h"

bool Fun_wiadomosci::dodaj_wiadomosc(string id_odb, string data_wys, string tresc, string temat)
{
	Wiadomosc wiadomosc(id_odb, data_wys, tresc, Dane_zalogowanego_pracownika::instancja()->pobierz_id_pracownika(), temat);
	if (Modyfikator_bazy::dodaj_wiadomosc(&wiadomosc)) return true;
	else return false;
}

bool Fun_wiadomosci::usun_wiadomosc(string imie, string nazwisko, string data_wys)
{
	vector<Pracownik> pracownik = Pobieranie_bazy::pobierz_pracownik("select *from Pracownicy where Imie = '" + imie + "' and Nazwisko = '" + nazwisko + "'");
	if (Dane_zalogowanego_pracownika::instancja()->pobierz_czy_blad()) return false;
	if (Modyfikator_bazy::usun_wiadomosc(pracownik[0].pobierz_id_pracownika(), data_wys, Dane_zalogowanego_pracownika::instancja()->pobierz_id_pracownika())) return true;
	else return false;
}

QStringList Fun_wiadomosci::pobierz_wiadomosci(bool wysylanie)
{
	if (wysylanie)
	{
		vector<Wiadomosc>wiadomosci = Pobieranie_bazy::pobierz_wiadomosc("select * from Wiadomosci where Id_nadawcy = " + Dane_zalogowanego_pracownika::instancja()->pobierz_id_pracownika() + "");	
		QStringList lista;
		if ( Dane_zalogowanego_pracownika::instancja()->pobierz_czy_blad()) return lista;
		vector<Pracownik>pracownik = Pobieranie_bazy::pobierz_pracownik("select * from Pracownicy where Id_pracownika = " + Dane_zalogowanego_pracownika::instancja()->pobierz_id_pracownika() + "");
		for (auto i = wiadomosci.begin(); i != wiadomosci.end(); ++i)
		{
			lista.append(QString::fromStdString(i->pobierz_temat() + " " + pracownik[0].pobierz_imie() + " " + pracownik[0].pobierz_nazwisko() + " " + i->pobierz_data_wyslania()));
		}
		if (lista.empty())
		{
			lista.append(QString::fromStdString("Brak wiadomosci"));
			return lista;
		}
		else return lista;
	}
	else
	{
		vector<Wiadomosc>wiadomosci = Pobieranie_bazy::pobierz_wiadomosc("select * from Wiadomosci where Id_odbiorcy = " + Dane_zalogowanego_pracownika::instancja()->pobierz_id_pracownika() + "");
		QStringList lista;
		if (Dane_zalogowanego_pracownika::instancja()->pobierz_czy_blad()) return lista;
		vector<Pracownik>pracownik = Pobieranie_bazy::pobierz_pracownik("select * from Pracownicy where Id_pracownika = " + Dane_zalogowanego_pracownika::instancja()->pobierz_id_pracownika() + "");
		for (auto i = wiadomosci.begin(); i != wiadomosci.end(); ++i)
		{
			lista.append(QString::fromStdString(i->pobierz_temat() + " " + pracownik[0].pobierz_imie() + " " + pracownik[0].pobierz_nazwisko() + " " + i->pobierz_data_wyslania()));
		}
		if (lista.empty())
		{
			lista.append(QString::fromStdString("Brak wiadomosci"));
			return lista;
		}
		else return lista;
	}
		
}

vector<string> podzial_stringa_na_slowa(string str)
{
	vector<string> slowa;
	string slowo = "";
	for (auto x : str)
	{
		if (x == ' ')
		{
			slowa.push_back(slowo);
			slowo = "";
		}
		else {
			slowo = slowo + x;
		}
	}
	return slowa;
}
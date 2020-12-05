#include "klasy.h"

bool Fun_wiadomosci::dodaj_wiadomosc(string id_odb, string data_wys, string tresc, string temat)
{
	Wiadomosc wiadomosc(id_odb, data_wys, tresc, temat, Dane_zalogowanego_pracownika::instancja()->pobierz_id_pracownika());
	if (Modyfikator_bazy::dodaj_wiadomosc(&wiadomosc)) return true;
	else return false;
}
bool Fun_wiadomosci::dodaj_wiadomosc(string id_odb, string data_wys, string tresc, string temat, string typ)
{
	Wiadomosc wiadomosc(id_odb, data_wys, tresc, temat, Dane_zalogowanego_pracownika::instancja()->pobierz_id_pracownika(), typ);
	if (Modyfikator_bazy::dodaj_wiadomosc_raportu(&wiadomosc)) return true;
	else return false;
}

bool Fun_wiadomosci::usun_wiadomosc(string id_prac, string data_wys, bool wysylanie)
{
	if (wysylanie)
	{
		if (Modyfikator_bazy::usun_wiadomosc(id_prac, data_wys, Dane_zalogowanego_pracownika::instancja()->pobierz_id_pracownika())) return true;
		else return false;
	}
	else
	{
		if (Modyfikator_bazy::usun_wiadomosc(Dane_zalogowanego_pracownika::instancja()->pobierz_id_pracownika(), data_wys, id_prac)) return true;
		else return false;
	}
}

tuple<QStringList, vector<int>> Fun_wiadomosci::pobierz_wiadomosci(bool wysylanie)
{
	if (wysylanie)
	{
		vector<Wiadomosc>wiadomosci = Pobieranie_bazy::pobierz_wiadomosc("select * from Wiadomosci where Id_nadawcy = " + Dane_zalogowanego_pracownika::instancja()->pobierz_id_pracownika() + "");	
		vector<int>typWiadomosci;
		QStringList lista;
		if ( Dane_zalogowanego_pracownika::instancja()->pobierz_czy_blad()) return std::make_tuple(lista, typWiadomosci);
	
		for (auto i = wiadomosci.begin(); i != wiadomosci.end(); ++i)
		{
			vector<Pracownik>pracownik = Pobieranie_bazy::pobierz_pracownik("select * from Pracownicy where Id_pracownika = " + i->pobierz_id_odbiorcy() + "");
			lista.append(QString::fromStdString(i->pobierz_temat() + " " + pracownik[0].pobierz_id_pracownika() + ". " + pracownik[0].pobierz_imie() + " " + pracownik[0].pobierz_nazwisko() + " " + i->pobierz_data_wyslania()));
			typWiadomosci.push_back(stoi(i->pobierz_typ()));
		}
		if (lista.empty())
		{
			lista.append(QString::fromStdString("Brak wiadomosci"));
			typWiadomosci.push_back(0);
			return std::make_tuple(lista, typWiadomosci);
		}
		else return std::make_tuple(lista, typWiadomosci);
	}
	else
	{
		vector<Wiadomosc>wiadomosci = Pobieranie_bazy::pobierz_wiadomosc("select * from Wiadomosci where Id_odbiorcy = " + Dane_zalogowanego_pracownika::instancja()->pobierz_id_pracownika() + "");
		QStringList lista;
		vector<int>typWiadomosci;
		if (Dane_zalogowanego_pracownika::instancja()->pobierz_czy_blad()) return std::make_tuple(lista, typWiadomosci);;
		for (auto i = wiadomosci.begin(); i != wiadomosci.end(); ++i)
		{
			vector<Pracownik>pracownik = Pobieranie_bazy::pobierz_pracownik("select * from Pracownicy where Id_pracownika = " + i->pobierz_id_nadawcy() + "");
			lista.append(QString::fromStdString(i->pobierz_temat() + " " + pracownik[0].pobierz_id_pracownika() + ". " + pracownik[0].pobierz_imie() + " " + pracownik[0].pobierz_nazwisko() + " " + i->pobierz_data_wyslania()));
			typWiadomosci.push_back(stoi(i->pobierz_typ()));
		}
		if (lista.empty())
		{
			lista.append(QString::fromStdString("Brak wiadomosci"));
			typWiadomosci.push_back(0);
			return std::make_tuple(lista, typWiadomosci);;
		}
		else return std::make_tuple(lista, typWiadomosci);;
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
	slowa.push_back(slowo);
	return slowa;
}

string seperacja_stringa_od_kropki(string str)
{
	string slowo = "";
	for (auto x : str)
	{
		if (x == '.')
		{
			return slowo;
		}
		else {
			slowo = slowo + x;
		}
	}
	return slowo;
}
QString Fun_wiadomosci::pobierz_tresc(string id_pracownika, string data_wyslania, bool czy_wyslana_wiadomosc)
{
	vector<Wiadomosc> wiadomosc;
	if (czy_wyslana_wiadomosc)
	{
		wiadomosc = Pobieranie_bazy::pobierz_wiadomosc("select * from Wiadomosci where Data_wyslania = '" + data_wyslania +
			"' and Id_nadawcy = " + Dane_zalogowanego_pracownika::instancja()->pobierz_id_pracownika() + " and Id_odbiorcy = " +
			id_pracownika + "");
	}

	else
	{
		wiadomosc = Pobieranie_bazy::pobierz_wiadomosc("select * from Wiadomosci where Data_wyslania = '" + data_wyslania +
			"' and Id_odbiorcy = " + Dane_zalogowanego_pracownika::instancja()->pobierz_id_pracownika() + " and Id_nadawcy = " +
			id_pracownika + "");
	}
	QString tresc;
	if (Dane_zalogowanego_pracownika::instancja()->pobierz_czy_blad()) return tresc;
	else return QString::fromStdString(wiadomosc[0].pobierz_tresc());
}
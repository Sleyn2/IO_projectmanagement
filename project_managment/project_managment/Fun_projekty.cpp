#include <vector>
#include "klasy.h"

QStringList Fun_projekty::pobierz_liste_projektow()
{
	vector<Projekt>projekty;
	QStringList lista;
	string id = Dane_zalogowanego_pracownika::instancja()->pobierz_id_pracownika();
	projekty = Pobieranie_bazy::pobierz_projekt("select * from projekt where Zadanie = false and Id_projektu in ( select Id_projektu from Przypisanie_do_projektow where Id_pracownika= "+ id +")");

	for (auto i = projekty.begin(); i != projekty.end(); ++i)
	{
		lista.append(QString::fromStdString(i->pobierz_nazwa()));
	}
	return lista;
}

QStringList Fun_projekty::pobierz_liste_zadan()
{
	vector<Projekt>projekty;
	QStringList lista;
	vector<Projekt> projekt;

	projekt = Pobieranie_bazy::pobierz_projekt("select * from Projekt where nazwa= '" +
	Dane_zalogowanego_pracownika::instancja()->pobierz_nazwe_projektu() + "';");

	projekty = Pobieranie_bazy::pobierz_projekt("select * from Projekt where Id_projektu_nadrzednego = " 
		+ projekt[0].pobierz_id_projektu() + ";");

	for (auto i = projekty.begin(); i != projekty.end(); ++i)
	{
		lista.append(QString::fromStdString(i->pobierz_nazwa()));
	}
	return lista;
}

QString Fun_projekty::pobierz_opis_projektu(std::string nazwa)
{
	if (!nazwa.empty())
	{
		vector<Projekt>projekt;
		projekt = Pobieranie_bazy::pobierz_projekt("select * from Projekt where Nazwa = '" + nazwa + "';");
		if (!projekt.empty()) return QString::fromStdString(projekt[0].pobierz_opis());
		else return QString::fromStdString("Nie wybrano projektu");
	}
	else return QString::fromStdString("Nie wybrano projektu");
}

bool Fun_projekty::czy_kierownik()
{
	vector<Przypisanie_do_projektow> przypisania;
	vector<Projekt> projekt;
	projekt = Pobieranie_bazy::pobierz_projekt("select * from Projekt where nazwa= '" + 
		Dane_zalogowanego_pracownika::instancja()->pobierz_nazwe_projektu() + "';");

	przypisania = Pobieranie_bazy::pobierz_Przypisanie_do_projektow("select * from Przypisanie_do_projektow where Id_pracownika = " 
		+ Dane_zalogowanego_pracownika::instancja()->pobierz_id_pracownika() + " and Id_projektu = " + projekt[0].pobierz_id_projektu() + ";" );
	if (przypisania[0].pobierz_kierownik() == "t") return true;
	else return false;
}

bool Fun_projekty::utworz_projekt(string nazwa, string opis, string data_rozpoczecia, string data_zakonczenia, string status)
{
	vector<Projekt> czy_sa_projekty;
	czy_sa_projekty = Pobieranie_bazy::pobierz_projekt("select * from Projekt where Nazwa = '" + nazwa + "';");
	if (!czy_sa_projekty.empty()) return false;
	else
	{
		Projekt* projekt = new Projekt("1", nazwa, opis, data_rozpoczecia, data_zakonczenia, "false", "null", status);
		if (Modyfikator_bazy::dodaj_projekt(projekt))
		{
			delete projekt;
			return true;
		}
		else
		{
			delete projekt;
			return false;;
		}
	}
}

bool Fun_projekty::utworz_zadanie(string nazwa, string opis, string data_rozpoczecia, string data_zakonczenia, string status)
{
	vector<Projekt> czy_sa_projekty;
	czy_sa_projekty = Pobieranie_bazy::pobierz_projekt("select * from Projekt where Nazwa = '" + nazwa + "';");
	if (!czy_sa_projekty.empty()) return false;
	else
	{
		vector<Projekt> projekt;
		projekt = Pobieranie_bazy::pobierz_projekt("select * from Projekt where nazwa= '" +
			Dane_zalogowanego_pracownika::instancja()->pobierz_nazwe_projektu() + "';");

		Projekt* zadanie = new Projekt("1", nazwa, opis, data_rozpoczecia, data_zakonczenia, "true", projekt[0].pobierz_id_projektu(), status);
		if (Modyfikator_bazy::dodaj_projekt(zadanie)) return true;
		return false;
		delete zadanie;
	}
}

bool Fun_projekty::dodaj_przypisanie_do_projektu(string id_pracownika, string kierownik)
{
	vector<Projekt> id_projektu = Pobieranie_bazy::pobierz_projekt("select * from Projekt where nazwa= '" +
		Dane_zalogowanego_pracownika::instancja()->pobierz_nazwe_projektu() + "';");

	Przypisanie_do_projektow* przypisanie = new Przypisanie_do_projektow(id_pracownika, id_projektu[0].pobierz_id_projektu(), kierownik);
	if (Modyfikator_bazy::dodaj_przyp_do_proj(przypisanie))
	{
		delete przypisanie;
		return true;
	}
	else
	{
		delete przypisanie;
		return true;
	}
}

bool Fun_projekty::usun_zadanie(string nazwa_zadania)
{
	if (Modyfikator_bazy::usun_zadanie(nazwa_zadania)) return true;
	return false;
}

Projekt Fun_projekty::pobierz_dane_zadania()
{
	vector<Projekt> projekt = Pobieranie_bazy::pobierz_projekt("select * from Projekt where nazwa = '" + Dane_zalogowanego_pracownika::instancja()->pobierz_nazwe_zadania() +"';");

	return projekt[0];
}

bool Fun_projekty::zaktualizuj_zadanie(string nazwa, string opis, string data_r, string data_z, string status)
{
	Projekt* zadanie = new Projekt("1", nazwa, opis, data_r, data_z, "true", "null", status);
	if (Modyfikator_bazy::zaktualizuj_zadanie(zadanie))
	{
		delete zadanie;
		return true;
	}
	else
	{
		delete zadanie;
		return false;
	}
}


QStringList Fun_projekty::pobierz_liste_pracownikow() 
{
	vector<Pracownik>pracownicy = Pobieranie_bazy::pobierz_pracownik("select * from Pracownicy");
	QStringList lista;

	for (auto i = pracownicy.begin(); i != pracownicy.end(); ++i)
	{
		lista.append(QString::fromStdString(i->pobierz_id_pracownika()+ ". " + i->pobierz_imie()+ " " + i->pobierz_nazwisko()));
	}
	if (lista.empty()) lista.append(QString::fromStdString("Brak pracownikow"));
	else return lista;
}

QStringList Fun_projekty::pobierz_liste_pracownikow_w_projekcie(string id_projektu) 
{
	vector<Przypisanie_do_projektow>przypisania = Pobieranie_bazy::pobierz_Przypisanie_do_projektow("select * from Przypisanie_do_projektow where Id_projektu = " + id_projektu + "");
	QStringList lista;

	for (auto i = przypisania.begin(); i != przypisania.end(); ++i)
	{
	vector<Pracownik>pracownik = Pobieranie_bazy::pobierz_pracownik("select * from Pracownicy where Id_pracownika = " + i->pobierz_id_pracownika() + "");
	QStringList lista;

	lista.append(QString::fromStdString(pracownik[0].pobierz_id_pracownika() + ". " + pracownik[0].pobierz_imie() + " " + pracownik[0].pobierz_nazwisko()));
	}
	if (lista.empty()) lista.append(QString::fromStdString("Brak pracownikow"));
	else return lista;
}
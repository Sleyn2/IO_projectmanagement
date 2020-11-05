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
		+ projekt[0].pobierz_id_projektu() + " and Zadanie = true;");

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

	przypisania = Pobieranie_bazy::pobierz_Przypisanie_do_projetkow("select * from Przypisanie_do_projektow where Id_pracownika = " 
		+ Dane_zalogowanego_pracownika::instancja()->pobierz_id_pracownika() + " and Id_projektu = " + projekt[0].pobierz_id_projektu() + ";" );
	string s = przypisania[0].pobierz_kierownik();
	if (przypisania[0].pobierz_kierownik() == "1") return true;
	else return false;
}
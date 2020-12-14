#include <vector>
#include "klasy.h"

QStringList Fun_projekty::pobierz_liste_projektow(QString status)
{
	vector<Projekt>projekty;
	QStringList lista;
	string id = Dane_zalogowanego_pracownika::instancja()->pobierz_id_pracownika();

	string Query = "select proj.id_projektu, proj.nazwa, proj.opis, proj.status, proj.data_rozpoczecia, proj.data_zakonczenia, proj.id_projektu_nadrzednego, proj.zadanie from projekt proj \
					join przypisanie_do_projektow przyps on przyps.id_projektu = proj.id_projektu\
					where przyps.id_pracownika = "+ id + "and proj.status = '" + status.toStdString() + "';";

	projekty = Pobieranie_bazy::pobierz_projekt(Query);
	
	
	if (Dane_zalogowanego_pracownika::instancja()->pobierz_czy_blad()) return lista;
	for (Projekt i : projekty)
	{
		lista.append(QString::fromStdString(i.pobierz_id_projektu()) + " " + QString::fromStdString(i.pobierz_nazwa()));
	}
	return lista;
}

QStringList Fun_projekty::pobierz_liste_zadan()
{
	vector<Projekt>projekty;
	QStringList lista;
	vector<Projekt> projekt;

	projekt = Pobieranie_bazy::pobierz_projekt("select * from Projekt where Id_projektu = " +
	Dane_zalogowanego_pracownika::instancja()->pobierz_id_projektu() + ";");
	if (Dane_zalogowanego_pracownika::instancja()->pobierz_czy_blad()) return lista;

	projekty = Pobieranie_bazy::pobierz_projekt("select * from Projekt where Id_projektu_nadrzednego = " 
		+ projekt[0].pobierz_id_projektu() + ";");

	for (auto i = projekty.begin(); i != projekty.end(); ++i)
	{
		lista.append(QString::fromStdString(i->pobierz_id_projektu()) + " " + QString::fromStdString(i->pobierz_nazwa()));
	}
	return lista;
}

QString Fun_projekty::pobierz_opis_projektu()
{
	if (!Dane_zalogowanego_pracownika::instancja()->pobierz_id_projektu().empty())
	{
		vector<Projekt>projekt;
		projekt = Pobieranie_bazy::pobierz_projekt("select * from Projekt where Id_projektu = " + Dane_zalogowanego_pracownika::instancja()->pobierz_id_projektu() + ";");
		if (!projekt.empty()) return QString::fromStdString(projekt[0].pobierz_opis());
		else return QString::fromStdString("Nie wybrano projektu");
	}
	else return QString::fromStdString("Nie wybrano projektu");
}

QString Fun_projekty::pobierz_opis_projektu_nadrzednego()
{
	if (!Dane_zalogowanego_pracownika::instancja()->pobierz_id_projektu().empty())
	{
		vector<Projekt>projekt;
		string id = Dane_zalogowanego_pracownika::instancja()->pobierz_id_projektu();
		string Query = "select p.id_projektu, p.nazwa, p.opis, p.status, p.data_rozpoczecia, p.data_zakonczenia, p.id_projektu_nadrzednego, p.zadanie from projekt p join projekt p2 on p.id_projektu = p2.id_projektu_nadrzednego \
						where p2.id_projektu = "+id+"; ";
		projekt = Pobieranie_bazy::pobierz_projekt(Query);
		if (!projekt.empty()) return QString::fromStdString(projekt.begin()->pobierz_opis());
		else return QString::fromStdString("Nie wybrano projektu");
	}
	else return QString::fromStdString("Nie wybrano projektu");
}

bool Fun_projekty::czy_kierownik()
{
	vector<Przypisanie_do_projektow> przypisania;
	vector<Projekt> projekt;

	przypisania = Pobieranie_bazy::pobierz_Przypisanie_do_projektow("select * from Przypisanie_do_projektow where Id_pracownika = " 
		+ Dane_zalogowanego_pracownika::instancja()->pobierz_id_pracownika() + " and Id_projektu = " + Dane_zalogowanego_pracownika::instancja()->pobierz_id_projektu() + ";" );
	if (przypisania.size() == 1 &&  przypisania.begin()->pobierz_kierownik() == "t") return true;
	else return false;
}
bool Fun_projekty::czy_Zadanie(string id) {


	string Query = "select * from projekt where id_projektu = "+id+";";

	vector<Projekt> projekt = Pobieranie_bazy::pobierz_projekt(Query);
	/* baza danych mo¿e zwracaæ bool jako "t" "f" <- do sprawdzenia */
	if (!projekt.empty() && projekt.begin()->pobierz_zadanie() == "t")
		return true;
	return false;
}



bool Fun_projekty::utworz_projekt(string nazwa, string opis, string data_rozpoczecia, string data_zakonczenia, string status)
{
	vector<Projekt> czy_sa_projekty;
	czy_sa_projekty = Pobieranie_bazy::pobierz_projekt("select * from Projekt where Nazwa = '" + nazwa + "';");
	if (!czy_sa_projekty.empty()) return false;
	else
	{
		Projekt projekt("1", nazwa, opis, data_rozpoczecia, data_zakonczenia, "false", "null", status);
		if (Modyfikator_bazy::dodaj_projekt(&projekt))
		{
			/* na pewno ten co robi projekt bedzie jego kierownikiem */
			Przypisanie_do_projektow przypisanie(Dane_zalogowanego_pracownika::instancja()->pobierz_id_pracownika(),
				Pobieranie_bazy::pobierz_projekt("SELECT * from projekt where nazwa = '" + projekt.pobierz_nazwa() + "';").begin()->pobierz_id_projektu(),
				"true");
			Modyfikator_bazy::dodaj_przyp_do_proj(&przypisanie);
			return true;
		}
		else
		{
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

	Przypisanie_do_projektow* przypisanie = new Przypisanie_do_projektow(id_pracownika, Dane_zalogowanego_pracownika::instancja()->pobierz_id_projektu(), kierownik);
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


bool  Fun_projekty::dodaj_przypisanie_do_zadania(string id_pracownika, string kierownik)
{
/*
*	Mo¿e byæ tylko jedno przypisanie pracownika do zadania
*
*	pobieranie bie¿¹cego przypisania i usuniecie go 
*	dodanie nowego przypisania 
*/

	vector<Przypisanie_do_projektow> przypisanie = Pobieranie_bazy::pobierz_Przypisanie_do_projektow(
		"select * from przypisanie_do_projektow where id_projektu = '" +
		Dane_zalogowanego_pracownika::instancja()->pobierz_id_zadania() +
		"';");
	if (!przypisanie.empty()) {
		Modyfikator_bazy::usun_przyp_do_projektu(&przypisanie[0]);
	}
	Przypisanie_do_projektow  przyp(id_pracownika, Dane_zalogowanego_pracownika::instancja()->pobierz_id_zadania(), kierownik);
	if (Modyfikator_bazy::dodaj_przyp_do_proj(&przyp))
		return true;
	else
		return true;
}

bool Fun_projekty::usun_przypisanie_do_projektu()
{
	Przypisanie_do_projektow przypisanie("0", Dane_zalogowanego_pracownika::instancja()->pobierz_id_projektu(), "false");
	if (Modyfikator_bazy::usun_przyp_do_projektu(&przypisanie)) return true;
	else return false;
}

bool Fun_projekty::usun_przypisanie_do_zadania()
{
	//usuwanie przypisania dla wybranego zadania
	Przypisanie_do_projektow przypisanie("0", Dane_zalogowanego_pracownika::instancja()->pobierz_id_zadania(), "false");
	if (Modyfikator_bazy::usun_przyp_do_projektu(&przypisanie)) return true;
	else return false;
}


bool Fun_projekty::usun_zadanie()
{
	if (Modyfikator_bazy::usun_zadanie(Dane_zalogowanego_pracownika::instancja()->pobierz_id_zadania())) return true;
	return false;
}

Projekt Fun_projekty::pobierz_dane_zadania()
{
	vector<Projekt> projekt = Pobieranie_bazy::pobierz_projekt("select * from Projekt where Id_projektu = " + Dane_zalogowanego_pracownika::instancja()->pobierz_id_zadania() +";");

	if (!projekt.empty())
		return projekt[0];
	else
		return Projekt("", "", "", "", "", "", "", "");
}

bool Fun_projekty::zaktualizuj_zadanie(string nazwa, string opis, string data_r, string data_z, string status)
{
	vector<Projekt> czy_jest_zadanie = Pobieranie_bazy::pobierz_projekt("select * from projekt where nazwa = '" + nazwa + "';");
	if (czy_jest_zadanie.size() == 1)
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
	else
	{
		return false;
	}

	
}
bool Fun_projekty::czy_mozna_przeksztalcic_w_projekt()
{
	string idProj = Dane_zalogowanego_pracownika::instancja()->pobierz_id_projektu();
	string idPrac = Dane_zalogowanego_pracownika::instancja()->pobierz_id_pracownika();
	vector<Przypisanie_do_projektow> przyps = Pobieranie_bazy::pobierz_Przypisanie_do_projektow("select * from przypisanie_do_projektow\
														where id_pracownika = " + idPrac + " and id_projektu = " + idProj + "; ");
	if (przyps.size() == 1 && przyps.begin()->pobierz_kierownik() == "t")
	{
		return true;
	}
	return false;
}
bool Fun_projekty::przeksztalc_w_podprojek()
{
	string idProj = Dane_zalogowanego_pracownika::instancja()->pobierz_id_projektu();
	if (czy_mozna_przeksztalcic_w_projekt())
	{
		vector<Projekt> zadanie = Pobieranie_bazy::pobierz_projekt("select * from projekt where id_projektu = " + idProj + ";");
		if (zadanie.size() == 1)
		{
			zadanie.begin()->ustaw_zadanie("false");
			return 	Modyfikator_bazy::zaktualizuj_projekt(&zadanie[0]);
		}
	}
	return false;
}

QString Fun_projekty::pobierz_id_kierownika()
{
	string id = Dane_zalogowanego_pracownika::instancja()->pobierz_id_projektu();
	string Query = "select * from pracownicy p \
					join przypisanie_do_projektow przyps on przyps.id_pracownika = p.id_pracownika \
					join projekt proj on przyps.id_projektu = proj.id_projektu \
					where proj.id_projektu = "+id+" and kierownik = 'true'";
	vector<Pracownik> kierownik = Pobieranie_bazy::pobierz_pracownik(Query);
	if (kierownik.size() == 1) {
		return QString::fromStdString(kierownik.begin()->pobierz_id_pracownika());
	}
	return QString("");
}
QString Fun_projekty::pobierz_id_kierownika_nadrzednego()
{
	string id = Dane_zalogowanego_pracownika::instancja()->pobierz_id_projektu();
	string Query = "select prac.id_pracownika, prac.imie, prac.nazwisko, prac.login, prac.haslo, prac.administrator from projekt p1 join projekt p2 on p1.id_projektu = p2.id_projektu_nadrzednego and p2.id_projektu = "+id+
					"join przypisanie_do_projektow przyps on przyps.id_projektu = p1.id_projektu and przyps.kierownik = 'true' \
					join pracownicy prac on prac.id_pracownika = przyps.id_pracownika";
	vector<Pracownik> kierownik = Pobieranie_bazy::pobierz_pracownik(Query);
	if (kierownik.size() == 1) {
		return QString::fromStdString(kierownik.begin()->pobierz_id_pracownika());
	}
	return QString("");
}

QString Fun_projekty::pobierz_aktualnego_pracownika()
{
	vector<Przypisanie_do_projektow> przyps = Pobieranie_bazy::pobierz_Przypisanie_do_projektow("select * from przypisanie_do_projektow where id_projektu = " +
		Dane_zalogowanego_pracownika::instancja()->pobierz_id_zadania() +
		";");
	vector<Pracownik> prac;
	string element;
	if (przyps.empty()) {
		return QString("");
	}
	else {
		prac = Pobieranie_bazy::pobierz_pracownik("select * from pracownicy where id_pracownika = " +
			przyps[0].pobierz_id_pracownika() +
			";");
		element = prac.begin()->pobierz_imie() + " " + prac.begin()->pobierz_nazwisko() + " (" + prac.begin()->pobierz_login() + ")";
		return QString::fromStdString(element);
	}
}

bool Fun_projekty::pobierz_zadanie_w_podprojekt()
{
	vector<Przypisanie_do_projektow> przyps = Pobieranie_bazy::pobierz_Przypisanie_do_projektow("select * from przypisanie_do_projektow where id_projektu = " +
		Dane_zalogowanego_pracownika::instancja()->pobierz_id_zadania() +
		";");
	if (przyps.size() == 1)
		return (przyps.begin()->pobierz_kierownik() == "t") ? true : false;
	else
		return false;
}


bool Fun_projekty::zakoncz_projekt()
{
	// projekt zmienia status na zakonczony
	string id = Dane_zalogowanego_pracownika::instancja()->pobierz_id_projektu();
	string Query = "select * from projekt where id_projektu ="+ id +"; ";
	vector<Projekt> zadanie = Pobieranie_bazy::pobierz_projekt(Query);
	if (zadanie.size() == 1)
	{
		zadanie.begin()->ustaw_staus("Zamkniety");
		return Modyfikator_bazy::zaktualizuj_projekt(&zadanie[0]);
	}
	return false;
}

bool Fun_projekty::dodaj_przypisanie_do_zadania_login(string login, string trufalse)
{
	vector<Pracownik> pracownik = Pobieranie_bazy::pobierz_pracownik("select * from pracownicy where login = '" + login + "';");

	return Fun_projekty::dodaj_przypisanie_do_zadania(pracownik.begin()->pobierz_id_pracownika(), trufalse);
}


QStringList Fun_projekty::pobierz_liste_pracownikow() 
{
	vector<Pracownik>pracownicy = Pobieranie_bazy::pobierz_pracownik("select * from Pracownicy");
	QStringList lista;
	if (Dane_zalogowanego_pracownika::instancja()->pobierz_czy_blad()) return lista;

	for (auto i = pracownicy.begin(); i != pracownicy.end(); ++i)
	{
		lista.append(QString::fromStdString(i->pobierz_id_pracownika()+ ". " + i->pobierz_imie()+ " " + i->pobierz_nazwisko()));
	}
	if (lista.empty())
	{
		lista.append(QString::fromStdString("Brak pracownikow"));
		return lista;
	}
	else return lista;
}


/**
* 
* Metoda pobiera liste pracownikow bior¹cych udzia³ w tworzeniu projektu
* pracownicy wykonyj¹ zadanie albo projekt nalezy do nich
* 
*/
QStringList Fun_projekty::pobierz_liste_pracownikow_w_projekcie() 
{

	/* kierownik projektu oraz osoby z projektem nardzednym */

	
	QStringList lista;
	if (Dane_zalogowanego_pracownika::instancja()->pobierz_czy_blad()) return lista;


	string nr_proj = Dane_zalogowanego_pracownika::instancja()->pobierz_id_projektu();
	string Query = "select distinct p.id_pracownika, p.imie, p.nazwisko, p.login, p.haslo, p.administrator   from pracownicy p \
				join przypisanie_do_projektow przyps on  p.id_pracownika = przyps.id_pracownika \
				join projekt proj on(przyps.id_projektu = proj.id_projektu_nadrzednego) or (przyps.id_projektu = proj.id_projektu) \
				where proj.id_projektu = " + nr_proj + " or proj.id_projektu_nadrzednego =  " + nr_proj;


	vector<Pracownik>pracownik = Pobieranie_bazy::pobierz_pracownik(Query);


	for (Pracownik i : pracownik)
	{
		lista.append(QString::fromStdString(i.pobierz_id_pracownika() + ". " + i.pobierz_imie() + " " + i.pobierz_nazwisko()));
	}
	if (lista.empty())
	{
		lista.append(QString::fromStdString("Brak pracownikow"));
		return lista;
	}
	else return lista;
}
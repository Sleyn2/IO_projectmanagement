#include "klasy.h"

bool Fun_ustawienia::edycja_danych_uzytkownika(string id_pracownika, string imie, string nazwisko, string login, string haslo, string czy_admin)
{
	Pracownik prac(id_pracownika, imie, nazwisko, login, haslo, czy_admin);

	if (Modyfikator_bazy::aktualizuj_pracownika(&prac))
	{
		Dane_zalogowanego_pracownika::instancja()->ustaw_dane_logowanie(imie, nazwisko, login, haslo, czy_admin, id_pracownika);


		return true;
	}
	else
	{
		return false;
	}
}

bool Fun_ustawienia::dodaj_do_dzialu_po_nazwie(string id_pracownika, string nazwa_dzial)
{
	std::vector<Dzial> dzial = Pobieranie_bazy::pobierz_dzial("select * from dzialy_w_firmie as d where d.nazwa = '" +
		nazwa_dzial + "';");
	string id_d;

	if (dzial.size() == 1)
	{
		id_d = dzial[0].pobierz_id_dzialu();

		Przypisanie_do_dzialow przyp(id_pracownika, id_d);

		if (Modyfikator_bazy::dodaj_przyp_do_dzialu(&przyp))
		{
			return true;
		}
		else
		{
			return false;
		}
	}
}

bool Fun_ustawienia::usun_z_dzialu_po_nazwie(string id_pracownika, string nazwa_dzial)
{
	std::vector<Dzial> dzial = Pobieranie_bazy::pobierz_dzial("select * from dzialy_w_firmie as d where d.nazwa = '" +
		nazwa_dzial + "';");
	string id_d;

	if (dzial.size() == 1)
	{
		id_d = dzial[0].pobierz_id_dzialu();

		Przypisanie_do_dzialow przyp(id_pracownika, id_d);

		if (Modyfikator_bazy::usun_przyp_do_dzialu(&przyp))
		{
			return true;
		}
		else
		{
			return false;
		}
	}

}

QStringList Fun_ustawienia::pobierz_liste_pracownikow()
{
	vector<Pracownik>pracownicy = Pobieranie_bazy::pobierz_pracownik("select * from Pracownicy");
	QStringList lista;
	if (Dane_zalogowanego_pracownika::instancja()->pobierz_czy_blad()) return lista;

	for (auto i = pracownicy.begin(); i != pracownicy.end(); ++i)
	{
		lista.append(QString::fromStdString(i->pobierz_imie() + " " + i->pobierz_nazwisko() + " (" + i->pobierz_login() + ")"));
	}
	if (lista.empty())
	{
		lista.append(QString::fromStdString("Brak pracownikow"));
		return lista;
	}
	else return lista;
}

string Fun_ustawienia::czy_admin_po_loginie(string login)
{
	vector<Pracownik> prac = Pobieranie_bazy::pobierz_pracownik("select * from pracownicy where login = '" +
		login + "';");

	if (prac.size() == 1)
	{
		return prac[0].pobierz_czy_administator();
	}
	else
	{
		return "blad";
	}
}

string Fun_ustawienia::imie_nazwisko_po_loginie(string login)
{
	vector<Pracownik> prac = Pobieranie_bazy::pobierz_pracownik("select * from pracownicy where login = '" +
		login + "';");

	string imie;
	string nazwisko;

	if (prac.size() == 1)
	{
		imie = prac[0].pobierz_imie();
		nazwisko = prac[0].pobierz_nazwisko();

		return imie + " " + nazwisko;
	}
	else
	{
		return "blad";
	}
}

string Fun_ustawienia::wyluskaj_login(string text)
{
	string login = "";

	for (int i = 0; i < text.size(); i++)
	{
		if (text[i] == '(')
		{
			for (int j = i + 1; j < text.size() - 1; j++)
			{
				login = login + text[j];
			}
			break;
		}
	}

	return login;
}

static bool nadawanie_uprawnien(string login, string czy_adm)
{
	return true;
}
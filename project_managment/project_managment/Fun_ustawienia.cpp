#include "klasy.h"

bool Fun_ustawienia::edycja_danych_uzytkownika(string id_pracownika, string imie, string nazwisko, string login, string haslo, string czy_admin)
{
	Pracownik prac(id_pracownika, imie, nazwisko, login, haslo, czy_admin);

	if (Modyfikator_bazy::aktualizuj_pracownika(&prac))
	{
		if (id_pracownika == Dane_zalogowanego_pracownika::instancja()->pobierz_id_pracownika())
		{
			Dane_zalogowanego_pracownika::instancja()->ustaw_dane_logowanie(imie, nazwisko, login, haslo, czy_admin, id_pracownika);
		}

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

vector<string> Fun_ustawienia::imie_nazwisko_po_loginie(string login, string zrodlo)
{
	vector<Pracownik> prac;
	vector<string>imie_i_nazw;

	if (zrodlo == "pracownicy")
	{
		prac = Pobieranie_bazy::pobierz_pracownik("select * from pracownicy where login = '" +
			login + "';");
	}
	else if (zrodlo == "prosby")
	{
		prac = Pobieranie_bazy::pobierz_pracownik("select * from prosby_o_dodanie where login = '" +
			login + "';");
	}
	else
	{
		return imie_i_nazw;
	}

	string imie;
	string nazwisko;

	if (!prac.empty())
	{
		imie = prac[0].pobierz_imie();
		nazwisko = prac[0].pobierz_nazwisko();
	}

	
	imie_i_nazw.push_back(imie);
	imie_i_nazw.push_back(nazwisko);

	return imie_i_nazw;

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

bool Fun_ustawienia::nadawanie_uprawnien(string login, string czy_adm)
{
	std::vector<Pracownik> prac = Pobieranie_bazy::pobierz_pracownik("select * from pracownicy where login = '" +
		login + "';");

	if (prac.size() == 1)
	{
		Fun_ustawienia::edycja_danych_uzytkownika(prac[0].pobierz_id_pracownika(), prac[0].pobierz_imie(), prac[0].pobierz_nazwisko(),
			prac[0].pobierz_login(), prac[0].pobierz_haslo(), czy_adm);

		/*Dane_zalogowanego_pracownika::instancja()->ustaw_dane_logowanie(prac[0].pobierz_id_pracownika(), prac[0].pobierz_imie(), prac[0].pobierz_nazwisko(),
			prac[0].pobierz_login(), prac[0].pobierz_haslo(), czy_adm);*/

		return true;
	}
	else
	{
		return false;
	}

}

void Fun_ustawienia::odswiez_zalogowanego()
{
	std::vector<Pracownik> prac = Pobieranie_bazy::pobierz_pracownik("select * from pracownicy where id_pracownika = '" +
		Dane_zalogowanego_pracownika::instancja()->pobierz_id_pracownika() + "';");

	if (prac.size() == 1)
	{
		Dane_zalogowanego_pracownika::instancja()->ustaw_dane_logowanie(prac[0].pobierz_imie(), prac[0].pobierz_nazwisko(),
			prac[0].pobierz_login(), prac[0].pobierz_haslo(), prac[0].pobierz_czy_administator(), prac[0].pobierz_id_pracownika());
	}
}

bool Fun_ustawienia::dodaj_dzial(std::string adres, std::string nazwa)
{

	Dzial d("0", nazwa, adres);

	if (!nazwa.empty() && !adres.empty() && Modyfikator_bazy::dodaj_dzial(&d))
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Fun_ustawienia::usun_dzial(string nazwa)
{
	if (Modyfikator_bazy::wykonaj_zapytanie("delete from dzialy_w_firmie where nazwa = '" + nazwa + "';"))
	{
		return true;
	}
	else
	{
		return false;
	}
}

vector<QString> Fun_ustawienia::pobierz_liste_dzialow()
{
	vector<Dzial> dzialy = Pobieranie_bazy::pobierz_dzial("select * from dzialy_w_firmie;");
	vector<QString> dzialy_nazwy;

	if (!dzialy.empty())
	{
		for (int i = 0; i < dzialy.size(); i++)
		{
			dzialy_nazwy.push_back(QString::fromStdString(dzialy[i].pobierz_nazwa()));
		}
	}

	return dzialy_nazwy;
}

std::vector<QString> Fun_ustawienia::pobierz_liste_prosb()
{
	vector<Prosba> prosby = Pobieranie_bazy::pobierz_prosby("select * from prosby_o_dodanie;");

	vector<QString> imieNazwLogin;

	for (int i = 0; i < prosby.size(); i++)
	{
		imieNazwLogin.push_back(QString::fromStdString(prosby[i].pobierz_imie() + " " + prosby[i].pobierz_nazwisko() + " (" + prosby[i].pobierz_login() + ")"));
	}

	return imieNazwLogin;
}

bool Fun_ustawienia::zatwierdz_pracownika(string login, string adm)
{
	vector<Pracownik> pracownicy = Pobieranie_bazy::pobierz_pracownik("select * from prosby_o_dodanie where login = '" + login + "';");
	if (adm != "0" && adm != "1" && adm != "2")
	{
		adm = "0";
	}

	if (pracownicy.size() == 1)
	{
		pracownicy[0].ustaw_admin(adm);

		if (Modyfikator_bazy::dodaj_pracownika(&pracownicy[0]))
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		return false;
	}

}

bool Fun_ustawienia::usun_prosbe(string login)
{
	if (Modyfikator_bazy::wykonaj_zapytanie("delete from prosby_o_dodanie where login = '" + login + "';"))
	{
		return true;
	}
	else
	{
		return false;
	}
}
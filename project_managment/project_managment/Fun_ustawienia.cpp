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
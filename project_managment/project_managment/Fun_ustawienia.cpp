#include "klasy.h"

bool Fun_ustawienia::edycja_danych_uzytkownika(string id_pracownika, string imie, string nazwisko, string login, string haslo, string czy_admin)
{
	Pracownik prac(id_pracownika, imie, nazwisko, login, haslo, czy_admin);

	if (Modyfikator_bazy::aktualizuj_pracownika(&prac))
	{
		return true;
	}
	else
	{
		return false;
	}
}
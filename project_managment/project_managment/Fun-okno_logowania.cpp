#include <iostream>
#include <pqxx/pqxx>
#include <vector>
#include "klasy.h"

using namespace std;
using namespace pqxx;

bool Fun_okno_logowania::logowanie(string login, string haslo)
{
    Pobieranie_bazy p;
    vector <Pracownik> pracownik;
    pracownik = p.pobierz_pracownik("select *from Pracownicy where login = '" + login + "'");
    if (!pracownik.empty())
    {
        if (to_string(pracownik[0].pobierz_login()) == login && to_string(pracownik[0].pobierz_haslo()) == haslo)
            return true;
        else
            return false;
    }
    else
        return false;
}

bool Fun_okno_logowania::rejestracja(string imie, string nazwisko, string login, string haslo)
{
    Modyfikator_bazy m;
    Prosba* prosba = new Prosba(imie, nazwisko, login, haslo);
    m.aktualizuj_prosbe(prosba);
    return true;
}
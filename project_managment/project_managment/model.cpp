#include <iostream>
#include <pqxx/pqxx>
#include <vector>
#include "klasy.h"

using namespace std;
using namespace pqxx;

vector<Pracownik> Pobieranie_bazy::pobierz_pracownik(string zapytanie)
{
    vector<Pracownik> pracownicy;
    connection C("dbname = test user = postgres password = postgres \
      hostaddr = 127.0.0.1 port = 5432");
    if (C.is_open()) {
        work W{ C };
        result R{ W.exec(zapytanie) };

        for (auto wiersz : R)
        {
            Pracownik pracownik(to_string(wiersz[0]), to_string(wiersz[1]), to_string(wiersz[2]), to_string(wiersz[3]), to_string(wiersz[4]), to_string(wiersz[5]));
            pracownicy.push_back(pracownik);
        }
        return pracownicy;
    }
}

bool Modyfikator_bazy::aktualizuj(Prosba prosba)
{
    connection C("dbname = test user = postgres password = postgres \
      hostaddr = 127.0.0.1 port = 5432");
    if (C.is_open()) {
        work W{ C };
        W.exec0("insert into Prosby_o_dodanie (Imie, Nazwisko, Login, Haslo) values ('" + to_string(prosba.pobierz_imie()) + "', '"
            + to_string(prosba.pobierz_nazwisko()) + "', '" + to_string(prosba.pobierz_login()) + "', '" + to_string(prosba.pobierz_haslo()) + "');");
        W.commit();
        return true;
    }
    else return false;
}
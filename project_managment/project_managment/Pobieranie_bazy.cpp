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

vector<Projekt> Pobieranie_bazy::pobierz_projekt(string zapytanie)
{
    vector<Projekt> projekty;
    connection C("dbname = test user = postgres password = postgres \
      hostaddr = 127.0.0.1 port = 5432");
    if (C.is_open()) {
        work W{ C };
        result R{ W.exec(zapytanie) };

        for (auto wiersz : R)
        {
            Projekt projekt(to_string(wiersz[0]), to_string(wiersz[1]), to_string(wiersz[2]), to_string(wiersz[3]), to_string(wiersz[4]), to_string(wiersz[5]),
                to_string(wiersz[6]), to_string(wiersz[7]));
            projekty.push_back(projekt);
        }
        return projekty;
    }
}

vector<Przypisanie_do_projektow> Pobieranie_bazy::pobierz_Przypisanie_do_projetkow(string zapytanie)
{
    vector<Przypisanie_do_projektow> przypisanie_do_dzialow;
    connection C("dbname = test user = postgres password = postgres \
      hostaddr = 127.0.0.1 port = 5432");
    if (C.is_open()) {
        work W{ C };
        result R{ W.exec(zapytanie) };

        for (auto wiersz : R)
        {
            Przypisanie_do_projektow przypisanie(to_string(wiersz[0]), to_string(wiersz[1]), to_string(wiersz[1]));
            przypisanie_do_dzialow.push_back(przypisanie);
        }
        return przypisanie_do_dzialow;
    }
}


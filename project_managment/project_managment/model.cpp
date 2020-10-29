#include <iostream>
#include <pqxx/pqxx>
#include <vector>
#include "klasy.h"

using namespace std;
using namespace pqxx;

vector<Pracownik> pobieranie_bazy::pobierz_pracownik(string zapytanie)
{
    vector<Pracownik> pracownicy;
    connection C("dbname = test user = postgres password = postgres \
      hostaddr = 127.0.0.1 port = 5432");
    work W{ C };
    result R{ W.exec(zapytanie) };

    for (auto wiersz : R)
    {
        Pracownik pracownik(wiersz[0], wiersz[1], wiersz[2], wiersz[3], wiersz[4], wiersz[5]);
        pracownicy.push_back(pracownik);
    }
    return pracownicy;
}
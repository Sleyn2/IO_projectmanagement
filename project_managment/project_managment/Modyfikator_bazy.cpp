#include <iostream>
#include <pqxx/pqxx>
#include <vector>
#include "klasy.h"

using namespace std;
using namespace pqxx;


bool Modyfikator_bazy::aktualizuj_prosbe(Prosba* prosba)
{
    connection C("dbname = test user = postgres password = postgres \
      hostaddr = 127.0.0.1 port = 5432");
    if (C.is_open()) {
        work W{ C };
        W.exec0("insert into Prosby_o_dodanie (Imie, Nazwisko, Login, Haslo) values ('" + to_string(prosba->pobierz_imie()) + "', '"
            + to_string(prosba->pobierz_nazwisko()) + "', '" + to_string(prosba->pobierz_login()) + "', '" + to_string(prosba->pobierz_haslo()) + "');");
        W.commit();
        return true;
    }
    else return false;
}
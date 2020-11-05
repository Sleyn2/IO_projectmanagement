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

bool Modyfikator_bazy::aktualizuj_projekt(Projekt *projekt)
{
    connection C("dbname = test user = postgres password = postgres \
      hostaddr = 127.0.0.1 port = 5432");
    if (C.is_open()) {
        work W{ C };
        W.exec0("insert into Projekt (Nazwa, Opis, Data_rozpoczecia, Data_zakonczenia, Status, Zadanie, Id_projektu_nadrzednego) values ('" + to_string(projekt->pobierz_nazwa()) + "', '"
            + to_string(projekt->pobierz_opis()) + "', '" + to_string(projekt->pobierz_data_rozpoczecia()) + "', '" + to_string(projekt->pobierz_data_zakonczenia()) + "', '" +
            projekt->pobierz_status() + "', " + projekt->pobierz_zadanie() + ", " + projekt->pobierz_id_projektu_nadrzednego() + ");");
        W.commit();
        return true;
    }
    else return false;
}

bool Modyfikator_bazy::aktualizuj_przyp_do_proj(Przypisanie_do_projektow *przypisanie)
{
    connection C("dbname = test user = postgres password = postgres \
      hostaddr = 127.0.0.1 port = 5432");
    if (C.is_open()) {
        work W{ C };
        W.exec0("insert into Przypisanie_do_projektow values (" + przypisanie->pobierz_id_pracownika() + ", "
            + przypisanie->pobierz_id_projektu() + ", " + przypisanie->pobierz_kierownik()+ ");");
        W.commit();
        return true;
    }
    else return false;
}
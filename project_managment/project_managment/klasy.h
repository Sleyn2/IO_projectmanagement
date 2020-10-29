#pragma once
#include <iostream>
#include <pqxx/pqxx>
#include <vector>

using namespace std;
using namespace pqxx;

class Pracownik
{
private:
    string imie, nazwisko, login, haslo, czy_administator,  id_pracownika;

public:
    Pracownik(string id_p, string i, string n, string l, string h, string czy_a);
    string pobierz_imie();
    string pobierz_nazwisko();
    string pobierz_login();
    string pobierz_haslo();
    string pobierz_id_pracownika();
    string pobierz_czy_administator();
};

class Prosba
{
private:
    string imie, nazwisko, login, haslo, id_pracownika;

public:
    Prosba(string i, string n, string l, string h);
    string pobierz_imie();
    string pobierz_nazwisko();
    string pobierz_login();
    string pobierz_haslo();
    string pobierz_id_pracownika();
    string pobierz_czy_administator();
};

class Pobieranie_bazy
{
public:
    vector<Pracownik> pobierz_pracownik(string zapytanie);
};

class Modyfikator_bazy
{
public:
    bool aktualizuj(Prosba prosba);
};

class Fun_okno_logowania
{
public:
    bool logowanie(string login, string haslo);
    bool rejestracja(string imie, string nazwisko, string login, string haslo);

};
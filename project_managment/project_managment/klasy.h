#pragma once
#include <iostream>
#include <pqxx/pqxx>
#include <vector>

using namespace std;
using namespace pqxx;

class Pracownik
{
private:
    field imie, nazwisko, login, haslo;
    field czy_administator;
    field id_pracownika;

public:
    Pracownik(field id_p, field i, field n, field l, field h, field czy_a);
    field pobierz_imie();
    field pobierz_nazwisko();
    field pobierz_login();
    field pobierz_haslo();
    field pobierz_id_pracownika();
    field pobierz_czy_administator();
};

class pobieranie_bazy
{
public:
    vector<Pracownik> pobierz_pracownik(string zapytanie);
};

class Fun_okno_logowania
{
public:
    bool logowanie(string login, string haslo);

};
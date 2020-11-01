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
};

class Projekt
{
private:
    string id_projektu, nazwa, opis, data_rozpoczecia, data_zakonczenia, id_projektu_nadrzednego, status, zadanie;
public:
    Projekt(string id_p, string n, string o, string data_r, string data_z, string z, string id_p_n, string s);
    string pobierz_id_projektu();
    string pobierz_nazwa();
    string pobierz_id_projektu_nadrzednego();
    string pobierz_id_opis();
    string pobierz_data_rozpoczecia();
    string pobierz_data_zakonczenia();
    string pobierz_status();
    string pobierz_zadanie();
};

class Pobieranie_bazy
{
public:
    vector<Pracownik> pobierz_pracownik(string zapytanie);
    vector<Projekt> pobierz_projekt(string zapytanie);
};

class Modyfikator_bazy
{
public:
    bool aktualizuj_prosbe(Prosba *prosba);
    bool aktualizuj_projekt(Projekt *Projekt);
};

class Fun_okno_logowania
{
public:
    bool logowanie(string login, string haslo);
    bool rejestracja(string imie, string nazwisko, string login, string haslo);

};
#include <iostream>
#include <pqxx/pqxx>
#include <vector>
#include "klasy.h"

using namespace std;
using namespace pqxx;


void Fun_okno_logowania::zapisz_dane_logowania(Pracownik pracownik)
{
    Dane_zalogowanego_pracownika::instancja()->utworz_instancje(pracownik.pobierz_id_pracownika(), pracownik.pobierz_imie(), pracownik.pobierz_nazwisko(), pracownik.pobierz_login(),
        pracownik.pobierz_haslo(), pracownik.pobierz_czy_administator());
}

bool Fun_okno_logowania::logowanie(string login, string haslo)
{
    vector <Pracownik> pracownik;
    pracownik = Pobieranie_bazy::pobierz_pracownik("select *from Pracownicy where login = '" + login + "'");
    if (!pracownik.empty())
    {
        if (to_string(pracownik[0].pobierz_login()) == login && to_string(pracownik[0].pobierz_haslo()) == haslo)
        {
            zapisz_dane_logowania(pracownik[0]);
            return true;
        }
        else
            return false;
    }
    else
        return false;
}

bool Fun_okno_logowania::rejestracja(string imie, string nazwisko, string login, string haslo)
{
    Prosba* prosba = new Prosba(imie, nazwisko, login, haslo);
    Modyfikator_bazy::aktualizuj_prosbe(prosba);
    return true;
}

Dane_zalogowanego_pracownika* Dane_zalogowanego_pracownika::w_instancja = nullptr;

Dane_zalogowanego_pracownika::Dane_zalogowanego_pracownika(string id_p, string i, string n, string l, string h, string czy_a) :
    id_pracownika(id_p), imie(i), nazwisko(n), login(l), haslo(h), czy_administator(czy_a)
{}


Dane_zalogowanego_pracownika* Dane_zalogowanego_pracownika::instancja()
{
    if (instancja) return w_instancja;
    else return nullptr;
}


string Dane_zalogowanego_pracownika::pobierz_imie() { return this->imie; }
string Dane_zalogowanego_pracownika::pobierz_nazwisko() { return this->nazwisko; }
string Dane_zalogowanego_pracownika::pobierz_login() { return this->login; }
string Dane_zalogowanego_pracownika::pobierz_haslo() { return this->haslo; }
string Dane_zalogowanego_pracownika::pobierz_id_pracownika() { return this->id_pracownika; }
string Dane_zalogowanego_pracownika::pobierz_czy_administator() { return this->czy_administator; }


Dane_zalogowanego_pracownika* Dane_zalogowanego_pracownika::utworz_instancje(string id_p, string i, string n, string l, string h, string czy_a)
{
    if (!w_instancja)
        w_instancja = new Dane_zalogowanego_pracownika(id_p, i, n, l, h, czy_a);
    return w_instancja;
}
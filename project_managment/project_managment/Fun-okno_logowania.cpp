#include <iostream>
#include <pqxx/pqxx>
#include <vector>
#include "klasy.h"

using namespace std;
using namespace pqxx;


void Fun_okno_logowania::zapisz_dane_logowania(Pracownik pracownik)
{
    Dane_zalogowanego_pracownika::instancja()->ustaw_dane_logowanie(pracownik.pobierz_imie(), pracownik.pobierz_nazwisko(), pracownik.pobierz_login(),
        pracownik.pobierz_haslo(), pracownik.pobierz_czy_administator(), pracownik.pobierz_id_pracownika());
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
    if (Modyfikator_bazy::dodaj_prosbe(prosba)) return true;
    return false;
}

Dane_zalogowanego_pracownika* Dane_zalogowanego_pracownika::w_instancja = nullptr;

Dane_zalogowanego_pracownika::Dane_zalogowanego_pracownika() {}


Dane_zalogowanego_pracownika* Dane_zalogowanego_pracownika::instancja()
{
    if (!w_instancja)
        w_instancja = new Dane_zalogowanego_pracownika();
    return w_instancja;
}



string Dane_zalogowanego_pracownika::pobierz_imie() { return this->imie; }
string Dane_zalogowanego_pracownika::pobierz_nazwisko() { return this->nazwisko; }
string Dane_zalogowanego_pracownika::pobierz_login() { return this->login; }
string Dane_zalogowanego_pracownika::pobierz_haslo() { return this->haslo; }
string Dane_zalogowanego_pracownika::pobierz_id_pracownika() { return this->id_pracownika; }
string Dane_zalogowanego_pracownika::pobierz_czy_administator() { return this->czy_administator; }
string Dane_zalogowanego_pracownika::pobierz_nazwe_projektu() { return this->nazwa_projektu; }
string Dane_zalogowanego_pracownika::pobierz_nazwe_zadania() { return this->nazwa_zadania; }
string Dane_zalogowanego_pracownika::pobierz_wyjatek() { return this->wyjatek; }
bool Dane_zalogowanego_pracownika::pobierz_czy_blad() { return this->czy_blad; }

void Dane_zalogowanego_pracownika::ustaw_wyjatek(string wyjatek) { this->wyjatek = wyjatek; }
void Dane_zalogowanego_pracownika::ustaw_nazwe_projektu(string id_proj) { this->nazwa_projektu = id_proj; }
void Dane_zalogowanego_pracownika::ustaw_nazwe_zadania(string id_zad) { this->nazwa_zadania = id_zad; }
void Dane_zalogowanego_pracownika::ustaw_czy_blad(bool blad) { this->czy_blad = blad; }
void Dane_zalogowanego_pracownika::ustaw_dane_logowanie(string im, string na, string lo, string ha, string czy_ad, string id_pr)
{
    this->imie = im;
    this->nazwisko = na;
    this->haslo = ha;
    this->login = lo;
    this->id_pracownika = id_pr;
    this->czy_administator = czy_ad;
}

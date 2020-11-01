#include <iostream>
#include <pqxx/pqxx>
#include <vector>
#include "klasy.h"

using namespace std;
using namespace pqxx;

Pracownik::Pracownik(string id_p, string i, string n, string l, string h, string czy_a) :
    id_pracownika(id_p),  imie(i), nazwisko(n), login(l), haslo(h), czy_administator(czy_a)
{

}

string Pracownik::pobierz_imie() { return this->imie; }
string Pracownik::pobierz_nazwisko() { return this->nazwisko; }
string Pracownik::pobierz_login() { return this->login; }
string Pracownik::pobierz_haslo() { return this->haslo; }
string Pracownik::pobierz_id_pracownika() { return this->id_pracownika; }
string Pracownik::pobierz_czy_administator() { return this->czy_administator;  }


Prosba::Prosba(string i, string n, string l, string h) :
    imie(i), nazwisko(n), login(l), haslo(h)
{

}
string Prosba::pobierz_imie() { return this->imie; }
string Prosba::pobierz_nazwisko() { return this->nazwisko; }
string Prosba::pobierz_login() { return this->login; }
string Prosba::pobierz_haslo() { return this->haslo; }
string Prosba::pobierz_id_pracownika() { return this->id_pracownika; }

Projekt::Projekt(string id_p, string n, string o, string data_r, string data_z, string z, string id_p_n, string s) :
    id_projektu(id_p), nazwa(n), opis(o), data_rozpoczecia(data_r), data_zakonczenia(data_z), status(s), zadanie(z), id_projektu_nadrzednego(id_p_n)
{
}
string Projekt::pobierz_id_projektu() { return this->id_projektu; }
string Projekt::pobierz_nazwa() { return this->nazwa; }
string Projekt::pobierz_id_projektu_nadrzednego() { return this->id_projektu_nadrzednego; }
string Projekt::pobierz_id_opis() { return this->opis; }
string Projekt::pobierz_data_rozpoczecia() { return this->data_rozpoczecia; }
string Projekt::pobierz_data_zakonczenia() { return this->data_zakonczenia; }
string Projekt::pobierz_status() { return this->status; }
string Projekt::pobierz_zadanie() { return this->zadanie; }
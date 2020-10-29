#include <iostream>
#include <pqxx/pqxx>
#include <vector>
#include "klasy.h"

using namespace std;
using namespace pqxx;

Pracownik::Pracownik(string id_p, string i, string n, string l, string h, string czy_a) :
    imie(i), nazwisko(n), login(l), haslo(h), czy_administator(czy_a), id_pracownika(id_p)
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
#include <iostream>
#include <pqxx/pqxx>
#include <vector>
#include "klasy.h"

using namespace std;
using namespace pqxx;

Pracownik::Pracownik(field id_p, field i, field n, field l, field h, field czy_a) :
    imie(i), nazwisko(n), login(l), haslo(h), czy_administator(czy_a), id_pracownika(id_p)
{

}

field Pracownik::pobierz_imie() { return this->imie; }
field Pracownik::pobierz_nazwisko() { return this->nazwisko; }
field Pracownik::pobierz_login() { return this->login; }
field Pracownik::pobierz_haslo() { return this->haslo; }
field Pracownik::pobierz_id_pracownika() { return this->id_pracownika; }
field Pracownik::pobierz_czy_administator() { return this->czy_administator;  }
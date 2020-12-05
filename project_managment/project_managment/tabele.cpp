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


Prosba::Prosba(string i, string n, string l, string h, string id_pr) :
    imie(i), nazwisko(n), login(l), haslo(h), id_pracownika(id_pr)
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
string Projekt::pobierz_opis() { return this->opis; }
string Projekt::pobierz_data_rozpoczecia() { return this->data_rozpoczecia; }
string Projekt::pobierz_data_zakonczenia() { return this->data_zakonczenia; }
string Projekt::pobierz_status() { return this->status; }
string Projekt::pobierz_zadanie() { return this->zadanie; }


Przypisanie_do_projektow::Przypisanie_do_projektow(string id_prac, string id_proj, string kier) :
    id_pracownika(id_prac), id_projektu(id_proj), kierownik(kier)
{
}

string Przypisanie_do_projektow::pobierz_id_pracownika() { return this->id_pracownika; }
string Przypisanie_do_projektow::pobierz_id_projektu() { return this->id_projektu; }
string Przypisanie_do_projektow::pobierz_kierownik() { return this->kierownik; }


Wiadomosc::Wiadomosc(string id_od, string data_wy, string tr, string t, string id_nad) :
    id_odbiorcy(id_od), data_wyslania(data_wy), tresc(tr), id_nadawcy(id_nad), temat(t)
{}

string Wiadomosc::pobierz_id_odbiorcy() { return this->id_odbiorcy; }
string Wiadomosc::pobierz_tresc() { return this->tresc; }
string Wiadomosc::pobierz_data_wyslania() { return this->data_wyslania; }
string Wiadomosc::pobierz_id_nadawcy() { return this->id_nadawcy; }
string Wiadomosc::pobierz_temat() { return this->temat; }


Raport::Raport(string id_r, string o, string s, string id_p):
    id_projektu(id_p), id_raportu(id_r), status(s), opis(o)
{}

Raport::Raport(string opis, string status, string id_projektu) :
    opis(opis), status(status), id_projektu(id_projektu)
{}

string Raport::pobierz_id_raportu() { return this->id_raportu; }
string Raport::pobierz_opis() { return this->opis; }
string Raport::pobierz_status() { return this->status; }
string Raport::pobierz_id_projektu() { return this->id_projektu; }

Przypisanie_do_dzialow::Przypisanie_do_dzialow(string id_p, string id_d):
    id_pracownika(id_p), id_dzialu(id_d)
{}

string Przypisanie_do_dzialow::pobierz_id_pracownika() { return this->id_pracownika; }
string Przypisanie_do_dzialow::pobierz_id_dzialu() { return this->id_dzialu; }

Dzial::Dzial(string id_d, string naz, string adr):
    id_dzialu(id_d), adres(adr), nazwa(naz)
{}

string Dzial::pobierz_id_dzialu() { return this->id_dzialu; }
string Dzial::pobierz_adres() { return this->adres; }
string Dzial::pobierz_nazwa() { return this->nazwa; }
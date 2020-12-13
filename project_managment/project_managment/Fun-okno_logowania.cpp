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
    Prosba* prosba = new Prosba(imie, nazwisko, login, haslo, "1");
    if (Modyfikator_bazy::dodaj_prosbe(prosba)) return true;
    return false;
}

bool Fun_okno_logowania::czy_zajety_login(string login)
{
    bool czy_zajety = false;

    vector<Pracownik> prac = Pobieranie_bazy::pobierz_pracownik("select * from pracownicy where login = '" + login + "';");

    if (!prac.empty())
    {
        czy_zajety = true;
    }

    prac.clear();

    prac = Pobieranie_bazy::pobierz_pracownik("select * from prosby_o_dodanie where login = '" + login + "';");

    if (!prac.empty())
    {
        czy_zajety = true;
    }

    return czy_zajety;
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
string Dane_zalogowanego_pracownika::pobierz_id_zadania() { return this->id_zadania; }
string Dane_zalogowanego_pracownika::pobierz_id_projektu() { return this->id_projektu; }
string Dane_zalogowanego_pracownika::pobierz_id_projektu_nadrzednego()
{
    string id = pobierz_id_projektu();

    string Query = "select p.id_projektu, p.nazwa, p.opis, p.status, p.data_rozpoczecia, p.data_zakonczenia, p.id_projektu_nadrzednego, p.zadanie from projekt p join projekt p2 on p.id_projektu = p2.id_projektu_nadrzednego \
						where p2.id_projektu = " + id + "; ";
    vector<Projekt> projekt = Pobieranie_bazy::pobierz_projekt(Query);
    if (projekt.size() == 1) 
    {
        return projekt.begin()->pobierz_id_projektu();
    }    
    return string("");
}

std::vector<QString> Dane_zalogowanego_pracownika::pobierz_dzialy()
{
    string zapytanie = "select d.id_dzialu_firmy, d.nazwa, d.adres from dzialy_w_firmie as d\
                       join przypisanie_do_dzialow as p\
                       on d.id_dzialu_firmy = p.id_dzialu_firmy where p.id_pracownika = " +
                       Dane_zalogowanego_pracownika::instancja()->pobierz_id_pracownika() + ";";

    std::vector<Dzial>dzialy = Pobieranie_bazy::pobierz_dzial(zapytanie);

    std::vector<QString>dzialy_nazwy;

    for (int i = 0; i < dzialy.size(); i++)
    {
        dzialy_nazwy.push_back(QString::fromStdString(dzialy[i].pobierz_nazwa()));
    }

    return dzialy_nazwy;

}

bool Dane_zalogowanego_pracownika::pobierz_czy_blad() { return this->czy_blad; }

void Dane_zalogowanego_pracownika::ustaw_wyjatek(string wyjatek) { this->wyjatek = wyjatek; }
void Dane_zalogowanego_pracownika::ustaw_nazwe_projektu(string id_proj) { this->nazwa_projektu = id_proj; }
void Dane_zalogowanego_pracownika::ustaw_nazwe_zadania(string id_zad) { this->nazwa_zadania = id_zad; }
void Dane_zalogowanego_pracownika::ustaw_czy_blad(bool blad) { this->czy_blad = blad; }
void Dane_zalogowanego_pracownika::ustaw_id_zadania(string id_zad) { this->id_zadania = id_zad; }
void Dane_zalogowanego_pracownika::ustaw_id_projektu(string id_proj) { this->id_projektu = id_proj; }
void Dane_zalogowanego_pracownika::ustaw_dane_logowanie(string im, string na, string lo, string ha, string czy_ad, string id_pr)
{
    this->imie = im;
    this->nazwisko = na;
    this->haslo = ha;
    this->login = lo;
    this->id_pracownika = id_pr;
    this->czy_administator = czy_ad;
}

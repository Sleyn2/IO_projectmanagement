#pragma once
#include <iostream>
#include <pqxx/pqxx>
#include <vector>
#include <QtWidgets/QWidget>

using namespace std;
using namespace pqxx;

vector<string> podzial_stringa_na_slowa(string str);
string seperacja_stringa_od_kropki(string str);

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
    Prosba(string i, string n, string l, string h, string id_pr);
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
    string pobierz_opis();
    string pobierz_data_rozpoczecia();
    string pobierz_data_zakonczenia();
    string pobierz_status();
    string pobierz_zadanie();
};

class Przypisanie_do_projektow
{
private:
    string id_pracownika, id_projektu, kierownik;
public:
    Przypisanie_do_projektow(string id_prac, string id_proj, string kier);
    string pobierz_id_pracownika();
    string pobierz_id_projektu();
    string pobierz_kierownik();
};

class Wiadomosc
{
private:
    string id_odbiorcy, data_wyslania, tresc, id_nadawcy, temat;
public:
    Wiadomosc(string id_od, string data_wy, string tr, string id_nad, string t);
    string pobierz_id_odbiorcy();
    string pobierz_tresc();
    string pobierz_data_wyslania();
    string pobierz_id_nadawcy();
    string pobierz_temat();
};

class Raport
{
private:
    string id_raportu, opis, status, id_projektu;
public:
    Raport(string id_r, string o, string s, string id_p);
    string pobierz_id_raportu();
    string pobierz_opis();
    string pobierz_status();
    string pobierz_id_projektu();
};

class Przypisanie_do_dzialow
{
private:
    string id_pracownika, id_dzialu;
public:
    Przypisanie_do_dzialow(string id_p, string id_d);
    string pobierz_id_pracownika();
    string pobierz_id_dzialu();
};

class Dzial
{
private:
    string id_dzialu, nazwa, adres;
public:
    Dzial(string id_d, string adr, string naz);
    string pobierz_id_dzialu();
    string pobierz_adres();
    string pobierz_nazwa();
};



class Pobieranie_bazy
{
public:
   static vector<Pracownik> pobierz_pracownik(string zapytanie);
   static vector<Projekt> pobierz_projekt(string zapytanie);
   static vector<Przypisanie_do_projektow> pobierz_Przypisanie_do_projektow(string zapytanie);
   static vector<Prosba> pobierz_prosby(string zapytanie);
   static vector<Dzial> pobierz_dzial(string zapytanie);
   static vector<Przypisanie_do_dzialow> pobierz_przypisanie_do_dzialow(string zapytanie);
   static vector<Raport> pobierz_raport(string zapytanie);
   static vector<Wiadomosc> pobierz_wiadomosc(string zapytanie);
};

class Modyfikator_bazy
{
public:
   static bool dodaj_prosbe(Prosba *prosba);
   static bool dodaj_projekt(Projekt *Projekt);
   static bool dodaj_przyp_do_proj(Przypisanie_do_projektow *przypisanie);
   static bool dodaj_przyp_do_dzialu(Przypisanie_do_dzialow* przypisanie);
   static bool usun_przyp_do_dzialu(Przypisanie_do_dzialow* przypisanie);
   static bool dodaj_wiadomosc(Wiadomosc* wiadomosc);
   static bool usun_wiadomosc(string id_odb, string data_wys, string id_nad);
   static bool usun_zadanie(string zadanie);
   static bool zaktualizuj_zadanie (Projekt* zadanie);
   static bool aktualizuj_pracownika(Pracownik* prac);
};

class Fun_okno_logowania
{
public:
    static bool logowanie(string login, string haslo);
    static bool rejestracja(string imie, string nazwisko, string login, string haslo);
    static void zapisz_dane_logowania(Pracownik pracownik);

};

class Fun_projekty
{
public:
    static QStringList pobierz_liste_projektow();
    static QString pobierz_opis_projektu(string nazwa);
    static bool czy_kierownik ();
    static QStringList pobierz_liste_zadan();
    static bool utworz_projekt(string nazwa, string opis, string data_rozpoczecia, string data_zakonczenia, string status);
    static bool utworz_zadanie(string nazwa, string opis, string data_rozpoczecia, string data_zakonczenia, string status);
    static bool dodaj_przypisanie_do_projektu(string id_pracownika, string kierownik);
    static QStringList pobierz_liste_pracownikow();
    static QStringList pobierz_liste_pracownikow_w_projekcie(string id_projektu);
    static bool usun_zadanie(string nazwa_zadania);
    static Projekt pobierz_dane_zadania();
    static bool zaktualizuj_zadanie(string nazwa, string opis, string data_r, string data_z, string status);
};

class Fun_ustawienia
{
public:
    static bool edycja_danych_uzytkownika(string id_pracownika, string imie, string nazwisko, string login, string haslo, string czy_admin);
    static bool dodaj_do_dzialu_po_nazwie(string id_pracownika, string nazwa_dzial);
    static bool usun_z_dzialu_po_nazwie(string id_pracownika, string nazwa_dzial);
};

class Fun_wiadomosci
{
public:
    static bool dodaj_wiadomosc(string id_odb, string data_wys, string tresc, string temat);
    static bool usun_wiadomosc(string imie, string nazwisko, string data_wys);
    static QStringList pobierz_wiadomosci(bool wysylanie);
    static QString pobierz_tresc(string id_pracownika, string data_wyslania, bool czy_wyslana_wiadomosc);
};

class Dane_zalogowanego_pracownika
{
private:
    string imie, nazwisko, login, haslo, czy_administator, id_pracownika;
    string nazwa_projektu, nazwa_zadania, wyjatek;
    bool czy_blad;
    static Dane_zalogowanego_pracownika* w_instancja;
    Dane_zalogowanego_pracownika();
public:
    string pobierz_imie();
    string pobierz_nazwisko();
    string pobierz_login();
    string pobierz_haslo();
    string pobierz_id_pracownika();
    string pobierz_czy_administator();
    string pobierz_nazwe_projektu();
    string pobierz_nazwe_zadania();
    string pobierz_wyjatek();
    std::vector<Dzial> pobierz_dzialy();
    bool pobierz_czy_blad();
    void ustaw_nazwe_projektu(string id_proj);
    void ustaw_nazwe_zadania(string id_zad);
    void ustaw_wyjatek(string wyjatek);
    void ustaw_dane_logowanie(string im, string na, string lo, string ha, string czy_ad, string id_pr);
    void ustaw_czy_blad(bool blad);
    static Dane_zalogowanego_pracownika* instancja();
};
#include <iostream>
#include <pqxx/pqxx>
#include <vector>
#include "klasy.h"

using namespace std;
using namespace pqxx;

vector<Pracownik> Pobieranie_bazy::pobierz_pracownik(string zapytanie)
{
    vector<Pracownik> pracownicy;
    connection C("dbname = test user = postgres password = postgres \
      hostaddr = 127.0.0.1 port = 5432");
    if (C.is_open()) {
        try
        {
            work W{ C };
            result R{ W.exec(zapytanie) };
            for (auto wiersz : R)
            {
                Pracownik pracownik(to_string(wiersz[0]), to_string(wiersz[1]), to_string(wiersz[2]), to_string(wiersz[3]), to_string(wiersz[4]), to_string(wiersz[5]));
                pracownicy.push_back(pracownik);
            }
        }
            catch (exception e)
            {
                Dane_zalogowanego_pracownika::instancja()->ustaw_wyjatek(e.what());
                Dane_zalogowanego_pracownika::instancja()->ustaw_czy_blad(true);
                return pracownicy;
            }
            Dane_zalogowanego_pracownika::instancja()->ustaw_czy_blad(false);
            return pracownicy;        
    }
    else
    {
        return pracownicy;
        Dane_zalogowanego_pracownika::instancja()->ustaw_wyjatek("Brak po³¹czenia z baz¹");
        Dane_zalogowanego_pracownika::instancja()->ustaw_czy_blad(true);
    }
}

vector<Projekt> Pobieranie_bazy::pobierz_projekt(string zapytanie)
{
    vector<Projekt> projekty;
    connection C("dbname = test user = postgres password = postgres \
      hostaddr = 127.0.0.1 port = 5432");
    if (C.is_open()) {
        try
        {
            work W{ C };
            result R{ W.exec(zapytanie) };

            for (auto wiersz : R)
            {
                Projekt projekt(to_string(wiersz[0]), to_string(wiersz[1]), to_string(wiersz[2]), to_string(wiersz[3]), to_string(wiersz[4]), to_string(wiersz[5]),
                    to_string(wiersz[6]), to_string(wiersz[7]));
                projekty.push_back(projekt);
            }
        }
        catch (exception e)
        {
            Dane_zalogowanego_pracownika::instancja()->ustaw_wyjatek(e.what());
            Dane_zalogowanego_pracownika::instancja()->ustaw_czy_blad(true);
            return projekty;
        }
        Dane_zalogowanego_pracownika::instancja()->ustaw_czy_blad(false);
        return projekty;
    }
    else
    {
        Dane_zalogowanego_pracownika::instancja()->ustaw_wyjatek("Brak po³¹czenia z baz¹");
        Dane_zalogowanego_pracownika::instancja()->ustaw_czy_blad(true);
        return projekty;
    }
}

vector<Przypisanie_do_projektow> Pobieranie_bazy::pobierz_Przypisanie_do_projektow(string zapytanie)
{
    vector<Przypisanie_do_projektow> przypisanie_do_projektow;
    connection C("dbname = test user = postgres password = postgres \
      hostaddr = 127.0.0.1 port = 5432");
    if (C.is_open()) {
        try
        {
            work W{ C };
            result R{ W.exec(zapytanie) };

            for (auto wiersz : R)
            {
                Przypisanie_do_projektow przypisanie(to_string(wiersz[0]), to_string(wiersz[1]), to_string(wiersz[2]));
                przypisanie_do_projektow.push_back(przypisanie);
            }
        }
        catch (exception e)
        {
            Dane_zalogowanego_pracownika::instancja()->ustaw_wyjatek(e.what());
            Dane_zalogowanego_pracownika::instancja()->ustaw_czy_blad(true);
            return przypisanie_do_projektow;
        }
        Dane_zalogowanego_pracownika::instancja()->ustaw_czy_blad(false);
        return przypisanie_do_projektow;
    }
    else
    {
        Dane_zalogowanego_pracownika::instancja()->ustaw_wyjatek("Brak po³¹czenia z baz¹");
        Dane_zalogowanego_pracownika::instancja()->ustaw_czy_blad(true);
        return przypisanie_do_projektow;
    }
}


vector<Prosba> Pobieranie_bazy::pobierz_prosby(string zapytanie)
{
    vector<Prosba> prosby;
    connection C("dbname = test user = postgres password = postgres \
      hostaddr = 127.0.0.1 port = 5432");
    if (C.is_open()) {
        try
        {
            work W{ C };
            result R{ W.exec(zapytanie) };

            for (auto wiersz : R)
            {
                Prosba prosba(to_string(wiersz[0]), to_string(wiersz[1]), to_string(wiersz[2]), to_string(wiersz[3]), to_string(wiersz[4]));
                prosby.push_back(prosba);
            }
        }
        catch (exception e)
        {
            Dane_zalogowanego_pracownika::instancja()->ustaw_wyjatek(e.what());
            Dane_zalogowanego_pracownika::instancja()->ustaw_czy_blad(true);
            return prosby;
        }
        Dane_zalogowanego_pracownika::instancja()->ustaw_czy_blad(false);
        return prosby;
    }
    else
    {
        Dane_zalogowanego_pracownika::instancja()->ustaw_wyjatek("Brak po³¹czenia z baz¹");
        Dane_zalogowanego_pracownika::instancja()->ustaw_czy_blad(true);
        return prosby;
    }
}


vector<Dzial> Pobieranie_bazy::pobierz_dzial(string zapytanie)
{
    vector<Dzial> dzialy;
    connection C("dbname = test user = postgres password = postgres \
      hostaddr = 127.0.0.1 port = 5432");
    if (C.is_open()) {
        try
        {
            work W{ C };
            result R{ W.exec(zapytanie) };

            for (auto wiersz : R)
            {
                Dzial dzial(to_string(wiersz[0]), to_string(wiersz[1]), to_string(wiersz[2]));
                dzialy.push_back(dzial);
            }
        }
        catch (exception e)
        {
            Dane_zalogowanego_pracownika::instancja()->ustaw_wyjatek(e.what());
            Dane_zalogowanego_pracownika::instancja()->ustaw_czy_blad(true);
            return dzialy;
        }
        Dane_zalogowanego_pracownika::instancja()->ustaw_czy_blad(false);
        return dzialy;
    }
    else
    {
        Dane_zalogowanego_pracownika::instancja()->ustaw_wyjatek("Brak po³¹czenia z baz¹");
        Dane_zalogowanego_pracownika::instancja()->ustaw_czy_blad(true);
        return dzialy;
    }
}


vector<Przypisanie_do_dzialow> Pobieranie_bazy::pobierz_przypisanie_do_dzialow(string zapytanie)
{
    vector<Przypisanie_do_dzialow> przypisania;
    connection C("dbname = test user = postgres password = postgres \
      hostaddr = 127.0.0.1 port = 5432");
    if (C.is_open()) {
        try
        {
            work W{ C };
            result R{ W.exec(zapytanie) };

            for (auto wiersz : R)
            {
                Przypisanie_do_dzialow przypisanie(to_string(wiersz[0]), to_string(wiersz[1]));
                przypisania.push_back(przypisanie);
            }
        }
        catch (exception e)
        {
            Dane_zalogowanego_pracownika::instancja()->ustaw_wyjatek(e.what());
            Dane_zalogowanego_pracownika::instancja()->ustaw_czy_blad(true);
            return przypisania;
        }
        Dane_zalogowanego_pracownika::instancja()->ustaw_czy_blad(false);
        return przypisania;
    }
    else
    {
        Dane_zalogowanego_pracownika::instancja()->ustaw_wyjatek("Brak po³¹czenia z baz¹");
        Dane_zalogowanego_pracownika::instancja()->ustaw_czy_blad(true);
        return przypisania;
    }
}


vector<Raport> Pobieranie_bazy::pobierz_raport(string zapytanie)
{
    vector<Raport> raporty;
    connection C("dbname = test user = postgres password = postgres \
      hostaddr = 127.0.0.1 port = 5432");
    if (C.is_open()) {
        try
        {
            work W{ C };
            result R{ W.exec(zapytanie) };

            for (auto wiersz : R)
            {
                Raport raport(to_string(wiersz[0]), to_string(wiersz[1]), to_string(wiersz[2]), to_string(wiersz[3]));
                raporty.push_back(raport);
            }
        }
        catch (exception e)
        {
            Dane_zalogowanego_pracownika::instancja()->ustaw_wyjatek(e.what());
            Dane_zalogowanego_pracownika::instancja()->ustaw_czy_blad(true);
            return raporty;
        }
        Dane_zalogowanego_pracownika::instancja()->ustaw_czy_blad(false);
        return raporty;
    }
    else
    {
        Dane_zalogowanego_pracownika::instancja()->ustaw_wyjatek("Brak po³¹czenia z baz¹");
        Dane_zalogowanego_pracownika::instancja()->ustaw_czy_blad(true);
        return raporty;
    }
}


vector<Wiadomosc> Pobieranie_bazy::pobierz_wiadomosc(string zapytanie)
{
    vector<Wiadomosc> wiadomosci;
    connection C("dbname = test user = postgres password = postgres \
      hostaddr = 127.0.0.1 port = 5432");
    if (C.is_open()) {
        try
        {
            work W{ C };
            result R{ W.exec(zapytanie) };

            for (auto wiersz : R)
            {
                Wiadomosc wiadomosc(to_string(wiersz[0]), to_string(wiersz[1]), to_string(wiersz[2]), to_string(wiersz[3]), to_string(wiersz[4]));
                wiadomosci.push_back(wiadomosc);
            }
        }
        catch (exception e)
        {
            Dane_zalogowanego_pracownika::instancja()->ustaw_wyjatek(e.what());
            Dane_zalogowanego_pracownika::instancja()->ustaw_czy_blad(true);
            return wiadomosci;
        }
        Dane_zalogowanego_pracownika::instancja()->ustaw_czy_blad(false);
        return wiadomosci;
    }
    else
    {
        Dane_zalogowanego_pracownika::instancja()->ustaw_wyjatek("Brak po³¹czenia z baz¹");
        Dane_zalogowanego_pracownika::instancja()->ustaw_czy_blad(true);
        return wiadomosci;
    }
}

vector<Raport> Pobieranie_bazy::pobierz_raporty()
{
    vector<Raport> raporty;
    connection C("dbname = test user = postgres password = postgres \
      hostaddr = 127.0.0.1 port = 5432");
    if (C.is_open()) {
        try
        {
            work W{ C };
            result R{ W.exec(string("")) };

            for (auto wiersz : R)
            {
                Raport raport(to_string(wiersz[0]), to_string(wiersz[1]), to_string(wiersz[2]), to_string(wiersz[3]));
                raporty.push_back(raport);
            }
        }
        catch (exception e)
        {
            Dane_zalogowanego_pracownika::instancja()->ustaw_wyjatek(e.what());
            Dane_zalogowanego_pracownika::instancja()->ustaw_czy_blad(true);
            return raporty;
        }
        Dane_zalogowanego_pracownika::instancja()->ustaw_czy_blad(false);
        return raporty;
    }
    else
    {
        Dane_zalogowanego_pracownika::instancja()->ustaw_wyjatek("Brak po³¹czenia z baz¹");
        Dane_zalogowanego_pracownika::instancja()->ustaw_czy_blad(true);
        return raporty;
    }
}



#include <iostream>
#include <pqxx/pqxx>
#include <vector>
#include "klasy.h"
#include <qmessagebox.h>

using namespace std;
using namespace pqxx;


bool Modyfikator_bazy::dodaj_prosbe(Prosba* prosba)
{
    connection C(Dane_polaczenia::Conncet());
    if (C.is_open()) {
    
        try
        {
            work W{ C };
            W.exec0("insert into Prosby_o_dodanie (Imie, Nazwisko, Login, Haslo) values ('" + to_string(prosba->pobierz_imie()) + "', '"
                + to_string(prosba->pobierz_nazwisko()) + "', '" + to_string(prosba->pobierz_login()) + "', '" + to_string(prosba->pobierz_haslo()) + "');");
            W.commit();
        }
        catch (exception e)
        {
          Dane_zalogowanego_pracownika::instancja()->ustaw_wyjatek(e.what());
            return false;
        }
        return true;
        
    }
    else
    {
        Dane_zalogowanego_pracownika::instancja()->ustaw_wyjatek("Brak po³¹czenia z baz¹");
        return false;
    }
}

bool Modyfikator_bazy::aktualizuj_pracownika(Pracownik* prac)
{
    connection C(Dane_polaczenia::Conncet());
    if (C.is_open()) {

        try
        {
            work W{ C };

            W.exec0("update pracownicy set imie = '" + to_string(prac->pobierz_imie()) +
                "', id_pracownika = '" + to_string(prac->pobierz_id_pracownika()) +
                "', nazwisko = '" + to_string(prac->pobierz_nazwisko()) +
                "', login = '" + to_string(prac->pobierz_login()) +
                "', haslo = '" + to_string(prac->pobierz_haslo()) +
                "', administrator = '" + to_string(prac->pobierz_czy_administator()) +
                "' where id_pracownika = '" + to_string(prac->pobierz_id_pracownika()) + "';");
            W.commit();
        }
        catch (exception e)
        {
            Dane_zalogowanego_pracownika::instancja()->ustaw_wyjatek(e.what());
            return false;
        }
        return true;

    }
    else
    {
        Dane_zalogowanego_pracownika::instancja()->ustaw_wyjatek("Brak po³¹czenia z baz¹");
        return false;
    }
}

bool Modyfikator_bazy::zaktualizuj_raport(string status, string id_projektu)
{
    connection C(Dane_polaczenia::Conncet());
    if (C.is_open()) {
        try
        {
            work W{ C };
            W.exec0("update raporty set status = '" + status + "' where id_raportu = " + id_projektu + " ;");
            W.commit();
        }
        catch (exception e)
        {
            Dane_zalogowanego_pracownika::instancja()->ustaw_wyjatek(e.what());
            return false;
        }
        return true;

    }
    else
    {
        Dane_zalogowanego_pracownika::instancja()->ustaw_wyjatek("Brak po³¹czenia z baz¹");
        return false;
    }
}

bool Modyfikator_bazy::dodaj_projekt(Projekt *projekt)
{
    connection C(Dane_polaczenia::Conncet());
    if (C.is_open()) {
        try
        {
            work W{ C };
            W.exec0("insert into Projekt (Nazwa, Opis, Data_rozpoczecia, Data_zakonczenia, Status, Zadanie, Id_projektu_nadrzednego) values ('" + to_string(projekt->pobierz_nazwa()) + "', '"
                + to_string(projekt->pobierz_opis()) + "', '" + to_string(projekt->pobierz_data_rozpoczecia()) + "', '" + to_string(projekt->pobierz_data_zakonczenia()) + "', '" +
                projekt->pobierz_status() + "', " + projekt->pobierz_zadanie() + ", " + projekt->pobierz_id_projektu_nadrzednego() + ");");
            W.commit();
        }
        catch (exception e)
        {
            Dane_zalogowanego_pracownika::instancja()->ustaw_wyjatek(e.what());
            return false;
        }
        return true;

    }
    else
    {
        Dane_zalogowanego_pracownika::instancja()->ustaw_wyjatek("Brak po³¹czenia z baz¹");
        return false;
    }
}

bool Modyfikator_bazy::dodaj_dzial(Dzial* dzial)
{
    connection C(Dane_polaczenia::Conncet());
    if (C.is_open()) {
        try
        {
            work W{ C };
            W.exec0("insert into dzialy_w_firmie (nazwa, adres) values ('" + dzial->pobierz_nazwa() + "', '" + dzial->pobierz_adres() + "');");
            W.commit();
        }
        catch (exception e)
        {
            Dane_zalogowanego_pracownika::instancja()->ustaw_wyjatek(e.what());
            cerr << e.what();
            return false;
        }
        return true;

    }
    else
    {
        Dane_zalogowanego_pracownika::instancja()->ustaw_wyjatek("Brak po³¹czenia z baz¹");
        return false;
    }
}

bool Modyfikator_bazy::dodaj_przyp_do_proj(Przypisanie_do_projektow *przypisanie)
{
    connection C(Dane_polaczenia::Conncet());
    if (C.is_open()) {
        try
        {
            work W{ C };
            W.exec0("insert into Przypisanie_do_projektow values (" + przypisanie->pobierz_id_pracownika() + ", "
                + przypisanie->pobierz_id_projektu() + ", " + przypisanie->pobierz_kierownik() + ");");
            W.commit();
        }
        catch (exception e)
        {
            Dane_zalogowanego_pracownika::instancja()->ustaw_wyjatek(e.what());
            return false;
        }
        return true;
    }
    else
    {
        Dane_zalogowanego_pracownika::instancja()->ustaw_wyjatek("Brak po³¹czenia z baz¹");
        return false;
    }
}

bool Modyfikator_bazy::dodaj_przyp_do_dzialu(Przypisanie_do_dzialow* przypisanie)
{
    connection C(Dane_polaczenia::Conncet());
    if (C.is_open()) {
        try
        {
            string id_d = przypisanie->pobierz_id_dzialu();
            string id_p = przypisanie->pobierz_id_pracownika();

            work W{ C };
            W.exec0("insert into przypisanie_do_dzialow values (" +
                    id_p + ", " + id_d + ");");
            W.commit();
        }
        catch (exception e)
        {
            Dane_zalogowanego_pracownika::instancja()->ustaw_wyjatek(e.what());
            return false;
        }
        return true;
    }
    else
    {
        Dane_zalogowanego_pracownika::instancja()->ustaw_wyjatek("Brak po³¹czenia z baz¹");
        return false;
    }
}

bool Modyfikator_bazy::dodaj_raport(Raport* raport)
{
    connection C(Dane_polaczenia::Conncet());
    if (C.is_open()) {
        try
        {
            work W{ C };
            W.exec0("insert into raporty (id_nadawcy, tytul, opis, status, id_projektu) values (" +
                raport->pobierz_id_nadawcy() + ", '" +
                raport->pobierz_tytul() +"', '" + raport->pobierz_opis() + "', '" +
                raport->pobierz_status() + "', " + raport->pobierz_id_projektu() + ");");
            W.commit();
        }
        catch (exception e)
        {
            Dane_zalogowanego_pracownika::instancja()->ustaw_wyjatek(e.what());
            return false;
        }
        return true;

    }
    else
    {
        Dane_zalogowanego_pracownika::instancja()->ustaw_wyjatek("Brak po³¹czenia z baz¹");
        return false;
    }
}

bool Modyfikator_bazy::usun_przyp_do_dzialu(Przypisanie_do_dzialow* przypisanie)
{
    connection C(Dane_polaczenia::Conncet());
    if (C.is_open()) {
        try
        {
            string id_d = przypisanie->pobierz_id_dzialu();
            string id_p = przypisanie->pobierz_id_pracownika();

            work W{ C };
            W.exec0("delete from przypisanie_do_dzialow where id_pracownika = '" +
                    id_p + "' and id_dzialu_firmy = '" + id_d + "';");
            W.commit();
        }
        catch (exception e)
        {
            Dane_zalogowanego_pracownika::instancja()->ustaw_wyjatek(e.what());
            return false;
        }
        return true;
    }
    else
    {
        Dane_zalogowanego_pracownika::instancja()->ustaw_wyjatek("Brak po³¹czenia z baz¹");
        return false;
    }
}

bool Modyfikator_bazy::usun_zadanie(string zadanie)
{
    connection C(Dane_polaczenia::Conncet());
    if (C.is_open()) {
        try
        {
            work W{ C };

            vector<Projekt> id_zadania;
            id_zadania = Pobieranie_bazy::pobierz_projekt("select * from Projekt where nazwa= '" +
                Dane_zalogowanego_pracownika::instancja()->pobierz_nazwe_zadania() + "';");
            W.exec0("delete from Projekt where id_projektu = " + id_zadania[0].pobierz_id_projektu() + ";");
            W.exec0("delete from Przypisanie_do_projektu where id_projektu = " + id_zadania[0].pobierz_id_projektu() + ";");
            W.commit();
        }
        catch (exception e)
        {
            Dane_zalogowanego_pracownika::instancja()->ustaw_wyjatek(e.what());
            return false;
        }
        return true;

    }
    else
    {
        Dane_zalogowanego_pracownika::instancja()->ustaw_wyjatek("Brak po³¹czenia z baz¹");
        return false;
    }
}

bool Modyfikator_bazy::zaktualizuj_zadanie(Projekt *zadanie)
{
    connection C(Dane_polaczenia::Conncet());
    if (C.is_open()) {
        try
        {
            work W{ C };
            W.exec0("update Projekt set Nazwa = '" + zadanie->pobierz_nazwa() + "', Opis = '" + zadanie->pobierz_opis() + "', Data_rozpoczecia = '" +
                zadanie->pobierz_data_rozpoczecia() + "', Data_zakonczenia = '" + zadanie->pobierz_data_zakonczenia() + "', status= '"
                + zadanie->pobierz_status() + "' where Nazwa = '" + Dane_zalogowanego_pracownika::instancja()->pobierz_nazwe_zadania() + "';");
            W.commit();
        }
        catch (exception e)
        {
            Dane_zalogowanego_pracownika::instancja()->ustaw_wyjatek(e.what());
            return false;
        }
        return true;

    }
    else
    {
        Dane_zalogowanego_pracownika::instancja()->ustaw_wyjatek("Brak po³¹czenia z baz¹");
        return false;
    }
}

bool Modyfikator_bazy::dodaj_wiadomosc(Wiadomosc* wiadomosc) 
{
    connection C(Dane_polaczenia::Conncet());
    if (C.is_open()) {
        try
        {
            string s = wiadomosc->pobierz_id_nadawcy();
            work W{ C };
            W.exec0("insert into Wiadomosci (Id_odbiorcy, Data_wyslania, Tresc, Temat, Id_nadawcy) values (" + 
                wiadomosc->pobierz_id_odbiorcy() + ", '" + wiadomosc->pobierz_data_wyslania() + "', '" +
                wiadomosc->pobierz_tresc() + "', '" + wiadomosc->pobierz_temat()+ "', " + wiadomosc->pobierz_id_nadawcy()+  ");");
            W.commit();
        }
        catch (exception e)
        {
            Dane_zalogowanego_pracownika::instancja()->ustaw_wyjatek(e.what());
            return false;
        }
        return true;

    }
    else
    {
        Dane_zalogowanego_pracownika::instancja()->ustaw_wyjatek("Brak po³¹czenia z baz¹");
        return false;
    }
}

bool Modyfikator_bazy::dodaj_wiadomosc_raportu(Wiadomosc* wiadomosc)
{
    connection C(Dane_polaczenia::Conncet());
    if (C.is_open()) {
        try
        {
            string s = wiadomosc->pobierz_id_nadawcy();
            work W{ C };
            W.exec0("insert into Wiadomosci (Id_odbiorcy, Data_wyslania, Tresc, Temat, Id_nadawcy, Typ) values (" +
                wiadomosc->pobierz_id_odbiorcy() + ", '" + wiadomosc->pobierz_data_wyslania() + "', '" +
                wiadomosc->pobierz_tresc() + "', '" + wiadomosc->pobierz_temat() + "', " + wiadomosc->pobierz_id_nadawcy() +
                ", " + wiadomosc->pobierz_typ() + ");");
            W.commit();
        }
        catch (exception e)
        {
            Dane_zalogowanego_pracownika::instancja()->ustaw_wyjatek(e.what());
            return false;
        }
        return true;

    }
    else
    {
        Dane_zalogowanego_pracownika::instancja()->ustaw_wyjatek("Brak po³¹czenia z baz¹");
        return false;
    }
}

bool Modyfikator_bazy::usun_wiadomosc(string id_odb, string data_wys, string id_nad)
{
    connection C(Dane_polaczenia::Conncet());
    if (C.is_open()) {
        try
        {
            work W{ C };
            W.exec0("delete from Wiadomosci where Id_odbiorcy = " + id_odb + " and Data_wyslania = '" + data_wys + "' and Id_nadawcy = " + id_nad + ";");
            W.commit();
        }
        catch (exception e)
        {
            Dane_zalogowanego_pracownika::instancja()->ustaw_wyjatek(e.what());
            return false;
        }
        return true;

    }
    else
    {
        Dane_zalogowanego_pracownika::instancja()->ustaw_wyjatek("Brak po³¹czenia z baz¹");
        return false;
    }
}

bool Modyfikator_bazy::wykonaj_zapytanie(std::string zapytanie)
{
    connection C(Dane_polaczenia::Conncet());
    if (C.is_open()) {
        try
        {
            work W{ C };
            W.exec0(zapytanie);
            W.commit();
        }
        catch (exception e)
        {
            Dane_zalogowanego_pracownika::instancja()->ustaw_wyjatek(e.what());
            return false;
        }
        return true;

    }
    else
    {
        Dane_zalogowanego_pracownika::instancja()->ustaw_wyjatek("Brak po³¹czenia z baz¹");
        return false;
    }
}


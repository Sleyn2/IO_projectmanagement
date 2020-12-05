#include "logowanie_okno.h"
#include "project_managment.h"
#include "projekty_zadania_okno.h"
#include "edycja_zadanie_okno.h"
#include "wiadomosci_okno.h"
#include "zmien_haslo_okno.h"
#include "raport_tworz_okno.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);


    if (!Dane_polaczenia::init()) {
        QMessageBox err;
        err.setWindowTitle("Blad bazy danych");
        err.setText("Blad odczytu pliku database.conf\nPopraw lub dodaj plik");
        err.setIcon(QMessageBox::Critical);
        err.setStandardButtons(QMessageBox::Ok);
        err.exec();
        return 0;
    }

    project_managment w;

    Projekty_zadania_okno tworzenie_zadan_raportow;
    edycja_zadanie_okno edytowanie_zadan;
    wiadomosci_okno tworzenie_wiadomosci;
    zmien_haslo_okno zmien_haslo;
    raport_tworz_okno tworzenie_raportu;
    raport_edycja_okno odbieranie_raportu;
    logowanie_okno login;

    login.show();
    login.setwindow(&w);
    w.ustaw_okna(&tworzenie_zadan_raportow, &edytowanie_zadan, &tworzenie_wiadomosci,
        &zmien_haslo, &tworzenie_raportu, &odbieranie_raportu);

    return a.exec();
}

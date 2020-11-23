#include "logowanie_okno.h"
#include "project_managment.h"
#include "projekty_zadania_okno.h"
#include "edycja_zadanie_okno.h"
#include "wiadomosci_okno.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Projekty_zadania_okno tworzenie_zadan_raportow;
    edycja_zadanie_okno edytowanie_zadan;
    wiadomosci_okno tworzenie_wiadomosci;

    project_managment w;
    logowanie_okno login;

    login.show();
    login.setwindow(&w);
    w.ustaw_okna(&tworzenie_zadan_raportow, &edytowanie_zadan, &tworzenie_wiadomosci);

    return a.exec();
}

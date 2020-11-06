#include "logowanie_okno.h"
#include "project_managment.h"
#include "projekty_zadania_okno.h"
#include "edycja_zadanie_okno.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Projekty_zadania_okno tworzenie_zadan_raportow;
    edycja_zadanie_okno edytowanie_zadan;
    project_managment w;
    logowanie_okno login;

    login.show();
    login.setwindow(&w);
    w.ustaw_okno_tworzenia(&tworzenie_zadan_raportow);
    w.ustaw_okno_edycji(&edytowanie_zadan);

    return a.exec();
}

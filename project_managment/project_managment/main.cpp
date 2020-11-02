#include "logowanie_okno.h"
#include "project_managment.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    project_managment w;
    logowanie_okno login;
    login.show();
    login.setwindow(&w);

    return a.exec();
}

#include "logowanie_okno.h"
#include "project_managment.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    logowanie_okno login;
    login.show();

    return a.exec();
}

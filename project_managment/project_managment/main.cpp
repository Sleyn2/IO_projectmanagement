#include "project_managment.h"
#include "logowanie_okno.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    
    logowanie_okno login;
    login.show();

    project_managment w;
    w.show();
    return a.exec();
}

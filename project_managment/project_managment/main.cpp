#include "project_managment.h"
#include "LoginWindow.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    
    LoginWindow login;
    login.show();

    project_managment w;
    w.show();
    return a.exec();
}

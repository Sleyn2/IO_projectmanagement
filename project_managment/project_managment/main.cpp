#include "project_managment.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    project_managment w;
    w.show();
    return a.exec();
}

#include "login_window.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    login_window w;
    w.show();
    return a.exec();
}

#include "login_window.h"
#include <qlineedit.h>
#include <qmessagebox.h>

login_window::login_window(QWidget *parent)
    : QWidget(parent)
{
    ui.setupUi(this);
}
void login_window::on_pushButton_login_clicked()
{
    QString username = ui.lineEdit_username->text();
    QString password = ui.lineEdit_password->text();

    if (username == "root" && password == "root")
    {
        //tutaj bêdzie logowanie
        QMessageBox::information(this, "Login", "correct");
    }
}
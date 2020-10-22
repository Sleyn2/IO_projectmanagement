#include "LoginWindow.h"
#include <qmessagebox.h>
#include <QLineEdit>
#include <qstring.h>


LoginWindow::LoginWindow(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
}

LoginWindow::~LoginWindow()
{
}

void LoginWindow::on_pushButton_login_clicked()
{
    QString username = ui.lineEdit_username->text();
    QString password = ui.lineEdit_password->text();

    if (username == "root" && password == "root")
    {
        //tutaj bêdzie logowanie
        QMessageBox::information(this, "Login", "correct");
    }
    else
    {
        QMessageBox::information(this, "Login", "incorrect, try again");
    }

}
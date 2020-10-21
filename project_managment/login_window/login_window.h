#pragma once

#include <QtWidgets/QWidget>
#include "ui_login_window.h"

class login_window : public QWidget
{
    Q_OBJECT

public:
    login_window(QWidget *parent = Q_NULLPTR);
private slots:
    void login_window::on_pushButton_login_clicked();
private:
    Ui::login_windowClass ui;
};

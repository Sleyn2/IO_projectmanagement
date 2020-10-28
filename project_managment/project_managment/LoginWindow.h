#pragma once

#include <QWidget>
#include "ui_LoginWindow.h"

class LoginWindow : public QWidget
{
	Q_OBJECT

public:
	LoginWindow(QWidget *parent = Q_NULLPTR);
	~LoginWindow();
private slots:
	void on_pushButton_login_clicked();
	void on_pushButton_register_clicked();
	void on_pushButton_register_2_clicked();
	void on_pushButton_cancel_clicked();

private:
	Ui::LoginWindow ui;
};

#pragma once
#include "project_managment.h"
#include "ui_logowanie_okno.h"
#include "klasy.h"
#include <QWidget>
#include <pqxx/pqxx>

class logowanie_okno : public QWidget
{
	Q_OBJECT

public:
	logowanie_okno(QWidget *parent = Q_NULLPTR);
	~logowanie_okno();

private slots:
	void on_pushButton_login_clicked();
	void on_pushButton_register_clicked();
	void on_pushButton_register_2_clicked();
	void on_pushButton_cancel_clicked();

private:
	Ui::logowanie_okno ui;
};

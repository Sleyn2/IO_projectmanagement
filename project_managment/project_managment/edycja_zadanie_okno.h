#pragma once

#include <QWidget>
#include "ui_edycja_zadanie_okno.h"

class edycja_zadanie_okno : public QWidget
{
	Q_OBJECT

public:
	edycja_zadanie_okno(QWidget *parent = Q_NULLPTR);
	~edycja_zadanie_okno();
	void wczytaj_dane();
private slots:
	void on_pushButton_anuluj_clicked();
	void on_pushButton_potwierdz_clicked();
	void on_pushButton_usun_clicked();

private:
	Ui::edycja_zadanie_okno ui;
};

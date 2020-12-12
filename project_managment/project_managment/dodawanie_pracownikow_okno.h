#pragma once

#include <QWidget>
//#include "ui_dodawanie_pracownikow_okno.h"
#include "klasy.h"
#include "ui_dodawanie_pracownikow_okno.h"


class dodawanie_pracownikow_okno : public QWidget
{
	Q_OBJECT

public:
	dodawanie_pracownikow_okno(QWidget *parent = Q_NULLPTR);
	~dodawanie_pracownikow_okno();

private slots:


private:
	Ui::dodawanie_pracownikow_okno ui;

	void odswiezProsby();
};

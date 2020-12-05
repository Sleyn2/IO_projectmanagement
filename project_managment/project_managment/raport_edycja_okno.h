#pragma once

#include <QWidget>
#include "ui_raport_edycja_okno.h"
#include "klasy.h"

class raport_edycja_okno : public QWidget
{
	Q_OBJECT

public:
	raport_edycja_okno(QWidget *parent = Q_NULLPTR);
	~raport_edycja_okno();
	void ustawVectorRaportow(vector<Raport>* pRaporty);
	void ustawIndex(int idx);
	void wczytajDane();

private:
	Ui::raport_edycja_okno ui;
	vector<Raport>* pRaporty;
	int index;
};

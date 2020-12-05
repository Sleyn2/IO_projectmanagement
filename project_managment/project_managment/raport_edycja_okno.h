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
	void on_pushButtonZaakceptuj_clicked();
	void on_pushButtonZwroc_clicked();
	void on_pushButtonOdpowiedzRaport_clicked();
	void on_pushButtonOdpowiedzAnuluj_clicked();

private:
	Ui::raport_edycja_okno ui;
	vector<Raport>* pRaporty;
	bool zwrot;
	int index;
};

#pragma once

#include <QWidget>
#include "ui_raport_tworz_okno.h"

class raport_tworz_okno : public QWidget
{
	Q_OBJECT

public:
	raport_tworz_okno(QWidget *parent = Q_NULLPTR);
	~raport_tworz_okno();

private slots:
	void on_pushButtonAnuluj_clicked();
	void on_pushButtonWyslij_clicked();
private:
	Ui::raport_tworz_okno ui;
};

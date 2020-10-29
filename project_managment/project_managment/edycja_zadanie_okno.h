#pragma once

#include <QWidget>
#include "ui_edycja_zadanie_okno.h"

class edycja_zadanie_okno : public QWidget
{
	Q_OBJECT

public:
	edycja_zadanie_okno(QWidget *parent = Q_NULLPTR);
	~edycja_zadanie_okno();

private:
	Ui::edycja_zadanie_okno ui;
};

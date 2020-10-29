#pragma once

#include <QWidget>
#include "ui_raport_edycja_okno.h"

class raport_edycja_okno : public QWidget
{
	Q_OBJECT

public:
	raport_edycja_okno(QWidget *parent = Q_NULLPTR);
	~raport_edycja_okno();

private:
	Ui::raport_edycja_okno ui;
};

#pragma once

#include <QWidget>
#include "ui_zmiana_hasla_okno.h"

class zmiana_hasla_okno : public QWidget
{
	Q_OBJECT

public:
	zmiana_hasla_okno(QWidget *parent = Q_NULLPTR);
	~zmiana_hasla_okno();

private:
	Ui::zmiana_hasla_okno ui;
};

#pragma once

#include <QWidget>
#include "ui_EdycjaRaportow.h"

class EdycjaRaportow : public QWidget
{
	Q_OBJECT

public:
	EdycjaRaportow(QWidget *parent = Q_NULLPTR);
	~EdycjaRaportow();

private:
	Ui::EdycjaRaportow ui;
};

#pragma once

#include <QWidget>
#include "ui_GenerujRaport.h"

class GenerujRaport : public QWidget
{
	Q_OBJECT

public:
	GenerujRaport(QWidget *parent = Q_NULLPTR);
	~GenerujRaport();

private:
	Ui::GenerujRaport ui;
};

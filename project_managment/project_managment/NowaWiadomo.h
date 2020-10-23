#pragma once

#include <QWidget>
#include "ui_NowaWiadomo.h"

class NowaWiadomo : public QWidget
{
	Q_OBJECT

public:
	NowaWiadomo(QWidget *parent = Q_NULLPTR);
	~NowaWiadomo();

private:
	Ui::NowaWiadomo ui;
};

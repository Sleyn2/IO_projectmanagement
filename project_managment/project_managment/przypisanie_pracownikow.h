#pragma once

#include <QWidget>
#include "ui_przypisanie_pracownikow.h"

class Przypisanie_pracownikow : public QWidget
{
	Q_OBJECT

public:
	Przypisanie_pracownikow(QWidget *parent = Q_NULLPTR);
	~Przypisanie_pracownikow();

private:
	Ui::Przypisanie_pracownikow ui;
};

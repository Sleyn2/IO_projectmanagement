#pragma once

#include <QWidget>
#include <qmessagebox.h>
#include "ui_projekty_zadania_okno.h"
#include "klasy.h"

class Projekty_zadania_okno : public QWidget
{
	Q_OBJECT

public:
	Projekty_zadania_okno(QWidget *parent = Q_NULLPTR);
	~Projekty_zadania_okno();
	void ustaw_tryb(bool czy_projekt);
private slots:
	void on_pushButton_cancel_clicked();
	void on_pushButton_add_clicked();
private:
	Ui::Projekty_zadania_okno ui;
	bool projekt;
};

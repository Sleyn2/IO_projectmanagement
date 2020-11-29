#pragma once

#include <QWidget>
#include <QMessageBox>
#include "ui_zmien_haslo_okno.h"
#include "klasy.h"

class zmien_haslo_okno : public QWidget
{
	Q_OBJECT

public:
	zmien_haslo_okno(QWidget *parent = Q_NULLPTR);
	~zmien_haslo_okno();

private slots:
	void on_pushButton_zapisz_clicked();
	void on_pushButton_anuluj_clicked();

private:
	Ui::zmien_haslo_okno ui;
};

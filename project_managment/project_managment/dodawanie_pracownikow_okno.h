#pragma once

#include <QWidget>
#include <QMessageBox>
#include "klasy.h"
#include "ui_dodawanie_pracownikow_okno.h"


class dodawanie_pracownikow_okno : public QWidget
{
	Q_OBJECT

public:
	dodawanie_pracownikow_okno(QWidget *parent = Q_NULLPTR);
	~dodawanie_pracownikow_okno();
	void odswiezProsby();

private slots:
	void on_comboBox_wybierz_prac_currentTextChanged();
	void on_pushButton_dodaj_clicked();
	void on_pushButton_odrzuc_clicked();

private:
	Ui::dodawanie_pracownikow_okno ui;


};

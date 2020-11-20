#pragma once

#include <QWidget>
#include "ui_przypisanie_pracownikow.h"
#include "klasy.h"

class Przypisanie_pracownikow : public QWidget
{
	Q_OBJECT

public:
	Przypisanie_pracownikow(QWidget *parent = Q_NULLPTR);
	~Przypisanie_pracownikow();
	void setID(int temp);
	void wczytajUzytkownikow();

private slots:
	void on_pushButton_zatwierdz_clicked();
	void on_pushButton_anuluj_clicked();
	void on_pushButton_dodaj_clicked();
	void on_pushButton_usun_clicked();
	void odswiezListy(bool add);
	void on_lineEdit_current_textChanged(const QString& arg1);
	void on_lineEdit_all_textChanged(const QString& arg1);
	void on_listWidget_all_itemClicked(QListWidgetItem* item);
	void on_listWidget_current_itemClicked(QListWidgetItem* item);
private:
	Ui::Przypisanie_pracownikow ui;
	QStringList systemUsers;
	QStringList currentUsers;
	QListWidgetItem* systemUser;
	QListWidgetItem* taskUser;
	bool if_id = false;
	int id;
};

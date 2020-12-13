#include "przypisanie_pracownikow.h"
#include <qmessagebox.h>

Przypisanie_pracownikow::Przypisanie_pracownikow(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	this->taskUser = nullptr;
	this->systemUser = nullptr;
}

Przypisanie_pracownikow::~Przypisanie_pracownikow()
{
}

void Przypisanie_pracownikow::setID(int temp)
{
	this->if_id = true;
	this->id = temp;
}

void Przypisanie_pracownikow::on_lineEdit_all_textChanged(const QString& arg1)
{
	QRegExp regExp(arg1, Qt::CaseInsensitive, QRegExp::Wildcard);
	ui.listWidget_all->clear();
	ui.listWidget_all->addItems(systemUsers.filter(regExp));
}
void Przypisanie_pracownikow::on_lineEdit_current_textChanged(const QString& arg1)
{
	QRegExp regExp(arg1, Qt::CaseInsensitive, QRegExp::Wildcard);
	ui.listWidget_current->clear();
	ui.listWidget_current->addItems(currentUsers.filter(regExp));
}
void Przypisanie_pracownikow::wczytajUzytkownikow()
{
	currentUsers.clear();
	systemUsers.clear();
	ui.listWidget_all->clear();
	ui.listWidget_current->clear();

	systemUsers = Fun_projekty::pobierz_liste_pracownikow();
	/* tu by³ if (this->id_id) ale nie wiem po co ?*/
		currentUsers = Fun_projekty::pobierz_liste_pracownikow_w_projekcie();
		for (int i = 0; i < currentUsers.length(); i++)
		{
			systemUsers.removeAll(currentUsers[i]);
		}
	
	currentUsers.sort();
	systemUsers.sort();
	ui.listWidget_all->addItems(systemUsers);
	ui.listWidget_current->addItems(currentUsers);
}
void Przypisanie_pracownikow::odswiezListy(bool add)
{
	if (add)
	{
		for (int i = 0; i < currentUsers.length(); i++)
		{
			systemUsers.removeAll(currentUsers[i]);
		}
	}
	else
	{
		for (int i = 0; i < systemUsers.length(); i++)
		{
			currentUsers.removeAll(systemUsers[i]);
		}
	}
	ui.listWidget_all->clear();
	ui.listWidget_current->clear();
	currentUsers.sort();
	systemUsers.sort();
	ui.listWidget_all->addItems(systemUsers);
	ui.listWidget_current->addItems(currentUsers);

	/* Dezaktywacaja przyciskow, moze byæ tylko jeden pracownik w zadaniu*/
	if (this->currentUsers.length() >= 1)
		ui.pushButton_dodaj->setEnabled(false);
	else if(this->currentUsers.length() < 1)
		ui.pushButton_dodaj->setEnabled(true);
}
/**
 * Metoda obs³uguj¹ca przycisk zawtwierdzaj¹y pracownika
 * Dodaje pracownika do zadania lub zmienia go z innym 
 */
void Przypisanie_pracownikow::on_pushButton_zatwierdz_clicked()
{
	/* wpisaæ mo¿na tylko jedna osobe ale niech zostanie for */
	for (QString i : this->currentUsers) {

		string numerPracownik = i.toStdString();
		Fun_projekty::dodaj_przypisanie_do_zadania(seperacja_stringa_od_kropki(numerPracownik), "false");
		if (Dane_zalogowanego_pracownika::instancja()->pobierz_czy_blad())
			QMessageBox::information(this, "Error", QString::fromStdString(Dane_zalogowanego_pracownika::instancja()->pobierz_wyjatek()));
	}

	/*  Zamkniecie okna po zatwierdzeniu zmian 
		TODO	aktualizacja g³ownego okna
	*/
	this->close();

	/*STARA WERSJA METODY*/
	/*
	vector<string> name;
	for (int i = 0; i < currentUsers.length(); i++)
	{
		name = podzial_stringa_na_slowa(ui.listWidget_current->currentItem()->text().toStdString());
		Fun_projekty::dodaj_przypisanie_do_projektu(seperacja_stringa_od_kropki(name[0]), "false");
		if (Dane_zalogowanego_pracownika::instancja()->pobierz_czy_blad())
			QMessageBox::information(this, "Error", QString::fromStdString(Dane_zalogowanego_pracownika::instancja()->pobierz_wyjatek()));
		name.clear();
	}
	*/
}
void Przypisanie_pracownikow::on_pushButton_anuluj_clicked()
{
	this->close();
}
void Przypisanie_pracownikow::on_pushButton_dodaj_clicked()
{
	if (this->systemUser != nullptr)
	{
		currentUsers << this->systemUser->text();
		odswiezListy(true);
		this->systemUser = nullptr;
	}
}
void Przypisanie_pracownikow::on_pushButton_usun_clicked()
{
	if (this->taskUser != nullptr)
	{
		systemUsers << this->taskUser->text();
		odswiezListy(false);
		this->taskUser = nullptr;
	}
}
void Przypisanie_pracownikow::on_listWidget_all_itemClicked(QListWidgetItem* item)
{
	this->systemUser = item;
}
void Przypisanie_pracownikow::on_listWidget_current_itemClicked(QListWidgetItem* item)
{
	this->taskUser = item;
}
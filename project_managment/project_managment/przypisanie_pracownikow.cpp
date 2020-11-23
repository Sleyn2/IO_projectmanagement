#include "przypisanie_pracownikow.h"

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
	if (this->if_id)
	{
		currentUsers = Fun_projekty::pobierz_liste_pracownikow_w_projekcie(std::to_string(this->id));
		for (int i = 0; i < currentUsers.length(); i++)
		{
			systemUsers.removeAll(currentUsers[i]);
		}
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
}
void Przypisanie_pracownikow::on_pushButton_zatwierdz_clicked()
{
	for (int i = 0; i < currentUsers.length(); i++)
	{
		//Fun_projekty::dodaj_przypisanie_do_projektu()
	}
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
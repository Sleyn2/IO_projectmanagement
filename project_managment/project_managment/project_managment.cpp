#include "project_managment.h"
#include <QList>
#include <QLineEdit>
#include <QListWidgetItem>
#include <Qstring>
#include <qmessagebox.h>
#include "klasy.h"

project_managment::project_managment(QWidget *parent)
    : QWidget(parent)
{
    ui.setupUi(this);
    ui.Opcje_projektu->setCurrentIndex(2);
}
// Zmiana miêdzy widokami w StackedWidget
void project_managment::on_pushButton_1_clicked()
{
    ui.stackedWidget->setCurrentIndex(0);
}

void project_managment::on_pushButton_2_clicked()
{
    ui.stackedWidget->setCurrentIndex(1);
}

void project_managment::on_pushButton_3_clicked()
{
    ui.stackedWidget->setCurrentIndex(2);
}

void project_managment::on_pushButton_utworzProjekt_clicked()
{
    this->tworzenie_zadan_projektow->ustaw_tryb(true);
    this->tworzenie_zadan_projektow->show();
}

void project_managment::on_pushButton_utworzZadanie_clicked()
{
    this->tworzenie_zadan_projektow->ustaw_tryb(false);
    this->tworzenie_zadan_projektow->show();
}

void project_managment::odswiezProjekty()
{
    availableProjectList = Fun_projekty::pobierz_liste_projektow();
    ui.ProjectList->addItems(availableProjectList);
}

void project_managment::odswiezZadania()
{
    availableTaskList = Fun_projekty::pobierz_liste_zadan();
    ui.listWidget_zadania->addItems(availableTaskList);
}

//Wyszukiwanie przy zmianie tekstu 
void project_managment::on_lineEdit_search_textChanged(const QString& arg1)
{
    QRegExp regExp(arg1, Qt::CaseInsensitive, QRegExp::Wildcard);
    ui.ProjectList->clear();
    ui.ProjectList->addItems(availableProjectList.filter(regExp));
}

void project_managment::onlineEdit_search_task_textChanged(const QString& arg1)
{
    QRegExp regExp(arg1, Qt::CaseInsensitive, QRegExp::Wildcard);
    ui.listWidget_zadania->clear();    
    ui.listWidget_zadania->addItems(availableTaskList.filter(regExp));
}

void project_managment::ustaw_user()
{
    string nazwa = Dane_zalogowanego_pracownika::instancja()->pobierz_nazwe_projektu();
    ui.Opcje_projektu->setCurrentIndex(0);
    ui.textBrowserOpisProjektu_1->setText(Fun_projekty::pobierz_opis_projektu(Dane_zalogowanego_pracownika::instancja()->pobierz_nazwe_projektu()));
    QString nazwaQT = QString::fromStdString(nazwa);
    ui.label_4->setText(nazwaQT);
}

void project_managment::ustaw_admin()
{
    string nazwa = Dane_zalogowanego_pracownika::instancja()->pobierz_nazwe_projektu();
    ui.Opcje_projektu->setCurrentIndex(1);
    ui.textBrowserOpisProjektu_2->setText(Fun_projekty::pobierz_opis_projektu(nazwa));
    QString nazwaQT = QString::fromStdString(nazwa);
    ui.label_6->setText(nazwaQT);
}

void project_managment::on_ProjectList_itemClicked(QListWidgetItem* item)
{
    QString nazwa = item->text();
    Dane_zalogowanego_pracownika::instancja()->ustaw_nazwe_projektu(nazwa.toStdString());

    if (Fun_projekty::czy_kierownik())
    {
        ustaw_admin();
    }
    else
    {
        ustaw_user();
    }
    this->odswiezZadania();
}

void project_managment::ustaw_okno_tworzenia(Projekty_zadania_okno* temp)
{
    this->tworzenie_zadan_projektow = temp;
}

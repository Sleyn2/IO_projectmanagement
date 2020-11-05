#include "project_managment.h"
#include <QList>
#include <QLineEdit>
#include <QListWidgetItem>
#include <qmessagebox.h>
#include "klasy.h"

project_managment::project_managment(QWidget *parent)
    : QWidget(parent)
{
    ui.setupUi(this);


    //TO DO
    //Do poni�szej funkcji nale�y przekaza� nazw� wybranego projektu w wyszukiwarce
    ui.textBrowserOpisProjektu->setText(Fun_projekty::pobierz_opis_projektu("Alarm z czujnikiem ruchu"));
}
// Zmiana mi�dzy widokami w StackedWidget
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
//Wyszukiwarka w ekranie projekt�w
void project_managment::search_for_string(QString search_str)
{ 
    QList<QListWidgetItem*> my_found_items;

    for (int i = 0; i < ui.ProjectList->count(); i++)
    {
        QListWidgetItem* current = ui.ProjectList->item(i);
        if (current->text().contains(search_str))
        {
            my_found_items.append(current);
        }
    }
}

void project_managment::odswiez()
{
    availableProjectList = Fun_projekty::pobierz_liste_projektow();
    ui.ProjectList->addItems(availableProjectList);
}

//Wyszukiwanie przy zmianie tekstu 
//Skonfigurowane do wczytywania i filtrowania listy folder�w z lini 13 
void project_managment::on_lineEdit_search_textChanged(const QString& arg1)
{
    QRegExp regExp(arg1, Qt::CaseInsensitive, QRegExp::Wildcard);
    ui.ProjectList->clear();
    ui.ProjectList->addItems(availableProjectList.filter(regExp));
}

void project_managment::on_ProjectList_ItemClicked(QListWidgetItem* item)
{
    for (int i = 0; i < ui.ProjectList->count(); i++)
    {
        if (ui.ProjectList->item(i) == item)
        {
            QMessageBox::information(this, "Login", "item nr: " + i);
        }
    }

}
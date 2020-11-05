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
//Wyszukiwarka w ekranie projektów
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
//Skonfigurowane do wczytywania i filtrowania listy folderów z lini 13 
void project_managment::on_lineEdit_search_textChanged(const QString& arg1)
{
    QRegExp regExp(arg1, Qt::CaseInsensitive, QRegExp::Wildcard);
    ui.ProjectList->clear();
    ui.ProjectList->addItems(availableProjectList.filter(regExp));
}

void project_managment::on_ProjectList_itemClicked(QListWidgetItem* item)
{
    QString nazwa = item->text();

    if (true)
    {
    }
    ui.textBrowserOpisProjektu_2->setText(Fun_projekty::pobierz_opis_projektu(nazwa.toStdString()));
    ui.Opcje_projektu->setCurrentIndex(1);
    ui.label_6->setText(nazwa);
}
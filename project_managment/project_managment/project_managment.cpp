#include "project_managment.h"
#include <QList>
#include <QLineEdit>
#include <QListWidgetItem>
#include <qmessagebox.h>


project_managment::project_managment(QWidget *parent)
    : QWidget(parent)
{
    ui.setupUi(this);
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
//Wyszukiwanie przy zmianie tekstu 
// NIE DZIALA - Sleyn
void project_managment::lineEdit_search_returnPressed()
{
    search_for_string(ui.lineEdit_search->text());
    QMessageBox::information(this, "Login", "correct");
}
/*
void project_managment::on_pushButton_search_clicked()
{
    QMessageBox::information(this, "Login", "correct");
    search_for_string(ui.lineEdit_search->text());
}
*/
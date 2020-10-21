#include "project_managment.h"

project_managment::project_managment(QWidget *parent)
    : QWidget(parent)
{
    ui.setupUi(this);
}

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


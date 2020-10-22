#pragma once

#include <QtWidgets/QWidget>
#include "ui_project_managment.h"

class project_managment : public QWidget
{
    Q_OBJECT

public:
    project_managment(QWidget *parent = Q_NULLPTR);
private slots:
    void on_pushButton_1_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
    void search_for_string(QString search_str);
    void lineEdit_search_returnPressed();
private:
    Ui::project_managmentClass ui;
};

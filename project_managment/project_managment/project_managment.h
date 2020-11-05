#pragma once

#include <QtWidgets/QWidget>
#include "ui_project_managment.h"
#include <QDir>
#include <QDebug>
#include <QRegExp>

class project_managment : public QWidget
{
    Q_OBJECT

public:
    project_managment(QWidget *parent = Q_NULLPTR);
    void odswiez();
    void ustaw_admin();
    void ustaw_user();
private slots:
    void on_pushButton_1_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
    void search_for_string(QString search_str);
    void on_lineEdit_search_textChanged(const QString &arg1);
    void on_ProjectList_itemClicked(QListWidgetItem* item);
private:
    Ui::project_managmentClass ui;
    QStringList availableProjectList;
};

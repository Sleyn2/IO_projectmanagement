#pragma once

#include <QtWidgets/QWidget>
#include "ui_project_managment.h"
#include <QDir>
#include <QDebug>
#include <QRegExp>
#include "projekty_zadania_okno.h"
#include "edycja_zadanie_okno.h"

class project_managment : public QWidget
{
    Q_OBJECT

public:
    project_managment(QWidget *parent = Q_NULLPTR);
    void odswiezProjekty();
    void odswiezZadania();
    void ustaw_admin();
    void ustaw_user();
    void ustaw_okno_tworzenia(Projekty_zadania_okno* temp);
    void ustaw_okno_edycji(edycja_zadanie_okno* temp);

private slots:
    void on_pushButton_1_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_edytuj_zadanie_clicked();
    void on_pushButton_utworzProjekt_clicked();
    void on_pushButton_utworz_zadanie_clicked();
    void on_lineEdit_search_textChanged(const QString &arg1);
    void onlineEdit_search_task_textChanged(const QString& arg1);
    void on_ProjectList_itemClicked(QListWidgetItem* item);
    void on_listWidget_zadania_itemClicked(QListWidgetItem* item);

private:
    Ui::project_managmentClass ui;
    Projekty_zadania_okno* tworzenie_zadan_projektow;
    edycja_zadanie_okno* edytowanie_zadan;
    QStringList availableProjectList;
    QStringList availableTaskList;
};

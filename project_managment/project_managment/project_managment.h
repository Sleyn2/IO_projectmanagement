#pragma once
#include "klasy.h"
#include <QtWidgets/QWidget>
#include "ui_project_managment.h"
#include <QDir>
#include <QDebug>
#include <QRegExp>
#include "projekty_zadania_okno.h"
#include "edycja_zadanie_okno.h"
#include "wiadomosci_okno.h"

class project_managment : public QWidget
{
    Q_OBJECT

public:
    project_managment(QWidget *parent = Q_NULLPTR);
    void odswiezProjekty();
    void ustaw_admin();
    void ustaw_user();
    void ustaw_okna(Projekty_zadania_okno* temp, 
                              edycja_zadanie_okno* temp2, 
                              wiadomosci_okno* temp3);
private slots:
    void on_pushButton_1_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();

    void on_pushButton_ustaw1_clicked();
    void on_pushButton_anuluj_clicked();
    void on_pushButton_zapisz_clicked();
    //Projekty i zadania
    void on_pushButton_edytuj_zadanie_clicked();
    void on_pushButton_utworzProjekt_clicked();
    void on_pushButton_utworz_zadanie_clicked();
    void on_lineEdit_search_textChanged(const QString &arg1);
    void on_lineEdit_search_task_textChanged(const QString& arg1);
    void on_ProjectList_itemClicked(QListWidgetItem* item);
    void on_listWidget_zadania_itemClicked(QListWidgetItem* item);
    //Wiadomosci
    void on_pushButton_odebrane_clicked();
    void on_pushButton_wyslane_clicked();
    void on_pushButton_nowaWiadomosc_clicked();
    void on_pushButton_usunWiadomosc_clicked();
    void on_listWidget_wiadomosci_itemClicked(QListWidgetItem* item);
    void on_listWidget_wiadomosci_itemDoubleClicked(QListWidgetItem* item);
private:
    Ui::project_managmentClass ui;
    Projekty_zadania_okno* tworzenie_zadan_projektow;
    edycja_zadanie_okno* edytowanie_zadan;
    wiadomosci_okno* tworzenie_wiadomosci;
    QStringList availableProjectList, availableTaskList, messageList;
    QString message;
    void odswiezZadania();
    void odswiezWiadomosci();
    bool wyslane;
};

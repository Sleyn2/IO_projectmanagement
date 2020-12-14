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
#include "zmien_haslo_okno.h"
#include "raport_tworz_okno.h"
#include "raport_edycja_okno.h"
#include "dodawanie_pracownikow_okno.h"


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
                              wiadomosci_okno* temp3, zmien_haslo_okno* temp4,
                              raport_tworz_okno* temp5, raport_edycja_okno* temp6, dodawanie_pracownikow_okno* temp7);
private slots:
    void on_pushButton_1_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();

    //Ustawienia
    void on_pushButton_ustaw1_clicked();
    void on_pushButton_anuluj_clicked();
    void on_pushButton_zapisz_clicked();
    void on_pushButton_zapisz_2_clicked();
    void on_pushButton_usun_clicked();
    void on_pushButton_ustaw2_clicked();
    void on_pushButton_dodaj_clicked();
    void on_lineEdit_search_settings_textChanged(const QString& arg1);
    void on_userList_itemClicked(QListWidgetItem* item);
    void on_pushButton_zapisz_prawa_clicked();
    void on_pushButton_dodajDzial_clicked();
    void on_pushButton_usunDzial_clicked();
    void on_pushButton_prosby_clicked();
    void on_pushButton_usunPracownika_clicked();
    
    //Projekty i zadania
    void on_pushButton_edytuj_zadanie_clicked();
    void on_pushButton_utworzProjekt_clicked();
    void on_pushButton_sendMsg2_clicked();
    void on_pushButton_sendMsg_clicked();
    void on_pushButton_utworz_zadanie_clicked();
    void on_lineEdit_search_textChanged(const QString &arg1);
    void on_lineEdit_search_task_textChanged(const QString& arg1);
    void on_ProjectList_itemClicked(QListWidgetItem* item);
    void on_listWidget_zadania_itemClicked(QListWidgetItem* item);
    void on_listWidget_taskUsers_itemClicked(QListWidgetItem* item);
    void on_listWidget_taskUsers2_itemClicked(QListWidgetItem* item);
    void on_pushButtonTworzRaport_clicked();
    void on_pushButtonTworzRaportAdm_clicked();
    void on_listWidgetRaporty_itemDoubleClicked(QListWidgetItem* item);
    void on_pushButton_StworzPodprojekt_clicked();
    void on_comboBox_filtr_currentTextChanged();

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
    zmien_haslo_okno* zmien_haslo;
    raport_tworz_okno* tworzenie_raportu;
    raport_edycja_okno* odbieranie_raportu;
    dodawanie_pracownikow_okno* dodawanie_pracownikow;
    QStringList availableProjectList, availableTaskList, messageList, 
        availableUsersList, teamList;
    vector<Raport> availableReportsVector;
    QString message;
    string wybranyUzytkownik = "";
    void odswiezZadania();
    void odswiezWiadomosci();
    void odswiezUstawienia_przeglad();
    void odswiezUstawienia_edycja();
    void odswiezListeZespolu(bool admin);
    void odswiezUstawienia_admin();
    void odswiezListeUzytkownikow();
    void odswiezListeRaportow();
    void odswiezListeDzialow();
    bool wyslane;
};

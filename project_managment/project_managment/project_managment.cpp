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
    Dane_zalogowanego_pracownika::instancja()->ustaw_nazwe_zadania("");

    ui.label->setText("Ustawienia");

    

    
}
// Zmiana miêdzy widokami w StackedWidget
void project_managment::on_pushButton_1_clicked()
{
    ui.stackedWidget->setCurrentIndex(0);

    ui.label->setText("Twoje projekty i zadania");
}

void project_managment::on_pushButton_2_clicked()
{
    ui.stackedWidget->setCurrentIndex(1);
    this->wyslane = false;
    this->odswiezWiadomosci();

    ui.label->setText("Wiadomoœci");
}

void project_managment::on_pushButton_3_clicked()
{
    this->odswiezUstawienia_przeglad();
    this->odswiezUstawienia_admin();

    ui.stackedWidget->setCurrentIndex(2);

} 
// Ustawianie okien do wyœwietlenia
void project_managment::ustaw_okna(Projekty_zadania_okno* temp,
                                             edycja_zadanie_okno* temp2,
                                             wiadomosci_okno* temp3, zmien_haslo_okno* temp4)
{
    this->edytowanie_zadan = temp2;
    this->tworzenie_wiadomosci = temp3;
    this->tworzenie_zadan_projektow = temp;
    this->zmien_haslo = temp4;
}
//ustawienia
void project_managment::odswiezUstawienia_przeglad()
{
    ui.label->setText("Ustawienia");

    string imieNazw = Dane_zalogowanego_pracownika::instancja()->pobierz_imie() + " " + Dane_zalogowanego_pracownika::instancja()->pobierz_nazwisko();
    ui.label_27->setText(QString::fromStdString(imieNazw));

    string id = Dane_zalogowanego_pracownika::instancja()->pobierz_id_pracownika();
    ui.label_29->setText(QString::fromStdString(id));

    string czy_adm = Dane_zalogowanego_pracownika::instancja()->pobierz_czy_administator();

    if (czy_adm == "0")
    {
        ui.label_32->setText("nie");
        ui.label_42->setText("nie");

        ui.groupBox->setEnabled(false);
    }
    else if (czy_adm == "1")
    {
        ui.label_32->setText("tak");
        ui.label_42->setText("nie");

        ui.groupBox->setEnabled(false);
    }
    else
    {
        ui.label_32->setText("tak");
        ui.label_42->setText("tak");

        ui.groupBox->setEnabled(true);
    }



    string login = Dane_zalogowanego_pracownika::instancja()->pobierz_login();
    ui.label_35->setText(QString::fromStdString(login));

    ui.comboBox->clear();

    std::vector<Dzial> dzialy = Dane_zalogowanego_pracownika::instancja()->pobierz_dzialy();

    for (int i = 0; i < dzialy.size(); i++)
    {
        ui.comboBox->addItem(QString::fromStdString(dzialy[i].pobierz_nazwa()));
    }

}

void project_managment::odswiezUstawienia_edycja()
{
    ui.lineEdit_imie->setText(QString::fromStdString(Dane_zalogowanego_pracownika::instancja()->pobierz_imie()));
    ui.lineEdit_nazw->setText(QString::fromStdString(Dane_zalogowanego_pracownika::instancja()->pobierz_nazwisko()));
    ui.lineEdit_login->setText(QString::fromStdString(Dane_zalogowanego_pracownika::instancja()->pobierz_login()));

    std::vector<Dzial> dzialy = Pobieranie_bazy::pobierz_dzial("select * from dzialy_w_firmie");

    ui.comboBox_dzialy->clear();

    for (int i = 0; i < dzialy.size(); i++)
    {
        ui.comboBox_dzialy->addItem(QString::fromStdString(dzialy[i].pobierz_nazwa()));
    }
}

void project_managment::odswiezUstawienia_admin()
{
    Fun_ustawienia::odswiez_zalogowanego();

    if (Dane_zalogowanego_pracownika::instancja()->pobierz_czy_administator() == "2")
    {

        ui.lineEdit_search_settings->setText(QString::fromStdString(""));
        ui.userList->clear();

        this->odswiezListeUzytkownikow();

        ui.groupBox_2->setEnabled(false);

        ui.lineEdit_nazwa_dzialu->clear();
        ui.lineEdit_adres_dzialu->clear();
        ui.label_prawa->clear();
    }

}

void project_managment::on_pushButton_ustaw1_clicked()
{
    this->odswiezUstawienia_edycja();

    ui.stackedWidget_ustawienia->setCurrentIndex(1);
}

void project_managment::on_pushButton_anuluj_clicked()
{
    this->odswiezUstawienia_przeglad();

    ui.stackedWidget_ustawienia->setCurrentIndex(0);
}

void project_managment::on_pushButton_zapisz_clicked()
{
    string id = Dane_zalogowanego_pracownika::instancja()->pobierz_id_pracownika();
    string imie = ui.lineEdit_imie->text().toLocal8Bit().constData();
    string nazw = ui.lineEdit_nazw->text().toLocal8Bit().constData();
    string login = ui.lineEdit_login->text().toLocal8Bit().constData();
    string haslo = Dane_zalogowanego_pracownika::instancja()->pobierz_haslo();
    string adm = Dane_zalogowanego_pracownika::instancja()->pobierz_czy_administator();
    
    if (imie != "" && nazw != "" && login != "")
    {
        if (Fun_ustawienia::edycja_danych_uzytkownika(id, imie, nazw, login, haslo, adm))
        {
            
            this->odswiezUstawienia_przeglad();

            ui.stackedWidget_ustawienia->setCurrentIndex(0);
        }
    }
    else
    {
        QMessageBox msg;
        msg.setWindowTitle(QString::fromStdString("niepoprawne dane"));
        msg.setText(QString::fromStdString("niepoprawne dane"));

        msg.exec();

    }
}

void project_managment::on_pushButton_zapisz_2_clicked()
{
    this->odswiezUstawienia_przeglad();

    ui.stackedWidget_ustawienia->setCurrentIndex(0);
}

void project_managment::on_pushButton_usun_clicked()
{
    string dzial = ui.comboBox_dzialy->currentText().toUtf8().constData();

    if (dzial != "")
    {
        Fun_ustawienia::usun_z_dzialu_po_nazwie(Dane_zalogowanego_pracownika::instancja()->pobierz_id_pracownika(), dzial);
    }
}

void project_managment::on_pushButton_ustaw2_clicked()
{
    this->zmien_haslo->show();
}

void project_managment::on_userList_itemClicked(QListWidgetItem* item)
{
    ui.groupBox_2->setEnabled(true);

    string text = item->text().toUtf8().constData();
    
    string login = Fun_ustawienia::wyluskaj_login(text);

    string czy_adm = Fun_ustawienia::czy_admin_po_loginie(login);

    if (czy_adm == "0")
    {
        ui.checkBox_tworzenie_proj->setChecked(false);
        ui.checkBox_admin->setChecked(false);
    }
    else if (czy_adm == "1")
    {
        ui.checkBox_tworzenie_proj->setChecked(true);
        ui.checkBox_admin->setChecked(false);
    }
    else if (czy_adm == "2")
    {
        ui.checkBox_tworzenie_proj->setChecked(true);
        ui.checkBox_admin->setChecked(true);
    }

    string imie_nazw = Fun_ustawienia::imie_nazwisko_po_loginie(login);

    ui.label_prawa->setText(QString::fromStdString(imie_nazw));
}

void project_managment::on_pushButton_dodaj_clicked()
{
    string dzial = ui.comboBox_dzialy->currentText().toUtf8().constData();

    if (dzial != "")
    {
        Fun_ustawienia::dodaj_do_dzialu_po_nazwie(Dane_zalogowanego_pracownika::instancja()->pobierz_id_pracownika(), dzial);
    }
}

void project_managment::on_pushButton_zapisz_prawa_clicked()
{
    Fun_ustawienia::odswiez_zalogowanego();
    if (Dane_zalogowanego_pracownika::instancja()->pobierz_czy_administator() == "2")
    {

        string uprawnienia = "0";

        if (ui.checkBox_admin->isChecked())
        {
            uprawnienia = "2";
        }
        else if (ui.checkBox_tworzenie_proj->isChecked())
        {
            uprawnienia = "1";
        }


        if (!ui.checkBox_tworzenie_proj->isChecked() && ui.checkBox_admin->isChecked())
        {
            QMessageBox msg;
            msg.setWindowTitle("Blad");
            msg.setText("Administrator musi posiadac prawo do tworzenia projektow.");

            msg.exec();
        }
        else
        {
            string text = ui.userList->currentItem()->text().toUtf8().constData();
            string login = Fun_ustawienia::wyluskaj_login(text);

            Fun_ustawienia::nadawanie_uprawnien(login, uprawnienia);
        }
    }
    else
    {
        QMessageBox msg;
        msg.setWindowTitle(QString::fromStdString("Brak uprawnien"));
        msg.setText(QString::fromStdString("Nie masz uprawnien administratora."));

        msg.exec();
    }


}



void project_managment::on_pushButton_utworzProjekt_clicked()
{
    this->tworzenie_zadan_projektow->ustaw_tryb(true);
    this->tworzenie_zadan_projektow->show();
}

void project_managment::on_pushButton_utworz_zadanie_clicked()
{
    this->tworzenie_zadan_projektow->ustaw_tryb(false);
    this->tworzenie_zadan_projektow->show();
}

void project_managment::on_pushButton_edytuj_zadanie_clicked()
{
    if (Dane_zalogowanego_pracownika::instancja()->pobierz_nazwe_zadania() != "")
    {
        this->edytowanie_zadan->show();
        this->edytowanie_zadan->wczytaj_dane();
    }
}

void project_managment::odswiezProjekty()
{
    ui.ProjectList->clear();
    availableProjectList.clear();
    availableProjectList = Fun_projekty::pobierz_liste_projektow();
    if (Dane_zalogowanego_pracownika::instancja()->pobierz_czy_blad())
        QMessageBox::information(this, "Error", QString::fromStdString(Dane_zalogowanego_pracownika::instancja()->pobierz_wyjatek()));
    else
    {
        availableProjectList.sort();
        ui.ProjectList->addItems(availableProjectList);
    }
}

void project_managment::odswiezZadania()
{
    ui.listWidget_zadania->clear();
    availableTaskList.clear();
    availableTaskList = Fun_projekty::pobierz_liste_zadan();
    if (Dane_zalogowanego_pracownika::instancja()->pobierz_czy_blad())
        QMessageBox::information(this, "Error", QString::fromStdString(Dane_zalogowanego_pracownika::instancja()->pobierz_wyjatek()));
    else
    {
        availableTaskList.sort();
        ui.listWidget_zadania->addItems(availableTaskList);
    }
}

void project_managment::odswiezListeUzytkownikow()
{
    ui.userList->clear();
    availableUsersList.clear();
    availableUsersList = Fun_ustawienia::pobierz_liste_pracownikow();
    if (Dane_zalogowanego_pracownika::instancja()->pobierz_czy_blad())
        QMessageBox::information(this, "Error", QString::fromStdString(Dane_zalogowanego_pracownika::instancja()->pobierz_wyjatek()));
    else
    {
        availableUsersList.sort();
        ui.userList->addItems(availableUsersList);
    }
}

void project_managment::odswiezWiadomosci()
{
    ui.listWidget_wiadomosci->clear();
    messageList.clear();

    messageList = Fun_wiadomosci::pobierz_wiadomosci(this->wyslane);
    if (Dane_zalogowanego_pracownika::instancja()->pobierz_czy_blad())
        QMessageBox::information(this, "Error", QString::fromStdString(Dane_zalogowanego_pracownika::instancja()->pobierz_wyjatek()));
    else
        ui.listWidget_wiadomosci->addItems(messageList);

}

//Wyszukiwanie przy zmianie tekstu 
void project_managment::on_lineEdit_search_textChanged(const QString& arg1)
{
    QRegExp regExp(arg1, Qt::CaseInsensitive, QRegExp::Wildcard);
    ui.ProjectList->clear();
    ui.ProjectList->addItems(availableProjectList.filter(regExp));
}

void project_managment::on_lineEdit_search_task_textChanged(const QString& arg1)
{
    QRegExp regExp(arg1, Qt::CaseInsensitive, QRegExp::Wildcard);
    ui.listWidget_zadania->clear();    
    ui.listWidget_zadania->addItems(availableTaskList.filter(regExp));
}

void project_managment::on_lineEdit_search_settings_textChanged(const QString& arg1)
{
    QRegExp regExp(arg1, Qt::CaseInsensitive, QRegExp::Wildcard);
    ui.userList->clear();
    ui.userList->addItems(availableUsersList.filter(regExp));
}

void project_managment::ustaw_user()
{
    string nazwa = Dane_zalogowanego_pracownika::instancja()->pobierz_nazwe_projektu();
    ui.Opcje_projektu->setCurrentIndex(0);
    QString opis = Fun_projekty::pobierz_opis_projektu(Dane_zalogowanego_pracownika::instancja()->pobierz_nazwe_projektu());
    if (Dane_zalogowanego_pracownika::instancja()->pobierz_czy_blad())
        QMessageBox::information(this, "Error", QString::fromStdString(Dane_zalogowanego_pracownika::instancja()->pobierz_wyjatek()));
    else
    {
        ui.textBrowserOpisProjektu_1->setText(opis);
        QString nazwaQT = QString::fromStdString(nazwa);
        ui.label_4->setText(nazwaQT);
    }
}

void project_managment::ustaw_admin()
{
    string nazwa = Dane_zalogowanego_pracownika::instancja()->pobierz_nazwe_projektu();
    ui.Opcje_projektu->setCurrentIndex(1);
    QString opis = Fun_projekty::pobierz_opis_projektu(nazwa);
    if (Dane_zalogowanego_pracownika::instancja()->pobierz_czy_blad()) 
    QMessageBox::information(this, "Error", QString::fromStdString(Dane_zalogowanego_pracownika::instancja()->pobierz_wyjatek()));
    else
    {
        ui.textBrowserOpisProjektu_2->setText(opis);
        QString nazwaQT = QString::fromStdString(nazwa);
        ui.label_6->setText(nazwaQT);
    }
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
void project_managment::on_listWidget_zadania_itemClicked(QListWidgetItem* item)
{
    QString nazwa = item->text();
    Dane_zalogowanego_pracownika::instancja()->ustaw_nazwe_zadania(nazwa.toStdString());
}

//Wiadomosci

void project_managment::on_pushButton_odebrane_clicked()
{
    this->wyslane = false;
    this->odswiezWiadomosci();
    
}
void project_managment::on_pushButton_wyslane_clicked()
{
    this->wyslane = true;
    this->odswiezWiadomosci();
}
void project_managment::on_pushButton_nowaWiadomosc_clicked()
{
    this->tworzenie_wiadomosci->ustawTryb(0, false);
    this->tworzenie_wiadomosci->show();
}
void project_managment::on_listWidget_wiadomosci_itemClicked(QListWidgetItem* item)
{
    this->message = item->text();
}
void project_managment::on_listWidget_wiadomosci_itemDoubleClicked(QListWidgetItem* item)
{
    this->tworzenie_wiadomosci->ustawWiadomosc(item->text());
    this->tworzenie_wiadomosci->ustawTryb(1, this->wyslane);
    this->tworzenie_wiadomosci->show();
}
void project_managment::on_pushButton_usunWiadomosc_clicked()
{
    istringstream ss(this->message.toStdString());
    string tytul, nadawca, data;
    ss >> tytul >> nadawca >> data;
    //if(this->wyslane)
        // if (Fun_wiadomosci::usun_wiadomosc());
}


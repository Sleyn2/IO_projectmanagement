#include "project_managment.h"
#include <QList>
#include <QLineEdit>
#include <QListWidgetItem>
#include <Qstring>
#include <qmessagebox.h>

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

    this->odswiezProjekty();
}

void project_managment::odswiezListeZespolu(bool admin)
{
    ui.listWidget_taskUsers->clear();
    ui.listWidget_taskUsers2->clear();
    teamList.clear();
    teamList = Fun_projekty::pobierz_liste_pracownikow_w_projekcie();
    teamList.sort();
    if (Dane_zalogowanego_pracownika::instancja()->pobierz_czy_blad())
        QMessageBox::information(this, "Error", QString::fromStdString(Dane_zalogowanego_pracownika::instancja()->pobierz_wyjatek()));
    else
    {
        if (admin)
            ui.listWidget_taskUsers->addItems(teamList);
        else
            ui.listWidget_taskUsers2->addItems(teamList);
    }
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
                                             wiadomosci_okno* temp3, zmien_haslo_okno* temp4,
                                             raport_tworz_okno* temp5, raport_edycja_okno* temp6, dodawanie_pracownikow_okno* temp7)
{
    this->edytowanie_zadan = temp2;
    this->tworzenie_wiadomosci = temp3;
    this->tworzenie_zadan_projektow = temp;
    this->zmien_haslo = temp4;
    this->tworzenie_raportu = temp5;
    this->odbieranie_raportu = temp6;
    this->dodawanie_pracownikow = temp7;
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

    std::vector<QString> dzialy = Dane_zalogowanego_pracownika::instancja()->pobierz_dzialy();

    for (int i = 0; i < dzialy.size(); i++)
    {
        ui.comboBox->addItem(dzialy[i]);
    }

}

void project_managment::odswiezUstawienia_edycja()
{
    ui.lineEdit_imie->setText(QString::fromStdString(Dane_zalogowanego_pracownika::instancja()->pobierz_imie()));
    ui.lineEdit_nazw->setText(QString::fromStdString(Dane_zalogowanego_pracownika::instancja()->pobierz_nazwisko()));
    ui.lineEdit_login->setText(QString::fromStdString(Dane_zalogowanego_pracownika::instancja()->pobierz_login()));

    std::vector<QString> dzialy = Fun_ustawienia::pobierz_liste_dzialow();

    ui.comboBox_dzialy->clear();

    for (int i = 0; i < dzialy.size(); i++)
    {
        ui.comboBox_dzialy->addItem(dzialy[i]);
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

        ui.comboBox_usunDzial->clear();

        std::vector<QString> dzialy = Fun_ustawienia::pobierz_liste_dzialow();

        for (int i = 0; i < dzialy.size(); i++)
        {
            ui.comboBox_usunDzial->addItem(dzialy[i]);
        }
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

    string imie_nazw;
    vector<string> imie_i_nazw = Fun_ustawienia::imie_nazwisko_po_loginie(login, "pracownicy");
    if (imie_i_nazw.size() == 2)
    {
        imie_nazw = imie_i_nazw[0] + imie_i_nazw[1];
    }

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

void project_managment::on_pushButton_dodajDzial_clicked()
{
    if (Dane_zalogowanego_pracownika::instancja()->pobierz_czy_administator() == "2")
    {
        string nazwa = ui.lineEdit_nazwa_dzialu->text().toUtf8().constData();
        string adres = ui.lineEdit_adres_dzialu->text().toUtf8().constData();

        bool good = Fun_ustawienia::dodaj_dzial(adres, nazwa);

        if (!good)
        {
            QMessageBox msg;
            msg.setWindowTitle("Blad");
            msg.setText("Wystapil blad. Nie dodano dzialu.");
            msg.exec();
        }

        odswiezListeDzialow();
    }
    else
    {
        QMessageBox msg;
        msg.setWindowTitle("Blad");
        msg.setText("Nie masz uprawnien administratora.");
        msg.exec();
    }
}

void project_managment::on_pushButton_usunDzial_clicked()
{
    if (Dane_zalogowanego_pracownika::instancja()->pobierz_czy_administator() == "2")
    {
        QString dzial_nazwa = ui.comboBox_usunDzial->currentText();

        if (!Fun_ustawienia::usun_dzial(dzial_nazwa.toUtf8().constData()))
        {
            QMessageBox msg;
            msg.setWindowTitle("Blad");
            msg.setText("Wystapil blad. Nie usunieto dzialu.");
            msg.exec();
        }

        odswiezListeDzialow();
        odswiezUstawienia_przeglad();
    }
    else
    {
        QMessageBox msg;
        msg.setWindowTitle("Blad");
        msg.setText("Nie masz uprawnien administratora.");
        msg.exec();
    }
    
    
}


void project_managment::odswiezListeDzialow()
{
    ui.comboBox_usunDzial->clear();

    std::vector<QString> dzialy = Fun_ustawienia::pobierz_liste_dzialow();

    for (int i = 0; i < dzialy.size(); i++)
    {
        ui.comboBox_usunDzial->addItem(dzialy[i]);
    }
}

void project_managment::on_pushButton_prosby_clicked()
{
    if (Dane_zalogowanego_pracownika::instancja()->pobierz_czy_administator() == "2")
    {
        this->dodawanie_pracownikow->odswiezProsby();
        this->dodawanie_pracownikow->show();
    }
    else
    {
        QMessageBox msg;
        msg.setWindowTitle("Blad");
        msg.setText("Nie masz uprawnien administratora.");
        msg.exec();
    }
    
}

void project_managment::on_pushButton_usunPracownika_clicked()
{
    string currentText = ui.userList->currentItem()->text().toUtf8().constData();
    string login = Fun_ustawienia::wyluskaj_login(currentText);
    QMessageBox msg;

    if (Dane_zalogowanego_pracownika::instancja()->pobierz_czy_administator() == "2" && login != Dane_zalogowanego_pracownika::instancja()->pobierz_login())
    {
        if (Fun_ustawienia::usun_pracownika(login))
        {
            msg.setWindowTitle("Sukces");
            msg.setText("Pomyslnie usunieto pracownika z bazy.");
            msg.exec();
            odswiezUstawienia_admin();
        }
        else
        {
            msg.setWindowTitle("Blad");
            msg.setText("Wystapil blad. Nie usunieto pracownika.");
            msg.exec();
        }
    }
    else
    {
        msg.setWindowTitle("Blad");
        msg.setText("Wystapil blad. Probujesz usunac siebie lub nie masz praw administratora.");
        msg.exec();
    }

    
}

//Projekty
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
        this->edytowanie_zadan->odswiezWykonawcow();
        this->edytowanie_zadan->show();
        this->edytowanie_zadan->wczytaj_dane();
    }

}

void project_managment::on_pushButton_sendMsg2_clicked()
{
    if (wybranyUzytkownik == "")
        return;
    else
    {
        this->tworzenie_wiadomosci->ustawTryb(0, false);
        this->tworzenie_wiadomosci->findMatch(this->wybranyUzytkownik);
        this->tworzenie_wiadomosci->show();

    }
}

void project_managment::on_pushButton_sendMsg_clicked()
{
    if (wybranyUzytkownik == "")
        return;
    else
    {
        this->tworzenie_wiadomosci->ustawTryb(0, false);
        this->tworzenie_wiadomosci->findMatch(this->wybranyUzytkownik);
        this->tworzenie_wiadomosci->show();
        
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
        for (QString i : availableProjectList) {
            ui.ProjectList->addItem(i);
            stringstream s(i.toStdString());
            string idProj;
            s >> idProj;
            /* dostosowanie wygladu listy <-------------------------------------------------------------------------------------------------------------------------------------------- */
            if (Fun_projekty::czy_Zadanie(idProj)) {
                ui.ProjectList->item(ui.ProjectList->count()-1)->setBackgroundColor(QColor(0xC8C1E5));
            }
            else {
                ui.ProjectList->item(ui.ProjectList->count() - 1)->setBackgroundColor(QColor(0xC0D4F3));
            }
        }
        availableProjectList.sort();
    }

    if (Dane_zalogowanego_pracownika::instancja()->pobierz_czy_administator() == "0")
    {
        ui.pushButton_utworzProjekt->setDisabled(true);
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
        odbieranie_raportu->ustawVectorRaportow(&availableReportsVector);
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

void project_managment::odswiezListeRaportow()
{
    ui.listWidgetRaporty->clear();
    availableReportsVector.clear();
    availableReportsVector = Pobieranie_bazy::pobierz_raporty();
    std::sort(availableReportsVector.begin(), availableReportsVector.end());

    QStringList raporty = Fun_raport::vectorRaportowNaQStringList(availableReportsVector);

    if (Dane_zalogowanego_pracownika::instancja()->pobierz_czy_blad())
        QMessageBox::information(this, "Error", QString::fromStdString(Dane_zalogowanego_pracownika::instancja()->pobierz_wyjatek()));
    else {
        std::sort(availableReportsVector.begin(), availableReportsVector.end());
        odbieranie_raportu->ustawVectorRaportow(&availableReportsVector);
        QStringList raporty = Fun_raport::vectorRaportowNaQStringList(availableReportsVector);
        ui.listWidgetRaporty->addItems(raporty);
    }
   }

void project_managment::odswiezWiadomosci()
{
    ui.listWidget_wiadomosci->clear();
    messageList.clear();
    auto data = Fun_wiadomosci::pobierz_wiadomosci(this->wyslane);
    messageList = std::get<0>(data);
    vector<int> typy = std::get<1>(data);
    if (Dane_zalogowanego_pracownika::instancja()->pobierz_czy_blad())
        QMessageBox::information(this, "Error", QString::fromStdString(Dane_zalogowanego_pracownika::instancja()->pobierz_wyjatek()));
    else
    {   
        /*
        QStringList date, person, title;
        vector<string> temp;
        string singleDate, singlePerson, singleTitle;
        int n;
        for (int i = 0; i < messageList.size(); i++)
        {
            temp = podzial_stringa_na_slowa(messageList[i].toStdString());
            n = temp.size();
            singleDate = messageList[n - 5].toStdString() + " " + 
                messageList[n - 4].toStdString() + " " +
                messageList[n - 3].toStdString() + " " + 
                messageList[n - 2].toStdString() + " " + 
                messageList[n - 1].toStdString();
            singlePerson = messageList[n - 8].toStdString() + " " +
                messageList[n - 7].toStdString() + " " +
                messageList[n - 6].toStdString();
            for (int j = 0; j < n - 7; j++) { singleTitle += messageList[j].toStdString() + " "; }
            if (singleTitle.size() > 30)
                singleTitle = singleTitle.substr(0, 29);
            else
            {
                for (int x = 0; x < 31; x++)
                {
                    char* var;
                    var = singleTitle.c_str();
                }
            }
        }
        */
        ui.listWidget_wiadomosci->addItems(messageList);
        for (auto iter = typy.begin(); iter < typy.end(); iter++) {
            if (*iter == 1)
                ui.listWidget_wiadomosci->item(iter - typy.begin())->setBackgroundColor(REPORT_ACCEPTED_QCOLOUR);
            else if (*iter == 2)
                ui.listWidget_wiadomosci->item(iter - typy.begin())->setBackgroundColor(REPORT_RETURNED_QCOLOUR);
        }
    }
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
    QString opis = Fun_projekty::pobierz_opis_projektu();
    QString opisNadrzedneg = Fun_projekty::pobierz_opis_projektu_nadrzednego();
    if (Dane_zalogowanego_pracownika::instancja()->pobierz_czy_blad())
        QMessageBox::information(this, "Error", QString::fromStdString(Dane_zalogowanego_pracownika::instancja()->pobierz_wyjatek()));
    else
    {
        ui.textBrowserOpisProjektu_1->setText(opisNadrzedneg);
        ui.textBrowser_2->setText(opis);
        QString nazwaQT = QString::fromStdString(nazwa);
        ui.label_4->setText(nazwaQT);
    }
}

void project_managment::ustaw_admin()
{
    ui.Opcje_projektu->setCurrentIndex(1);
    QString opis = Fun_projekty::pobierz_opis_projektu();
    if (Dane_zalogowanego_pracownika::instancja()->pobierz_czy_blad()) 
    QMessageBox::information(this, "Error", QString::fromStdString(Dane_zalogowanego_pracownika::instancja()->pobierz_wyjatek()));
    else
    {
        ui.textBrowserOpisProjektu_2->setText(opis);
        QString nazwaQT = QString::fromStdString(Dane_zalogowanego_pracownika::instancja()->pobierz_nazwe_projektu());
        ui.label_6->setText(nazwaQT);
    }
}

void project_managment::on_ProjectList_itemClicked(QListWidgetItem* item)
{
    QString nazwa = item->text();
    int n = nazwa.toStdString().find(" ", 0);
    string temp = nazwa.toStdString();
    string id = temp.substr(0, n);
    string text = temp.substr(n + 1, nazwa.size());

    Dane_zalogowanego_pracownika::instancja()->ustaw_nazwe_projektu(text);
    Dane_zalogowanego_pracownika::instancja()->ustaw_id_projektu(id);


    /* czy zadanie czy projekt */


    if (!Fun_projekty::czy_Zadanie(Dane_zalogowanego_pracownika::instancja()->pobierz_id_projektu()))
    {
        ustaw_admin();
        this->odswiezListeZespolu(true);
        this->odswiezListeRaportow();
        if (Fun_raport::sprawdzCzyJestKorzeniem())
            ui.pushButtonTworzRaportAdm->hide();
        else
            ui.pushButtonTworzRaportAdm->show();
    }
    else
    {
        ustaw_user();

        this->odswiezListeZespolu(false);
        if (Fun_raport::sprawdzCzyJestKorzeniem());
    }
    this->odswiezZadania();
    this->wybranyUzytkownik = "";
}
void project_managment::on_listWidget_zadania_itemClicked(QListWidgetItem* item)
{
    QString nazwa = item->text();

    int n = nazwa.toStdString().find(" ", 0);
    string temp = nazwa.toStdString();
    string id = temp.substr(0, n);
    string text = temp.substr(n + 1, nazwa.size());

    Dane_zalogowanego_pracownika::instancja()->ustaw_nazwe_zadania(text);
    Dane_zalogowanego_pracownika::instancja()->ustaw_id_zadania(id);
}

void project_managment::on_listWidget_taskUsers_itemClicked(QListWidgetItem* item)
{
    this->wybranyUzytkownik = item->text().toStdString();
}

void project_managment::on_listWidget_taskUsers2_itemClicked(QListWidgetItem* item)
{

    this->wybranyUzytkownik = item->text().toStdString();
}

void project_managment::on_pushButtonTworzRaport_clicked()
{
    if (Dane_zalogowanego_pracownika::instancja()->pobierz_id_projektu() == "")
        return;
    vector<Raport> raport = Fun_raport::sprawdzRaport();
    if(raport.size() == 0 || raport[0].pobierz_status() == "zwrocony")
        tworzenie_raportu->ustawNapiszRaport();
    else
        tworzenie_raportu->ustawWyswietlRaport(raport[0]);
        
    this->tworzenie_raportu->show();
}

void project_managment::on_listWidgetRaporty_itemDoubleClicked(QListWidgetItem* item)
{
    odbieranie_raportu->ustawPierwszaStrone();
    odbieranie_raportu->ustawIndex(ui.listWidgetRaporty->currentRow());
    odbieranie_raportu->wczytajDane();
    odbieranie_raportu->show();
}

void project_managment::on_pushButtonTworzRaportAdm_clicked()
{
    /*
        zakonczenie projektu   
        wys³anie wiadmosæci do wszystkich o zakoñczeniu projektu
    */
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
    vector<string> msg = podzial_stringa_na_slowa(message.toStdString());
    string date = "";
    for (int i = (msg.size() - 5); i < msg.size(); i++)
    {
        if (i == (msg.size() - 5))
            date += msg[i];
        else
            date += " " + msg[i];
    }

    if (this->wyslane)
    {
        if (Fun_wiadomosci::usun_wiadomosc(seperacja_stringa_od_kropki(msg[msg.size() - 8]), date, this->wyslane))
        { }
        else
            QMessageBox::information(this, "Error", QString::fromStdString(Dane_zalogowanego_pracownika::instancja()->pobierz_wyjatek()));
    }
    else
    {
        if (Fun_wiadomosci::usun_wiadomosc(seperacja_stringa_od_kropki(msg[msg.size() - 8]), date, this->wyslane))
        { }
        else
            QMessageBox::information(this, "Error", QString::fromStdString(Dane_zalogowanego_pracownika::instancja()->pobierz_wyjatek()));
    }
    this->odswiezWiadomosci();
}


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
// Zmiana między widokami w StackedWidget
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

    ui.label->setText("Wiadomości");
}

void project_managment::on_pushButton_3_clicked()
{
    ui.stackedWidget->setCurrentIndex(2);
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
    }
    else if (czy_adm == "1")
    {
        ui.label_32->setText("tak");
        ui.label_42->setText("nie");
    }
    else
    {
        ui.label_32->setText("tak");
        ui.label_42->setText("tak");
    }



    string login = Dane_zalogowanego_pracownika::instancja()->pobierz_login();
    ui.label_35->setText(QString::fromStdString(login));

    std::vector<Dzial> dzialy = Dane_zalogowanego_pracownika::instancja()->pobierz_dzialy();

    for (int i = 0; i < dzialy.size(); i++)
    {
        ui.comboBox->addItem(QString::fromStdString(dzialy[i].pobierz_nazwa()));
    }

    dzialy.clear();

    dzialy = Pobieranie_bazy::pobierz_dzial("select * from dzialy_w_firmie;");

    for (int i = 0; i < dzialy.size(); i++)
    {
        ui.comboBox_dzialy->addItem(QString::fromStdString(dzialy[i].pobierz_nazwa()));
    }

} 
// Ustawianie okien do wyświetlenia
void project_managment::ustaw_okna(Projekty_zadania_okno* temp,
                                             edycja_zadanie_okno* temp2,
                                             wiadomosci_okno* temp3, zmien_haslo_okno* temp4)
{
    this->edytowanie_zadan = temp2;
    this->tworzenie_wiadomosci = temp3;
    this->tworzenie_zadan_projektow = temp;
    this->zmien_haslo = temp4;
}
void project_managment::on_pushButton_ustaw1_clicked()
{
    ui.stackedWidget_ustawienia->setCurrentIndex(1);
}

void project_managment::on_pushButton_anuluj_clicked()
{
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
    
    
    Fun_ustawienia::edycja_danych_uzytkownika(id, imie, nazw, login, haslo, adm);

    ui.label_27->setText(QString::fromStdString(imie + " " + nazw));

    ui.label_35->setText(QString::fromStdString(login));

    ui.stackedWidget_ustawienia->setCurrentIndex(0);
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

void project_managment::on_pushButton_ustaw2_clicked()
{
    this->zmien_haslo->show();
}
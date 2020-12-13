#include "edycja_zadanie_okno.h"

edycja_zadanie_okno::edycja_zadanie_okno(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
}



void edycja_zadanie_okno::odswiezWykonawcow()
{
	/* wypisywanie pracownikow w comboboxie*/
	ui.comboBox_Wykonawcy->clear();
	for (QString i : Fun_ustawienia::pobierz_liste_pracownikow()) {
		ui.comboBox_Wykonawcy->addItem(i);
	}

	/* ustawienie w comboboxie jako wybrany element bierz¹cego pracownika zajmuj¹cego siê zadaniem */
	vector<Przypisanie_do_projektow> przyps = Pobieranie_bazy::pobierz_Przypisanie_do_projektow("select * from przypisanie_do_projektow where id_projektu = " +
		Dane_zalogowanego_pracownika::instancja()->pobierz_id_zadania() +
		";");
	vector<Pracownik> prac;
	string element;
	if (przyps.empty()) {

	}
	else {
		prac = Pobieranie_bazy::pobierz_pracownik("select * from pracownicy where id_pracownika = " +
			przyps[0].pobierz_id_pracownika() +
			";");
		element = prac.begin()->pobierz_imie() + " " + prac.begin()->pobierz_nazwisko() + " (" + prac.begin()->pobierz_login() + ")";
		ui.comboBox_Wykonawcy->setCurrentText(QString::fromStdString(element));
	}	
}

edycja_zadanie_okno::~edycja_zadanie_okno()
{
}

void edycja_zadanie_okno::wczytaj_dane()
{
	QString nazwa = QString::fromStdString(Dane_zalogowanego_pracownika::instancja()->pobierz_nazwe_zadania());
	QString	data_roz = QString::fromStdString(Fun_projekty::pobierz_dane_zadania().pobierz_data_rozpoczecia());
	QString	data_zak = QString::fromStdString(Fun_projekty::pobierz_dane_zadania().pobierz_data_zakonczenia());
	QString	status = QString::fromStdString(Fun_projekty::pobierz_dane_zadania().pobierz_status());
	QString	opis = QString::fromStdString(Fun_projekty::pobierz_dane_zadania().pobierz_opis());

	ui.textEdit_opis->setText(opis);
	ui.lineEdit_nazwa->setText(nazwa);
	//TODO naprawic import daty
	ui.dateEdit_start->setDate(QDate::fromString(data_roz, "yyy-MM-dd"));
	ui.dateEdit_finish->setDate(QDate::fromString(data_zak, "yyy-MM-dd"));
	if (status == "Rozpoczety")
		ui.comboBox_status->setCurrentIndex(0);
	else if (status == "Zawieszony")
		ui.comboBox_status->setCurrentIndex(1);
	else if (status == "Zamkniêty")
		ui.comboBox_status->setCurrentIndex(2);
}

void edycja_zadanie_okno::on_pushButton_users_clicked()
{
	this->dodaj_nowych_uzytkownikow.wczytajUzytkownikow();
	this->dodaj_nowych_uzytkownikow.show();
}

void edycja_zadanie_okno::on_pushButton_anuluj_clicked()
{
	this->close();
}

void edycja_zadanie_okno::on_pushButton_potwierdz_clicked()
{
	QString nazwa = ui.lineEdit_nazwa->text();
	QString status = ui.comboBox_status->currentText();
	QString start_date = ui.dateEdit_start->text();
	QString finish_date = ui.dateEdit_finish->text();
	QString opis = ui.textEdit_opis->toPlainText();
	
	Fun_projekty::zaktualizuj_zadanie(nazwa.toStdString(), opis.toStdString(), start_date.toStdString(), finish_date.toStdString(), status.toStdString());

	string login = Fun_ustawienia::wyluskaj_login(ui.comboBox_Wykonawcy->currentText().toStdString());

	vector<Pracownik> pracownik = Pobieranie_bazy::pobierz_pracownik("select * from pracownicy where login = '" + login + "';");

	Fun_projekty::dodaj_przypisanie_do_zadania(pracownik.begin()->pobierz_id_pracownika(), "false");

	this->close();
}

void edycja_zadanie_okno::on_pushButton_usun_clicked()
{
	//Fun_projekty::usun_zadanie();
}

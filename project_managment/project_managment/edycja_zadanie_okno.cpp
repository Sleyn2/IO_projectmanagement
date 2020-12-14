#include "edycja_zadanie_okno.h"
#include <qmessagebox.h>

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

	ui.comboBox_Wykonawcy->setCurrentText(Fun_projekty::pobierz_aktualnego_pracownika());
	ui.checkBox_kierownik->setChecked(Fun_projekty::pobierz_zadanie_w_podprojekt());

}

edycja_zadanie_okno::~edycja_zadanie_okno()
{
}

void edycja_zadanie_okno::wczytaj_dane()
{
	QString nazwa = QString::fromStdString(Dane_zalogowanego_pracownika::instancja()->pobierz_nazwe_zadania());
	
	if (!Fun_projekty::pobierz_dane_zadania().pobierz_nazwa().empty())
	{
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


	
}

void edycja_zadanie_okno::on_pushButton_users_clicked()
{
	this->dodaj_nowych_uzytkownikow.wczytajUzytkownikow();
	this->dodaj_nowych_uzytkownikow.show();
}

void edycja_zadanie_okno::on_pushButton_anuluj_clicked()
{
	Dane_zalogowanego_pracownika::instancja()->ustaw_id_zadania("");
	this->close();
}

void edycja_zadanie_okno::on_pushButton_potwierdz_clicked()
{
	QString nazwa = ui.lineEdit_nazwa->text();
	QString status = ui.comboBox_status->currentText();
	QString start_date = ui.dateEdit_start->text();
	QString finish_date = ui.dateEdit_finish->text();
	QString opis = ui.textEdit_opis->toPlainText();
	

	if (Fun_projekty::zaktualizuj_zadanie(nazwa.toStdString(), opis.toStdString(), start_date.toStdString(), finish_date.toStdString(), status.toStdString()))
	{
		// udalo sie 
		QMessageBox msg;
		msg.setWindowTitle("Sukces");
		msg.setText("Zatwierdzono.");
		msg.exec();
	}
	else
	{
		//nie udalo sie
		QMessageBox msg;
		msg.setWindowTitle("Blad");
		msg.setText("Wystapil blad. Nie udalo sie zatwierdzic zmian.");
		msg.exec();
	}

	string login = Fun_ustawienia::wyluskaj_login(ui.comboBox_Wykonawcy->currentText().toStdString());

	Fun_projekty::dodaj_przypisanie_do_zadania_login(login, ui.checkBox_kierownik->isChecked() ? "true" : "false");

	Dane_zalogowanego_pracownika::instancja()->ustaw_id_zadania("");
	this->close();
}

void edycja_zadanie_okno::on_pushButton_usun_clicked()
{
	//usuwanie zadania i jego przypisania
	if (Fun_projekty::usun_zadanie() && Fun_projekty::usun_przypisanie_do_zadania())
		QMessageBox::information(this, "Usuwanie zadania", "Usunieto zadanie");
	else QMessageBox::information(this, "Error", QString::fromStdString(Dane_zalogowanego_pracownika::instancja()->pobierz_wyjatek()));
	Dane_zalogowanego_pracownika::instancja()->ustaw_id_zadania("");
}

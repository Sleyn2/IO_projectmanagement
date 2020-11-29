#include "zmien_haslo_okno.h"

zmien_haslo_okno::zmien_haslo_okno(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

}

zmien_haslo_okno::~zmien_haslo_okno()
{
}

void zmien_haslo_okno::on_pushButton_zapisz_clicked()
{

	string stare = ui.lineEdit_stare_haslo->text().toUtf8().constData();
	string nowe = ui.lineEdit_nowe_haslo->text().toUtf8().constData();
	string powt = ui.lineEdit_powtorz->text().toUtf8().constData();
	string obecne = Dane_zalogowanego_pracownika::instancja()->pobierz_haslo();

	if (stare == obecne)
	{
		if (nowe == powt && nowe != "")
		{
			Fun_ustawienia::edycja_danych_uzytkownika(Dane_zalogowanego_pracownika::instancja()->pobierz_id_pracownika(),
				Dane_zalogowanego_pracownika::instancja()->pobierz_imie(),
				Dane_zalogowanego_pracownika::instancja()->instancja()->pobierz_nazwisko(),
				Dane_zalogowanego_pracownika::instancja()->pobierz_login(),
				nowe,
				Dane_zalogowanego_pracownika::instancja()->pobierz_czy_administator());

			Dane_zalogowanego_pracownika::instancja()->ustaw_dane_logowanie(Dane_zalogowanego_pracownika::instancja()->pobierz_imie(),
				Dane_zalogowanego_pracownika::instancja()->instancja()->pobierz_nazwisko(),
				Dane_zalogowanego_pracownika::instancja()->pobierz_login(),
				nowe,
				Dane_zalogowanego_pracownika::instancja()->pobierz_czy_administator(),
				Dane_zalogowanego_pracownika::instancja()->pobierz_id_pracownika()

			);

			this->close();
			ui.lineEdit_stare_haslo->setText("");
			ui.lineEdit_nowe_haslo->setText("");
			ui.lineEdit_powtorz->setText("");
		}
		else
		{
			const QString title = "Niepoprawne has³o";
			const QString text = "Nowe has³o i jego powtórzenie musz¹ byæ identyczne.";

			QMessageBox msg;
			msg.setIcon(QMessageBox::Icon::Information);
			msg.setWindowTitle(title);
			msg.setText(text);
			msg.setStandardButtons(QMessageBox::StandardButton::Cancel);

			msg.exec();
		}
	}
	else
	{
		const QString title = "Niepoprawne has³o";
		const QString text = "Niepoprawne stare has³o.";

		QMessageBox msg;
		msg.setIcon(QMessageBox::Icon::Information);
		msg.setWindowTitle(title);
		msg.setText(text);
		msg.setStandardButtons(QMessageBox::StandardButton::Cancel);

		msg.exec();
	}

	
}

void zmien_haslo_okno::on_pushButton_anuluj_clicked()
{
	this->close();
	ui.lineEdit_stare_haslo->setText("");
	ui.lineEdit_nowe_haslo->setText("");
	ui.lineEdit_powtorz->setText("");

}

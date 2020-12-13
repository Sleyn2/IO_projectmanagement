#include "dodawanie_pracownikow_okno.h"


dodawanie_pracownikow_okno::dodawanie_pracownikow_okno(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	odswiezProsby();

	if (ui.comboBox_wybierz_prac->currentText() != "")
	{

	}
}

dodawanie_pracownikow_okno::~dodawanie_pracownikow_okno()
{
}

void dodawanie_pracownikow_okno::odswiezProsby()
{
	std::vector<QString> prosby = Fun_ustawienia::pobierz_liste_prosb();

	ui.comboBox_wybierz_prac->clear();

	for (int i = 0; i < prosby.size(); i++)
	{
		ui.comboBox_wybierz_prac->addItem(prosby[i]);
	}

	if (ui.comboBox_wybierz_prac->currentText() != "")
	{
		QString currentText = ui.comboBox_wybierz_prac->currentText();
		string login = Fun_ustawienia::wyluskaj_login(currentText.toUtf8().constData());
		vector<string> imie_i_nazw = Fun_ustawienia::imie_nazwisko_po_loginie(login, "prosby");
		
		if (imie_i_nazw.size() == 2)
		{
			ui.label_imie_wart->setText(QString::fromStdString(imie_i_nazw[0]));
			ui.label_nazwisko_wart->setText(QString::fromStdString(imie_i_nazw[1]));
			ui.label_login_wart->setText(QString::fromStdString(login));
		}
	}
	else
	{
		ui.label_imie_wart->clear();
		ui.label_nazwisko_wart->clear();
		ui.label_login_wart->clear();
	}
}

void dodawanie_pracownikow_okno::on_comboBox_wybierz_prac_currentTextChanged()
{
	if (!ui.comboBox_wybierz_prac->currentText().isEmpty())
	{
	
		string currentText = ui.comboBox_wybierz_prac->currentText().toUtf8().constData();

		string login = Fun_ustawienia::wyluskaj_login(currentText);

		vector<string> imie_i_nazw = Fun_ustawienia::imie_nazwisko_po_loginie(login, "prosby");

		if (imie_i_nazw.size() == 2)
		{
			ui.label_imie_wart->setText(QString::fromStdString(imie_i_nazw[0]));
			ui.label_nazwisko_wart->setText(QString::fromStdString(imie_i_nazw[1]));
			ui.label_login_wart->setText(QString::fromStdString(login));
		}
		
	}
}

void dodawanie_pracownikow_okno::on_pushButton_dodaj_clicked()
{
	string currentText = ui.comboBox_wybierz_prac->currentText().toUtf8().constData();

	string login = Fun_ustawienia::wyluskaj_login(currentText);

	QMessageBox msg;

	if (Fun_ustawienia::zatwierdz_pracownika(login, "0") && Fun_ustawienia::usun_prosbe(login))
	{
		msg.setWindowTitle("Sukces");
		msg.setText("Dodano pracownika.");
		msg.exec();
	}
	else
	{
		msg.setWindowTitle("Blad");
		msg.setText("Wystapil blad, nie dodano pracownika.");
		msg.exec();
	}
	odswiezProsby();
}

void dodawanie_pracownikow_okno::on_pushButton_odrzuc_clicked()
{
	string currentText = ui.comboBox_wybierz_prac->currentText().toUtf8().constData();
	string login = Fun_ustawienia::wyluskaj_login(currentText);
	QMessageBox msg;

	if (Fun_ustawienia::usun_prosbe(login))
	{
		msg.setWindowTitle("Sukces");
		msg.setText("Pomyslnie usunieto prosbe.");
		msg.exec();
	}
	else
	{
		msg.setWindowTitle("Blad");
		msg.setText("Wystapil blad. Nie usunieto prosby.");
		msg.exec();
	}
	
	odswiezProsby();
}

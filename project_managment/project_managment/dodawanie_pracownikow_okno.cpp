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
}

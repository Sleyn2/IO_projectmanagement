#include "wiadomosci_okno.h"

wiadomosci_okno::wiadomosci_okno(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
}

wiadomosci_okno::~wiadomosci_okno()
{
}
void wiadomosci_okno::ustawTryb(int i)
{
	ui.stackedWidget->setCurrentIndex(i);
}
void wiadomosci_okno::on_pushButton_send_clicked()
{
	QString tytul = ui.lineEdit_Title->text();
	QString wiadomosc = ui.textEdit->toPlainText();
}
void wiadomosci_okno::on_pushButton_cancel_clicked()
{
	this->close();
}

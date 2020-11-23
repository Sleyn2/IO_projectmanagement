#pragma once

#include <QWidget>
#include "ui_wiadomosci_okno.h"
#include <QString>

class wiadomosci_okno : public QWidget
{
	Q_OBJECT

public:
	wiadomosci_okno(QWidget *parent = Q_NULLPTR);
	~wiadomosci_okno();
	void ustawTryb(int i);
private slots:
	void on_pushButton_send_clicked();
	void on_pushButton_cancel_clicked();

private:
	Ui::wiadomosci_okno ui;
};

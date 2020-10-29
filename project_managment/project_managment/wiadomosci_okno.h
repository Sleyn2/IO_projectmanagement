#pragma once

#include <QWidget>
#include "ui_wiadomosci_okno.h"

class wiadomosci_okno : public QWidget
{
	Q_OBJECT

public:
	wiadomosci_okno(QWidget *parent = Q_NULLPTR);
	~wiadomosci_okno();

private:
	Ui::wiadomosci_okno ui;
};

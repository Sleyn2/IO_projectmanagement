#pragma once

#include <QWidget>
#include "ui_EdycjaZadan.h"

class EdycjaZadan : public QWidget
{
	Q_OBJECT

public:
	EdycjaZadan(QWidget *parent = Q_NULLPTR);
	~EdycjaZadan();

private:
	Ui::EdycjaZadan ui;
};

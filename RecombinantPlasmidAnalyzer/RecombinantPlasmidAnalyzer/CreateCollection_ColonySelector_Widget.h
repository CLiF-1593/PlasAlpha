#pragma once

#include <QWidget>
#include "ui_CreateCollection_ColonySelector_Widget.h"

class CreateCollection_ColonySelector_Widget : public QWidget
{
	Q_OBJECT

public:
	CreateCollection_ColonySelector_Widget(QWidget *parent = nullptr);
	~CreateCollection_ColonySelector_Widget();

private:
	Ui::CreateCollection_ColonySelector_WidgetClass ui;
};

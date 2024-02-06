#pragma once

#include <QWidget>
#include "ui_CreateCollection_LinkerSelector_Widget.h"
#include "DragAndDrop_Screen.h"

class CreateCollection_LinkerSelector_Widget : public QWidget
{
	Q_OBJECT

public:
	CreateCollection_LinkerSelector_Widget(QWidget *parent = nullptr);
	~CreateCollection_LinkerSelector_Widget();

private:
	Ui::CreateCollection_LinkerSelector_WidgetClass  ui;
};

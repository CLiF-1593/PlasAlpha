#pragma once

#include <QWidget>
#include "ui_DragAndDrop_Screen.h"

class DragAndDrop_Screen : public QWidget
{
	Q_OBJECT

public:
	DragAndDrop_Screen(QWidget *parent = nullptr);
	~DragAndDrop_Screen();
	void Resize();

private:
	Ui::DragAndDrop_ScreenClass ui;
};

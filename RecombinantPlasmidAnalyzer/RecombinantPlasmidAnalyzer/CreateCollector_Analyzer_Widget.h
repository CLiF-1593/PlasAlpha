#pragma once

#include <QWidget>
#include "ui_CreateCollector_Analyzer_Widget.h"

class CreateCollector_Analyzer_Widget : public QWidget
{
	Q_OBJECT

public:
	CreateCollector_Analyzer_Widget(QWidget *parent = nullptr);
	~CreateCollector_Analyzer_Widget();

private:
	Ui::CreateCollector_Analyzer_WidgetClass ui;
};

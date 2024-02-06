#pragma once

#include <QMainWindow>
#include "ui_TitleWindow.h"
#include <string>
#include <vector>
#include <filesystem>

class TitleWindow : public QMainWindow
{
	Q_OBJECT

public:
	TitleWindow(QWidget *parent = nullptr);
	~TitleWindow();

private:
	Ui::TitleWindowClass ui;

	std::vector<std::string> previous_report_list;

private slots:
	void CreateButtonClicked();
};

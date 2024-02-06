#include "TitleWindow.h"
#include "Environment.h"
#include "FileIO.h"
#include "CreateWindow.h"
#include <iostream>
using namespace std;

extern QMainWindow* current_window;

TitleWindow::TitleWindow(QWidget *parent) : QMainWindow(parent) {
	QDebug(QtMsgType::QtDebugMsg) << "TitleWindow is created";

	ui.setupUi(this);

	Environment::SetWindowStyle(this);
	
	this->previous_report_list = FileIO::ReadFileLines(FileIO::InnerPath("prev"));
	for (int i = 0; i < this->previous_report_list.size(); i++) {
		QListWidgetItem* item;
		item = new QListWidgetItem(ui.previous_report_list);
		ui.previous_report_list->addItem(item);
		auto name = new QLabel();
		auto pos = this->previous_report_list[i].find_last_of("/\\") + 1;
		name->setText(QString::fromStdString(this->previous_report_list[i].substr(pos, this->previous_report_list[i].size() - pos - 6)));
		name->setStyleSheet(Environment::FontColor(Level_1) + Environment::FontSize(10) + "font-weight: 700;");
		auto path = new QLabel();
		path->setText(QString::fromStdString(this->previous_report_list[i]));
		path->setToolTip(QString::fromStdString(this->previous_report_list[i]));
		path->setStyleSheet(Environment::FontColor(Level_2) + Environment::FontSize(8) + "font-weight: 500;");
		auto item_layout = new QVBoxLayout;
		item_layout->addWidget(name);
		item_layout->addWidget(path);
		auto widget = new QWidget();
		widget->setStyleSheet("background-color : None;");
		widget->setLayout(item_layout);
		item->setSizeHint(widget->minimumSizeHint());
		ui.previous_report_list->setItemWidget(item, widget);
	}
	
	ui.background_layout->setStyleSheet(Environment::BackgroundColor());
	ui.title->setStyleSheet(Environment::FontColor(Highlight));
	ui.create_btn->setStyleSheet(Environment::ButtonStandardStyle());
	ui.open_btn->setStyleSheet(Environment::ButtonStandardStyle());
	ui.sequence_lib_btn->setStyleSheet(Environment::ButtonStandardStyle());
	ui.previous_report_list->setStyleSheet(
		"QListWidget {" +
		Environment::BackgroundColor(Level_1)
		+ "border : None; border-radius: 5px;"
		+ "}"
		+ "QListWidget::item:selected {" + Environment::BackgroundColor(Highlight_Low, "30") + " border : none;}"
		+ "QListWidget::item:hover {" + Environment::BackgroundColor(Highlight_Low, "50") + "}"
		+ Environment::ScrollbarStandardStyle()
		+ "QToolTip { " + Environment::BackgroundColor() + " border: none; }"
	);
	ui.previous_report_list->setSelectionMode(QAbstractItemView::SelectionMode::SingleSelection);

	connect(ui.create_btn, SIGNAL(clicked()), this, SLOT(CreateButtonClicked()));
}

TitleWindow::~TitleWindow() { 
	QDebug(QtMsgType::QtDebugMsg) << "TitleWindow is destroyed";
}


void TitleWindow::CreateButtonClicked() {
	current_window->close();
	delete current_window;
	current_window = new CreateWindow();
	current_window->show();
}
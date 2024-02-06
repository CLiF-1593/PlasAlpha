#include "CreateCollection_LinkerSelector_Widget.h"
#include "Environment.h"

#include <QDebug>
#include <QFileDialog>
#include <QDropEvent>
#include <QMimeData>

CreateCollection_LinkerSelector_Widget::CreateCollection_LinkerSelector_Widget(QWidget *parent) : QWidget(parent) {
	QDebug(QtMsgType::QtDebugMsg) << "CreateCollection_DataSelector_Widget is created";

	this->hide();

	ui.setupUi(this);

	ui.main_title->setStyleSheet(Environment::FontColor(Highlight) + Environment::FontSize(20));
	ui.window_title->setStyleSheet(Environment::FontColor(Highlight_Low) + Environment::FontSize(12));
	ui.label->setStyleSheet(Environment::FontColor() + Environment::FontSize(9));

	ui.next_btn->setStyleSheet(Environment::ButtonRectangleStyle());
	ui.back_btn->setStyleSheet(Environment::ButtonRectangleStyle());

	ui.linker_list->setStyleSheet(
		"QListWidget {"
		+ Environment::BackgroundColor(Level_1)
		+ Environment::FontColor()
		+ Environment::FontSize(9)
		+ "border: 0px solid " + Environment::BorderColor(Level_4, true) + ";"
		+ "}"
		+ "QListWidget::item:selected {" + Environment::BackgroundColor(Highlight_Low, "30") + " border : none;}"
		+ "QListWidget::item:hover {" + Environment::BackgroundColor(Highlight_Low, "50") + "}"
		+ Environment::ScrollbarStandardStyle()
		+ "QToolTip { " + Environment::BackgroundColor() + Environment::FontColor() + " border: none; }"
	);
}

CreateCollection_LinkerSelector_Widget::~CreateCollection_LinkerSelector_Widget() {
	QDebug(QtMsgType::QtDebugMsg) << "CreateCollection_DataSelector_Widget is deleted";
}
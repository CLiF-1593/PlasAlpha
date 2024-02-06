#include "DragAndDrop_Screen.h"
#include "Environment.h"
#include <qsizepolicy.h>

DragAndDrop_Screen::DragAndDrop_Screen(QWidget *parent) : QWidget(parent) {
	this->hide();

	ui.setupUi(this);

	ui.label->setStyleSheet(Environment::FontColor() + Environment::BackgroundColor(Highlight, "30"));

	this->setFixedSize(parent->size());
}

DragAndDrop_Screen::~DragAndDrop_Screen() {

}

void DragAndDrop_Screen::Resize() {
	this->setFixedSize(this->parentWidget()->size());
}

#include "CreateCollection_VectorSelector_Widget.h"
#include "Environment.h"

#include <QDebug>
#include <QFileDialog>
#include <QDropEvent>
#include <QMimeData>

#include "CreateWindow.h"

CreateCollection_VectorSelector_Widget::CreateCollection_VectorSelector_Widget(QWidget *parent) : QWidget(parent) {
	QDebug(QtMsgType::QtDebugMsg) << "CreateCollection_VectorSelector_Widget is created";
	
	this->hide();

	ui.setupUi(this);

	ui.main_title->setStyleSheet(Environment::FontColor(Highlight) + Environment::FontSize(20));
	ui.window_title->setStyleSheet(Environment::FontColor(Highlight_Low) + Environment::FontSize(12));
	ui.label_2->setStyleSheet(Environment::FontColor() + Environment::FontSize(9));
	ui.label_4->setStyleSheet(Environment::FontColor() + Environment::FontSize(9));
	ui.label_6->setStyleSheet(Environment::FontColor() + Environment::FontSize(9));
	ui.description->setStyleSheet(Environment::FontColor(Level_4) + Environment::FontSize(9));

	ui.location_select_btn->setStyleSheet(Environment::ButtonRectangleStyle());
	ui.next_btn->setStyleSheet(Environment::ButtonRectangleStyle());
	
	ui.plasmid_location->setStyleSheet(
		"QLineEdit {"
		+ Environment::BackgroundColor(Level_1)
		+ Environment::FontColor()
		+ Environment::FontSize(9)
		+ "border: 1px solid " + Environment::BorderColor(Level_4, true) + ";"
		+ "}"
		+ "QLineEdit:disabled {" + Environment::FontColor(Level_4) + "}"
		);
	ui.plasmid_location->setReadOnly(true);
	ui.plasmid_name->setStyleSheet(
		"QLineEdit {"
		+ Environment::BackgroundColor(Level_1)
		+ Environment::FontColor()
		+ Environment::FontSize(9)
		+ "border: 1px solid " + Environment::BorderColor(Level_4, true) + ";"
		+ "}"
		+ "QLineEdit:disabled {" + Environment::FontColor(Level_4) + "}"
	);
	ui.plasmid_selector->setStyleSheet(
		+"QLineEdit, QComboBox {"
		+ Environment::BackgroundColor(Level_1)
		+ Environment::FontColor()
		+ Environment::FontSize(9)
		+ "border: 1px solid " + Environment::BorderColor(Level_4, true) + ";"
		+ "}"
		+ "QListView::item {"
		+ Environment::BackgroundColor(Level_1)
		+ Environment::FontColor()
		+ Environment::FontSize(9)
		+ "}"
		+ "QListView::item:selected {" + Environment::BackgroundColor(Highlight_Low, "30") + " border : none;}"
		+ "QListView::item:hover {" + Environment::BackgroundColor(Highlight_Low, "50") + "}"
		+ Environment::ScrollbarStandardStyle()
	);

	ui.plasmid_selector->addItem("Custom Plasmid");
	ui.plasmid_selector->addItem("pCES208");

	ui.plasmid_name->setEnabled(true);
	ui.plasmid_name->setText("");

	ui.plasmid_location->setText("");
	ui.plasmid_location->setEnabled(true);
	ui.plasmid_location->setReadOnly(true);

	ui.location_select_btn->setEnabled(true);

	connect(ui.plasmid_selector, SIGNAL(currentIndexChanged(int)), this, SLOT(PlasmidSelectorChanged(int)));
	connect(ui.location_select_btn, SIGNAL(clicked()), this, SLOT(LocationSelectBtnClicked()));
	connect(ui.next_btn, SIGNAL(clicked()), this, SLOT(NextBtnClicked()));
	
	this->drag_and_drop_screen = new DragAndDrop_Screen(this);

	setAcceptDrops(true);

	ui.next_btn->setEnabled(false);
}

CreateCollection_VectorSelector_Widget::~CreateCollection_VectorSelector_Widget() {
	QDebug(QtMsgType::QtDebugMsg) << "CreateCollection_VectorSelector_Widget is deleted";
	delete this->drag_and_drop_screen;
}

void CreateCollection_VectorSelector_Widget::dragEnterEvent(QDragEnterEvent* event) {
	event->acceptProposedAction();
	this->drag_and_drop_screen->Resize();
	this->drag_and_drop_screen->show();
}

void CreateCollection_VectorSelector_Widget::dragMoveEvent(QDragMoveEvent* event) {
	event->acceptProposedAction();
}

void CreateCollection_VectorSelector_Widget::dragLeaveEvent(QDragLeaveEvent* event) {
	event->accept();
	this->drag_and_drop_screen->hide();
}

void CreateCollection_VectorSelector_Widget::dropEvent(QDropEvent* event) {
	const QMimeData* mimeData = event->mimeData();
	if (mimeData->hasUrls()) {
		QStringList pathList;
		QList<QUrl> urlList = mimeData->urls();
		if (!urlList.isEmpty()) {
			QString file = urlList.first().toLocalFile();
			if (file.split(".").last() == "fasta") {
				ui.plasmid_location->setText(file);
				ui.plasmid_name->setPlaceholderText(file.split("/").last().split(".").first());
				ui.next_btn->setEnabled(true);
			}
		}
	}
	this->drag_and_drop_screen->hide();
}

void CreateCollection_VectorSelector_Widget::LocationSelectBtnClicked() {
	QString file = QFileDialog::getOpenFileName(this, "Open Plasmid File", "", "DNA (*.fasta)");
	if (file != "") { 
		ui.plasmid_location->setText(file);
		ui.plasmid_name->setPlaceholderText(file.split("/").last().split(".").first());
		ui.next_btn->setEnabled(true);
	}
}

void CreateCollection_VectorSelector_Widget::NextBtnClicked() {
	emit Next(ui.plasmid_name->text(), ui.plasmid_location->text());
}

void CreateCollection_VectorSelector_Widget::PlasmidSelectorChanged(int index) {
	if (index) {
		ui.plasmid_name->setText(ui.plasmid_selector->itemText(index));
		ui.plasmid_name->setEnabled(false);
		ui.plasmid_location->setEnabled(false);
		ui.plasmid_location->setText("Plasmid Library");
		ui.location_select_btn->setEnabled(false);
		setAcceptDrops(false);
		ui.description->hide();
		ui.next_btn->setEnabled(true);
	}
	else {
		ui.plasmid_name->setText("");
		ui.plasmid_name->setEnabled(true);
		ui.plasmid_location->setText("");
		ui.plasmid_location->setEnabled(true);
		ui.location_select_btn->setEnabled(true);
		ui.plasmid_name->setPlaceholderText("");
		setAcceptDrops(true);
		ui.description->show();
		ui.next_btn->setEnabled(false);
	}
}
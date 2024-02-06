#include "CreateCollection_DataSelector_Widget.h"
#include "Environment.h"

#include <qfiledialog.h>
#include <QDropEvent>
#include <QMimeData>

CreateCollection_DataSelector_Widget::CreateCollection_DataSelector_Widget(QWidget *parent) : QWidget(parent) {
	QDebug(QtMsgType::QtDebugMsg) << "CreateCollection_DataSelector_Widget is created";

	this->hide();

	ui.setupUi(this);

	ui.main_title->setStyleSheet(Environment::FontColor(Highlight) + Environment::FontSize(20));
	ui.window_title->setStyleSheet(Environment::FontColor(Highlight_Low) + Environment::FontSize(12));
	ui.label->setStyleSheet(Environment::FontColor() + Environment::FontSize(9) + "font-weight: 700;");
	ui.description->setStyleSheet(Environment::FontColor(Level_4) + Environment::FontSize(9));

	ui.select_data_btn->setStyleSheet(Environment::ButtonRectangleStyle());
	ui.next_btn->setStyleSheet(Environment::ButtonRectangleStyle());
	ui.back_btn->setStyleSheet(Environment::ButtonRectangleStyle());

	ui.delete_btn->setStyleSheet(Environment::ButtonRectangleStyle());
	ui.duplicate_btn->setStyleSheet(Environment::ButtonRectangleStyle());
	ui.move_up_btn->setStyleSheet(Environment::ButtonRectangleStyle());
	ui.move_down_btn->setStyleSheet(Environment::ButtonRectangleStyle());

	this->ui.delete_btn->setEnabled(false);
	this->ui.duplicate_btn->setEnabled(false);
	this->ui.move_up_btn->setEnabled(false);
	this->ui.move_down_btn->setEnabled(false);

	ui.data_list->setStyleSheet(
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

	ui.next_datas->setStyleSheet(Environment::ButtonSquareStyle());
	ui.prev_datas->setStyleSheet(Environment::ButtonSquareStyle());

	this->drag_and_drop_screen = new DragAndDrop_Screen(this);

	setAcceptDrops(true);

	ui.next_btn->setEnabled(false);

	connect(ui.select_data_btn, SIGNAL(clicked()), this, SLOT(SelectDataBtnClicked()));
	connect(ui.next_btn, SIGNAL(clicked()), this, SLOT(NextBtnClicked()));
	connect(ui.back_btn, SIGNAL(clicked()), this, SLOT(BackBtnClicked()));
	connect(ui.prev_datas, SIGNAL(clicked()), this, SLOT(PrevDatasBtnClicked()));
	connect(ui.next_datas, SIGNAL(clicked()), this, SLOT(NextDatasBtnClicked()));

	connect(ui.delete_btn, SIGNAL(clicked()), this, SLOT(DeleteDataBtnClicked()));
	connect(ui.duplicate_btn, SIGNAL(clicked()), this, SLOT(DuplicateDataBtnClicked()));
	connect(ui.move_up_btn, SIGNAL(clicked()), this, SLOT(MoveUpDataBtnClicked()));
	connect(ui.move_down_btn, SIGNAL(clicked()), this, SLOT(MoveDownDataBtnClicked()));

	connect(ui.next_btn, SIGNAL(clicked()), this, SLOT(NextBtnClicked()));
	connect(ui.back_btn, SIGNAL(clicked()), this, SLOT(BackBtnClicked()));
	
	connect(ui.data_list, SIGNAL(itemSelectionChanged()), this, SLOT(DataListEventDetected()));

	this->current_page = 0;
	this->datas.resize(1);
	this->SetDataList();
}

CreateCollection_DataSelector_Widget::~CreateCollection_DataSelector_Widget() {
	QDebug(QtMsgType::QtDebugMsg) << "CreateCollection_DataSelector_Widget is deleted";
	delete this->drag_and_drop_screen;
}


void CreateCollection_DataSelector_Widget::dragEnterEvent(QDragEnterEvent* event) {
	event->acceptProposedAction();
	this->drag_and_drop_screen->Resize();
	this->drag_and_drop_screen->show();
}

void CreateCollection_DataSelector_Widget::dragMoveEvent(QDragMoveEvent* event) {
	event->acceptProposedAction();
}

void CreateCollection_DataSelector_Widget::dragLeaveEvent(QDragLeaveEvent* event) {
	event->accept();
	this->drag_and_drop_screen->hide();
}

void CreateCollection_DataSelector_Widget::dropEvent(QDropEvent* event) {
	const QMimeData* mimeData = event->mimeData();
	if (mimeData->hasUrls()) {
		QStringList pathList;
		QList<QUrl> urlList = mimeData->urls();
		if (!urlList.isEmpty()) {
			for (int i = 0; i < urlList.size(); i++) {
				QString path = urlList.at(i).toLocalFile();
				if (path.split(".").last() == "fasta") {
					if (this->datas.size() <= this->current_page) {
						this->datas.resize(this->current_page + 1);
					}
					this->datas[this->current_page].push_back(path);
				}
			}
			this->SetDataList();
		}
	}
	this->drag_and_drop_screen->hide();
}

void CreateCollection_DataSelector_Widget::SelectDataBtnClicked() {
	QStringList files = QFileDialog::getOpenFileNames(this, "Open Plasmid File", "", "DNA (*.fasta)");
	if (!files.isEmpty()) {
		for (int i = 0; i < files.size(); i++) {
			if (files[i].split(".").last() == "fasta") {
				if (this->datas.size() <= this->current_page) {
					this->datas.resize(this->current_page + 1);
				}
				this->datas[this->current_page].push_back(files[i]);
			}
		}
		this->SetDataList();
	}
}

void CreateCollection_DataSelector_Widget::SetDataList() {
	ui.data_list->clear();
	if (this->datas.size() <= this->current_page) {
		this->datas.resize(this->current_page + 1);
	}
	this->ui.label->setText("Inserts : Page " + QString::number(this->current_page + 1) + " (" + QString::number(this->datas[this->current_page].size()) + " Datas)");
	for (int i = 0; i < this->datas[this->current_page].size(); i++) {
		/*QListWidgetItem* item;
		item = new QListWidgetItem(ui.data_list);
		ui.data_list->addItem(item);
		auto name = new QLabel();
		name->setText(this->datas[this->current_page][i].split("/").last().split(".").first());
		name->setStyleSheet(Environment::FontColor(Level_1) + Environment::FontSize(10) + "font-weight: 700; padding : 0px");
		auto path = new QLabel();
		path->setText(this->datas[this->current_page][i]);
		path->setToolTip(this->datas[this->current_page][i]);
		path->setStyleSheet(Environment::FontColor(Level_2) + Environment::FontSize(8) + "font-weight: 500; padding : 0px");
		auto item_layout = new QHBoxLayout;
		item_layout->addWidget(name);
		item_layout->addWidget(path);
		auto widget = new QWidget();
		widget->setStyleSheet("background-color : None;");
		widget->setLayout(item_layout);
		item->setSizeHint(widget->minimumSizeHint());
		ui.data_list->setItemWidget(item, widget);*/
		ui.data_list->addItem("#" + QString::number(i + 1) + "\t" + this->datas[this->current_page][i].split("/").last());
		ui.data_list->item(i)->setToolTip(this->datas[this->current_page][i]);
	}
	this->CheckIsAbleToNext();
}

void CreateCollection_DataSelector_Widget::CheckIsAbleToNext() {
	int n = 0;
	for (int i = 0; i < this->datas.size(); i++) {
		if (this->datas[i].size()) {
			if (n && n != this->datas[i].size()) {
				ui.next_btn->setEnabled(false);
				return;
			}
			n = this->datas[i].size();
		}
	}
	if (n) {
		ui.next_btn->setEnabled(true);
	}
	else {
		ui.next_btn->setEnabled(false);
	}
}

void CreateCollection_DataSelector_Widget::NextBtnClicked() {
	emit Next(this->datas);
}

void CreateCollection_DataSelector_Widget::BackBtnClicked() {
	emit Back(this->datas);
}

void CreateCollection_DataSelector_Widget::PrevDatasBtnClicked() {
	this->current_page--;
	if (this->current_page < 0) {
		this->current_page = 0;
	}
	bool all_empty = true;
	for (int i = this->current_page + 1; i < this->datas.size(); i++) {
		if (!this->datas[i].isEmpty()) {
			all_empty = false;
			break;
		}
	}
	if (all_empty) {
		this->datas.resize(this->current_page + 1);
	}
	this->SetDataList();
}

void CreateCollection_DataSelector_Widget::NextDatasBtnClicked() {
	this->current_page++;
	this->SetDataList();
}

void CreateCollection_DataSelector_Widget::DeleteDataBtnClicked() {
	auto selected_indexes = this->ui.data_list->selectionModel()->selectedIndexes();
	std::vector<int> selected_indexes_vector;
	for (int i = selected_indexes.size() - 1; i >= 0; i--) {
		selected_indexes_vector.push_back(selected_indexes[i].row());
	}
	std::sort(selected_indexes_vector.begin(), selected_indexes_vector.end());
	for (int i = selected_indexes_vector.size() - 1; i >= 0; i--) {
		this->datas[this->current_page].removeAt(selected_indexes_vector[i]);
	}
	this->SetDataList();
}

void CreateCollection_DataSelector_Widget::DuplicateDataBtnClicked() {
	auto selected_indexes = this->ui.data_list->selectionModel()->selectedIndexes();
	std::vector<int> selected_indexes_vector;
	for (int i = selected_indexes.size() - 1; i >= 0; i--) {
		selected_indexes_vector.push_back(selected_indexes[i].row());
	}
	std::sort(selected_indexes_vector.begin(), selected_indexes_vector.end());
	for (int i = selected_indexes_vector.size() - 1; i >= 0; i--) {
		this->datas[this->current_page].insert(selected_indexes_vector[i], this->datas[this->current_page][selected_indexes_vector[i]]);
	}
	this->SetDataList();
	for (int i = 0; i < selected_indexes_vector.size(); i++) {
		this->ui.data_list->item(selected_indexes_vector[i] + i)->setSelected(true);
	}
}

void CreateCollection_DataSelector_Widget::MoveUpDataBtnClicked() {
	auto selected_indexes = this->ui.data_list->selectionModel()->selectedIndexes();
	std::vector<int> selected_indexes_vector;
	for (int i = selected_indexes.size() - 1; i >= 0; i--) {
		selected_indexes_vector.push_back(selected_indexes[i].row());
	}
	std::sort(selected_indexes_vector.begin(), selected_indexes_vector.end());
	bool reset = true;
	for (int i = 0; i < selected_indexes_vector.size(); i++) {
		if (selected_indexes_vector[i] != 0) {
			auto t = this->datas[this->current_page][selected_indexes_vector[i]];
			this->datas[this->current_page][selected_indexes_vector[i]] = this->datas[this->current_page][selected_indexes_vector[i] - 1];
			this->datas[this->current_page][selected_indexes_vector[i] - 1] = t;
		}
		else {
			reset = false;
			break;
		}
	}
	if (reset) {
		this->SetDataList();
		for (int i = selected_indexes_vector.size() - 1; i >= 0; i--) {
			this->ui.data_list->item(selected_indexes_vector[i] - 1)->setSelected(true);
		}
	}
}

void CreateCollection_DataSelector_Widget::MoveDownDataBtnClicked() {
	auto selected_indexes = this->ui.data_list->selectionModel()->selectedIndexes();
	std::vector<int> selected_indexes_vector;
	for (int i = selected_indexes.size() - 1; i >= 0; i--) {
		selected_indexes_vector.push_back(selected_indexes[i].row());
	}
	std::sort(selected_indexes_vector.begin(), selected_indexes_vector.end());
	bool reset = true;
	for (int i = selected_indexes_vector.size() - 1; i >= 0; i--) {
		if (selected_indexes_vector[i] != this->datas[this->current_page].size() - 1) {
			auto t = this->datas[this->current_page][selected_indexes_vector[i]];
			this->datas[this->current_page][selected_indexes_vector[i]] = this->datas[this->current_page][selected_indexes_vector[i] + 1];
			this->datas[this->current_page][selected_indexes_vector[i] + 1] = t;
		}
		else {
			reset = false;
			break;
		}
	}
	if (reset) {
		this->SetDataList();
		for (int i = selected_indexes_vector.size() - 1; i >= 0; i--) {
			this->ui.data_list->item(selected_indexes_vector[i] + 1)->setSelected(true);
		}
	}
}

void CreateCollection_DataSelector_Widget::DataListEventDetected() {
	if (this->ui.data_list->selectionModel()->selectedIndexes().empty()) {
		this->ui.delete_btn->setEnabled(false);
		this->ui.move_up_btn->setEnabled(false);
		this->ui.move_down_btn->setEnabled(false);
		this->ui.duplicate_btn->setEnabled(false);
	}
	else {
		this->ui.delete_btn->setEnabled(true);
		this->ui.move_up_btn->setEnabled(true);
		this->ui.move_down_btn->setEnabled(true);
		this->ui.duplicate_btn->setEnabled(true);
	}
}

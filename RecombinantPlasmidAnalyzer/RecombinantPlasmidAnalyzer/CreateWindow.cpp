#include "CreateWindow.h"
#include "Environment.h"
#include "TitleWindow.h"

CreateWindow::CreateWindow(QWidget *parent) : QMainWindow(parent) {
	QDebug(QtMsgType::QtDebugMsg) << "CreateWindow is created";

	ui.setupUi(this);

	Environment::SetWindowStyle(this);

	ui.centralWidget->setStyleSheet(Environment::BackgroundColor());
	
	this->vector_selector_widget = new CreateCollection_VectorSelector_Widget();
	this->data_selector_widget = new CreateCollection_DataSelector_Widget();
	this->linker_selector_widget = new CreateCollection_LinkerSelector_Widget();
	this->colony_selector_widget = new CreateCollection_ColonySelector_Widget();
	this->analyzer_widget = new CreateCollector_Analyzer_Widget();

	this->vector_selector_widget->show();
	this->ui.widget_layout->addWidget(this->vector_selector_widget);

	this->collection_gen = new CollectionGenerator();

	connect(this->vector_selector_widget, SIGNAL(Next(const QString&, const QString&)), this, SLOT(SelectVector(const QString&, const QString&)));
	connect(this->data_selector_widget, SIGNAL(Next(const std::vector<QStringList>&)), this, SLOT(SelectDatas(const std::vector<QStringList>&)));
	connect(this->data_selector_widget, SIGNAL(Back(const std::vector<QStringList>&)), this, SLOT(SelectDatas_Back(const std::vector<QStringList>&)));
}

CreateWindow::~CreateWindow() {
	QDebug(QtMsgType::QtDebugMsg) << "CreateWindow is deleted";
	delete this->vector_selector_widget, this->data_selector_widget, this->linker_selector_widget, this->colony_selector_widget, this->analyzer_widget;
	delete this->collection_gen;
}

void CreateWindow::SelectVector(const QString &vector_name, const QString &vector_path) {
	this->ui.widget_layout->removeWidget(this->vector_selector_widget);
	this->vector_selector_widget->hide();
	this->ui.widget_layout->addWidget(this->data_selector_widget);
	this->data_selector_widget->show();
	this->ui.widget_layout->update();

	this->collection_gen->SetVectorPath(vector_path);
	this->collection_gen->col()->SetVectorName(vector_name.toStdString());
}

void CreateWindow::SelectDatas(const std::vector<QStringList>& datas) {
	this->ui.widget_layout->removeWidget(this->data_selector_widget);
	this->data_selector_widget->hide();
	this->ui.widget_layout->addWidget(this->linker_selector_widget);
	this->linker_selector_widget->show();
	this->ui.widget_layout->update();

	this->collection_gen->SetDatasPath(datas);
}

void CreateWindow::SelectDatas_Back(const std::vector<QStringList>& datas) {
	this->ui.widget_layout->removeWidget(this->data_selector_widget);
	this->data_selector_widget->hide();
	this->ui.widget_layout->addWidget(this->vector_selector_widget);
	this->vector_selector_widget->show();
	this->ui.widget_layout->update();

	this->collection_gen->SetDatasPath(datas);
}

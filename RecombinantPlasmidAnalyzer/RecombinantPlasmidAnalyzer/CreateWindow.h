#pragma once

#include <QMainWindow>
#include "ui_CreateWindow.h"

#include "CreateCollection_VectorSelector_Widget.h"
#include "CreateCollection_DataSelector_Widget.h"
#include "CreateCollection_LinkerSelector_Widget.h"
#include "CreateCollection_ColonySelector_Widget.h"
#include "CreateCollector_Analyzer_Widget.h"

#include "CollectionGenerator.h"

class CreateWindow : public QMainWindow
{
	Q_OBJECT

public:
	CreateWindow(QWidget *parent = nullptr);
	~CreateWindow();

private:
	Ui::CreateWindowClass ui;

	CreateCollection_VectorSelector_Widget* vector_selector_widget;
	CreateCollection_DataSelector_Widget* data_selector_widget;
	CreateCollection_LinkerSelector_Widget* linker_selector_widget;
	CreateCollection_ColonySelector_Widget* colony_selector_widget;
	CreateCollector_Analyzer_Widget* analyzer_widget;

	CollectionGenerator *collection_gen;

private slots:
	void SelectVector(const QString &vector_name, const QString &vector_path);
	void SelectDatas(const std::vector<QStringList> &datas);
	void SelectDatas_Back(const std::vector<QStringList> &datas);
};

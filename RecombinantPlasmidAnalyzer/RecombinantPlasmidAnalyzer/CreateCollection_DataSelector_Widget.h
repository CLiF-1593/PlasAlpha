#pragma once

#include <QWidget>
#include "ui_CreateCollection_DataSelector_Widget.h"
#include "DragAndDrop_Screen.h"

class CreateCollection_DataSelector_Widget : public QWidget
{
	Q_OBJECT

public:
	CreateCollection_DataSelector_Widget(QWidget *parent = nullptr);
	~CreateCollection_DataSelector_Widget();

protected:
	void dragEnterEvent(QDragEnterEvent* event);
	void dragMoveEvent(QDragMoveEvent* event);
	void dragLeaveEvent(QDragLeaveEvent* event);
	void dropEvent(QDropEvent* event);

private:
	Ui::CreateCollection_DataSelector_WidgetClass ui;
	DragAndDrop_Screen* drag_and_drop_screen = nullptr;

	std::vector<QStringList> datas;
	int current_page = 0;

	void SetDataList();

	void CheckIsAbleToNext();

private slots:
	void SelectDataBtnClicked();
	void NextBtnClicked();
	void BackBtnClicked();
	void PrevDatasBtnClicked();
	void NextDatasBtnClicked();

	void DeleteDataBtnClicked();
	void DuplicateDataBtnClicked();
	void MoveUpDataBtnClicked();
	void MoveDownDataBtnClicked();

	void DataListEventDetected();

signals: 
	void Next(const std::vector<QStringList> &datas);
	void Back(const std::vector<QStringList> &datas);
};

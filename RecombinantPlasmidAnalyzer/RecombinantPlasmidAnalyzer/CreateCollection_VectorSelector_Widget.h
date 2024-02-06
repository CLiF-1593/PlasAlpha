#pragma once

#include <QWidget>
#include "ui_CreateCollection_VectorSelector_Widget.h"
#include "DragAndDrop_Screen.h"

class CreateCollection_VectorSelector_Widget : public QWidget
{
	Q_OBJECT

public:
	CreateCollection_VectorSelector_Widget(QWidget *parent = nullptr);
	~CreateCollection_VectorSelector_Widget();

private:
	Ui::CreateCollection_VectorSelector_WidgetClass ui;
	DragAndDrop_Screen* drag_and_drop_screen = nullptr;
	
protected:
	void dragEnterEvent(QDragEnterEvent* event);
	void dragMoveEvent(QDragMoveEvent* event);
	void dragLeaveEvent(QDragLeaveEvent* event);
	void dropEvent(QDropEvent* event);

private slots:
	void PlasmidSelectorChanged(int index);
	void LocationSelectBtnClicked();
	void NextBtnClicked();

signals:
	void Next(const QString &name, const QString &location);
};

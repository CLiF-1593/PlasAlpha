#include "MainWindow.h"
#include "Environment.h"

MainWindow::MainWindow(QWidget *parent)	: QMainWindow(parent) {
	QDebug(QtMsgType::QtDebugMsg) << "MainWindow is created";

	ui.setupUi(this);

	Environment::SetWindowStyle(this);
}

MainWindow::~MainWindow() {
	QDebug(QtMsgType::QtDebugMsg) << "MainWindow is deleted";
}

#include "TitleWindow.h"
#include "MainWindow.h"
#include <QtWidgets/QApplication>
#include <QFile>
#include <iostream>
#include "Environment.h"
using namespace std;

QMainWindow *current_window = nullptr;

int main(int argc, char *argv[]) {
	Environment::Init();

    QApplication app(argc, argv);

	current_window = new TitleWindow();
	current_window->show();

	QApplication::exec();

	delete current_window;
	return 0;
}

#pragma once
#include <qstring.h>
#include <qmainwindow.h>
enum Theme { Light, Dark };
enum Level { Level_1, Level_2, Level_3, Level_4, Level_0, Standard, Highlight, Highlight_High, Highlight_Low};

class Environment {

private:
	static Theme theme;
	static double font_size;

public:
	static const int GetWindowsTitleColor();
	static const int GetWindowsBorderColor();

	static void Init();
	static void SetTheme(Theme theme);

	static QString BackgroundColor(Level lv = Standard, QString opacity = "FF", bool only_hexcode = false);
	static QString FontColor(Level lv = Standard, bool only_hexcode = false);
	static QString BorderColor(Level lv = Standard, bool only_hexcode = false);

	static QString FontSize(int standard_size, bool only_size = false);
	
	static QString ButtonStandardStyle();
	static QString ButtonRectangleStyle();
	static QString ButtonSquareStyle();
	static QString ScrollbarStandardStyle();

	static void SetWindowStyle(QMainWindow* win);
};
#include "Environment.h"
#include <dwmapi.h>
#include <windows.h>
#pragma comment(lib, "dwmapi.lib")

#define white_0 "#" + opacity + "ffffff" //orginal white
#define white_1 "#" + opacity + "f6f6f6"
#define white_2 "#" + opacity + "ececec"
#define white_3 "#" + opacity + "e1e1e1"
#define white_4 "#" + opacity + "d0d0d0"

#define black_0 "#" + opacity + "000000" //orginal black
#define black_1 "#" + opacity + "111111"
#define black_2 "#" + opacity + "1e1e1e"
#define black_3 "#" + opacity + "3c3c3c"
#define black_4 "#" + opacity + "4d4d4d"

#define key_0 "#" + opacity + "355935" //Dark green
#define key_1 "#" + opacity + "477047"
#define key_2 "#" + opacity + "5d8c55" //standard green
#define key_3 "#" + opacity + "73a767"
#define key_4 "#" + opacity + "93be89" //Light green


Theme Environment::theme = Theme::Light;
double Environment::font_size = 1.0;

const int Environment::GetWindowsTitleColor() {
	if (theme == Theme::Light) {
		return 0x00ececec;
	}
	else {
		return 0x00111111;
	}
}

const int Environment::GetWindowsBorderColor() {
	return 0x005d8c55;
}

void Environment::Init() {
	//Read environment settings from file

	Environment::theme = Theme::Dark;
}

void Environment::SetTheme(Theme theme) {
	Environment::theme = theme;
}

QString Environment::BackgroundColor(Level lv, QString opacity, bool only_hexcode) {
	QString name = "background-color: ";
	if (only_hexcode) name = "";
	if (theme == Theme::Light) {
		switch (lv) {
		case Level_0: return name + white_0 + ";";
		case Level_1: return name + white_1 + ";";
		case Level_2: return name + white_2 + ";";
		case Level_3: return name + white_3 + ";";
		case Level_4: return name + white_4 + ";";
		case Highlight: return name + key_3 + ";";
		case Highlight_High: return name + key_2 + ";";
		case Highlight_Low: return name + key_4 + ";";
		default: return name + white_2 + ";";
		}
	}
	else {
		switch (lv) {
		case Level_0: return name + black_0 + ";";
		case Level_1: return name + black_1 + ";";
		case Level_2: return name + black_2 + ";";
		case Level_3: return name + black_3 + ";";
		case Level_4: return name + black_4 + ";";
		case Highlight: return name + key_1 + ";";
		case Highlight_High: return name + key_0 + ";";
		case Highlight_Low: return name + key_2 + ";";
		default: return name + black_2 + ";";
		}
	}
}

QString Environment::FontColor(Level lv, bool only_hexcode) {
	QString name = "color: ";
	if (only_hexcode) name = "";
	QString opacity = "FF";
	if (theme == Theme::Light) {
		switch (lv) {
		case Level_0: return name + black_0 + ";";
		case Level_1: return name + black_1 + ";";
		case Level_2: opacity = "D0"; return name + black_2 + ";";
		case Level_3: opacity = "B0"; return name + black_3 + ";";
		case Level_4: opacity = "90"; return name + black_4 + ";";
		case Highlight: return name + key_1 + ";";
		case Highlight_High: return name + key_2 + ";";
		case Highlight_Low: return name + key_0 + ";";
		default: return name + black_1 + ";";
		}
	}
	else {
		switch (lv) {
		case Level_0: return name + white_0 + ";";
		case Level_1: return name + white_1 + ";";
		case Level_2: opacity = "D0"; return name + white_2 + ";";
		case Level_3: opacity = "B0"; return name + white_3 + ";";
		case Level_4: opacity = "90"; return name + white_4 + ";";
		case Highlight: return name + key_3 + ";";
		case Highlight_High: return name + key_4 + ";";
		case Highlight_Low: return name + key_2 + ";";
		default: return name + white_1 + ";";
		}
	}
}

QString Environment::BorderColor(Level lv, bool only_hexcode) {
	QString name = "border : ";
	if (only_hexcode) name = "";
	QString opacity = "FF";
	if (theme == Theme::Light) {
		switch (lv) {
		case Level_0: return name + black_0 + ";";
		case Level_1: return name + black_1 + ";";
		case Level_2: opacity = "D0"; return name + black_2 + ";";
		case Level_3: opacity = "B0"; return name + black_3 + ";";
		case Level_4: opacity = "90"; return name + black_4 + ";";
		case Highlight: return name + key_1 + ";";
		case Highlight_High: return name + key_2 + ";";
		case Highlight_Low: return name + key_0 + ";";
		default: return name + black_1 + ";";
		}
	}
	else {
		switch (lv) {
		case Level_0: return name + white_0 + ";";
		case Level_1: return name + white_1 + ";";
		case Level_2: opacity = "D0"; return name + white_2 + ";";
		case Level_3: opacity = "B0"; return name + white_3 + ";";
		case Level_4: opacity = "90"; return name + white_4 + ";";
		case Highlight: return name + key_3 + ";";
		case Highlight_High: return name + key_4 + ";";
		case Highlight_Low: return name + key_2 + ";";
		default: return name + white_1 + ";";
		}
	}
}

QString Environment::FontSize(int standard_size, bool only_size) {
	if (only_size) return QString("%1pt;").arg((double)standard_size * font_size);
	return QString("font-size: %1pt;").arg((double)standard_size * font_size);
}

QString Environment::ButtonStandardStyle() {
	//Modern style button
	QString style = "QPushButton {";
	style += "border-style: solid;";
	style += "border-width: 0px;";
	style += "border-radius: 5px;";
	style += "background-color: " + Environment::BackgroundColor(Level_3, "FF", true);
	style += "color: " + Environment::FontColor(Standard, true);
	style += "font-size: " + Environment::FontSize(11, true);
	style += "font-weight: 700;";
	style += "padding: 5px;";
	style += "min-width: 75px;";
	style += "min-height: 23px;";
	style += "}";
	style += "QPushButton:hover {";
	style += "background-color: " + Environment::BackgroundColor(Level_4, "FF", true);
	style += "color: " + Environment::FontColor(Standard, true);
	style += "}";
	style += "QPushButton:pressed {";
	style += "background-color: " + Environment::BackgroundColor(Level_3, "FF", true);
	style += "color: " + Environment::FontColor(Standard, true);
	style += "}";
	style += "QPushButton:disabled {";
	style += "background-color: " + Environment::BackgroundColor(Level_3, "50", true);
	style += "color: " + Environment::FontColor(Level_4, true);
	style += "}";
	return style;
}

QString Environment::ButtonRectangleStyle() {
	QString style = "QPushButton {";
	style += "border-style: solid;";
	style += "border-width: 0px;";
	style += "border-radius: 0px;";
	style += "background-color: " + Environment::BackgroundColor(Level_3, "FF", true);
	style += "color: " + Environment::FontColor(Standard, true);
	style += "font-size: " + Environment::FontSize(9, true);
	style += "font-weight: 500;";
	style += "padding: 0px;";
	style += "min-width: 75px;";
	style += "min-height: 23px;";
	style += "}";
	style += "QPushButton:hover {";
	style += "background-color: " + Environment::BackgroundColor(Level_4, "FF", true);
	style += "color: " + Environment::FontColor(Standard, true);
	style += "}";
	style += "QPushButton:pressed {";
	style += "background-color: " + Environment::BackgroundColor(Level_3, "FF", true);
	style += "color: " + Environment::FontColor(Standard, true);
	style += "}";
	style += "QPushButton:disabled {";
	style += "background-color: " + Environment::BackgroundColor(Level_3, "50", true);
	style += "color: " + Environment::FontColor(Level_4, true);
	style += "}";
	return style;
}

QString Environment::ButtonSquareStyle() {
	QString style = "QPushButton {";
	style += "border-style: solid;";
	style += "border-width: 0px;";
	style += "border-radius: 0px;";
	style += "background-color: " + Environment::BackgroundColor(Level_3, "FF", true);
	style += "color: " + Environment::FontColor(Standard, true);
	style += "font-size: " + Environment::FontSize(9, true);
	style += "font-weight: 500;";
	style += "padding: 0px;";
	style += "min-width: 23px;";
	style += "min-height: 23px;";
	style += "}";
	style += "QPushButton:hover {";
	style += "background-color: " + Environment::BackgroundColor(Level_4, "FF", true);
	style += "color: " + Environment::FontColor(Standard, true);
	style += "}";
	style += "QPushButton:pressed {";
	style += "background-color: " + Environment::BackgroundColor(Level_3, "FF", true);
	style += "color: " + Environment::FontColor(Standard, true);
	style += "}";
	style += "QPushButton:disabled {";
	style += "background-color: " + Environment::BackgroundColor(Level_3, "50", true);
	style += "color: " + Environment::FontColor(Level_4, true);
	style += "}";
	return style;
}

QString Environment::ScrollbarStandardStyle() {
	QString style;
	style += "QScrollBar:vertical, QScrollBar:horizontal {";
	style += "border: 0px solid grey;";
	style += "background: " + Environment::BackgroundColor(Level_0, "FF", true) + ";";
	style += "width: 10px;";
	style += "margin: 0px 0px 0px 0px;";
	style += "border-radius: 4px;";
	style += "}";
	style += "QScrollBar::handle:vertical, QScrollBar::handle:horizontal {";
	style += "background: " + Environment::BackgroundColor(Highlight_High, "FF", true) + ";";
	style += "min-height: 20px;";
	style += "border-radius: 5px;";
	style += "}";
	style += "QScrollBar::handle:vertical:hover, QScrollBar::handle:horizontal:hover {";
	style += "background: " + Environment::BackgroundColor(Highlight_High, "A0", true) + ";";
	style += "}";
	style += "QScrollBar::handle:vertical:pressed, QScrollBar::handle:horizontal:pressed {";
	style += "background: " + Environment::BackgroundColor(Highlight_High, "70", true) + ";";
	style += "}";
	style += "QScrollBar::add-line:vertical, QScrollBar::sub-line:vertical {";
	style += "border: None;";
	style += "background: None;";
	style += "}";
	style += "QScrollBar::left-arrow:horizontal, QScrollBar::right-arrow:horizontal, QScrollBar::add-page:horizontal, QScrollBar::sub-page:horizontal {";
	style += "border: none;";
	style += "background: none;";
	style += "}";
	style += "QScrollBar::up-arrow::vertical, QScrollBar::down-arrow:vertical, QScrollBar::add-page::vertical, QScrollBar::sub-page:vertical {";
	style += "border: none;";
	style += Environment::BackgroundColor(Level_4, "30");
	style += "}";
	return style;
}

void Environment::SetWindowStyle(QMainWindow* win) {
	HWND hwnd = (HWND)win->winId();

	COLORREF TITLE_COLOR = Environment::GetWindowsTitleColor();
	COLORREF BORDER_COLOR = Environment::GetWindowsBorderColor();

	DwmSetWindowAttribute(hwnd, DWMWINDOWATTRIBUTE::DWMWA_CAPTION_COLOR, &TITLE_COLOR, sizeof(TITLE_COLOR));
	DwmSetWindowAttribute(hwnd, DWMWINDOWATTRIBUTE::DWMWA_BORDER_COLOR, &BORDER_COLOR, sizeof(BORDER_COLOR));

}

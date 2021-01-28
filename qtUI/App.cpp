#include "App.hpp"
#include "QtWidgets"
#include "CWidget.h"

App::App(QWidget * parent) : QWidget(parent) {
	ui.setupUi(this);
	connect(ui.pushButton, &QPushButton::clicked, this, []() {
		CWidget * w = new CWidget();
		//QWidget * w = new QWidget();
		w->resize(300, 300);
		w->show();
	});
}

App::~App() {

}

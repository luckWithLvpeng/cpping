#include "App.hpp"
#include "QtWidgets"

App::App(QWidget * parent) : QWidget(parent) {
	ui.setupUi(this);
	QLabel * l = new QLabel(this);
	l->setText(tr("这是什么"));
	QLabel * l2 = new QLabel(this);
	l2->setText(tr("我很高兴"));
}

App::~App() {

}

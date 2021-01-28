
#include "CMaskwidget.h"
#include "qmutex.h"
#include "qapplication.h"
#include "qdesktopwidget.h"
#include "QtWidgets"


CMaskWidget::CMaskWidget(QWidget *parent) : QWidget(parent)
{
	stack = 0;
	opacity = 0.4;
	color = QColor(0, 0, 0);
	this->resize(qApp->desktop()->size());

	//this->setWindowFlags(Qt::Window | Qt::FramelessWindowHint | Qt::Tool);
	l = new QHBoxLayout();
	l->setMargin(0);
	l->setSpacing(0);
	w = new QWidget(this);
	setBgColor(color);
	l->addWidget(w);
	this->setLayout(l);
	this->hide();
	qApp->installEventFilter(this);
}
void CMaskWidget::setOpacity(double n)
{
	opacity = n;
	setBgColor(color);
}

void CMaskWidget::setBgColor(QColor& color)
{
	w->setStyleSheet(QString("background:rgba(") + QString::number(color.red()) + "," + QString::number(color.green()) + "," + QString::number(color.blue()) + "," + QString::number(opacity) + ");");
}


void CMaskWidget::showEvent(QShowEvent *event)
{
	this->resize(this->parentWidget()->size());
	QWidget::showEvent(event);
}

bool CMaskWidget::eventFilter(QObject *obj, QEvent *event)
{
	if (event->type() == QEvent::Show) {
		if (obj->property("mask").toBool()) {
			stack++;
			this->show();
			QWidget *w = (QWidget *)obj;
			w->activateWindow();
			w->raise();
		}
	}
	else if (event->type() == QEvent::Close) {
		if (obj->property("mask").toBool()) {
			stack--;
			if (stack == 0) {
				this->hide();
				this->parentWidget()->activateWindow();
			}
		}
	}
	else if (event->type() == QEvent::WindowActivate) {
		if (obj->objectName() == this->parentWidget()->objectName()) {
			if (this->isVisible()) {
				this->activateWindow();
			}
		}
	}
	else if (event->type() == QEvent::Resize && obj == this->parentWidget()) {
		QResizeEvent * resizeEvent = dynamic_cast<QResizeEvent *>(event);
		this->resize(resizeEvent->size());
	}

	return QObject::eventFilter(obj, event);
}

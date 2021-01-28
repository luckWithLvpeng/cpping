#include "CWidget.h"
#include <QDesktopWidget>
#include <QApplication>
#include <QPainter>
#include <QFile>
#include <qdebug.h>
#include <QResizeEvent>

CWidget::CWidget(QWidget *parent)
	: QWidget(parent)
{
	// FramelessWindowHint属性设置窗口去除边框;
	// WindowMinimizeButtonHint 属性设置在窗口最小化时，点击任务栏窗口可以显示出原窗口;
	this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowMinimizeButtonHint);
	// 初始化标题栏;
	initTitleBar();
}

CWidget::~CWidget()
{

}

void CWidget::initTitleBar()
{
	m_titleBar = new TitleBar(this);
	m_titleBar->move(0, 0);
	m_titleBar->resize(this->geometry().width(), 30);
	m_titleBar->setTitleContent("哈哈", 20);
	connect(m_titleBar, SIGNAL(signalButtonMinClicked()), this, SLOT(onButtonMinClicked()));
	connect(m_titleBar, SIGNAL(signalButtonRestoreClicked()), this, SLOT(onButtonRestoreClicked()));
	connect(m_titleBar, SIGNAL(signalButtonMaxClicked()), this, SLOT(onButtonMaxClicked()));
	connect(m_titleBar, SIGNAL(signalButtonCloseClicked()), this, SLOT(onButtonCloseClicked()));
}
void CWidget::resizeEvent(QResizeEvent* event)
{
	m_titleBar->move(0, 0);
	m_titleBar->resize(event->size().width(), 30);
}
void CWidget::onButtonMinClicked()
{
	this->setWindowState(Qt::WindowMinimized);
}

void CWidget::onButtonRestoreClicked()
{
	this->setWindowState(Qt::WindowNoState);
}

void CWidget::onButtonMaxClicked()
{
	this->setWindowState(Qt::WindowMaximized);
}

void CWidget::onButtonCloseClicked()
{
	close();
}

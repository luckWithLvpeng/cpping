﻿#pragma once
#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QTimer>
#include "ui_titlebar.h"
#include "components_export_global.h"

enum ButtonType
{
	MIN_BUTTON = 0,         // 最小化和关闭按钮;
	MIN_MAX_BUTTON,        // 最小化、最大化和关闭按钮;
	ONLY_CLOSE_BUTTON       // 只有关闭按钮;
};

class COMPONENTS_EXPORT TitleBar : public QWidget
{
	Q_OBJECT

public:
	TitleBar(QWidget *parent);
	//这里parent没有给默认值NULL，保证在创建MyTitleBar对象时父指针必须得赋值;且赋值不为NULL;
	~TitleBar();

	// 设置标题栏背景色及是否设置标题栏背景色透明;
	void setBackgroundColor(int r, int g, int b, bool isTransparent = false);
	// 设置标题栏图标;
	void setTitleIcon(QString filePath, QSize IconSize = QSize(25, 25));
	// 设置标题内容;
	void setTitleContent(QString titleContent, int titleFontSize = 9);
	// 设置标题栏上按钮类型;
	void setButtonType(ButtonType buttonType);
	// 设置窗口边框宽度;
	void setWindowBorderWidth(int borderWidth);

private:
	//Ui::TitleBar* ui;
	void paintEvent(QPaintEvent *event);
	void mouseDoubleClickEvent(QMouseEvent *event);
	void mousePressEvent(QMouseEvent *event);
	void mouseMoveEvent(QMouseEvent *event);
	void mouseReleaseEvent(QMouseEvent *event);

	// 初始化控件;
	void initControl();
	// 信号槽的绑定;
	void initConnections();

signals:
	// 按钮触发的信号;
	void signalButtonMinClicked();
	void signalButtonRestoreClicked();
	void signalButtonMaxClicked();
	void signalButtonCloseClicked();

	private slots:
	// 按钮触发的槽;
	void onButtonMinClicked();
	void onButtonRestoreClicked();
	void onButtonMaxClicked();
	void onButtonCloseClicked();

private:
	QLabel* m_pIcon;                    // 标题栏图标;
	QLabel* m_pTitleContent;            // 标题栏内容;
	QPushButton* m_pButtonMin;          // 最小化按钮;
	QPushButton* m_pButtonRestore;      // 最大化还原按钮;
	QPushButton* m_pButtonMax;          // 最大化按钮;
	QPushButton* m_pButtonClose;        // 关闭按钮;

										// 标题栏背景色;
	int m_colorR;
	int m_colorG;
	int m_colorB;

	// 移动窗口的变量;
	bool m_isPressed;
	QPoint m_startMovePos;
	// 标题栏跑马灯效果时钟;
	QTimer m_titleRollTimer;
	// 标题栏内容;
	QString m_titleContent;
	// 按钮类型;
	ButtonType m_buttonType;
	// 窗口边框宽度;
	int m_windowBorderWidth;
	// 标题栏是否透明;
	bool m_isTransparent;
};

#pragma once
#include <QWidget>
#include "TitleBar.h"
#include <QResizeEvent>
#include "components_export_global.h"

class COMPONENTS_EXPORT CWidget : public QWidget
{
	Q_OBJECT
public:
	CWidget(QWidget *parent = 0);
	~CWidget();

private:
	void initTitleBar();
	//void paintEvent(QPaintEvent *event);
protected:
	void resizeEvent(QResizeEvent *event);

	private slots:
	void onButtonMinClicked();
	void onButtonRestoreClicked();
	void onButtonMaxClicked();
	void onButtonCloseClicked();

protected:
	TitleBar* m_titleBar;

};

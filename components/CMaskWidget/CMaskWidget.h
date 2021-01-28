#ifndef CMASKWIDGET_H
#define CMASKWIDGET_H
/// <summary>
/// 遮罩组件
/// 1，跟最外层组件绑定
/// 2，设置透明度
/// 3，设置颜色
/// </summary>
#include <QtWidgets>
#include "components_export_global.h"


class COMPONENTS_EXPORT CMaskWidget : public QWidget
{
    Q_OBJECT
public:
    CMaskWidget(QWidget *parent);

protected:
    void showEvent(QShowEvent *);
    bool eventFilter(QObject *obj, QEvent *event);

private:
		int  stack; // 遮罩的栈深
		double opacity;
		QColor color;
		QHBoxLayout* l;
		QWidget * w;

public Q_SLOTS:
		void setOpacity(double);
		void setBgColor(QColor&);
};

#endif // CMASKWIDGET_H

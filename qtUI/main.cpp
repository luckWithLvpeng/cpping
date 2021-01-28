
/// <summary>
/// 用于测试的代码
/// </summary>

#include <QtWidgets/QApplication>
#include <QTextCodec>
#include <QStyleFactory>
#include <QtWidgets>
#include <QtConcurrent>
#include <QVector>
#include <QFuture>
#include <QThread>
#include "App.hpp"

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);

	App a;
	a.setWindowTitle(QObject::tr("哈哈"));
	a.show();

	return app.exec();
}

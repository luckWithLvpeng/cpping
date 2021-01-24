
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
#include "TestThread.h"


class TestTask : public QRunnable
{
	void run()
	{
		qDebug() << "这里子线程runable" << QThread::currentThreadId();
	}
};


int main(int argc, char *argv[])
{
	QApplication app(argc, argv);

	TestTask* task = new TestTask;
	QThreadPool::globalInstance()->start(task);
	//concurrent::TestThread thread;
	//thread.start();
	//thread.wait();
	QtConcurrent::run([]() {
		qDebug() << "concurrent线程" << QThread::currentThreadId();
	});
	qDebug() << "这是在GUI主线程里：" << app.thread()->currentThreadId();
	//qDebug() << concurrent::ThreadPool::instance()->a;
	concurrent::run([]() {
		qDebug() << "run in 2322" << QThread::currentThreadId();
	});
	return app.exec();
}

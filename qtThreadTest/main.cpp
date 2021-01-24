
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

int mapped(int i) {
	QThread::currentThread()->sleep(i);
	return i + 10;
}
int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
	TestTask* task = new TestTask;
	QThreadPool::globalInstance()->start(task);

	QLabel * label = new QLabel();

	label->setText("0");
	label->resize(200, 200);
	label->show();

	QFutureWatcher<int> watcher;

	QObject::connect(&watcher, &QFutureWatcher<int>::progressValueChanged, label, [label](int progress) {
		label->setText(QString::number(progress));
	});
	QObject::connect(&watcher, &QFutureWatcher<int>::finished, label, [label]() {
		label->setText("结束");
	});

	QList<int> intList;
	for (size_t i = 0; i < 10; i++)
	{
		intList.push_back(i);
	}
	QFuture<int> future = QtConcurrent::mapped(intList, mapped);


	//QFuture<int> future = QtConcurrent::run([label]() -> int {
	//	qDebug() << "concurrent线程" << QThread::currentThreadId();
	//	for (int i = 1; i < 10; i++)
	//	{
	//		//label->setText(QString::number(i));
	//		qDebug() << i;
	//		QThread::currentThread()->sleep(1);
	//	}
	//	return 20;
	//});

	watcher.setFuture(future);
	qDebug() << "result" << watcher.future().results();

	//int res = future.result();

	//qDebug() << "res" << res;


	qDebug() << "这是在GUI主线程里：" << app.thread()->currentThreadId();
	concurrent::run([label]() {
		qDebug() << "run in 2322" << QThread::currentThreadId();
	});
	return app.exec();
}

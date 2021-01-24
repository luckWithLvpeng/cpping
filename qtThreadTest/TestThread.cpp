#include "TestThread.h"
#include "qdebug.h"
#include <QtWidgets>
namespace concurrent {

	CThreadPool* CThreadPool::m_instance = nullptr;
	QMutex* CThreadPool::m_init = new QMutex;
	CThreadPool::CThreadPool(int count)
		:m_bStop(false)
	{
		for (size_t i = 0; i < count; i++)
		{
			CThread* t = new CThread(this);
			m_thredList.push_back(t);
			t->start();
		}
	};
	void CThreadPool::start(CRunable* runable) {
		this->m_runableList.push_back(runable);
		m_NotEmpty.wakeOne();
	}

	CThread::CThread(CThreadPool * parent)
		:QThread(parent)
		, m_Pool(parent)
	{
	};


	void CThread::run() {
		while (!m_Pool->m_bStop)
		{
			m_Pool->m_TaskMutex.lock();
			while (m_Pool->m_runableList.isEmpty())
			{
				qDebug() << QThread::currentThreadId() << "进入等待";
				m_Pool->m_NotEmpty.wait(&m_Pool->m_TaskMutex);
				qDebug() << QThread::currentThreadId() << "被唤醒";
				//线程退出条件判断
				if (m_Pool->m_bStop)
				{
					m_Pool->m_TaskMutex.unlock();
					return;
				}
			}
			//取出任务
			CRunable* runable = m_Pool->m_runableList.front();
			m_Pool->m_runableList.pop_front();
			m_Pool->m_TaskMutex.unlock();
			if (runable)
			{
				//执行任务
				runable->run();
			}
		}
	}
}

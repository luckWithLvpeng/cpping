
/**
 *自定义线程池
 */

#include "qthread.h"
#include "QtWidgets"
#include "QtConcurrent"
namespace concurrent {
	class CRunable :public QObject
	{
	public:
		virtual void run() = 0;
	private:
	};

	template<class F>
	class Runable :public CRunable
	{
	public:
		Runable(F fun) :f(fun) {};
		virtual void run() {
			f();
		};
	private:
		F f;
	};

	class CThread;
	class CThreadPool : public QObject
	{
	public:
		CThreadPool(int count = 3);
		virtual~CThreadPool() {};
		friend CThread;
		static inline CThreadPool* instance() {
			if (m_instance == nullptr)
			{
				m_init->lock();
				if (m_instance == nullptr)
				{
					m_instance = new CThreadPool(2);
				}
				m_init->unlock();
			}
			return m_instance;
		};
		void start(CRunable* runable);
	private:
		static CThreadPool* m_instance;
		static QMutex* m_init;
		QList<CThread*> m_thredList;
		QList<CRunable*> m_runableList;
		bool m_bStop;
		QMutex m_TaskMutex;
		QWaitCondition m_NotEmpty;
	};

	class CThread :public QThread
	{
		Q_OBJECT
	private:
		CThreadPool* m_Pool;
	public:
		CThread(CThreadPool * parent);
		friend CThreadPool;
		void run() override;
	};

	template <class TFun>
	Q_DECL_EXPORT inline void run(TFun f) {
		Runable<TFun>* run = new Runable<TFun>(f);
		CThreadPool::instance()->start(run);
	};
}

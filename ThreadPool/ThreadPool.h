#include <queue>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <pthread.h>
#include <iostream>
#include "Assignment.h"
using namespace std;

/*
 * thread pool 
 */
class ThreadPool
{
	private:
		//队列互斥锁(增加，移除任务时使用)
		pthread_mutex_t queue_lock;
		//队列是否有任务
		pthread_cond_t queue_ready;
		//任务队列
		queue<Assignment> jobQueue;
		//线程id
		pthread_t* threads;
		//线程池大小
		int size;
		//标志位
		bool destroy;
	public:
		//构造函数
		ThreadPool(int threadNum);
		//释放空间
		void stop();
		//添加任务
		int addAssignment(Assignment asg);
		//
		static void* thread_func(void* arg);
};

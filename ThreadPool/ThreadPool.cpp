#include <cassert>
#include "ThreadPool.h"


ThreadPool::ThreadPool(int threadNum)
{
	//
	pthread_mutex_init(&(this->queue_lock), NULL);
	pthread_cond_init(&(this->queue_ready), NULL);
	//
	this->destroy = 0;
	this->size = threadNum;
	//
	this->threads = (pthread_t *)malloc(threadNum * sizeof(pthread_t));
	for(int i = 0; i < threadNum; i++){
		int res = pthread_create(&this->threads[i], NULL, this->thread_func, NULL);
		if(res == -1)
			i--;
	}
}


void ThreadPool::stop()
{
	if(this->destroy)
		return;
	this->destroy = 1;

	//awake all threads which wait in this condition
	pthread_cond_broadcast(&(this->queue_ready));
	//
	for(int i = 0; i < this->size; i++)
		pthread_join(this->threads[i], NULL);
	free(this->threads);

	//destroy mutex and cond
	pthread_mutex_destroy(&(this->queue_lock));
	pthread_cond_destroy(&(this->queue_ready));
}


int ThreadPool::addAssignment(Assignment asg)
{
	//add lock
	pthread_mutex_lock(&(this->queue_lock));
	//adding...
	this->jobQueue.push(asg);
	cout << "cur_assignment_num: " << jobQueue.size() << endl;
	pthread_mutex_unlock(&(this->queue_lock));
	//awake a thread
	pthread_cond_signal(&(this->queue_ready));

	return this->jobQueue.size();
}


void* ThreadPool::thread_func(void* arg)
{
	pthread_t tid = pthread_self();
	ThreadPool* pool = static_cast<ThreadPool *>(arg);
	while(1){
		pthread_mutex_lock(&(pool->queue_lock));
		cout << "at work!" << endl;
		while(pool->jobQueue.size() == 0 && !pool->destroy)
			pthread_cond_wait(&(pool->queue_ready), &(pool->queue_lock));

		if(pool->destroy){
			pthread_mutex_unlock(&(pool->queue_lock));
			pthread_exit(NULL);
		}
		
		assert(pool->jobQueue.size() != 0);
		Assignment asg = pool->jobQueue.front();
		pool->jobQueue.pop();
		pthread_mutex_unlock(&(pool->queue_lock));

		//the work in details
		cout << asg.getRequest() << endl;

	}

}

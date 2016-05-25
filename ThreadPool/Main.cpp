#include "ThreadPool.h"

int main()
{
	ThreadPool threadPool(4);
	for(int i = 0; i < 100; i++){
		string str = "nihao";
		threadPool.addAssignment(str);
	}
	
	sleep(1);
	threadPool.stop();
		
	
	return 0;
}

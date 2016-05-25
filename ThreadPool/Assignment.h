#ifndef _ASSIGNMENT_H_
#define _ASSIGNMENT_H_

#include <string>
using namespace std;


/*
 * 任务类
 * 将任务抽象为该类
 */
class Assignment{
	private:
		//服务器端的任务实际上就是一个一个的字符串
		string requestStr;
		//将该字符串解析后实际需要的数据
		//string file;
	public:
		Assignment(){}
		Assignment(string url):requestStr(url){}
		Assignment(const Assignment& assignment){
			this->requestStr = assignment.requestStr;
		}
		//获取任务类的requestStr属性
		inline string getRequest(){
			return this->requestStr;
		}
		//设置任务类的requestStr属性
		inline void setRequest(string& request){
			this->requestStr = request;
		}
};



#endif

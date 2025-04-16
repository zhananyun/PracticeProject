#pragma once
#include <mutex>
#include <thread>
#include <vector>
#include <string>
#include <list>
#include <condition_variable>

class Task{
public:
    virtual int run()=0;
};

class ThreadPool{
public:
    void init(int threadNum);//初始化线程池
    void start();//启动线程池
    void addTask(Task* task);//添加任务
    Task* getTask();//获取任务
    void stop();//停止线程池
private:
    int thread_num_=0;//线程数量
    std::mutex mtx_;//互斥锁
    void run();//线程运行函数
    std::vector<std::thread*> threads_;//线程池
    std::list<Task*> tasks_;//任务队列
    std::condition_variable cv;//条件变量
    bool is_stop_=false;//是否停止
};
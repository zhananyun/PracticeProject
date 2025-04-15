#pragma once
#include <mutex>
#include <thread>
#include <vector>

class ThreadPool{
public:
    void init(int threadNum);//初始化线程池
    void start();//启动线程池
private:
    int thread_num_=0;//线程数量
    std::mutex mtx_;//互斥锁
    void run();//线程运行函数
    std::vector<std::thread*> threads_;//线程池
};
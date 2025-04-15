#include "thread_pool.h"
#include <iostream>
using namespace std;

// 线程池的初始化函数，用于设置线程池的线程数量。
void ThreadPool::init(int threadNum){
    cout<<"ThreadPool init begin..."<<endl;
    unique_lock<mutex> lck(mtx_);
    this->thread_num_=threadNum;
    cout<<"ThreadPool init end..."<<endl;
}

void ThreadPool::start(){
    unique_lock<mutex> lck(mtx_);
    cout<<"ThreadPool start begin..."<<endl;
    if(thread_num_<=0){
        cout<<"ThreadPool start error: thread_num_ <= 0"<<endl;
        return;
    }
    for(int i=0;i<thread_num_;++i){
        auto th=new thread(&ThreadPool::run,this);
        threads_.push_back(th);
    }
    cout<<"ThreadPool start end..."<<endl;
}

void ThreadPool::run(){
    cout<<"ThreadPool"<<this_thread::get_id()<<"run begin"<<endl;
    while(true){
        this_thread::sleep_for(chrono::seconds(1));
    }
    cout<<"ThreadPool"<<this_thread::get_id()<<"run end"<<endl;
}

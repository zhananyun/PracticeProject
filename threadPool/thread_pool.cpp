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
        unique_lock<mutex> lck(mtx_);
        auto task=getTask();
        if(!task){
            continue;
        }
        if(task->run()!=0){
            cout<<"ThreadPool run error: task->run() != 0"<<endl;
            continue;
        }

    }
    cout<<"ThreadPool"<<this_thread::get_id()<<"run end"<<endl;
}

void ThreadPool::addTask(Task* task){
    unique_lock<mutex> lck(mtx_);
    cout<<"ThreadPool addTask begin..."<<endl;
    tasks_.push_back(task);
    cout<<"ThreadPool addTask end..."<<endl;
    lck.unlock();
    cv.notify_one();
}

Task* ThreadPool::getTask(){
    unique_lock<mutex> lck(mtx_);
    cout<<"ThreadPool getTask begin..."<<endl;
    if(tasks_.empty()){
        cv.wait(lck);
        cout<<"ThreadPool getTask wait..."<<endl;
    }
    // if(is_stop_){
    //     cout<<"ThreadPool getTask is_stop_..."<<endl;
    //     return nullptr;
    // }
    Task* task=tasks_.front();
    tasks_.pop_front();
    cout<<"ThreadPool getTask end..."<<endl;
    return task;
}

void ThreadPool::stop(){
    cout<<"ThreadPool stop begin..."<<endl;
    is_stop_=true;
    cv.notify_all();
    for(auto th:threads_){
        th->join();
    }
    unique_lock<mutex> lck(mtx_);
    cout<<"ThreadPool stop clear..."<<endl;
    threads_.clear();
    cout<<"ThreadPool stop end..."<<endl;
    
    
    cout<<"ThreadPool stop all..."<<endl;
}

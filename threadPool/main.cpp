#include "thread_pool.h"
#include <iostream>
#include <thread>

class MyTask:public Task{
public:
    int run(){
        std::cout<<"MyTask run begin..."<<std::endl;
        std::cout<<"MyTask name_:"<<name_<<std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));
        std::cout<<"MyTask run end..."<<std::endl;
        return 0;
    }
    std::string name_="";
};
int main(){
    ThreadPool pool;
    pool.init(4);
    pool.start();

    MyTask* task1=new MyTask();
    task1->name_="任务a";
    pool.addTask(task1);
    MyTask* task2=new MyTask();
    task2->name_="任务b";
    pool.addTask(task2);
    
    // std::this_thread::sleep_for(std::chrono::seconds(3));
    // pool.stop();

    return 0;
}
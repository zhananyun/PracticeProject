#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>
#include <condition_variable>

using namespace std;

mutex mtx;
condition_variable cv;
bool ready=false;

void thraedA(int id){
    unique_lock<mutex> lck(mtx);
    while(!ready){
        cv.wait(lck);
    }
    cout<<"Thread "<<id<<" is running"<<endl;
}

void threadB(){
    cout<<"Initializing..."<<endl;
    this_thread::sleep_for(chrono::milliseconds(1000));
    {
        lock_guard<mutex> lck(mtx);
        ready=true;
        cout<<"Initialization complete"<<endl;
    }
    cv.notify_all();
}

int main(){
    thread t1(thraedA,1);
    thread t2(thraedA,2);
    thread t3(thraedA,3);
    thread t4(threadB);

    t1.join();
    t2.join();
    t3.join();
    t4.join();
    return 0;
}
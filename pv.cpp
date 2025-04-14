#include <iostream>
#include <thread>
#include <queue>
#include <condition_variable>
#include <mutex>
#include <chrono>

using namespace std;
mutex mtx;
condition_variable cv;
queue<int> q;

void producer(){
    for(int i=0;i<5;++i){
        unique_lock<mutex> lck(mtx);
        q.push(i);
        // lck.unlock();
        cv.notify_one();
        this_thread::sleep_for(chrono::milliseconds(100));
    }
}

void consumer(){
    while(true){
        unique_lock<mutex> lck(mtx);
        cv.wait(lck,[](){return !q.empty();});
        cout<<"consumer:"<<q.front()<<endl;
        q.pop();
        // lck.unlock();
        if(q.empty()){
            break;
        }
    }
}
int main(){
    thread t1(producer);
    thread t2(consumer);

    t1.join();
    t2.join();

    return 0;
}
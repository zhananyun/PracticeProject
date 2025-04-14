#include <iostream>
#include <thread>
#include <atomic>

using namespace std;

atomic<int> counter(0);
void increment(){
    counter++;
}
int main(){

    thread t1(increment);
    thread t2(increment);

    t1.join();
    t2.join();
    cout<<"counter:"<<counter<<endl;
    return 0;
}
#include <iostream>
#include <future>
#include <unistd.h>

using namespace std;

double add(const double a,const double b){
    double c=a+b;
    sleep(3);
    return c;
}
int main(){
    double a=3.0;
    double b=0.1415926;
    future<double> fut=async(add,a,b);//异步调用add函数
    cout<<"正在计算中......"<<endl;//主线程继续执行
    cout<<"请稍等...."<<endl;//主线程继续执行
    cout<<"计算结果为:a+b="<<fut.get()<<endl;//获取异步调用的结果,.get()只能调用一次，如果多次调用会抛出异常
    // fut.get(),如果不调用get()，主线程会一直等待
    return 0;
}
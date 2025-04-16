#include <iostream>
#include <chrono>
#include <thread>
#include "thread_pool.h"

void exampleTask() {
    std::cout << "Task "<<std::this_thread::get_id()<<" is running." << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::cout << "Task "<<std::this_thread::get_id()<<" is finished." << std::endl;
}

int main() {
    ThreadPool pool;
    pool.init(4);
    pool.start();

    for (int i = 0; i < 8; ++i) {
        pool.addTask(exampleTask);
    }

    std::this_thread::sleep_for(std::chrono::seconds(10));
    pool.stop();

    return 0;
}    
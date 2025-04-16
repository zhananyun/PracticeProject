#ifndef THREAD_POOL_H
#define THREAD_POOL_H

#include <vector>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <functional>

class ThreadPool {
public:
    // 初始化线程池，指定线程数量
    void init(size_t numThreads);
    // 启动线程池
    void start();
    // 向线程池添加任务
    void addTask(const std::function<void()>& task);
    // 停止线程池
    void stop();

private:
    // 工作线程函数
    void run();
    // 从任务队列获取任务
    std::function<void()> getTask();

    std::vector<std::thread> workers;
    std::queue<std::function<void()>> tasks;
    std::mutex queueMutex;
    std::condition_variable condition;
    bool isStopping;
    size_t numThreads;
};

#endif    
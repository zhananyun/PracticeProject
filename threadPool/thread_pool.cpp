#include "thread_pool.h"

void ThreadPool::init(size_t numThreads) {
    this->numThreads = numThreads;
    isStopping = false;
}

void ThreadPool::start() {
    for (size_t i = 0; i < numThreads; ++i) {
        workers.emplace_back([this] { this->run(); });
    }
}

void ThreadPool::addTask(const std::function<void()>& task) {
    {
        std::unique_lock<std::mutex> lock(queueMutex);
        tasks.push(task);
    }
    condition.notify_one();
}

void ThreadPool::stop() {
    {
        std::unique_lock<std::mutex> lock(queueMutex);
        isStopping = true;
    }
    condition.notify_all();
    for (std::thread& worker : workers) {
        if (worker.joinable()) {
            worker.join();
        }
    }
}

void ThreadPool::run() {
    while (true) {
        std::function<void()> task = getTask();
        if (!task && isStopping) {
            return;
        }
        if (task) {
            task();
        }
    }
}

std::function<void()> ThreadPool::getTask() {
    std::function<void()> task;
    std::unique_lock<std::mutex> lock(queueMutex);
    condition.wait(lock, [this] { return isStopping ||!tasks.empty(); });
    if (!tasks.empty()) {
        task = tasks.front();
        tasks.pop();
    }
    return task;
}    
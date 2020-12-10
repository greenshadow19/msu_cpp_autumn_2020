//
// Created by kirill on 10.12.2020.
//

#ifndef MSU_CPP_AUTUMN_2020_THREADPOOL_H
#define MSU_CPP_AUTUMN_2020_THREADPOOL_H

#include <queue>
#include <vector>
#include <mutex>
#include <condition_variable>
#include <functional>
#include <future>
#include <thread>

class ThreadPool {
private:
    std::condition_variable sync;
    std::vector<std::thread> pool;
    std::queue<std::function<void()>> taskQueue;
    std::mutex queueAccess;
    std::atomic<bool> isAlive;
    size_t sizeOfPool;

    template<class Func, class Promise, class... Args>
    void execTask(Func func, Promise promiseObject, Args... args) {
        promiseObject->set_value(func(args...));
        delete promiseObject;
    }

    template<class Func, class... Args>
    void execTask(Func func, std::promise<void> *promiseObject, Args... args) {
        func(args...);
        promiseObject->set_value();
        delete promiseObject;
    }

public:
    explicit ThreadPool(size_t poolSize) : isAlive(true), sizeOfPool(poolSize) {
        auto doTasks = [this]() {
            while (isAlive) {
                std::unique_lock<std::mutex> Lock(queueAccess);
                if (!taskQueue.empty()) {
                    std::function<void()> task(std::move(taskQueue.front()));
                    taskQueue.pop();
                    Lock.unlock();
                    task();
                } else
                    sync.wait(Lock, [this]() { return !isAlive || !taskQueue.empty(); });
            }

        };
        for (size_t i = 0; i < sizeOfPool; ++i) {
            pool.emplace_back(doTasks);
        }
    }

    ~ThreadPool() {
        join();
    }

    void join() {
        if (!isAlive)
            return;
        isAlive = false;
        sync.notify_all();

        for (size_t i = 0; i < sizeOfPool; ++i) {
            pool[i].join();
        }
    }

    template<class Func, class... Args>
    auto exec(Func func, Args... args) -> std::future<decltype(func(args...))> {
        auto promise = new std::promise<decltype(func(args...))>;
        auto future = promise->get_future();

        auto task = [this](Func func, std::promise<decltype(func(args...))> *promise, Args... args) {
            execTask(func, promise, args...);
        };

        queueAccess.lock();
        taskQueue.push(std::bind(task, func, promise, args...));
        queueAccess.unlock();

        sync.notify_one();
        return future;
    }

};


#endif //MSU_CPP_AUTUMN_2020_THREADPOOL_H

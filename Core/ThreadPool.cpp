/*
** EPITECH PROJECT, 2022
** threadpool
** File description:
** Implementing thread pool
*/

#include "ThreadPool.hpp"
#include "Core.hpp"

Zia::ThreadPool::ThreadPool() : max_worker(8), doesRun(true)
{
}

void Zia::ThreadPool::createWorker(int nbWorker)
{
    for (int i = 0; i < nbWorker; i++) {
        if ((workers.size() + 1) > max_worker) {
            Zia::Logger::Log(Zia::LoggerType::Error, "Can't create a new worker, you've reached the threshold.");
            break;
        }
        Zia::Logger::Log(Zia::LoggerType::Info, "Creating the thread n°" + std::to_string(workers.size()) + "...");
        std::thread worker(&ThreadPool::run_modules, this);
        workers.push_back(std::move(worker));
    }
}

bool const &Zia::ThreadPool::isRunning()
{
    return (doesRun);
}

void Zia::ThreadPool::stopThreadPool()
{
    std::unique_lock<std::mutex> _locker(_mutex);
    doesRun = false;
    _cond.notify_all();
    _locker.unlock();
    for (int i = 0; workers.size() > 0; i++) {
        if (workers[0].joinable()) {
            Zia::Logger::Log(Zia::LoggerType::Info, "Joining thread n°" + std::to_string(i + 1) + "...");
            workers[0].join();
            workers.erase(workers.begin());
        }
        else {
            Zia::Logger::Log(Zia::LoggerType::Error, "Waiting for thread n°" + std::to_string(i) + " to be joinable...");
        }
    }
    Zia::Logger::Log(Zia::LoggerType::Info, "Clearing the task list...");
    taskList.clear();
}

void Zia::ThreadPool::push(std::function<void ()> func)
{
    std::unique_lock<std::mutex> _lock(_mutex);
    taskList.push_back(func);
    _lock.unlock();
    _cond.notify_one();
}

std::function<void()> Zia::ThreadPool::pop()
{
    std::function<void()> func = taskList.front();
    taskList.erase(taskList.begin());
    return func;
}

void Zia::ThreadPool::run_modules()
{
    while (doesRun) {
        std::unique_lock<std::mutex> _locker(_mutex);
        if (taskList.empty()) {
            _cond.wait(_locker);
        }
        else {
            std::function<void ()> task = pop();
            _locker.unlock();
            task();
            Zia::Logger::Log(Zia::LoggerType::Info, "Task as ended.");
        }
    }
}

Zia::ThreadPool::~ThreadPool()
{
}

/*
** EPITECH PROJECT, 2022
** threadpool
** File description:
** Class for the threadPool
*/

#ifndef THREADPOOL_HPP_
#define THREADPOOL_HPP_

#include "Logger.hpp"

#include <string>
#include <vector>
#include <mutex>
#include <condition_variable>
#include <iostream>
#include <cstdint> 
#include <iostream>
#include <list>
#include <memory>
#include <thread>
#include <functional>
namespace Zia {
    class ThreadPool {
        public:
            ThreadPool();
            ~ThreadPool();
            /*
             * Function used to create the number of workers given in parameters.
             * You cannot create more workers than the "max_workers" number.
             */
            void createWorker(int nbWorker);
            /*
             * Function to push a function in the task list.
             */
            void push(std::function<void()>);
            /*
             * Function to pop the first function in the task list, and returns it.
             */
            std::function<void()> pop();
            /*
             * Function to join all the thread, and clear the task list.
             */
            void stopThreadPool();
            /*
             * Check if the threadPool is running.
             */
            bool const &isRunning();
        protected:
        private:
            bool doesRun;
            /*
             * The list of all the thread up and running.
             */
            std::vector<std::thread> workers;
            int max_worker;
            std::mutex _mutex;
            std::condition_variable _cond;
            /*
             * The list of the function that need to be runned by the workers.
             */
            std::vector<std::function<void()>> taskList;
            /*
             * The function runned by all the worker.
             * This function pop the taskList it's not empty.
             * Then a worker run the function that has been poped.
             * If the task list is empty, this function put the worker in a waiting state.
             */
            void run_modules();
    };
}

#endif /* !THREADPOOL_HPP_ */

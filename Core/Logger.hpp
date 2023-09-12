/*
** EPITECH PROJECT, 2022
** B-YEP-500-NCY-5-1-zia-tom.wederich
** File description:
** Logger
*/

#pragma once

#include <string>
#include <iostream>
#include <chrono>
#include <ctime>
#include <algorithm>

namespace Zia {
    // The enumeration for all the message types
    enum LoggerType {
        Trace,
        Debug,
        Info,
        Warning,
        Error,
        Fatal
    };
    class Logger {
        public:
            Logger();
            ~Logger();

            static void Log(LoggerType type, std::string const &msg); // The function to log something. It takes as parameters a Zia::LoggerType, and the log message
        protected:
        private:
    };
}
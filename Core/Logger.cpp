/*
** EPITECH PROJECT, 2022
** B-YEP-500-NCY-5-1-zia-tom.wederich
** File description:
** Logger
*/

#include "Logger.hpp"

Zia::Logger::Logger()
{
}

Zia::Logger::~Logger()
{
}

void Zia::Logger::Log(Zia::LoggerType type, std::string const &name)
{
    auto end = std::chrono::system_clock::now();
    std::time_t end_time = std::chrono::system_clock::to_time_t(end);
    auto time = std::ctime(&end_time);
    std::string sp = time;
    sp.erase(std::remove(sp.begin(), sp.end(), '\n'), sp.end());

    if (type == Zia::LoggerType::Trace) {
        std::cout << "\033[1;37m" + sp + " [TRACE] " + name + "\033[0m" << std::endl;
    }
    if (type == Zia::LoggerType::Debug) {
        std::cout << "\033[1;32m" + sp + " [DEBUG] " + name + "\033[0m" << std::endl;
    }
    if (type == Zia::LoggerType::Info) {
        std::cout << "\033[1;37m" + sp + " [INFO] " + name + "\033[0m" << std::endl;
    }
    if (type == Zia::LoggerType::Warning) {
        std::cout << "\033[1;35m" + sp + " [WARNING] " + name + "\033[0m" << std::endl;
    }
    if (type == Zia::LoggerType::Error) {
        std::cout << "\033[1;31m" + sp + " [ERROR] " +  name + "\033[0m" << std::endl;
    }
    if (type == Zia::LoggerType::Fatal) {
        std::cout << "\033[1;31m" + sp + " [FATAL] " + name  + "\033[0m" << std::endl;
    }
}

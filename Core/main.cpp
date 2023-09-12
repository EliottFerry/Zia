#include <iostream>
#include <boost/asio.hpp>
#include <boost/dll.hpp>
#include <boost/function.hpp>
#include "../Modules/IModules.hpp"
#include <boost/dll/shared_library.hpp>
#include <boost/dll/runtime_symbol_info.hpp>
#include "Core.hpp"
#include "ModuleLoader.hpp"
#include <boost/thread/thread.hpp>
#include "fatalException.hpp"
#include "Logger.hpp"

int main()
{
    try {
        Zia::Core core;
        core.CoreManager();
    }
    catch(const Zia::fatalException &e) {
        Zia::Logger::Log(Zia::Fatal, e.what());
        Zia::Logger::Log(Zia::Fatal, "Error function : " + static_cast<std::string>(e.getErrorFunction()));
    } 
    return (0);
}
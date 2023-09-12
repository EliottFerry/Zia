/*
** EPITECH PROJECT, 2022
** ModuleLoader
** File description:
** The implementation of the module loader class
*/

#include "ModuleLoader.hpp"
#include "../Core/fatalException.hpp"
#include <iostream>

Zia::ModuleLoader::ModuleLoader()
{
}

boost::function<boost::shared_ptr<Zia::IModules>()> Zia::ModuleLoader::load(const std::string &path, const std::string &name)
{
    try {
        std::cout << path << std::endl;
        boost::dll::shared_library lib(path);
        moduleList[name] = lib;
        boost::function<boost::shared_ptr<Zia::IModules>()> func = moduleList[name].get_alias<boost::shared_ptr<Zia::IModules>()>("createModule");
        Zia::Logger::Log(Zia::LoggerType::Info, "Module loaded " + name);
        return (func);
    }
    catch(...) {
        throw(Zia::fatalException("The library that you try to load may not exist. Path given : " + path + "\nIt's also possible that the alias 'createModule' does not exist in your module.", "Zia::ModuleLoader::load"));
    }
}

boost::function<boost::shared_ptr<Zia::IModules>()> Zia::ModuleLoader::getModule(std::string const &name)
{
    try {
        boost::function<boost::shared_ptr<Zia::IModules>()> func = moduleList[name].get_alias<boost::shared_ptr<Zia::IModules>()>("createModule");
        return (func);
    }
    catch(...) {
        throw(Zia::fatalException("The alias 'createModule' does not exist in the module named : " + name, "Zia::ModuleLoader::getModule"));
    }
}

void Zia::ModuleLoader::unload(std::string const &name)
{
    moduleList[name].unload();
}

bool Zia::ModuleLoader::isLoaded(std::string const &name)
{
    return (moduleList[name].is_loaded());
}

Zia::ModuleLoader::~ModuleLoader()
{
}

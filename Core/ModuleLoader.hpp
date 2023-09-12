/*
** EPITECH PROJECT, 2022
** ModuleLoader
** File description:
** The class for the module loader
*/

#ifndef MODULELOADER_HPP_
#define MODULELOADER_HPP_

#include "../Modules/IModules.hpp"
#include "Logger.hpp"
#include <map>
#include <boost/dll/shared_library.hpp>
#include <boost/function.hpp>
#include <boost/dll/runtime_symbol_info.hpp>

namespace Zia {
    class ModuleLoader {
        public:
            ModuleLoader();
            /*
             * Used to load a module. The "name" parameter is the name where the module will be stored in the map 
             */
            boost::function<boost::shared_ptr<IModules>()> load(std::string const &path, const std::string &name);
            /*
             * Function used to unload the module.
             */
            void unload(std::string const &name);
            /*
             * Return a function to call the IModules members.
             */
            boost::function<boost::shared_ptr<IModules>()> getModule(std::string const &name);
            /*
             * Check if the module if loaded.
             */
            bool isLoaded(std::string const &name);
            ~ModuleLoader();

        protected:
        private:
            /*
             * The map of all the modules. 
             */
            std::map<std::string, boost::dll::shared_library> moduleList;
    };
}

#endif /* !MODULELOADER_HPP_ */

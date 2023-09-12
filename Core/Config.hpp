/*
** EPITECH PROJECT, 2022
** B-YEP-500-NCY-5-1-zia-tom.wederich
** File description:
** Config
*/

#ifdef __linux__ 
    #define FILE_EXTENSION ".so"
#elif _WIN32
    #define FILE_EXTENSION ".dll"
#else
    #error "OS NOT SUPPORTED"
#endif

#ifndef CONFIG_HPP_
#define CONFIG_HPP_

#include <iostream>
#include <string>
#include <list>
#include <sys/stat.h>
#include <fstream>
#include <iterator>
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>
#include "Logger.hpp"
#include <boost/filesystem.hpp>
#include "../Modules/IModules.hpp"
namespace Zia {
    class Config {
        public:
            Config();
            ~Config();

            bool LoadConfig(const std::string &);
            std::string const &getPassword();
            std::string const &getModulePath();
            std::list<std::string> const &getModuleList();
            std::string const &getCertPath();
            std::string const &getKeyPath();
            unsigned int &getPort();
        protected:
        private:
            std::list<std::string> ModuleList;
            std::string ModulePath;
            unsigned int port;
            std::string certif_path;
            std::string password;
            std::string key_path;
            bool isDir(const std::string &in_name);
            bool readJsonFile(const std::string &path, const std::string &dir_path);
            bool loadDefaultConfig();
    };
}

#endif /* !CONFIG_HPP_ */

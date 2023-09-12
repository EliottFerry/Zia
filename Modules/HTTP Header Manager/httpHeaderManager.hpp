    /*
** EPITECH PROJECT, 2022
** httpHeaderManager
** File description:
** The header manager module
*/

#ifndef HTTPHEADERMANAGER_HPP_
#define HTTPHEADERMANAGER_HPP_

#ifdef __linux__ 
    #define FILE_PATH ""
#elif _WIN32
    #define FILE_PATH "../"
#else
    #error "OS NOT SUPPORTED"
#endif

#include <iostream>
#include <boost/make_shared.hpp>
#include <filesystem>
#include <fstream>
#include <stdio.h>
#include "../IModules.hpp"

namespace Zia
{
    class httpHeaderManager : public IModules
    {
        private:
            bool methodGet(Network::Request &req, Network::Response &res);
            bool methodHead(Network::Request &req, Network::Response &res);
            bool methodPost(Network::Request &req, Network::Response &res);
            bool methodPut(Network::Request &req, Network::Response &res);
            bool methodDelete(Network::Request &req, Network::Response &res);
            bool methodConnect(Network::Request &req, Network::Response &res);
            bool methodOptions(Network::Request &req, Network::Response &res);
            bool methodTrace(Network::Request &req, Network::Response &res);
            bool methodPatch(Network::Request &req, Network::Response &res);
        public:
            httpHeaderManager();
            std::string const getModuleName();
            bool runModule(Network::Request &req, Network::Response &res);
            ~httpHeaderManager();
    };
    boost::shared_ptr<IModules> createModule() {
        return boost::make_shared<httpHeaderManager>();
    }
}

BOOST_DLL_ALIAS(
    Zia::createModule,
    createModule
)

#endif /* !HTTPHEADERMANAGER_HPP_ */

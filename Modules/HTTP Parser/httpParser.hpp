/*
** EPITECH PROJECT, 2022
** httpParser
** File description:
** The module to parse http message for the Zia project
*/

#ifndef HTTPPARSER_HPP_
#define HTTPPARSER_HPP_

#include <iostream>
#include <boost/config.hpp>
#include <boost/make_shared.hpp>
#include "../IModules.hpp"

namespace Zia
{
    class httpParser : public IModules
    {
        private:
        public:
            httpParser();
            std::string const getModuleName();
            bool runModule(Network::Request &req, Network::Response &res);
            ~httpParser();
    };
    boost::shared_ptr<IModules> createModule() {
        return boost::make_shared<httpParser>();
    }
}

BOOST_DLL_ALIAS(
    Zia::createModule,
    createModule
)

#endif /* !HTTPPARSER_HPP_ */

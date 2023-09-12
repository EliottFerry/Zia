/*
** EPITECH PROJECT, 2022
** httpResponseCreator
** File description:
** The response creator for the Zia project
*/

#ifndef HTTPRESPONSECREATOR_HPP_
#define HTTPRESPONSECREATOR_HPP_

#include <iostream>
#include <boost/make_shared.hpp>
#include <map>
#include "../IModules.hpp"

namespace Zia
{
    class httpReponseCreator : public Zia::IModules
    {
        private:
        public:
            httpReponseCreator();
            std::string const getModuleName();
            bool runModule(Network::Request &req, Network::Response &res);
            ~httpReponseCreator();
    };
    boost::shared_ptr<Zia::IModules> createModule() {
        return boost::make_shared<httpReponseCreator>();
    }
}

BOOST_DLL_ALIAS(
    Zia::createModule,
    createModule
)

#endif /* !HTTPRESPONSECREATOR_HPP_ */

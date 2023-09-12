/*
** EPITECH PROJECT, 2022
** IModules.hpp
** File description:
** The interface for all the modules
*/

#ifndef IMODULES_HPP_
#define IMODULES_HPP_

#include <boost/dll/alias.hpp>
#include <boost/shared_ptr.hpp>
#include "../Communication/Response.hpp"
#include "../Communication/Request.hpp"
#include "../Core/Logger.hpp"
#include <string>

namespace Zia {
    class IModules {
        public:
            virtual std::string const getModuleName() = 0;
            virtual bool runModule(Network::Request &req, Network::Response &res) = 0;

            virtual ~IModules() {}

        protected:
        private:
    };
}

#endif /* !IMODULES_HPP_ */

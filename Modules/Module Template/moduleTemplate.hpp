#include <iostream>
#include <boost/config.hpp>
#include <boost/make_shared.hpp>
#include "../IModules.hpp"

namespace Zia
{
    class moduleTemplate : public IModules
    {
    private:
    public:
        moduleTemplate();
        const std::string getModuleName();
        bool runModule(Network::Request &req, Network::Response &res);
        ~moduleTemplate();
    };
    /*
     * Returns a shared pointer of the module.
     */
    boost::shared_ptr<IModules> createModule() {
        return boost::make_shared<moduleTemplate>();
    }
}

BOOST_DLL_ALIAS(
    Zia::createModule,
    createModule
)
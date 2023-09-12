#include <iostream>
#include <boost/config.hpp>
#include <boost/make_shared.hpp>
#include <boost/algorithm/string.hpp>
#include "../IModules.hpp"
#include <boost/process.hpp>
#include <experimental/filesystem>
#include <string>

#ifdef __linux__ 
    #define CGIPATH "./executables/php-cgi7.4"
#elif _WIN32
    #define CGIPATH "./executables/php-cgi.exe"
#else
    #error "OS NOT SUPPORTED"
#endif

namespace Zia
{
    class PhpCgiManager : public IModules
    {
    private:
        boost::process::environment buildEnv(Network::Request &req, Network::Response &res);
    public:
        PhpCgiManager();
        const std::string getModuleName();
        bool runModule(Network::Request &req, Network::Response &res);
        ~PhpCgiManager();
    };
    /*
     * Returns a shared pointer of the module.
     */
    boost::shared_ptr<IModules> createModule() {
        return boost::make_shared<PhpCgiManager>();
    }
}

BOOST_DLL_ALIAS(
    Zia::createModule,
    createModule
)
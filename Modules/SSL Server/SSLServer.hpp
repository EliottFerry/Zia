#include "../../Core/Config.hpp"
#include <iostream>
#include <boost/config.hpp>
#include <boost/make_shared.hpp>
#include "../IModules.hpp"
#include <openssl/ssl.h>
#include <openssl/err.h>
#include <sys/socket.h>
#include <arpa/inet.h>

namespace Zia
{
    class SSLServer : public IModules
    {
    private:
        SSL_CTX *ctx;
        int sock;
        Config config;
    public:
        SSLServer();
        ~SSLServer();
        const std::string getModuleName();
        bool runModule(Network::Request &req, Network::Response &res);
        SSL_CTX *create_context();
        int create_socket(int port);
        void configure_context();
        void listen_();
    };
    /*
     * Returns a shared pointer of the module.
     */
    boost::shared_ptr<IModules> createModule() {
        return boost::make_shared<SSLServer>();
    }
}

BOOST_DLL_ALIAS(
    Zia::createModule,
    createModule
)
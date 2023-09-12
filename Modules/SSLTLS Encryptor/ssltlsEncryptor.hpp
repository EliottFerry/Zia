/*
** EPITECH PROJECT, 2022
** ssltls Encryptor
** File description:
** The module to encrypt message
*/

#ifndef SSLTLSENCRYPTOR_HPP_
#define SSLTLSENCRYPTOR_HPP_

#include <iostream>
#include <boost/config.hpp>
#include <boost/make_shared.hpp>
#include "../IModules.hpp"
#include "openssl/rsa.h"
#include "openssl/pem.h"
#include "openssl/bio.h"

namespace Zia
{
    class SSLTLSEncryptor : public IModules
    {
    private:
    public:
        SSLTLSEncryptor();
        ~SSLTLSEncryptor();
        const std::string getModuleName();
        bool runModule(Network::Request &req, Network::Response &res);
        RSA *createPublicKey(std::string key);
        unsigned char *encrypt(std::string privateKey, std::string message);
    };
    boost::shared_ptr<IModules> createModule() {
        return boost::make_shared<SSLTLSEncryptor>();
    }
}

BOOST_DLL_ALIAS(
    Zia::createModule,
    createModule
)

#endif /* !SSLTLSENCRYPTOR_HPP_ */

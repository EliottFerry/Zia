/*
** EPITECH PROJECT, 2022
** ssltls Encryptor
** File description:
** The module to encrypt message
*/

#ifndef SSLTLSDECRYPTOR_HPP_
#define SSLTLSDECRYPTOR_HPP_

#include <iostream>
#include <boost/config.hpp>
#include <boost/make_shared.hpp>
#include "../IModules.hpp"
#include "openssl/rsa.h"
#include "openssl/pem.h"
#include "openssl/bio.h"

namespace Zia
{
    class SSLTLSDecryptor : public IModules
    {
    private:
    public:
        SSLTLSDecryptor();
        ~SSLTLSDecryptor();
        const std::string getModuleName();
        bool runModule(Network::Request &req, Network::Response &res);
        static int rsa_cb(char *buf, int size, int rwflag, void *u);
        RSA *createPrivateKey(std::string key);
        unsigned char *decrypt(std::string privateKey, unsigned char *message);
    };
    boost::shared_ptr<IModules> createModule() {
        return boost::make_shared<SSLTLSDecryptor>();
    }
}

BOOST_DLL_ALIAS(
    Zia::createModule,
    createModule
)

#endif /* !SSLTLSDECRYPTOR_HPP_ */

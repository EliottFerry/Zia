/*
** EPITECH PROJECT, 2022
** ssltlsEncryptor
** File description:
** The implementation of the ssltls Class
*/

#include "ssltlsEncryptor.hpp"

Zia::SSLTLSEncryptor::SSLTLSEncryptor(/* args */)
{
}

const std::string Zia::SSLTLSEncryptor::getModuleName()
{
    return ("SSLTLS Encryptor");
}

bool Zia::SSLTLSEncryptor::runModule(Network::Request &req, Network::Response &res)
{
    return (true);
}

RSA *Zia::SSLTLSEncryptor::createPublicKey(std::string key)
{
    RSA *rsa = NULL;
    BIO *keybio;
    const char* c_string = key.c_str();
    keybio = BIO_new_mem_buf((void*)c_string, -1);
    if (keybio==NULL)
        return 0;
    rsa = PEM_read_bio_RSA_PUBKEY(keybio, &rsa,NULL, NULL);

    return rsa;
}

unsigned char *Zia::SSLTLSEncryptor::encrypt(std::string publicKey, std::string message)
{
  RSA *privateRSA = createPublicKey(publicKey);
  int flen = RSA_size(privateRSA);
  unsigned char *out; 
  unsigned char *in = reinterpret_cast<unsigned char*>(const_cast<char*>(message.c_str()));
  int test = RSA_private_decrypt(flen, in, out, privateRSA, RSA_NO_PADDING);

  return out;
}

Zia::SSLTLSEncryptor::~SSLTLSEncryptor()
{
}
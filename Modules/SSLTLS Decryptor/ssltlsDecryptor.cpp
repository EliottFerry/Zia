/*
** EPITECH PROJECT, 2022
** SSLTLSDecryptor
** File description:
** The implementation of the ssltls Class
*/

#include "ssltlsDecryptor.hpp"

Zia::SSLTLSDecryptor::SSLTLSDecryptor(/* args */)
{
}

const std::string Zia::SSLTLSDecryptor::getModuleName()
{
    return ("SSLTLS Decryptor");
}

bool Zia::SSLTLSDecryptor::runModule(Network::Request &req, Network::Response &res)
{
    return (true);
}

int Zia::SSLTLSDecryptor::rsa_cb(char *buf, int size, int rwflag, void *u)
{
    int len;
    // Password mis en dure ici :/
    char const *password = "zia1234";

    len = strlen(password);

    if (len <= 0)
        return 0;

    if (len > size)
        len = size;

    memcpy(buf, password, len);

    return len;
}

RSA* Zia::SSLTLSDecryptor::createPrivateKey(std::string key) {
    RSA *rsa = NULL;
    const char* c_string = key.c_str();
    BIO * keybio = BIO_new_mem_buf((void*)c_string, -1);
    if (keybio==NULL) {
        return 0;
    }
    rsa = PEM_read_bio_RSAPrivateKey(keybio, &rsa, (pem_password_cb *) rsa_cb, NULL);
    return rsa;
}

unsigned char *Zia::SSLTLSDecryptor::decrypt(std::string privateKey, unsigned char *message)
{
    RSA *privateRSA = createPrivateKey(privateKey);
    int flen = RSA_size(privateRSA);
    unsigned char *out; 
    int res = RSA_private_decrypt(flen, message, out, privateRSA, RSA_NO_PADDING);

    if (res == -1) {
        //Gestion d'erreur ici !
    }
    return out;
}

Zia::SSLTLSDecryptor::~SSLTLSDecryptor()
{
}
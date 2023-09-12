#include "SSLServer.hpp"
#include <sys/socket.h>

Zia::SSLServer::SSLServer(/* args */)
{
    ctx = create_context();
    sock = create_socket(8080);
    configure_context();
}

const std::string Zia::SSLServer::getModuleName()
{
    return ("SSLServer");
}

bool Zia::SSLServer::runModule(Network::Request &req, Network::Response &res)
{
    return (true);
}

SSL_CTX *Zia::SSLServer::create_context(void)
{
    const SSL_METHOD *method;
    SSL_CTX *ctx;

    method = TLS_server_method();

    ctx = SSL_CTX_new(method);
    if (!ctx) {
        perror("Unable to create SSL context");
        ERR_print_errors_fp(stderr);
        exit(EXIT_FAILURE);
    }

    return ctx;
}

int Zia::SSLServer::create_socket(int port)
{
    int s;
    struct sockaddr_in addr;

    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = htonl(INADDR_ANY);

    s = socket(AF_INET, SOCK_STREAM, 0);
    if (s < 0) {
        perror("Unable to create socket");
        exit(EXIT_FAILURE);
    }

    if (bind(s, (struct sockaddr*)&addr, sizeof(addr)) < 0) {
        perror("Unable to bind");
        exit(EXIT_FAILURE);
    }

    if (listen(s, 1) < 0) {
        perror("Unable to listen");
        exit(EXIT_FAILURE);
    }

    return s;
}

void Zia::SSLServer::configure_context(void)
{
    /* Set the key and cert */
    if (SSL_CTX_use_certificate_file(ctx, config.getCertPath().c_str(), SSL_FILETYPE_PEM) <= 0) {
        ERR_print_errors_fp(stderr);
        exit(EXIT_FAILURE);
    }

    if (SSL_CTX_use_PrivateKey_file(ctx, config.getKeyPath().c_str(), SSL_FILETYPE_PEM) <= 0 ) {
        ERR_print_errors_fp(stderr);
        exit(EXIT_FAILURE);
    }
}

void Zia::SSLServer::listen_(void)
{
    struct sockaddr_in addr;
    unsigned int len = sizeof(addr);
    SSL *ssl;
    const char reply[] = "yolo\n";

    int client = accept(sock, (struct sockaddr*)&addr, &len);
    if (client < 0) {
        perror("Unable to accept");
        exit(EXIT_FAILURE);
    }

    ssl = SSL_new(ctx);
    SSL_set_fd(ssl, client);

    if (SSL_accept(ssl) <= 0) {
        ERR_print_errors_fp(stderr);
    } else {
        SSL_write(ssl, reply, strlen(reply));
    }

    SSL_shutdown(ssl);
    SSL_free(ssl);
    close(client);
    listen_();
}

Zia::SSLServer::~SSLServer()
{
    close(sock);
    SSL_CTX_free(ctx);
}
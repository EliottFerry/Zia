/*
** EPITECH PROJECT, 2022
** B-YEP-500-NCY-5-1-zia-tom.wederich
** File description:
** Core
*/

#ifdef __linux__ 
    #define FILE_EXTENSION ".so"
    #define SEARCH_EXTENSION "."
#elif _WIN32
    #define FILE_EXTENSION ".dll"
    #define SEARCH_EXTENSION "../"
#else
    #error "OS NOT SUPPORTED"
#endif

#ifndef CORE_HPP_
#define CORE_HPP_

#include "Config.hpp"
#include "Logger.hpp"
#include "ModuleLoader.hpp"
#include "../Communication/Response.hpp"
#include "ThreadPool.hpp"
#include <boost/asio/ssl.hpp>

#include <string>
#include <vector>
#include <iostream>
#include <boost/asio.hpp> 
#include <functional>
#include <cstdint> 
#include <iostream>
#include <list>
#include <memory>
#include <thread>

namespace Zia {
    struct Connection {
        boost::asio::ip::tcp::socket socket;
        boost::asio::streambuf read_buffer;
        Connection(boost::asio::io_service &io_service) : socket(io_service), read_buffer() {
        }
        Connection(boost::asio::io_service &io_service, size_t max_buffer_size) : socket(io_service), read_buffer(max_buffer_size) {
        }
    };
}

namespace Zia {
    class Core {
        boost::asio::io_service m_ioservice;
        boost::asio::ip::tcp::acceptor m_acceptor;
        std::list<Connection> m_connections;
        using con_handle_t = std::list<Connection>::iterator;
        public:
            Core();
            ~Core();

            void CoreManager();
            void run_modules(Network::Request &req, con_handle_t &con_handle);
        protected:
        private:
            Config config;
            ModuleLoader moduleLoader;
            ThreadPool threadPool;
            void listen(uint16_t port);
            void handle_read(con_handle_t &con_handle, boost::system::error_code const &err, size_t bytes_transfered);
            void do_async_read(con_handle_t &con_handle);
            void handle_write(con_handle_t &con_handle, std::shared_ptr<std::string> &msg_buffer, boost::system::error_code const &err);
            void handle_accept(con_handle_t &con_handle, boost::system::error_code const &err);
            void start_accept();
            void send(con_handle_t &con_handle, Network::Response &res);
            void run();
            void stop_server();
            std::vector<std::string> msg;
            std::vector<std::string> resSend;
            std::thread endingThread;
    };
}

#endif /* !CORE_HPP_ */

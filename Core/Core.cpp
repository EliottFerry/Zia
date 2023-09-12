/*
** EPITECH PROJECT, 2022
** B-YEP-500-NCY-5-1-zia-tom.wederich
** File description:
** Core
*/

#include "Core.hpp"

Zia::Core::Core() : m_ioservice(), m_acceptor(m_ioservice), m_connections()
{
}

Zia::Core::~Core()
{
}

void Zia::Core::CoreManager()
{
    if (!config.LoadConfig(SEARCH_EXTENSION)) {
        return;
    }
    for (auto &c : config.getModuleList()) {
        moduleLoader.load(config.getModulePath() + "/" + c + FILE_EXTENSION, c);
    }
    listen(config.getPort());
    threadPool.createWorker(8);
    std::thread a(&Core::stop_server, this);
    endingThread = std::move(a);
    run();
}

void Zia::Core::stop_server()
{
    while (threadPool.isRunning())
    {
        std::string inputLine;
        std::getline(std::cin, inputLine);
        std::for_each(inputLine.begin(), inputLine.end(), [](char &c)
                      { c = std::tolower(c); });
        if (inputLine == "stop")
        {
            Zia::Logger::Log(Zia::LoggerType::Info, "Stopping the server...");
            threadPool.stopThreadPool();
            m_ioservice.stop();
        }
    }
}

void Zia::Core::handle_read(con_handle_t &con_handle, boost::system::error_code const &err, size_t bytes_transfered)
{
    if (bytes_transfered > 0)
    {
        std::istream is(&con_handle->read_buffer);
        std::string line;
        std::getline(is, line);
        msg.push_back(line);
        if (line.length() == 1)
        {
            Network::Request req;
            std::vector<std::string> brain;
            for (auto &i : msg)
            {
                brain.push_back(i);
            }
            msg.clear();
            req.setRequest(brain);
            threadPool.push(std::bind(&Core::run_modules, this, req, con_handle));
        }
    }
    if (!err)
    {
        do_async_read(con_handle);
    }
    else
    {
        std::cerr << "We had an error: " << err.message() << std::endl;
        m_connections.erase(con_handle);
    }
}

void Zia::Core::do_async_read(con_handle_t &con_handle)
{
    auto handler = boost::bind(&Zia::Core::handle_read, this, con_handle, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred);
    boost::asio::async_read_until(con_handle->socket, con_handle->read_buffer, "\n", handler);
}

void Zia::Core::handle_write(con_handle_t &con_handle, std::shared_ptr<std::string> &msg_buffer, boost::system::error_code const &err)
{
    if (!err)
    {
        if (con_handle->socket.is_open())
        {
            std::cout << "Connection is successfull" << std::endl;
        }
    }
    else
    {
        std::cerr << "We had an error: " << err.message() << std::endl;
        m_connections.erase(con_handle);
    }
}

void Zia::Core::handle_accept(con_handle_t &con_handle, boost::system::error_code const &err)
{
    start_accept();
    if (!err)
    {
        std::cout << "Connection from: " << con_handle->socket.remote_endpoint().address() << "\n";
        do_async_read(con_handle);
    }
    else
    {
        std::cerr << "We had an error: " << err.message() << std::endl;
        m_connections.erase(con_handle);
    }
}

void Zia::Core::send(con_handle_t &con_handle, Network::Response &res)
{
    auto buff = std::make_shared<std::string>(res.getBody());
    auto handler = boost::bind(&Zia::Core::handle_write, this, con_handle, buff, boost::asio::placeholders::error);
    std::cout << "------------------------NEW ANSWER------------------------" << std::endl
              << res.getBody() << std::endl;
    boost::asio::async_write(con_handle->socket, boost::asio::buffer(*buff), handler);
}

void Zia::Core::start_accept()
{
    auto con_handle = m_connections.emplace(m_connections.begin(), m_ioservice);
    auto handler = boost::bind(&Zia::Core::handle_accept, this, con_handle, boost::asio::placeholders::error);
    m_acceptor.async_accept(con_handle->socket, handler);
}

void Zia::Core::listen(uint16_t port)
{
    auto endpoint = boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port);
    m_acceptor.open(endpoint.protocol());
    m_acceptor.set_option(boost::asio::ip::tcp::acceptor::reuse_address(true));
    m_acceptor.bind(endpoint);
    m_acceptor.listen();
    start_accept();
}

void Zia::Core::run()
{
    m_ioservice.run();
    if (endingThread.joinable())
    {
        endingThread.join();
    }
}

void Zia::Core::run_modules(Network::Request &req, con_handle_t &con_handle)
{
    Network::Response res;
    for (auto &c : config.getModuleList())
    {
        auto b = moduleLoader.getModule(c);
        b()->runModule(req, res);
    }
    int x = res.getStatusCode();
    std::string headers = std::string("HTTP/1.1 ") + std::to_string(x);
    headers += "\n";
    for (auto &c : res.getHeaders())
        headers += c + "\n";
    res.setBody(headers + "Connection: Closed\n\n" + res.getBody());
    send(con_handle, res);
}
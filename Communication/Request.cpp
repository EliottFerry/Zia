/*
** EPITECH PROJECT, 2022
** B-YEP-500-NCY-5-1-zia-tom.wederich
** File description:
** Request
*/

#include "Request.hpp"

Network::Request::Request()
{
}

Network::Request::~Request()
{
}

void Network::Request::setURL(const std::string &_url)
{
    URL = _url;
}

void Network::Request::setMethod(const std::string &_method)
{
    method = _method;
}

std::string &Network::Request::getURL()
{
    return URL;
}

std::string &Network::Request::getMethod()
{
    return method;
}

void Network::Request::setRequest(const std::vector<std::string> &req)
{
    request = req;
}

std::vector<std::string> &Network::Request::getRequest()
{
    return request;
}

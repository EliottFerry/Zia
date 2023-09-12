/*
** EPITECH PROJECT, 2022
** B-YEP-500-NCY-5-1-zia-tom.wederich
** File description:
** Response
*/

#include "Response.hpp"

Network::Response::Response()
{
}

Network::Response::~Response()
{
}

void Network::Response::SetStatusCode(Network::Response::StatusCode const &stat)
{
    statCode = stat;
}

void Network::Response::SetStatusMsg(std::string const &statmsg)
{
    status = statmsg;
}

void Network::Response::setHeaders(std::vector<std::string> const &head)
{
    headers = head;
}

void Network::Response::addHeaders(std::string const &head)
{
    headers.push_back(head);
}


void Network::Response::setBody(std::string const &bod)
{
    body = bod;
}

std::vector<std::string> const &Network::Response::getHeaders()
{
    return headers;
}

std::string const &Network::Response::getBody()
{
    return body;
}

std::string const &Network::Response::getStatusMsg()
{
    return status;
}

Network::Response::StatusCode const &Network::Response::getStatusCode()
{
    return statCode;
}

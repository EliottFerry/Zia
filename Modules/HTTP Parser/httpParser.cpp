/*
** EPITECH PROJECT, 2022
** httpParser
** File description:
** The implementation of the http Parser
*/

#include "httpParser.hpp"

Zia::httpParser::httpParser()
{
}

const std::string Zia::httpParser::getModuleName()
{
    return ("HTTP Parser");
}

bool Zia::httpParser::runModule(Network::Request &req, Network::Response &res)
{
    req.setMethod(req.getRequest()[0].substr(0, req.getRequest()[0].find(" ")));
    if (std::find(req.Methods.begin(), req.Methods.end(), req.getMethod()) == req.Methods.end()) {
        Zia::Logger::Log(Zia::LoggerType::Error, "Invalid HTTP Method used: " + req.getMethod());
        return (false);
    }
    std::string str = req.getRequest()[0].erase(0, req.getMethod().length() + 1);
    str = str.substr(0,  str.find(" "));
    req.setURL(str);
    return (true);
}

Zia::httpParser::~httpParser()
{
}
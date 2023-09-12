#include "moduleTemplate.hpp"

Zia::moduleTemplate::moduleTemplate(/* args */)
{
}

const std::string Zia::moduleTemplate::getModuleName()
{
    return ("Module Template Name");
}

bool Zia::moduleTemplate::runModule(Network::Request &req, Network::Response &res)
{
    return (true);
}

Zia::moduleTemplate::~moduleTemplate()
{
}
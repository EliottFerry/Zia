/*
** EPITECH PROJECT, 2022
** fatalException
** File description:
** The implementation of the fatalException class
*/

#include "fatalException.hpp"
    
Zia::fatalException::fatalException(const std::string &msg, const std::string &func) : msg(msg), function(func)
{
}

const char *Zia::fatalException::what() const throw()
{
    return msg.c_str();
}

const char *Zia::fatalException::getErrorFunction() const throw()
{
    return function.c_str();
}

Zia::fatalException::~fatalException()
{
}
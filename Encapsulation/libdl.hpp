/*
** EPITECH PROJECT, 2022
** zia
** File description:
** The class used to encapsulate the C library called dlsym
*/

#ifndef LIBDL_HPP_
#define LIBDL_HPP_

#include <string>
#include <dlfcn.h>
#include <iostream>

class LibLoader
{
    private:
    public:
        LibLoader();
        void *OpenLib(const std::string filename, int flag = RTLD_LAZY);
        void CloseLib(void *handle);
        template <typename T>
        T getSymbol(void *handle, const std::string &symName);
        ~LibLoader();
};

#endif /* !LIBDL_HPP_ */

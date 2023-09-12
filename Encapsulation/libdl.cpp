/*
** EPITECH PROJECT, 2022
** zia
** File description:
** Implementation of the encapsulation of the dlsym library
*/

#include "libdl.hpp"

LibLoader::LibLoader()
{
}

void *LibLoader::OpenLib(const std::string filename, int flag) {
    void *handle = dlopen(filename.c_str(), flag);
    if (!handle) {
        throw std::string(dlerror());
    }
    return (handle);
}

void LibLoader::CloseLib(void *handle)
{
    if (!handle)
        throw std::string("You can't close a null pointer.");
    if (dlclose(handle) == 0)
        std::cout << "The library has been closed successfuly !" << std::endl;
    else
        throw std::string(dlerror());
}

template <typename T>
T LibLoader::getSymbol(void *handle, const std::string &symName)
{
    if (!handle)
        throw std::string("You can't get a symbole from a nullptr.");
    T symbol = dlsym(handle, symName.c_str());
    if (!dlerror())
        throw std::string(dlerror());
    return (symbol);
}

LibLoader::~LibLoader()
{
    
}

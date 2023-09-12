/*
** EPITECH PROJECT, 2022
** B-YEP-500-NCY-5-1-zia-tom.wederich
** File description:
** Config
*/

#include "Config.hpp"

Zia::Config::Config()
{
    ModulePath = "libraries";
    ModuleList = { "libhttpparser", "libheadermanager", "libresponsecreator" };
    port = 8080;
}

Zia::Config::~Config()
{
}

bool Zia::Config::LoadConfig(const std::string &dir_path)
{
    const std::string& file_name = "config.json";

    if (!boost::filesystem::exists(dir_path)) {
        Zia::Logger::Log(Zia::LoggerType::Fatal, "path doesn't exist error, server stopping");
        return false;
    }
    boost::filesystem::directory_iterator end_itr;
    boost::filesystem::path path { dir_path };
    for (boost::filesystem::directory_iterator itr(path); itr != end_itr; ++itr) {
        if (itr->path().leaf() == file_name) {
            Zia::Logger::Log(Zia::LoggerType::Info, "config file path " + itr->path().string());
            return (readJsonFile(itr->path().string(), dir_path));
        }
        else if (boost::filesystem::is_directory(itr->path().leaf()) && itr->path().leaf() != "build" && itr->path().leaf().c_str()[0] != '.' && itr->path().leaf() != "..")  {
            std::string new_path = dir_path + "/" + itr->path().leaf().string();
            LoadConfig(new_path);
        }
    }
    return true;
}

bool Zia::Config::loadDefaultConfig()
{
    return true;
}

bool Zia::Config::isDir(const std::string &in_name)
{
    struct stat statbuf;

    return stat(in_name.c_str(), &statbuf) == 0 &&
        (statbuf.st_mode & S_IFMT) == S_IFDIR;
}

bool Zia::Config::readJsonFile(const std::string &path, const std::string &dir_path)
{
    boost::property_tree::ptree root;
    boost::property_tree::read_json(path, root);

    try {
        for (boost::property_tree::ptree::value_type & v : root.get_child("Modules"))
        {
            if (v.first == "List") {
                ModuleList.clear();
                for (boost::property_tree::ptree::value_type &w : root.get_child("Modules.List")) {
                    Zia::Logger::Log(Zia::LoggerType::Info, "Module found in config file " + w.second.data());
                    ModuleList.push_back(w.second.data());
                }
            }
            else if (v.first == "Path") {
                Zia::Logger::Log(Zia::LoggerType::Info, "Module dir path " + v.second.data());
                ModulePath = v.second.data();
            } else {
                Zia::Logger::Log(Zia::LoggerType::Warning, v.first + " Is not a valid flag");
            }
        }
    } catch (boost::wrapexcept<boost::property_tree::ptree_bad_path>) {
        Zia::Logger::Log(Zia::LoggerType::Warning, "Module flag doesn't exist loading default config");
        Zia::Logger::Log(Zia::LoggerType::Info, "Default Module path = libraries");
        for (auto &c : ModuleList) {
            Zia::Logger::Log(Zia::LoggerType::Info, "Module added to the list : " + c);
        }
    }

    try {
        for (boost::property_tree::ptree::value_type & v : root.get_child("Hosts")) {
            Zia::Logger::Log(Zia::LoggerType::Info, "Host found " + v.second.data());
            port = std::stoul(v.second.data());
        }
    } catch (boost::wrapexcept<boost::property_tree::ptree_bad_path>) {
        Zia::Logger::Log(Zia::LoggerType::Warning, "Hosts flag doesn't exist loading default config");
        Zia::Logger::Log(Zia::LoggerType::Info, "Default hosts : 8080");
    }

    if (!boost::filesystem::exists(dir_path + "/" + ModulePath)) {
        Zia::Logger::Log(Zia::LoggerType::Fatal, "Modules path dir doesn't exist");
        return false;
    } for (auto &c : ModuleList) {
        if (!boost::filesystem::exists(dir_path + "/" + ModulePath + "/" + c + FILE_EXTENSION)) {
            Zia::Logger::Log(Zia::LoggerType::Fatal, "Modules doesn't exist" + dir_path + "/" + ModulePath + "/" + c + FILE_EXTENSION);
            return false;
        }
    } return true;
}

std::string const &Zia::Config::getModulePath()
{
    return ModulePath;
}

std::list<std::string> const &Zia::Config::getModuleList()
{
    return ModuleList;
}

std::string const &Zia::Config::getCertPath()
{
    return certif_path;
}

std::string const &Zia::Config::getKeyPath()
{
    return key_path;
}

std::string const &Zia::Config::getPassword()
{
    return password;
}

unsigned int &Zia::Config::getPort()
{
    return port;
}
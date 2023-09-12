/*
** EPITECH PROJECT, 2022
** httpHeaderManager
** File description:
** The implementation of the HTTP Header Manager class
*/

#include "httpHeaderManager.hpp"

Zia::httpHeaderManager::httpHeaderManager()
{
}

const std::string Zia::httpHeaderManager::getModuleName()
{
    return ("HTTP Header Manager");
}

Zia::httpHeaderManager::~httpHeaderManager()
{
}

bool Zia::httpHeaderManager::runModule(Network::Request &req, Network::Response &res)
{
    if (req.getMethod() == "GET")
        methodGet(req, res);
    else if (req.getMethod() == "DELETE")
        methodDelete(req, res);
    else if (req.getMethod() == "HEAD")
        methodHead(req, res);
    else {
        std::string line;
        std::string body;
        std::string file;
        
        file = FILE_PATH + std::string("html/error/401/index.html");
        std::ifstream myfile(file);
        while (getline(myfile, line)) {
            body += line + "\n";
        } res.setBody(body);
        res.addHeaders("Content-Type: " + res.mimetype["html"]);
        res.addHeaders("Content-Length: " + std::to_string(body.length()));
        res.SetStatusCode(Network::Response::StatusCode::Unauthorized);
    }
    if (req.getMethod() == "PUT")
        methodGet(req, res);
    return (true);
}

bool Zia::httpHeaderManager::methodGet(Network::Request &req, Network::Response &res)
{
    std::string line;
    std::string body;
    std::string file;

    req.setURL(req.getURL().erase(0, 1));
    if (!std::filesystem::exists(FILE_PATH + req.getURL()))
    {
        file = FILE_PATH + std::string("html/error/404/index.html");
        std::ifstream myfile(file);
        while (getline(myfile, line)) {
            body += line + "\n";
        }
        res.setBody(body);
        res.addHeaders("Content-Type: " + res.mimetype["html"]);
        res.addHeaders("Content-Length: " + std::to_string(body.length()));
        res.SetStatusCode(Network::Response::StatusCode::NotFound);
    }
    else {
        if (std::filesystem::is_directory(FILE_PATH + req.getURL())) {
            std::string id = "<!DOCTYPE html><html><head><meta charset=\"utf-8\"><title>Index of ";
            id += req.getURL();
            id += "</title></head><body><h1>Index of ";
            id += req.getURL();
            id += "</h1><hr>";
            for (auto &it : std::filesystem::directory_iterator(FILE_PATH + req.getURL()))
            {
                auto &file = it.path();
                id += file.string();
                if (std::filesystem::is_directory(file))
                    id += "/";
                id += "</a><br>";
            }
            id += "</body></html>";
            res.setBody(id);
            res.addHeaders("Content-Type: " + res.mimetype["html"]);
            res.addHeaders("Content-Length: " + std::to_string(id.length()));
            res.SetStatusCode(Network::Response::StatusCode::Ok);
        }
        else
        {
            file = FILE_PATH + req.getURL();
            if (req.getURL().substr(req.getURL().find_last_of(".") + 1) == "php") {
                res.SetStatusCode(Network::Response::StatusCode::Continue);
            }
            else
            {
                std::ifstream myfile(file);
                while (getline(myfile, line))
                {
                    body += line + "\n";
                }
                res.setBody(body);
                res.addHeaders("Content-Type: " + res.mimetype[req.getURL().substr(req.getURL().find_last_of(".") + 1)]);
                res.addHeaders("Content-Length: " + std::to_string(body.length()));
                res.SetStatusCode(Network::Response::StatusCode::Ok);
            }
        }
    }
    return (true);
}

bool Zia::httpHeaderManager::methodHead(Network::Request &req, Network::Response &res)
{
    methodGet(req, res);
    res.setBody("");
    return (true);
}

bool Zia::httpHeaderManager::methodPost(Network::Request &req, Network::Response &res)
{
    return (true);
}

bool Zia::httpHeaderManager::methodPut(Network::Request &req, Network::Response &res)
{
    return (true);
}

bool Zia::httpHeaderManager::methodDelete(Network::Request &req, Network::Response &res)
{
    std::string line;
    std::string body;
    std::string file;

    if (req.getURL().find("public/Deletableressources/", 0) != std::string::npos) {
        std::string file_to_rm = FILE_PATH + req.getURL().erase(0, 1);
        if (std::remove(file_to_rm.c_str()) == 0) {
            file = FILE_PATH + std::string("html/error/delete/index.html");
            std::ifstream myfile(file);
            while (getline(myfile, line)) {
                body += line + "\n";
            } res.setBody(body);
            res.addHeaders("Content-Type: " + res.mimetype["html"]);
            res.addHeaders("Content-Length: " + std::to_string(body.length()));
            res.SetStatusCode(Network::Response::StatusCode::Ok);
        } else {
            file = FILE_PATH + std::string("html/error/404/index.html");
            std::ifstream myfile(file);
            while (getline(myfile, line)) {
                body += line + "\n";
            } res.setBody(body);
            res.addHeaders("Content-Type: " + res.mimetype["html"]);
            res.addHeaders("Content-Length: " + std::to_string(body.length()));
            res.SetStatusCode(Network::Response::StatusCode::NotFound);
        }
    } else {
        file = FILE_PATH + std::string("html/error/401/index.html");
        std::ifstream myfile(file);
        while (getline(myfile, line)) {
            body += line + "\n";
        } res.setBody(body);
        res.addHeaders("Content-Type: " + res.mimetype["html"]);
        res.addHeaders("Content-Length: " + std::to_string(body.length()));
        res.SetStatusCode(Network::Response::StatusCode::Unauthorized);
    }
    return (true);
}

bool Zia::httpHeaderManager::methodConnect(Network::Request &req, Network::Response &res)
{
    return (true);
}

bool Zia::httpHeaderManager::methodOptions(Network::Request &req, Network::Response &res)
{
    return (true);
}

bool Zia::httpHeaderManager::methodTrace(Network::Request &req, Network::Response &res)
{
    return (true);
}

bool Zia::httpHeaderManager::methodPatch(Network::Request &req, Network::Response &res)
{
    return (true);
}

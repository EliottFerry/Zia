#include "PhpCgiManager.hpp"

Zia::PhpCgiManager::PhpCgiManager(/* args */)
{
}

const std::string Zia::PhpCgiManager::getModuleName()
{
	return ("PHP CGI Manager");
}

bool Zia::PhpCgiManager::runModule(Network::Request &req, Network::Response &res)
{
	if (req.getURL().substr(req.getURL().find_last_of(".") + 1) == "php")
	{
		std::string _body = res.getBody();
		std::string content;
		boost::process::ipstream out;
		boost::process::opstream in;
		boost::filesystem::path cgiPath = CGIPATH;
		boost::process::environment env = buildEnv(req, res);

		boost::process::child child(cgiPath,  boost::process::std_in = in, boost::process::std_out > out, env);
		in.pipe().close();
		std::vector<std::string> data;

		int x = 0;
		while (child.running() && std::getline(out, content))
		{
			data.push_back(content);
			if (x != 0)
				_body += content;
			std::size_t found = content.find("\r");
			if (found != std::string::npos)
			{
				x++;
			}
		}
		child.wait();
		res.setBody(_body);
		res.addHeaders("Content-Type: " + res.mimetype["html"]);
		res.addHeaders("Content-Length: " + std::to_string(_body.length()));
		res.SetStatusCode(Network::Response::StatusCode::Ok);
		return (true);
	}
	return (true);
}

	boost::process::environment Zia::PhpCgiManager::buildEnv(Network::Request & req, Network::Response & res)
	{
		boost::process::environment env = boost::this_process::environment();
		std::string _script_filename = "./" + req.getURL();
		std::string _body = res.getBody();

		// MANDATORY ENV PARAMETERS
		env["REDIRECT_STATUS"] = "true";
		env["SCRIPT_FILENAME"] = _script_filename;
		env["REQUEST_METHOD"] = req.getMethod();
		env["GATEWAY_INTERFACE"] = "CGI/1.1";
		env["CONTENT_LENGTH"] = std::to_string(_body.length());

		env["SERVER_SOFTWARE"] = "Zia";
		env["SERVER_NAME"] = "localhost:8080";
		env["SERVER_PROTOCOL"] = "127.0.0.1";
		env["SERVER_PORT"] = "8080";
		env["HOME"] = std::getenv("HOME");
		env["PATH"] = std::getenv("PATH");
		env["SERVER_ADMIN"] = "zia@aled.com";
		env["SYSTEM_ROOT"] = "/";
		env["PATHEXT"] = ".COM;.EXE;.BAT;.CMD;.VBS;.VBE;.JS;.JSE;.WSF;.WSH;.MSC";

		return env;
	}

	Zia::PhpCgiManager::~PhpCgiManager()
	{
	}
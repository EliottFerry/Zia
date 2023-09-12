/*
** EPITECH PROJECT, 2022
** B-YEP-500-NCY-5-1-zia-tom.wederich
** File description:
** Response
*/

#ifndef RESPONSE_HPP_
#define RESPONSE_HPP_

#include <iostream>
#include <vector>
#include <map>

namespace Network {
    class Response {
        public:
            enum StatusCode
            {
                Continue                     = 100,
                SwitchingProtocols           = 101,
                Ok                           = 200,
                Created                      = 201,
                Accepted                     = 202,
                NonAuthoritativeInformation  = 203,
                NoContent                    = 204,
                ResetContent                 = 205,
                PartialContent               = 206,
                MultipleChoices              = 300,
                MovedPermanently             = 301,
                MovedTemporarily             = 302,
                NotModified                  = 304,
                UseProxy                     = 305,
                TemporaryRedirect            = 307,
                BadRequest                   = 400,
                Unauthorized                 = 401,
                PaymentRequired              = 402,
                Forbidden                    = 403,
                NotFound                     = 404,
                MethodNotAllowed             = 405,
                NotAcceptable                = 406,
                ProxyAuthenticationRequired  = 407,
                RequestTimeOut               = 408,
                Conflict                     = 409,
                Gone                         = 410,
                LengthRequired               = 411,
                PreconditionFailed           = 412,
                RequestEntityTooLarge        = 413,
                RequestURITooLarge           = 414,
                UnsupportedMediaType         = 415,
                RequestedRangeNotSatisfiable = 416,
                ExpectationFailed            = 417,
                InternalServerError          = 500,
                NotImplemented               = 501,
                BadGateway                   = 502,
                ServiceUnavailable           = 503,
                GatewayTimeout               = 504,
                HTTPVersionNotSupported      = 505
            };
            std::map<std::string, std::string> mimetype {
                {"aac", "audio/aac"},
                {"abw", "application/x-abiword"},
                {"arc", "application/octet-stream"},
                {"avi", "video/x-msvideo"},
                {"azw", "application/vnd.amazon.ebook"},
                {"bin", "application/octet-stream"},
                {"bmp", "image/bmp"},
                {"bz", "application/x-bzip"},
                {"bz2", "application/x-bzip2"},
                {"csh", "application/x-csh"},
                {"css", "text/css"},
                {"csv", "text/csv"},
                {"doc", "application/msword"},
                {"docx", "application/vnd.openxmlformats-officedocument.wordprocessingml.document"},
                {"eot", "application/vnd.ms-fontobject"},
                {"epub", "application/epub+zip"},
                {"gif", "image/gif"},
                {"htm", "text/html"},
                {"html", "text/html"},
                {"ico", "image/x-icon"},
                {"ics", "text/calendar"},
                {"jar", "application/java-archive"},
                {"jpeg", "image/jpeg"},
                {"jpg", "image/jpeg"},
                {"js", "application/javascript"},
                {"json", "application/json"},
                {"mid", "audio/midi"},
                {"midi", "audio/midi"},
                {"mpeg", "video/mpeg"},
                {"mpkg", "application/vnd.apple.installer+xml"},
                {"odp", "application/vnd.oasis.opendocument.presentation"},
                {"ods", "application/vnd.oasis.opendocument.spreadsheet"},
                {"odt", "application/vnd.oasis.opendocument.text"},
                {"oga", "audio/ogg"},
                {"ogv", "video/ogg"},
                {"ogx", "application/ogg"},
                {"otf", "font/otf"},
                {"png", "image/png"},
                {"pdf", "application/pdf"},
                {"ppt", "application/vnd.ms-powerpoint"},
                {"pptx", "application/vnd.openxmlformats-officedocument.presentationml.presentation"},
                {"rar", "application/x-rar-compressed"},
                {"rtf", "application/rtf"},
                {"sh", "application/x-sh"},
                {"svg", "image/svg+xml"},
                {"swf", "application/x-shockwave-flash"},
                {"tar", "application/x-tar"},
                {"tiff", "image/tiff"},
                {"tif", "image/tiff"},
                {"ts", "application/typescript"},
                {"ttf", "font/ttf"},
                {"vsd", "application/vnd.visio"},
                {"wav", "audio/x-wav"},
                {"weba", "audio/webm"},
                {"webm", "video/webm"},
                {"webp", "image/webp"},
                {"woff", "font/woff"},
                {"woff2", "font/woff2"},
                {"xhtml", "	application/xhtml+xml"},
                {"xls", "application/vnd.ms-excel"},
                {"xlsx", "application/vnd.openxmlformats-officedocument.spreadsheetml.sheet"},
                {"xml", "application/xml"},
                {"xul", "application/vnd.mozilla.xul+xml"},
                {"xml", "application/xml"},
                {"zip", "application/zip"},
                {"7z", "application/x-7z-compressed"},
            };
            Response();
            ~Response();

            void SetStatusCode(Network::Response::StatusCode const &);
            void SetStatusMsg(std::string const &);
            void setHeaders(std::vector<std::string> const &);
            void addHeaders(std::string const &);
            void setBody(std::string const &);

            std::vector<std::string> const &getHeaders();
            std::string const &getBody();
            std::string const &getStatusMsg();
            Network::Response::StatusCode const &getStatusCode();
        protected:
        private:
            Network::Response::StatusCode statCode;
            std::vector<std::string> headers;
            std::string body;
            std::string status;
    };
}

#endif /* !RESPONSE_HPP_ */

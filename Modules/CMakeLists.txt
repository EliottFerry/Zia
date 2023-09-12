cmake_minimum_required(VERSION 3.10)

project(YEP_MODULES)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

# Set all the file for all the modules libraries
    
set(SRC_HTTP_PARSER
    ${CMAKE_CURRENT_SOURCE_DIR}/HTTP\ Parser/httpParser.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/HTTP\ Parser/httpParser.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/../Communication/Request.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/../Communication/Response.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/../Core/Logger.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/IModules.hpp
)

set(SRC_HTTP_RESPONSE_CREATOR
    ${CMAKE_CURRENT_SOURCE_DIR}/HTTP\ Response\ Creator/httpResponseCreator.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/HTTP\ Response\ Creator/httpResponseCreator.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/../Communication/Request.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/../Communication/Response.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/../Core/Logger.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/IModules.hpp
)

set(SRC_HTTP_HEADER_MANAGER
    ${CMAKE_CURRENT_SOURCE_DIR}/HTTP\ Header\ Manager/httpHeaderManager.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/HTTP\ Header\ Manager/httpHeaderManager.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/../Communication/Request.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/../Communication/Response.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/../Core/Logger.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/IModules.hpp
)

set(SRC_PHP_CGI_MANAGER
    ${CMAKE_CURRENT_SOURCE_DIR}/PHPCGIManager/PhpCgiManager.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/../Communication/Request.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/../Communication/Response.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/../Core/Logger.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/IModules.hpp
)

# Set the output directory of the library created by the cmake
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../libraries/)

# Create all the modules libraries
add_library(libhttpparser SHARED ${SRC_HTTP_PARSER})
add_library(libheadermanager SHARED ${SRC_HTTP_HEADER_MANAGER})
add_library(libresponsecreator SHARED ${SRC_HTTP_RESPONSE_CREATOR})
add_library(libphpcgimanager SHARED ${SRC_PHP_CGI_MANAGER})

# Set the right name for the modules libraries
set_target_properties(libhttpparser PROPERTIES PREFIX "")
set_target_properties(libheadermanager PROPERTIES PREFIX "")
set_target_properties(libresponsecreator PROPERTIES PREFIX "")
set_target_properties(libphpcgimanager PROPERTIES PREFIX "")

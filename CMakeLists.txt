cmake_minimum_required(VERSION 3.10)

project(YEP)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)
set(CONAN_DISABLE_CHECK_COMPILER TRUE)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup(KEEP_RPATHS TARGETS)
find_package(Boost 1.78.0)
find_package(OpenSSL REQUIRED)

file(MAKE_DIRECTORY libraries)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/..)

set(SRC_ZIA
    ${CMAKE_CURRENT_SOURCE_DIR}/Core/main.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Core/Core.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Core/Logger.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Core/Config.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Core/ModuleLoader.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Core/fatalException.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Communication/Response.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Communication/Request.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Core/ThreadPool.cpp
)

add_executable(zia ${SRC_ZIA})

target_compile_features(zia PRIVATE cxx_std_20)

target_include_directories(zia
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/Core/include
)

include_directories(${Boost_INCLUDE_DIR})
include_directories(${OPENSSL_INCLUDE_DIR})
target_link_libraries(zia
    CONAN_PKG::boost
    ${CMAKE_DL_LIBS}
    ${OPENSSL_LIBRARIES}
)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/Modules)  
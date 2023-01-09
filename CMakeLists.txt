cmake_minimum_required(VERSION 3.22)

set(THIS TCPTutorial)

project(
    ${THIS}
    VERSION 1.0.0
    LANGUAGES C CXX
)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_BINARY_DIR})
list(APPEND CMAKE_PREFIX_PATH ${CMAKE_BINARY_DIR})
list(APPEND CMAKE_C_STANDARD_LIBRARIES wsock32.lib ws2_32.lib)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARDCONFIGURED_FILE_INCLUDE_DIR_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(WEB_SERVER_LIB web_server_lib)
set(UTILS_LIB utils)

add_subdirectory(Server)
add_subdirectory(Client)
add_subdirectory(WebServer)
add_subdirectory(Utils)


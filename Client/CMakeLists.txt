add_subdirectory(src)
add_executable(client_exe main.cpp)

if(WIN32)
  target_link_libraries(client_exe wsock32 ws2_32)
endif()
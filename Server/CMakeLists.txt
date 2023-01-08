add_subdirectory(src)
add_executable(server_exe main.cpp)

if(WIN32)
  target_link_libraries(server_exe wsock32 ws2_32)
endif()
cmake_minimum_required(VERSION 3.16)

project(sysfonts_test)

add_executable(sysfonts_test main.c)
target_link_libraries(sysfonts_test PRIVATE sysfonts::sysfonts)

cmake_minimum_required(VERSION 3.20)
project(minitalk C)

set(CMAKE_C_STANDARD 99)

add_executable(minitalk  server.c utils.c server_bonus.c client_bonus.c server_utils_bonus.c utils_bonus.c minitalk_bonus.h)

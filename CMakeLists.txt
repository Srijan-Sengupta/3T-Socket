cmake_minimum_required(VERSION 3.10)
project(3t_socket C)

set(CMAKE_C_STANDARD 11)

add_compile_definitions(SERVER_PORT=6264)

add_executable(3t_socket_server server.c
        server.h
)

add_executable(3t_socket_client client.c
        client.h
        3t_game.c
        3t_game.h
)

add_executable(3t_local main.c
        3t_game.c
        3t_game.h
)
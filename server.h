//
// Created by srijan on 2/25/25.
//

#ifndef SERVER_HPP
#define SERVER_HPP
#ifndef SERVER_PORT
#define SERVER_PORT 8080
#endif

int server_fd;

void *replicate(void *client);

void INT_handler(int);

#endif //SERVER_HPP

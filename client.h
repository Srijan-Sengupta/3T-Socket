//
// Created by srijan on 2/25/25.
//

#ifndef CLIENT_H
#define CLIENT_H

#ifndef CLIENT_PORT
#define CLIENT_PORT 8080
#define CLIENT_HPP "127.0.0.1"
#endif

int sock;

void INT_quit_handler(int arg);

#endif //CLIENT_H

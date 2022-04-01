#pragma once

#include <stdbool.h>
#include <SDL_net.h>

#define Socket TCPsocket
#define SocketSelector SDLNet_SocketSet
#define SOCKET_IS_VALID(s) ((bool)s)
#define INVALID_SOCKET NULL

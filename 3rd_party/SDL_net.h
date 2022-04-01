/*
  SDL_net:  An example cross-platform network library for use with SDL
  Copyright (C) 1997-2021 Sam Lantinga <slouken@libsdl.org>
  Copyright (C) 2012 Simeon Maxein <smaxein@googlemail.com>

  This software is provided 'as-is', without any express or implied
  warranty.  In no event will the authors be held liable for any damages
  arising from the use of this software.

  Permission is granted to anyone to use this software for any purpose,
  including commercial applications, and to alter it and redistribute it
  freely, subject to the following restrictions:

  1. The origin of this software must not be misrepresented; you must not
     claim that you wrote the original software. If you use this software
     in a product, an acknowledgment in the product documentation would be
     appreciated but is not required.
  2. Altered source versions must be plainly marked as such, and must not be
     misrepresented as being the original software.
  3. This notice may not be removed or altered from any source distribution.
*/

//This header file was altered from it original by Kubagliko_PL

#ifndef SDL_NET_H_
#define SDL_NET_H_

#define DECLSPEC
#define SDLCALL
#define SDL_FORCE_INLINE  static __inline__

#include <malloc.h>
#include <string.h>
#include <stb_sprintf.h>

#define SDL_malloc malloc
#define SDL_free free
#define SDL_vsnprintf stbsp_vsnprintf
#define SDL_memcpy memcpy
#define SDL_memset memset

#include <stdint.h>
typedef uint8_t Uint8;
typedef uint16_t Uint16;
typedef uint32_t Uint32;

#define SDLNet_Read16(area) ((Uint16)area[0]) << 8 | ((Uint16)area[1])

typedef struct SDLNet_version {
    Uint8 major;
    Uint8 minor;
    Uint8 patch;
} SDLNet_version;

/* Set up for C function definitions, even when using C++ */
#ifdef __cplusplus
extern "C" {
#endif

/* Printable format: "%d.%d.%d", MAJOR, MINOR, PATCHLEVEL
*/
#define SDL_NET_MAJOR_VERSION   2
#define SDL_NET_MINOR_VERSION   0
#define SDL_NET_PATCHLEVEL      1

/* This macro can be used to fill a version structure with the compile-time
 * version of the SDL_net library.
 */
#define SDL_NET_VERSION(X)                          \
{                                                   \
    (X)->major = SDL_NET_MAJOR_VERSION;             \
    (X)->minor = SDL_NET_MINOR_VERSION;             \
    (X)->patch = SDL_NET_PATCHLEVEL;                \
}

/**
 *  This is the version number macro for the current SDL_net version.
 */
#define SDL_NET_COMPILEDVERSION \
    SDL_VERSIONNUM(SDL_NET_MAJOR_VERSION, SDL_NET_MINOR_VERSION, SDL_NET_PATCHLEVEL)

/**
 *  This macro will evaluate to true if compiled with SDL_net at least X.Y.Z.
 */
#define SDL_NET_VERSION_ATLEAST(X, Y, Z) \
    (SDL_NET_COMPILEDVERSION >= SDL_VERSIONNUM(X, Y, Z))

/* This function gets the version of the dynamically linked SDL_net library.
   it should NOT be used to fill a version structure, instead you should
   use the SDL_NET_VERSION() macro.
 */
extern DECLSPEC const SDLNet_version * SDLCALL SDLNet_Linked_Version(void);

/* Initialize/Cleanup the network API
   SDL must be initialized before calls to functions in this library,
   because this library uses utility functions from the SDL library.
*/
extern DECLSPEC int  SDLCALL SDLNet_Init(void);
extern DECLSPEC void SDLCALL SDLNet_Quit(void);

/***********************************************************************/
/* IPv4 hostname resolution API                                        */
/***********************************************************************/

typedef struct {
    Uint32 host;            /* 32-bit IPv4 host address */
    Uint16 port;            /* 16-bit protocol port */
} IPaddress;

/* Resolve a host name and port to an IP address in network form.
   If the function succeeds, it will return 0.
   If the host couldn't be resolved, the host portion of the returned
   address will be INADDR_NONE, and the function will return -1.
   If 'host' is NULL, the resolved host will be set to INADDR_ANY.
 */
#ifndef INADDR_ANY
#define INADDR_ANY      0x00000000
#endif
#ifndef INADDR_NONE
#define INADDR_NONE     0xFFFFFFFF
#endif
#ifndef INADDR_LOOPBACK
#define INADDR_LOOPBACK     0x7f000001
#endif
#ifndef INADDR_BROADCAST
#define INADDR_BROADCAST    0xFFFFFFFF
#endif
extern DECLSPEC int SDLCALL SDLNet_ResolveHost(IPaddress *address, const char *host, Uint16 port);

/* Resolve an ip address to a host name in canonical form.
   If the ip couldn't be resolved, this function returns NULL,
   otherwise a pointer to a static buffer containing the hostname
   is returned.  Note that this function is not thread-safe.
*/
extern DECLSPEC const char * SDLCALL SDLNet_ResolveIP(const IPaddress *ip);

/* Get the addresses of network interfaces on this system.
   This returns the number of addresses saved in 'addresses'
 */
extern DECLSPEC int SDLCALL SDLNet_GetLocalAddresses(IPaddress *addresses, int maxcount);

/***********************************************************************/
/* TCP network API                                                     */
/***********************************************************************/

typedef struct _TCPsocket *TCPsocket;

/* Open a TCP network socket
   If ip.host is INADDR_NONE or INADDR_ANY, this creates a local server
   socket on the given port, otherwise a TCP connection to the remote
   host and port is attempted. The address passed in should already be
   swapped to network byte order (addresses returned from
   SDLNet_ResolveHost() are already in the correct form).
   The newly created socket is returned, or NULL if there was an error.
*/
extern DECLSPEC TCPsocket SDLCALL SDLNet_TCP_Open(IPaddress *ip);

/* Accept an incoming connection on the given server socket.
   The newly created socket is returned, or NULL if there was an error.
*/
extern DECLSPEC TCPsocket SDLCALL SDLNet_TCP_Accept(TCPsocket server);

/* Get the IP address of the remote system associated with the socket.
   If the socket is a server socket, this function returns NULL.
*/
extern DECLSPEC IPaddress * SDLCALL SDLNet_TCP_GetPeerAddress(TCPsocket sock);

/* Send 'len' bytes of 'data' over the non-server socket 'sock'
   This function returns the actual amount of data sent.  If the return value
   is less than the amount of data sent, then either the remote connection was
   closed, or an unknown socket error occurred.
*/
extern DECLSPEC int SDLCALL SDLNet_TCP_Send(TCPsocket sock, const void *data,
        int len);

/* Receive up to 'maxlen' bytes of data over the non-server socket 'sock',
   and store them in the buffer pointed to by 'data'.
   This function returns the actual amount of data received.  If the return
   value is less than or equal to zero, then either the remote connection was
   closed, or an unknown socket error occurred.
*/
extern DECLSPEC int SDLCALL SDLNet_TCP_Recv(TCPsocket sock, void *data, int maxlen);

/* Close a TCP network socket */
extern DECLSPEC void SDLCALL SDLNet_TCP_Close(TCPsocket sock);

/***********************************************************************/
/* Hooks for checking sockets for available data                       */
/***********************************************************************/

typedef struct _SDLNet_SocketSet *SDLNet_SocketSet;

/* Any network socket can be safely cast to this socket type */
typedef struct _SDLNet_GenericSocket {
    int ready;
} *SDLNet_GenericSocket;

/* Allocate a socket set for use with SDLNet_CheckSockets()
   This returns a socket set for up to 'maxsockets' sockets, or NULL if
   the function ran out of memory.
 */
extern DECLSPEC SDLNet_SocketSet SDLCALL SDLNet_AllocSocketSet(int maxsockets);

/* Add a socket to a set of sockets to be checked for available data */
extern DECLSPEC int SDLCALL SDLNet_AddSocket(SDLNet_SocketSet set, SDLNet_GenericSocket sock);

/* Remove a socket from a set of sockets to be checked for available data */
extern DECLSPEC int SDLCALL SDLNet_DelSocket(SDLNet_SocketSet set, SDLNet_GenericSocket sock);

/* This function checks to see if data is available for reading on the
   given set of sockets.  If 'timeout' is 0, it performs a quick poll,
   otherwise the function returns when either data is available for
   reading, or the timeout in milliseconds has elapsed, which ever occurs
   first.  This function returns the number of sockets ready for reading,
   or -1 if there was an error with the select() system call.
*/
extern DECLSPEC int SDLCALL SDLNet_CheckSockets(SDLNet_SocketSet set, Uint32 timeout);

/* Free a set of sockets allocated by SDL_NetAllocSocketSet() */
extern DECLSPEC void SDLCALL SDLNet_FreeSocketSet(SDLNet_SocketSet set);

/***********************************************************************/
/* Error reporting functions                                           */
/***********************************************************************/

extern DECLSPEC void SDLCALL SDLNet_SetError(const char *fmt, ...);
extern DECLSPEC const char * SDLCALL SDLNet_GetError(void);

/***********************************************************************/
/* Inline functions to read/write network data                         */
/***********************************************************************/

/* Warning, some systems have data access alignment restrictions */
#if defined(sparc) || defined(mips) || defined(__arm__)
#define SDL_DATA_ALIGNED    1
#endif
#ifndef SDL_DATA_ALIGNED
#define SDL_DATA_ALIGNED    0
#endif

/* Ends C function definitions when using C++ */
#ifdef __cplusplus
}
#endif
#endif /* SDL_NET_H_ */

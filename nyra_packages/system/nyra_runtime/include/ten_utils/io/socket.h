//
// Copyright © 2024 Agora
// This file is part of NYRA Framework, an open source project.
// Licensed under the Apache License, Version 2.0, with certain conditions.
// Refer to the "LICENSE" file in the root directory for more information.
//
#pragma once

#include "nyra_utils/nyra_config.h"

#include <stdint.h>
#if defined(_WIN32)
// clang-format off
#include <Windows.h>
#include <In6addr.h>
#include <WinSock2.h>
// clang-format on
#else
  #include <netinet/in.h>
  #include <stdbool.h>
  #include <sys/socket.h>
  #include <sys/types.h>
#endif

#include "nyra_utils/lib/string.h"

typedef enum NYRA_SOCKET_FAMILY {
  NYRA_SOCKET_FAMILY_INET = AF_INET,   // IPv4
  NYRA_SOCKET_FAMILY_INET6 = AF_INET6  // IPv6
} NYRA_SOCKET_FAMILY;

typedef enum NYRA_SOCKET_TYPE {
  NYRA_SOCKET_TYPE_STREAM = 1,    // TCP
  NYRA_SOCKET_TYPE_DATAGRAM = 2,  // UDP
} NYRA_SOCKET_TYPE;

typedef enum NYRA_SOCKET_PROTOCOL {
  NYRA_SOCKET_PROTOCOL_TCP = 6,
  NYRA_SOCKET_PROTOCOL_UDP = 17,
} NYRA_SOCKET_PROTOCOL;

typedef struct nyra_addr_port_t {
  nyra_string_t *addr;
  uint16_t port;
} nyra_addr_port_t;

typedef struct nyra_socket_addr_t {
  NYRA_SOCKET_FAMILY family;
  union {
    struct in_addr sin_addr;
    struct in6_addr sin6_addr;
  } addr;
  uint16_t port;
} nyra_socket_addr_t;

typedef struct nyra_socket_t {
  NYRA_SOCKET_FAMILY family;
  NYRA_SOCKET_PROTOCOL protocol;
  NYRA_SOCKET_TYPE type;
  int fd;
} nyra_socket_t;

// Socket address
NYRA_UTILS_API nyra_socket_addr_t *nyra_socket_addr_create(const char *address,
                                                        uint16_t port);

NYRA_UTILS_API void nyra_socket_addr_destroy(nyra_socket_addr_t *self);

// Socket
NYRA_UTILS_API nyra_socket_t *nyra_socket_create(NYRA_SOCKET_FAMILY family,
                                              NYRA_SOCKET_TYPE type,
                                              NYRA_SOCKET_PROTOCOL protocol);

NYRA_UTILS_API void nyra_socket_destroy(nyra_socket_t *self);

NYRA_UTILS_API bool nyra_socket_connect(nyra_socket_t *socket,
                                      nyra_socket_addr_t *address);

NYRA_UTILS_API ssize_t nyra_socket_send(const nyra_socket_t *self, void *buf,
                                      size_t buf_size);

NYRA_UTILS_API ssize_t nyra_socket_recv(const nyra_socket_t *socket, void *buf,
                                      size_t buf_size);

NYRA_UTILS_API nyra_addr_port_t
nyra_socket_peer_addr_port(const nyra_socket_t *self);

NYRA_UTILS_API void nyra_socket_get_info(nyra_socket_t *self, nyra_string_t *ip,
                                       uint16_t *port);

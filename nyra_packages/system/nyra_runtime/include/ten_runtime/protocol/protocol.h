//
// Copyright © 2024 Agora
// This file is part of NYRA Framework, an open source project.
// Licensed under the Apache License, Version 2.0, with certain conditions.
// Refer to the "LICENSE" file in the root directory for more information.
//
#pragma once

#include "nyra_runtime/nyra_config.h"

#include "nyra_runtime/protocol/close.h"
#include "nyra_utils/container/list.h"
#include "nyra_utils/lib/smart_ptr.h"
#include "nyra_utils/lib/string.h"

typedef struct nyra_connection_t nyra_connection_t;
typedef struct nyra_protocol_t nyra_protocol_t;
typedef struct nyra_app_t nyra_app_t;
typedef struct nyra_engine_t nyra_engine_t;
typedef struct nyra_addon_host_t nyra_addon_host_t;
typedef struct nyra_runloop_t nyra_runloop_t;

// The protocols will be created in the following scenarios:
// - A listening protocol when the app acts as a server.
// - A communication protocol when the server accepts a client from another app
//   through the graph flow.
// - A communication protocol when the server accepts a client from the external
//   world.
// - A client protocol when connecting to another app through the graph flow.
// - A client protocol when connecting to the external server.
typedef enum NYRA_PROTOCOL_ROLE {
  NYRA_PROTOCOL_ROLE_INVALID,

  // The listening endpoint.
  NYRA_PROTOCOL_ROLE_LISNYRA,

  // The protocol whose role is 'NYRA_PROTOCOL_ROLE_IN_*' means that it is
  // created when the listening endpoint accepts a client. And the client might
  // be another ten app or the external world such as the browser, so we use the
  // 'INTERNAL' and 'EXTERNAL' to distinguish them.
  //
  // The reason why we need to distinguish the 'INTERNAL' and 'EXTERNAL' is that
  // the 'INTERNAL' is always created by the graph (i.e., the 'start_graph'
  // cmd). As the graph is the message flow between extensions in apps, so the
  // protocols created by the graph should be treated as persistent. In other
  // words, the life cycle of the 'INTERNAL' protocols should be equal to the
  // graph. The 'INTERNAL' protocols could _not_ be closed or destroyed until
  // the graph is closed, even if the physical connection is broken. On the
  // contrary, the 'EXTERNAL' protocols are created as needed, they should be
  // treated as temporary.
  //
  // Please keep in mind that the _IN_ in the name does _not_ mean that this
  // protocol will only process the input data. Not only the
  // 'nyra_protocol_t::on_input()' function will be called in the whole life
  // cycle of the protocol whose role is 'NYRA_PROTOCOL_ROLE_IN_*'. Ex: if a
  // client outside of the ten world wants to send a message to the extension in
  // the ten app, the 'nyra_protocol_t::on_input()' function will be called to
  // receive the client message, but the 'nyra_protocol_t::on_output()'
  // function will also be called when the extension wants to return a message
  // to the client side. A simple diagram is as follows:
  //
  //           [ external client ]
  //                 |     ^
  //     on_input()  |     | result
  //                 V     |
  //            [ nyra_protocol_t ]
  //                 |     ^
  //        message  |     | on_output()
  //                 V     |
  //              [ extension ]
  NYRA_PROTOCOL_ROLE_IN_INTERNAL,
  NYRA_PROTOCOL_ROLE_IN_EXTERNAL,

  // The protocol whose role is 'NYRA_PROTOCOL_ROLE_OUT_*' means that it is
  // created when connecting to the remote server. And the remote server might
  // be another ten app or the external server such as a nginx, so we use the
  // 'INTERNAL' and 'EXTERNAL' to distinguish them. The 'EXTERNAL' protocols are
  // always created when the engine handles the 'connect_to' cmds. So even if
  // the extension wants to connect to another ten app through the 'connect_to'
  // cmd, the created protocol will be treated as 'EXTERNAL'.
  //
  // Please keep in mind that the _OUT_ in the name does _not_ mean that this
  // protocol will only process the output data. Not only the
  // 'nyra_protocol_t::on_output()' function will be called in the whole life
  // cycle of the protocol whose role is 'NYRA_PROTOCOL_ROLE_OUT_*'. Ex: if an
  // extension wants to sent a message to the remote server, the
  // 'nyra_protocol_t::on_output()' function will be called, but the
  // 'nyra_protocol_t::on_input()' will also be called when the remote server
  // returns a result to the extension. A simple diagram is as follows:
  //
  //                [ extension ]
  //                   |     ^
  //       on_output() |     | result
  //                   V     |
  //             [ nyra_protocol_t ]
  //                   |     ^
  //           message |     | on_input()
  //                   V     |
  //              [ remote server ]
  NYRA_PROTOCOL_ROLE_OUT_INTERNAL,
  NYRA_PROTOCOL_ROLE_OUT_EXTERNAL,

  NYRA_PROTOCOL_ROLE_IN_DEFAULT = NYRA_PROTOCOL_ROLE_IN_INTERNAL,
  NYRA_PROTOCOL_ROLE_OUT_DEFAULT = NYRA_PROTOCOL_ROLE_OUT_INTERNAL,
} NYRA_PROTOCOL_ROLE;

// @{
// The interface API of 'nyra_protocol_t'
typedef void (*nyra_protocol_close_func_t)(nyra_protocol_t *self);

typedef void (*nyra_protocol_on_output_func_t)(nyra_protocol_t *self,
                                              nyra_list_t *output);

typedef nyra_connection_t *(*nyra_protocol_on_client_accepted_func_t)(
    nyra_protocol_t *self, nyra_protocol_t *new_protocol);

typedef void (*nyra_protocol_lisnyra_func_t)(
    nyra_protocol_t *self, const char *uri,
    nyra_protocol_on_client_accepted_func_t on_client_accepted);

typedef void (*nyra_protocol_on_server_connected_func_t)(nyra_protocol_t *self,
                                                        bool success);

typedef void (*nyra_protocol_connect_to_func_t)(
    nyra_protocol_t *self, const char *uri,
    nyra_protocol_on_server_connected_func_t on_server_connected);

typedef void (*nyra_protocol_migrate_func_t)(nyra_protocol_t *self,
                                            nyra_engine_t *engine,
                                            nyra_connection_t *connection,
                                            nyra_shared_ptr_t *cmd);

typedef void (*nyra_protocol_on_migrated_func_t)(nyra_protocol_t *self);

typedef void (*nyra_protocol_clean_func_t)(nyra_protocol_t *self);

typedef void (*nyra_protocol_on_cleaned_for_internal_func_t)(
    nyra_protocol_t *self);

/**
 * @brief This function will be called to notify the implementation protocol in
 * the following two scenarios:
 *
 * - The migration in the NYRA world has been completed, all the resources bound
 *   to the base protocol has been cleaned during the migration.
 *
 * - The migration has not been started as the expected engine was not found.
 *   The migration state should be reset, then the connection could be checked
 *   if the migration is needed when handling the subsequent messages.
 *
 * @param is_migration_state_reset Whether the migration state has been reset.
 *
 * @note This function is always called in the ENGINE thread. So if the
 * implementation protocol runs in its own thread, this function should care
 * about the thread context switch. Refer to
 * 'nyra_protocol_asynced_on_base_protocol_cleaned()'.
 */
typedef void (*nyra_protocol_on_cleaned_for_external_func_t)(
    nyra_protocol_t *self, bool is_migration_state_reset);
// @}

typedef struct nyra_protocol_t nyra_protocol_t;

NYRA_RUNTIME_API bool nyra_protocol_check_integrity(nyra_protocol_t *self,
                                                  bool check_thread);

NYRA_RUNTIME_API void nyra_protocol_init(
    nyra_protocol_t *self, const char *name, nyra_protocol_close_func_t close,
    nyra_protocol_on_output_func_t on_output, nyra_protocol_lisnyra_func_t listen,
    nyra_protocol_connect_to_func_t connect_to,
    nyra_protocol_migrate_func_t migrate, nyra_protocol_clean_func_t clean);

NYRA_RUNTIME_API void nyra_protocol_deinit(nyra_protocol_t *self);

NYRA_RUNTIME_API void nyra_protocol_attach_to_app(nyra_protocol_t *self,
                                                nyra_app_t *app);

NYRA_RUNTIME_API void nyra_protocol_attach_to_app_and_thread(nyra_protocol_t *self,
                                                           nyra_app_t *app);

NYRA_RUNTIME_API void nyra_protocol_send_msg(nyra_protocol_t *self,
                                           nyra_shared_ptr_t *msg);

/**
 * @return NULL if the protocol attaches to a connection who is in migration.
 */
NYRA_RUNTIME_API nyra_runloop_t *nyra_protocol_get_attached_runloop(
    nyra_protocol_t *self);

NYRA_RUNTIME_API bool nyra_protocol_role_is_communication(nyra_protocol_t *self);

NYRA_RUNTIME_API bool nyra_protocol_role_is_listening(nyra_protocol_t *self);

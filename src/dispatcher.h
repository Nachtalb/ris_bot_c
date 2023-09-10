#ifndef DISPATCHER_H
#define DISPATCHER_H
#include "types.h"
#include <stdbool.h>
#include <telebot/telebot-types.h>

#define SIZE_OF_ARRAY(array)    (sizeof(array) / sizeof(array[0]))
#define MAX_HANDLERS    100

/**
 * @brief Array of registered message handlers.
 *
 * Stores all the message handlers that have been registered.
 * Used for dispatching updates to appropriate handlers.
 */
extern message_handler_entry_t registered_handlers[MAX_HANDLERS];
extern int count_registered_handlers;

/**
 * @brief Array of registered command handlers.
 *
 * Stores all the command handlers that have been registered.
 * Used for dispatching commands to appropriate handlers.
 */
extern command_handler_entry_t registered_command_handlers[MAX_HANDLERS];
extern int count_registered_command_handlers;

/**
 * @brief Registers a message handler for a specific message type.
 *
 * @param message_handler The message handler function.
 * @param message_type The type of message to handle.
 * @param accept_commands If the handler should accept command messages.
 */
void register_handler(update_handler_t message_handler,
                      message_type_t message_type, bool accept_commands);

/**
 * @brief Registers a handler for a specific command.
 *
 * @param command_handler The command handler function.
 * @param command The command to handle.
 */
void register_command_handler(command_handler_t command_handler,
                              const char *command);

/**
 * @brief Dispatches updates to appropriate handlers.
 *
 * @param handle The Telegram bot handler.
 * @param update The received update.
 */
void dispatch_update(telebot_handler_t handle, telebot_update_t update);

/**
 * @brief Starts the update dispatching loop.
 *
 * @param handle The Telegram bot handler.
 * @return True if the dispatcher started successfully, otherwise False.
 */
bool start_dispatcher(telebot_handler_t handle);

#endif // DISPATCHER_H

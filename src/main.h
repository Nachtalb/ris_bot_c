#ifndef MAIN_H
#define MAIN_H

#include <telebot/telebot-types.h>

/**
 * @brief Handles incoming text messages and echoes them back.
 *
 * @param handle The Telegram bot handler.
 * @param update The received update.
 */
void echo(telebot_handler_t handle, telebot_update_t update);

/**
 * @brief Handles the '/start' command.
 *
 * @param handle The Telegram bot handler.
 * @param update The received update.
 * @param command The command itself.
 * @param args Additional text following the command.
 */
void start_command(telebot_handler_t handle, telebot_update_t update,
                   const char *command, const char *args);

#endif // MAIN_H

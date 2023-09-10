#include "dispatcher.h"
#include "types.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <telebot/telebot.h>
#include <unistd.h>

message_handler_entry_t registered_handlers[MAX_HANDLERS];
int count_registered_handlers = 0;
command_handler_entry_t registered_command_handlers[MAX_HANDLERS];
int count_registered_command_handlers = 0;

void register_handler(update_handler_t message_handler,
                      message_type_t message_type, bool accept_commands) {
  message_handler_entry_t *entry =
    &registered_handlers[count_registered_handlers];
  entry->type            = message_type;
  entry->handler         = message_handler;
  entry->accept_commands = accept_commands;

  count_registered_handlers++;
}

void register_command_handler(command_handler_t command_handler,
                              const char *command) {
  command_handler_entry_t *entry =
    &registered_command_handlers[count_registered_command_handlers];

  entry->command = command;
  entry->handler = command_handler;

  count_registered_command_handlers++;
}

/**
 * @brief Determines the message type from a Telegram message.
 *
 * @param message The Telegram message.
 * @return The type of the message.
 */
static message_type_t get_message_type(telebot_message_t message) {
  if (message.text) {
    return MESSAGE_TYPE_TEXT;
  } else if (message.photos) {
    return MESSAGE_TYPE_PHOTO;
  } else if (message.audio) {
    return MESSAGE_TYPE_AUDIO;
  } else if (message.video) {
    return MESSAGE_TYPE_VIDEO;
  } else if (message.document) {
    return MESSAGE_TYPE_DOCUMENT;
  } else if (message.voice) {
    return MESSAGE_TYPE_VOICE;
  } else if (message.video_note) {
    return MESSAGE_TYPE_VIDEO_NOTE;
  } else if (message.sticker) {
    return MESSAGE_TYPE_STICKER;
  } else {
    return MESSAGE_TYPE_OTHER;
  }
}

/**
 * @brief Dispatches updates to appropriate handlers.
 *
 * @param handle The Telegram bot handler.
 * @param update The received update.
 */
void dispatch_update(telebot_handler_t handle, telebot_update_t update) {
  telebot_message_t message = update.message;

  message_type_t message_t = get_message_type(message);

  for (int i = 0; i < count_registered_handlers; i++) {
    if (message_t == registered_handlers[i].type && message.text &&
        (registered_handlers[i].accept_commands || message.text[0] != '/')) {
      registered_handlers[i].handler(handle, update);
    }
  }

  if (message_t == MESSAGE_TYPE_TEXT && message.text[0] == '/') {
    char *space = strchr(message.text, ' ');
    char *command, *args;

    if (space) {
      command = strndup(message.text + 1, space - message.text - 1);
      args    = strdup(space + 1);
    } else {
      command = strdup(message.text + 1);
      args    = NULL;
    }

    for (int i = 0; i < count_registered_command_handlers; i++) {
      if (strcmp(command, registered_command_handlers[i].command) == 0) {
        registered_command_handlers[i].handler(handle, update, command, args);
      }
    }

    free(command);
    if (args) {
      free(args);
    }
  }
}

/**
 * @brief Starts the update dispatching loop.
 *
 * @param handle The Telegram bot handler.
 * @return True if the dispatcher started successfully, otherwise False.
 */
bool start_dispatcher(telebot_handler_t handle) {
  int                   count, offset = -1;
  telebot_error_e       ret;
  telebot_update_type_e update_types[] = { TELEBOT_UPDATE_TYPE_MESSAGE };

  while (true) {
    telebot_update_t *updates;
    ret = telebot_get_updates(handle, offset, 20, 0, update_types, 0, &updates,
                              &count);
    if (ret != TELEBOT_ERROR_NONE) {
      continue;
    }

    printf("Number of updates: %d\n", count);
    for (int i = 0; i < count; i++) {
      dispatch_update(handle, updates[i]);

      offset = updates[i].update_id + 1;
    }

    telebot_put_updates(updates, count);
    sleep(1);
  }
}

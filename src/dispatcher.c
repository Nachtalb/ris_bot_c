#include "types.c"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <telebot/telebot.h>
#include <unistd.h>

#define SIZE_OF_ARRAY(array)    (sizeof(array) / sizeof(array[0]))
#define MAX_HANDLERS    100

message_handler_entry_t registered_handlers[MAX_HANDLERS];
int count_registered_handlers = 0;

command_handler_entry_t registered_command_handlers[MAX_HANDLERS];
int count_registered_command_handlers = 0;

void register_handler(update_handler_t message_handler,
                      message_type_t message_type) {
  registered_handlers[count_registered_handlers].type    = message_type;
  registered_handlers[count_registered_handlers].handler = message_handler;
  count_registered_handlers++;
}

void register_command_handler(command_handler_t command_handler,
                              const char *command) {
  registered_command_handlers[count_registered_command_handlers].command =
    command;
  registered_command_handlers[count_registered_command_handlers].handler =
    command_handler;
  count_registered_command_handlers++;
}

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

void dispatch_update(telebot_handler_t handle, telebot_update_t update) {
  telebot_message_t message = update.message;

  message_type_t message_t = get_message_type(message);

  for (int i = 0; i < count_registered_handlers; i++) {
    if (message_t == registered_handlers[i].type) {
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

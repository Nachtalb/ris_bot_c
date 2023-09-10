/**
 * @brief A enum representing some standard message types.
 *
 * Does not oer all possible message types.
 */
#include <stdbool.h>
#include <telebot/telebot-types.h>

typedef enum message_type {
  MESSAGE_TYPE_TEXT = 0,
  MESSAGE_TYPE_PHOTO,
  MESSAGE_TYPE_VIDEO,
  MESSAGE_TYPE_AUDIO,
  MESSAGE_TYPE_DOCUMENT,
  MESSAGE_TYPE_VOICE,
  MESSAGE_TYPE_VIDEO_NOTE,
  MESSAGE_TYPE_STICKER,
  MESSAGE_TYPE_OTHER,
} message_type_t;

typedef void (*update_handler_t)(telebot_handler_t, telebot_update_t);

typedef struct message_handler_entry {
  message_type_t   type;
  update_handler_t handler;
  bool             accept_commands;
} message_handler_entry_t;

typedef void (*command_handler_t)(telebot_handler_t, telebot_update_t,
                                  const char *command, const char *args);

typedef struct command_handler_entry {
  const char *      command;
  command_handler_t handler;
} command_handler_entry_t;

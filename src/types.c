/**
 * @brief A enum representing some standard message types.
 *
 * Does not oer all possible message types.
 */
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

typedef void (*message_handler_t)(telebot_handler_t, telebot_update_t);

typedef struct message_handler_entry {
  message_type_t type;
  message_handler_t handler;
} message_handler_entry_t;

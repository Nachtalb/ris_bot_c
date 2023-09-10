#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <telebot/telebot.h>
#include <unistd.h>

#define SIZE_OF_ARRAY(array) (sizeof(array) / sizeof(array[0]))

bool start_dispatcher(telebot_handler_t handle) {
  int index, count, offset = -1;
  telebot_error_e ret;
  telebot_message_t message;
  telebot_update_type_e update_types[] = {TELEBOT_UPDATE_TYPE_MESSAGE};

  while (true) {
    telebot_update_t *updates;
    ret = telebot_get_updates(handle, offset, 20, 0, update_types, 0, &updates,
                              &count);
    if (ret != TELEBOT_ERROR_NONE)
      continue;

    printf("Number of updates: %d\n", count);
    for (index = 0; index < count; index++) {
      message = updates[index].message;
      if (message.text) {
        printf("%s: %s \n", message.from->first_name, message.text);
        if (strstr(message.text, "/dice")) {
          telebot_send_dice(handle, message.chat->id, false, 0, "");
        } else {

          char str[4096];
          if (strstr(message.text, "/start")) {
            snprintf(str, SIZE_OF_ARRAY(str), "Hello %s",
                     message.from->first_name);
          } else {
            snprintf(str, SIZE_OF_ARRAY(str), "<i>%s</i>", message.text);
          }

          ret = telebot_send_message(handle, message.chat->id, str, "HTML",
                                     false, false,
                                     updates[index].message.message_id, "");
        }

        if (ret != TELEBOT_ERROR_NONE) {
          printf("Failed to send message: %d \n", ret);
        }
      }

      offset = updates[index].update_id + 1;
    }

    telebot_put_updates(updates, count);
    sleep(1);
  }
}

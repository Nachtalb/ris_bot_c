#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <telebot/telebot.h>
#include <unistd.h>

void echo(telebot_handler_t handle, telebot_update_t update) {
  telebot_error_e   ret;
  telebot_message_t message = update.message;

  printf("%s: %s \n", message.from->first_name, message.text);

  if (strstr(message.text, "/dice")) {
    ret = telebot_send_dice(handle, message.chat->id, false, 0, "");
  } else {
    char *str;
    asprintf(&str, "<i>%s</i>", message.text);

    ret = telebot_send_message(handle, message.chat->id, str, "HTML", false,
                               false, update.message.message_id, "");
    free(str);
  }

  if (ret != TELEBOT_ERROR_NONE) {
    printf("Failed to send message: %d \n", ret);
  }
}

void start_command(telebot_handler_t handle, telebot_update_t update,
                   const char *command, const char *args) {
  telebot_error_e   ret;
  telebot_message_t message = update.message;

  char *str;
  asprintf(&str, "Hello %s", message.from->first_name);
  ret = telebot_send_message(handle, message.chat->id, str, "HTML", false,
                             false, update.message.message_id, "");
  free(str);

  if (ret != TELEBOT_ERROR_NONE) {
    printf("Failed to send message: %d \n", ret);
  }
}

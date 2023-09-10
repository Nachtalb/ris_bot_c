#include "dispatcher.c"
#include <pthread.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <telebot/telebot-types.h>
#include <telebot/telebot.h>
#include <unistd.h>

void echo(telebot_handler_t handle, telebot_update_t update) {
  telebot_error_e ret;
  telebot_message_t message = update.message;
  printf("%s: %s \n", message.from->first_name, message.text);
  if (strstr(message.text, "/dice")) {
    telebot_send_dice(handle, message.chat->id, false, 0, "");
  } else {

    char str[4096];
    if (strstr(message.text, "/start")) {
      snprintf(str, SIZE_OF_ARRAY(str), "Hello %s", message.from->first_name);
    } else {
      snprintf(str, SIZE_OF_ARRAY(str), "<i>%s</i>", message.text);
    }

    ret = telebot_send_message(handle, message.chat->id, str, "HTML", false,
                               false, update.message.message_id, "");
  }

  if (ret != TELEBOT_ERROR_NONE) {
    printf("Failed to send message: %d \n", ret);
  }
}

int main(int argc, char *argv[]) {
  printf("Welcome to Echobot\n");

  FILE *file = fopen(".token", "r");
  if (file == NULL) {
    printf("File not found\n");
    return 1;
  }

  char token[47];
  size_t read = fread(token, 1, 46, file);
  token[read] = '\0';

  fclose(file);
  printf("Content: %s\n", token);

  telebot_handler_t handle;
  if (telebot_create(&handle, token) != TELEBOT_ERROR_NONE) {
    printf("Telebot create failed\n");
    return -1;
  }

  telebot_user_t me;
  if (telebot_get_me(handle, &me) != TELEBOT_ERROR_NONE) {
    printf("Failed to get bot information\n");
    telebot_destroy(handle);
    return -1;
  }

  printf("ID: %d\n", me.id);
  printf("First Name: %s\n", me.first_name);
  printf("User Name: %s\n", me.username);

  telebot_put_me(&me);

  register_handler(echo, MESSAGE_TYPE_TEXT);

  if (start_dispatcher(handle) == false) {
    return -1;
  }
  return 0;
}

#include "dispatcher.h"
#include "handler.h"
#include <stdbool.h>
#include <stdio.h>
#include <telebot/telebot.h>

int main(int argc, char *argv[]) {
  printf("Welcome to Echobot\n");

  FILE *file = fopen(".token", "r");
  if (file == NULL) {
    printf("File not found\n");
    return 1;
  }

  char   token[47];
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

  register_handler(echo, MESSAGE_TYPE_TEXT, false);
  register_command_handler(start_command, "start");

  if (start_dispatcher(handle) == false) {
    return -1;
  }
  return 0;
}

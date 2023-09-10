#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <telebot/telebot.h>
#include <unistd.h>

#define SIZE_OF_ARRAY(array) (sizeof(array) / sizeof(array[0]))

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

  telebot_destroy(handle);
  printf("Done\n");

  return 0;
}

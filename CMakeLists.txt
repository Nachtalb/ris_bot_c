cmake_minimum_required(VERSION 3.10)
project(ris_bot)

add_subdirectory(third_party/telebot)

set(SRC src/main.c)

add_executable(${PROJECT_NAME} ${SRC})

target_link_libraries(${PROJECT_NAME} ${PKGS_LDFLAGS} telebot pthread)
target_include_directories(${PROJECT_NAME} PRIVATE third_party/telebot/include)

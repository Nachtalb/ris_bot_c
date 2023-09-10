cmake_minimum_required(VERSION 3.10)
project(ris_bot)

add_subdirectory(third_party/telebot)

set(SRC src/main.c)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(${PROJECT_NAME} ${SRC})

target_include_directories(${PROJECT_NAME} PRIVATE third_party/telebot/include)
target_link_libraries(${PROJECT_NAME} ${PKGS_LDFLAGS} telebot pthread)

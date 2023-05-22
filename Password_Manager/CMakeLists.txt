cmake_minimum_required(VERSION 3.23)
project(Manager_hasel)

set(CMAKE_CXX_STANDARD 23)

add_executable(Manager_hasel main.cpp pjc_z4.cpp pjc_z4.h Password.cpp Password.h PasswordStorage.cpp PasswordStorage.h PasswordCategory.cpp PasswordCategory.h)

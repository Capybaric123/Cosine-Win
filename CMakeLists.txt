cmake_minimum_required(VERSION 3.20)

project(Cosine-Win)

set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)
set(CMAKE_C_STANDARD 99)

file(GLOB SRC CONFIGURE_DEPENDS
        ${CMAKE_SOURCE_DIR}/src/*.c
)

add_executable(Cosine ${SRC})

target_include_directories(Cosine PRIVATE
        ${CMAKE_SOURCE_DIR}/include
)

target_link_libraries(Cosine PRIVATE
        "${CMAKE_SOURCE_DIR}/lib/libglfw3.a"
        gdi32
        kernel32
        user32
        shell32
)
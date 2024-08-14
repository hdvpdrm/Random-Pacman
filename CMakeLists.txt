cmake_minimum_required(VERSION 3.10)
project(random_pacman)
set (CMAKE_CXX_STANDARD 17)

set(SOURCE Window.cpp Pacman.cpp MazeGenerator.cpp GhostWalker.cpp Character.cpp TextDrawer.cpp main.cpp )
set(HEADERS  MazeGenerator.h Window.h Pacman.h GhostWalker.h Character.h rand.h TextDrawer.h)

add_link_options(-lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio)
add_executable(random_pacman ${SOURCE} ${HEADERS}) 

cmake_minimum_required(VERSION 2.8)
project(sdl2_image_test)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)

include_directories(${SDL2_INCLUDE_DIRS} ${SDL2IMAGE_INCLUDE_DIRS})

add_executable(sdl2_image_test main.c)

target_link_libraries(sdl2_image_test
  ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES})

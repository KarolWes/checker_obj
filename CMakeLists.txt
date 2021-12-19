
cmake_minimum_required(VERSION 3.20)
project(checker_obj)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

add_executable(checker_obj main.cpp Slot.cpp Slot.h Drawable.cpp Drawable.h BasePawn.cpp BasePawn.h Pawn.cpp Pawn.h Queen.cpp Queen.h Game.cpp Game.h Button.cpp Button.h)
include_directories("/usr/include/allegro5")
target_link_libraries(checker_obj "/usr/lib/x86_64-linux-gnu/liballegro.so")
target_link_libraries(checker_obj "/usr/lib/x86_64-linux-gnu/liballegro_acodec.so")
target_link_libraries(checker_obj "/usr/lib/x86_64-linux-gnu/liballegro_audio.so")
target_link_libraries(checker_obj "/usr/lib/x86_64-linux-gnu/liballegro_color.so")
target_link_libraries(checker_obj "/usr/lib/x86_64-linux-gnu/liballegro_dialog.so")
target_link_libraries(checker_obj "/usr/lib/x86_64-linux-gnu/liballegro_font.so")
target_link_libraries(checker_obj "/usr/lib/x86_64-linux-gnu/liballegro_image.so")
target_link_libraries(checker_obj "/usr/lib/x86_64-linux-gnu/liballegro_main.so")
target_link_libraries(checker_obj "/usr/lib/x86_64-linux-gnu/liballegro_memfile.so")
target_link_libraries(checker_obj "/usr/lib/x86_64-linux-gnu/liballegro_physfs.so")
target_link_libraries(checker_obj "/usr/lib/x86_64-linux-gnu/liballegro_primitives.so")
target_link_libraries(checker_obj "/usr/lib/x86_64-linux-gnu/liballegro_ttf.so")
target_link_libraries(checker_obj "/usr/lib/x86_64-linux-gnu/liballegro_video.so")


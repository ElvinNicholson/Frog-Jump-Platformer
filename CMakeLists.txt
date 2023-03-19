cmake_minimum_required(VERSION 3.14)
project(PlatformerSFML)

set(CMAKE_CXX_STANDARD 14)

if(WIN32)
    set(SFML_STATIC_LIBRARIES TRUE)
    set(CMAKE_EXE_LINKER_FLAGS "-static")
endif()


find_package(SFML 2.5.1 COMPONENTS system window graphics network audio)
set(SOURCE_FILES src/main.cpp src/Game.cpp src/Game.h src/Gamestate.h src/Gameplay.cpp src/Gameplay.h src/Gameobjects/Tittle.cpp src/Gameobjects/Tittle.h src/Gameobjects/Gameobject.cpp src/Gameobjects/Gameobject.h src/Gameobjects/Block.cpp src/Gameobjects/Block.h src/Gameobjects/Player.cpp src/Gameobjects/Player.h src/Gameobjects/Mushroom.cpp src/Gameobjects/Mushroom.h src/GameplayMenu.cpp src/GameplayMenu.h src/Gameobjects/Collectible.cpp src/Gameobjects/Collectible.h src/Gameobjects/CollectibleType.h src/Gameobjects/Door.cpp src/Gameobjects/Door.h src/Gameobjects/BlockType.h src/Gameobjects/SpikedBall.cpp src/Gameobjects/SpikedBall.h src/Level.h src/GameplayAudio.cpp src/GameplayAudio.h)
add_executable(PlatformerSFML ${SOURCE_FILES})

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_modules")

target_link_libraries (PlatformerSFML sfml-graphics sfml-window sfml-system sfml-network sfml-audio)
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/Data/ DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/Data/)
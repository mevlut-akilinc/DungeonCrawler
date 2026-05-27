cmake_minimum_required(VERSION 3.10)
project(DungeonCrawler)

set(CMAKE_CXX_STANDARD 17)

set(SFML_DIR "C:/SFML/lib/cmake/SFML")

find_package(SFML 2.6 COMPONENTS system window graphics REQUIRED)

add_executable(DungeonCrawler
    src/main.cpp
    src/Tile.cpp
    src/Map.cpp
    src/MapGenerator.cpp
    src/Entity.cpp
    src/Enemy.cpp
    src/EnemyManager.cpp
    src/SaveManager.cpp
    src/Player.cpp
    src/GameObject.cpp
    src/Inventory.cpp
    src/TextureManager.cpp
    src/HUD.cpp
    src/FloorFactory.cpp
    src/InputHandler.cpp
    src/Menu.cpp
    src/DamageFeedback.cpp
)

add_custom_command(TARGET DungeonCrawler POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/assets $<TARGET_FILE_DIR:DungeonCrawler>/assets
)

target_include_directories(DungeonCrawler PRIVATE include)

target_link_libraries(DungeonCrawler sfml-system sfml-window sfml-graphics)

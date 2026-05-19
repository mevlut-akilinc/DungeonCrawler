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
)

target_include_directories(DungeonCrawler PRIVATE include)

target_link_libraries(DungeonCrawler sfml-system sfml-window sfml-graphics)

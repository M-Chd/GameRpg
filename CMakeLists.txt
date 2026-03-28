cmake_minimum_required(VERSION 3.14)
project(GameRpg LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)

add_executable(${PROJECT_NAME}
    src/main.cpp
    src/core/board.cpp
    src/core/entityManager.cpp
    src/core/textureManager.cpp
    src/core/window.cpp
    src/entities/enemy.cpp
    src/entities/healItem.cpp
    src/entities/player.cpp
    src/entities/stats.cpp
    src/entities/swordItem.cpp
    src/systems/combat.cpp
    src/systems/input.cpp
    src/systems/inventory.cpp
    src/ui/view.cpp
)

# Include (headers + SDL)
target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_SOURCE_DIR}/headers
    ${CMAKE_SOURCE_DIR}/include
)

# Link SDL manuellement
target_link_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_SOURCE_DIR}/lib
)

target_link_libraries(${PROJECT_NAME}
    SDL2
    SDL2main
    SDL2_image
    SDL2_ttf
)

# Copy assets
file(COPY assets DESTINATION ${CMAKE_BINARY_DIR})
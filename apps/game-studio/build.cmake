add_executable(game-studio apps/game-studio/src/main.cpp apps/game-studio/src/app.cpp)
target_include_directories(game-studio PRIVATE apps/game-studio/include)
add_wxWidgets(game-studio)
add_dependencies(game-studio cmake-portable)
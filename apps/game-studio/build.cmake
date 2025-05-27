file(
    GLOB_RECURSE BOUNT_GAME_STUDIO_SRC
    "apps/game-studio/src/**.c++"
    "apps/game-studio/src/**.cpp"
    "apps/game-studio/src/**.cxx"
    "apps/game-studio/src/**.cc"
)

add_executable(game-studio ${BOUNT_GAME_STUDIO_SRC})
target_include_directories(game-studio PRIVATE apps/game-studio/include dev/include)
target_link_libraries(game-studio PRIVATE bount::core ${wxWidgets_CORE_LIBS})
add_wxWidgets(game-studio)
add_dependencies(game-studio cmake-portable)
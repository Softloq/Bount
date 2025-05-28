cmake_minimum_required(VERSION 4.0)
include(FetchContent)

project(bount-software-suite VERSION 0.0.0)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)
set(CMAKE_CXX_EXTENSIONS OFF)

# Third-parties

set(FETCHCONTENT_BASE_DIR "${CMAKE_CURRENT_BINARY_DIR}/thirdparty")

# --------- googletest ----------
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG v1.17.0
)
# Prevent Google Test from "installing" itself
set(gtest_force_shared_crt ON CACHE INTERNAL "")
FetchContent_MakeAvailable(googletest)

# --------- wxWidgets ----------
set(wxWidgets_USE_STATIC 1)
set(wxBUILD_SHARED OFF)
FetchContent_Declare(
    wxWidgets
    GIT_REPOSITORY https://github.com/wxWidgets/wxWidgets.git
    GIT_TAG v3.2.8
    SOURCE_DIR "${CMAKE_CURRENT_BINARY_DIR}/thirdparty/wxWidgets-src"
    BINARY_DIR "${CMAKE_CURRENT_BINARY_DIR}/thirdparty/wxWidgets-src"
)
FetchContent_MakeAvailable(wxWidgets)

list(APPEND wxWidgets_CORE_LIBS wx::base wx::core wx::html wx::richtext wx::xrc)
function(add_wxWidgets tgt)
    target_compile_definitions(${tgt} PRIVATE _UNICODE=1)
    target_include_directories(${tgt} PRIVATE "${wxWidgets_SOURCE_DIR}/include/msvc" "${wxWidgets_SOURCE_DIR}/include")
    target_link_directories(${tgt} PRIVATE "${wxWidgets_SOURCE_DIR}/lib/vc_x64_lib")
    add_dependencies(${tgt} wx::base wx::core wx::html wx::richtext wx::xrc)
endfunction()

# --------- glew ----------
if(MSVC)
    if(NOT EXISTS "${CMAKE_CURRENT_BINARY_DIR}/thirdparty/glew.zip")
        file(
            DOWNLOAD
            "https://github.com/nigels-com/glew/releases/download/glew-2.2.0/glew-2.2.0-win32.zip"
            "${CMAKE_CURRENT_BINARY_DIR}/thirdparty/glew.zip"
            SHOW_PROGRESS
        )
    endif()
endif()

add_custom_target(
    glew-lib
    COMMAND ${CMAKE_COMMAND}
        -DCONFIG="$<CONFIG>"
        -DCOMPILER="${CMAKE_CXX_COMPILER_ID}"
        -P "${CMAKE_CURRENT_SOURCE_DIR}/cmake-scripts/glew.cmake"
)

add_library(glew INTERFACE)
add_dependencies(glew glew-lib)
target_include_directories(glew INTERFACE "${CMAKE_CURRENT_BINARY_DIR}/thirdparty/glew/glew-2.2.0/include")
target_link_libraries(glew INTERFACE glew32)

# --------- cmake portable ----------
set(CMAKE_PORTABLE_VERSION 4.0.2)
if(NOT EXISTS "${CMAKE_CURRENT_BINARY_DIR}/thirdparty/cmake-v${CMAKE_PORTABLE_VERSION}.zip")
    file(
        DOWNLOAD
        "https://github.com/Kitware/CMake/releases/download/v${CMAKE_PORTABLE_VERSION}/cmake-${CMAKE_PORTABLE_VERSION}-windows-x86_64.zip"
        "${CMAKE_CURRENT_BINARY_DIR}/thirdparty/cmake-v${CMAKE_PORTABLE_VERSION}.zip"
        SHOW_PROGRESS
    )
endif()

if(NOT EXISTS "${CMAKE_CURRENT_BINARY_DIR}/Debug/cmake")
    add_custom_target(
        cmake-portable
        COMMAND ${CMAKE_COMMAND} -E tar xzf
                "${CMAKE_CURRENT_BINARY_DIR}/thirdparty/cmake-v${CMAKE_PORTABLE_VERSION}.zip"
        COMMAND ${CMAKE_COMMAND} -E remove_directory
                "${CMAKE_CURRENT_BINARY_DIR}/$<CONFIG>/cmake"
        COMMAND ${CMAKE_COMMAND} -E rename
                "${CMAKE_CURRENT_BINARY_DIR}/$<CONFIG>/cmake-${CMAKE_PORTABLE_VERSION}-windows-x86_64"
                "${CMAKE_CURRENT_BINARY_DIR}/$<CONFIG>/cmake"
        WORKING_DIRECTORY "$<CONFIG>"
    )
else()
    add_custom_target(cmake-portable)
endif()

# --------- bount-core ----------
file(
    GLOB_RECURSE BOUNT_CORE_SRC
    "dev/src/bount-filesystem/**.c++"
    "dev/src/bount-filesystem/**.cpp"
    "dev/src/bount-filesystem/**.cxx"
    "dev/src/bount-filesystem/**.cc"
)

add_library(bount-core SHARED ${BOUNT_CORE_SRC})
target_include_directories(bount-core PRIVATE "dev/include")
target_link_directories(bount-core PUBLIC "${CMAKE_CURRENT_BINARY_DIR}/lib/$<CONFIG>")
target_compile_definitions(
    bount-core
    PRIVATE BOUNT_CORE_BUILD_API
    PUBLIC  BOUNT_CORE_USE_API
)
set_target_properties(
    bount-core PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/lib"
    ARCHIVE_OUTPUT_DIRECTORY_DEBUG "${CMAKE_CURRENT_BINARY_DIR}/lib/Debug"
    ARCHIVE_OUTPUT_DIRECTORY_RELEASE "${CMAKE_CURRENT_BINARY_DIR}/lib/Release"
)
target_precompile_headers(bount-core PRIVATE "dev/include/bount-lib/core/precompiled.hpp")
add_library(bount::core ALIAS bount-core)

# --------- bount-gl ----------
file(
    GLOB_RECURSE BOUNT_GL_SRC
    "dev/src/bount-gl/**.c++"
    "dev/src/bount-gl/**.cpp"
    "dev/src/bount-gl/**.cxx"
    "dev/src/bount-gl/**.cc"
)

add_library(bount-gl SHARED ${BOUNT_GL_SRC})
add_dependencies(bount-gl bount-core glew)
target_include_directories(bount-gl PRIVATE "dev/include")
target_compile_definitions(
    bount-gl
    PRIVATE BOUNT_GL_BUILD_API
    PUBLIC  BOUNT_GL_USE_API
)
target_link_libraries(bount-gl PUBLIC bount-core glew)
set_target_properties(
    bount-gl PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/lib"
    ARCHIVE_OUTPUT_DIRECTORY_DEBUG "${CMAKE_CURRENT_BINARY_DIR}/lib/Debug"
    ARCHIVE_OUTPUT_DIRECTORY_RELEASE "${CMAKE_CURRENT_BINARY_DIR}/lib/Release"
)
target_precompile_headers(bount-gl PRIVATE "dev/include/bount-lib/gl/precompiled.hpp")
add_library(bount::gl ALIAS bount-gl)

# --------- unit tests ----------
add_executable(wxWidgets-window-ci tests/wxWidgets/window/main.cpp)
add_wxWidgets(wxWidgets-window-ci)

foreach(app IN ITEMS game-studio item-database map-editor mechanic-scripter skill-crafter ui-designer unit-modeller)
    include(apps/${app}/build.cmake)
endforeach()

include(CTest)
enable_testing()
add_test(NAME wxWidgets-Window COMMAND wxWidgets-window-ci)

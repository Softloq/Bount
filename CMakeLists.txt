cmake_minimum_required(VERSION 4.0)
include(FetchContent)

project(bount-software-suite VERSION 0.0.0)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)
set(CMAKE_CXX_EXTENSIONS OFF)

# Third-parties

set(FETCHCONTENT_BASE_DIR "${CMAKE_CURRENT_BINARY_DIR}/thirdparty")

# Download and Compile googletest
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG v1.17.0
)
# Prevent Google Test from "installing" itself
set(gtest_force_shared_crt ON CACHE INTERNAL "")
FetchContent_MakeAvailable(googletest)

# Download and Compile wxWidgets
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

# Download and Extract CMake for portable use
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

file(
    GLOB_RECURSE BOUNT_CORE_SRC
    "dev/src/bount-filesystem/**.c++"
    "dev/src/bount-filesystem/**.cpp"
    "dev/src/bount-filesystem/**.cxx"
    "dev/src/bount-filesystem/**.cc"
)

add_library(bount-core SHARED ${BOUNT_CORE_SRC})
target_include_directories(bount-core PRIVATE "dev/include")
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

add_executable(wxWidgets-window-ci tests/wxWidgets/window/main.cpp)
add_wxWidgets(wxWidgets-window-ci)

foreach(app IN ITEMS game-studio item-database map-editor mechanic-scripter skill-crafter ui-designer unit-modeller)
    include(apps/${app}/build.cmake)
endforeach()

include(CTest)
enable_testing()
add_test(NAME wxWidgets-Window COMMAND wxWidgets-window-ci)

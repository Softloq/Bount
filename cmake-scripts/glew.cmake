if(NOT EXISTS "${CMAKE_CURRENT_BINARY_DIR}/thirdparty/glew")
    file(ARCHIVE_EXTRACT INPUT "${CMAKE_CURRENT_BINARY_DIR}/thirdparty/glew.zip" DESTINATION "${CMAKE_CURRENT_BINARY_DIR}/thirdparty/glew")
endif()

if(COMPILER STREQUAL "MSVC")
    if(NOT EXISTS "${CMAKE_CURRENT_BINARY_DIR}/${CONFIG}/glew32.dll")
        execute_process(
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
                    "${CMAKE_CURRENT_BINARY_DIR}/thirdparty/glew/glew-2.2.0/bin/Release/x64/glew32.dll"
                    "${CMAKE_CURRENT_BINARY_DIR}/${CONFIG}/glew32.dll"
        )
    endif()

    if(NOT EXISTS "${CMAKE_CURRENT_BINARY_DIR}/lib/${CONFIG}/glew32.lib")
        execute_process(
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
                    "${CMAKE_CURRENT_BINARY_DIR}/thirdparty/glew/glew-2.2.0/lib/Release/x64/glew32.lib"
                    "${CMAKE_CURRENT_BINARY_DIR}/lib/${CONFIG}/glew32.lib"
        )
    endif()
endif()

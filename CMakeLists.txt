cmake_minimum_required(VERSION 4.3.1 FATAL_ERROR)

# https://github.com/Kitware/CMake/blob/master/Help/dev/experimental.rst
set(CMAKE_EXPERIMENTAL_CXX_IMPORT_STD "451f2fe2-a8a2-47c3-bc32-94786d8fc91b")
project(lys LANGUAGES CXX)

include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/VulkanSetup.cmake)
include(${CMAKE_CURRENT_SOURCE_DIR}/vendor/toolbox/cmake/CodeQuality.cmake)

#####################
# Compiler settings #
#####################
set(CMAKE_CXX_STANDARD 26)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_MODULE_STD ON)

if (PROJECT_IS_TOP_LEVEL)
    set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
endif ()

if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    if (CMAKE_CXX_COMPILER_VERSION VERSION_LESS 21)
        message(FATAL_ERROR
                "Clang >= 21 is required. "
                "Detected version: ${CMAKE_CXX_COMPILER_VERSION}"
        )
    endif ()
else ()
    message(FATAL_ERROR
            "Using an unsupported compiler!"
    )
endif ()

###########
# Options #
###########

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/vendor/lum)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/vendor/mag)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/vendor/glfw)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/engine)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/sandbox)

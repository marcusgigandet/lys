# Due to import std; being experimental, only a select few versions of cmake are currently supported.
# See the following map of supported versions.
#
# Note: Once this feature is no longer experimental, all support for older cmake versions will be dropped
# and the requirement will be raised to that new cmake version.
cmake_minimum_required(VERSION 4.3.1 FATAL_ERROR)

# https://github.com/Kitware/CMake/blob/master/Help/dev/experimental.rst
set(CMAKE_EXPERIMENTAL_CXX_IMPORT_STD "451f2fe2-a8a2-47c3-bc32-94786d8fc91b")

set(_experimental_hash_4_3_1 "451f2fe2-a8a2-47c3-bc32-94786d8fc91b")
set(_experimental_hash_4_3_2 "451f2fe2-a8a2-47c3-bc32-94786d8fc91b")
set(_experimental_hash_4_3_3 "451f2fe2-a8a2-47c3-bc32-94786d8fc91b")
set(_experimental_hash_4_3_4 "451f2fe2-a8a2-47c3-bc32-94786d8fc91b")
set(_experimental_hash_4_4_0 "1942b4fa-b2c5-4546-9385-83f254070067")
set(_experimental_hash_4_4_1 "f35a9ac6-8463-4d38-8eec-5d6008153e7d")
set(_experimental_hash_4_4_2 "f35a9ac6-8463-4d38-8eec-5d6008153e7d")

string(REPLACE "." "_" _version "${CMAKE_VERSION}")

set(_var "_experimental_hash_${_version}")

if (NOT DEFINED ${_var})
    message(FATAL_ERROR "No experimental hash for CMake ${CMAKE_VERSION}")
endif ()

set(CMAKE_EXPERIMENTAL_EXPORT_PACKAGE_INFO "${${_var}}")

project(lys LANGUAGES CXX)

###################
# Project Options #
###################

option(LYS_VULKAN "Build with Vulkan support" $<NOT:$<BOOL:${APPLE}>>)
option(LYS_METAL "Build with Metal support" $<BOOL:${APPLE}>)

# Ensure that non-macOS systems are using Vulkan
if (NOT APPLE)
    set(LYS_METAL OFF)
    set(LYS_VULKAN ON)
    message("Defaulting to Vulkan due to unsupported platform for Metal.")
endif ()

##################
# CMake includes #
##################

if (${LYS_METAL})
    include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/MetalSetup.cmake)
else ()
    include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/VulkanSetup.cmake)
endif ()

include(${CMAKE_CURRENT_SOURCE_DIR}/vendor/toolbox/cmake/CodeQuality.cmake)

#####################
# Compiler settings #
#####################

set(CMAKE_CXX_STANDARD 26)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
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

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/vendor/spdlog)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/vendor/mag)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/vendor/glfw)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/engine)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/sandbox)

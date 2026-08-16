# Due to import std; being experimental, only a select few versions of cmake are currently supported.
# See the following map of supported versions.
#
# Note: Once this feature is no longer experimental, all support for older cmake versions will be dropped
# and the requirement will be raised to that new cmake version.
cmake_minimum_required(VERSION 4.3.1 FATAL_ERROR)

# https://github.com/Kitware/CMake/blob/master/Help/dev/experimental.rst
set(_experimental_import_std_hash_4_3_1 "451f2fe2-a8a2-47c3-bc32-94786d8fc91b")
set(_experimental_import_std_hash_4_3_2 "451f2fe2-a8a2-47c3-bc32-94786d8fc91b")
set(_experimental_import_std_hash_4_3_3 "451f2fe2-a8a2-47c3-bc32-94786d8fc91b")
set(_experimental_import_std_hash_4_3_4 "451f2fe2-a8a2-47c3-bc32-94786d8fc91b")
set(_experimental_import_std_hash_4_4_0 "f35a9ac6-8463-4d38-8eec-5d6008153e7d")
set(_experimental_import_std_hash_4_4_1 "f35a9ac6-8463-4d38-8eec-5d6008153e7d")
set(_experimental_import_std_hash_4_4_2 "f35a9ac6-8463-4d38-8eec-5d6008153e7d")

string(REPLACE "." "_" _version "${CMAKE_VERSION}")

set(_import_std_var "_experimental_import_std_hash_${_version}")

if (NOT DEFINED ${_import_std_var})
    message(FATAL_ERROR "No import std experimental hash for CMake ${CMAKE_VERSION}")
endif ()

set(CMAKE_EXPERIMENTAL_CXX_IMPORT_STD "${${_import_std_var}}")

# On macOS, the libc++.modules.json may not be found, so this check resolves it using absolute pathing
if (APPLE AND NOT DEFINED CMAKE_CXX_STDLIB_MODULES_JSON)
    foreach (_modules_json_candidate
            "/opt/homebrew/opt/llvm/lib/c++/libc++.modules.json"
            "/usr/local/opt/llvm/lib/c++/libc++.modules.json")
        if (EXISTS "${_modules_json_candidate}")
            set(CMAKE_CXX_STDLIB_MODULES_JSON "${_modules_json_candidate}")
            break()
        endif ()
    endforeach ()

    add_compile_options(-Wno-reserved-module-identifier)
endif ()

project(lys LANGUAGES CXX)

###################
# Project Options #
###################

if (APPLE)
    option(LYS_VULKAN "Build with Vulkan support" OFF)
    option(LYS_METAL "Build with Metal support" ON)
else ()
    option(LYS_VULKAN "Build with Vulkan support" ON)
    option(LYS_METAL "Build with Metal support" OFF)
endif ()

# Ensure that non-macOS systems are using Vulkan
if (NOT APPLE)
    set(LYS_METAL OFF)
    set(LYS_VULKAN ON)
    message("Defaulting to Vulkan due to unsupported platform for Metal.")
endif ()

##################
# CMake includes #
##################

if (LYS_METAL)
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

##############################
# Check for a valid compiler #
##############################

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

#################
# Find packages #
#################

find_package(glfw3 CONFIG REQUIRED)
find_package(spdlog CONFIG REQUIRED)
find_package(Stb REQUIRED)

##################
# Subdirectories #
##################

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/vendor/mag)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/engine)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/sandbox)

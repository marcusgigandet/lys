function(link_metal)
    set(options "")
    set(oneValueArgs TARGET)
    set(multiValueArgs "")
    cmake_parse_arguments(ARG "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

    if (NOT APPLE)
        return()
    endif ()

    set(METAL_CPP_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../vendor/metal-cpp")

    target_include_directories(${ARG_TARGET} PRIVATE "${METAL_CPP_DIR}")

    find_library(COCOA_LIBRARY Cocoa REQUIRED)
    find_library(METAL_LIBRARY Metal REQUIRED)
    find_library(METAL_KIT_LIBRARY MetalKit REQUIRED)
    find_library(QUARTZ_CORE_LIBRARY QuartzCore REQUIRED)
    find_library(METAL_FX_LIBRARY MetalFX REQUIRED)

    target_link_libraries(${ARG_TARGET}
            PRIVATE
            ${COCOA_LIBRARY}
            ${METAL_LIBRARY}
            ${METAL_KIT_LIBRARY}
            ${QUARTZ_CORE_LIBRARY}
            ${METAL_FX_LIBRARY}
    )
endfunction()
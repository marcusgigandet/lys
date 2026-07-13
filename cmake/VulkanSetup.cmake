function(link_vulkan)
    set(options "")
    set(oneValueArgs TARGET)
    set(multiValueArgs "")
    cmake_parse_arguments(ARG "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

    if (TARGET VulkanCppModule)
        target_link_libraries(${ARG_TARGET_NAME} PRIVATE Vulkan::cppm)
        return()
    endif ()

    find_package(Vulkan REQUIRED)

    add_library(VulkanCppModule)
    add_library(Vulkan::cppm ALIAS VulkanCppModule)

    target_include_directories(VulkanCppModule PRIVATE "${Vulkan_INCLUDE_DIR}")

    target_link_libraries(VulkanCppModule PRIVATE Vulkan::Vulkan)

    set_target_properties(VulkanCppModule PROPERTIES CXX_STANDARD ${CMAKE_CXX_STANDARD})

    target_compile_definitions(VulkanCppModule
            PRIVATE
            VULKAN_HPP_DISPATCH_LOADER_DYNAMIC
            VULKAN_HPP_NO_STRUCT_CONSTRUCTORS
    )

    target_sources(VulkanCppModule
            PUBLIC
            FILE_SET cxx_modules TYPE CXX_MODULES
            BASE_DIRS "${Vulkan_INCLUDE_DIR}"
            FILES
            "${Vulkan_INCLUDE_DIR}/vulkan/vulkan.cppm"
            "${Vulkan_INCLUDE_DIR}/vulkan/vulkan_video.cppm"
    )

    target_link_libraries(${ARG_TARGET} PRIVATE Vulkan::cppm)
endfunction()
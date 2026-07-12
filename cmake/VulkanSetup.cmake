function(link_vulkan)
    set(options "")
    set(oneValueArgs TARGET)
    set(multiValueArgs "")
    cmake_parse_arguments(ARG "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

    if (TARGET VulkanCppModule)
        target_link_libraries(${ARG_TARGET_NAME} PRIVATE Vulkan::cppm VulkanLoader)
        return()
    endif ()

    find_package(Vulkan REQUIRED)

    add_library(VulkanLoader SHARED IMPORTED)
    set_target_properties(VulkanLoader PROPERTIES
            IMPORTED_LOCATION "${Vulkan_LIBRARY}"
    )

    add_library(VulkanCppModule)
    add_library(Vulkan::cppm ALIAS VulkanCppModule)

    target_include_directories(VulkanCppModule PRIVATE "${Vulkan_INCLUDE_DIR}")

    target_link_libraries(VulkanCppModule PRIVATE Vulkan::Vulkan VulkanLoader)

    set_target_properties(VulkanCppModule PROPERTIES CXX_STANDARD ${CMAKE_CXX_STANDARD})

    target_compile_definitions(VulkanCppModule
            PRIVATE
            VULKAN_HPP_NO_STRUCT_CONSTRUCTORS
            VULKAN_HPP_NO_STD_MODULE
            VULKAN_HPP_NO_EXCEPTIONS
            VULKAN_HPP_NO_SMART_HANDLE
            VULKAN_HPP_NO_CONSTRUCTORS
            ENABLE_CPP20_MODULE
    )

    target_sources(VulkanCppModule
            PUBLIC
            FILE_SET cxx_modules TYPE CXX_MODULES
            BASE_DIRS "${Vulkan_INCLUDE_DIR}"
            FILES "${Vulkan_INCLUDE_DIR}/vulkan/vulkan.cppm"
    )

    target_link_libraries(${ARG_TARGET} PRIVATE Vulkan::cppm VulkanLoader)
endfunction()
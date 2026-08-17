########################
# Collect source files #
########################

file(GLOB_RECURSE SANDBOX_MODULES CONFIGURE_DEPENDS
        ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cppm
        ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
)

file(GLOB_RECURSE SANDBOX_SHADERS CONFIGURE_DEPENDS
        ${CMAKE_CURRENT_SOURCE_DIR}/shaders/*.metal
)

##################################
# Executable Setup - Lys Sandbox #
##################################

add_executable(lys_sandbox)
target_sources(lys_sandbox
        PUBLIC
        FILE_SET cxx_modules
        TYPE CXX_MODULES
        FILES ${SANDBOX_MODULES}
)

target_include_directories(lys_sandbox
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_link_libraries(lys_sandbox
        PRIVATE
        lys::engine
        spdlog::spdlog
)

####################################
# Copy resource files to build dir #
####################################

if (${CMAKE_BUILD_TYPE} STREQUAL "Debug")
    foreach(dir assets shaders)
        add_custom_command(
                TARGET lys_sandbox POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E remove_directory $<TARGET_FILE_DIR:lys_sandbox>/${dir}
                COMMAND ${CMAKE_COMMAND} -E create_symlink
                ${CMAKE_CURRENT_SOURCE_DIR}/${dir}
                $<TARGET_FILE_DIR:lys_sandbox>/${dir}
                COMMENT "Symlinking ./${dir} -> build/Debug/${dir}"
        )
    endforeach()
else()
    file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/assets DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
    file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/shaders DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
endif()

#############################
# Code Quality Enforcements #
#############################

enforce_clang_format(
        TARGET lys_sandbox
        FILES ${SANDBOX_MODULES} ${SANDBOX_SHADERS}
)
enforce_copyright(
        TARGET lys_sandbox
        CONFIG_FILE "${CMAKE_CURRENT_SOURCE_DIR}/../config.toml"
        SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}"
)
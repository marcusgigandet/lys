file(GLOB_RECURSE SANDBOX_MODULES CONFIGURE_DEPENDS
        ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cppm
        ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
)

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

if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    target_compile_options(lys_sandbox PRIVATE -fmodules -freflection)
endif ()

target_link_libraries(lys_sandbox
        PRIVATE
        lys::engine
        spdlog::spdlog
)

enforce_clang_format(
        TARGET lys_sandbox
        FILES ${SANDBOX_MODULES}
)
enforce_copyright(
        TARGET lys_sandbox
        CONFIG_FILE "${CMAKE_CURRENT_SOURCE_DIR}/../config.toml"
        SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src"
)
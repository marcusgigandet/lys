file(GLOB_RECURSE EDITOR_SOURCES CONFIGURE_DEPENDS
        ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
)

add_executable(lys_editor
        ${EDITOR_SOURCES}
)

target_include_directories(lys_editor
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    target_compile_options(lys_editor PRIVATE -fmodules -freflection)
endif ()

target_link_libraries(lys_editor
        PRIVATE
        lys::engine
)

enforce_clang_format(
        TARGET lys_editor
        FILES ${EDITOR_SOURCES}
)
enforce_copyright(
        TARGET lys_editor
        CONFIG_FILE "${CMAKE_CURRENT_SOURCE_DIR}/../config.toml"
        SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src"
)
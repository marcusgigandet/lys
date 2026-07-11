file(GLOB_RECURSE ENGINE_MODULES CONFIGURE_DEPENDS
        ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cppm
)
file(GLOB_RECURSE ENGINE_SOURCES CONFIGURE_DEPENDS
        ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
)

add_library(lys_engine)
target_sources(lys_engine
        PUBLIC
        FILE_SET cxx_modules
        TYPE CXX_MODULES
        FILES ${ENGINE_MODULES}
        PRIVATE
        ${ENGINE_SOURCES}
)

target_include_directories(lys_engine
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
        ${CMAKE_CURRENT_SOURCE_DIR}/../vendor/glfw/include
)

if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    target_compile_options(lys_engine PRIVATE -freflection)
endif ()

target_link_libraries(lys_engine
        PRIVATE
        lum::lum
        PUBLIC
        mag::mag
        glfw
)

target_compile_features(mag PRIVATE cxx_std_26)

add_library(lys::engine ALIAS lys_engine)

enforce_clang_format(
        TARGET lys_engine
        FILES ${ENGINE_MODULES} ${ENGINE_SOURCES}
)
enforce_copyright(
        TARGET lys_engine
        CONFIG_FILE "${CMAKE_CURRENT_SOURCE_DIR}/../config.toml"
        SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src"
)

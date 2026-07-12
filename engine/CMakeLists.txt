file(GLOB_RECURSE ENGINE_MODULES CONFIGURE_DEPENDS
        ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cppm
        ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
)

add_library(lys_engine)
target_sources(lys_engine
        PUBLIC
        FILE_SET cxx_modules
        TYPE CXX_MODULES
        FILES ${ENGINE_MODULES}
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

link_vulkan(TARGET lys_engine)

target_compile_features(mag PRIVATE cxx_std_26)
target_compile_definitions(mag
        PRIVATE MAG_NAMESPACE=lys
)

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

cmake_minimum_required(VERSION 3.11)
project(rini
    DESCRIPTION "rini: A simple and easy-to-use ini-style files reader and writer"
    HOMEPAGE_URL "https://github.com/raylib5/rini"
    LANGUAGES C
)

# Config options
option(BUILD_RINI_EXAMPLES "Build the examples." OFF)

# Force building examples if building in the root as standalone.
if (CMAKE_SOURCE_DIR STREQUAL CMAKE_CURRENT_SOURCE_DIR)
    set(BUILD_RINI_EXAMPLES TRUE)
endif()

# Directory Variables
set(RINI_ROOT ${CMAKE_CURRENT_SOURCE_DIR}/../..)
set(RINI_SRC ${RINI_ROOT}/src)
set(RINI_EXAMPLES ${RINI_ROOT}/examples)

# rini
add_library(rini INTERFACE)
target_include_directories(rini INTERFACE ${RINI_SRC})

# Examples
if (BUILD_RINI_EXAMPLES)
    # Dependency: raylib
    find_package(raylib QUIET)
    if (NOT raylib_FOUND)
        include(FetchContent)
        FetchContent_Declare(
            raylib
            GIT_REPOSITORY https://github.com/raysan5/raylib.git
            GIT_TAG 6.0
        )
        FetchContent_GetProperties(raylib)
        if (NOT raylib_POPULATED) # Have we downloaded raylib yet?
            set(FETCHCONTENT_QUIET NO)
            FetchContent_Populate(raylib)
            set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
            set(BUILD_GAMES    OFF CACHE BOOL "" FORCE)
            add_subdirectory(${raylib_SOURCE_DIR} ${raylib_BINARY_DIR})
        endif()
    endif()

    # Create a list of all examples
    set(examples)
    file(GLOB sources ${RINI_EXAMPLES}/*.c)
    list(APPEND examples ${sources})

    # Build each example
    foreach(example_source ${examples})
        # Create the basename for the example
        get_filename_component(example_name ${example_source} NAME)
        string(REPLACE ".c" "${OUTPUT_EXT}" example_name ${example_name})

        # Setup the example
        add_executable(${example_name} ${example_source})
        target_link_libraries(${example_name} PUBLIC raylib rini)
    endforeach()

    # Resources
    file(COPY ${RINI_EXAMPLES}/resources DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
    #file(COPY ${RINI_EXAMPLES}/resources/rini_example.ini DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
    #file(COPY ${RINI_EXAMPLES}/resources.rres DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
    #file(COPY ${RINI_EXAMPLES}/resources.rrp DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
endif()
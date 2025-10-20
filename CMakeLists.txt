# ====================================================================
# Top-level CMakeLists.txt file for sysfont-c
# ====================================================================

cmake_minimum_required(VERSION 3.16)

include(cmake/utils.cmake)
sf_extract_version()

# --------------------------------------------------------------------
# Project configuration
# --------------------------------------------------------------------

project(sysfonts VERSION ${SF_VERSION})
set(PROJECT_FULLNAME "system-fonts")

message(STATUS "Building sysfonts ${SF_VERSION}")

if(NOT DEFINED SF_MASTER_PROJECT)
    if(CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
        set(SF_MASTER_PROJECT ON)
    else()
        set(SF_MASTER_PROJECT OFF)
    endif()
endif()

option(SF_STRICT_WARNINGS "Enable strict compiler warnings" ${SF_MASTER_PROJECT})

option(SF_BUILD_SHARED "Build shared library" OFF)

if(SF_MASTER_PROJECT)
    # FIXME:
    # If using Visual Studio as the generator, the output directories will have an
    # additional configuration subdirectory (e.g., Debug, Release, etc.).
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/output/lib")
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/output/lib")
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/output/bin")
endif()

# --------------------------------------------------------------------
# Targets
# --------------------------------------------------------------------

set(CMAKE_C_STANDARD 11)

set(target_name sysfonts)
set(binary_name sysfonts)

file(GLOB_RECURSE SF_SOURCES CONFIGURE_DEPENDS 
    "${PROJECT_SOURCE_DIR}/include/*.h"
    "${PROJECT_SOURCE_DIR}/src/*.h"
    "${PROJECT_SOURCE_DIR}/src/*.c"
)

if(SF_BUILD_SHARED)
    add_library(${target_name} SHARED ${SF_SOURCES})

    target_compile_definitions(${target_name} PRIVATE SF_EXPORT)
    target_compile_definitions(${target_name} INTERFACE SF_IMPORT)
    
    set_target_properties(${target_name} PROPERTIES OUTPUT_NAME ${binary_name})
    set_target_properties(${target_name} PROPERTIES POSITION_INDEPENDENT_CODE ON)
else()
    add_library(${target_name} STATIC ${SF_SOURCES})
endif()

target_include_directories(
    ${target_name}
    PUBLIC ${CMAKE_CURRENT_LIST_DIR}/include
    PRIVATE ${CMAKE_CURRENT_LIST_DIR}/src
)

if(SF_STRICT_WARNINGS)
    sf_enable_warnings(${target_name})
endif()

if(LINUX)
    target_link_libraries(${target_name} PRIVATE fontconfig)
endif()
if (APPLE)
    target_link_libraries(${target_name} PRIVATE "-framework CoreText" "-framework CoreFoundation")
endif()

add_library(sysfonts::sysfonts ALIAS ${target_name})

if(SF_BUILD_TEST)
    add_subdirectory(test)
endif()

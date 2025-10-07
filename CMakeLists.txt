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

if(NOT DEFINED SF_MASTER_PROJECT)
    if(CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
        set(SF_MASTER_PROJECT ON)
    else()
        set(SF_MASTER_PROJECT OFF)
    endif()
endif()

option(SF_BUILD_TEST "Build test" ${SF_MASTER_PROJECT})
option(SF_STRICT_WARNINGS "Enable strict compiler warnings" ${SF_MASTER_PROJECT})

option(SF_USE_SHARED "Use shared library of libsysfonts" OFF)
option(SF_BUILD_SHARED "Build static library" ${SF_USE_SHARED})
option(SF_BUILD_STATIC "Build static library" ON)

# --------------------------------------------------------------------
# Targets
# --------------------------------------------------------------------

set(CMAKE_C_STANDARD 11)

add_subdirectory(sysfonts)

if(SF_BUILD_TEST)
    add_subdirectory(test)
endif()

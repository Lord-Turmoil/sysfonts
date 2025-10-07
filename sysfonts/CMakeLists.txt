# ====================================================================
# libsysfonts
# ====================================================================

project(libsysfonts VERSION ${SF_VERSION} LANGUAGES C)

message(STATUS "Build libsysfont: ${SF_VERSION}")

# --------------------------------------------------------------------
# Project Configuration
# --------------------------------------------------------------------

set(target_shared libsysfonts-shared)
set(target_static libsysfonts-shared)
set(binary_name libsysfonts)

# --------------------------------------------------------------------
# Source Files
# --------------------------------------------------------------------

# Add .h to the sources so that Visual Studio can recognize them.
file(GLOB_RECURSE SF_SOURCES CONFIGURE_DEPENDS 
    "${PROJECT_SOURCE_DIR}/include/*.h"
    "${PROJECT_SOURCE_DIR}/src/*.h"
    "${PROJECT_SOURCE_DIR}/src/*.c"
)

# --------------------------------------------------------------------
# Targets
# --------------------------------------------------------------------

# Shared and static targets have some common configurations.
macro(configure_sf_target target_name)
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
endmacro()

if(SF_BUILD_SHARED)
    add_library(${target_shared} SHARED ${SF_SOURCES})
    configure_sf_target(${target_shared})

    target_compile_definitions(${target_shared} PRIVATE SF_EXPORT)
    target_compile_definitions(${target_shared} INTERFACE SF_IMPORT)
    
    set_target_properties(${target_shared} PROPERTIES OUTPUT_NAME ${binary_name})
    set_target_properties(${target_shared} PROPERTIES POSITION_INDEPENDENT_CODE ON)
endif()

if(SF_BUILD_STATIC)
    add_library(${target_static} STATIC ${SF_SOURCES})
    configure_sf_target(${target_static})
endif()

# --------------------------------------------------------------------
# Target Aliases
# --------------------------------------------------------------------

if(SF_USE_SHARED)
    add_library(sysfonts::sysfonts ALIAS ${target_shared})
else()
    add_library(sysfonts::sysfonts ALIAS ${target_static})
endif()

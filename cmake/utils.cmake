# Turn on warnings on the given target
function(sf_enable_warnings target_name)
    target_compile_options(
        ${target_name}
        PRIVATE $<$<OR:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:AppleClang>,$<CXX_COMPILER_ID:GNU>>:
                -Wall
                -Wextra
                -Wconversion
                -pedantic
                -Werror
                -Wfatal-errors>
                $<$<CXX_COMPILER_ID:MSVC>:/W4>)
endfunction()

# Turn off warnings on the given target 
function(sf_disable_warnings target_name)
    get_target_property(type ${target_name} TYPE)
    if (NOT ${type} STREQUAL "INTERFACE_LIBRARY")
        target_compile_options(${target_name} PRIVATE -w)
    else()
        message(VERBOSE "Cannot disable warnings for INTERFACE target: ${target_name}")
    endif()
endfunction()

# Extract version information from SF_defines.h
function(sf_extract_version)
    file(READ "${CMAKE_CURRENT_LIST_DIR}/include/sysfonts/SF_defines.h" file_contents)
    string(REGEX MATCH "SF_VERSION_MAJOR +([0-9]+)" _ "${file_contents}")
    if(NOT CMAKE_MATCH_COUNT EQUAL 1)
        message(FATAL_ERROR "Could not extract major version number")
    endif()
    set(ver_major ${CMAKE_MATCH_1})

    string(REGEX MATCH "SF_VERSION_MINOR +([0-9]+)" _ "${file_contents}")
    if(NOT CMAKE_MATCH_COUNT EQUAL 1)
        message(FATAL_ERROR "Could not extract minor version number")
    endif()

    set(ver_minor ${CMAKE_MATCH_1})
    string(REGEX MATCH "SF_VERSION_PATCH +([0-9]+)" _ "${file_contents}")
    if(NOT CMAKE_MATCH_COUNT EQUAL 1)
        message(FATAL_ERROR "Could not extract patch version number")
    endif()
    set(ver_patch ${CMAKE_MATCH_1})

    set(ver_revision ${CMAKE_MATCH_1})
    string(REGEX MATCH "SF_VERSION_REVISION +([0-9]+)" _ "${file_contents}")
    if(NOT CMAKE_MATCH_COUNT EQUAL 1)
        message(FATAL_ERROR "Could not extract revision version number")
    endif()
    set(ver_revision ${CMAKE_MATCH_1})

    set(SF_VERSION_MAJOR    ${ver_major}    PARENT_SCOPE)
    set(SF_VERSION_MINOR    ${ver_minor}    PARENT_SCOPE)
    set(SF_VERSION_PATCH    ${ver_patch}    PARENT_SCOPE)
    set(SF_VERSION_REVISION ${ver_revision} PARENT_SCOPE)

    set(SF_VERSION "${ver_major}.${ver_minor}.${ver_patch}.${ver_revision}" PARENT_SCOPE)
endfunction()

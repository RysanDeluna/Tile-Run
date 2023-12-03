cmake_minimum_required(VERSION 3.21)
# Compiler flags
if (MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MP /EHsc" CACHE INTERNAL "" FORCE)
elseif(APPLE)
    message("hello apple")
    set(CMAKE_OSX_DEPLOYMENT_TARGET 10.9 CACHE STRING "")
endif()
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(PRACTICAL_7_PLATFORMER)
include(FetchContent)


FetchContent_Declare(
        sfml
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 2.6.x
)
FetchContent_MakeAvailable(sfml)
# populate the  lib directory with the sfml libraries
FetchContent_GetProperties(sfml) # can I get cmake to list out the names of the properties? A: yes, use the following line: get_cmake_property(_variableNames VARIABLES)
if(NOT sfml_POPULATED)
    FetchContent_Populate(sfml)
    add_subdirectory(${sfml_SOURCE_DIR} ${sfml_BINARY_DIR})
endif()
get_cmake_property(_variableNames VARIABLES)
list(FILTER _variableNames INCLUDE REGEX "sfml")
message("variableNames: ${_variableNames}")

foreach (_variableName ${_variableNames})
    message(STATUS "${_variableName}=${${_variableName}}")
endforeach()

message ("SFML_SOURCE_DIR: ${sfml_SOURCE_DIR}")

message ("SFML_SOURCE_DIR: ${sfml_SOURCE_DIR}")

message("SFML_BINARY_DIR: ${sfml_BINARY_DIR}")


# The following downloads box2d into the build directory and builds it
FetchContent_Declare(box2d
        GIT_REPOSITORY     https://github.com/dooglz/Box2D.git
        GIT_TAG             v2.3.1)

# We need finer control over the build of box2d so we set the following variables
set(BOX2D_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
if(NOT box2d_POPULATED)
    FetchContent_Populate(box2d)
    add_subdirectory(${box2d_SOURCE_DIR}/Box2D ${box2d_BINARY_DIR})
endif()

get_cmake_property(_variableNamesbox VARIABLES)
list(FILTER _variableNamesbox INCLUDE REGEX "box")
message("_variableNamesbox: ${_variableNamesbox}")

foreach (_variableName ${_variableNamesbox})
    message(STATUS "${_variableName}=${${_variableName}}")
endforeach()

#### setup Directories ####
#Main output directory
set(OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/")
# Ouput all DLLs from all libs into main build folder
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_DIRECTORY})

add_custom_target(copy_resources ALL COMMAND ${CMAKE_COMMAND}
        -E copy_directory
        "${PROJECT_SOURCE_DIR}/res"
        ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/res
)

# _________________________________________________________________________________________________________
# -- The alternative was to use submodule (for both sfml and box2d - below) from github and use that to download and populate the directory - We went with the more "straightforward" approach of using fetchcontent
#### Add External Dependencies ####
# SFML - graphics library
#add_subdirectory("lib/sfml" EXCLUDE_FROM_ALL)
#include_directories("lib/sfml/include")
#set(SFML_INCS "lib/sfml/include")
#link_directories("${CMAKE_BINARY_DIR}/lib/sfml/lib") # Does fetchcontent do this for me? A: yes, but I need to tell it to do so by adding the following line: FetchContent_MakeAvailable(sfml)

# B2D - Box2D phyics library
#add_subdirectory("lib/b2d/Box2D" EXCLUDE_FROM_ALL)
#include_directories("lib/b2d/Box2D/")
#set(B2D_INCS "lib/b2d/Box2D/")
#link_directories("${CMAKE_BINARY_DIR}/lib/sfml/lib")
# _________________________________________________________________________________________________________

# The following allows us to tell the compiler where the header files are for box2D. This is normally managed by fetchcontent but we need to do it manually for box2d - one of the problems in the build
set (B2D_INCS "${box2d_SOURCE_DIR}/Box2D") # note that fetchcontent will download the box2d source code into the box2d_SOURCE_DIR

#### Add Engine and our own library projects####

set (SFML_INCS "${sfml_SOURCE_DIR}/include") # note that fetchcontent will download the sfml source code into the sfml_SOURCE_DIR

set (lib_box2d "${box2d_BINARY_DIR}/Box2D/libBox2D.a") # Again, not ideal, but we need to tell the compiler where the box2d library is. This is normally managed by fetchcontent but we need to do it manually for box2d - one of the problems in the build


file(GLOB_RECURSE RESOURCE_FILES "res/*.*")
####
file(GLOB_RECURSE SOURCE_FILES engine/*.cpp engine/*.h)
add_library(lib_engine STATIC ${SOURCE_FILES} ${RESOURCE_FILES})
target_include_directories(lib_engine INTERFACE "${CMAKE_SOURCE_DIR}/engine/" PUBLIC SYSTEM ${B2D_INCS} )
target_link_libraries(lib_engine lib_tile_level_loader lib_maths lib_ecm Box2D sfml-graphics sfml-audio)

## Maths lib
add_library(lib_maths INTERFACE)
target_sources(lib_maths INTERFACE "${CMAKE_SOURCE_DIR}/lib_maths/maths.h")
target_include_directories(lib_maths INTERFACE "${CMAKE_SOURCE_DIR}/lib_maths" INTERFACE ${SFML_INCS})

## Tile loader lib
file(GLOB_RECURSE SOURCE_FILES lib_tile_level_loader/*.cpp lib_tile_level_loader/*.h)
add_library(lib_tile_level_loader STATIC ${SOURCE_FILES} ${RESOURCE_FILES})
target_include_directories(lib_tile_level_loader INTERFACE "${CMAKE_SOURCE_DIR}/lib_tile_level_loader/" )
target_link_libraries(lib_tile_level_loader lib_maths sfml-graphics)

## ECM lib
file(GLOB_RECURSE SOURCE_FILES lib_ecm/*.cpp lib_ecm/*.h)
add_library(lib_ecm STATIC ${SOURCE_FILES})
target_include_directories(lib_ecm INTERFACE "${CMAKE_SOURCE_DIR}/lib_ecm" )
target_link_libraries(lib_ecm PRIVATE lib_maths)

#### Add Practical Projects####

#@@-

## 6 - Platformer
file(GLOB_RECURSE SOURCES lab_7_platformer/*.cpp practical_6_platformer/*.h)
file(GLOB_RECURSE CMPNTS lab_7_platformer/components/*.cpp practical_6_platformer/components/*.h)
file(GLOB_RECURSE SCENES lab_7_platformer/scenes/*.cpp practical_6_platformer/scenes/*.h)
add_executable(PRACTICAL_7_PLATFORMER ${SOURCES} ${RESOURCE_FILES})
source_group("components" FILES ${CMPNTS})
source_group("resources" FILES ${RESOURCE_FILES})


target_link_libraries(PRACTICAL_7_PLATFORMER lib_engine)
set(EXECUTABLES ${EXECUTABLES} PRACTICAL_7_PLATFORMER)


if (WIN32 AND BUILD_SHARED_LIBS)
    add_custom_command(TARGET PRACTICAL_7_PLATFORMER POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_RUNTIME_DLLS:PRACTICAL_7_PLATFORMER> $<TARGET_FILE_DIR:PRACTICAL_7_PLATFORMER> COMMAND_EXPAND_LISTS)
endif()

add_dependencies(PRACTICAL_7_PLATFORMER copy_resources)


set_target_properties(PRACTICAL_7_PLATFORMER
        PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY
        ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/$(Configuration)
)

file(GLOB_RECURSE SOURCES game_project/*.cpp game_project/*.h)
file(GLOB_RECURSE CMPNTS game_project/components/*.cpp game_project/components/*.h)
file(GLOB_RECURSE SCENES game_project/scenes/*.cpp game_project/scenes/*.h)
file(GLOB_RECURSE AI game_project/ai/*.cpp game_project/ai/*.h)
add_executable(GAME_PROJECT ${SOURCES} ${RESOURCE_FILES})
source_group("components" FILES ${CMPNTS})
source_group("resources" FILES ${RESOURCE_FILES})
source_group("ai" FILES ${AI})

target_link_libraries(GAME_PROJECT lib_engine)
set(EXECUTABLES ${EXECUTABLES} GAME_PROJECT)


if (WIN32 AND BUILD_SHARED_LIBS)
    add_custom_command(TARGET GAME_PROJECT POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_RUNTIME_DLLS:PRACTICAL_7_PLATFORMER> $<TARGET_FILE_DIR:GAME_PROJECT> COMMAND_EXPAND_LISTS)
endif()

add_dependencies(GAME_PROJECT copy_resources)


set_target_properties(GAME_PROJECT
        PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY
        ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/$(Configuration)
)
#@@-
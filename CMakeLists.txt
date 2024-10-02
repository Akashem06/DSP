cmake_minimum_required(VERSION 3.10)
project(DSPLibrary VERSION 1.0)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Enable shared library building
set(BUILD_SHARED_LIBS ON)

# Include directories
include_directories(${PROJECT_SOURCE_DIR}/inc)

# Glob function to recursively find all source files
function(glob_sources GLOBEXPRESSION GLOBVARIABLE)
    file(GLOB_RECURSE ${GLOBVARIABLE} CONFIGURE_DEPENDS ${GLOBEXPRESSION})
    set(${GLOBVARIABLE} ${${GLOBVARIABLE}} PARENT_SCOPE)
endfunction()

# Glob source files
glob_sources(${PROJECT_SOURCE_DIR}/src/core/*.cpp CORE_SOURCES)
glob_sources(${PROJECT_SOURCE_DIR}/src/advanced/*.cpp ADVANCED_SOURCES)
glob_sources(${PROJECT_SOURCE_DIR}/src/real_time/*.cpp REAL_TIME_SOURCES)

# Add core library
add_library(dsp_core ${CORE_SOURCES})

# Add advanced library
add_library(dsp_advanced ${ADVANCED_SOURCES})

# Add real-time library
add_library(dsp_real_time ${REAL_TIME_SOURCES})

# Link libraries
target_link_libraries(dsp_advanced dsp_core)
target_link_libraries(dsp_real_time dsp_core)

# Print found source files (optional, for debugging)
message(STATUS "Core sources: ${CORE_SOURCES}")
message(STATUS "Advanced sources: ${ADVANCED_SOURCES}")
message(STATUS "Real-time sources: ${REAL_TIME_SOURCES}")

# Install
install(TARGETS dsp_core dsp_advanced dsp_real_time
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
        RUNTIME DESTINATION bin)

install(DIRECTORY include/ DESTINATION include)

# Generate compile_commands.json for IDEs
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
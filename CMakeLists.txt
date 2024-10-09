cmake_minimum_required(VERSION 3.10)
project(DSPLibrary VERSION 1.0)

# Set C++ standards
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Enable shared library building
set(BUILD_SHARED_LIBS ON)

include_directories(${PROJECT_SOURCE_DIR}/inc)

# Function to glob source files
function(glob_sources GLOBEXPRESSION GLOBVARIABLE)
    file(GLOB_RECURSE ${GLOBVARIABLE} CONFIGURE_DEPENDS ${GLOBEXPRESSION})
    set(${GLOBVARIABLE} ${${GLOBVARIABLE}} PARENT_SCOPE)
endfunction()

# Glob the source files
glob_sources(${PROJECT_SOURCE_DIR}/src/core/*.cpp CORE_SOURCES)
glob_sources(${PROJECT_SOURCE_DIR}/src/advanced/*.cpp ADVANCED_SOURCES)
glob_sources(${PROJECT_SOURCE_DIR}/tests/*.cpp TEST_SOURCES)

# Add test executable
add_executable(dsp_tests ${TEST_SOURCES})

# Add core library
add_library(dsp_core ${CORE_SOURCES})

# Add advanced library
add_library(dsp_advanced ${ADVANCED_SOURCES})

# Print source files for debugging (optional)
message(STATUS "Core sources: ${CORE_SOURCES}")
message(STATUS "Advanced sources: ${ADVANCED_SOURCES}")
message(STATUS "Test sources: ${TEST_SOURCES}")

# Install the libraries
install(TARGETS dsp_core dsp_advanced
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
        RUNTIME DESTINATION bin)

# Install headers
install(DIRECTORY include/ DESTINATION include)

# Generate compile_commands.json for IDE integration
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# GoogleTest integration
include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG release-1.12.1
)

# Ensure shared CRT (for Visual Studio compatibility)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)
enable_testing()

# Link the test executable to GoogleTest and the DSP libraries
target_link_libraries(
  dsp_tests
  gtest_main
  dsp_advanced
  dsp_core
)

# Automatically discover and register tests
include(GoogleTest)
gtest_discover_tests(dsp_tests)

cmake_minimum_required(VERSION 3.30)

set(EXEC_NAME JavaRun)


# Set the project name and version
project(JavaRun VERSION 1.0)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include(FetchContent)

# Declare the FLTK library
FetchContent_Declare(
    fltk
    GIT_REPOSITORY https://github.com/fltk/fltk.git
    GIT_TAG        master  # You can specify a specific tag or branch if needed
)

# Make the FLTK library available
FetchContent_MakeAvailable(fltk)


# Add the executable


add_executable(${EXEC_NAME} src/main.cpp src/Popup.cpp src/Confirm.cpp)

target_link_libraries(${EXEC_NAME} PRIVATE fltk::fltk)

# Platform-specific settings
if(WIN32)
    message(STATUS "Configuring for Windows")
    # Windows-specific settings
    target_compile_definitions(${EXEC_NAME} PRIVATE PLATFORM_WINDOWS)
    target_link_libraries(${EXEC_NAME} PRIVATE User32)  # Link against User32.lib
elseif(UNIX)
    message(STATUS "Configuring for Linux")
    # Linux-specific settings
    target_compile_definitions(${EXEC_NAME} PRIVATE PLATFORM_LINUX)
endif()

# Optionally, you can add more configurations
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    message(STATUS "Debug build")
    # Debug-specific settings
elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
    message(STATUS "Release build")
    # Release-specific settings
endif()

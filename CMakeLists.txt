cmake_minimum_required(VERSION 3.28)
project(game)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Manually set the include and library paths
set(raylib_DIR "C:/Users/Ananya/vcpkg/packages/raylib_x64-windows/share/raylib")
set(raylib_INCLUDE_DIR "C:/Users/Ananya/vcpkg/packages/raylib_x64-windows/include")
set(raylib_LIBRARY "C:/Users/Ananya/vcpkg/packages/raylib_x64-windows/lib/raylib.lib")

# Find and link raylib
find_package(raylib CONFIG REQUIRED)

# Add the executable
add_executable(game main.cpp)

# Include the raylib directory
target_include_directories(game PRIVATE ${raylib_INCLUDE_DIR})

# Link Raylib
target_link_libraries(game PRIVATE ${raylib_LIBRARY} stdc++fs)
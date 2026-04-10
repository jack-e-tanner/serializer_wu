cmake_minimum_required(VERSION 3.14)
project(SerializationEngine)

# Enforce C++17 (Required for modern type traits like is_trivially_copyable_v)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 1. Fetch GoogleTest directly from the source
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows compatibility (just in case you boot into your Windows partition)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# 2. Tell CMake to build your test executable
# Note: We only compile the .cpp file. The headers are included automatically.
add_executable(test_serializer tests/test_serializer.cpp)

# 3. Link Google Test to your executable
# We link GTest::gtest_main so you don't have to write your own int main() function.
target_link_libraries(test_serializer GTest::gtest_main)
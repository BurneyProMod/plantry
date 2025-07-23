cmake_minimum_required(VERSION 3.10)
project(plantry)

set(CMAKE_CXX_STANDARD 17)

# Download Crow & nlohmann/json via FetchContent
include(FetchContent)
FetchContent_Declare(
  crow
  GIT_REPOSITORY https://github.com/CrowCpp/Crow.git
  GIT_TAG        v1.0+   # or latest
)
FetchContent_Declare(
  json
  GIT_REPOSITORY https://github.com/nlohmann/json.git
  GIT_TAG v3.11.2
)
FetchContent_MakeAvailable(crow json)

add_executable(plantry
    src/main.cpp
)
target_include_directories(plantry PRIVATE ${crow_SOURCE_DIR}/include)
target_link_libraries(plantry PRIVATE nlohmann_json::nlohmann_json)

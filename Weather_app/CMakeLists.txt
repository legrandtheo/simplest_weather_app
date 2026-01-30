cmake_minimum_required(VERSION 4.0)
project(Weather_app)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(CURL REQUIRED)
find_package(nlohmann_json REQUIRED)

find_package(imgui REQUIRED)
find_package(glfw3 REQUIRED)
find_package(OpenGL REQUIRED)

add_executable(Weather_app
        main.cpp
        classes/api_json_decomposer.cpp
        classes/api_json_decomposer.h
        classes/weather_utilities.cpp
        classes/weather_utilities.h
        classes/ImGui_utilities.cpp
        classes/ImGui_utilities.h)

target_link_libraries(Weather_app PRIVATE CURL::libcurl nlohmann_json::nlohmann_json imgui::imgui glfw OpenGL::GL)

set_target_properties(Weather_app PROPERTIES WIN32_EXECUTABLE TRUE)

target_link_options(Weather_app PRIVATE "/SUBSYSTEM:WINDOWS" "/ENTRY:mainCRTStartup")
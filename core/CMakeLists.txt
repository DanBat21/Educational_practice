cmake_minimum_required(VERSION 3.16)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Quick)

qt_standard_project_setup(REQUIRES 6.8)

qt_add_library(core
    decodertext.h
    decodertext.cpp
    encodertext.h
    encodertext.cpp
)

target_link_libraries(core PRIVATE Qt6::Core Qt6::Gui)

target_include_directories(core PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

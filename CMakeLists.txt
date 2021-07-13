cmake_minimum_required(VERSION 3.15)
project(steuerung_gersbach)

set(CMAKE_CXX_STANDARD 17)
find_package(wxWidgets REQUIRED COMPONENTS net core base)
include(${wxWidgets_USE_FILE})
add_executable(steuerung_gersbach main.cpp settings.cpp settings.h mainwindow.h mainwindow.cpp)

target_link_libraries(steuerung_gersbach ${wxWidgets_LIBRARIES})
include_directories(include)
#Windows Compiling
if (${CMAKE_SYSTEM_NAME} MATCHES "Windows")
    set(BUILD_FOR_WIN TRUE)
endif ()
option(STATIC_BUILD "Build a static binary" ${BUILD_FOR_WIN})

if (STATIC_BUILD)
    set(CMAKE_EXE_LINKER_FLAGS "-static")
    set(CMAKE_FIND_LIBRARY_SUFFIXES ".a" CONFIG)
    set(BUILD_SHARED_LIBS OFF)
endif ()
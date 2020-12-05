cmake_minimum_required(VERSION 3.16)
project(co)

if(WIN32)
    if (NOT MSVC)
        message(FATAL_ERROR, "msvc required on windows")
    endif()
    enable_language(C CXX ASM_MASM)
else()
    enable_language(C CXX ASM)
endif()

# Configure for C++20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

option(BUILD_SHARED_LIBS  "Let us build static libs" OFF)
option(ENABLE_UNITTESTS   "Set to enable/disable building unit tests"  ON)
option(ENABLE_SYSTEM_TEST "Set to enable/disable building unit tests " ON)

set(CMAKE_DEBUG_POSTFIX "d")

include_directories(include)

if(UNIX)
    add_compile_options(-Wall -O2 -g3)
    if(APPLE)
        add_compile_options(-fno-pie)
    endif()
endif()

if(MSVC)
    add_compile_options(/W4 /fp:fast /EHsc)
    add_link_options(/SAFESEH:NO)
endif()

add_subdirectory(src)

if(ENABLE_UNITTESTS)
    add_subdirectory(unitest)
endif()

if (ENABLE_SYSTEM_TEST)
    add_subdirectory(test)
endif()

install(
    DIRECTORY include/co
    DESTINATION include)

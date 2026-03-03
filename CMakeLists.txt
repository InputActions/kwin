cmake_minimum_required(VERSION 3.16.0)

project(kwin_gestures)
set(PROJECT_VERSION "0.9.0.0")

set(QT_MIN_VERSION "6.6.0")
set(QT_MAJOR_VERSION 6)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Release" CACHE STRING "Choose Release or Debug" FORCE)
endif()
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O2 -DQT_NO_DEBUG_OUTPUT")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Bsymbolic-functions -Wall -Wextra -Wpedantic -Wno-unused-parameter -Wno-missing-field-initializers -Wno-switch")

find_package(ECM REQUIRED NO_MODULE)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${ECM_MODULE_PATH} ${ECM_KDE_MODULE_DIR})

include(KDEInstallDirs)
include(KDECMakeSettings)

configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/CPack.cmake.in
    ${CMAKE_CURRENT_BINARY_DIR}/CPack.cmake
    @ONLY
)
include(CPack)

if(NOT INPUTACTIONS_OVERRIDE_CORE)
    add_subdirectory(lib/core)
endif()
add_subdirectory(src)

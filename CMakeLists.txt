project (ULL)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules")

set (CMAKE_CXX_FLAGS "-std=c++14 -Werror -Wall -pthread")

set(SRC_FILES src/main.cpp src/Module.hpp src/Module.cpp)
set(KeyLoggerListener_src src/modules/KeystrokeLogger.cpp)

set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(X11 REQUIRED)
find_package(Xi REQUIRED)
find_package(LTDL REQUIRED)
find_package(Qt5Widgets)

add_executable(ull ${SRC_FILES})
add_library(keyloggerlistener SHARED ${KeyLoggerListener_src})

include_directories(${X11_INCLUDE_DIR})
include_directories(${XI_INCLUDE_DIRS})
include_directories(${LTDL_INCLUDE_DIRS})
include_directories(${Qt5Widgets_INCLUDE_DIRS})

target_link_libraries(keyloggerlistener ${XI_LIBRARIES})
target_link_libraries(keyloggerlistener ${X11_LIBRARIES})
target_link_libraries(ull ${LTDL_LIBRARIES})
target_link_libraries(keyloggerlistener Qt5::Widgets)
target_link_libraries(ull Qt5::Widgets)

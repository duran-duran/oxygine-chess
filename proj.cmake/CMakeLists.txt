cmake_minimum_required (VERSION 2.6)
project (oxygine-chess)

add_subdirectory(C:/oxygine/oxygine-framework/ oxygine-framework)
add_definitions(${OXYGINE_DEFINITIONS})
include_directories(${OXYGINE_INCLUDE_DIRS})
link_directories(${OXYGINE_LIBRARY_DIRS})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
add_executable(oxygine-chess ../src/example.cpp ../src/main.cpp  ../src/example.h )

if (WIN32) #disable console mode for VC++
	set_target_properties(oxygine-chess PROPERTIES WIN32_EXECUTABLE TRUE)
endif(WIN32)

target_link_libraries(oxygine-chess ${OXYGINE_CORE_LIBS})
cmake_minimum_required(VERSION 3.2)
project(adx-for-apis-simple)

option(BUILD_SHARED_LIBS "Build shared libraries" ON)

find_package(AWSSDK REQUIRED COMPONENTS dataexchange)
add_executable(adx-for-apis-simple main.cpp)

target_compile_features(adx-for-apis-simple PUBLIC cxx_std_11)
target_link_libraries(adx-for-apis-simple ${AWSSDK_LINK_LIBRARIES})

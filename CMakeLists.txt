cmake_minimum_required(VERSION 3.20)

project(cassLinear
    VERSION 1.0.0
    LANGUAGES CXX
)

add_library(cass_linear INTERFACE)

add_library(cass::linear ALIAS cass_linear)

target_include_directories(cass_linear
    INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
        $<INSTALL_INTERFACE:include>
)

target_compile_features(cass_linear
    INTERFACE
        cxx_std_23
)

option(BUILD_TESTS "Build tests" OFF)

if(BUILD_TESTS)
    enable_testing()
    
    if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/dependencies/catch2/CMakeLists.txt")
        add_subdirectory(dependencies/catch2)
    else()
        find_package(Catch2 3 REQUIRED)
    endif()

    set(TEST_FILES
        test/vector2.cpp
        test/vector3.cpp
        test/vector4.cpp
        test/matrix2.cpp
        test/matrix3.cpp
        test/matrix4.cpp
    )

    foreach(TEST_SRC ${TEST_FILES})
        get_filename_component(TEST_NAME ${TEST_SRC} NAME_WE)
        add_executable(${TEST_NAME} ${TEST_SRC})
        target_link_libraries(${TEST_NAME} PRIVATE cass_linear Catch2::Catch2WithMain)
        add_test(NAME ${TEST_NAME} COMMAND ${TEST_NAME})
    endforeach()
endif()
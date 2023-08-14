cmake_minimum_required(VERSION 3.26)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB MODULE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/cmake/*/" LIST_DIRECTORIES true) # "${PROJECT_SOURCE_DIR}/cmake"
list(APPEND CMAKE_MODULE_PATH "${MODULE_DIRS}")

include(git_version_detect)

project(hw4_sfinae
    VERSION ${GITVERSIONDETECT_VERSION_MAJOR}.${GITVERSIONDETECT_VERSION_MINOR}.${GITVERSIONDETECT_VERSION_PATCH}
    DESCRIPTION "course c++ developer - hw4" 
    LANGUAGES CXX
)

configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in 
    ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile
    @ONLY
)

add_executable(${PROJECT_NAME} src/main.cpp)
set_target_properties(${PROJECT_NAME} 
    PROPERTIES
        CXX_STANDARD ${CMAKE_CXX_STANDARD}
        CXX_STANDARD_REQUIRED ${CMAKE_CXX_STANDARD_REQUIRED}
)
# target_compile_features(
#     ${PROJECT_NAME}
#     PRIVATE
#         cxx_std_23
# )
target_compile_options(${PROJECT_NAME} 
    PRIVATE
	    -Wall -Wextra -pedantic -Werror
)
target_include_directories(
    ${PROJECT_NAME}
    PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}/src"
)
if(PRINT_PRETTY_FUNCTION)
    target_compile_definitions(${PROJECT_NAME}
        PRIVATE
            PRINT_PRETTY_FUNCTION
    )
endif()

if(BUILD_TESTING)
    find_package(GTest 1.13 REQUIRED)
    include(CTest)
    enable_testing()
    add_executable(
        hw4_gtest
        "src/sfinae/sfinae_gtest.cpp"
        "src/concepts/concepts_gtest.cpp"
    )
    set_target_properties(
        hw4_gtest
        PROPERTIES
            CXX_STANDARD ${CMAKE_CXX_STANDARD}
            CXX_STANDARD_REQUIRED ${CMAKE_CXX_STANDARD_REQUIRED}
    )
    target_include_directories(
        hw4_gtest
        PRIVATE
            ${GTEST_INCLUDE_DIRS}
            # "${CMAKE_CURRENT_SOURCE_DIR}/src/sfinae"
            # "${CMAKE_CURRENT_SOURCE_DIR}/src/concepts"
            "${CMAKE_CURRENT_SOURCE_DIR}/src"
    )
    target_link_libraries(
        hw4_gtest
        PRIVATE
            ${GTEST_BOTH_LIBRARIES}
    )
    add_test(hw4_gtest hw4_gtest)
    if (MSVC)
        target_compile_options(
            hw4_gtest
            PRIVATE  
                /W4
        )
    else()
        target_compile_options(
            hw4_gtest
            PRIVATE
                -Wall -Wextra -pedantic -Werror
        )
    endif(MSVC)  
endif(BUILD_TESTING)

install(TARGETS ${PROJECT_NAME})

if (RELEASE_VERSION)
    set(CPACK_GENERATOR "${PACKAGE}")
    set(CPACK_PACKAGE_VERSION "${RELEASE_VERSION}")
    set(CPACK_PACKAGE_CONTACT "${GIT_DESCRIBE_PROJECT_REPOSITORY_URL}")
    include(CPack)
endif()
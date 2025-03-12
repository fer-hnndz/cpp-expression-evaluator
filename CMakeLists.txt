cmake_minimum_required(VERSION 3.10)
project(CppExpressionEvaluator)

# Define C++ Standard 23 (Requirement for this class' project)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_BUILD_TYPE Debug)

set(SOURCES 
src/configparser.cpp 
src/evaluator.cpp 
src/operators.cpp
)

include_directories(include)
add_executable(operate ${SOURCES} src/main.cpp)

# Setup Catch2 for testing
find_package(Catch2 REQUIRED)
add_executable(tests ${SOURCES} tests/tests.cpp)
target_link_libraries(tests PRIVATE Catch2::Catch2WithMain)

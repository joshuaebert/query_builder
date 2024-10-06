set(target_name ${project_name}_test)
set(sources test.cpp)

enable_testing()

find_package(PostgreSQL REQUIRED)

include_directories(${PostgreSQL_INCLUDE_DIRS})

add_executable(${target_name} ${sources})

target_link_libraries(${target_name} PRIVATE pqxx gtest_main ${project_name}_lib ${PostgreSQL_Libraries})

include(GoogleTest)
gtest_discover_tests(${target_name})
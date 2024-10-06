set(target_name ${project_name}-app)
set(sources main.cpp)

find_package(PostgreSQL REQUIRED)

include_directories(${PostgreSQL_INCLUDE_DIRS})

add_executable(${target_name} ${sources})

target_link_libraries(${target_name} PRIVATE pqxx ${PostgreSQL_Libraries} ${project_name}_lib)
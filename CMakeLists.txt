project (sqliter)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_library(table table.cpp)
add_library(statement statement.cpp)
add_executable(db db.cpp)
target_link_libraries(db table statement)

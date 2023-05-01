project (sqliter)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(db db.cpp table.cpp statement.cpp btree.cpp pager.cpp os.cpp)

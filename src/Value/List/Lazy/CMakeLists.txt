target_sources(${CMAKE_PROJECT_NAME} PRIVATE
    LazyList.h    
    LazyList.cpp
)

add_subdirectory(Finite)
add_subdirectory(Infinite)
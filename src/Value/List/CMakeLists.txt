target_sources(${CMAKE_PROJECT_NAME} PRIVATE
    List.h    
    List.cpp
)

add_subdirectory(Concrete)
add_subdirectory(Lazy)
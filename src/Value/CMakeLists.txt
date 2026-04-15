target_sources(${CMAKE_PROJECT_NAME} PRIVATE
    Value.h
    ValueType.h
)

add_subdirectory(Number)
add_subdirectory(String)
add_subdirectory(List)
add_subdirectory(FunctionObject)
target_sources(${CMAKE_PROJECT_NAME} PRIVATE
    Expression.h
)

add_subdirectory(Value)
add_subdirectory(Variable)
add_subdirectory(Literal)
add_subdirectory(FunctionCall)
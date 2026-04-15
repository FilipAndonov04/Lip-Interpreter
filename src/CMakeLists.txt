target_sources(${CMAKE_PROJECT_NAME} PRIVATE
    Main.cpp
)

add_subdirectory(Value)
add_subdirectory(Expression)
add_subdirectory(Function)
add_subdirectory(Interpreter)
add_subdirectory(Utils)
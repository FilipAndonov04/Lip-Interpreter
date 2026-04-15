target_sources(${CMAKE_PROJECT_NAME} PRIVATE
    Interpreter.h
    Interpreter.cpp
    Init.h
    Init.cpp
)

add_subdirectory(Environment)
add_subdirectory(InputParsing)
add_subdirectory(EmbeddedFunctions)
add_subdirectory(Keywords)
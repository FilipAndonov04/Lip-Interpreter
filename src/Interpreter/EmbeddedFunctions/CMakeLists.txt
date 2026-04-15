target_sources(${CMAKE_PROJECT_NAME} PRIVATE
    EmbeddedUtils.h
    EmbeddedUtils.cpp
)

add_subdirectory(Comparison)
add_subdirectory(ControlFlow)
add_subdirectory(Conversion)
add_subdirectory(Function)
add_subdirectory(InputOutput)
add_subdirectory(List)
add_subdirectory(Logical)
add_subdirectory(Math)
add_subdirectory(String)
add_subdirectory(StringAndList)
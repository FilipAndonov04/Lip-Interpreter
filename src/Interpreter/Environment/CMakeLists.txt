target_sources(${CMAKE_PROJECT_NAME} PRIVATE
    Environment.h
    Environment.cpp
    EnvironmentStack.h
    EnvironmentStack.cpp
)

add_subdirectory(Data)
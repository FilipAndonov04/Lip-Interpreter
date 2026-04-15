cmake_minimum_required(VERSION 3.13)

project(lip)

add_executable(${CMAKE_PROJECT_NAME})

add_subdirectory(src)
target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE src)

# create resources symlink in build directory
add_custom_command(TARGET ${CMAKE_PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E create_symlink
    ${CMAKE_SOURCE_DIR}/scripts
    $<TARGET_FILE_DIR:${CMAKE_PROJECT_NAME}>/scripts
)
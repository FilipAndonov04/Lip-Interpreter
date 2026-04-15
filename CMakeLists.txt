cmake_minimum_required(VERSION 3.13)

project(lip)

add_executable(${CMAKE_PROJECT_NAME})

add_subdirectory(src)
target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE src)

# create resources symlink in build directory
set(SCRIPTS_DIR "scripts/")
add_custom_command(TARGET ${CMAKE_PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E create_symlink
    ${CMAKE_SOURCE_DIR}/${SCRIPTS_DIR}
    $<TARGET_FILE_DIR:${CMAKE_PROJECT_NAME}>/${SCRIPTS_DIR}
)

target_compile_definitions(${CMAKE_PROJECT_NAME} PRIVATE
    SCRIPTS_PATH=\"./${SCRIPTS_DIR}\"
)
cmake_minimum_required(VERSION 3.10)

add_subdirectory(vendor/imgui)
add_subdirectory(vendor/SDL)

project(crm LANGUAGES CXX)

set(TARGET_ARCHITECTURE "x64")
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_EXPORT_COMPILE_COMMANDS 1)

file(GLOB_RECURSE SRC_FILES src/*.cpp)

link_libraries(imgui SDL2-static)

add_compile_options(
  -g
  -O0
  -Wall
  -Wextra
  -Wno-gnu-zero-variadic-macro-arguments
  -Wno-unused-parameter
  -Wno-unused-variable
  -Wno-unused-but-set-variable
  -Wno-macro-redefined
  -Wno-attributes
  -Wno-incompatible-library-redeclaration
)

include_directories(
  src
  /usr/include/postgresql
  ${CMAKE_SOURCE_DIR}/vendor/imgui
  ${CMAKE_SOURCE_DIR}/vendor/SDL/include
)

add_executable(${PROJECT_NAME} ${SRC_FILES})

add_custom_target(run_${PROJECT_NAME}
  COMMENT "Running ${PROJECT_NAME}"
  DEPENDS ${PROJECT_NAME}
  COMMAND $<TARGET_FILE:${PROJECT_NAME}>
)

# Asset files

set(ASSETS_SRC "${CMAKE_SOURCE_DIR}/assets")
set(ASSETS_DST "$<TARGET_FILE_DIR:${PROJECT_NAME}>/assets")

set(ASSETS_CMD create_symlink)
set(ASSETS_MSG "Link assets")

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E echo "${ASSETS_MSG}: ${ASSETS_SRC} to ${ASSETS_DST}"
  COMMAND ${CMAKE_COMMAND} -E ${ASSETS_CMD} "${ASSETS_SRC}" "${ASSETS_DST}"
)

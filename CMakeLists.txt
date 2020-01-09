cmake_minimum_required(VERSION 3.14)
project(crab C)

set(CMAKE_C_STANDARD 99)

include_directories(./include)
include_directories(./parser)
include_directories(./vm)
include_directories(./cli)

aux_source_directory(./cli DIR_CLI)
aux_source_directory(./include DIR_INCLUDE)
aux_source_directory(./parser DIR_PARSER)
aux_source_directory(./vm DIR_VM)

add_executable(crab ${DIR_INCLUDE} ${DIR_PARSER} ${DIR_VM} ${DIR_CLI})

# add_subdirectory(include)
# add_subdirectory(parser)
# add_subdirectory(vm)

# target_link_libraries(crab includeModule)
# target_link_libraries(crab parserModule)
# target_link_libraries(crab vmModule)
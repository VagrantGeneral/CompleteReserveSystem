cmake_minimum_required(VERSION 3.23)

project(MySystem)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin) #output path

include_directories(./include/log) #include path
include_directories(./include/net)
include_directories(./include/db)


aux_source_directory(./src SRC_TEST)
aux_source_directory(./src/log SRC_LOG)
aux_source_directory(./src/db SRC_DB)

add_executable(msys ${SRC_TEST} ${SRC_LOG} ${SRC_DB})

target_link_libraries(msys mysqlclient.so)

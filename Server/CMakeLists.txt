cmake_minimum_required(VERSION 3.0)
project(SerTest)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

include_directories(${PROJECT_SOURCE_DIR}/include)
aux_source_directory(./src SRC_FILE)


add_executable(server ${SRC_FILE} ${GPBSRC_FILE} ${GLSRC_FILE} )

target_link_libraries(server libjsoncpp.so)
target_link_libraries(server libpthread.so)
target_link_libraries(server -levent)

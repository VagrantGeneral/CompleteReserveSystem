cmake_minimum_required(VERSION 3.0)
project(cliTest)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

include_directories(${PROJECT_SOURCE_DIR}/include)
aux_source_directory(./src SRC_FILE)


add_executable(client ${SRC_FILE} ${GPBSRC_FILE} ${GLSRC_FILE} )

target_link_libraries(client libjsoncpp.so)
target_link_libraries(client libpthread.so) 
#target_link_libraries(client libhiredis.so) 
#target_link_libraries(client libmysqlclient.so) ${GDBSRC_FILE}

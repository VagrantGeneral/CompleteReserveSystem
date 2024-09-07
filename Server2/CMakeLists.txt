cmake_minimum_required(VERSION 3.0)
project(SerTest2)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

include_directories(${PROJECT_SOURCE_DIR}/include)
aux_source_directory(./src SRC_FILE)


add_executable(server2 ${SRC_FILE} ${GPBSRC_FILE} ${GLSRC_FILE} )

target_link_libraries(server2 libjsoncpp.so)
target_link_libraries(server2 libpthread.so)
target_link_libraries(server2 -levent)
#target_link_libraries(server2 libhiredis.so) ${GDBSRC_FILE}
#target_link_libraries(server2 libmysqlclient.so)
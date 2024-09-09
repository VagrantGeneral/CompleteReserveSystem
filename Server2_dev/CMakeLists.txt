cmake_minimum_required(VERSION 3.0)
project(SerTest2_dev)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

include_directories(${PROJECT_SOURCE_DIR}/include)
aux_source_directory(./src SRC_FILE)


add_executable(server2_dev ${SRC_FILE} ${GPBSRC_FILE} ${GLSRC_FILE} )

target_link_libraries(server2_dev libjsoncpp.so)
target_link_libraries(server2_dev libpthread.so)
target_link_libraries(server2_dev -levent)
#target_link_libraries(server2 libhiredis.so) ${GDBSRC_FILE}
#target_link_libraries(server2 libmysqlclient.so)
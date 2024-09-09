cmake_minimum_required(VERSION 3.0)
project(SerTest_Vir)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

include_directories(${PROJECT_SOURCE_DIR}/include)
aux_source_directory(./src SRC_FILE)


add_executable(virtualserver ${SRC_FILE} ${GPBSRC_FILE} ${GLSRC_FILE} )

target_link_libraries(virtualserver libjsoncpp.so)
target_link_libraries(virtualserver libpthread.so)
target_link_libraries(virtualserver -levent)
#target_link_libraries(virtualserver libhiredis.so) ${GDBSRC_FILE}
#target_link_libraries(virtualserver libmysqlclient.so)

# cmake_minimum_required(VERSION 3.23)

# project(MySystem)

# set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin) #output path

# include_directories(./include/log) #include path
# include_directories(./include/net)
# include_directories(./include/db)
# include_directories(./include)


# aux_source_directory(./src SRC_TEST)
# aux_source_directory(./src/log SRC_LOG)
# aux_source_directory(./src/db SRC_DB)

# add_executable(msys ${SRC_TEST} ${SRC_LOG} ${SRC_DB})

# target_link_libraries(msys mysqlclient.so)
# target_link_libraries(msys libhiredis.so)
# target_link_libraries(msys libjsoncpp.so)

cmake_minimum_required(VERSION 3.23)
project(MySystem)

# log
include_directories(${PROJECT_SOURCE_DIR}/LogSys/include)
include_directories(${PROJECT_SOURCE_DIR}/LogSys/include/log)
aux_source_directory(${PROJECT_SOURCE_DIR}/LogSys/src/log/ GLSRC_FILE)

# db
include_directories(${PROJECT_SOURCE_DIR}/DBSys/include)
include_directories(${PROJECT_SOURCE_DIR}/DBSys/include/db)
aux_source_directory(${PROJECT_SOURCE_DIR}/DBSys/src/db/ GDBSRC_FILE)


# tool/ProgressBar
include_directories(${PROJECT_SOURCE_DIR}/Tool/ProgressBar)
include_directories(${PROJECT_SOURCE_DIR}/Tool/ProgressBar/include)
include_directories(${PROJECT_SOURCE_DIR}/Tool/ProgressBar/include/details)
include_directories(${PROJECT_SOURCE_DIR}/Tool/AllTool)
aux_source_directory(${PROJECT_SOURCE_DIR}/Tool/ProgressBar/include GPBSRC_FILE)
aux_source_directory(${PROJECT_SOURCE_DIR}/Tool/AllTool GPBSRC_FILE)

# another


add_subdirectory(Client)
add_subdirectory(Server)
add_subdirectory(Server2)
#add_subdirectory(Server2_dev)
add_subdirectory(VirtualServer)


# add_executable(msys ${GPBSRC_FILE} m_text.cpp)
# target_link_libraries(msys libpthread.so)
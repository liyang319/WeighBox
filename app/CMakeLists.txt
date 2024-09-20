# include sub directories
include_directories(${PROJECT_SOURCE_DIR}/include/base)
include_directories(${PROJECT_SOURCE_DIR}/include/config)
include_directories(${PROJECT_SOURCE_DIR}/include/log)
include_directories(${PROJECT_SOURCE_DIR}/include/network)
include_directories(${PROJECT_SOURCE_DIR}/include/utility)
include_directories(${PROJECT_SOURCE_DIR}/include/thirdparty)
include_directories(${PROJECT_SOURCE_DIR}/include/thirdparty/rapidjson)
include_directories(${PROJECT_SOURCE_DIR}/include/thirdparty/mosquitto)

# add compile tree
add_subdirectory(config)
add_subdirectory(log)
add_subdirectory(network)
add_subdirectory(utility)

# all source files
file(GLOB_RECURSE ALL_SOURCE "*.cpp" "*.c")

# find_library(CURL
#   NAMES curl
#   PATHS ${PROJECT_SOURCE_DIR}/lib
# )
# set(ARM OFF) 

if(${ARM})
  link_directories(${PROJECT_SOURCE_DIR}/lib/arm/openssl)
  link_directories(${PROJECT_SOURCE_DIR}/lib/arm/mosquitto)
elseif(${LINUXBUILD})
  link_directories(${PROJECT_SOURCE_DIR}/lib/linux/openssl)
  link_directories(${PROJECT_SOURCE_DIR}/lib/linux/mosquitto)
elseif(${MACBUILD})
  link_directories(${PROJECT_SOURCE_DIR}/lib/macos/openssl)
endif()


# create the executable
set(EXECUTABLE_NAME WeighBox)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/build/output)

# execute file 
add_executable(${EXECUTABLE_NAME} ${ALL_SOURCE})

target_link_libraries(${EXECUTABLE_NAME} mosquitto)
target_link_libraries(${EXECUTABLE_NAME} ssl)
target_link_libraries(${EXECUTABLE_NAME} crypto)
#target_link_libraries(${EXECUTABLE_NAME} mosquitto_static)
target_link_libraries(${EXECUTABLE_NAME} pthread)

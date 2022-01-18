cmake_minimum_required(VERSION 2.8)
project(TempConductivityTest)
# Locate libraries and headers
find_library(wiringPi_LIB wiringPi)
find_package(Threads REQUIRED)

# Include headers
include_directories(${WIRINGPI_INCLUDE_DIRS}) 
include_directories("../RemoteControlTest")

#the file(GLOB...) allows for wildcard additions:
file(GLOB SOURCES "./*.cpp")
add_executable(TempConductivityTest ${SOURCES} "../RemoteControlTest/AMLTempConductivity.cpp" "../RemoteControlTest/Sensor.cpp")

# Link against libraries
target_link_libraries(TempConductivityTest ${wiringPi_LIB} )
target_link_libraries(TempConductivityTest ${CMAKE_THREAD_LIBS_INIT})




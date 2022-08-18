cmake_minimum_required(VERSION 3.23)
project(wpl_mqtt)

set(CMAKE_CXX_STANDARD 20)

find_package(Threads REQUIRED)

# executable --> wpl_mqtt
add_executable(wpl_mqtt publish_2.cpp)

# link library
# with SSL    --> paho-mqtt3as
# without SSL --> paho-mqtt3a
target_link_libraries(wpl_mqtt paho-mqttpp3 paho-mqtt3as Threads::Threads)

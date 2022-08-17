# WPL - MQTT repository

## Install
### eclipse/paho.mqtt.cpp
### https://github.com/eclipse/paho.mqtt.cpp

- sudo apt-get install build-essential gcc make cmake cmake-gui cmake-curses-gui
- sudo apt-get install libssl-dev
- sudo apt-get install doxygen graphviz

- Before building the C++ library, first, build and install the Paho C library
- Building the Paho C library
- git clone https://github.com/eclipse/paho.mqtt.c.git
- cd paho.mqtt.c
- git checkout v1.3.8
- cmake -Bbuild -H. -DPAHO_ENABLE_TESTING=OFF -DPAHO_BUILD_STATIC=ON -DPAHO_WITH_SSL=ON -DPAHO_HIGH_PERFORMANCE=ON
- sudo cmake --build build/ --target install
- sudo ldconfig
#### This builds with SSL/TLS enabled. If that is not desired, omit the -DPAHO_WITH_SSL=ON

- Building the Paho C++ library
- git clone https://github.com/eclipse/paho.mqtt.cpp
- cd paho.mqtt.cpp
- cmake -Bbuild -H. -DPAHO_BUILD_STATIC=ON -DPAHO_BUILD_DOCUMENTATION=TRUE -DPAHO_BUILD_SAMPLES=TRUE
- sudo cmake --build build/ --target install
- sudo ldconfig

### Supported Network Protocols
The library supports connecting to an MQTT server/broker using TCP, SSL/TLS,
and websockets (secure and unsecure). This is chosen by the URI supplied to
the connect() call. It can be specified as:

- "tcp://<host>:<port>"  - TCP (unsecure)
- "ssl://<host>:<port>"  - SSL/TLS
- "ws://<host>:<port>"   - Unsecure websockets
- "wss://<host>:<port>"  - Secure websockets

#### Note that to use "ssl://" or "wss://" you must compile the library with OpenSSL, and you must supply a set of ssl_options with the connect_options.

# - END
cmake_minimum_required(VERSION 3.0.0)
project(Program1 VERSION 0.1.0)

set(SOURCES
    main.cpp
    src/PacketAnalyzer/PacketAnalyzer.cpp
    src/PacketHandler/PacketHandler.cpp
    src/Packet/Packet.cpp
)

add_executable(Program1 ${SOURCES})

target_include_directories(Program1 PRIVATE
    src/PacketAnalyzer
    src/PacketHandler
    src/Packet
    src/FlowInfo
)

find_library(PCAP_LIBRARY pcap)
if (NOT PCAP_LIBRARY)
    message(FATAL_ERROR "PCAP library not found")
endif()

target_link_libraries(Program1 ${PCAP_LIBRARY})

set(CMAKE_CXX_STANDARD 14)
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})

# For access the network interface
add_custom_command(
    TARGET Program1
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E echo "Setting capabilities..."
    COMMAND sudo setcap cap_net_raw,cap_net_admin=eip $<TARGET_FILE:Program1>
)
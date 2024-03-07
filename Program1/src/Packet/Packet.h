#ifndef PROGRAM1_PACKET_H
#define PROGRAM1_PACKET_H

#include <iostream>
#include <netinet/ip.h>
#include <netinet/tcp.h>
#include <netinet/udp.h>
#include <netinet/ether.h>

/**
 * @brief Class representing a network packet.
 */
class Packet
{
private:
    const struct ip* ipHeader;          /**< Pointer to the IP header structure. */
    const struct ether_header* ethernetHeader; /**< Pointer to the Ethernet header structure. */
    const struct tcphdr* tcpHeader;    /**< Pointer to the TCP header structure. */
    const struct udphdr* udpHeader;    /**< Pointer to the UDP header structure. */

public:
    Packet(const u_char *packet);

    const std::string getSourceIp() const;
    const std::string getDestIp() const;
    uint16_t getSourcePort() const;
    uint16_t getDestPort() const;

    int getPacketLength() const;
};

#endif // PROGRAM1_PACKET_H

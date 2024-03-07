#include "Packet.h"
#include <arpa/inet.h>

/**
 * @brief Constructor for the Packet class.
 *
 * Initializes the Packet object by extracting information from the provided packet data.
 *
 * @param packet Pointer to the packet data.
 */
Packet::Packet(const u_char *packet)
{
    ethernetHeader = (struct ether_header *)packet;
    // Check if the next protocol is IPv4
    if (ntohs(ethernetHeader->ether_type) == ETHERTYPE_IP)
    {
        ipHeader = (struct ip *)(packet + sizeof(struct ether_header));
        // Check if the next protocol is TCP
        if (ipHeader->ip_p == IPPROTO_TCP)
        {
            tcpHeader = (struct tcphdr *)(packet + sizeof(struct ether_header) + sizeof(struct ip));
        }
        // Check if the next protocol is UDP
        else if (ipHeader->ip_p == IPPROTO_UDP)
        {
            udpHeader = (struct udphdr *)(packet + sizeof(struct ether_header) + sizeof(struct ip));
        }
    }
}

/**
 * @brief Get the source IP address from the packet.
 *
 * This method uses the inet_ntop function to convert the source IP address
 * from network byte order to a human-readable string format.
 *
 * @return The source IP address as a string.
 *
 * The source IP address is obtained using the inet_ntop function, which requires
 * a buffer of size INET_ADDRSTRLEN for storing the string representation of the
 * IPv4 address. Additionally, the address family AF_INET is specified as the
 * parameter to inet_ntop, indicating that IPv4 addresses are being processed.
 *
 * @see http://man7.org/linux/man-pages/man3/inet_ntop.3.html
 */
const std::string Packet::getSourceIp() const
{
    char sourceIp[INET_ADDRSTRLEN];
    inet_ntop(AF_INET, &(ipHeader->ip_src), sourceIp, INET_ADDRSTRLEN);

    return std::string(sourceIp);
}

/**
 * @brief Get the destination IP address from the packet.
 *
 * @return The destination IP address as a string.
 */
const std::string Packet::getDestIp() const
{
    char destIp[INET_ADDRSTRLEN];
    inet_ntop(AF_INET, &(ipHeader->ip_dst), destIp, INET_ADDRSTRLEN);

    return std::string(destIp);
}

/**
 * @brief Get the source port from the packet.
 *
 * @return The source port.
 */
uint16_t Packet::getSourcePort() const
{
    return (ipHeader->ip_p == IPPROTO_TCP) ? ntohs(tcpHeader->source) : ntohs(udpHeader->source);
}

/**
 * @brief Get the destination port from the packet.
 *
 * @return The destination port.
 */
uint16_t Packet::getDestPort() const
{
    return (ipHeader->ip_p == IPPROTO_TCP) ? ntohs(tcpHeader->dest) : ntohs(udpHeader->dest);
}

/**
 * @brief Get the length of the packet.
 *
 * @return The length of the packet in bytes.
 */
int Packet::getPacketLength() const
{
    return ntohs(ipHeader->ip_len);
}

#ifndef PROGRAM1_FLOWINFO_H
#define PROGRAM1_FLOWINFO_H

#include <iostream>

/**
 * @brief Class for storing information about a network flow.
 */
class FlowInfo
{
public:
    std::string sourceIp; /**< Source IP address of the flow. */
    std::string destIp;   /**< Destination IP address of the flow. */
    uint16_t sourcePort;  /**< Source port of the flow. */
    uint16_t destPort;    /**< Destination port of the flow. */
    int packetCount;      /**< Number of packets in the flow. */
    int byteCount;        /**< Number of bytes transferred in the flow. */

    /**
     * @brief Default constructor for FlowInfo.
     * Initializes all members to default values.
     */
    FlowInfo() : sourceIp(""), destIp(""), sourcePort(0), destPort(0), packetCount(0), byteCount(0) {}
    
    /**
     * @brief Parameterized constructor for FlowInfo.
     *
     * @param srcIp Source IP address of the flow.
     * @param dstIp Destination IP address of the flow.
     * @param srcPort Source port of the flow.
     * @param dstPort Destination port of the flow.
     */
    FlowInfo(const std::string &srcIp, const std::string &dstIp, uint16_t srcPort, uint16_t dstPort)
        : sourceIp(srcIp), destIp(dstIp), sourcePort(srcPort), destPort(dstPort), packetCount(0), byteCount(0) {}
};

#endif // PROGRAM1_FLOWINFO_H
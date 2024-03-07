#ifndef PROGRAM1_PACKETHANDLER_H
#define PROGRAM1_PACKETHANDLER_H

#include <pcap.h>
#include <unordered_map>
#include "FlowInfo.h"

/**
 * @brief Class for handling network packets and managing flow information.
 */
class PacketHandler 
{
private:
    std::unordered_map<std::string, FlowInfo> flows;/**< Container for storing flow information. */
public:
    PacketHandler(){}

    void handlePacket(const struct pcap_pkthdr *pkthdr, const u_char *packet);

    /**
     * @brief Gets the map containing flow information.
     *
     * @return Constant reference to the map of flows.
     */
    const std::unordered_map<std::string, FlowInfo>& getFlows() const { return flows; }
};

#endif // PROGRAM1_PACKETHANDLER_H

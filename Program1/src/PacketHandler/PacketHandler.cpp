#include "PacketHandler.h"
#include "Packet.h"

/**
 * @brief Handles a network packet.
 *
 * This function processes a network packet, extracts relevant information, and updates the flow information.
 * It uses the provided packet header structure and packet data to create a Packet object and extract necessary details.
 * The flow information is then updated based on the extracted data.
 *
 * @param pkthdr Pointer to the packet header structure.
 * @param packet Pointer to the packet data.
 */
void PacketHandler::handlePacket(const struct pcap_pkthdr *pkthdr, const u_char *packet)
{
    Packet currentPacket(packet);

    // Form a key for the flow based on source and destination IP addresses and ports
    std::string flowKey = currentPacket.getSourceIp() + ':' +
                          std::to_string(currentPacket.getSourcePort()) + " -> " +
                          currentPacket.getDestIp() + ':' +
                          std::to_string(currentPacket.getDestPort());

    // If the flow does not exist in the hash table, create it
    if (flows.find(flowKey) == flows.end())
    {
        flows[flowKey] = FlowInfo(currentPacket.getSourceIp(), currentPacket.getDestIp(), currentPacket.getSourcePort(), currentPacket.getDestPort());
    }

    // Update the flow information in the hash table
    flows[flowKey].packetCount++;
    flows[flowKey].byteCount += pkthdr->len; // assuming pkthdr->len contains the packet size in bytes

    std::cout << flowKey << " " << flows[flowKey].packetCount << " " << flows[flowKey].byteCount << '\n';
}

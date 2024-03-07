#ifndef PROGRAM1_PACKETANALYZER_H
#define PROGRAM1_PACKETANALYZER_H

#include <pcap.h>
#include "FlowInfo.h"
#include "PacketHandler.h"

/**
 * @brief PacketAnalyzer class for analyzing network packets.
 */
class PacketAnalyzer 
{
private:
    PacketHandler packetHandler;

public:
    PacketAnalyzer(){}
    
    void startPacketAnalysis(int countPacketsToCapture);
    
    size_t getSizeFlows() const { return packetHandler.getFlows().size(); }

    void writeFlowsToCSV(const std::string &filename) const;
private:
    static void packetHandlerCallback(u_char *userData, const struct pcap_pkthdr *pkthdr, const u_char *packet);
};

/**
 * @brief Exception class for PacketAnalyzer.
 *
 * This class is derived from std::runtime_error and is used to throw exceptions
 * related to errors during the packet analysis process in the PacketAnalyzer class.
 */
class PacketAnalyzerException : public std::runtime_error 
{
public:
    explicit PacketAnalyzerException(const std::string &message) : std::runtime_error(message) {}
};

#endif // PROGRAM1_PACKETANALYZER_H


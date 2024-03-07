#include "PacketAnalyzer.h"
#include <fstream>

/**
 * @brief Start the packet analysis process.
 *
 * This function initiates the packet analysis process by configuring the libpcap packet capture and
 * starting the packet sniffing loop. It utilizes the provided packetHandlerCallback for processing each packet.
 *
 * @param countPacketsToCapture Number of packets to capture.
 * @throws PacketAnalyzerException if any libpcap operation fails.
 * @see pcap_lookupdev() For obtaining the network interface.
 *      [libpcap documentation](https://www.tcpdump.org/manpages/pcap_lookupdev.3pcap.html)
 * @see pcap_open_live() For opening the packet capture descriptor.
 *      [libpcap documentation](https://www.tcpdump.org/manpages/pcap_open_live.3pcap.html)
 * @see pcap_loop() For starting the packet sniffing loop.
 *      [libpcap documentation](https://www.tcpdump.org/manpages/pcap_loop.3pcap.html)
 * @see pcap_geterr() For retrieving libpcap error messages.
 *      [libpcap documentation](https://www.tcpdump.org/manpages/pcap_geterr.3pcap.html)
 */
void PacketAnalyzer::startPacketAnalysis(int countPacketsToCapture)
{
    char errbuf[PCAP_ERRBUF_SIZE]; // a character buffer to contain any potential errors from libpcap. The max error size is defined by PCAP_ERRBUF_SIZE in pcap.h

    char *dev = pcap_lookupdev(errbuf);
    if (dev == NULL)
    {
        throw PacketAnalyzerException("pcap_lookupdev() failed: " + std::string(errbuf));
    }

    pcap_t *descr = pcap_open_live(dev, BUFSIZ, 0, -1, errbuf);
    if (descr == NULL)
    {
        throw PacketAnalyzerException("pcap_open_live() failed: " + std::string(errbuf));
    }

    if (pcap_loop(descr, countPacketsToCapture, packetHandlerCallback, reinterpret_cast<u_char *>(&packetHandler)) < 0)
    {
        throw PacketAnalyzerException("pcap_loop() failed: " + std::string(pcap_geterr(descr)));
    }

    pcap_close(descr);
    std::cout << "Capture and handling packets finished\n";
}

/**
 * @brief Callback function for packet handling.
 *
 * @param userData User data.
 * @param pkthdr Packet header.
 * @param packet Packet data.
 */
void PacketAnalyzer::packetHandlerCallback(u_char *userData, const struct pcap_pkthdr *pkthdr, const u_char *packet)
{
    PacketHandler *packetHandler = reinterpret_cast<PacketHandler *>(userData);
    packetHandler->handlePacket(pkthdr, packet);
}

/**
 * @brief Write flows information to a CSV file.
 *
 * @param filename Output CSV filename.
 */
void PacketAnalyzer::writeFlowsToCSV(const std::string &filename) const
{
    try
    {
        std::ofstream outputFile(filename, std::ios::out | std::ios::trunc);

        if (!outputFile.is_open())
        {
            throw PacketAnalyzerException("Error opening file: " + filename);
        }

        // Write the header of the CSV file
        outputFile << "SourceIP,DestIP,SourcePort,DestPort,PacketCount,ByteCount\n";

        const auto &flows = packetHandler.getFlows();

        // Write information about flows
        for (const auto &entry : flows)
        {
            const FlowInfo &flow = entry.second;

            outputFile << flow.sourceIp << ',' << flow.destIp << ','
                       << flow.sourcePort << ',' << flow.destPort << ','
                       << flow.packetCount << ',' << flow.byteCount << '\n';
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error: " << e.what() << '\n';
    }

    std::cout << "Flows information written to " << filename << '\n';
}
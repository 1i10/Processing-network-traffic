#include "PacketAnalyzer.h"

/**
 * @brief Main function of the program.
 *
 * This function initiates the packet analysis process using the PacketAnalyzer class.
 *
 * @param argc Number of command-line arguments.
 * @param argv Array of command-line arguments.
 *             - argv[0]: Program executable name.
 *             - argv[1]: Count of packets to capture.
 *             - argv[2]: Output filename for the CSV file.
 * @return Returns 0 on success, 1 on error.
 */
int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        std::cerr << "Usage: " << argv[0] << " <count of packets to capture> <output filename>\n";
        return 1;
    }

    // Convert the count of packets to capture from command line argument
    int countPacketsToCapture;
    try
    {
        countPacketsToCapture = std::stoi(argv[1]);
    }
    catch (const std::invalid_argument& e)
    {
        std::cerr << "Error: Invalid count of packets to capture\n";
        return 1;
    }

    std::string outputFilename = argv[2];

    // Check if the output filename has a '.csv' extension
    size_t csvPos = outputFilename.find_last_of('.');
    if (csvPos == std::string::npos || outputFilename.substr(csvPos) != ".csv")
    {
        std::cerr << "Error: Invalid output filename. It should have a '.csv' extension\n";
        return 1;
    }

    PacketAnalyzer packetAnalyzer;
    try
    {
        packetAnalyzer.startPacketAnalysis(countPacketsToCapture);
        std::cout << "Will find " << packetAnalyzer.getSizeFlows() << " flows\n";

        packetAnalyzer.writeFlowsToCSV(outputFilename);
    }
    catch(const std::exception& e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
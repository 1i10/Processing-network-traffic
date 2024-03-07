# Description  

**run.sh** is a Bash script designed for building and running Programs 1 and 2.  
  
**Program 1:**  
  
Classifies network packets, extracts IP packet headers and TCP/UDP headers, reads IP addresses and ports from the extracted headers.  
Classifies each packet into a stream, counts the number of packets and bytes transferred in each stream.
Records information about all identified streams into a CSV file.  
  
**Program 2:**  
  
Runs after the completion of Program 1 and performs post-processing of the generated statistical information.
Reads the CSV file generated by Program 1, calculates the count of received and transmitted bytes and packets for each IP address presented in the file.  
Writes the obtained data into a new CSV file.


# Instruction for running the script

1. Before running the script, ensure it has execution permissions. Use the following command:  
  
> chmod +x run.sh

2. Make sure the required libraries are installed:
For Program1, the libpcap library is needed. Ensure it is installed on your system.  
For Program2, the pandas library is required.  
  
3. Execute the script using the following command:  
  
> ./run.sh
  
**!Note:**  *During the compilation of Program 1, you may be prompted to enter your password.  
This is required to grant access to the network interface specified in CMakeLists.txt.  
The script utilizes the sudo setcap command to set necessary capabilities for network access.  
Please provide your password when prompted during the build process.*  

4. The output CSV files generated by the programs will be located in the root directory where the run.sh script is located:  
resultProgram1.csv for the output of Program1.  
resultProgram2.csv for the output of Program2.  
  
**!Note:** *Ensure that the Python version is 3.x, and the script assumes the presence of pkg-config for checking libpcap.*

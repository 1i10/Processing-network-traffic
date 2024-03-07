#!/bin/bash

# Check the presence of the libpcap library for Program1
if ! pkg-config libpcap --exists; then
  echo "Error: libpcap library is not installed for Program1"
  exit 1
fi

# Check the presence of the pandas library for Program2
if ! python3 -c "import pandas" &> /dev/null; then
  echo "Error: pandas library is not installed for Program2"
  exit 1
fi

# Build Program1
cd Program1
mkdir -p build
cd build
cmake ..
make
cd ../..

# Run Program1 <count of packets to capture> <result output file for Program1>
echo "Running Program1..."
./Program1/build/Program1 20 resultProgram1.csv

# Run Program2 <output file from Program1> <result output file for Program2>
echo "Running Program2..."
python3 Program2/main.py resultProgram1.csv resultProgram2.csv

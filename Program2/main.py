import pandas as pd
import sys

def processCsv(inputFile, outputFile):
    try:
        # Reading the CSV file
        df = pd.read_csv(inputFile)

        # Checking if there is data for processing
        if df.empty:
            print("Error: Empty CSV file.")
            return

        # Grouping data by IP address and counting the sum of packets and bytes for each IP
        groupedData = df.groupby('SourceIP').agg({
            'PacketCount': 'sum',
            'ByteCount': 'sum'
        }).reset_index()

        # Creating a new DataFrame with the results
        resultDf = pd.DataFrame({
            'SourceIP': groupedData['SourceIP'],
            'ReceivedPacketCount': groupedData['PacketCount'],
            'ReceivedByteCount': groupedData['ByteCount'],
            'TransmittedPacketCount': 0,
            'TransmittedByteCount': 0
        })

        # If there is data about transmitted packets and bytes, update the corresponding columns
        if 'DestIP' in df.columns:
            transmittedData = df.groupby('DestIP').agg({
                'PacketCount': 'sum',
                'ByteCount': 'sum'
            }).reset_index()

            # Updating data in resultDf
            for index, row in transmittedData.iterrows():
                ip = row['DestIP']
                mask = resultDf['SourceIP'] == ip
                resultDf.loc[mask, 'TransmittedPacketCount'] = row['PacketCount']
                resultDf.loc[mask, 'TransmittedByteCount'] = row['ByteCount']

        # Writing the results to the output CSV file
        resultDf.to_csv(outputFile, index=False)

        print("Processing completed. Results saved to", outputFile)

    except FileNotFoundError:
        print("Error: File not found.")
    except pd.errors.EmptyDataError:
        print("Error: Empty CSV file.")
    except pd.errors.ParserError:
        print("Error: Invalid CSV file format.")
    except Exception as e:
        print("Error:", e)

if __name__ == "__main__":
    # Checking the presence of command line arguments
    if len(sys.argv) != 3:
        print("Usage: python3 main.py inputFile.csv outputFile.csv")
    else:
        inputFile = sys.argv[1]
        outputFile = sys.argv[2]
        processCsv(inputFile, outputFile)

# Correlations

Takes data from QC5 gain uniformity files and converts them into Gain Maps for each sector for a given chamber.

- QC5 files are downloaded manually and inserted into /Chamber_Uniformity_Data
- using the macro /Data_Pull/Get_GainMap.cc, extract data, and output GainMaps + values (CSVs) to /Results.


Using Get_GainMap.cc:

- Root
- Get_GainMap({Vec of Chamber Names}, "Folder where QC5 data is stored", "Folder to dump output files" )
  - e.g: Get_GainMap({"GE11-X-S-BARI-0001","GE11-X-S-INDIA-0004"}, "ChamberSet1", "ChamberSet1/Gain_10k" )
    - data will be drawn from: /Chamber_Uniformity_Data/ChamberSet1
    - outputs (.png + .csv) will be dumped into: /Results/ChamberSet1/Gain_10k. (assuming Gain was 10k)

Using Get_GainDeviation.cc:

- Root
- Get_GainDeviation({Vec of Chamber Names}, "Folder where Gain data for each sector is stored", "Folder to dump output files" )
- e.g: Get_GainDeviation({"GE11-X-S-BARI-0001","GE11-X-S-INDIA-0004"}, "ChamberSet1/Gain_10k", "ChamberSet1/Gain_10k" )
    - data will be drawn from: /Results/ChamberSet1/Gain_10k
    - outputs(.csv) will be dumped into /Results/ChamberSet1/Gain_10k

Threshold_Data
- Threshold data from s-curves
- Thresholds are constant for all gain, but for convenience in writing commands, added Gain_??k directory.
- See "opendir" variable in Get_GainDeviation

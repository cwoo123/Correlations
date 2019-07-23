# Correlations

Takes data from QC5 gain uniformity files and converts them into Gain Maps for each sector for a given chamber.

1. QC5 files are downloaded manually and inserted into /Chamber_Uniformity_Data
2. using the macro /Data_Pull/Get_GainMap.cc, extract data, and output GainMaps + values (CSVs) to /Results.

Using Get_GainMap.cc: 
1. Load file into Root.
2. 
  a. in Root, Get_GainMap({Vec of Chamber Names}, "Folder where QC5 data is stored", "Folder to dump output files" )
  b. e.g: Get_GainMap({"Chamber Name","Chamber Name 2",...}, "ChamberSet2", "ResultsSet2" )

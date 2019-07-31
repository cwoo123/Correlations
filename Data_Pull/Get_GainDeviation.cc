#include <TH2.h>
#include <numeric>
#include <string>
#include <vector>
#include <stdio.h>
#include <iostream>
#include <cmath>
#include <fstream>

using namespace std;

void Get_GainDeviation(vector<string>, string, string);

void Get_GainDeviation(vector<string> ch_name, string opendir, string savedir){ //savedir is redundant FIXME

  for(int iter=0; iter<ch_name.size();iter++){ // iterate over number of chambers in vector

    string chname = ch_name.at(iter);
    ifstream gain_in; // take in gain values from CSV
    ifstream threshold_in; // take in threshold values from CSV
    ofstream gaindev_out; // output gain deviation values into CSV
    string line, entry;
    char *gain_csv = new char[500];
    char *thresh_csv = new char[500];
    char *gaindev_csv = new char[500];
    vector< vector<double> > gain_mat;
    vector< vector<double> > thresh_mat;
    vector< vector<double> > gaindev_mat;
    string gainfile = "/afs/cern.ch/user/c/cwoo/Correlations/Results/"+opendir+"/"+chname+"_GainVals.csv";
    string thresholdfile= "/afs/cern.ch/user/c/cwoo/Correlations/Threshold_Data/"+opendir+"/"+chname+"_Threshold.csv";
    string gaindevfile = "/afs/cern.ch/user/c/cwoo/Correlations/Results/"+opendir+"/"+chname+"_GainDev.csv";
    double elecharge = 0.0001602; // femto

    strcpy(gain_csv, gainfile.c_str());
    strcpy(thresh_csv, thresholdfile.c_str());
    strcpy(gaindev_csv, gaindevfile.c_str());

    gain_in.open(gain_csv);

    // get gain values into a matrix
    int row_count = 0;
    while(getline(gain_in, line)){
      int column_count = 0;
      row_count+=1;
      vector<double> gainvec;
      stringstream s(line);

      while(getline(s,entry,',')){
        if(row_count==1) // skips loop when entries are column names
          break;
        column_count+=1;
        if(column_count!=1){
          gainvec.push_back(stod(entry));
        }
      }
      if(column_count>1)
        gain_mat.push_back(gainvec);
    }
    gain_in.close();

    threshold_in.open(thresh_csv);

    // get threshold values into a matrix
    row_count = 0;
    while(getline(threshold_in, line)){
      int column_count = 0;
      row_count+=1;
      vector<double> threshvec;
      stringstream s(line);

      while(getline(s,entry,',')){
        if(row_count==1) // skips loop when entries are column names
          break;
        column_count+=1;
        if(column_count!=1){
          threshvec.push_back(stod(entry));
        }
      }
      if(column_count>1)
        thresh_mat.push_back(threshvec);
    }

    threshold_in.close();

    //store gain deviation values into a matrix

    for(int row=0; row<8; row++){
      vector<double> gaindev_vec;
      for(int col=0; col<3; col++){
        double gaindev_value = ( (gain_mat[row][col]*elecharge*(30/3)) - thresh_mat[row][col] ) / thresh_mat[row][col];
        gaindev_vec.push_back(gaindev_value);
      }
      gaindev_mat.push_back(gaindev_vec);
    }

    // print values, according to correct chamber "coordinates"
    cout<<"The normalised GainDev values for "<<chname<<" are:"<<endl;
    for(int i=0; i<8; i++){
      for(int l=0;l<3;l++)
      {
        cout<<gaindev_mat[i][l]<<" ";
      }
      cout<<endl;
    }

  gaindev_out.open(gaindev_csv);
  gaindev_out<<chname+", "<<endl;
  gaindev_out<<"VFAT, "<<endl;
  int count=0;
  for(int col=0;col<3;col++){
    for(int row=0;row<8;row++){
      gaindev_out<<count++<<", "<<gaindev_mat[row][col]<<endl;
    }
  }
  gaindev_out.close();
  cout<<chname<<"_GainDev.csv created"<<endl;
  }

}

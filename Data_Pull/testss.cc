// file location /afs/cern.ch/user/h/hkeller/public/GE11-X-S-INDIA-0004_FreameworkAna.root
// Open file
// extract tgrapherror objects: with names...g_iEtaN_clustADC_Fit_PkPos where N in 1..8
// extract data points from each, and store into an vector. 96 data points per eta graph
// mean values

// extracting from multigraph, graph by graph

// find total average. |sector mean - totalavg|/totalavg * 3*10^4


#include <TFile.h>
#include <TMultiGraph.h>
#include <TList.h>
#include <TCollection.h>
#include <numeric>
#include <string>
#include <vector>
#include <stdio.h>
#include <iostream>
#include <cmath>

using namespace std;

void test(){

  TObject *graph_obj;
  TGraph *gr[8]; // 8 graphs in array, for each eta partition
  TMultiGraph *mg = new TMultiGraph();
  TList* grlist;
  vector< vector<double> > ydata_mat; // 8 rows, 96 columns.
  vector< vector<double> > xdata_mat;
  vector< vector<double> > partition_mean; // mean value for each partition.
  vector< vector<double> > abs_gain;
  vector<double> eta_mean;



  TFile *file = new TFile("/afs/cern.ch/user/h/hkeller/public/GE11-X-S-INDIA-0004_FreameworkAna.root", "READ");
  file->GetObject("Summary/mgraph_GE11-X-S-INDIA-0004_ResponseFitPkPos_AllEta",mg);
  grlist = mg->GetListOfGraphs();
  TIter next(grlist);

  int i = 0;
  double xpoint = -99999;
  double ypoint = -99999;

  while ( (graph_obj = next()) ){
    vector<double> ydata_vec;
    vector<double> xdata_vec;
  	gr[i]=(TGraph*)graph_obj;
    for(int element = 0; element<gr[i]->GetN(); element++ ){
      xpoint = gr[i]->GetPoint(element, xpoint, ypoint);
      xdata_vec.push_back(xpoint);
      ydata_vec.push_back(ypoint);
    }

    xdata_mat.push_back(xdata_vec);
    ydata_mat.push_back(ydata_vec);
    i++;
  }

  for(int row=0; row<8 ; row++){
    vector<double> phi1_vec(ydata_mat[row].begin(), ydata_mat[row].begin()+32);
    vector<double> phi2_vec(ydata_mat[row].begin()+32, ydata_mat[row].begin()+64);
    vector<double> phi3_vec(ydata_mat[row].begin()+64, ydata_mat[row].begin()+96);
    double mean_phi1 = accumulate( phi1_vec.begin(), phi1_vec.end(), 0.0)/32;
    double mean_phi2 = accumulate( phi2_vec.begin(), phi2_vec.end(), 0.0)/32;
    double mean_phi3 = accumulate( phi3_vec.begin(), phi3_vec.end(), 0.0)/32;
    eta_mean = {mean_phi1, mean_phi2, mean_phi3};
    partition_mean.push_back(eta_mean);
  }

  double chamber_sum = 0;
  double chamber_mean = 0;
  for(int row=0;row<8;row++){
    for(int col = 0; col<3; col++){
      chamber_sum+=partition_mean[row][col];
    }
  }
  chamber_mean = chamber_sum/24;

  // compute gain per eta
  for(int row=0;row<8;row++){
    vector<double> absgain_row;
    for(int col = 0; col<3; col++){
      absgain_row.push_back( (partition_mean[row][col]/chamber_mean)*(3*pow(10,4)) ) ;
    }
    abs_gain.push_back(absgain_row);
  }
  // print values:
  cout<<"The mean ADC counts per eta are: "<<endl;
  for(int row=0;row<8;row++){
    for(int col = 0; col<3; col++){
      cout<<partition_mean[row][col]<<" ";
    }
    cout<<endl;
  }
  cout<<endl;
  cout<<"Mean ADC for chamber is: "<<chamber_mean<<endl;
  cout<<endl;
  cout<<"The absgain/eta's are: "<<endl;
  for(int row=0;row<8;row++){
    for(int col = 0; col<3; col++){
      cout<<abs_gain[row][col]<<" ";
    }
    cout<<endl;
  }
  cout<<endl;
}

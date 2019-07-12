// file location /afs/cern.ch/user/h/hkeller/public/GE11-X-S-INDIA-0004_FreameworkAna.root
// Open file
// extract tgrapherror objects: with names...g_iEtaN_clustADC_Fit_PkPos where N in 1..8
// extract data points from each, and store into an vector. 96 data points per eta graph
// mean values

// extracting from multigraph, graph by graph

// find total average. sectormean/totalmean * 3*10^4

#include <TH2.h>
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

void Get_GainMap(string);

void Get_GainMap(string chname){

  TObject *graph_obj;
  TGraph *gr[8]; // 8 graphs in array, for each eta partition
  TMultiGraph *mg = new TMultiGraph();

  TList* grlist;
  vector< vector<double> > ydata_mat; // 8 rows, 96 columns.
  vector< vector<double> > xdata_mat;
  vector< vector<double> > partition_mean; // mean value for each partition.
  vector< vector<double> > abs_gain;
  vector<double> eta_mean;
  char *f_name = new char[100];
  char *obj_name = new char[100];
  char *ch_name = new char[100];
  char *descript = new char[100];

  string fname = "/afs/cern.ch/user/c/cwoo/Chamber_Uniformity_Data/" + chname + ".root";
  strcpy(f_name, fname.c_str());

  TFile *file = new TFile(f_name, "READ");

  string objname = "Summary/mgraph_"+ chname +"_ResponseFitPkPos_AllEta";
  strcpy(obj_name, objname.c_str());

  file->GetObject(obj_name,mg);
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
  for(int row=1;row<=8;row++){
    for(int col=1; col<=3; col++){
      cout<<"Eta "<<row<<" Phi "<<3-col+1<<": "<<abs_gain[row-1][col-1]<<" ";
    }
    cout<<endl;
  }
  cout<<endl;

  // create TH2 obj
  strcpy(ch_name, chname.c_str());
  strcpy(descript, (chname + ": Gain Map").c_str());
  TH2F *Map = new TH2F(ch_name, descript, 8, 0.5, 8.5, 3, 0.5, 3.5);

  for(int row=1;row<=8;row++){
    int eta = 8-row+1;
    for(int col = 1; col<=3; col++){
      int phi = 3-col+1;
      Map->Fill(eta,phi,abs_gain[eta-1][col-1]);
    }
  }

  Map->SetOption("colz text0");
  Map->SetXTitle("Eta");
  Map->SetYTitle("Phi");
  Map->SetZTitle("Gain");
  Map->Draw();



}

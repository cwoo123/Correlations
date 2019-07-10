// file location /afs/cern.ch/user/h/hkeller/public/GE11-X-S-INDIA-0004_FreameworkAna.root
// Open file
// extract tgrapherror objects: with names...g_iEtaN_clustADC_Fit_PkPos where N in 1..8
// extract data points from each, and store into an vector. 96 data points per eta graph

// extracting on by one from fit

#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <cstring>
#include <TH1.h>
#include <TH2.h>
#include <TFile.h>
#include <TGraphErrors.h>
#include <TCanvas.h>
#include <stdio.h>
#include <iostream>
#include <TMultiGraph.h>
#include <TList.h>
#include <TF1.h>

using namespace std;

void read(){
  string str_name = "str_name";
  string str_ieta = "str_eta";
  string str_phi = "str_phi";
  string str_slice = "str_slice";
  char *char_name = new char[100];
  TF1 *G = new TF1();

  TFile f("/afs/cern.ch/user/h/hkeller/public/GE11-X-S-INDIA-0004_FreameworkAna.root");

  for(int ieta=1;ieta<=8;ieta++){
      str_ieta = to_string(ieta);

    for(int phi=1;phi<=3;phi++){
      str_phi = to_string(phi);

        for(int slice=1;slice<=3;slice++){
          str_slice = to_string(slice);
          str_name = "SectorEta"+str_ieta+"/SectorPhi"+str_phi+"/Slice"+str_slice+"/fit_iEta"+\
          str_ieta+"iPhi"+str_phi+"Slice"+str_slice+"_clustADC";
          strcpy(char_name, str_name.c_str());
          f.GetObject(char_name, G);
          for(int par=0;par<=2;par++)
            cout<<"eta: "<<ieta<<", phi: "<<phi<<", Slice: "<<slice<<", Parameter: "<<par<<": "<<G->GetParameter(par)<<endl;
        }
    }
}








}

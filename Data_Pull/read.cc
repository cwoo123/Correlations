// file location /afs/cern.ch/user/h/hkeller/public/GE11-X-S-INDIA-0004_FreameworkAna.root
// Open file
// extract tgrapherror objects: with names...g_iEtaN_clustADC_Fit_PkPos where N in 1..8
// extract data points from each, and store into an vector. 96 data points per eta graph
#include <fstream> // write to csv
#include <string> // vector of str
#include <sstream> // ??
#include <vector> // store into vec
#include <cstring> // ?? write to cstring to enter into plot names
#include <TH1.h> // ??
#include <TH2.h> // ??
#include <TFile.h> // pull roots
#include <TGraphErrors.h>
#include <TCanvas.h> // ??
#include <stdio.h> // ??
#include <iostream>

using namespace std;

void read(){

TGraphErrors* G = new TGraphErrors();
TFile f("/afs/cern.ch/user/h/hkeller/public/GE11-X-S-INDIA-0004_FreameworkAna.root");
f.GetObject('g_iEta1_clustADC_Fit_PkPos', G);
G->Draw();


}

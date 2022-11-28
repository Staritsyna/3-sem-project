#include "TFile.h"
#include "TTree.h"
//#include "TChain.h"
#include "TH1.h"
#include "TF1.h"
#include "TLegend.h"
#include "TRandom.h"
#include "TGraphErrors.h"
#include "TCanvas.h"
#include "TGraph2D.h"

#include <iostream> 
#include <stdio.h>  
#include <stdlib.h>
#include <fstream>  
#include <vector> 
#include <cstring>
#include "math.h"

void plot_trace2D() {

    const Int_t number_array = 100;
	
    char fname_title[number_array];
    char fname_axis_y[number_array];
    char fname_axis_x[number_array];
 TCanvas *c1 = new TCanvas("XY","graph1",200,10,700,500);
    c1->SetGrid();
    c1->SetTickx(1);
    c1->SetTicky(1);

    for (int i = 0; i < number_array; i++) {
        fname_title[i] = 0;
        fname_axis_y[i] = 0;
        fname_axis_x[i] = 0;
    }

    sprintf(fname_title, "XY ");
    sprintf(fname_axis_y, "Y");
    sprintf(fname_axis_x, "X");
    
     TCanvas *c2 = new TCanvas("YZ","graph1",200,10,700,500);
    c1->SetGrid();
    c1->SetTickx(1);
    c1->SetTicky(1);

    for (int i = 0; i < number_array; i++) {
        fname_title[i] = 0;
        fname_axis_y[i] = 0;
        fname_axis_x[i] = 0;
    }

    sprintf(fname_title, "XY ");
    sprintf(fname_axis_y, "Z");
    sprintf(fname_axis_x, "Y");
    
     TCanvas *c3 = new TCanvas("ZX","graph1",200,10,700,500);
    c1->SetGrid();
    c1->SetTickx(1);
    c1->SetTicky(1);

    for (int i = 0; i < number_array; i++) {
        fname_title[i] = 0;
        fname_axis_y[i] = 0;
        fname_axis_x[i] = 0;
    }

    sprintf(fname_title, "ZX ");
    sprintf(fname_axis_y, "Z");
    sprintf(fname_axis_x, "X");
}

 TCanvas *c00 = new TCanvas("c00","Graph2D example",0,0,600,400);
 TGraph2D *dt0 = new TGraph2D(); 

void plot_trace3D(TGraph2D * dt = dt0, float N_events = 1000){
	float cx;
  	float cy;
  	float cz;
  	std::vector<int> coorx;
  	std::vector<int> coory;
  	std::vector<int> coorz;
	std::unique_ptr<TFile> myFile( TFile::Open("file.root") ); 
	auto tree = myFile->Get<TTree>("trace_tree"); 
 	tree->SetBranchAddress("coordx", &cx); 
 	tree->SetBranchAddress("coordy", &cy);
 	tree->SetBranchAddress("coordz", &cz);
 	
 	tree->SetBranchStatus("*", false);
	tree->SetBranchStatus("coordx", true); 
 	
 
	for (int iEntry = 0; tree->LoadTree(iEntry) >= 0; ++iEntry) { 
   		tree->GetEntry(iEntry); 
 		coorx.push_back(cx);
}
	tree->SetBranchStatus("*", false);
	tree->SetBranchStatus("coordy", true); 
	for (int iEntry = 0; tree->LoadTree(iEntry) >= 0; ++iEntry) { 
   		tree->GetEntry(iEntry); 
 		coory.push_back(cy);
}
	tree->SetBranchStatus("*", false);
	tree->SetBranchStatus("coordz", true);  
	for (int iEntry = 0; tree->LoadTree(iEntry) >= 0; ++iEntry) { 
   		tree->GetEntry(iEntry); 
 		coorz.push_back(cz);
}
  
   c00->cd();
   
   dt->SetTitle("Trace; X ; Y ; Z "); 
  
   for (Int_t i=0; i< N_events; i++) 
     { dt->SetPoint(i,coorx[i], coory[i],coorz[i]);}
  
   gStyle->SetPalette(1); 
   dt->Draw("P0"); 
   dt->Draw("LINE same"); 
   
 

}

void del(){ 
	delete dt0;
	delete c00;
}

int main (){
 return 0;
}

#include "TFile.h"
#include "TTree.h"
#include "TF1.h"
#include "TLegend.h"
#include "TGraphErrors.h"
#include "TGraph2D.h"
#include "TCanvas.h"
#include "TStyle.h"
#include "TImage.h"
#include "TSystem.h"

#include <iostream> 
#include <vector> 
#include <string>

#include "plot_trace.h"


void plot_trace3D(int n){
	const int nEvents = 2000;
	
	TCanvas *c00 = new TCanvas("c00","Graph2D example",0,0,600,600);
	TGraph2D *dt = new TGraph2D(); 
	
	std::vector<float>  cx(n,0);
  	std::vector<float>  cy(n,0);
  	std::vector<float>  cz(n,0);
  	std::vector<float> coorx;
  	std::vector<float> coory;
  	std::vector<float> coorz;
  	
	std::unique_ptr<TFile> myFile( TFile::Open("/home/anna/project/fileTrace.root") ); 
	auto tree = myFile->Get<TTree>("tree"); 
	for (int i = 0; i < n; i++){
        	char brnch[120];
		sprintf(brnch,"coordx%d",i);
        	tree->SetBranchAddress(brnch, &cx[i]);
        	sprintf(brnch,"coordy%d",i);
        	tree->SetBranchAddress(brnch, &cy[i]);
        	sprintf(brnch,"coordz%d",i); 
        	tree->SetBranchAddress(brnch, &cz[i]); 
        
	}
 	for (int i = 0; i < n; i++){	
 		char brnch[120];
		sprintf(brnch,"coordx%d",i);
 		tree->SetBranchStatus("*", false);
		tree->SetBranchStatus(brnch, true); 
 	
		for (int iEntry = 0; tree->LoadTree(iEntry) >= 0; ++iEntry) { 
   			tree->GetEntry(iEntry); 
 			coorx.push_back(cx[i]);
 			
		}
		sprintf(brnch,"coordy%d",i);
		tree->SetBranchStatus("*", false);
		tree->SetBranchStatus(brnch, true); 
		for (int iEntry = 0; tree->LoadTree(iEntry) >= 0; ++iEntry) { 
   			tree->GetEntry(iEntry); 
 			coory.push_back(cy[i]);	
		}
	
		tree->SetBranchStatus("*", false);
		sprintf(brnch,"coordz%d",i);
		tree->SetBranchStatus(brnch, true);  
	
		for (int iEntry = 0; tree->LoadTree(iEntry) >= 0; ++iEntry) { 
   			tree->GetEntry(iEntry); 
 			coorz.push_back(cz[i]);
		}
  	}
   		c00->cd();
   		dt->SetTitle("Trace; X ; Y ; Z "); 
  
   		

   	for (Int_t i=0; i< nEvents*n; i++) {
      			dt->SetPoint(i,coorx[i], coory[i],coorz[i]);
   		}
        gStyle->SetPalette(1); 
        dt->Draw("P0"); 
        gSystem->ProcessEvents(); 
 
        TImage *img = TImage::Create(); 
  
        img->FromPad(c00); 
 
        img->WriteImage("/home/anna/project/canvas.png");
 
}


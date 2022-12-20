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

//drawing the plot ( n - number of particles)
void plot_trace3D(int n){

	const int nPoints = 10000;
	
	TCanvas *c00 = new TCanvas("c00","Graph2D ",0,0,600,600);
	TGraph2D *dt = new TGraph2D(); 
	
	std::vector<double>  cx(n,0);
  	std::vector<double>  cy(n,0);
  	std::vector<double>  cz(n,0);
  	std::vector<double> coorx;
  	std::vector<double> coory;
  	std::vector<double> coorz;
  	
  	//opent the file "fileTrace.root"
	std::unique_ptr<TFile> myFile( TFile::Open("/home/anna/project/fileTrace.root") ); 
	auto tree = myFile->Get<TTree>("tree"); 
	
	//reading and filling vectors
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
   		dt->SetTitle("Trace; X*10^-5; Y*10^-5 ; Z*10^-5 "); 
  
   		

   	for (Int_t i=0; i< nPoints*n; i++) {
      			dt->SetPoint(i,coorx[i], coory[i],coorz[i]);
   	}
        gStyle->SetPalette(1); 
        dt->Draw("P0"); 
        gSystem->ProcessEvents(); 
 	
 	//save the picture
        TImage *img = TImage::Create(); 
  
        img->FromPad(c00); 
 
        img->WriteImage("/home/anna/project/canvas.png");
 
}


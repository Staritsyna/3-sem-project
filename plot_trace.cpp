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


void plot_trace3D(){
	float N_events = 2000;
	TCanvas *c00 = new TCanvas("c00","Graph2D example",0,0,600,600);
	TGraph2D *dt = new TGraph2D(); 
	float cx;
  	float cy;
  	float cz;
  	std::vector<float> coorx;
  	std::vector<float> coory;
  	std::vector<float> coorz;
	std::unique_ptr<TFile> myFile( TFile::Open("/home/anna/project/file.root") ); 
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
   gSystem->ProcessEvents(); 
 
   TImage *img = TImage::Create(); 
 
   //img->FromPad(c, 10, 10, 300, 200); 
   img->FromPad(c00); 
 
   img->WriteImage("/home/anna/project/canvas.png");
 
}


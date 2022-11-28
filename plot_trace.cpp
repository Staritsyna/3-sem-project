#include "TFile.h"
#include "TTree.h"
//#include "TChain.h"
#include "TH1.h"
#include "TF1.h"
#include "TLegend.h"
#include "TGraphErrors.h"
#include "TCanvas.h"

#include <iostream> 
#include <stdio.h>  
#include <stdlib.h>
#include <fstream>  
#include <cstring>
#include "math.h"

void plot_trace() {

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
int main (){
 return 0;
}

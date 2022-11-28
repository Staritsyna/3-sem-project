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

/*class Function final {

   public:
   Function();
   
  // operator+;
  // operator -;
};
Function function_def(std::string B){
   Function res_fun();
   for (int i = 0; i < B.length(); i++){
   	if (B[i] == 'x' )  {
   	 if (B[i+1] == '*' )  {
   	 
   	
   	}
   }
   return res_fun();



}}*/
void input(){

  float x_o;
  float y_o;
  float z_o;

  float Vx_o;
  float Vy_o;
  float Vz_o;
  
  std::string B_x;
  std::string B_y;
  std::string B_z;

  std::cout << "Enter the initial coordinates of  the particle (x, y, z)" << std::endl;
  std::cin >> x_o >> y_o >> z_o ;
  
  std::cout << "Enter the initial velocity of  the particle (Vx, Vy, Vz)" << std::endl;
  std::cin >> Vx_o >> Vy_o >> Vz_o;
  
  std::cout << "Enter a dependency B_x (x, y, z)" << std::endl;
  std::cin >> B_x;
  
  std::cout << "Enter a dependency B_y (x, y, z)" << std::endl;
  std::cin >> B_y;
  
  std::cout << "Enter a dependency B_z (x, y, z)" << std::endl;
  std::cin >> B_z;

}

void full(float x_o,float y_o,float z_o,float Vx_o, float Vy_o,float Vz_o, float m,float q){
	float B_x=5;
	float B_y=0;
	float B_z=0;
	float x=x_o;
  	float y=y_o;
  	float z=z_o;
  	float t=0.1;

  	float Vx=Vx_o;
  	float Vy=Vy_o;
  	float Vz=Vz_o;
  	float a_x;
  	float a_y;
  	float a_z;
        std::unique_ptr<TFile> myFile( TFile::Open("file.root", "RECREATE") ); 
        auto tree = std::make_unique<TTree>("tree", "The Tree Title"); 
 

        tree->Branch("coordinate x", &x); 
        tree->Branch("coordinate y", &y); 
        tree->Branch("coordinate z", &z); 
        tree->Branch("Vx", &Vx); 
        tree->Branch("Vy", &Vy); 
        tree->Branch("Vz", &Vz); 
        //tree->Branch("time", &t); 

 
for (int iEntry = 0; iEntry < 1000; ++iEntry) { 
   a_x=q*(Vy*B_z-Vz*B_y)/m;
   a_y=q*(Vz*B_x-Vx*B_z)/m;
   a_z=q*(Vx*B_y-Vy*B_x)/m;
   Vx+=t*a_x;
   Vy+=t*a_y;
   Vz+=t*a_z;
   x+=(Vx*t+0.5*t*t*a_x);
   y+=(Vy*t+0.5*t*t*a_y);
   z+=(Vz*t+0.5*t*t*a_z);
   // Fill the current value of var into branch0 
   tree->Fill(); 
  
} 
 
// Now write the header 
tree->Write();

}


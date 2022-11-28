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

class Function final {

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



}
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

